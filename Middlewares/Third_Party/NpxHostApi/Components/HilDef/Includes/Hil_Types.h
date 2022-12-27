/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: Hil_Types.h 3816 2018-02-28 16:09:11Z dirk $:

  Description:
    Hilscher Type Definition

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2016-11-30  File created.

**************************************************************************************/


#ifndef __HIL_TYPES_H
#define __HIL_TYPES_H


#include <stdint.h>
#include "Hil_Compiler.h"

#ifdef __HIL_PRAGMA_PACK_ENABLE
  #pragma __HIL_PRAGMA_PACK_1(HIL_TYPES)
#endif

/* UUID */
typedef __HIL_PACKED_PRE struct HIL_UUID_Ttag
{
  uint32_t  ulData1;
  uint16_t  usData2;
  uint16_t  usData3;
  uint8_t   abData4[8];
} __HIL_PACKED_POST HIL_UUID_T;


/* task UUID with special meaning of the elements */
typedef __HIL_PACKED_PRE struct HIL_TASK_UID_Ttag
{
  uint32_t        ulProtocolType;         /* see TLR_TASK_UID_STACK_xxx */
  uint16_t        usMajorVersion;         /* major number of the task (or stack) version */
  uint16_t        usTaskType;             /* see TLR_TASK_UID_TASK_TYPE_xxx */
  uint32_t        ulLayerLevel;           /* layer number (per the OSI model) */
  uint32_t        ulLayerSubTask;         /* subtask number, e.g. in case of multiple channels */
} __HIL_PACKED_POST HIL_TASK_UID_T;

#ifdef __HIL_PRAGMA_PACK_ENABLE
  #pragma __HIL_PRAGMA_UNPACK_1(HIL_TYPES)
#endif

#endif  /* __HIL_TYPES_H */
