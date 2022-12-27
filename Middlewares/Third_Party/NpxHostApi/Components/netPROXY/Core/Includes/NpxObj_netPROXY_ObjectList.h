/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id: NpxObj_netPROXY_ObjectList.h 3816 2018-02-28 16:09:11Z dirk $

  Description:
    netPROXY - Object List object (0x00001000)

  NOTE:
    Do not include this file separate. This file will included in the correct order
    by using netPROXY.h

**************************************************************************************/
#ifndef __NETPROXY_OBJECT_NETPROXY_OBJECT_LIST_H
#define __NETPROXY_OBJECT_NETPROXY_OBJECT_LIST_H

#include "OSAL.h"
#include "netPROXY.h"

#ifdef PRAGMA_PACK_ENABLE
#pragma PRAGMA_PACK_1(NETPROXY_OBJ_NETPROXY_OBJECT_LIST)
#endif


/* Define for the object Id */
#define NPX_OBJ_ID_NETPROXY_OBJECT_LIST  0x00001000


/* Object element numbers defines */
#define NPX_OBJ_NETPROXY_OBJECT_LIST_ELEMENT_OBJECT_ID                                   0
#define NPX_OBJ_NETPROXY_OBJECT_LIST_ELEMENT_GROUP                                       1

typedef __PACKED_PRE struct NPX_OBJ_NETPROXY_OBJECT_LIST_Ttag
{
  uint32_t   ulObjectID;                              /* Object Id                               */
  uint32_t   ulGroup;                                 /* Group ID where the object can be found  */
} __PACKED_POST NPX_OBJ_NETPROXY_OBJECT_LIST_T;


#ifndef __ALIGN_POST
#define __ALIGN_POST(align) __attribute__((aligned(align)))
#define __ALIGN_POST_NPX_OBJ_NETPROXY_OBJECT_LIST_T
#endif

/* It is the same structure but it is 4 bytes aligned (use it for optimized (aligned) accesses to the elements */
typedef NPX_OBJ_NETPROXY_OBJECT_LIST_T  ALIGN4_NPX_OBJ_NETPROXY_OBJECT_LIST_T __ALIGN_POST(4);

/* remove define if it was not defined previously */
#ifdef __ALIGN_POST_NPX_OBJ_NETPROXY_OBJECT_LIST_T
#undef __ALIGN_POST
#undef __ALIGN_POST_NPX_OBJ_NETPROXY_OBJECT_LIST_T
#endif



extern const NPX_OBJECT_DESCRIPTION_T g_tNetPROXY_ObjectList_ObjectDescription;


#ifdef PRAGMA_PACK_ENABLE
#pragma PRAGMA_UNPACK_1(NETPROXY_OBJ_NETPROXY_OBJECT_LIST)
#endif

#endif /* __NETPROXY_OBJECT_NETPROXY_OBJECT_LIST_H */
