/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id: npx_core_api.h 3816 2018-02-28 16:09:11Z dirk $

  Description:
    netPROXY Server API

  NOTE:
    Do not include this file separate. This file will included in the correct order
    by using netPROXY.h

**************************************************************************************/
#ifndef __NPX_CORE_API_H
#define __NPX_CORE_API_H
/*! \addtogroup npx_sys_functions
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif  /* _cplusplus */


/*! netPROXY handle.
 * The handle is used to access the local netPROXY server component.
 * */
typedef struct NPX_HANDLE_Ttag* NPX_H;

/*! Function callback to receive a object or element string of a specific object.
 *
 * \note There is a reference implementation available in specified in npx_extensions_api.h
 *
 * \param pvObjectDescriptionUserParameter [in]  given user parameter
 * \param ulObjectID                       [in]  Object ID of the requested string
 * \param ulElement                        [in]  Element ID of requested string. 0xFFFFFFFF (::NPX_ELEMENT_NO_OBJECT_INSTANCE)
 *                                               request the object name
 * \param szStringBuffer                   [out] Pointer to a \0 terminated string which can hold up to
 *                                               ::NPX_MAX_DESCRIPTION_STRING_LEN bytes.
 *
 * */
typedef void (APIENTRY *Npx_GetObjectDescriptionStrings)(
    void*       pvObjectDescriptionUserParameter,
    uint32_t    ulObjectID,
    uint32_t    ulElement,
    char*       szStringBuffer
);

/*! Set a new name for a object or element string of a specific object.
 *
 * \note There is a reference implementation available in specified in npx_extensions_api.h
 *
 *
 * \param pvObjectDescriptionUserParameter [in]  given user parameter
 * \param ulObjectID                       [in]  Object ID of the requested string
 * \param ulElement                        [in]  Element ID of requested string. 0xFFFFFFFF (::NPX_ELEMENT_NO_OBJECT_INSTANCE)
 *                                               request the object name
 * \param szStringBuffer                   [in]  Pointer to a buffer with the new string.
 *
 * */
typedef void (APIENTRY *Npx_SetObjectDescriptionStrings)(
    void*       pvObjectDescriptionUserParameter,
    uint32_t    ulObjectID,
    uint32_t    ulElement,
    const char* szStringBuffer
);

/*! Delete all strings for a specific object.
 *
 * \note There is a reference implementation available in specified in npx_extensions_api.h
 *
 * \param pvObjectDescriptionUserParameter [in]  given user parameter
 * \param ulObjectID                       [in]  Object ID of the requested string
 *
 * */
typedef void (APIENTRY *Npx_DelObjectDescriptionStrings)(
    void*       pvObjectDescriptionUserParameter,
    uint32_t    ulObjectID
);


/* Default configuration values for V1 */
#define NPX_CORE_CONFIG_VERSION_V1                       1
#define NPX_CORE_CONFIG_DEFAULT_NUMBER_OF_LOG_ENTRIES   16

/* Default configuration values for V2 */
#define NPX_CORE_CONFIG_VERSION_V2                                    2
#define NPX_CORE_CONFIG_DEFAULT_NUMBER_OF_LOG_ENTRIES                 16
#define NPX_CORE_CONFIG_DEFAULT_GET_OBJECT_DESCRIPTION_CALLBACK       NULL
#define NPX_CORE_CONFIG_DEFAULT_SET_OBJECT_DESCRIPTION_CALLBACK       NULL
#define NPX_CORE_CONFIG_DEFAULT_DEL_OBJECT_DESCRIPTION_CALLBACK       NULL
#define NPX_CORE_CONFIG_DEFAULT_OBJECT_DESCRIPTION_USER_PARAM         NULL

/*! Core configuration structure.
 *
 * \note
 * To invent or extend the configuration structure, add a new struct within
 * the union with the next free available number.
 *
 */
typedef struct NPX_CORE_CONFIG_Ttag {
  uint32_t ulCoreConfigVersion;           /*!< This value defines which version union will be used */

  /* This union holds all different versions of the configuration structure */
  union {
    /* configuration Version 1 structure */
    struct NPX_CORE_CONFIG_V1_Ttag {
      uint32_t ulNumberOfEventLogEntries;   /*!< Amount of log entries which the log book can hold   */
    } tVersion1;

    struct NPX_CORE_CONFIG_V2_Ttag {
      uint32_t ulNumberOfEventLogEntries;   /*!< Amount of log entries which the log book can hold   */

      Npx_GetObjectDescriptionStrings pfnGetObjectDescriptionStr;
      Npx_SetObjectDescriptionStrings pfnSetObjectDescriptionStr;
      Npx_DelObjectDescriptionStrings pfnDelObjectDescriptionStr;
      void*                           pvObjectDescriptionUserParameter;

    } tVersion2;


  } unVersion;
}NPX_CORE_CONFIG_T;


/*! System initialization of netPROXY.
 *
 * This function initialize the netPROXY server and must be called during
 * system initialization. Must be called during system initialization before
 * any other netPROXY function is called. The netPROXY core is a singleton and
 * can only initialized once in a system.
 *
 * \note Once the netPROXY in initialized it is not possible to delete the core afterward
 *
 * \param ptConfig [in] Configuration structure for the netPROXY core
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_Init(const NPX_CORE_CONFIG_T *ptConfig);

/*! Open the netPROXY server.
 *
 * To work with the netPROXY a handle to the server must be open. This handle
 * is used afterwards to create, open or close netPROXY Interfaces.
 *
 * \param phNpx [out] pointer to variable to store handle to
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_Open(NPX_H* phNpx);

/*! Closes the netPROXY server.
 *
 * \note Should be the last call to be processed by an application.
 *
 * \note Freeing the same handle twice is not allowed, the function will not check the handle again.
 *       Doing so will invoke undefined behavior!
 *
 * \param hNpx [in] handle to netPROXY
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_Close(NPX_H hNpx);

/*! @}*/
#endif /* __NPX_CORE_API_H */
