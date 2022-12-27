/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id: NpxHostApi.c 3816 2018-02-28 16:09:11Z dirk $

  \file NpxHostApi.c
  \brief Provides netPROXY host functionality when accessed via DPM.

  \note Exclusion of Liability for this demo software:\n
    The following software is intended for and must only be used for reference and in an evaluation laboratory
    environment. It is provided without charge and is subject to alterations. There is no warranty for the software,
    to the extent permitted by applicable law. Except when otherwise stated in writing the copyright holders and/or
    other parties provide the software "as is" without warranty of any kind, either expressed or implied.\n
    Please refer to the Agreement in \ref disclaimer, provided  together with this file! By installing or otherwise
    using the software, you accept the terms of this Agreement. If you do not agree to the terms of this Agreement,
    then do not install or use the Software!

**************************************************************************************/

#include "NpxHostApi.h"

/* netPROXY dependencies */
#include "netPROXY.h"           /* netPROXY core */
#include "NpxPck_Hif_Packet.h"  /* netPROXY host adapter packet definitions */

/* Hilscher definitions */
#include "Hil_Results.h"

#include "string.h"

/*************************************************************************************/
/* Symbol Definitions                                                                */
/*************************************************************************************/


/* DPM access timeouts, given in ticks (multi-threaded mode only) */
#define NPX_HOST_RECV_TIMEOUT             5
#define NPX_HOST_SEND_TIMEOUT             1


/* driver states */
typedef enum NPX_HOST_DRIVER_STATE_Ttag
{
  NPX_HOST_DRIVER_STATE_UNDEFINED,
  NPX_HOST_DRIVER_STATE_INIT,
  NPX_HOST_DRIVER_STATE_READY,
  NPX_HOST_DRIVER_STATE_RUN,
  NPX_HOST_DRIVER_STATE_SHUTDOWN,
  NPX_HOST_DRIVER_STATE_TERMINATED,
} NPX_HOST_DRIVER_STATE_T;


/* interface states */
typedef enum NPX_HOST_INTERFACE_STATE_Ttag
{
  NPX_HOST_INTERFACE_STATE_UNDEFINED,
  NPX_HOST_INTERFACE_STATE_INIT,
  NPX_HOST_INTERFACE_STATE_READY,
  NPX_HOST_INTERFACE_STATE_RUN,
  NPX_HOST_INTERFACE_STATE_SHUTDOWN,
  NPX_HOST_INTERFACE_STATE_CLOSED,
} NPX_HOST_INTERFACE_STATE_T;



/*************************************************************************************/
/* Class, Type, and Structure Definitions                                            */
/*************************************************************************************/


/* internal management variant providing different views of the DPM packets */
typedef union NPX_HOST_PACKET_Ttag
{ /* generic packet view */
  CIFX_PACKET                                     tCifxPacket;
  CIFX_PACKET_HEADER                              tHeader;
  /* object data access */
  NPXPCK_HIF_READ_OBJECT_ELEMENT_REQ_T            tReadObjectElementReq;
  NPXPCK_HIF_READ_OBJECT_ELEMENT_CNF_T            tReadObjectElementCnf;
  NPXPCK_HIF_WRITE_OBJECT_ELEMENT_REQ_T           tWriteObjectElementReq;
  NPXPCK_HIF_WRITE_OBJECT_ELEMENT_CNF_T           tWriteObjectElementCnf;
  NPXPCK_HIF_GET_ELEMENT_BYTESIZE_REQ_T           tGetElementByteSizeReq;
  NPXPCK_HIF_GET_ELEMENT_BYTESIZE_CNF_T           tGetElementByteSizeCnf;
  /* object description management */
  NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_REQ_T         tAddObjectDescriptionReq;
  NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_CNF_T         tAddObjectDescriptionCnf;
  NPXPCK_HIF_GET_OBJECT_DESCRIPTION_REQ_T         tGetObjectDescriptionReq;
  NPXPCK_HIF_GET_OBJECT_DESCRIPTION_CNF_T         tGetObjectDescriptionCnf;
  NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_REQ_T      tDeleteObjectDescriptionReq;
  NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_CNF_T      tDeleteObjectDescriptionCnf;
  /* object management */
  NPXPCK_HIF_ADD_VOLATILE_OBJECT_REQ_T            tAddVolatileObjectReq;
  NPXPCK_HIF_ADD_VOLATILE_OBJECT_CNF_T            tAddVolatileObjectCnf;
  NPXPCK_HIF_DELETE_OBJECT_REQ_T                  tDeleteObjectReq;
  NPXPCK_HIF_DELETE_OBJECT_CNF_T                  tDeleteObjectCnf;
  NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_REQ_T        tGetNumberOfInstancesReq;
  NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_CNF_T        tGetNumberOfInstancesCnf;
  /* update notification management */
  NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_REQ_T   tRegisterUpdateNotificationReq;
  NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_CNF_T   tRegisterUpdateNotificationCnf;
  NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_REQ_T tUnregisterUpdateNotificationReq;
  NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_CNF_T tUnregisterUpdateNotificationCnf;
  NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND_T     tUpdateNotificationInd;
  NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_RES_T     tUpdateNotificationRes;
  /* behavior object management */
  NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_REQ_T            tAddBehaviorObjectReq;
  NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_CNF_T            tAddBehaviorObjectCnf;
  NPXPCK_HIF_SET_BEHAVIOR_OBJECT_NUM_INST_REQ_T   tSetBehaviorObjectNumInstReq;
  NPXPCK_HIF_SET_BEHAVIOR_OBJECT_NUM_INST_CNF_T   tSetBehaviorObjectNumInstCnf;
  NPXPCK_HIF_READ_BEHAVIOR_OBJECT_IND_T           tReadBehaviorObjectInd;
  NPXPCK_HIF_READ_BEHAVIOR_OBJECT_RES_T           tReadBehaviorObjectRes;
  NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_IND_T          tWriteBehaviorObjectInd;
  NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_RES_T          tWriteBehaviorObjectRes;
} NPX_HOST_PACKET_T;


/* internal management structure for the packet send FIFOs */
typedef struct NPX_HOST_FIFO_Ttag
{
  uint32_t           uSize;                       /* number of elements in the array of FIFO elements */
  uint32_t           uPutIndex;                   /* zero-based element index for the next put operation */
  uint32_t           uGetIndex;                   /* zero-based element index for the next get operation */
  NPX_HOST_PACKET_T* patElements;                 /* array of FIFO elements (buffer space) */
} NPX_HOST_FIFO_T;


/* internal management structure for callback addresses */
typedef union NPX_HOST_CALLBACK_Ttag
{
  uint32_t                                      ulAddress;
  NPX_HOST_READ_OBJECT_ELEMENT_CBK_T            tReadObjectElementCnf;
  NPX_HOST_WRITE_OBJECT_ELEMENT_CBK_T           tWriteObjectElementCnf;
  NPX_HOST_GET_ELEMENT_BYTESIZE_CBK_T           tGetElementByteSizeCnf;
  NPX_HOST_ADD_OBJECT_DESCRIPTION_CBK_T         tAddObjectDescriptionCnf;
  NPX_HOST_DELETE_OBJECT_DESCRIPTION_CBK_T      tDeleteObjectDescriptionCnf;
  NPX_HOST_GET_OBJECT_DESCRIPTION_CBK_T         tGetObjectDescriptionCnf;
  NPX_HOST_ADD_VOLATILE_OBJECT_CBK_T            tAddVolatileObjectCnf;
  NPX_HOST_DELETE_OBJECT_CBK_T                  tDeleteObjectCnf;
  NPX_HOST_GET_NUMBER_OF_INSTANCES_CBK_T        tGetNumberOfInstancesCnf;
  NPX_HOST_REGISTER_UPDATE_NOTIFICATION_CBK_T   tRegisterUpdateNotificationCnf;
  NPX_HOST_UNREGISTER_UPDATE_NOTIFICATION_CBK_T tUnregisterUpdateNotificationCnf;
  NPX_HOST_UPDATE_NOTIFICATION_CBK_T            tUpdateNotificationInd;
  NPX_HOST_ADD_BEHAVIOR_OBJECT_CBK_T            tAddBehaviorObjectCnf;
  NPX_HOST_SET_BEHAVIOR_OBJECT_NUM_INST_CBK_T   tSetBehaviorObjectNumInstCnf;
  NPX_HOST_BEHAVIOR_OBJECT_READ_CBK_T           tBehaviorObjectReadInd;
  NPX_HOST_BEHAVIOR_OBJECT_WRITE_CBK_T          tBehaviorObjectWriteInd;
} NPX_HOST_CALLBACK_T;


/* internal management structure for outstanding services */
typedef struct NPX_HOST_OUTSTANDING_Ttag
{
  uint32_t            ulId;                     /* unique ID assigned to the service request packet */
  uint32_t            ulCmd;                    /* command code expected in the service confirmation packet */
  uint32_t            ulGroupId;                /* group ID of the associated object */
  uint32_t            ulObjectId;               /* object ID of the associated object */
  void*               hEvent;                   /* handle for the event to be fired when completing a synchronous service */
  NPX_HOST_CALLBACK_T pfnDone;                  /* address of the callback to be invoked when receiving the confirmation packet */
  void*               pvDoneParam;              /* generic parameter to be passed to the confirmation callback */
  NPX_HOST_CALLBACK_T pfnIndication;            /* address of the callback to be invoked when receiving an Update Notification / read indication packet */
  NPX_HOST_CALLBACK_T pfnIndication2;           /* address of the callback to be invoked when receiving a write indication packet */
  void*               pvIndicationParam;        /* generic parameter to be passed to the Update Notification callback */
} NPX_HOST_OUTSTANDING_T;


/* internal management structure for synchronous API calls */
typedef struct NPX_HOST_SYNC_Ttag
{
  uint32_t                ulNpxResult;          /* result / status code taken from the service confirmation packet */
  NPX_HOST_OUTSTANDING_T* ptOutstanding;        /* address of the associated outstanding service management record */
  void*                   pvBuffer;             /* application data buffer used with services expected to return data */
  uint32_t                ulDataLen;            /* length of the application data in the buffer */
} NPX_HOST_SYNC_T;


/* internal management structure for interfaces */
typedef struct NPX_HOST_INTERFACE_Ttag
{
  NPX_HOST_INTERFACE_STATE_T  eState;
  void*                       hMutex;
  CIFXHANDLE                  hChannel;
  uint32_t                    ulRefCount;
  uint32_t                    ulBoard;
  uint32_t                    ulChannel;
  uint32_t                    ulSendPacketCount;
  uint32_t                    ulSendErrorCount;
  uint32_t                    ulRecvPacketCount;
  uint32_t                    ulRecvErrorCount;
  NPX_HOST_FIFO_T             tSendFifo;
  NPX_HOST_OUTSTANDING_T*     patOutstanding;
} NPX_HOST_INTERFACE_T;


/* internal management structure for the complete host API implementation */
typedef struct NPX_HOST_Ttag
{
  NPX_HOST_DRIVER_STATE_T     eState;
  void*                       hMutex;
  CIFXHANDLE                  hDriver;
  uint32_t                    ulRefCount;
  NPX_HOST_CONFIG_T           tConfig;
  NPX_HOST_INTERFACE_T*       patInterfaces;
} NPX_HOST_T;



/*************************************************************************************/
/* Global Variables                                                                  */
/*************************************************************************************/


/* the one and only instance of the host API implementation */
static NPX_HOST_T s_tNpxHostApi;



/*************************************************************************************/
/* Macros                                                                            */
/*************************************************************************************/


/* Macro-based FIFO implementation, taken from PS_Toolbox_Public.h.
 * (copied to avoid including the external references defined in this header file)
 *
 * Can be used with any structure containing the following fields:
 *
 * struct {
 *   xxxx uSize;
 *   xxxx uPutIndex;
 *   xxxx uGetIndex;
 *   xxxx *patElements
 * }
 *
 * patElements can also be a statically declared array.
 * patElements can be of any kind of type,
 * insertion is atomic per element
 */
#define FIFO_DEPTH(ptFifo) ((ptFifo)->uSize)
#define FIFO_LEVEL(ptFifo) (((ptFifo)->uPutIndex - (ptFifo)->uGetIndex) + (((ptFifo)->uPutIndex >= (ptFifo)->uGetIndex) ? 0 : (2*(ptFifo)->uSize)))

#define FIFO_EMPTY(ptFifo) (FIFO_LEVEL(ptFifo) == 0)
#define FIFO_FULL(ptFifo)  (FIFO_LEVEL(ptFifo) >= FIFO_DEPTH(ptFifo))

#define FIFO_INDEX_PUT(ptFifo) ((ptFifo)->uPutIndex - (((ptFifo)->uPutIndex >= (ptFifo)->uSize) ? (ptFifo)->uSize : 0))
#define FIFO_INDEX_GET(ptFifo) ((ptFifo)->uGetIndex - (((ptFifo)->uGetIndex >= (ptFifo)->uSize) ? (ptFifo)->uSize : 0))

#define FIFO_IN(ptFifo)  ((ptFifo)->patElements[FIFO_INDEX_PUT(ptFifo)])
#define FIFO_OUT(ptFifo) ((ptFifo)->patElements[FIFO_INDEX_GET(ptFifo)])

#define FIFO_NEXT(ptFifo) ((ptFifo)->uGetIndex = ((((ptFifo)->uGetIndex + 1) < (2*(ptFifo)->uSize)) ? ((ptFifo)->uGetIndex + 1) : 0))
#define FIFO_PUT(ptFifo)  ((ptFifo)->uPutIndex = ((((ptFifo)->uPutIndex + 1) < (2*(ptFifo)->uSize)) ? ((ptFifo)->uPutIndex + 1) : 0))



/*************************************************************************************/
/* Internal Callbacks used with Synchronous API Functions                            */
/*************************************************************************************/


static void APIENTRY NpxHost_ReadObjectElementDone(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulObjectInstance,
  uint32_t   ulElementNumber,
  void*      pvBuffer,
  uint32_t   ulDataLen)
{
  NPX_HOST_SYNC_T* ptSync = (NPX_HOST_SYNC_T*) pvDoneParam;

  if (ptSync != NULL)
  {
    ptSync->ulNpxResult = ulNpxResult;
    if (ptSync->pvBuffer != NULL && pvBuffer != NULL)
    {
      ptSync->ulDataLen = ulDataLen;
      OS_Memcpy(ptSync->pvBuffer, pvBuffer, ulDataLen);
    }
    if (ptSync->ptOutstanding != NULL && ptSync->ptOutstanding->hEvent != NULL)
      OS_SetEvent(ptSync->ptOutstanding->hEvent);
  }
}



static void APIENTRY NpxHost_WriteObjectElementDone(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulObjectInstance,
  uint32_t   ulElementNumber)
{
  NPX_HOST_SYNC_T* ptSync = (NPX_HOST_SYNC_T*) pvDoneParam;

  if (ptSync != NULL)
  {
    ptSync->ulNpxResult = ulNpxResult;
    if (ptSync->ptOutstanding != NULL && ptSync->ptOutstanding->hEvent != NULL)
      OS_SetEvent(ptSync->ptOutstanding->hEvent);
  }
}



static void APIENTRY NpxHost_GetElementByteSizeDone(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulObjectId,
  uint32_t   ulElementNumber,
  uint32_t   ulByteSize)
{
  NPX_HOST_SYNC_T* ptSync = (NPX_HOST_SYNC_T*) pvDoneParam;

  if (ptSync != NULL)
  {
    ptSync->ulNpxResult = ulNpxResult;
    if (ptSync->pvBuffer != NULL)
    {
      ptSync->ulDataLen = sizeof(ulByteSize);
      OS_Memcpy(ptSync->pvBuffer, &ulByteSize, sizeof(ulByteSize));
    }
    if (ptSync->ptOutstanding != NULL && ptSync->ptOutstanding->hEvent != NULL)
      OS_SetEvent(ptSync->ptOutstanding->hEvent);
  }
}



static void APIENTRY NpxHost_AddObjectDescriptionDone(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulObjectId)
{
  NPX_HOST_SYNC_T* ptSync = (NPX_HOST_SYNC_T*) pvDoneParam;

  if (ptSync != NULL)
  {
    ptSync->ulNpxResult = ulNpxResult;
    if (ptSync->ptOutstanding != NULL && ptSync->ptOutstanding->hEvent != NULL)
      OS_SetEvent(ptSync->ptOutstanding->hEvent);
  }
}



