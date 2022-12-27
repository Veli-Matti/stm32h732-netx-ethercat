/**************************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************************
  $Id: NpxPck_Hif_Packet.h 3816 2018-02-28 16:09:11Z dirk $

  Description:
    Version header

**************************************************************************************************/
#ifndef __NPXPCK_HIF_PACKET_H
#define __NPXPCK_HIF_PACKET_H

#include "Hil_Packet.h"

/* pragma pack */
#ifdef __HIL_PRAGMA_PACK_ENABLE
#pragma __HIL_PRAGMA_PACK_1(__NPXPCK_HIF_PACKET)
#endif

/** name of queue */
#define NPXPCK_HIF_QUEUE_NAME             "QUE_NPCK_NHIF"

/* due API-Changes all Commands will start with 0x00008840 */
#define NPXPCK_HIF_READ_OBJECT_ELEMENT_REQ            0x00008840
#define NPXPCK_HIF_READ_OBJECT_ELEMENT_CNF            0x00008841

#define NPXPCK_HIF_WRITE_OBJECT_ELEMENT_REQ           0x00008842
#define NPXPCK_HIF_WRITE_OBJECT_ELEMENT_CNF           0x00008843

#define NPXPCK_HIF_GET_ELEMENT_BYTESIZE_REQ           0x00008844
#define NPXPCK_HIF_GET_ELEMENT_BYTESIZE_CNF           0x00008845

#define NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_REQ         0x00008846
#define NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_CNF         0x00008847

#define NPXPCK_HIF_GET_OBJECT_DESCRIPTION_REQ         0x00008848
#define NPXPCK_HIF_GET_OBJECT_DESCRIPTION_CNF         0x00008849

#define NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_REQ      0x0000884A
#define NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_CNF      0x0000884B

#define NPXPCK_HIF_ADD_VOLATILE_OBJECT_REQ            0x0000884C
#define NPXPCK_HIF_ADD_VOLATILE_OBJECT_CNF            0x0000884D

#define NPXPCK_HIF_DELETE_OBJECT_REQ                  0x0000884E
#define NPXPCK_HIF_DELETE_OBJECT_CNF                  0x0000884F

#define NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_REQ        0x00008850
#define NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_CNF        0x00008851

#define NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_REQ   0x00008852
#define NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_CNF   0x00008853

#define NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_REQ 0x00008854
#define NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_CNF 0x00008855

#define NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND     0x00008856
#define NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_RES     0x00008857

#define NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_REQ            0x00008858
#define NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_CNF            0x00008859

#define NPXPCK_HIF_SET_BEHAVIOR_OBJECT_NUM_INST_REQ   0x0000885A
#define NPXPCK_HIF_SET_BEHAVIOR_OBJECT_NUM_INST_CNF   0x0000885B

#define NPXPCK_HIF_READ_BEHAVIOR_OBJECT_IND           0x0000885C
#define NPXPCK_HIF_READ_BEHAVIOR_OBJECT_RES           0x0000885D

#define NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_IND          0x0000885E
#define NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_RES          0x0000885F

/*Access to object entity (parameter 'ulElementNo')*/
#define NPXPCK_HIF_ELEMENT_NO_OBJECT_INSTANCE            0xffffffff

/*************************************************************************************/
/* Read object element packets - Npx_AsyncReadObjectElement() */

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_READ_OBJECT_ELEMENT_REQ_DATA_Ttag
{
  uint32_t ulGroupId;
  uint32_t ulObjectId;
  uint32_t ulObjectInstance;
  uint32_t ulElementNo;

} __HIL_PACKED_POST NPXPCK_HIF_READ_OBJECT_ELEMENT_REQ_DATA_T;

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_READ_OBJECT_ELEMENT_CNF_DATA_Ttag
{
  uint32_t ulGroupId;
  uint32_t ulObjectId;
  uint32_t ulObjectInstance;
  uint32_t ulElementNo;
  uint8_t  abData[(HIL_MAX_DATA_SIZE - (4 * sizeof(uint32_t)))];

} __HIL_PACKED_POST NPXPCK_HIF_READ_OBJECT_ELEMENT_CNF_DATA_T;

#define NPXPCK_HIF_READ_OBJECT_ELEMENT_REQ_DATA_SIZE \
  (sizeof(NPXPCK_HIF_READ_OBJECT_ELEMENT_REQ_DATA_T))

