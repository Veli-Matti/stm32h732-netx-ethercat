/**************************************************************************************
 Exclusion of Liability for this demo software:
 The following software is intended for and must only be used for reference and in an
 evaluation laboratory environment. It is provided without charge and is subject to
 alterations. There is no warranty for the software, to the extent permitted by
 applicable law. Except when otherwise stated in writing the copyright holders and/or
 other parties provide the software "as is" without warranty of any kind, either
 expressed or implied.
 Please refer to the Agreement in README_DISCLAIMER.txt, provided together with this file!
 By installing or otherwise using the software, you accept the terms of this Agreement.
 If you do not agree to the terms of this Agreement, then do not install or use the
 Software!
 **************************************************************************************/

/**************************************************************************************

 Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

 ***************************************************************************************
 $Id: UserInterface.c 3234 2017-07-19 12:22:45Z dirk $

 Description:
 The functions defined in this C-Module are called from the cifXApplicationDemo.
 These functions are protocol independent.
 This module must be adapted to the used Host System. I.e. it is hardware dependent
 and acts as an Hardware Abstraction Layer.
 In this implementation, STM32 HAL functions are used.


 Changes:
 Date        Description
 -----------------------------------------------------------------------------------
 2017-02-16  initial version

 **************************************************************************************/

#include "main.h"
#include "cifXApplicationDemo.h"
#include "UserInterface.h"
#include "OS_Dependent.h"
#include <stdio.h>

/** STATUS LEDS ****************************/
#define UI_STAT_LED_STATUS_MSK  0x01 /** LED P411 */
#define UI_STAT_LED_DATA_MSK    0x02 /** LED P410 */
#define UI_STAT_LED_ERROR_MSK   0x04 /** LED P409 */
#define UI_STAT_LED_ALARM_MSK   0x08 /** LED P408 */

static uint8_t g_cStatusLed = 0; /* status LED register */
// VMK
//extern UART_HandleTypeDef UartHandle;
//extern GPIO_TypeDef *GPIO_PORT[];
//extern const uint16_t GPIO_PIN[];

//static void Error_Handler(void);

UI_RESULT_E UserInterface_updateStatLed(void);

void (*g_pfTimerCallback)(void *pPrm) = NULL;
void *g_pTimerPrm = NULL;

/* TIM handle declaration */
//TIM_HandleTypeDef TimHandle;

/* Prescaler declaration */
__IO uint32_t uwPrescalerValue = 0;

// VMK
#if 0
/**
 * @brief  Period elapsed callback in non blocking mode
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

    if (g_pfTimerCallback != NULL) {
        g_pfTimerCallback(g_pTimerPrm);
    }
}
#endif

/**
 * @brief  Returns the user Button state.
 * @param  None
 * @retval The Button GPIO pin value.
 */
static uint32_t UserInterfaceGetUserButtonState()
{
	return HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin);
}

/**********************************************************************************//**
 Initializes the IO hardware
 \return         eRslt ( UI_OK == succeeded )
 **************************************************************************************/
UI_RESULT_E UserInterface_init(void) {
// VMK
#if 0
    /*setup timer*/
    /*##-1- Configure the TIM peripheral #######################################*/
    /* -----------------------------------------------------------------------
     In this example TIM3 input clock (TIM3CLK)  is set to APB1 clock (PCLK1) x2,
     since APB1 prescaler is equal to 4.
     TIM3CLK = PCLK1*2
     PCLK1 = HCLK/4
     => TIM3CLK = HCLK/2 = SystemCoreClock/2
     To get TIM3 counter clock at 10 KHz, the Prescaler is computed as follows:
     Prescaler = (TIM3CLK / TIM3 counter clock) - 1
     Prescaler = ((SystemCoreClock/2) /10 KHz) - 1

     Note:
     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f7xx.c file.
     Each time the core clock (HCLK) changes, user had to update SystemCoreClock
     variable value. Otherwise, any configuration based on this variable will be incorrect.
     This variable is updated in three ways:
     1) by calling CMSIS function SystemCoreClockUpdate()
     2) by calling HAL API function HAL_RCC_GetSysClockFreq()
     3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
     ----------------------------------------------------------------------- */

    /* Compute the prescaler value to have TIMx counter clock equal to 10000 Hz */
    uwPrescalerValue = (uint32_t) ((SystemCoreClock / 2) / 10000) - 1;

    /* Set TIMx instance */
    TimHandle.Instance = TIMx;

    /* Initialize TIMx peripheral as follows:
     + Period = 10000 - 1
     + Prescaler = ((SystemCoreClock / 2)/10000) - 1
     + ClockDivision = 0
     + Counter direction = Up
     */
    //	  TimHandle.Init.Period            = 10 - 1; // 10-1 = 1msec
    TimHandle.Init.Period = 100 - 1;
    TimHandle.Init.Prescaler = uwPrescalerValue;
    TimHandle.Init.ClockDivision = 0;
    TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
    TimHandle.Init.RepetitionCounter = 0;

    if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK) {
        /* Initialization Error */
        Error_Handler();
    }

    /*##-2- Start the TIM Base generation in interrupt mode ####################*/
    /* Start Channel1 */
    if (HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK) {
        /* Starting Error */
        Error_Handler();
    }

    /* Configure LED1, LED2 and LED3 */
    BSP_LED_Init(LED1);
    BSP_LED_Init(LED2);
    BSP_LED_Init(LED3);

    BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
    BSP_LED_Off(LED1);
    BSP_LED_Off(LED2);
    BSP_LED_Off(LED3);