static void APIENTRY NpxHost_GetObjectDescriptionDone(
  uint32_t                              ulNpxResult,
  void*                                 pvDoneParam,
  NPX_HOST_OBJECT_DESCRIPTION_BUFFER_T* ptObjectDescriptionBuffer,
  uint32_t                              ulDataLen)
{
  NPX_HOST_SYNC_T* ptSync = (NPX_HOST_SYNC_T*) pvDoneParam;

  if (ptSync != NULL)
  {
    ptSync->ulNpxResult = ulNpxResult;
    if (ptSync->pvBuffer != NULL && ptObjectDescriptionBuffer != NULL)
    {
      ptSync->ulDataLen = ulDataLen;
      OS_Memcpy(ptSync->pvBuffer, ptObjectDescriptionBuffer, ulDataLen);
    }
    if (ptSync->ptOutstanding != NULL && ptSync->ptOutstanding->hEvent != NULL)
      OS_SetEvent(ptSync->ptOutstanding->hEvent);
  }
}



static void APIENTRY NpxHost_DeleteObjectDescriptionDone(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulObjectId)
{
  NPX_HOST_SYNC_T* ptSync = (NPX_HOST_SYNC_T*) pvDoneParam;

  if (ptSync != NULL)
  {
    ptSync->ulNpxResult = ulNpxResult;
    if (ptSync->ptOutstanding != NULL && ptSync->ptOutstanding->hEvent != NULL)
      OS_SetEvent(ptSync->ptOutstanding->hEvent);
  }
}



static void APIENTRY NpxHost_AddVolatileObjectDone(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulNumberOfInstances)
{
  NPX_HOST_SYNC_T* ptSync = (NPX_HOST_SYNC_T*) pvDoneParam;

  if (ptSync != NULL)
  {
    ptSync->ulNpxResult = ulNpxResult;
    if (ptSync->ptOutstanding != NULL && ptSync->ptOutstanding->hEvent != NULL)
      OS_SetEvent(ptSync->ptOutstanding->hEvent);
  }
}



static void APIENTRY NpxHost_DeleteObjectDone(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId)
{
  NPX_HOST_SYNC_T* ptSync = (NPX_HOST_SYNC_T*) pvDoneParam;

  if (ptSync != NULL)
  {
    ptSync->ulNpxResult = ulNpxResult;
    if (ptSync->ptOutstanding != NULL && ptSync->ptOutstanding->hEvent != NULL)
      OS_SetEvent(ptSync->ptOutstanding->hEvent);
  }
}



static void APIENTRY NpxHost_GetNumberOfInstancesDone(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulNumberOfInstances)
{
  NPX_HOST_SYNC_T* ptSync = (NPX_HOST_SYNC_T*) pvDoneParam;

  if (ptSync != NULL)
  {
    ptSync->ulNpxResult = ulNpxResult;
    if (ptSync->pvBuffer != NULL)
    {
      ptSync->ulDataLen = sizeof(ulNumberOfInstances);
      OS_Memcpy(ptSync->pvBuffer, &ulNumberOfInstances, sizeof(ulNumberOfInstances));
    }
    if (ptSync->ptOutstanding != NULL && ptSync->ptOutstanding->hEvent != NULL)
      OS_SetEvent(ptSync->ptOutstanding->hEvent);
  }
}



static void APIENTRY NpxHost_RegisterUpdateNotificationDone(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulObjectInstance,
  uint32_t   ulElementNumber)
{
  NPX_HOST_SYNC_T* ptSync = (NPX_HOST_SYNC_T*) pvDoneParam;

  if (ptSync != NULL)
  {
    ptSync->ulNpxResult = ulNpxResult;
    if (ptSync->ptOutstanding != NULL && ptSync->ptOutstanding->hEvent != NULL)
      OS_SetEvent(ptSync->ptOutstanding->hEvent);
  }
}



static void APIENTRY NpxHost_UnregisterUpdateNotificationDone(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulObjectInstance,
  uint32_t   ulElementNumber)
{
  NPX_HOST_SYNC_T* ptSync = (NPX_HOST_SYNC_T*) pvDoneParam;

  if (ptSync != NULL)
  {
    ptSync->ulNpxResult = ulNpxResult;
    if (ptSync->ptOutstanding != NULL && ptSync->ptOutstanding->hEvent != NULL)
      OS_SetEvent(ptSync->ptOutstanding->hEvent);
  }
}



static void APIENTRY NpxHost_AddBehaviorObjectDone(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulNumberOfInstances)
{
  NPX_HOST_SYNC_T* ptSync = (NPX_HOST_SYNC_T*) pvDoneParam;

  if (ptSync != NULL)
  {
    ptSync->ulNpxResult = ulNpxResult;
    if (ptSync->ptOutstanding != NULL && ptSync->ptOutstanding->hEvent != NULL)
      OS_SetEvent(ptSync->ptOutstanding->hEvent);
  }
}



static void APIENTRY NpxHost_SetBehaviorObjectNumInstDone(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulNumberOfInstances)
{
  NPX_HOST_SYNC_T* ptSync = (NPX_HOST_SYNC_T*) pvDoneParam;

  if (ptSync != NULL)
  {
    ptSync->ulNpxResult = ulNpxResult;
    if (ptSync->ptOutstanding != NULL && ptSync->ptOutstanding->hEvent != NULL)
      OS_SetEvent(ptSync->ptOutstanding->hEvent);
  }
}



/*************************************************************************************/
/* Basic Helper Functions                                                            */
/*************************************************************************************/


static uint32_t NpxHost_GetPacketId(void)
{
  static uint32_t         s_ulPacketId;
  uint32_t                ulPacketId;
  void*                   hLock = NULL;

  OS_DisableInterrupts(&hLock);
  ulPacketId = ++s_ulPacketId;
  if (ulPacketId == 0)
    ulPacketId = ++s_ulPacketId;
  OS_EnableInterrupts(&hLock);
  return (ulPacketId);
}



static void NpxHost_InitPacketHeader(NPX_HOST_PACKET_T* ptPacket)
{
  if (ptPacket != NULL)
  {
    ptPacket->tHeader.ulDest    = 0x20;
    ptPacket->tHeader.ulSrc     = 0;
    ptPacket->tHeader.ulDestId  = 0;
    ptPacket->tHeader.ulSrcId   = 0;
    ptPacket->tHeader.ulLen     = 0;
    ptPacket->tHeader.ulId      = NpxHost_GetPacketId();
    ptPacket->tHeader.ulState   = SUCCESS_NET_PROXY_OK;
    ptPacket->tHeader.ulCmd     = 0;
    ptPacket->tHeader.ulExt     = 0;
    ptPacket->tHeader.ulRout    = 0;
  }
}



static NPX_HOST_INTERFACE_T* NpxHost_GetInterface(NPX_HOST_IF_H hInterface)
{
  NPX_HOST_INTERFACE_T* ptInterface = (NPX_HOST_INTERFACE_T*) hInterface;

  if (ptInterface == NULL
  ||  ptInterface <  s_tNpxHostApi.patInterfaces
  ||  ptInterface >= s_tNpxHostApi.patInterfaces + s_tNpxHostApi.tConfig.ulMaxInterfaces
  ||  (ptInterface - s_tNpxHostApi.patInterfaces) % (int) sizeof(*ptInterface) != 0
  ||  ptInterface->hChannel   == NULL
  ||  ptInterface->ulRefCount == 0)
    ptInterface = NULL;
  return (ptInterface);
}



static uint32_t   NpxHost_ResetInterface(NPX_HOST_INTERFACE_T* ptInterface)
{
  uint32_t                ulNpxResult   = SUCCESS_NET_PROXY_OK;
  uint32_t                ulIndex       = 0;
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;

  if (ptInterface == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    ptInterface->eState = NPX_HOST_INTERFACE_STATE_SHUTDOWN;

    if (ptInterface->hChannel != NULL)
    {
      (void) xChannelClose(ptInterface->hChannel);
      ptInterface->hChannel = NULL;
    }
    for (ulIndex = 0; ulIndex < s_tNpxHostApi.tConfig.ulMaxOutstanding; ulIndex++)
    {
      ptOutstanding = &ptInterface->patOutstanding[ulIndex];
      if (ptOutstanding->hEvent != NULL)
      {
        OS_DeleteEvent(ptOutstanding->hEvent);
        ptOutstanding->hEvent = NULL;
      }
    }
    ptInterface->tSendFifo.uPutIndex = ptInterface->tSendFifo.uGetIndex = 0;
    ptInterface->eState = NPX_HOST_INTERFACE_STATE_CLOSED;
  }
  return (ulNpxResult);
}



static uint32_t NpxHost_GetGroupId(NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t ulGroupId = 0;

  if (NULL != ptPacket)
  {
    switch (ptPacket->tHeader.ulCmd)
    {
      case NPXPCK_HIF_READ_OBJECT_ELEMENT_REQ            : ulGroupId = ptPacket->tReadObjectElementReq.tData.ulGroupId;            break;
      case NPXPCK_HIF_READ_OBJECT_ELEMENT_CNF            : ulGroupId = ptPacket->tReadObjectElementCnf.tData.ulGroupId;            break;
      case NPXPCK_HIF_WRITE_OBJECT_ELEMENT_REQ           : ulGroupId = ptPacket->tWriteObjectElementReq.tData.ulGroupId;           break;
      case NPXPCK_HIF_WRITE_OBJECT_ELEMENT_CNF           : ulGroupId = ptPacket->tWriteObjectElementCnf.tData.ulGroupId;           break;
      case NPXPCK_HIF_GET_ELEMENT_BYTESIZE_REQ           : ulGroupId = 0;                                                          break;
      case NPXPCK_HIF_GET_ELEMENT_BYTESIZE_CNF           : ulGroupId = 0;                                                          break;
      /* object description management */
      case NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_REQ         : ulGroupId = 0;                                                          break;
      case NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_CNF         : ulGroupId = 0;                                                          break;
      case NPXPCK_HIF_GET_OBJECT_DESCRIPTION_REQ         : ulGroupId = 0;                                                          break;
      case NPXPCK_HIF_GET_OBJECT_DESCRIPTION_CNF         : ulGroupId = 0;                                                          break;
      case NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_REQ      : ulGroupId = 0;                                                          break;
      case NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_CNF      : ulGroupId = 0;                                                          break;
      /* object management */
      case NPXPCK_HIF_ADD_VOLATILE_OBJECT_REQ            : ulGroupId = ptPacket->tAddVolatileObjectReq.tData.ulGroupId;            break;
      case NPXPCK_HIF_ADD_VOLATILE_OBJECT_CNF            : ulGroupId = ptPacket->tAddVolatileObjectCnf.tData.ulGroupId;            break;
      case NPXPCK_HIF_DELETE_OBJECT_REQ                  : ulGroupId = ptPacket->tDeleteObjectReq.tData.ulGroupId;                 break;
      case NPXPCK_HIF_DELETE_OBJECT_CNF                  : ulGroupId = ptPacket->tDeleteObjectCnf.tData.ulGroupId;                 break;
      case NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_REQ        : ulGroupId = ptPacket->tGetNumberOfInstancesReq.tData.ulGroupId;         break;
      case NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_CNF        : ulGroupId = ptPacket->tGetNumberOfInstancesCnf.tData.ulGroupId;         break;
      /* update notification management */
      case NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_REQ   : ulGroupId = ptPacket->tRegisterUpdateNotificationReq.tData.ulGroupId;   break;
      case NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_CNF   : ulGroupId = ptPacket->tRegisterUpdateNotificationCnf.tData.ulGroupId;   break;
      case NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_REQ : ulGroupId = ptPacket->tUnregisterUpdateNotificationReq.tData.ulGroupId; break;
      case NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_CNF : ulGroupId = ptPacket->tUnregisterUpdateNotificationCnf.tData.ulGroupId; break;
      case NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND     : ulGroupId = ptPacket->tUpdateNotificationInd.tData.ulGroupId;           break;
      case NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_RES     : ulGroupId = ptPacket->tUpdateNotificationRes.tData.ulGroupId;           break;
      /* Behavior object management */
      case NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_REQ            : ulGroupId = ptPacket->tAddBehaviorObjectReq.tData.ulGroupId;            break;
      case NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_CNF            : ulGroupId = ptPacket->tAddBehaviorObjectCnf.tData.ulGroupId;            break;
      case NPXPCK_HIF_SET_BEHAVIOR_OBJECT_NUM_INST_REQ   : ulGroupId = ptPacket->tSetBehaviorObjectNumInstReq.tData.ulGroupId;     break;
      case NPXPCK_HIF_SET_BEHAVIOR_OBJECT_NUM_INST_CNF   : ulGroupId = ptPacket->tSetBehaviorObjectNumInstCnf.tData.ulGroupId;     break;
      case NPXPCK_HIF_READ_BEHAVIOR_OBJECT_IND           : ulGroupId = ptPacket->tReadBehaviorObjectInd.tData.ulGroupId;           break;
      case NPXPCK_HIF_READ_BEHAVIOR_OBJECT_RES           : ulGroupId = ptPacket->tReadBehaviorObjectRes.tData.ulGroupId;           break;
      case NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_IND          : ulGroupId = ptPacket->tWriteBehaviorObjectInd.tData.ulGroupId;          break;
      case NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_RES          : ulGroupId = ptPacket->tWriteBehaviorObjectRes.tData.ulGroupId;          break;
      default                                            : ulGroupId = 0;
    }
  }
  return (ulGroupId);
}



static uint32_t NpxHost_GetObjectId(NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t ulObjectId = 0;

  if (NULL != ptPacket)
  {
    switch (ptPacket->tHeader.ulCmd)
    {
      case NPXPCK_HIF_READ_OBJECT_ELEMENT_REQ            : ulObjectId = ptPacket->tReadObjectElementReq.tData.ulObjectId;            break;
      case NPXPCK_HIF_READ_OBJECT_ELEMENT_CNF            : ulObjectId = ptPacket->tReadObjectElementCnf.tData.ulObjectId;            break;
      case NPXPCK_HIF_WRITE_OBJECT_ELEMENT_REQ           : ulObjectId = ptPacket->tWriteObjectElementReq.tData.ulObjectId;           break;
      case NPXPCK_HIF_WRITE_OBJECT_ELEMENT_CNF           : ulObjectId = ptPacket->tWriteObjectElementCnf.tData.ulObjectId;           break;
      case NPXPCK_HIF_GET_ELEMENT_BYTESIZE_REQ           : ulObjectId = ptPacket->tGetElementByteSizeReq.tData.ulObjectId;           break;
      case NPXPCK_HIF_GET_ELEMENT_BYTESIZE_CNF           : ulObjectId = ptPacket->tGetElementByteSizeCnf.tData.ulObjectId;           break;
      /* object description management */
      case NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_REQ         : ulObjectId = ptPacket->tAddObjectDescriptionReq.tData.ulObjectId;         break;
      case NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_CNF         : ulObjectId = ptPacket->tAddObjectDescriptionCnf.tData.ulObjectId;         break;
      case NPXPCK_HIF_GET_OBJECT_DESCRIPTION_REQ         : ulObjectId = ptPacket->tGetObjectDescriptionReq.tData.ulObjectId;         break;
      case NPXPCK_HIF_GET_OBJECT_DESCRIPTION_CNF         : ulObjectId = ptPacket->tGetObjectDescriptionCnf.tData.ulObjectId;         break;
      case NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_REQ      : ulObjectId = ptPacket->tDeleteObjectDescriptionReq.tData.ulObjectId;      break;
      case NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_CNF      : ulObjectId = ptPacket->tDeleteObjectDescriptionCnf.tData.ulObjectId;      break;
      /* object management */
      case NPXPCK_HIF_ADD_VOLATILE_OBJECT_REQ            : ulObjectId = ptPacket->tAddVolatileObjectReq.tData.ulObjectId;            break;
      case NPXPCK_HIF_ADD_VOLATILE_OBJECT_CNF            : ulObjectId = ptPacket->tAddVolatileObjectCnf.tData.ulObjectId;            break;
      case NPXPCK_HIF_DELETE_OBJECT_REQ                  : ulObjectId = ptPacket->tDeleteObjectReq.tData.ulObjectId;                 break;
      case NPXPCK_HIF_DELETE_OBJECT_CNF                  : ulObjectId = ptPacket->tDeleteObjectCnf.tData.ulObjectId;                 break;
      case NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_REQ        : ulObjectId = ptPacket->tGetNumberOfInstancesReq.tData.ulObjectId;         break;
      case NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_CNF        : ulObjectId = ptPacket->tGetNumberOfInstancesCnf.tData.ulObjectId;         break;
      /* update notification management */
      case NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_REQ   : ulObjectId = ptPacket->tRegisterUpdateNotificationReq.tData.ulObjectId;   break;
      case NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_CNF   : ulObjectId = ptPacket->tRegisterUpdateNotificationCnf.tData.ulObjectId;   break;
      case NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_REQ : ulObjectId = ptPacket->tUnregisterUpdateNotificationReq.tData.ulObjectId; break;
      case NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_CNF : ulObjectId = ptPacket->tUnregisterUpdateNotificationCnf.tData.ulObjectId; break;
      case NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND     : ulObjectId = ptPacket->tUpdateNotificationInd.tData.ulObjectId;           break;
      case NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_RES     : ulObjectId = ptPacket->tUpdateNotificationRes.tData.ulObjectId;           break;
      /* Behavior object management */
      case NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_REQ            : ulObjectId = ptPacket->tAddBehaviorObjectReq.tData.ulObjectId;            break;
      case NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_CNF            : ulObjectId = ptPacket->tAddBehaviorObjectCnf.tData.ulObjectId;            break;
      case NPXPCK_HIF_SET_BEHAVIOR_OBJECT_NUM_INST_REQ   : ulObjectId = ptPacket->tSetBehaviorObjectNumInstReq.tData.ulObjectId;     break;
      case NPXPCK_HIF_SET_BEHAVIOR_OBJECT_NUM_INST_CNF   : ulObjectId = ptPacket->tSetBehaviorObjectNumInstCnf.tData.ulObjectId;     break;
      case NPXPCK_HIF_READ_BEHAVIOR_OBJECT_IND           : ulObjectId = ptPacket->tReadBehaviorObjectInd.tData.ulObjectId;           break;
      case NPXPCK_HIF_READ_BEHAVIOR_OBJECT_RES           : ulObjectId = ptPacket->tReadBehaviorObjectRes.tData.ulObjectId;           break;
      case NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_IND          : ulObjectId = ptPacket->tWriteBehaviorObjectInd.tData.ulObjectId;          break;
      case NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_RES          : ulObjectId = ptPacket->tWriteBehaviorObjectRes.tData.ulObjectId;          break;
      default                                            : ulObjectId = 0;
    }
  }
  return (ulObjectId);
}