#define NPXPCK_HIF_READ_OBJECT_ELEMENT_CNF_DATA_MIN_SIZE \
  (4 * sizeof(uint32_t))

#define NPXPCK_HIF_READ_OBJECT_ELEMENT_CNF_DATA_MAX_SIZE \
  (HIL_MAX_DATA_SIZE)

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_READ_OBJECT_ELEMENT_REQ_Ttag
{
  HIL_PACKET_HEADER_T                       tHead;
  NPXPCK_HIF_READ_OBJECT_ELEMENT_REQ_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_READ_OBJECT_ELEMENT_REQ_T;

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_READ_OBJECT_ELEMENT_CNF_Ttag
{
  HIL_PACKET_HEADER_T                       tHead;
  NPXPCK_HIF_READ_OBJECT_ELEMENT_CNF_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_READ_OBJECT_ELEMENT_CNF_T;


/*************************************************************************************/
/* Write object element packets - Npx_AsyncWriteObjectElement() */

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_WRITE_OBJECT_ELEMENT_REQ_DATA_Ttag
{
  uint32_t ulGroupId;
  uint32_t ulObjectId;
  uint32_t ulObjectInstance;
  uint32_t ulElementNo;
  uint8_t  abData[(HIL_MAX_DATA_SIZE - (4 * sizeof(uint32_t)))];

} __HIL_PACKED_POST NPXPCK_HIF_WRITE_OBJECT_ELEMENT_REQ_DATA_T;

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_WRITE_OBJECT_ELEMENT_CNF_DATA_Ttag
{
  uint32_t ulGroupId;
  uint32_t ulObjectId;
  uint32_t ulObjectInstance;
  uint32_t ulElementNo;

} __HIL_PACKED_POST NPXPCK_HIF_WRITE_OBJECT_ELEMENT_CNF_DATA_T;


#define NPXPCK_HIF_WRITE_OBJECT_ELEMENT_REQ_DATA_MIN_SIZE\
  (4 * sizeof(uint32_t))

#define NPXPCK_HIF_WRITE_OBJECT_ELEMENT_REQ_DATA_MAX_SIZE \
  (HIL_MAX_DATA_SIZE)

#define NPXPCK_HIF_WRITE_OBJECT_ELEMENT_CNF_DATA_SIZE \
   (sizeof(NPXPCK_HIF_WRITE_OBJECT_ELEMENT_CNF_DATA_T))


typedef __HIL_PACKED_PRE struct NPXPCK_HIF_WRITE_OBJECT_ELEMENT_REQ_Ttag
{
  HIL_PACKET_HEADER_T                        tHead;
  NPXPCK_HIF_WRITE_OBJECT_ELEMENT_REQ_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_WRITE_OBJECT_ELEMENT_REQ_T;


typedef __HIL_PACKED_PRE struct NPXPCK_HIF_WRITE_OBJECT_ELEMENT_CNF_Ttag
{
  HIL_PACKET_HEADER_T                        tHead;
  NPXPCK_HIF_WRITE_OBJECT_ELEMENT_CNF_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_WRITE_OBJECT_ELEMENT_CNF_T;


/*************************************************************************************/
/* Get object element size packets - Npx_GetElementByteSize() */

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_GET_ELEMENT_BYTESIZE_REQ_DATA_Ttag
{
  uint32_t ulObjectId;
  uint32_t ulElementNo;

} __HIL_PACKED_POST NPXPCK_HIF_GET_ELEMENT_BYTESIZE_REQ_DATA_T;

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_GET_ELEMENT_BYTESIZE_CNF_DATA_Tag
{
  uint32_t ulObjectId;
  uint32_t ulElementNo;
  uint32_t ulByteSize;

} __HIL_PACKED_POST NPXPCK_HIF_GET_ELEMENT_BYTESIZE_CNF_DATA_T;


#define NPXPCK_HIF_GET_ELEMENT_BYTESIZE_REQ_DATA_SIZE \
  (sizeof(NPXPCK_HIF_GET_ELEMENT_BYTESIZE_REQ_DATA_T))

#define NPXPCK_HIF_GET_ELEMENT_BYTESIZE_CNF_DATA_SIZE \
  (sizeof(NPXPCK_HIF_GET_ELEMENT_BYTESIZE_CNF_DATA_T))


typedef __HIL_PACKED_PRE struct NPXPCK_HIF_GET_ELEMENT_BYTESIZE_REQ_Ttag
{
  HIL_PACKET_HEADER_T                        tHead;
  NPXPCK_HIF_GET_ELEMENT_BYTESIZE_REQ_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_GET_ELEMENT_BYTESIZE_REQ_T;


typedef __HIL_PACKED_PRE struct NPXPCK_HIF_GET_ELEMENT_BYTESIZE_CNF_Ttag
{
  HIL_PACKET_HEADER_T                        tHead;
  NPXPCK_HIF_GET_ELEMENT_BYTESIZE_CNF_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_GET_ELEMENT_BYTESIZE_CNF_T;


/*************************************************************************************/
/* Add Object Description - Npx_AddObjectDescription()
 *
 * In order to minimize data copying the structures for object description manipulation
 * are binary compatible with the netPROXY API structures.
 * Once received the packet data is modified to match the NPX_OBJECT_DESCRIPTION_T and
 * NPX_ELEMENT_DESCRIPTION_T structures:
 * - name offsets are converted to actual addresses (void*)
 * - the ulReserved field in NPXPCK_HIF_OBJECT_DESCRIPTION_T is converted to a (void*) to point
 *   to the first element description - abData[0]. */

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_ELEMENT_DESCRIPTION_Ttag
{
  uint32_t ulElementNameOffset;  /* Offset of string within text block, see below */
  uint32_t ulReserved;           /* Currently unused, set to zero. */
  uint16_t usElementType;        /* netPROXY element type. */
  uint16_t usElementByteSize;    /* size of the element in bytes. */

} __HIL_PACKED_POST NPXPCK_HIF_ELEMENT_DESCRIPTION_T;

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_OBJECT_DESCRIPTION_Ttag
{
  uint32_t ulObjectId;               /* ID of the object. */
  uint32_t ulObjectNameOffset;       /* Offset of string within text block. */
  uint32_t ulNumberOfElements;       /* Number of elements in the array. */
  uint32_t ulReserved;               /* Reserved, set to zero. */
  uint8_t  abData[(HIL_MAX_DATA_SIZE - (4 * sizeof(uint32_t)))];

  /* TEXT BLOCK */
  /* Zero-terminated strings used in the packet must be appended here one after another,
   * right after the last element. If no elements are provided,
   * strings area starts right after the ulReserved field.
   * Set the first byte of the block to 0, so that
   * if an empty string is required the corresponding name offset field
   * can be set to block offset 0. */

} __HIL_PACKED_POST NPXPCK_HIF_OBJECT_DESCRIPTION_T;

typedef NPXPCK_HIF_OBJECT_DESCRIPTION_T \
  NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_REQ_DATA_T;

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_CNF_DATA_Ttag
{
  uint32_t ulObjectId;

} __HIL_PACKED_POST NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_CNF_DATA_T;

/* An object description with no elements and just the empty string */
#define NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_REQ_MIN_DATA_SIZE \
  (offsetof(NPXPCK_HIF_OBJECT_DESCRIPTION_T, abData) + 1)

#define NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_REQ_MAX_DATA_SIZE \
  (HIL_MAX_DATA_SIZE)

#define NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_CNF_DATA_SIZE \
  (sizeof(NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_CNF_DATA_T))


typedef __HIL_PACKED_PRE struct NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_REQ_Ttag
{
  HIL_PACKET_HEADER_T                          tHead;
  NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_REQ_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_REQ_T;

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_CNF_Ttag
{
  HIL_PACKET_HEADER_T                          tHead;
  NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_CNF_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_CNF_T;


/*************************************************************************************/
/* Get Object Description - Npx_GetObjectDescription() */

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_GET_OBJECT_DESCRIPTION_REQ_DATA_Ttag
{
  uint32_t ulObjectId; /* ID of the object. */

} __HIL_PACKED_POST NPXPCK_HIF_GET_OBJECT_DESCRIPTION_REQ_DATA_T;

typedef NPXPCK_HIF_OBJECT_DESCRIPTION_T \
  NPXPCK_HIF_GET_OBJECT_DESCRIPTION_CNF_DATA_T;


#define NPXPCK_HIF_GET_OBJECT_DESCRIPTION_REQ_DATA_SIZE \
  (sizeof(NPXPCK_HIF_GET_OBJECT_DESCRIPTION_REQ_DATA_T))

/* An object description with no elements and just the empty string */
#define NPXPCK_HIF_GET_OBJECT_DESCRIPTION_CNF_MIN_DATA_SIZE \
  (offsetof(NPXPCK_HIF_OBJECT_DESCRIPTION_T, abData) + 1)

#define NPXPCK_HIF_GET_OBJECT_DESCRIPTION_CNF_MAX_DATA_SIZE \
  (HIL_MAX_DATA_SIZE)


typedef __HIL_PACKED_PRE struct NPXPCK_HIF_GET_OBJECT_DESCRIPTION_REQ_Ttag
{
  HIL_PACKET_HEADER_T                          tHead;
  NPXPCK_HIF_GET_OBJECT_DESCRIPTION_REQ_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_GET_OBJECT_DESCRIPTION_REQ_T;

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_GET_OBJECT_DESCRIPTION_CNF_Ttag
{
  HIL_PACKET_HEADER_T                          tHead;
  NPXPCK_HIF_GET_OBJECT_DESCRIPTION_CNF_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_GET_OBJECT_DESCRIPTION_CNF_T;


/*************************************************************************************/
/* Delete Object Description - Npx_DeleteObjectDescription() */

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_REQ_DATA_Ttag
{
  uint32_t ulObjectId; /* ID of the object. */

} __HIL_PACKED_POST NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_REQ_DATA_T;

/* The format of the confirmation message is the same as the request. */
typedef NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_REQ_DATA_T \
  NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_CNF_DATA_T;


#define NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_REQ_DATA_SIZE \
  (sizeof(NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_REQ_DATA_T))

#define NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_CNF_DATA_SIZE \
  (sizeof(NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_CNF_DATA_T))


typedef __HIL_PACKED_PRE struct NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_REQ_Ttag
{
  HIL_PACKET_HEADER_T                             tHead;
  NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_REQ_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_REQ_T;

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_CNF_Ttag
{
  HIL_PACKET_HEADER_T                             tHead;
  NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_CNF_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_CNF_T;


/*************************************************************************************/
/* Add Volatile Storage Object - Npx_AddVolatileStorageObjectEntity() */

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_ADD_VOLATILE_OBJECT_REQ_DATA_Ttag
{
  uint32_t ulGroupId;
  uint32_t ulObjectId;
  uint32_t ulNumberOfInstances;

}__HIL_PACKED_POST NPXPCK_HIF_ADD_VOLATILE_OBJECT_REQ_DATA_T;

/* The format of the confirmation message is the same as the request. */
typedef NPXPCK_HIF_ADD_VOLATILE_OBJECT_REQ_DATA_T \
  NPXPCK_HIF_ADD_VOLATILE_OBJECT_CNF_DATA_T;


#define NPXPCK_HIF_ADD_VOLATILE_OBJECT_REQ_DATA_SIZE \
  (sizeof(NPXPCK_HIF_ADD_VOLATILE_OBJECT_REQ_DATA_T))

#define NPXPCK_HIF_ADD_VOLATILE_OBJECT_CNF_DATA_SIZE \
  (sizeof(NPXPCK_HIF_ADD_VOLATILE_OBJECT_CNF_DATA_T))


typedef __HIL_PACKED_PRE struct NPXPCK_HIF_ADD_VOLATILE_OBJECT_REQ_Ttag
{
  HIL_PACKET_HEADER_T                       tHead;
  NPXPCK_HIF_ADD_VOLATILE_OBJECT_REQ_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_ADD_VOLATILE_OBJECT_REQ_T;

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_ADD_VOLATILE_OBJECT_CNF_Ttag
{
  HIL_PACKET_HEADER_T                       tHead;
  NPXPCK_HIF_ADD_VOLATILE_OBJECT_CNF_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_ADD_VOLATILE_OBJECT_CNF_T;


/*************************************************************************************/
/* Delete Object - Npx_DeleteObjectEntity() */

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_DELETE_OBJECT_REQ_DATA_Ttag
{
  uint32_t ulGroupId;
  uint32_t ulObjectId;

} __HIL_PACKED_POST NPXPCK_HIF_DELETE_OBJECT_REQ_DATA_T;

/* The format of the confirmation message is the same as the request. */
typedef NPXPCK_HIF_DELETE_OBJECT_REQ_DATA_T \
  NPXPCK_HIF_DELETE_OBJECT_CNF_DATA_T;


#define NPXPCK_HIF_DELETE_OBJECT_REQ_DATA_SIZE \
  (sizeof(NPXPCK_HIF_DELETE_OBJECT_REQ_DATA_T))

#define NPXPCK_HIF_DELETE_OBJECT_CNF_DATA_SIZE \
  (sizeof(NPXPCK_HIF_DELETE_OBJECT_CNF_DATA_T))


typedef __HIL_PACKED_PRE struct NPXPCK_HIF_DELETE_OBJECT_REQ_Ttag
{
  HIL_PACKET_HEADER_T                 tHead;
  NPXPCK_HIF_DELETE_OBJECT_REQ_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_DELETE_OBJECT_REQ_T;

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_DELETE_OBJECT_CNF_Ttag
{
  HIL_PACKET_HEADER_T                 tHead;
  NPXPCK_HIF_DELETE_OBJECT_CNF_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_DELETE_OBJECT_CNF_T;

/*************************************************************************************/
/* Get number of instances - Npx_GetNumberOfObjectInstances() */

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_REQ_DATA_Ttag
{
  uint32_t ulGroupId;
  uint32_t ulObjectId;

} __HIL_PACKED_POST NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_REQ_DATA_T;

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_CNF_DATA_Tag
{
  uint32_t ulGroupId;
  uint32_t ulObjectId;
  uint32_t ulNumberOfInstances;

} __HIL_PACKED_POST NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_CNF_DATA_T;


#define NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_REQ_DATA_SIZE \
  (sizeof(NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_REQ_DATA_T))

#define NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_CNF_DATA_SIZE \
  (sizeof(NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_CNF_DATA_T))


typedef __HIL_PACKED_PRE struct NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_REQ_Ttag
{
  HIL_PACKET_HEADER_T                           tHead;
  NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_REQ_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_REQ_T;


typedef __HIL_PACKED_PRE struct NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_CNF_Ttag
{
  HIL_PACKET_HEADER_T                           tHead;
  NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_CNF_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_CNF_T;

/*************************************************************************************/
/* Register update notification - Npx_RegisterUpdateNotifyCallback() */

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_REQ_DATA_Ttag
{
  uint32_t ulGroupId;
  uint32_t ulObjectId;
  uint32_t ulObjectInstance;
  uint32_t ulElementNo;

}__HIL_PACKED_POST NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_REQ_DATA_T;

/* The format of the confirmation message is the same as the request. */
typedef NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_REQ_DATA_T \
  NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_CNF_DATA_T;


#define NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_REQ_DATA_SIZE \
  (sizeof(NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_REQ_DATA_T))

#define NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_CNF_DATA_SIZE \
  (sizeof(NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_CNF_DATA_T))


typedef __HIL_PACKED_PRE struct NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_REQ_Ttag
{
  HIL_PACKET_HEADER_T                                tHead;
  NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_REQ_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_REQ_T;

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_CNF_Ttag
{
  HIL_PACKET_HEADER_T                                tHead;
  NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_CNF_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_CNF_T;

/*************************************************************************************/
/* Register update notification - Npx_UnregisterUpdateNotifyCallback() */

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_REQ_DATA_Ttag
{
  uint32_t ulGroupId;
  uint32_t ulObjectId;
  uint32_t ulObjectInstance;
  uint32_t ulElementNo;

}__HIL_PACKED_POST NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_REQ_DATA_T;

/* The format of the confirmation message is the same as the request. */
typedef NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_REQ_DATA_T \
  NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_CNF_DATA_T;


#define NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_REQ_DATA_SIZE \
  (sizeof(NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_REQ_DATA_T))

#define NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_CNF_DATA_SIZE \
  (sizeof(NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_CNF_DATA_T))


typedef __HIL_PACKED_PRE struct NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_REQ_Ttag
{
  HIL_PACKET_HEADER_T                                  tHead;
  NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_REQ_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_REQ_T;

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_CNF_Ttag
{
  HIL_PACKET_HEADER_T                                  tHead;
  NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_CNF_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_CNF_T;

/*************************************************************************************/
/* object update notification - Npx_WriteNotifyCallback */

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND_DATA_Ttag
{
  uint32_t ulGroupId;
  uint32_t ulObjectId;
  uint32_t ulObjectInstance;
  uint32_t ulElementNo;
  uint8_t  abData[(HIL_MAX_DATA_SIZE - (4 * sizeof(uint32_t)))];

}__HIL_PACKED_POST NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND_DATA_T;

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_RES_DATA_Ttag
{
  uint32_t ulGroupId;
  uint32_t ulObjectId;
  uint32_t ulObjectInstance;
  uint32_t ulElementNo;

}__HIL_PACKED_POST NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_RES_DATA_T;


#define NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND_DATA_MIN_SIZE \
  (4 * sizeof(uint32_t))

#define NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND_DATA_MAX_SIZE \
  (HIL_MAX_DATA_SIZE)

#define NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_RES_DATA_SIZE \
  (sizeof(NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_RES_DATA_T))


typedef __HIL_PACKED_PRE struct NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND_Ttag
{
  HIL_PACKET_HEADER_T                              tHead;
  NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND_T;

typedef __HIL_PACKED_PRE struct NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_RES_Ttag
{
  HIL_PACKET_HEADER_T                              tHead;
  NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_RES_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_RES_T;


/*************************************************************************************/
/* Add Behavior Object - structure is the same as in "Add Volatile Storage Object" */

typedef NPXPCK_HIF_ADD_VOLATILE_OBJECT_REQ_DATA_T  NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_REQ_DATA_T;
/* The format of the confirmation message is the same as the request. */
typedef NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_REQ_DATA_T  NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_CNF_DATA_T;

typedef NPXPCK_HIF_ADD_VOLATILE_OBJECT_REQ_T   NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_REQ_T;
typedef NPXPCK_HIF_ADD_VOLATILE_OBJECT_CNF_T   NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_CNF_T;

/*************************************************************************************/
/* Set Behavior Object instance number - structure is the same as in "Add Behavior Object" */

typedef NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_REQ_DATA_T NPXPCK_HIF_SET_BEHAVIOR_OBJECT_NUM_INST_REQ_DATA_T ;
/* The format of the confirmation message is the same as the request. */
typedef NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_CNF_DATA_T NPXPCK_HIF_SET_BEHAVIOR_OBJECT_NUM_INST_CNF_DATA_T;

typedef NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_REQ_T  NPXPCK_HIF_SET_BEHAVIOR_OBJECT_NUM_INST_REQ_T;
typedef NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_CNF_T  NPXPCK_HIF_SET_BEHAVIOR_OBJECT_NUM_INST_CNF_T;

/*************************************************************************************/
/* Read Behavior Object */

typedef NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_RES_DATA_T   NPXPCK_HIF_READ_BEHAVIOR_OBJECT_IND_DATA_T;
typedef NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND_DATA_T   NPXPCK_HIF_READ_BEHAVIOR_OBJECT_RES_DATA_T;

typedef __HIL_PACKED_PRE struct
{
  HIL_PACKET_HEADER_T                        tHead;
  NPXPCK_HIF_READ_BEHAVIOR_OBJECT_IND_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_READ_BEHAVIOR_OBJECT_IND_T;

typedef __HIL_PACKED_PRE struct
{
  HIL_PACKET_HEADER_T                        tHead;
  NPXPCK_HIF_READ_BEHAVIOR_OBJECT_RES_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_READ_BEHAVIOR_OBJECT_RES_T;

/*************************************************************************************/
/* Write Behavior Object */

typedef NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_RES_DATA_T   NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_RES_DATA_T;
typedef NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND_DATA_T   NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_IND_DATA_T;

typedef __HIL_PACKED_PRE struct
{
  HIL_PACKET_HEADER_T                         tHead;
  NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_IND_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_IND_T;

typedef __HIL_PACKED_PRE struct
{
  HIL_PACKET_HEADER_T                         tHead;
  NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_RES_DATA_T tData;

} __HIL_PACKED_POST NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_RES_T;


/* pragma unpack */
#ifdef __HIL_PRAGMA_PACK_ENABLE
#pragma __HIL_PRAGMA_UNPACK_1(__NPXPCK_HIF_PACKET)
#endif

#endif /* #ifndef __NPXPCK_HIF_PACKET_H */

/*************************************************************************************************/
/*-----------------------------------------------------------------------------------------------*/
/*-------------------------------- EOF  ---------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------*/
/*************************************************************************************************/