#endif
    return UI_OK;
}

/**********************************************************************************//**
 Function puts output data to LEDs
 \param[in]      ulData cyclic output data to be displayed UI_OUTPUT_BITS wide
 \return         eRslt ( UI_OK == succeeded )
 **************************************************************************************/
UI_RESULT_E UserInterface_putOutData(uint32_t ulData) {
    /*due to limited number of available LEDs on Nucelo board, map only 2 data bits to two LEDs*/
    HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin,
            ulData & 0x00000008 ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin,
            ulData & 0x00000800 ? GPIO_PIN_SET : GPIO_PIN_RESET);

    return UI_OK;
}

/**********************************************************************************//**
 Function puts output data to the console
 \param[in]      ulData cyclic output data to be displayed UI_OUTPUT_BITS wide
 \return         eRslt ( UI_OK == succeeded )
 **************************************************************************************/
UI_RESULT_E UserInterface_putStatLed(uint32_t ulData) {
    return UI_OK;
}

/**********************************************************************************//**
 Function set the defined status LED "on"
 \param[in]     specifies the status LED
 \return        eRslt ( UI_OK == succeeded )
 **************************************************************************************/
UI_RESULT_E UserInterface_putStatLedOn(UI_STATUS_LED_TYPE_E eStatusLed) {
    switch (eStatusLed) {
    case UI_STAT_LED_ALARM:
        g_cStatusLed |= UI_STAT_LED_ALARM_MSK;
        break;
    case UI_STAT_LED_ERROR:
        g_cStatusLed |= UI_STAT_LED_ERROR_MSK;
        break;
    case UI_STAT_LED_STATUS:
        g_cStatusLed |= UI_STAT_LED_STATUS_MSK;
        break;
    case UI_STAT_LED_DATA:
        g_cStatusLed |= UI_STAT_LED_DATA_MSK;
        break;
    default:
        return UI_UNKNOWN_STAT_LED;
    }

    UserInterface_updateStatLed();
    return UI_OK;
}

UI_RESULT_E UserInterface_updateStatLed(void) {
    /* map only the ALARM and ERROR flags to one LED (or'ed) , other status flags are ignored due to limited number of status LEDs*/
    if (g_cStatusLed & (UI_STAT_LED_ERROR_MSK | UI_STAT_LED_ALARM_MSK)) {
        HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
    }
    return UI_OK;
}

/**********************************************************************************//**
 Function set the defined status LED "off"
 \param[in]     specifies the status LED
 \return        eRslt ( UI_OK == succeeded )
 **************************************************************************************/
UI_RESULT_E UserInterface_putStatLedOff(UI_STATUS_LED_TYPE_E eStatusLed) {
    switch (eStatusLed) {
    case UI_STAT_LED_ALARM:
        g_cStatusLed &= ~UI_STAT_LED_ALARM_MSK;
        break;
    case UI_STAT_LED_ERROR:
        g_cStatusLed &= ~UI_STAT_LED_ERROR_MSK;
        break;
    case UI_STAT_LED_STATUS:
        g_cStatusLed &= ~UI_STAT_LED_STATUS_MSK;
        break;
    case UI_STAT_LED_DATA:
        g_cStatusLed &= ~UI_STAT_LED_DATA_MSK;
        break;
    default:
        return UI_UNKNOWN_STAT_LED;
    }

    UserInterface_updateStatLed();
    return UI_OK;
}