static NPX_HOST_OUTSTANDING_T* NpxHost_GetOutstanding(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;

  if (ptInterface != NULL && ptInterface->patOutstanding != NULL && ptPacket != NULL)
  {
    switch (ptPacket->tHeader.ulCmd)
    {
      case NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND:
      { /* indication: entry index located in ulDestId */
        if (ptPacket->tHeader.ulDestId < s_tNpxHostApi.tConfig.ulMaxOutstanding
        &&  ptInterface->patOutstanding[ptPacket->tHeader.ulDestId].ulId != 0
        &&  ptInterface->patOutstanding[ptPacket->tHeader.ulDestId].ulCmd == ptPacket->tHeader.ulCmd
        &&  ptInterface->patOutstanding[ptPacket->tHeader.ulDestId].pfnIndication.ulAddress != 0)
          ptOutstanding = &ptInterface->patOutstanding[ptPacket->tHeader.ulDestId];
        break;
      }
      case NPXPCK_HIF_READ_BEHAVIOR_OBJECT_IND:
      { /* indication: entry index located in ulDestId */
        if (ptPacket->tHeader.ulDestId < s_tNpxHostApi.tConfig.ulMaxOutstanding
        &&  ptInterface->patOutstanding[ptPacket->tHeader.ulDestId].ulId != 0
        &&  ptInterface->patOutstanding[ptPacket->tHeader.ulDestId].ulCmd == ptPacket->tHeader.ulCmd
        &&  ptInterface->patOutstanding[ptPacket->tHeader.ulDestId].pfnIndication.ulAddress != 0)
          ptOutstanding = &ptInterface->patOutstanding[ptPacket->tHeader.ulDestId];
        break;
      }
      case NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_IND:
      { /* indication: entry index located in ulDestId */
        if (ptPacket->tHeader.ulDestId < s_tNpxHostApi.tConfig.ulMaxOutstanding
        &&  ptInterface->patOutstanding[ptPacket->tHeader.ulDestId].ulId != 0
        &&  ptInterface->patOutstanding[ptPacket->tHeader.ulDestId].ulCmd == NPXPCK_HIF_READ_BEHAVIOR_OBJECT_IND
        &&  ptInterface->patOutstanding[ptPacket->tHeader.ulDestId].pfnIndication2.ulAddress != 0)
          ptOutstanding = &ptInterface->patOutstanding[ptPacket->tHeader.ulDestId];
        break;
      }
      default:
      { /* confirmation: entry index located in ulSrcId */
        if (ptPacket->tHeader.ulSrcId < s_tNpxHostApi.tConfig.ulMaxOutstanding
        &&  ptInterface->patOutstanding[ptPacket->tHeader.ulSrcId].ulId != 0
        &&  ptInterface->patOutstanding[ptPacket->tHeader.ulSrcId].ulId == ptPacket->tHeader.ulId
        &&  ptInterface->patOutstanding[ptPacket->tHeader.ulSrcId].ulCmd == ptPacket->tHeader.ulCmd
        &&  ptInterface->patOutstanding[ptPacket->tHeader.ulSrcId].pfnDone.ulAddress != 0)
          ptOutstanding = &ptInterface->patOutstanding[ptPacket->tHeader.ulSrcId];
      }
    }
  }
  return (ptOutstanding);
}



