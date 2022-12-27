/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id:: NpxObj_HifOutputMappingConfiguration.h 3816 2018-02-28 16:09:11Z dirk  $ *//**

  \note  This file is generated automatically, do not change it.

  \brief Hif Output Mapping Configuration object (0x30000003).

  Mapping configuration object of output data, HIF to NET

**************************************************************************************/
#ifndef __NETPROXY_OBJECT_HIF_OUTPUT_MAPPING_CONFIGURATION_H
#define __NETPROXY_OBJECT_HIF_OUTPUT_MAPPING_CONFIGURATION_H

#include "Hil_Compiler.h"
#include "netPROXY.h"

#ifdef __HIL_PRAGMA_PACK_ENABLE
#pragma __HIL_PRAGMA_PACK_1(NETPROXY_OBJ_HIF_OUTPUT_MAPPING_CONFIGURATION)
#endif


/* Define for the object Id */
#define NPX_OBJ_ID_HIF_OUTPUT_MAPPING_CONFIGURATION  0x30000003


/* Object element numbers defines */
#define NPX_OBJ_HIF_OUTPUT_MAPPING_CONFIGURATION_ELEMENT_OBJECT_REFERENCE                            0

typedef __HIL_PACKED_PRE struct NPX_OBJ_HIF_OUTPUT_MAPPING_CONFIGURATION_Ttag
{
  NPX_OBJECT_REFERENCE_T tObjectReference;                        /* Reference to the object from where the data gets mapped to/from*/
} __HIL_PACKED_POST NPX_OBJ_HIF_OUTPUT_MAPPING_CONFIGURATION_T;


#ifdef __HIL_ALIGNED_DWORD__
/* It is the same structure but it is 4 bytes aligned (use it for optimized (aligned) accesses to the elements */
typedef NPX_OBJ_HIF_OUTPUT_MAPPING_CONFIGURATION_T  ALIGN4_NPX_OBJ_HIF_OUTPUT_MAPPING_CONFIGURATION_T __HIL_ALIGNED_DWORD__;
#endif




extern const NPX_OBJECT_DESCRIPTION_T g_tHifOutputMappingConfiguration_ObjectDescription;


#ifdef __HIL_PRAGMA_PACK_ENABLE
#pragma __HIL_PRAGMA_UNPACK_1(NETPROXY_OBJ_HIF_OUTPUT_MAPPING_CONFIGURATION)
#endif

#endif /* __NETPROXY_OBJECT_HIF_OUTPUT_MAPPING_CONFIGURATION_H */
