/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id:: NpxObj_HifConfiguration.h 3816 2018-02-28 16:09:11Z dirk               $ *//**

  \note  This file is generated automatically, do not change it.

  \brief Hif Configuration object (0x30000000).

  The NetPROXY HIF Configuration Object

**************************************************************************************/
#ifndef __NETPROXY_OBJECT_HIF_CONFIGURATION_H
#define __NETPROXY_OBJECT_HIF_CONFIGURATION_H

#include "Hil_Compiler.h"
#include "netPROXY.h"

#ifdef __HIL_PRAGMA_PACK_ENABLE
#pragma __HIL_PRAGMA_PACK_1(NETPROXY_OBJ_HIF_CONFIGURATION)
#endif


/* Define for the object Id */
#define NPX_OBJ_ID_HIF_CONFIGURATION  0x30000000


/* Object element numbers defines */
#define NPX_OBJ_HIF_CONFIGURATION_ELEMENT_COMMAND                                     0
#define NPX_OBJ_HIF_CONFIGURATION_ELEMENT_STATUS                                      1

typedef __HIL_PACKED_PRE struct NPX_OBJ_HIF_CONFIGURATION_Ttag
{
  uint32_t   eCommand;                                /* Configuration Command                   */
  uint32_t   eStatus;                                 /* Configuration Status                    */
} __HIL_PACKED_POST NPX_OBJ_HIF_CONFIGURATION_T;


#ifdef __HIL_ALIGNED_DWORD__
/* It is the same structure but it is 4 bytes aligned (use it for optimized (aligned) accesses to the elements */
typedef NPX_OBJ_HIF_CONFIGURATION_T  ALIGN4_NPX_OBJ_HIF_CONFIGURATION_T __HIL_ALIGNED_DWORD__;
#endif



/* Command */
typedef enum NPX_OBJ_HIF_CONFIGURATION_COMMAND_Etag
{
  NPX_OBJ_HIF_CONFIGURATION_COMMAND_RELEASE                                          = 0,
  NPX_OBJ_HIF_CONFIGURATION_COMMAND_ACTIVATE                                         = 1,
}NPX_OBJ_HIF_CONFIGURATION_COMMAND_E;

/* Status */
typedef enum NPX_OBJ_HIF_CONFIGURATION_STATUS_Etag
{
  NPX_OBJ_HIF_CONFIGURATION_STATUS_NOT_CONFIGURED                                    = 0,
  NPX_OBJ_HIF_CONFIGURATION_STATUS_CONFIGURATION_OK                                  = 1,
  NPX_OBJ_HIF_CONFIGURATION_STATUS_CONFIGURATION_ERROR                               = 2,
}NPX_OBJ_HIF_CONFIGURATION_STATUS_E;


extern const NPX_OBJECT_DESCRIPTION_T g_tHifConfiguration_ObjectDescription;


#ifdef __HIL_PRAGMA_PACK_ENABLE
#pragma __HIL_PRAGMA_UNPACK_1(NETPROXY_OBJ_HIF_CONFIGURATION)
#endif

#endif /* __NETPROXY_OBJECT_HIF_CONFIGURATION_H */