static uint32_t   NpxHost_SetOutstanding(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket, uint32_t ulDoneAddress, void* pvDoneParam, uint32_t ulIndicationAddress, uint32_t ulIndication2Address, void* pvIndicationParam)
{
  uint32_t                ulNpxResult   = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;
  uint32_t                ulIndex       = 0;

  if (ptInterface == NULL || ptInterface->patOutstanding == NULL || ptPacket == NULL || ulDoneAddress == 0)
    ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
  else
  {
    for (ulIndex = 0; ulIndex < s_tNpxHostApi.tConfig.ulMaxOutstanding; ulIndex++)
    {
      ptOutstanding = &ptInterface->patOutstanding[ulIndex];
      if (ptOutstanding->ulId == 0)
      { /* found a free entry */
        ptOutstanding->ulId                     = ptPacket->tHeader.ulId;
        ptOutstanding->ulCmd                    = ptPacket->tHeader.ulCmd | 1;
        ptOutstanding->ulGroupId                = NpxHost_GetGroupId(ptPacket);
        ptOutstanding->ulObjectId               = NpxHost_GetObjectId(ptPacket);
        ptOutstanding->pfnDone.ulAddress        = ulDoneAddress;
        ptOutstanding->pvDoneParam              = pvDoneParam;
        ptOutstanding->pfnIndication.ulAddress  = ulIndicationAddress;
        ptOutstanding->pfnIndication2.ulAddress = ulIndication2Address;
        ptOutstanding->pvIndicationParam        = pvIndicationParam;
        ptPacket->tHeader.ulSrcId               = ulIndex;
        if (ptOutstanding->hEvent != NULL)
        { /* check if this is a synchronous call */
          if (ulDoneAddress == (uint32_t) NpxHost_ReadObjectElementDone
          ||  ulDoneAddress == (uint32_t) NpxHost_WriteObjectElementDone
          ||  ulDoneAddress == (uint32_t) NpxHost_GetElementByteSizeDone
          ||  ulDoneAddress == (uint32_t) NpxHost_AddObjectDescriptionDone
          ||  ulDoneAddress == (uint32_t) NpxHost_GetObjectDescriptionDone
          ||  ulDoneAddress == (uint32_t) NpxHost_DeleteObjectDescriptionDone
          ||  ulDoneAddress == (uint32_t) NpxHost_AddVolatileObjectDone
          ||  ulDoneAddress == (uint32_t) NpxHost_DeleteObjectDone
          ||  ulDoneAddress == (uint32_t) NpxHost_GetNumberOfInstancesDone
          ||  ulDoneAddress == (uint32_t) NpxHost_RegisterUpdateNotificationDone
          ||  ulDoneAddress == (uint32_t) NpxHost_UnregisterUpdateNotificationDone
          ||  ulDoneAddress == (uint32_t) NpxHost_AddBehaviorObjectDone
          ||  ulDoneAddress == (uint32_t) NpxHost_SetBehaviorObjectNumInstDone)
          { /* synchronous call: link the management structures and reset the wakeup event */
            ((NPX_HOST_SYNC_T*) ptOutstanding->pvDoneParam)->ptOutstanding = ptOutstanding;
            (void) OS_WaitEvent(ptOutstanding->hEvent, 0);
          }
        }
        break;
      }
    }
    if (ulIndex >= s_tNpxHostApi.tConfig.ulMaxOutstanding)
      ulNpxResult = NPX_HOST_ERR_MAX_OUTSTANDING;
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_ReleaseOutstandingIndications(NPX_HOST_INTERFACE_T* ptInterface, uint32_t ulGroupId, uint32_t ulObjectId)
{
  uint32_t                ulNpxResult   = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;
  uint32_t                ulIndex       = 0;

  if (ptInterface == NULL || ptInterface->patOutstanding == NULL)
    ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
  else
  {
    for (ulIndex = 0; ulIndex < s_tNpxHostApi.tConfig.ulMaxOutstanding; ulIndex++)
    {
      ptOutstanding = &ptInterface->patOutstanding[ulIndex];
      if (ptOutstanding->ulId != 0 && ptOutstanding->ulGroupId == ulGroupId && ptOutstanding->ulObjectId == ulObjectId)
      { /* found a matching entry: release it */
        ptOutstanding->ulId = 0;
      }
    }
  }
  return (ulNpxResult);
}



/*************************************************************************************/
/* Internal Callbacks used with Asynchronous API Functions                           */
/*************************************************************************************/


static uint32_t   NpxHost_ReadObjectElementCnf(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t                ulNpxResult   = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;
  uint32_t                ulDataLen     = 0;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    ptOutstanding = NpxHost_GetOutstanding(ptInterface, ptPacket);
    if (ptOutstanding == NULL)
      ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    else
    { /* invoke the callback associated with the outstanding service entry */
      if (ptOutstanding->pfnDone.ulAddress != 0)
      {
        ulDataLen = ptPacket->tHeader.ulLen - (sizeof(ptPacket->tReadObjectElementCnf.tData) - sizeof(ptPacket->tReadObjectElementCnf.tData.abData));
        ptOutstanding->pfnDone.tReadObjectElementCnf(
          ptPacket->tHeader.ulState,
          ptOutstanding->pvDoneParam,
          ptPacket->tReadObjectElementCnf.tData.ulGroupId,
          ptPacket->tReadObjectElementCnf.tData.ulObjectId,
          ptPacket->tReadObjectElementCnf.tData.ulObjectInstance,
          ptPacket->tReadObjectElementCnf.tData.ulElementNo,
          ptPacket->tReadObjectElementCnf.tData.abData,
          ulDataLen);
      }
      /* release the outstanding service entry */
      ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_WriteObjectElementCnf(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t                ulNpxResult   = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    ptOutstanding = NpxHost_GetOutstanding(ptInterface, ptPacket);
    if (ptOutstanding == NULL)
      ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    else
    { /* invoke the callback associated with the outstanding service entry */
      if (ptOutstanding->pfnDone.ulAddress != 0)
      {
        ptOutstanding->pfnDone.tWriteObjectElementCnf(
          ptPacket->tHeader.ulState,
          ptOutstanding->pvDoneParam,
          ptPacket->tWriteObjectElementCnf.tData.ulGroupId,
          ptPacket->tWriteObjectElementCnf.tData.ulObjectId,
          ptPacket->tWriteObjectElementCnf.tData.ulObjectInstance,
          ptPacket->tWriteObjectElementCnf.tData.ulElementNo);
      }
      /* release the outstanding service entry */
      ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_GetElementByteSizeCnf(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t                ulNpxResult   = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    ptOutstanding = NpxHost_GetOutstanding(ptInterface, ptPacket);
    if (ptOutstanding == NULL)
      ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    else
    { /* invoke the callback associated with the outstanding service entry */
      if (ptOutstanding->pfnDone.ulAddress != 0)
      {
        ptOutstanding->pfnDone.tGetElementByteSizeCnf(
          ptPacket->tHeader.ulState,
          ptOutstanding->pvDoneParam,
          ptPacket->tGetElementByteSizeCnf.tData.ulObjectId,
          ptPacket->tGetElementByteSizeCnf.tData.ulElementNo,
          ptPacket->tGetElementByteSizeCnf.tData.ulByteSize);
      }
      /* release the outstanding service entry */
      ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_AddObjectDescriptionCnf(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t                ulNpxResult   = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    ptOutstanding = NpxHost_GetOutstanding(ptInterface, ptPacket);
    if (ptOutstanding == NULL)
      ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    else
    { /* invoke the callback associated with the outstanding service entry */
      if (ptOutstanding->pfnDone.ulAddress != 0)
      {
        ptOutstanding->pfnDone.tAddObjectDescriptionCnf(
          ptPacket->tHeader.ulState,
          ptOutstanding->pvDoneParam,
          ptPacket->tAddObjectDescriptionCnf.tData.ulObjectId);
      }
      /* release the outstanding service entry */
      ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_DeleteObjectDescriptionCnf(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t                ulNpxResult   = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    ptOutstanding = NpxHost_GetOutstanding(ptInterface, ptPacket);
    if (ptOutstanding == NULL)
      ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    else
    { /* invoke the callback associated with the outstanding service entry */
      if (ptOutstanding->pfnDone.ulAddress != 0)
      {
        ptOutstanding->pfnDone.tDeleteObjectDescriptionCnf(
          ptPacket->tHeader.ulState,
          ptOutstanding->pvDoneParam,
          ptPacket->tDeleteObjectDescriptionCnf.tData.ulObjectId);
      }
      /* release the outstanding service entry */
      ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_GetObjectDescriptionCnf(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t                              ulNpxResult         = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T*               ptOutstanding       = NULL;
  NPX_HOST_OBJECT_DESCRIPTION_BUFFER_T* ptObjectDescription = NULL;
  uint32_t                              ulCount             = 0;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    ptOutstanding = NpxHost_GetOutstanding(ptInterface, ptPacket);
    if (ptOutstanding == NULL)
      ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    else
    {
      if (ptOutstanding->pfnDone.ulAddress != 0)
      { /* perform basic checks of the given packet data length, the object name offset, and the number of element descriptions vs. the packet length */
        if (ptPacket->tHeader.ulLen > CIFX_MAX_DATA_SIZE
        ||  ptPacket->tGetObjectDescriptionCnf.tData.ulObjectNameOffset != 0)
          ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
        else
        {
          ptObjectDescription = (NPX_HOST_OBJECT_DESCRIPTION_BUFFER_T*) &ptPacket->tGetObjectDescriptionCnf.tData;
          ptObjectDescription->patElementDescriptions = (NPX_HOST_ELEMENT_DESCRIPTION_T*) ptPacket->tGetObjectDescriptionCnf.tData.abData;
          ptObjectDescription->pszObjectName = (char*) (ptObjectDescription->patElementDescriptions + ptObjectDescription->ulNumberOfElements);
          for (ulCount = 0; ulCount < ptObjectDescription->ulNumberOfElements; ulCount++)
          { /* convert the relative offset to a string pointer by adding the base offset */
            ptObjectDescription->patElementDescriptions[ulCount].pszElementName += (uint32_t) ptObjectDescription->pszObjectName;
            /* check the element name offset against the given packet length */
            if (ptObjectDescription->patElementDescriptions[ulCount].pszElementName > (char*) &ptPacket->tGetObjectDescriptionCnf.tData + ptPacket->tHeader.ulLen)
            {
              ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
              break;
            }
          }
          if (ulNpxResult == SUCCESS_NET_PROXY_OK)
          { /* invoke the callback associated with the outstanding service entry */
            ptOutstanding->pfnDone.tGetObjectDescriptionCnf(
              ptPacket->tHeader.ulState,
              ptOutstanding->pvDoneParam,
              ptObjectDescription,
              ptPacket->tHeader.ulLen);
          }
        }
      }
      /* release the outstanding service entry */
      ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_AddVolatileObjectCnf(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t                ulNpxResult   = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    ptOutstanding = NpxHost_GetOutstanding(ptInterface, ptPacket);
    if (ptOutstanding == NULL)
      ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    else
    { /* invoke the callback associated with the outstanding service entry */
      if (ptOutstanding->pfnDone.ulAddress != 0)
      {
        ptOutstanding->pfnDone.tAddVolatileObjectCnf(
          ptPacket->tHeader.ulState,
          ptOutstanding->pvDoneParam,
          ptPacket->tAddVolatileObjectCnf.tData.ulGroupId,
          ptPacket->tAddVolatileObjectCnf.tData.ulObjectId,
          ptPacket->tAddVolatileObjectCnf.tData.ulNumberOfInstances);
      }
      /* release the outstanding service entry */
      ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_DeleteObjectCnf(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t                ulNpxResult   = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    ptOutstanding = NpxHost_GetOutstanding(ptInterface, ptPacket);
    if (ptOutstanding == NULL)
      ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    else
    { /* invoke the callback associated with the outstanding service entry */
      if (ptOutstanding->pfnDone.ulAddress != 0)
      {
        ptOutstanding->pfnDone.tDeleteObjectCnf(
          ptPacket->tHeader.ulState,
          ptOutstanding->pvDoneParam,
          ptPacket->tDeleteObjectCnf.tData.ulGroupId,
          ptPacket->tDeleteObjectCnf.tData.ulObjectId);
      }
      /* release the outstanding service entry */
      ptOutstanding->ulId = 0;
      /* release any remaining outstanding service entries for indications or update notifications associated with the deleted object */
      (void) NpxHost_ReleaseOutstandingIndications(ptInterface, ptPacket->tDeleteObjectCnf.tData.ulGroupId, ptPacket->tDeleteObjectCnf.tData.ulObjectId);
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_GetNumberOfInstancesCnf(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t                ulNpxResult   = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    ptOutstanding = NpxHost_GetOutstanding(ptInterface, ptPacket);
    if (ptOutstanding == NULL)
      ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    else
    { /* invoke the callback associated with the outstanding service entry */
      if (ptOutstanding->pfnDone.ulAddress != 0)
      {
        ptOutstanding->pfnDone.tGetNumberOfInstancesCnf(
          ptPacket->tHeader.ulState,
          ptOutstanding->pvDoneParam,
          ptPacket->tGetNumberOfInstancesCnf.tData.ulGroupId,
          ptPacket->tGetNumberOfInstancesCnf.tData.ulObjectId,
          ptPacket->tGetNumberOfInstancesCnf.tData.ulNumberOfInstances);
      }
      /* release the outstanding service entry */
      ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_RegisterUpdateNotificationCnf(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t                ulNpxResult   = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    ptOutstanding = NpxHost_GetOutstanding(ptInterface, ptPacket);
    if (ptOutstanding == NULL)
      ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    else
    { /* invoke the callback associated with the outstanding service entry */
      if (ptOutstanding->pfnDone.ulAddress != 0)
      {
        ptOutstanding->pfnDone.tRegisterUpdateNotificationCnf(
          ptPacket->tHeader.ulState,
          ptOutstanding->pvDoneParam,
          ptPacket->tRegisterUpdateNotificationCnf.tData.ulGroupId,
          ptPacket->tRegisterUpdateNotificationCnf.tData.ulObjectId,
          ptPacket->tRegisterUpdateNotificationCnf.tData.ulObjectInstance,
          ptPacket->tRegisterUpdateNotificationCnf.tData.ulElementNo);
      }
      /* do not release the outstanding service entry but re-use it for assigning update notification indications */
      ptOutstanding->ulCmd = NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND;
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_UnregisterUpdateNotificationCnf(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t                ulNpxResult      = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding    = NULL;
  NPX_HOST_OUTSTANDING_T* ptOutstandingInd = NULL;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    ptOutstanding = NpxHost_GetOutstanding(ptInterface, ptPacket);
    if (ptOutstanding == NULL)
      ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    else
    { /* release the entry associated with the associated indications */
      ptPacket->tHeader.ulDestId = ptPacket->tHeader.ulSrcId;
      ptPacket->tHeader.ulCmd    = NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND;
      ptOutstandingInd = NpxHost_GetOutstanding(ptInterface, ptPacket);
      if (ptOutstandingInd != NULL)
        ptOutstandingInd->ulId = 0;
      /* invoke the callback associated with the outstanding service entry */
      if (ptOutstanding->pfnDone.ulAddress != 0)
      {
        ptOutstanding->pfnDone.tUnregisterUpdateNotificationCnf(
          ptPacket->tHeader.ulState,
          ptOutstanding->pvDoneParam,
          ptPacket->tUnregisterUpdateNotificationCnf.tData.ulGroupId,
          ptPacket->tUnregisterUpdateNotificationCnf.tData.ulObjectId,
          ptPacket->tUnregisterUpdateNotificationCnf.tData.ulObjectInstance,
          ptPacket->tUnregisterUpdateNotificationCnf.tData.ulElementNo);
      }
      /* release the outstanding service entry */
      ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_UpdateNotificationInd(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t                ulNpxResult   = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    ptOutstanding = NpxHost_GetOutstanding(ptInterface, ptPacket);
    if (ptOutstanding == NULL)
      ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    else
    { /* invoke the indication callback associated with the outstanding service entry */
      if (ptOutstanding->pfnIndication.ulAddress != 0)
      {
        ptOutstanding->pfnIndication.tUpdateNotificationInd(
          ptOutstanding->pvIndicationParam,
          ptPacket->tUpdateNotificationInd.tData.ulGroupId,
          ptPacket->tUpdateNotificationInd.tData.ulObjectId,
          ptPacket->tUpdateNotificationInd.tData.ulObjectInstance,
          ptPacket->tUpdateNotificationInd.tData.ulElementNo,
          ptPacket->tUpdateNotificationInd.tData.abData);
      }
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_AddBehaviorObjectCnf(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t                ulNpxResult    = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding  = NULL;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    ptOutstanding = NpxHost_GetOutstanding(ptInterface, ptPacket);
    if (ptOutstanding == NULL)
      ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    else
    { /* invoke the callback associated with the outstanding service entry */
      if (ptOutstanding->pfnDone.ulAddress != 0)
      {
        ptOutstanding->pfnDone.tAddBehaviorObjectCnf(
          ptPacket->tHeader.ulState,
          ptOutstanding->pvDoneParam,
          ptPacket->tAddBehaviorObjectCnf.tData.ulGroupId,
          ptPacket->tAddBehaviorObjectCnf.tData.ulObjectId,
          ptPacket->tAddBehaviorObjectCnf.tData.ulNumberOfInstances);
      }
      /* do not release the outstanding service entry but re-use it for assigning indications */
      ptOutstanding->ulCmd = NPXPCK_HIF_READ_BEHAVIOR_OBJECT_IND;
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_BehaviorObjectReadInd(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t                ulNpxResult   = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;
  NPX_HOST_PACKET_T*      ptResponse    = NULL;
  uint32_t                ulDataLen     = 0;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    ptOutstanding = NpxHost_GetOutstanding(ptInterface, ptPacket);
    if (ptOutstanding == NULL)
      ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    else
    {
      (void) OS_WaitMutex(ptInterface->hMutex, 0xFFFFFFFF);
      if (FIFO_FULL(&ptInterface->tSendFifo))
        ulNpxResult = NPX_HOST_ERR_FIFO_FULL;
      else
      { /* get a buffer for the response */
        ptResponse = &FIFO_IN(&ptInterface->tSendFifo);
        OS_Memcpy(ptResponse, ptPacket, sizeof(NPXPCK_HIF_READ_BEHAVIOR_OBJECT_IND_T));
        ptResponse->tHeader.ulCmd  |= 1; /* indication --> response */
        ptResponse->tHeader.ulState = ulNpxResult;
        /* invoke the indication callback associated with the outstanding service entry */
        if (ptOutstanding->pfnIndication.ulAddress == 0)
          ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
        else
        { /* on callback invocation, ulDataLen holds the data buffer length; on callback exit, ulDataLen holds the read data length */
          ulDataLen = sizeof(ptResponse->tReadBehaviorObjectRes.tData.abData);
          ptOutstanding->pfnIndication.tBehaviorObjectReadInd(
            ptOutstanding->pvIndicationParam,
            ptPacket->tReadBehaviorObjectInd.tData.ulGroupId,
            ptPacket->tReadBehaviorObjectInd.tData.ulObjectId,
            ptPacket->tReadBehaviorObjectInd.tData.ulObjectInstance,
            ptPacket->tReadBehaviorObjectInd.tData.ulElementNo,
            ptResponse->tReadBehaviorObjectRes.tData.abData,
            &ulDataLen,
            &ulNpxResult);
        }
        ptResponse->tHeader.ulState = ulNpxResult;
        if (SUCCESS_NET_PROXY_OK == ulNpxResult)
          ptResponse->tHeader.ulLen = sizeof(ptResponse->tReadBehaviorObjectRes.tData) - sizeof(ptResponse->tReadBehaviorObjectRes.tData.abData) + ulDataLen;
        FIFO_PUT(&ptInterface->tSendFifo);
      }
      (void) OS_ReleaseMutex(ptInterface->hMutex);
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_BehaviorObjectWriteInd(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t                ulNpxResult   = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;
  NPX_HOST_PACKET_T*      ptResponse    = NULL;
  uint32_t                ulDataLen     = 0;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    ptOutstanding = NpxHost_GetOutstanding(ptInterface, ptPacket);
    if (ptOutstanding == NULL)
      ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    else
    {
      (void) OS_WaitMutex(ptInterface->hMutex, 0xFFFFFFFF);
      if (FIFO_FULL(&ptInterface->tSendFifo))
        ulNpxResult = NPX_HOST_ERR_FIFO_FULL;
      else
      { /* get a buffer for the response */
        ptResponse = &FIFO_IN(&ptInterface->tSendFifo);
        OS_Memcpy(ptResponse, ptPacket, sizeof(NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_RES_T));
        ptResponse->tHeader.ulCmd  |= 1; /* indication --> response */
        ptResponse->tHeader.ulState = ulNpxResult;
        ptResponse->tHeader.ulLen   = sizeof(ptResponse->tWriteBehaviorObjectRes.tData);
        /* invoke the indication callback associated with the outstanding service entry */
        if (ptOutstanding->pfnIndication2.ulAddress == 0)
          ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
        else
        { /* on callback invocation, ulDataLen holds the write data length */
          ulDataLen = ptPacket->tHeader.ulLen - (sizeof(ptPacket->tWriteBehaviorObjectInd.tData) - sizeof(ptPacket->tWriteBehaviorObjectInd.tData.abData));
          ptOutstanding->pfnIndication2.tBehaviorObjectWriteInd(
            ptOutstanding->pvIndicationParam,
            ptPacket->tWriteBehaviorObjectInd.tData.ulGroupId,
            ptPacket->tWriteBehaviorObjectInd.tData.ulObjectId,
            ptPacket->tWriteBehaviorObjectInd.tData.ulObjectInstance,
            ptPacket->tWriteBehaviorObjectInd.tData.ulElementNo,
            ptPacket->tWriteBehaviorObjectInd.tData.abData,
            ulDataLen,
            &ulNpxResult);
        }
        ptResponse->tHeader.ulState = ulNpxResult;
        FIFO_PUT(&ptInterface->tSendFifo);
      }
      (void) OS_ReleaseMutex(ptInterface->hMutex);
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_SetBehaviorObjectNumInstCnf(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t                ulNpxResult   = SUCCESS_NET_PROXY_OK;
  NPX_HOST_OUTSTANDING_T* ptOutstanding = NULL;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    ptOutstanding = NpxHost_GetOutstanding(ptInterface, ptPacket);
    if (ptOutstanding == NULL)
      ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    else
    { /* invoke the callback associated with the outstanding service entry */
      if (ptOutstanding->pfnDone.ulAddress != 0)
      {
        ptOutstanding->pfnDone.tSetBehaviorObjectNumInstCnf(
          ptPacket->tHeader.ulState,
          ptOutstanding->pvDoneParam,
          ptPacket->tSetBehaviorObjectNumInstCnf.tData.ulGroupId,
          ptPacket->tSetBehaviorObjectNumInstCnf.tData.ulObjectId,
          ptPacket->tSetBehaviorObjectNumInstCnf.tData.ulNumberOfInstances);
      }
      /* release the outstanding service entry */
      ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



/*************************************************************************************/
/* DPM Interface Handling                                                            */
/*************************************************************************************/


static uint32_t   NpxHost_PutDpmPacket(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket, uint32_t ulTimeout)
{
  uint32_t   ulNpxResult = SUCCESS_NET_PROXY_OK;
  int32_t    iCifxResult = CIFX_NO_ERROR;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
  else
  {
    iCifxResult = xChannelPutPacket(ptInterface->hChannel, &ptPacket->tCifxPacket, 0);

    if (iCifxResult != CIFX_NO_ERROR)
    { /* usually CIFX_DEV_MAILBOX_FULL: unable to put packet into mailbox within the given time */
      ulNpxResult = NPX_HOST_ERR_TIMEOUT;
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_GetDpmPacket(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket, uint32_t ulTimeout)
{
  uint32_t   ulNpxResult = SUCCESS_NET_PROXY_OK;
  int32_t    iCifxResult = CIFX_NO_ERROR;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
  else
  {
    iCifxResult = xChannelGetPacket(ptInterface->hChannel, sizeof(CIFX_PACKET), &ptPacket->tCifxPacket, 0);

    if (iCifxResult != CIFX_NO_ERROR)
    { /* usually CIFX_DEV_GET_NO_PACKET: no packet received from mailbox within the given timeout */
      ulNpxResult = NPX_HOST_ERR_TIMEOUT;
    }
  }
  return (ulNpxResult);
}



static uint32_t   NpxHost_TriggerCallback(NPX_HOST_INTERFACE_T* ptInterface, NPX_HOST_PACKET_T* ptPacket)
{
  uint32_t   ulNpxResult = SUCCESS_NET_PROXY_OK;

  if (ptInterface == NULL || ptPacket == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    switch (ptPacket->tHeader.ulCmd)
    {
      case NPXPCK_HIF_READ_OBJECT_ELEMENT_CNF:
        ulNpxResult = NpxHost_ReadObjectElementCnf(ptInterface, ptPacket);
        break;
      case NPXPCK_HIF_WRITE_OBJECT_ELEMENT_CNF:
        ulNpxResult = NpxHost_WriteObjectElementCnf(ptInterface, ptPacket);
        break;
      case NPXPCK_HIF_GET_ELEMENT_BYTESIZE_CNF:
        ulNpxResult = NpxHost_GetElementByteSizeCnf(ptInterface, ptPacket);
        break;
      case NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_CNF:
        ulNpxResult = NpxHost_AddObjectDescriptionCnf(ptInterface, ptPacket);
        break;
      case NPXPCK_HIF_GET_OBJECT_DESCRIPTION_CNF:
        ulNpxResult = NpxHost_GetObjectDescriptionCnf(ptInterface, ptPacket);
        break;
      case NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_CNF:
        ulNpxResult = NpxHost_DeleteObjectDescriptionCnf(ptInterface, ptPacket);
        break;
      case NPXPCK_HIF_ADD_VOLATILE_OBJECT_CNF:
        ulNpxResult = NpxHost_AddVolatileObjectCnf(ptInterface, ptPacket);
        break;
      case NPXPCK_HIF_DELETE_OBJECT_CNF:
        ulNpxResult = NpxHost_DeleteObjectCnf(ptInterface, ptPacket);
        break;
      case NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_CNF:
        ulNpxResult = NpxHost_GetNumberOfInstancesCnf(ptInterface, ptPacket);
        break;
      case NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_CNF:
        ulNpxResult = NpxHost_RegisterUpdateNotificationCnf(ptInterface, ptPacket);
        break;
      case NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_CNF:
        ulNpxResult = NpxHost_UnregisterUpdateNotificationCnf(ptInterface, ptPacket);
        break;
      case NPXPCK_HIF_OBJECT_UPDATE_NOTIFICATION_IND:
        ulNpxResult = NpxHost_UpdateNotificationInd(ptInterface, ptPacket);
        break;
      case NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_CNF:
        ulNpxResult = NpxHost_AddBehaviorObjectCnf(ptInterface, ptPacket);
        break;
      case NPXPCK_HIF_READ_BEHAVIOR_OBJECT_IND:
        ulNpxResult = NpxHost_BehaviorObjectReadInd(ptInterface, ptPacket);
        break;
      case NPXPCK_HIF_WRITE_BEHAVIOR_OBJECT_IND:
        ulNpxResult = NpxHost_BehaviorObjectWriteInd(ptInterface, ptPacket);
        break;
      case NPXPCK_HIF_SET_BEHAVIOR_OBJECT_NUM_INST_CNF:
        ulNpxResult = NpxHost_SetBehaviorObjectNumInstCnf(ptInterface, ptPacket);
        break;
      default:
        ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    }
  }
  return (ulNpxResult);
}



static void NpxHost_HandleInterface(NPX_HOST_INTERFACE_T* ptInterface)
{
  uint32_t           ulNpxResult  = SUCCESS_NET_PROXY_OK;
  NPX_HOST_FIFO_T*   ptFifo       = NULL;
  NPX_HOST_PACKET_T* ptSendPacket = NULL;
  NPX_HOST_PACKET_T  tRecvPacket;

  if (ptInterface != NULL && ptInterface->tSendFifo.patElements != NULL)
  {
    ptFifo = &ptInterface->tSendFifo;
    if (!FIFO_EMPTY(ptFifo))
    {
      ptSendPacket = &FIFO_OUT(ptFifo);
      ulNpxResult = NpxHost_PutDpmPacket(ptInterface, ptSendPacket, NPX_HOST_SEND_TIMEOUT);
      if (ulNpxResult != SUCCESS_NET_PROXY_OK)
        ptInterface->ulSendErrorCount++;
      else
      {
        FIFO_NEXT(ptFifo);
        ptInterface->ulSendPacketCount++;
      }
    }
    if (FIFO_EMPTY(ptFifo))
      ulNpxResult = NpxHost_GetDpmPacket(ptInterface, &tRecvPacket, NPX_HOST_RECV_TIMEOUT);
    else
      ulNpxResult = NpxHost_GetDpmPacket(ptInterface, &tRecvPacket, 0);
    if (ulNpxResult == SUCCESS_NET_PROXY_OK)
    {
      ptInterface->ulRecvPacketCount++;
      ulNpxResult = NpxHost_TriggerCallback(ptInterface, &tRecvPacket);
      if (ulNpxResult != SUCCESS_NET_PROXY_OK)
        ptInterface->ulRecvErrorCount++;
    }
  }
}




/*************************************************************************************/
/* Basic API Functions                                                               */
/*************************************************************************************/


uint32_t   APIENTRY NpxHost_Reset(void)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NULL;
  uint32_t              ulCount     = 0;

  s_tNpxHostApi.eState = NPX_HOST_DRIVER_STATE_SHUTDOWN;
  if (s_tNpxHostApi.patInterfaces != NULL)
  {
    for (ulCount = 0; ulCount < s_tNpxHostApi.tConfig.ulMaxInterfaces; ulCount++)
    {
      ptInterface = &s_tNpxHostApi.patInterfaces[ulCount];
      (void) NpxHost_ResetInterface(ptInterface);
      if (ptInterface->tSendFifo.patElements != NULL)
        OS_Memfree(ptInterface->tSendFifo.patElements);
      OS_Memset(&ptInterface->tSendFifo, 0, sizeof(ptInterface->tSendFifo));
      if (ptInterface->patOutstanding == NULL)
      {
        OS_Memfree(ptInterface->patOutstanding);
        ptInterface->patOutstanding = NULL;
      }
    }
    OS_Memfree(s_tNpxHostApi.patInterfaces);
    s_tNpxHostApi.patInterfaces = NULL;
  }
  if (s_tNpxHostApi.hDriver != NULL)
  {
    (void) xDriverClose(s_tNpxHostApi.hDriver);
    s_tNpxHostApi.hDriver = NULL;
  }
  if (s_tNpxHostApi.hMutex != NULL)
  {
    OS_DeleteMutex(s_tNpxHostApi.hMutex);
    s_tNpxHostApi.hMutex = NULL;
  }
  s_tNpxHostApi.eState = NPX_HOST_DRIVER_STATE_TERMINATED;
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_Init(const NPX_HOST_CONFIG_T* ptConfig)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NULL;
  uint32_t              ulCount     = 0;

  if (ptConfig == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    if (ptConfig->ulParamVersion  != NPX_HOST_CONFIG_VERSION_V2
    ||  ptConfig->ulMaxInterfaces  < NPX_HOST_NUM_INTERFACES_MIN
    ||  ptConfig->ulMaxInterfaces  > NPX_HOST_NUM_INTERFACES_MAX
    ||  ptConfig->ulFifoLength     < NPX_HOST_FIFO_LENGTH_MIN
    ||  ptConfig->ulFifoLength     > NPX_HOST_FIFO_LENGTH_MAX)
      ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
    else
    {
      (void) NpxHost_Reset();
      OS_Memset(&s_tNpxHostApi, 0, sizeof(s_tNpxHostApi));
      s_tNpxHostApi.eState = NPX_HOST_DRIVER_STATE_INIT;
      OS_Memcpy((void*)&s_tNpxHostApi.tConfig, (void*)ptConfig, sizeof(*ptConfig));
      s_tNpxHostApi.hMutex = OS_CreateMutex();
      if (s_tNpxHostApi.hMutex == NULL)
        ulNpxResult = ERR_NET_PROXY_RESOURCE_CREATE_FAILED;
      else
      {
        s_tNpxHostApi.patInterfaces = OS_Memalloc(s_tNpxHostApi.tConfig.ulMaxInterfaces * sizeof(*s_tNpxHostApi.patInterfaces));
        if (s_tNpxHostApi.patInterfaces == NULL)
          ulNpxResult = ERR_NET_PROXY_OUT_OF_MEMORY;
        else
        {
          OS_Memset(s_tNpxHostApi.patInterfaces, 0, s_tNpxHostApi.tConfig.ulMaxInterfaces * sizeof(*s_tNpxHostApi.patInterfaces));
          for (ulCount = 0; ulCount < s_tNpxHostApi.tConfig.ulMaxInterfaces; ulCount++)
          {
            ptInterface = &s_tNpxHostApi.patInterfaces[ulCount];
            ptInterface->tSendFifo.uSize = s_tNpxHostApi.tConfig.ulFifoLength;
            ptInterface->tSendFifo.uPutIndex = ptInterface->tSendFifo.uGetIndex = 0;
            ptInterface->tSendFifo.patElements = OS_Memalloc(s_tNpxHostApi.tConfig.ulFifoLength * sizeof(NPX_HOST_PACKET_T));
            if (ptInterface->tSendFifo.patElements == NULL)
            {
              ulNpxResult = ERR_NET_PROXY_OUT_OF_MEMORY;
              ptInterface->tSendFifo.uSize = 0;
              break;
            }
            OS_Memset(ptInterface->tSendFifo.patElements, 0, s_tNpxHostApi.tConfig.ulFifoLength * sizeof(NPX_HOST_PACKET_T));
            ptInterface->patOutstanding = OS_Memalloc(s_tNpxHostApi.tConfig.ulMaxOutstanding * sizeof(NPX_HOST_OUTSTANDING_T));
            if (ptInterface->patOutstanding == NULL)
            {
              ulNpxResult = ERR_NET_PROXY_OUT_OF_MEMORY;
              break;
            }
            OS_Memset(ptInterface->patOutstanding, 0, s_tNpxHostApi.tConfig.ulMaxOutstanding * sizeof(NPX_HOST_OUTSTANDING_T));
          }
        }
      }
      if (ulNpxResult != SUCCESS_NET_PROXY_OK)
        (void) NpxHost_Reset();
      else
        s_tNpxHostApi.eState = NPX_HOST_DRIVER_STATE_READY;
    }
  }
  return (ulNpxResult);
}



void APIENTRY NpxHost_Cyclic(void)
{
  NPX_HOST_INTERFACE_T* ptInterface = NULL;
  uint32_t              ulCount     = 0;

  if (s_tNpxHostApi.eState == NPX_HOST_DRIVER_STATE_RUN
  &&  s_tNpxHostApi.patInterfaces != NULL)
  {
    for (ulCount = 0; ulCount < s_tNpxHostApi.tConfig.ulMaxInterfaces; ulCount++)
    {
      ptInterface = &s_tNpxHostApi.patInterfaces[ulCount];
      NpxHost_HandleInterface(ptInterface);
    }
  }
}



uint32_t   APIENTRY NpxHost_Open(NPX_HOST_DRIVER_H* phNpx)
{
  uint32_t   ulNpxResult = SUCCESS_NET_PROXY_OK;
  int32_t    iCifxResult = CIFX_NO_ERROR;

  if (phNpx == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    *phNpx = NULL;
    if (s_tNpxHostApi.eState < NPX_HOST_DRIVER_STATE_READY
    ||  s_tNpxHostApi.eState > NPX_HOST_DRIVER_STATE_RUN
    ||  s_tNpxHostApi.hMutex == NULL)
      ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
    else
    {
      (void) OS_WaitMutex(s_tNpxHostApi.hMutex, 0xFFFFFFFF);
      if (s_tNpxHostApi.hDriver == NULL)
      {
        iCifxResult = xDriverOpen(&s_tNpxHostApi.hDriver);
        if (iCifxResult != CIFX_NO_ERROR)
          ulNpxResult = ERR_NET_PROXY_INITIALIZE_FAILED;
        else
        {
          s_tNpxHostApi.ulRefCount = 1;
          *phNpx = (NPX_HOST_DRIVER_H) &s_tNpxHostApi;
          s_tNpxHostApi.eState = NPX_HOST_DRIVER_STATE_RUN;
        }
      }
      else
      {
        s_tNpxHostApi.ulRefCount++;
        *phNpx = (NPX_HOST_DRIVER_H) &s_tNpxHostApi;
      }
      (void) OS_ReleaseMutex(s_tNpxHostApi.hMutex);
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_Close(NPX_HOST_DRIVER_H hNpx)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NULL;
  uint32_t              ulCount     = 0;

  if (hNpx != &s_tNpxHostApi)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    if (s_tNpxHostApi.eState < NPX_HOST_DRIVER_STATE_READY
    ||  s_tNpxHostApi.eState > NPX_HOST_DRIVER_STATE_RUN
    ||  s_tNpxHostApi.hMutex == NULL)
      ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
    else
    {
      (void) OS_WaitMutex(s_tNpxHostApi.hMutex, 0xFFFFFFFF);
      if (s_tNpxHostApi.hDriver != NULL && s_tNpxHostApi.ulRefCount > 0)
      {
        if (--s_tNpxHostApi.ulRefCount == 0)
        {
          s_tNpxHostApi.eState = NPX_HOST_DRIVER_STATE_SHUTDOWN;
          if (s_tNpxHostApi.patInterfaces != NULL)
          {
            for (ulCount = 0; ulCount < s_tNpxHostApi.tConfig.ulMaxInterfaces; ulCount++)
            {
              ptInterface = &s_tNpxHostApi.patInterfaces[ulCount];
              (void) NpxHost_ResetInterface(ptInterface);
            }
          }
          (void) xDriverClose(s_tNpxHostApi.hDriver);
          s_tNpxHostApi.hDriver = NULL;
          s_tNpxHostApi.eState = NPX_HOST_DRIVER_STATE_READY;
        }
      }
      (void) OS_ReleaseMutex(s_tNpxHostApi.hMutex);
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_EnumInterfaces(NPX_HOST_DRIVER_H hNpx,
                                           uint32_t          ulInterfaceIndex,
                                           char*             pszInterfaceNameBuffer,
                                           uint32_t*         pulBufferLen)
{
  uint32_t            ulNpxResult     = SUCCESS_NET_PROXY_OK;
  int32_t             iCifxResult     = CIFX_NO_ERROR;
  uint32_t            ulBoard         = 0;
  uint32_t            ulChannel       = 0;
  uint32_t            ulCount         = 0;
  CHANNEL_INFORMATION tChannelInfo    = {{0}};

  if (hNpx != &s_tNpxHostApi)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    if (pszInterfaceNameBuffer == NULL || pulBufferLen == NULL)
      ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
    else
    {
      *pszInterfaceNameBuffer = '\0';
      if (*pulBufferLen < sizeof("Board0/Channel0"))
        ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
      else
      {
        if (s_tNpxHostApi.eState < NPX_HOST_DRIVER_STATE_READY
        ||  s_tNpxHostApi.eState > NPX_HOST_DRIVER_STATE_RUN
        ||  s_tNpxHostApi.hMutex == NULL)
          ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
        else
        {
          if (s_tNpxHostApi.hDriver == NULL
          ||  s_tNpxHostApi.patInterfaces == NULL)
            ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
          else
          {
            if (ulInterfaceIndex >= s_tNpxHostApi.tConfig.ulMaxInterfaces)
              ulNpxResult = ERR_NET_PROXY_INTERFACE_DOES_NOT_EXIST;
            else
            {
              for (ulCount = 0; ulCount <= ulInterfaceIndex; ulCount++)
              {
                iCifxResult = xDriverEnumChannels(s_tNpxHostApi.hDriver, ulBoard, ulChannel, sizeof(tChannelInfo), &tChannelInfo);
                if (iCifxResult == CIFX_INVALID_BOARD)
                { /* no more boards to scan */
                  ulNpxResult = ERR_NET_PROXY_INTERFACE_DOES_NOT_EXIST;
                  break;
                }
                if (iCifxResult == CIFX_NO_MORE_ENTRIES)
                { /* no more channels on this board: continue with the next board */
                  ulBoard++;
                  ulChannel = 0;
                  continue;
                }
                if (iCifxResult != CIFX_NO_ERROR)
                { /* enumeration error */
                  ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
                  break;
                }
                /* continue with the next channel */
                ulChannel++;
              }
              if (ulNpxResult == SUCCESS_NET_PROXY_OK)
              {
                OS_Memcpy(pszInterfaceNameBuffer, "Board0/Channel0", sizeof("Board0/Channel0"));
                pszInterfaceNameBuffer[5]  = (char) (ulBoard + '0');
                pszInterfaceNameBuffer[14] = (char) (ulChannel + '0');
                *pulBufferLen = sizeof("Board0/Channel0");
              }
            }
          }
        }
        if (ulNpxResult != SUCCESS_NET_PROXY_OK)
          *pulBufferLen = 0;
      }
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_OpenInterface(NPX_HOST_DRIVER_H hNpx,
                                          const char*       pszInterfaceName,
                                          NPX_HOST_IF_H*    phInterface)
{
  uint32_t                ulNpxResult     = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T*   ptInterface     = NULL;
  int32_t                 iCifxResult     = CIFX_NO_ERROR;
  uint32_t                ulBoard         = 0;
  uint32_t                ulChannel       = 0;
  uint32_t                ulCount         = 0;
  uint32_t                ulIndex         = 0;
  const char*             pcBoard         = NULL;
  const char*             pcChannel       = NULL;
  char                    szBoardName[7]  = "Board0";
  NPX_HOST_OUTSTANDING_T* ptOutstanding   = NULL;

  if (hNpx != &s_tNpxHostApi)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    if (phInterface == NULL)
      ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
    else
    {
      *phInterface = NULL;
      if (s_tNpxHostApi.eState < NPX_HOST_DRIVER_STATE_READY
      ||  s_tNpxHostApi.eState > NPX_HOST_DRIVER_STATE_RUN
      ||  s_tNpxHostApi.hMutex == NULL)
        ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
      else
      {
        (void) OS_WaitMutex(s_tNpxHostApi.hMutex, 0xFFFFFFFF);
        if (s_tNpxHostApi.hDriver == NULL
        ||  s_tNpxHostApi.patInterfaces == NULL)
          ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
        else
        {
          if (pszInterfaceName == NULL || *pszInterfaceName == '\0')
            pszInterfaceName = NPX_HOST_INTERFACE_NAME_DEFAULT;
          pcBoard = strstr(pszInterfaceName, "Board");
          if (pcBoard != NULL)
            pcBoard += sizeof("Board") - 1;
          pcChannel = strstr(pszInterfaceName, "/Channel");
          if (pcChannel != NULL)
            pcChannel += sizeof("/Channel") - 1;
          if (pcBoard == NULL || pcChannel == NULL || *pcBoard < '0' || *pcBoard > '9' || *pcChannel < '0' || *pcChannel > '9')
            ulNpxResult = ERR_NET_PROXY_INTERFACE_DOES_NOT_EXIST;
          else
          {
            ulBoard = *pcBoard - '0';
            ulChannel = *pcChannel - '0';
            szBoardName[sizeof(szBoardName) - 2] = *pcBoard;
            for (ulCount = 0; ulCount < s_tNpxHostApi.tConfig.ulMaxInterfaces; ulCount++)
            {
              ptInterface = &s_tNpxHostApi.patInterfaces[ulCount];
              if (ptInterface->hChannel  != NULL
              &&  ptInterface->ulBoard   == ulBoard
              &&  ptInterface->ulChannel == ulChannel)
              { /* the specified interface is already open */
                ptInterface->ulRefCount++;
                *phInterface = (NPX_HOST_IF_H) ptInterface;
                break;
              }
            }
            if (*phInterface == NULL)
            { /* the specified interface has not been opened before */
              for (ulCount = 0; ulCount < s_tNpxHostApi.tConfig.ulMaxInterfaces; ulCount++)
              {
                ptInterface = &s_tNpxHostApi.patInterfaces[ulCount];
                if (ptInterface->hChannel == NULL)
                { /* this is an unused interface entry: initialize it */
                  iCifxResult = xChannelOpen(s_tNpxHostApi.hDriver, szBoardName, ulChannel, &ptInterface->hChannel);
                  if (iCifxResult != CIFX_NO_ERROR || ptInterface->hChannel == NULL)
                    ulNpxResult = ERR_NET_PROXY_INTERFACE_DOES_NOT_EXIST;
                  else
                  { /* create the interface's outstanding service confirmation events for use with the synchronous API calls */
                    for (ulIndex = 0; ulIndex < s_tNpxHostApi.tConfig.ulMaxOutstanding; ulIndex++)
                    {
                      ptOutstanding = &ptInterface->patOutstanding[ulIndex];
                      ptOutstanding->hEvent = OS_CreateEvent();
                      if (ptOutstanding->hEvent == NULL)
                      {
                        ulNpxResult = ERR_NET_PROXY_RESOURCE_CREATE_FAILED;
                        break;
                      }
                    }
                    if (ulNpxResult == SUCCESS_NET_PROXY_OK)
                    {
                      ptInterface->eState     = NPX_HOST_INTERFACE_STATE_READY;
                      ptInterface->ulRefCount = 1;
                      ptInterface->hMutex     = s_tNpxHostApi.hMutex; /* this is a borrowed handle */
                      ptInterface->ulBoard    = ulBoard;
                      ptInterface->ulChannel  = ulChannel;
                      ptInterface->tSendFifo.uPutIndex = ptInterface->tSendFifo.uGetIndex = 0;
                      ptInterface->eState = NPX_HOST_INTERFACE_STATE_RUN;
                    }
                  }
                  if (ulNpxResult != SUCCESS_NET_PROXY_OK)
                    (void) NpxHost_ResetInterface(ptInterface);
                  else
                    *phInterface = (NPX_HOST_IF_H) ptInterface;
                  break;
                }
              }
            }
          }
        }
        (void) OS_ReleaseMutex(s_tNpxHostApi.hMutex);
      }
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_CloseInterface(NPX_HOST_IF_H hInterface)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NULL;

  if (s_tNpxHostApi.hMutex == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
  else
  {
    (void) OS_WaitMutex(s_tNpxHostApi.hMutex, 0xFFFFFFFF);
    if (s_tNpxHostApi.patInterfaces == NULL)
      ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
    else
    {
      ptInterface = NpxHost_GetInterface(hInterface);
      if (ptInterface == NULL)
        ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
      else
      {
        if (--ptInterface->ulRefCount == 0)
        {
          ulNpxResult = NpxHost_ResetInterface(ptInterface);
        }
      }
    }
    (void) OS_ReleaseMutex(s_tNpxHostApi.hMutex);
  }
  return (ulNpxResult);
}



/*************************************************************************************/
/* Asynchronous API Functions                                                        */
/*************************************************************************************/


uint32_t   APIENTRY NpxHost_ReadObjectElementAsync(
  NPX_HOST_IF_H                      hInterface,
  uint32_t                           ulGroupId,
  uint32_t                           ulObjectId,
  uint32_t                           ulObjectInstance,
  uint32_t                           ulElementNumber,
  NPX_HOST_READ_OBJECT_ELEMENT_CBK_T pfnDone,
  void*                              pvDoneParam)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NpxHost_GetInterface(hInterface);
  NPX_HOST_PACKET_T*    ptPacket    = NULL;

  if (ptInterface == NULL || ptInterface->hMutex == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    (void) OS_WaitMutex(ptInterface->hMutex, 0xFFFFFFFF);
    if (FIFO_FULL(&ptInterface->tSendFifo))
      ulNpxResult = NPX_HOST_ERR_FIFO_FULL;
    else
    {
      ptPacket = &FIFO_IN(&ptInterface->tSendFifo);
      NpxHost_InitPacketHeader(ptPacket);
      ptPacket->tHeader.ulLen = sizeof(NPXPCK_HIF_READ_OBJECT_ELEMENT_REQ_DATA_T);
      ptPacket->tHeader.ulCmd = NPXPCK_HIF_READ_OBJECT_ELEMENT_REQ;
      ptPacket->tReadObjectElementReq.tData.ulGroupId        = ulGroupId;
      ptPacket->tReadObjectElementReq.tData.ulObjectId       = ulObjectId;
      ptPacket->tReadObjectElementReq.tData.ulObjectInstance = ulObjectInstance;
      ptPacket->tReadObjectElementReq.tData.ulElementNo      = ulElementNumber;
      ulNpxResult = NpxHost_SetOutstanding(ptInterface, ptPacket, (uint32_t) pfnDone, pvDoneParam, 0, 0, NULL);
      if (ulNpxResult == SUCCESS_NET_PROXY_OK)
      {
        FIFO_PUT(&ptInterface->tSendFifo);
      }
    }
    (void) OS_ReleaseMutex(ptInterface->hMutex);
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_WriteObjectElementAsync(
  NPX_HOST_IF_H                       hInterface,
  uint32_t                            ulGroupId,
  uint32_t                            ulObjectId,
  uint32_t                            ulObjectInstance,
  uint32_t                            ulElementNumber,
  const void*                         pvBuffer,
  uint32_t                            ulDataLen,
  NPX_HOST_WRITE_OBJECT_ELEMENT_CBK_T pfnDone,
  void*                               pvDoneParam)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NpxHost_GetInterface(hInterface);
  NPX_HOST_PACKET_T*    ptPacket    = NULL;

  if (ptInterface == NULL || ptInterface->hMutex == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    if (pvBuffer == NULL || ulDataLen == 0 || ulDataLen > sizeof(ptPacket->tWriteObjectElementReq.tData.abData))
      ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
    else
    {
      (void) OS_WaitMutex(ptInterface->hMutex, 0xFFFFFFFF);
      if (FIFO_FULL(&ptInterface->tSendFifo))
        ulNpxResult = NPX_HOST_ERR_FIFO_FULL;
      else
      {
        ptPacket = &FIFO_IN(&ptInterface->tSendFifo);
        NpxHost_InitPacketHeader(ptPacket);
        ptPacket->tHeader.ulLen = sizeof(NPXPCK_HIF_WRITE_OBJECT_ELEMENT_REQ_DATA_T) - sizeof(ptPacket->tWriteObjectElementReq.tData.abData) + ulDataLen;
        ptPacket->tHeader.ulCmd = NPXPCK_HIF_WRITE_OBJECT_ELEMENT_REQ;
        ptPacket->tWriteObjectElementReq.tData.ulGroupId        = ulGroupId;
        ptPacket->tWriteObjectElementReq.tData.ulObjectId       = ulObjectId;
        ptPacket->tWriteObjectElementReq.tData.ulObjectInstance = ulObjectInstance;
        ptPacket->tWriteObjectElementReq.tData.ulElementNo      = ulElementNumber;
        OS_Memcpy(ptPacket->tWriteObjectElementReq.tData.abData, (void*) pvBuffer, ulDataLen);
        ulNpxResult = NpxHost_SetOutstanding(ptInterface, ptPacket, (uint32_t) pfnDone, pvDoneParam, 0, 0, NULL);
        if (ulNpxResult == SUCCESS_NET_PROXY_OK)
        {
          FIFO_PUT(&ptInterface->tSendFifo);
        }
      }
      (void) OS_ReleaseMutex(ptInterface->hMutex);
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_GetElementByteSizeAsync(
  NPX_HOST_IF_H                       hInterface,
  uint32_t                            ulObjectId,
  uint32_t                            ulElementNumber,
  NPX_HOST_GET_ELEMENT_BYTESIZE_CBK_T pfnDone,
  void*                               pvDoneParam)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NpxHost_GetInterface(hInterface);
  NPX_HOST_PACKET_T*    ptPacket    = NULL;

  if (ptInterface == NULL || ptInterface->hMutex == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    (void) OS_WaitMutex(ptInterface->hMutex, 0xFFFFFFFF);
    if (FIFO_FULL(&ptInterface->tSendFifo))
      ulNpxResult = NPX_HOST_ERR_FIFO_FULL;
    else
    {
      ptPacket = &FIFO_IN(&ptInterface->tSendFifo);
      NpxHost_InitPacketHeader(ptPacket);
      ptPacket->tHeader.ulLen = sizeof(NPXPCK_HIF_GET_ELEMENT_BYTESIZE_REQ_DATA_T);
      ptPacket->tHeader.ulCmd = NPXPCK_HIF_GET_ELEMENT_BYTESIZE_REQ;
      ptPacket->tGetElementByteSizeReq.tData.ulObjectId  = ulObjectId;
      ptPacket->tGetElementByteSizeReq.tData.ulElementNo = ulElementNumber;
      ulNpxResult = NpxHost_SetOutstanding(ptInterface, ptPacket, (uint32_t) pfnDone, pvDoneParam, 0, 0, NULL);
      if (ulNpxResult == SUCCESS_NET_PROXY_OK)
      {
        FIFO_PUT(&ptInterface->tSendFifo);
      }
    }
    (void) OS_ReleaseMutex(ptInterface->hMutex);
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_AddObjectDescriptionAsync(
  NPX_HOST_IF_H                         hInterface,
  const NPX_HOST_OBJECT_DESCRIPTION_T*  ptObjectDescription,
  NPX_HOST_ADD_OBJECT_DESCRIPTION_CBK_T pfnDone,
  void*                                 pvDoneParam)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NpxHost_GetInterface(hInterface);
  NPX_HOST_PACKET_T*    ptPacket    = NULL;

  if (ptInterface == NULL || ptInterface->hMutex == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    if (ptObjectDescription == NULL
    ||  ptObjectDescription->pszObjectName == NULL
    ||  ptObjectDescription->pszObjectName[0] == '\0'
    ||  ptObjectDescription->ulNumberOfElements == 0
    ||  ptObjectDescription->patElementDescriptions == NULL)
      ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
    else
    {
      (void) OS_WaitMutex(ptInterface->hMutex, 0xFFFFFFFF);
      if (FIFO_FULL(&ptInterface->tSendFifo))
        ulNpxResult = NPX_HOST_ERR_FIFO_FULL;
      else
      {
        ptPacket = &FIFO_IN(&ptInterface->tSendFifo);
        NpxHost_InitPacketHeader(ptPacket);
        ptPacket->tHeader.ulLen = sizeof(NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_REQ_DATA_T) - sizeof(ptPacket->tAddObjectDescriptionReq.tData.abData) + ptObjectDescription->ulNumberOfElements * sizeof(NPXPCK_HIF_ELEMENT_DESCRIPTION_T);
        ptPacket->tHeader.ulCmd = NPXPCK_HIF_ADD_OBJECT_DESCRIPTION_REQ;
        ptPacket->tAddObjectDescriptionReq.tData.ulObjectId         = ptObjectDescription->ulObjectId;
        ptPacket->tAddObjectDescriptionReq.tData.ulObjectNameOffset = 0;
        ptPacket->tAddObjectDescriptionReq.tData.ulNumberOfElements = ptObjectDescription->ulNumberOfElements;
        ptPacket->tAddObjectDescriptionReq.tData.ulReserved         = 0;
        if (ptPacket->tHeader.ulLen > sizeof(ptPacket->tAddObjectDescriptionReq.tData))
          ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
        else
        {
          char*    pszName      = (char*) &ptPacket->tAddObjectDescriptionReq.tData + ptPacket->tHeader.ulLen;
          uint32_t ulNameOffset = 0;
          uint32_t ulNameLength = OS_Strlen(ptObjectDescription->pszObjectName) + 1;

          ptPacket->tHeader.ulLen += ulNameLength;
          if (ptPacket->tHeader.ulLen > sizeof(ptPacket->tAddObjectDescriptionReq.tData))
            ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
          else
          {
            NPX_HOST_ELEMENT_DESCRIPTION_T*   ptElementDescription    = ptObjectDescription->patElementDescriptions;
            NPXPCK_HIF_ELEMENT_DESCRIPTION_T* ptHifElementDescription = (NPXPCK_HIF_ELEMENT_DESCRIPTION_T*) ptPacket->tAddObjectDescriptionReq.tData.abData;
            uint32_t                          ulCount;

            strcpy(pszName, ptObjectDescription->pszObjectName);
            for (ulCount = 0; ulCount < ptObjectDescription->ulNumberOfElements; ulCount++)
            {
              pszName       = (char*) &ptPacket->tAddObjectDescriptionReq.tData + ptPacket->tHeader.ulLen;
              ulNameOffset += ulNameLength;
              ulNameLength  = OS_Strlen(ptElementDescription->pszElementName) + 1;
              ptHifElementDescription->ulElementNameOffset = ulNameOffset;
              ptHifElementDescription->ulReserved          = 0;
              ptHifElementDescription->usElementType       = ptElementDescription->usElementType;
              ptHifElementDescription->usElementByteSize   = ptElementDescription->usElementByteSize;
              ptPacket->tHeader.ulLen += ulNameLength;
              if (ptPacket->tHeader.ulLen + ulNameLength > sizeof(ptPacket->tAddObjectDescriptionReq.tData))
              {
                ulNpxResult = ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER;
                break;
              }
              strcpy(pszName, ptElementDescription->pszElementName);
              ptElementDescription++;
              ptHifElementDescription++;
            }
            if (ulNpxResult == SUCCESS_NET_PROXY_OK)
            {
              ulNpxResult = NpxHost_SetOutstanding(ptInterface, ptPacket, (uint32_t) pfnDone, pvDoneParam, 0, 0, NULL);
              if (ulNpxResult == SUCCESS_NET_PROXY_OK)
              {
                FIFO_PUT(&ptInterface->tSendFifo);
              }
            }
          }
        }
      }
      (void) OS_ReleaseMutex(ptInterface->hMutex);
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_DeleteObjectDescriptionAsync(
  NPX_HOST_IF_H                            hInterface,
  uint32_t                                 ulObjectId,
  NPX_HOST_DELETE_OBJECT_DESCRIPTION_CBK_T pfnDone,
  void*                                    pvDoneParam)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NpxHost_GetInterface(hInterface);
  NPX_HOST_PACKET_T*    ptPacket    = NULL;

  if (ptInterface == NULL || ptInterface->hMutex == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    (void) OS_WaitMutex(ptInterface->hMutex, 0xFFFFFFFF);
    if (FIFO_FULL(&ptInterface->tSendFifo))
      ulNpxResult = NPX_HOST_ERR_FIFO_FULL;
    else
    {
      ptPacket = &FIFO_IN(&ptInterface->tSendFifo);
      NpxHost_InitPacketHeader(ptPacket);
      ptPacket->tHeader.ulLen = sizeof(NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_REQ_DATA_T);
      ptPacket->tHeader.ulCmd = NPXPCK_HIF_DELETE_OBJECT_DESCRIPTION_REQ;
      ptPacket->tDeleteObjectDescriptionReq.tData.ulObjectId = ulObjectId;
      ulNpxResult = NpxHost_SetOutstanding(ptInterface, ptPacket, (uint32_t) pfnDone, pvDoneParam, 0, 0, NULL);
      if (ulNpxResult == SUCCESS_NET_PROXY_OK)
      {
        FIFO_PUT(&ptInterface->tSendFifo);
      }
    }
    (void) OS_ReleaseMutex(ptInterface->hMutex);
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_GetObjectDescriptionAsync(
  NPX_HOST_IF_H                         hInterface,
  uint32_t                              ulObjectId,
  NPX_HOST_GET_OBJECT_DESCRIPTION_CBK_T pfnDone,
  void*                                 pvDoneParam)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NpxHost_GetInterface(hInterface);
  NPX_HOST_PACKET_T*    ptPacket    = NULL;

  if (ptInterface == NULL || ptInterface->hMutex == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    (void) OS_WaitMutex(ptInterface->hMutex, 0xFFFFFFFF);
    if (FIFO_FULL(&ptInterface->tSendFifo))
      ulNpxResult = NPX_HOST_ERR_FIFO_FULL;
    else
    {
      ptPacket = &FIFO_IN(&ptInterface->tSendFifo);
      NpxHost_InitPacketHeader(ptPacket);
      ptPacket->tHeader.ulLen = sizeof(NPXPCK_HIF_GET_OBJECT_DESCRIPTION_REQ_DATA_T);
      ptPacket->tHeader.ulCmd = NPXPCK_HIF_GET_OBJECT_DESCRIPTION_REQ;
      ptPacket->tGetObjectDescriptionReq.tData.ulObjectId = ulObjectId;
      ulNpxResult = NpxHost_SetOutstanding(ptInterface, ptPacket, (uint32_t) pfnDone, pvDoneParam, 0, 0, NULL);
      if (ulNpxResult == SUCCESS_NET_PROXY_OK)
      {
        FIFO_PUT(&ptInterface->tSendFifo);
      }
    }
    (void) OS_ReleaseMutex(ptInterface->hMutex);
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_AddVolatileObjectAsync(
  NPX_HOST_IF_H                      hInterface,
  uint32_t                           ulGroupId,
  uint32_t                           ulObjectId,
  uint32_t                           ulNumberOfInstances,
  NPX_HOST_ADD_VOLATILE_OBJECT_CBK_T pfnDone,
  void*                              pvDoneParam)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NpxHost_GetInterface(hInterface);
  NPX_HOST_PACKET_T*    ptPacket    = NULL;

  if (ptInterface == NULL || ptInterface->hMutex == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    (void) OS_WaitMutex(ptInterface->hMutex, 0xFFFFFFFF);
    if (FIFO_FULL(&ptInterface->tSendFifo))
      ulNpxResult = NPX_HOST_ERR_FIFO_FULL;
    else
    {
      ptPacket = &FIFO_IN(&ptInterface->tSendFifo);
      NpxHost_InitPacketHeader(ptPacket);
      ptPacket->tHeader.ulLen = sizeof(NPXPCK_HIF_ADD_VOLATILE_OBJECT_REQ_DATA_T);
      ptPacket->tHeader.ulCmd = NPXPCK_HIF_ADD_VOLATILE_OBJECT_REQ;
      ptPacket->tAddVolatileObjectReq.tData.ulGroupId           = ulGroupId;
      ptPacket->tAddVolatileObjectReq.tData.ulObjectId          = ulObjectId;
      ptPacket->tAddVolatileObjectReq.tData.ulNumberOfInstances = ulNumberOfInstances;
      ulNpxResult = NpxHost_SetOutstanding(ptInterface, ptPacket, (uint32_t) pfnDone, pvDoneParam, 0, 0, NULL);
      if (ulNpxResult == SUCCESS_NET_PROXY_OK)
      {
        FIFO_PUT(&ptInterface->tSendFifo);
      }
    }
    (void) OS_ReleaseMutex(ptInterface->hMutex);
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_DeleteObjectAsync(
  NPX_HOST_IF_H                hInterface,
  uint32_t                     ulGroupId,
  uint32_t                     ulObjectId,
  NPX_HOST_DELETE_OBJECT_CBK_T pfnDone,
  void*                        pvDoneParam)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NpxHost_GetInterface(hInterface);
  NPX_HOST_PACKET_T*    ptPacket    = NULL;

  if (ptInterface == NULL || ptInterface->hMutex == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    (void) OS_WaitMutex(ptInterface->hMutex, 0xFFFFFFFF);
    if (FIFO_FULL(&ptInterface->tSendFifo))
      ulNpxResult = NPX_HOST_ERR_FIFO_FULL;
    else
    {
      ptPacket = &FIFO_IN(&ptInterface->tSendFifo);
      NpxHost_InitPacketHeader(ptPacket);
      ptPacket->tHeader.ulLen = sizeof(NPXPCK_HIF_DELETE_OBJECT_REQ_DATA_T);
      ptPacket->tHeader.ulCmd = NPXPCK_HIF_DELETE_OBJECT_REQ;
      ptPacket->tDeleteObjectReq.tData.ulGroupId  = ulGroupId;
      ptPacket->tDeleteObjectReq.tData.ulObjectId = ulObjectId;
      ulNpxResult = NpxHost_SetOutstanding(ptInterface, ptPacket, (uint32_t) pfnDone, pvDoneParam, 0, 0, NULL);
      if (ulNpxResult == SUCCESS_NET_PROXY_OK)
      {
        FIFO_PUT(&ptInterface->tSendFifo);
      }
    }
    (void) OS_ReleaseMutex(ptInterface->hMutex);
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_GetNumberOfInstancesAsync(
  NPX_HOST_IF_H                          hInterface,
  uint32_t                               ulGroupId,
  uint32_t                               ulObjectId,
  NPX_HOST_GET_NUMBER_OF_INSTANCES_CBK_T pfnDone,
  void*                                  pvDoneParam)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NpxHost_GetInterface(hInterface);
  NPX_HOST_PACKET_T*    ptPacket    = NULL;

  if (ptInterface == NULL || ptInterface->hMutex == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    (void) OS_WaitMutex(ptInterface->hMutex, 0xFFFFFFFF);
    if (FIFO_FULL(&ptInterface->tSendFifo))
      ulNpxResult = NPX_HOST_ERR_FIFO_FULL;
    else
    {
      ptPacket = &FIFO_IN(&ptInterface->tSendFifo);
      NpxHost_InitPacketHeader(ptPacket);
      ptPacket->tHeader.ulLen = sizeof(NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_REQ_DATA_T);
      ptPacket->tHeader.ulCmd = NPXPCK_HIF_GET_NUMBER_OF_INSTANCES_REQ;
      ptPacket->tGetNumberOfInstancesReq.tData.ulGroupId  = ulGroupId;
      ptPacket->tGetNumberOfInstancesReq.tData.ulObjectId = ulObjectId;
      ulNpxResult = NpxHost_SetOutstanding(ptInterface, ptPacket, (uint32_t) pfnDone, pvDoneParam, 0, 0, NULL);
      if (ulNpxResult == SUCCESS_NET_PROXY_OK)
      {
        FIFO_PUT(&ptInterface->tSendFifo);
      }
    }
    (void) OS_ReleaseMutex(ptInterface->hMutex);
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_RegisterUpdateNotificationAsync(
  NPX_HOST_IF_H                               hInterface,
  uint32_t                                    ulGroupId,
  uint32_t                                    ulObjectId,
  uint32_t                                    ulObjectInstance,
  uint32_t                                    ulElementNumber,
  NPX_HOST_REGISTER_UPDATE_NOTIFICATION_CBK_T pfnDone,
  void*                                       pvDoneParam,
  NPX_HOST_UPDATE_NOTIFICATION_CBK_T          pfnNotification,
  void*                                       pvNotificationParam)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NpxHost_GetInterface(hInterface);
  NPX_HOST_PACKET_T*    ptPacket    = NULL;

  if (ptInterface == NULL || ptInterface->hMutex == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    (void) OS_WaitMutex(ptInterface->hMutex, 0xFFFFFFFF);
    if (FIFO_FULL(&ptInterface->tSendFifo))
      ulNpxResult = NPX_HOST_ERR_FIFO_FULL;
    else
    {
      ptPacket = &FIFO_IN(&ptInterface->tSendFifo);
      NpxHost_InitPacketHeader(ptPacket);
      ptPacket->tHeader.ulLen = sizeof(NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_REQ_DATA_T);
      ptPacket->tHeader.ulCmd = NPXPCK_HIF_REGISTER_UPDATE_NOTIFICATION_REQ;
      ptPacket->tRegisterUpdateNotificationReq.tData.ulGroupId        = ulGroupId;
      ptPacket->tRegisterUpdateNotificationReq.tData.ulObjectId       = ulObjectId;
      ptPacket->tRegisterUpdateNotificationReq.tData.ulObjectInstance = ulObjectInstance;
      ptPacket->tRegisterUpdateNotificationReq.tData.ulElementNo      = ulElementNumber;
      ulNpxResult = NpxHost_SetOutstanding(ptInterface, ptPacket, (uint32_t) pfnDone, pvDoneParam, (uint32_t) pfnNotification, 0, pvNotificationParam);
      if (ulNpxResult == SUCCESS_NET_PROXY_OK)
      {
        FIFO_PUT(&ptInterface->tSendFifo);
      }
    }
    (void) OS_ReleaseMutex(ptInterface->hMutex);
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_UnregisterUpdateNotificationAsync(
  NPX_HOST_IF_H                                 hInterface,
  uint32_t                                      ulGroupId,
  uint32_t                                      ulObjectId,
  uint32_t                                      ulObjectInstance,
  uint32_t                                      ulElementNumber,
  NPX_HOST_UNREGISTER_UPDATE_NOTIFICATION_CBK_T pfnDone,
  void*                                         pvDoneParam)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NpxHost_GetInterface(hInterface);
  NPX_HOST_PACKET_T*    ptPacket    = NULL;

  if (ptInterface == NULL || ptInterface->hMutex == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    (void) OS_WaitMutex(ptInterface->hMutex, 0xFFFFFFFF);
    if (FIFO_FULL(&ptInterface->tSendFifo))
      ulNpxResult = NPX_HOST_ERR_FIFO_FULL;
    else
    {
      ptPacket = &FIFO_IN(&ptInterface->tSendFifo);
      NpxHost_InitPacketHeader(ptPacket);
      ptPacket->tHeader.ulLen = sizeof(NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_REQ_DATA_T);
      ptPacket->tHeader.ulCmd = NPXPCK_HIF_UNREGISTER_UPDATE_NOTIFICATION_REQ;
      ptPacket->tUnregisterUpdateNotificationReq.tData.ulGroupId        = ulGroupId;
      ptPacket->tUnregisterUpdateNotificationReq.tData.ulObjectId       = ulObjectId;
      ptPacket->tUnregisterUpdateNotificationReq.tData.ulObjectInstance = ulObjectInstance;
      ptPacket->tUnregisterUpdateNotificationReq.tData.ulElementNo      = ulElementNumber;
      ulNpxResult = NpxHost_SetOutstanding(ptInterface, ptPacket, (uint32_t) pfnDone, pvDoneParam, 0, 0, NULL);
      if (ulNpxResult == SUCCESS_NET_PROXY_OK)
      {
        FIFO_PUT(&ptInterface->tSendFifo);
      }
    }
    (void) OS_ReleaseMutex(ptInterface->hMutex);
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_AddBehaviorObjectAsync(
  NPX_HOST_IF_H                        hInterface,
  uint32_t                             ulGroupId,
  uint32_t                             ulObjectId,
  uint32_t                             ulNumberOfInstances,
  NPX_HOST_ADD_BEHAVIOR_OBJECT_CBK_T   pfnDone,
  void*                                pvDoneParam,
  NPX_HOST_BEHAVIOR_OBJECT_READ_CBK_T  pfnReadIndication,
  NPX_HOST_BEHAVIOR_OBJECT_WRITE_CBK_T pfnWriteIndication,
  void*                                pvIndicationParam)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NpxHost_GetInterface(hInterface);
  NPX_HOST_PACKET_T*    ptPacket    = NULL;

  if (ptInterface == NULL || ptInterface->hMutex == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    (void) OS_WaitMutex(ptInterface->hMutex, 0xFFFFFFFF);
    if (FIFO_FULL(&ptInterface->tSendFifo))
      ulNpxResult = NPX_HOST_ERR_FIFO_FULL;
    else
    {
      ptPacket = &FIFO_IN(&ptInterface->tSendFifo);
      NpxHost_InitPacketHeader(ptPacket);
      ptPacket->tHeader.ulLen = sizeof(NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_REQ_DATA_T);
      ptPacket->tHeader.ulCmd = NPXPCK_HIF_ADD_BEHAVIOR_OBJECT_REQ;
      ptPacket->tAddVolatileObjectReq.tData.ulGroupId           = ulGroupId;
      ptPacket->tAddVolatileObjectReq.tData.ulObjectId          = ulObjectId;
      ptPacket->tAddVolatileObjectReq.tData.ulNumberOfInstances = ulNumberOfInstances;
      ulNpxResult = NpxHost_SetOutstanding(ptInterface, ptPacket, (uint32_t) pfnDone, pvDoneParam, (uint32_t) pfnReadIndication, (uint32_t) pfnWriteIndication, pvIndicationParam);
      if (ulNpxResult == SUCCESS_NET_PROXY_OK)
      {
        FIFO_PUT(&ptInterface->tSendFifo);
      }
    }
    (void) OS_ReleaseMutex(ptInterface->hMutex);
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_SetBehaviorObjectNumInstAsync(
  NPX_HOST_IF_H                               hInterface,
  uint32_t                                    ulGroupId,
  uint32_t                                    ulObjectId,
  uint32_t                                    ulNumberOfInstances,
  NPX_HOST_SET_BEHAVIOR_OBJECT_NUM_INST_CBK_T pfnDone,
  void*                                       pvDoneParam)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NpxHost_GetInterface(hInterface);
  NPX_HOST_PACKET_T*    ptPacket    = NULL;

  if (ptInterface == NULL || ptInterface->hMutex == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  {
    (void) OS_WaitMutex(ptInterface->hMutex, 0xFFFFFFFF);
    if (FIFO_FULL(&ptInterface->tSendFifo))
      ulNpxResult = NPX_HOST_ERR_FIFO_FULL;
    else
    {
      ptPacket = &FIFO_IN(&ptInterface->tSendFifo);
      NpxHost_InitPacketHeader(ptPacket);
      ptPacket->tHeader.ulLen = sizeof(NPXPCK_HIF_SET_BEHAVIOR_OBJECT_NUM_INST_REQ_DATA_T);
      ptPacket->tHeader.ulCmd = NPXPCK_HIF_SET_BEHAVIOR_OBJECT_NUM_INST_REQ;
      ptPacket->tAddVolatileObjectReq.tData.ulGroupId           = ulGroupId;
      ptPacket->tAddVolatileObjectReq.tData.ulObjectId          = ulObjectId;
      ptPacket->tAddVolatileObjectReq.tData.ulNumberOfInstances = ulNumberOfInstances;
      ulNpxResult = NpxHost_SetOutstanding(ptInterface, ptPacket, (uint32_t) pfnDone, pvDoneParam, 0, 0, NULL);
      if (ulNpxResult == SUCCESS_NET_PROXY_OK)
      {
        FIFO_PUT(&ptInterface->tSendFifo);
      }
    }
    (void) OS_ReleaseMutex(ptInterface->hMutex);
  }
  return (ulNpxResult);
}



/*************************************************************************************/
/* Synchronous API Functions                                                        */
/*************************************************************************************/


uint32_t   APIENTRY NpxHost_ReadObjectElement(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulGroupId,
  uint32_t      ulObjectId,
  uint32_t      ulObjectInstance,
  uint32_t      ulElementNumber,
  void*         pvBuffer,
  uint32_t*     pulDataLen,
  uint32_t      ulTimeout)
{
  uint32_t        ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_SYNC_T tSync       = {SUCCESS_NET_PROXY_OK, NULL, NULL, 0};

  tSync.pvBuffer = pvBuffer;
  ulNpxResult = NpxHost_ReadObjectElementAsync(hInterface, ulGroupId, ulObjectId, ulObjectInstance, ulElementNumber, NpxHost_ReadObjectElementDone, &tSync);
  if (ulNpxResult == SUCCESS_NET_PROXY_OK)
  {
    if (tSync.ptOutstanding != NULL && tSync.ptOutstanding->hEvent != NULL)
    { /* derive the error code to be returned by the function */
      switch (OS_WaitEvent(tSync.ptOutstanding->hEvent, ulTimeout))
      {
        case SUCCESS_HIL_OK          : ulNpxResult = tSync.ulNpxResult;    break;  /* confirmation packet received within the given timeout */
//        case OSAL_ERR_TIMEOUT : ulNpxResult = NPX_HOST_ERR_TIMEOUT; break;  /* no confirmation packet received within the given timeout */
        default               : ulNpxResult = ERR_NET_PROXY_UNEXPECTED;     /* event handling error */
      }
      /* release the outstanding service management entry */
      tSync.ptOutstanding->ulId = 0;
    }
    if (ulNpxResult == SUCCESS_NET_PROXY_OK && pulDataLen != NULL)
      *pulDataLen = tSync.ulDataLen;
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_WriteObjectElement(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulGroupId,
  uint32_t      ulObjectId,
  uint32_t      ulObjectInstance,
  uint32_t      ulElementNumber,
  void*         pvBuffer,
  uint32_t      ulDataLen,
  uint32_t      ulTimeout)
{
  uint32_t        ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_SYNC_T tSync       = {SUCCESS_NET_PROXY_OK, NULL, NULL, 0};

  ulNpxResult = NpxHost_WriteObjectElementAsync(hInterface, ulGroupId, ulObjectId, ulObjectInstance, ulElementNumber, pvBuffer, ulDataLen, NpxHost_WriteObjectElementDone, &tSync);
  if (ulNpxResult == SUCCESS_NET_PROXY_OK)
  {
    if (tSync.ptOutstanding != NULL && tSync.ptOutstanding->hEvent != NULL)
    { /* derive the error code to be returned by the function */
      switch (OS_WaitEvent(tSync.ptOutstanding->hEvent, ulTimeout))
      {
        case SUCCESS_HIL_OK          : ulNpxResult = tSync.ulNpxResult;    break;  /* confirmation packet received within the given timeout */
//        case OSAL_ERR_TIMEOUT : ulNpxResult = NPX_HOST_ERR_TIMEOUT; break;  /* no confirmation packet received within the given timeout */
        default               : ulNpxResult = ERR_NET_PROXY_UNEXPECTED;     /* event handling error */
      }
      /* release the outstanding service management entry */
      tSync.ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_GetElementByteSize(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulObjectId,
  uint32_t      ulElementNumber,
  uint32_t*     pulByteSize,
  uint32_t      ulTimeout)
{
  uint32_t        ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_SYNC_T tSync       = {SUCCESS_NET_PROXY_OK, NULL, NULL, 0};

  tSync.pvBuffer = pulByteSize;
  ulNpxResult = NpxHost_GetElementByteSizeAsync(hInterface, ulObjectId, ulElementNumber, NpxHost_GetElementByteSizeDone, &tSync);
  if (ulNpxResult == SUCCESS_NET_PROXY_OK)
  {
    if (tSync.ptOutstanding != NULL && tSync.ptOutstanding->hEvent != NULL)
    { /* derive the error code to be returned by the function */
      switch (OS_WaitEvent(tSync.ptOutstanding->hEvent, ulTimeout))
      {
        case SUCCESS_HIL_OK          : ulNpxResult = tSync.ulNpxResult;    break;  /* confirmation packet received within the given timeout */
//        case OSAL_ERR_TIMEOUT : ulNpxResult = NPX_HOST_ERR_TIMEOUT; break;  /* no confirmation packet received within the given timeout */
        default               : ulNpxResult = ERR_NET_PROXY_UNEXPECTED;     /* event handling error */
      }
      /* release the outstanding service management entry */
      tSync.ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_AddObjectDescription(
  NPX_HOST_IF_H                        hInterface,
  const NPX_HOST_OBJECT_DESCRIPTION_T* ptObjectDescription,
  uint32_t                             ulTimeout)
{
  uint32_t        ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_SYNC_T tSync       = {SUCCESS_NET_PROXY_OK, NULL, NULL, 0};

  ulNpxResult = NpxHost_AddObjectDescriptionAsync(hInterface, ptObjectDescription, NpxHost_AddObjectDescriptionDone, &tSync);
  if (ulNpxResult == SUCCESS_NET_PROXY_OK)
  {
    if (tSync.ptOutstanding != NULL && tSync.ptOutstanding->hEvent != NULL)
    { /* derive the error code to be returned by the function */
      switch (OS_WaitEvent(tSync.ptOutstanding->hEvent, ulTimeout))
      {
        case SUCCESS_HIL_OK          : ulNpxResult = tSync.ulNpxResult;    break;  /* confirmation packet received within the given timeout */
//        case OSAL_ERR_TIMEOUT : ulNpxResult = NPX_HOST_ERR_TIMEOUT; break;  /* no confirmation packet received within the given timeout */
        default               : ulNpxResult = ERR_NET_PROXY_UNEXPECTED;     /* event handling error */
      }
      /* release the outstanding service management entry */
      tSync.ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_DeleteObjectDescription(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulObjectId,
  uint32_t      ulTimeout)
{
  uint32_t        ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_SYNC_T tSync       = {SUCCESS_NET_PROXY_OK, NULL, NULL, 0};

  ulNpxResult = NpxHost_DeleteObjectDescriptionAsync(hInterface, ulObjectId, NpxHost_DeleteObjectDescriptionDone, &tSync);
  if (ulNpxResult == SUCCESS_NET_PROXY_OK)
  {
    if (tSync.ptOutstanding != NULL && tSync.ptOutstanding->hEvent != NULL)
    { /* derive the error code to be returned by the function */
      switch (OS_WaitEvent(tSync.ptOutstanding->hEvent, ulTimeout))
      {
        case SUCCESS_HIL_OK          : ulNpxResult = tSync.ulNpxResult;    break;  /* confirmation packet received within the given timeout */
//        case OSAL_ERR_TIMEOUT : ulNpxResult = NPX_HOST_ERR_TIMEOUT; break;  /* no confirmation packet received within the given timeout */
        default               : ulNpxResult = ERR_NET_PROXY_UNEXPECTED;     /* event handling error */
      }
      /* release the outstanding service management entry */
      tSync.ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_GetObjectDescription(
  NPX_HOST_IF_H                         hInterface,
  NPX_HOST_OBJECT_DESCRIPTION_BUFFER_T* ptObjectDescriptionBuffer,
  uint32_t*                             pulDataLen,
  uint32_t                              ulTimeout)
{
  uint32_t        ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_SYNC_T tSync       = {SUCCESS_NET_PROXY_OK, NULL, NULL, 0};

  tSync.pvBuffer = ptObjectDescriptionBuffer;
  ulNpxResult = NpxHost_GetObjectDescriptionAsync(hInterface, ptObjectDescriptionBuffer->ulObjectId, NpxHost_GetObjectDescriptionDone, &tSync);
  if (ulNpxResult == SUCCESS_NET_PROXY_OK)
  {
    if (tSync.ptOutstanding != NULL && tSync.ptOutstanding->hEvent != NULL)
    { /* derive the error code to be returned by the function */
      switch (OS_WaitEvent(tSync.ptOutstanding->hEvent, ulTimeout))
      {
        case SUCCESS_HIL_OK          : ulNpxResult = tSync.ulNpxResult;    break;  /* confirmation packet received within the given timeout */
//        case OSAL_ERR_TIMEOUT : ulNpxResult = NPX_HOST_ERR_TIMEOUT; break;  /* no confirmation packet received within the given timeout */
        default               : ulNpxResult = ERR_NET_PROXY_UNEXPECTED;     /* event handling error */
      }
      /* release the outstanding service management entry */
      tSync.ptOutstanding->ulId = 0;
    }
    if (ulNpxResult == SUCCESS_NET_PROXY_OK && pulDataLen != NULL)
      *pulDataLen = tSync.ulDataLen;
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_AddVolatileObject(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulGroupId,
  uint32_t      ulObjectId,
  uint32_t      ulNumberOfInstances,
  uint32_t      ulTimeout)
{
  uint32_t        ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_SYNC_T tSync       = {SUCCESS_NET_PROXY_OK, NULL, NULL, 0};

  ulNpxResult = NpxHost_AddVolatileObjectAsync(hInterface, ulGroupId, ulObjectId, ulNumberOfInstances, NpxHost_AddVolatileObjectDone, &tSync);
  if (ulNpxResult == SUCCESS_NET_PROXY_OK)
  {
    if (tSync.ptOutstanding != NULL && tSync.ptOutstanding->hEvent != NULL)
    { /* derive the error code to be returned by the function */
      switch (OS_WaitEvent(tSync.ptOutstanding->hEvent, ulTimeout))
      {
        case SUCCESS_HIL_OK          : ulNpxResult = tSync.ulNpxResult;    break;  /* confirmation packet received within the given timeout */
//        case OSAL_ERR_TIMEOUT : ulNpxResult = NPX_HOST_ERR_TIMEOUT; break;  /* no confirmation packet received within the given timeout */
        default               : ulNpxResult = ERR_NET_PROXY_UNEXPECTED;     /* event handling error */
      }
      /* release the outstanding service management entry */
      tSync.ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_DeleteObject(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulGroupId,
  uint32_t      ulObjectId,
  uint32_t      ulTimeout)
{
  uint32_t        ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_SYNC_T tSync       = {SUCCESS_NET_PROXY_OK, NULL, NULL, 0};

  ulNpxResult = NpxHost_DeleteObjectAsync(hInterface, ulGroupId, ulObjectId, NpxHost_DeleteObjectDone, &tSync);
  if (ulNpxResult == SUCCESS_NET_PROXY_OK)
  {
    if (tSync.ptOutstanding != NULL && tSync.ptOutstanding->hEvent != NULL)
    { /* derive the error code to be returned by the function */
      switch (OS_WaitEvent(tSync.ptOutstanding->hEvent, ulTimeout))
      {
        case SUCCESS_HIL_OK          : ulNpxResult = tSync.ulNpxResult;    break;  /* confirmation packet received within the given timeout */
//        case OSAL_ERR_TIMEOUT : ulNpxResult = NPX_HOST_ERR_TIMEOUT; break;  /* no confirmation packet received within the given timeout */
        default               : ulNpxResult = ERR_NET_PROXY_UNEXPECTED;     /* event handling error */
      }
      /* release the outstanding service management entry */
      tSync.ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_GetNumberOfInstances(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulGroupId,
  uint32_t      ulObjectId,
  uint32_t*     pulNumberOfInstances,
  uint32_t      ulTimeout)
{
  uint32_t        ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_SYNC_T tSync       = {SUCCESS_NET_PROXY_OK, NULL, NULL, 0};

  tSync.pvBuffer = pulNumberOfInstances;
  ulNpxResult = NpxHost_GetNumberOfInstancesAsync(hInterface, ulGroupId, ulObjectId, NpxHost_GetNumberOfInstancesDone, &tSync);
  if (ulNpxResult == SUCCESS_NET_PROXY_OK)
  {
    if (tSync.ptOutstanding != NULL && tSync.ptOutstanding->hEvent != NULL)
    { /* derive the error code to be returned by the function */
      switch (OS_WaitEvent(tSync.ptOutstanding->hEvent, ulTimeout))
      {
        case SUCCESS_HIL_OK          : ulNpxResult = tSync.ulNpxResult;    break;  /* confirmation packet received within the given timeout */
//        case OSAL_ERR_TIMEOUT : ulNpxResult = NPX_HOST_ERR_TIMEOUT; break;  /* no confirmation packet received within the given timeout */
        default               : ulNpxResult = ERR_NET_PROXY_UNEXPECTED;     /* event handling error */
      }
      /* release the outstanding service management entry */
      tSync.ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_RegisterUpdateNotification(
  NPX_HOST_IF_H                      hInterface,
  uint32_t                           ulGroupId,
  uint32_t                           ulObjectId,
  uint32_t                           ulObjectInstance,
  uint32_t                           ulElementNumber,
  NPX_HOST_UPDATE_NOTIFICATION_CBK_T pfnNotification,
  void*                              pvNotificationParam,
  uint32_t                           ulTimeout)
{
  uint32_t        ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_SYNC_T tSync       = {SUCCESS_NET_PROXY_OK, NULL, NULL, 0};

  ulNpxResult = NpxHost_RegisterUpdateNotificationAsync(hInterface, ulGroupId, ulObjectId, ulObjectInstance, ulElementNumber, NpxHost_RegisterUpdateNotificationDone, &tSync, pfnNotification, pvNotificationParam);
  if (ulNpxResult == SUCCESS_NET_PROXY_OK)
  {
    if (tSync.ptOutstanding != NULL && tSync.ptOutstanding->hEvent != NULL)
    { /* derive the error code to be returned by the function */
      switch (OS_WaitEvent(tSync.ptOutstanding->hEvent, ulTimeout))
      {
        case SUCCESS_HIL_OK          : ulNpxResult = tSync.ulNpxResult;    break;  /* confirmation packet received within the given timeout */
//        case OSAL_ERR_TIMEOUT : ulNpxResult = NPX_HOST_ERR_TIMEOUT; break;  /* no confirmation packet received within the given timeout */
        default               : ulNpxResult = ERR_NET_PROXY_UNEXPECTED;     /* event handling error */
      }
      /* do not release the outstanding service entry: the host API will re-use it for assigning assigning update notification indications */
      /* tSync.ptOutstanding->ulId = 0; */
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_UnregisterUpdateNotification(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulGroupId,
  uint32_t      ulObjectId,
  uint32_t      ulObjectInstance,
  uint32_t      ulElementNumber,
  uint32_t      ulTimeout)
{
  uint32_t        ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_SYNC_T tSync       = {SUCCESS_NET_PROXY_OK, NULL, NULL, 0};

  ulNpxResult = NpxHost_UnregisterUpdateNotificationAsync(hInterface, ulGroupId, ulObjectId, ulObjectInstance, ulElementNumber, NpxHost_UnregisterUpdateNotificationDone, &tSync);
  if (ulNpxResult == SUCCESS_NET_PROXY_OK)
  {
    if (tSync.ptOutstanding != NULL && tSync.ptOutstanding->hEvent != NULL)
    { /* derive the error code to be returned by the function */
      switch (OS_WaitEvent(tSync.ptOutstanding->hEvent, ulTimeout))
      {
        case SUCCESS_HIL_OK          : ulNpxResult = tSync.ulNpxResult;    break;  /* confirmation packet received within the given timeout */
//        case OSAL_ERR_TIMEOUT : ulNpxResult = NPX_HOST_ERR_TIMEOUT; break;  /* no confirmation packet received within the given timeout */
        default               : ulNpxResult = ERR_NET_PROXY_UNEXPECTED;     /* event handling error */
      }
      /* release the outstanding service management entry */
      tSync.ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_AddBehaviorObject(
  NPX_HOST_IF_H                        hInterface,
  uint32_t                             ulGroupId,
  uint32_t                             ulObjectId,
  uint32_t                             ulNumberOfInstances,
  NPX_HOST_BEHAVIOR_OBJECT_READ_CBK_T  pfnReadIndication,
  NPX_HOST_BEHAVIOR_OBJECT_WRITE_CBK_T pfnWriteIndication,
  void*                                pvIndicationParam,
  uint32_t                             ulTimeout)
{
  uint32_t        ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_SYNC_T tSync       = {SUCCESS_NET_PROXY_OK, NULL, NULL, 0};

  ulNpxResult = NpxHost_AddBehaviorObjectAsync(hInterface, ulGroupId, ulObjectId, ulNumberOfInstances, NpxHost_AddBehaviorObjectDone, &tSync, pfnReadIndication, pfnWriteIndication, pvIndicationParam);
  if (ulNpxResult == SUCCESS_NET_PROXY_OK)
  {
    if (tSync.ptOutstanding != NULL && tSync.ptOutstanding->hEvent != NULL)
    { /* derive the error code to be returned by the function */
      switch (OS_WaitEvent(tSync.ptOutstanding->hEvent, ulTimeout))
      {
        case SUCCESS_HIL_OK          : ulNpxResult = tSync.ulNpxResult;    break;  /* confirmation packet received within the given timeout */
//        case OSAL_ERR_TIMEOUT : ulNpxResult = NPX_HOST_ERR_TIMEOUT; break;  /* no confirmation packet received within the given timeout */
        default               : ulNpxResult = ERR_NET_PROXY_UNEXPECTED;     /* event handling error */
      }
      /* do not release the outstanding service entry: the host API will re-use it for assigning behavior object service indications */
      /* tSync.ptOutstanding->ulId = 0; */
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_SetBehaviorObjectNumInst(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulGroupId,
  uint32_t      ulObjectId,
  uint32_t      ulNumberOfInstances,
  uint32_t      ulTimeout)
{
  uint32_t        ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_SYNC_T tSync       = {SUCCESS_NET_PROXY_OK, NULL, NULL, 0};

  ulNpxResult = NpxHost_SetBehaviorObjectNumInstAsync(hInterface, ulGroupId, ulObjectId, ulNumberOfInstances, NpxHost_SetBehaviorObjectNumInstDone, &tSync);
  if (ulNpxResult == SUCCESS_NET_PROXY_OK)
  {
    if (tSync.ptOutstanding != NULL && tSync.ptOutstanding->hEvent != NULL)
    { /* derive the error code to be returned by the function */
      switch (OS_WaitEvent(tSync.ptOutstanding->hEvent, ulTimeout))
      {
        case SUCCESS_HIL_OK          : ulNpxResult = tSync.ulNpxResult;    break;  /* confirmation packet received within the given timeout */
//        case OSAL_ERR_TIMEOUT : ulNpxResult = NPX_HOST_ERR_TIMEOUT; break;  /* no confirmation packet received within the given timeout */
        default               : ulNpxResult = ERR_NET_PROXY_UNEXPECTED;     /* event handling error */
      }
      /* release the outstanding service management entry */
      tSync.ptOutstanding->ulId = 0;
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_ReadInput(
  NPX_HOST_IF_H hInterface,
  void*         pvBuffer,
  uint32_t      ulDataLen,
  uint32_t      ulOffset,
  uint32_t      ulTimeout)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NULL;
  int32_t               iCifxResult = CIFX_NO_ERROR;

  ptInterface = NpxHost_GetInterface(hInterface);
  if (ptInterface == NULL || ptInterface->hMutex == NULL || ptInterface->hChannel == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  { /* read from the low-priority input data area (assuming a default channel layout) */
    iCifxResult = xChannelIORead(ptInterface->hChannel, 0, ulOffset, ulDataLen, pvBuffer, ulTimeout);
    switch (iCifxResult)
    {
      case CIFX_NO_ERROR:
        break;
      case CIFX_DEV_EXCHANGE_TIMEOUT:
      case CIFX_DEV_EXCHANGE_FAILED:
        ulNpxResult = NPX_HOST_ERR_TIMEOUT;
        break;
      default:
        ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    }
  }
  return (ulNpxResult);
}



uint32_t   APIENTRY NpxHost_WriteOutput(
  NPX_HOST_IF_H hInterface,
  void*         pvBuffer,
  uint32_t      ulDataLen,
  uint32_t      ulOffset,
  uint32_t      ulTimeout)
{
  uint32_t              ulNpxResult = SUCCESS_NET_PROXY_OK;
  NPX_HOST_INTERFACE_T* ptInterface = NULL;
  int32_t               iCifxResult = CIFX_NO_ERROR;

  ptInterface = NpxHost_GetInterface(hInterface);
  if (ptInterface == NULL || ptInterface->hMutex == NULL || ptInterface->hChannel == NULL)
    ulNpxResult = ERR_NET_PROXY_INVALID_HANDLE;
  else
  { /* write to the low-priority output data area (assuming a default channel layout) */
    iCifxResult = xChannelIOWrite(ptInterface->hChannel, 0, ulOffset, ulDataLen, pvBuffer, ulTimeout);
    switch (iCifxResult)
    {
      case CIFX_NO_ERROR:
        break;
      case CIFX_DEV_EXCHANGE_TIMEOUT:
      case CIFX_DEV_EXCHANGE_FAILED:
        ulNpxResult = NPX_HOST_ERR_TIMEOUT;
        break;
      default:
        ulNpxResult = ERR_NET_PROXY_UNEXPECTED;
    }
  }
  return (ulNpxResult);
}
