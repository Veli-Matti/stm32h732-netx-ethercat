/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id:: NpxPck_Hif_Public.h 3816 2018-02-28 16:09:11Z dirk                     $ *//**

  \note  This file is generated automatically.

  \brief Hif package

**************************************************************************************/

#ifndef __NETPROXY_PACKAGE_HIF_PUBLIC_H
#define __NETPROXY_PACKAGE_HIF_PUBLIC_H

#include "npx_types.h"
#include "npx_package_api.h"

#include "PS_Toolbox_Public.h"

#include "NpxPck_Hif_Packet.h"

/******************************************************************************
 *  Package will add messages with following markers (bMarker) to
 *  the netPROXY event log (in critical situations)
 ******************************************************************************/
/* error occurred on returning packet to the tasks packet pool */
#define NPXPCK_HIF_EVENT_LOG_MARKER_TASK_POOL_ERROR  1

/******************************************************************************/
/*  Package configuration parameter version                                   */
/******************************************************************************/
#define NPXPCK_HIF_CONFIG_PARAM_VERSION_2  (2)

#define NPXPCK_HIF_DPM_CHANNEL_0           0
#define NPXPCK_HIF_DPM_CHANNEL_1           1
#define NPXPCK_HIF_DPM_CHANNEL_2           2
#define NPXPCK_HIF_DPM_CHANNEL_3           3
#define NPXPCK_HIF_DPM_CHANNEL_DISABLED    0xFFFFFFFFUL

#define NPXPCK_HIF_THREAD_NAME             "NPXPKG_HIF"

/** Pool and queue configuration for  netPROXY HIF thread*/
#define NPXPCK_HIF_QUEUE_DEFAULT_ELEM       32
#define NPXPCK_HIF_POOL_DEFAULT_ELEM        16

/** Default number of instances of HIF input and output mapping objects */
#define NPX_PCK_MAX_INSTANCES_HIF_INPUT_MAPPING_CONFIGURATION_DEFAULT  64
#define NPX_PCK_MAX_INSTANCES_HIF_OUTPUT_MAPPING_CONFIGURATION_DEFAULT 64

/** Configuration of fragmentation buffer */
#define NPXPCK_HIF_FRAGMENTATION_BUFFER_SIZE_MIN     2048
#define NPXPCK_HIF_FRAGMENTATION_BUFFER_SIZE_DEFAULT 8192

/** Configuration of simultaneous possible fragmentation services*/
#define NPXPCK_HIF_FRAGMENTATION_SIMULTANEOUS_SERVICES_MIN      1
#define NPXPCK_HIF_FRAGMENTATION_SIMULTANEOUS_SERVICES_DEFAULT  4

/** Configuration of application timeout for fragmentation services*/
#define NPXPCK_HIF_FRAGMENTATION_TIMEOUT_MS_MIN        10
#define NPXPCK_HIF_FRAGMENTATION_TIMEOUT_MS_DEFAULT    1000

#define NPXPCK_HIF_BEHAVIOROBJECT_TIMEOUT_MS_MIN        10
#define NPXPCK_HIF_BEHAVIOROBJECT_TIMEOUT_MS_DEFAULT    1000

/******************************************************************************/
/*  Package configuration structure                                           */
/******************************************************************************/

typedef struct NPXPCK_HIF_THREAD_CONFIG_PARAM_Ttag
{
  OSAL_THREAD_PRIO bPriority;
  uint8_t          bInstance;

} NPXPCK_HIF_THREAD_CONFIG_PARAM_T;

typedef struct NPXPCK_HIF_FRAGMENTATION_CONFIG_PARAM_Ttag
{
  uint32_t ulFragmentationBufferSize;
  uint32_t ulSimultaneousServices;
  uint32_t ulTimeoutMs;

} NPXPCK_HIF_FRAGMENTATION_CONFIG_PARAM_T;

typedef struct NPXPCK_HIF_BEHAVIOROBJECT_CONFIG_PARAM_Ttag
{
  uint32_t ulResponseTimeoutMs;

} NPXPCK_HIF_BEHAVIOROBJECT_CONFIG_PARAM_T;

typedef struct NPXPCK_HIF_CONFIG_PARAM_Ttag
{
  uint32_t                                ulPackageConfigParamVersion;
  uint32_t                                ulDpmChannel;
  uint32_t                                ulQueueEntries;
  uint32_t                                ulPoolEntries;
  uint32_t                                ulMaxHifInputMappingConfiguration;
  uint32_t                                ulMaxHifOutputMappingConfiguration;
  const NETX_FW_IDENTIFICATION*           ptFirmwareIdentification;
  NPXPCK_HIF_THREAD_CONFIG_PARAM_T        tPackageThreadConfigParam;
  PS_WORKER_H                             hWorkerObjectList;
  PS_WORKER_H                             hWorkerIo;
  /* pointer to the function "NpxPackage_InOutTrigger_App_InitService" from the Common Communication package */
  void*                                   pfnInOutTriggerAppInitService;
  /* configuration of the packet-fragmentation service */
  NPXPCK_HIF_FRAGMENTATION_CONFIG_PARAM_T tFragmentationConfigParam;
  /* configuration of the Behavior Object service */
  NPXPCK_HIF_BEHAVIOROBJECT_CONFIG_PARAM_T tBehaviorObject;
} NPXPCK_HIF_CONFIG_PARAM_T;

/* Configuration structure for the Hif package*/
extern const NPX_PACKAGE_DESCRIPTION_T g_tNpxHif_PkgDesc;


#endif /* __NETPROXY_PACKAGE_HIF_PUBLIC_H */