/**********************************************************************************//**
 Function returns process data
 \param[in]
 \return        eRslt ( UI_OK == succeeded )
 **************************************************************************************/
uint32_t UserInterface_getInData(void) {

	uint32_t ulTempInput = 0;

    ulTempInput = UserInterfaceGetUserButtonState();

    return ((uint32_t) ulTempInput);
}

/**********************************************************************************//**
 Function returns rotary switch input
 since Nucleo-144 features just one user push button but no rotary switches, we
 "emulate" rotary switch input by shifting the bush button bit
 \param[in]
 \return        eRslt ( UI_OK == succeeded )
 **************************************************************************************/
uint32_t UserInterface_getRotary(void) {

    uint32_t ulTempInput = 0;

    ulTempInput = (UserInterfaceGetUserButtonState() << 2)
            + (UserInterfaceGetUserButtonState() << 4 << 3);

    return ((uint32_t) ulTempInput);
}

uint8_t UserInterface_getRotary0(void) {

    uint32_t ulTempInput = 0;

    ulTempInput = UserInterfaceGetUserButtonState() << 2;

    return ((uint8_t) ulTempInput);
}

uint8_t UserInterface_getRotary1(void) {

    uint32_t ulTempInput = 0;

    ulTempInput = UserInterfaceGetUserButtonState() << 3;

    return ((uint8_t) ulTempInput);
}

/**********************************************************************************//**
 Function returns diagnosis DIP switch
 \param[in]
 \return        eRslt ( UI_OK == succeeded )
 **************************************************************************************/
UI_DIAG_T UserInterface_getDiag(void) {

    UI_DIAG_T tDiag = { { 0 } };

    tDiag.fAlarm0 = UserInterfaceGetUserButtonState();
    tDiag.fError0 = UserInterfaceGetUserButtonState();

    return tDiag;
}

/*
 UI_RESULT_E UserInterface_getTemp(uint32_t *ulData);
 */

/**********************************************************************************//**
 Function returns diagnosis DIP switch
 \param[in]
 \return        eRslt ( UI_OK == succeeded )
 **************************************************************************************/
uint8_t UserInterface_getDiagAlarm0(void) {

	uint8_t ulTempInput = 0;

	ulTempInput = UserInterfaceGetUserButtonState();

	return ((uint8_t) ulTempInput);
}

/**********************************************************************************//**
 Function returns diagnosis DIP switch
 \param[in]
 \return        eRslt ( UI_OK == succeeded )
 **************************************************************************************/
uint8_t UserInterface_getDiagError0(void) {

	uint8_t ulTempInput = 0;

    ulTempInput = UserInterfaceGetUserButtonState();

    return ((uint8_t) ulTempInput);
}

/*****************************************************************************/
/*! registers callback function
 *   \param eClbType callback type
 *   \param pfnEventClb callback function pointer
 *   \param pPrm parameters
 *   \return UI_OK on success                                                 */
/*****************************************************************************/
UI_RESULT_E UserInterface_registerCallback(UI_CALLBACK_TYPE_E eClbType,
        void (*pfnEventClb)(void *pPrm), void *pPrm) {
    switch (eClbType) {
    case UI_CB_TIMER:
        g_pfTimerCallback = pfnEventClb;
        g_pTimerPrm = pPrm;
        break;
    default:
        return UI_UNKNOWN_CALLBACK_TYPE;
    }
    return UI_OK;
}

/*****************************************************************************/
/*! Enable callback functions
 *   \return UI_OK on success                                                 */
/*****************************************************************************/
UI_RESULT_E UserInterface_enableCallbacks(void) {
    //  NX51_VIC_SetIrqVector(0, 2, UserInterface_timerIsr);
    //  NX51_VIC_EnableIrqSources(1 << 2);  /** TIMER1 IRQ*/
    return UI_OK;
}

/*****************************************************************************/
/*! Disable callback functions
 *   \return UI_OK on success                                                 */
/*****************************************************************************/
UI_RESULT_E UserInterface_disableCallbacks(void) {
    //  NX51_VIC_DisableIrqSources(1 << 2);  /** TIMER1 IRQ*/
    return UI_OK;
}

int UserInterface_kbhit(void) {
    // VMK
    return 0;
    //return __HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_RXNE);
}

void UserInterface_Sleep(uint32_t ulSleepTimeMs) {
    HAL_Delay(ulSleepTimeMs);
}
