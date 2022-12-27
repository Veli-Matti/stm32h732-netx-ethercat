/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id: NpxObj_netPROXY_EventLog.h 3816 2018-02-28 16:09:11Z dirk $

  Description:
    netPROXY - Event Log object (0x00002000)

  NOTE:
    Do not include this file separate. This file will included in the correct order
    by using netPROXY.h

**************************************************************************************/
#ifndef __NETPROXY_OBJECT_NETPROXY_EVENT_LOG_H
#define __NETPROXY_OBJECT_NETPROXY_EVENT_LOG_H

#include "OSAL.h"
#include "netPROXY.h"

#ifdef PRAGMA_PACK_ENABLE
#pragma PRAGMA_PACK_1(NETPROXY_OBJ_NETPROXY_EVENT_LOG)
#endif


/* Define for the object Id */
#define NPX_OBJ_ID_NETPROXY_EVENT_LOG  0x00002000


/* Object element numbers defines */
#define NPX_OBJ_NETPROXY_EVENT_LOG_ELEMENT_ENTRY_ID                                    0
#define NPX_OBJ_NETPROXY_EVENT_LOG_ELEMENT_TIME_STAMP                                  1
#define NPX_OBJ_NETPROXY_EVENT_LOG_ELEMENT_SEVERITY                                    2
#define NPX_OBJ_NETPROXY_EVENT_LOG_ELEMENT_MARKER                                      3
#define NPX_OBJ_NETPROXY_EVENT_LOG_ELEMENT_FACILITY                                    4
#define NPX_OBJ_NETPROXY_EVENT_LOG_ELEMENT_ERROR_CODE                                  5
#define NPX_OBJ_NETPROXY_EVENT_LOG_ELEMENT_ADDITIONAL_CODE                             6

typedef __PACKED_PRE struct NPX_OBJ_NETPROXY_EVENT_LOG_Ttag
{
  uint32_t   ulEntryID;                               /* Unique entry ID                         */
  uint32_t   ulTimeStamp;                             /* Time stamp in ms since system start     */
  uint8_t    eSeverity;                               /* Severity level of the entry             */
  uint8_t    bMarker;                                 /* Marker                                  */
  uint16_t   usFacility;                              /* Facility identification number          */
  uint32_t   ulErrorCode;                             /* Generic Error code, this code should be unique (e.g. TLR, OSAL, or Protocol specific) if no facility is defined*/
  uint32_t   ulAdditionalCode;                        /* The meaning of the additional code depend on the Facility and Marker value*/
} __PACKED_POST NPX_OBJ_NETPROXY_EVENT_LOG_T;


#ifndef __ALIGN_POST
#define __ALIGN_POST(align) __attribute__((aligned(align)))
#define __ALIGN_POST_NPX_OBJ_NETPROXY_EVENT_LOG_T
#endif

/* It is the same structure but it is 4 bytes aligned (use it for optimized (aligned) accesses to the elements */
typedef NPX_OBJ_NETPROXY_EVENT_LOG_T  ALIGN4_NPX_OBJ_NETPROXY_EVENT_LOG_T __ALIGN_POST(4);

/* remove define if it was not defined previously */
#ifdef __ALIGN_POST_NPX_OBJ_NETPROXY_EVENT_LOG_T
#undef __ALIGN_POST
#undef __ALIGN_POST_NPX_OBJ_NETPROXY_EVENT_LOG_T
#endif


/* Severity */
typedef enum NPX_OBJ_NETPROXY_EVENT_LOG_SEVERITY_Etag
{
  NPX_OBJ_NETPROXY_EVENT_LOG_SEVERITY_EMERGENCY                                      = 0,
  NPX_OBJ_NETPROXY_EVENT_LOG_SEVERITY_ALERT                                          = 1,
  NPX_OBJ_NETPROXY_EVENT_LOG_SEVERITY_CRITICAL                                       = 2,
  NPX_OBJ_NETPROXY_EVENT_LOG_SEVERITY_ERROR                                          = 3,
  NPX_OBJ_NETPROXY_EVENT_LOG_SEVERITY_WARNING                                        = 4,
  NPX_OBJ_NETPROXY_EVENT_LOG_SEVERITY_NOTIFICATION                                   = 5,
  NPX_OBJ_NETPROXY_EVENT_LOG_SEVERITY_INFORMATION                                    = 6,
  NPX_OBJ_NETPROXY_EVENT_LOG_SEVERITY_DEBUG                                          = 7,
}NPX_OBJ_NETPROXY_EVENT_LOG_SEVERITY_E;

/* Facility */
typedef enum NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_Etag
{
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_UNDEFINED                                      = 0,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_SYSTEM                                         = 1,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_TARGET                                         = 2,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_NETPROXY                                       = 3,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_RESERVED_FIRST                                 = 4,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_RESERVED_LAST                                  = 15,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_USER_FIRST                                     = 16,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_USER_LAST                                      = 32,

  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_PROFINET                                       = 256,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_ETHERNET_IP                                    = 257,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_ETHERCAT                                       = 258,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_SERCOS                                         = 259,

  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_GENERIC_DEVICE                                 = 512,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_REMANENT_MODULE                                = 513,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_COMMON_COMMUNICATION                           = 514,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_INTERNET_PROTOCOL_V4                           = 515,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_HOST_INTERFACE_ADAPTER                         = 516,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_PDO_MAPPER                                     = 517,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_DIAGNOSIS                                      = 518,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_IO_LINK_MASTER                                 = 519,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_SAFETY_INTERFACE                               = 520,
  NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_SSIO_HANDLER                                   = 521,
}NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_E;


extern const NPX_OBJECT_DESCRIPTION_T g_tNetPROXY_EventLog_ObjectDescription;


#ifdef PRAGMA_PACK_ENABLE
#pragma PRAGMA_UNPACK_1(NETPROXY_OBJ_NETPROXY_EVENT_LOG)
#endif

#endif /* __NETPROXY_OBJECT_NETPROXY_EVENT_LOG_H */
