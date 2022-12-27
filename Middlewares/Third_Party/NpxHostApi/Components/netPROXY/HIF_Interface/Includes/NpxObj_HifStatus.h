/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id:: NpxObj_HifStatus.h 3816 2018-02-28 16:09:11Z dirk                      $ *//**

  \note  This file is generated automatically, do not change it.

  \brief Hif Status object (0x30000001).

  The NetPROXY HIF Status Object

**************************************************************************************/
#ifndef __NETPROXY_OBJECT_HIF_STATUS_H
#define __NETPROXY_OBJECT_HIF_STATUS_H

#include "Hil_Compiler.h"
#include "netPROXY.h"

#ifdef __HIL_PRAGMA_PACK_ENABLE
#pragma __HIL_PRAGMA_PACK_1(NETPROXY_OBJ_HIF_STATUS)
#endif


/* Define for the object Id */
#define NPX_OBJ_ID_HIF_STATUS  0x30000001


/* Object element numbers defines */
#define NPX_OBJ_HIF_STATUS_ELEMENT_DPM_CHANNEL                                 0
#define NPX_OBJ_HIF_STATUS_ELEMENT_REQUEST_COUNT                               1
#define NPX_OBJ_HIF_STATUS_ELEMENT_CONFIRMATION_COUNT                          2
#define NPX_OBJ_HIF_STATUS_ELEMENT_INVALID_REQUEST_COUNT                       3
#define NPX_OBJ_HIF_STATUS_ELEMENT_CONFIRMATION_FAILURE_COUNT                  4
#define NPX_OBJ_HIF_STATUS_ELEMENT_INDICATION_SENT_COUNT                       5
#define NPX_OBJ_HIF_STATUS_ELEMENT_INDICATION_ERROR_COUNT                      6
#define NPX_OBJ_HIF_STATUS_ELEMENT_SHORT_RESPONSE_RECEIVE_COUNT                7
#define NPX_OBJ_HIF_STATUS_ELEMENT_RESPONSE_RECEIVE_COUNT                      8
#define NPX_OBJ_HIF_STATUS_ELEMENT_HOST_UPDATE_NET_TO_HIF_COUNT                9
#define NPX_OBJ_HIF_STATUS_ELEMENT_HOST_UPDATE_HIF_TO_NET_COUNT               10
#define NPX_OBJ_HIF_STATUS_ELEMENT_NETWORK_UPDATE_NET_TO_HIF_COUNT            11
#define NPX_OBJ_HIF_STATUS_ELEMENT_NETWORK_UPDATE_HIF_TO_NET_COUNT            12

typedef __HIL_PACKED_PRE struct NPX_OBJ_HIF_STATUS_Ttag
{
  uint32_t   ulDpmChannel;                            /* ID of the DPM channel on which the interface is started*/
  uint32_t   ulRequestCount;                          /* Counter for requests received           */
  uint32_t   ulConfirmationCount;                     /* Counter for confirmations sent          */
  uint32_t   ulInvalidRequestCount;                   /* Counter for invalid request.            */
  uint32_t   ulConfirmationFailureCount;              /* Counter for confirmation sent failures  */
  uint32_t   ulIndicationSentCount;                   /* Counter for indication sent             */
  uint32_t   ulIndicationErrorCount;                  /* Counter for indication errors           */
  uint32_t   ulShortResponseReceiveCount;             /* Counter for short response received     */
  uint32_t   ulResponseReceiveCount;                  /* Counter for response received           */
  uint32_t   ulHostUpdateNetToHifCount;               /* Counter Host data updated from network to HIF*/
  uint32_t   ulHostUpdateHifToNetCount;               /* Counter Host data updated from HIF to network*/
  uint32_t   ulNetworkUpdateNetToHifCount;            /* Counter Network data updated from network to HIF*/
  uint32_t   ulNetworkUpdateHifToNetCount;            /* Counter Network data updated from HIF to network*/
} __HIL_PACKED_POST NPX_OBJ_HIF_STATUS_T;


#ifdef __HIL_ALIGNED_DWORD__
/* It is the same structure but it is 4 bytes aligned (use it for optimized (aligned) accesses to the elements */
typedef NPX_OBJ_HIF_STATUS_T  ALIGN4_NPX_OBJ_HIF_STATUS_T __HIL_ALIGNED_DWORD__;
#endif




extern const NPX_OBJECT_DESCRIPTION_T g_tHifStatus_ObjectDescription;


#ifdef __HIL_PRAGMA_PACK_ENABLE
#pragma __HIL_PRAGMA_UNPACK_1(NETPROXY_OBJ_HIF_STATUS)
#endif

#endif /* __NETPROXY_OBJECT_HIF_STATUS_H */
