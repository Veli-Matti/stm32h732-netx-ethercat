/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id:: NpxObj_HifTriggerConfiguration.h 3816 2018-02-28 16:09:11Z dirk        $ *//**

  \note  This file is generated automatically, do not change it.

  \brief Hif Trigger Configuration object (0x30000004).

  Trigger Configuration for Input and Output Process Data

**************************************************************************************/
#ifndef __NETPROXY_OBJECT_HIF_TRIGGER_CONFIGURATION_H
#define __NETPROXY_OBJECT_HIF_TRIGGER_CONFIGURATION_H

#include "Hil_Compiler.h"
#include "netPROXY.h"

#ifdef __HIL_PRAGMA_PACK_ENABLE
#pragma __HIL_PRAGMA_PACK_1(NETPROXY_OBJ_HIF_TRIGGER_CONFIGURATION)
#endif


/* Define for the object Id */
#define NPX_OBJ_ID_HIF_TRIGGER_CONFIGURATION  0x30000004


/* Object element numbers defines */
#define NPX_OBJ_HIF_TRIGGER_CONFIGURATION_ELEMENT_INPUT_TRIGGER                               0
#define NPX_OBJ_HIF_TRIGGER_CONFIGURATION_ELEMENT_OUTPUT_TRIGGER                              1

typedef __HIL_PACKED_PRE struct NPX_OBJ_HIF_TRIGGER_CONFIGURATION_Ttag
{
  uint32_t   eInputTrigger;                           /* Input Trigger Configuration             */
  uint32_t   eOutputTrigger;                          /* Output Trigger Configuration            */
} __HIL_PACKED_POST NPX_OBJ_HIF_TRIGGER_CONFIGURATION_T;


#ifdef __HIL_ALIGNED_DWORD__
/* It is the same structure but it is 4 bytes aligned (use it for optimized (aligned) accesses to the elements */
typedef NPX_OBJ_HIF_TRIGGER_CONFIGURATION_T  ALIGN4_NPX_OBJ_HIF_TRIGGER_CONFIGURATION_T __HIL_ALIGNED_DWORD__;
#endif



/* Input Trigger */
typedef enum NPX_OBJ_HIF_TRIGGER_CONFIGURATION_INPUT_TRIGGER_Etag
{
  NPX_OBJ_HIF_TRIGGER_CONFIGURATION_INPUT_TRIGGER_INACTIVE                           = 0,
  NPX_OBJ_HIF_TRIGGER_CONFIGURATION_INPUT_TRIGGER_TRIGGER_ON_HANDSHAKE               = 1,
}NPX_OBJ_HIF_TRIGGER_CONFIGURATION_INPUT_TRIGGER_E;

/* Output Trigger */
typedef enum NPX_OBJ_HIF_TRIGGER_CONFIGURATION_OUTPUT_TRIGGER_Etag
{
  NPX_OBJ_HIF_TRIGGER_CONFIGURATION_OUTPUT_TRIGGER_INACTIVE                          = 0,
  NPX_OBJ_HIF_TRIGGER_CONFIGURATION_OUTPUT_TRIGGER_TRIGGER_ON_HANDSHAKE              = 1,
}NPX_OBJ_HIF_TRIGGER_CONFIGURATION_OUTPUT_TRIGGER_E;


extern const NPX_OBJECT_DESCRIPTION_T g_tHifTriggerConfiguration_ObjectDescription;


#ifdef __HIL_PRAGMA_PACK_ENABLE
#pragma __HIL_PRAGMA_UNPACK_1(NETPROXY_OBJ_HIF_TRIGGER_CONFIGURATION)
#endif

#endif /* __NETPROXY_OBJECT_HIF_TRIGGER_CONFIGURATION_H */
