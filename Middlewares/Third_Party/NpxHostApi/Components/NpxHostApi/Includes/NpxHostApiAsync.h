/**********************************************************************************************************************
                 Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***********************************************************************************************************************
  $Id: NpxHostApiAsync.h 3816 2018-02-28 16:09:11Z dirk $ *//**

  \file NpxHostApiAsync.h
  \brief Host API providing asynchronous access to netPROXY functionality via DPM.

  \note Exclusion of Liability for this demo software:\n
    The following software is intended for and must only be used for reference and in an evaluation laboratory
    environment. It is provided without charge and is subject to alterations. There is no warranty for the software,
    to the extent permitted by applicable law. Except when otherwise stated in writing the copyright holders and/or
    other parties provide the software "as is" without warranty of any kind, either expressed or implied.\n
    Please refer to the Agreement in \ref disclaimer, provided  together with this file! By installing or otherwise
    using the software, you accept the terms of this Agreement. If you do not agree to the terms of this Agreement,
    then do not install or use the Software!

***********************************************************************************************************************/
#ifndef __NPX_HOST_API_ASYNC_H
#define __NPX_HOST_API_ASYNC_H

#if defined(__cplusplus)
extern "C" {
#endif


/*! \addtogroup npxhost_async_doc
@{*/

/** Confirmation callback for NpxHost_ReadObjectElementAsync().
 *
 * \param ulNpxResult             [in]  netPROXY error code (taken from the confirmation packet)
 * \param pvDoneParam             [in]  user-defined callback parameter supplied when invoking the service
 * \param ulGroupId               [in]  group ID supplied when invoking the service
 * \param ulObjectId              [in]  object ID supplied when invoking the service
 * \param ulObjectInstance        [in]  object instance number supplied when invoking the service
 * \param ulElementNumber         [in]  object element number supplied when invoking the service
 * \param pvBuffer                [in]  buffer containing the data read (valid only until the end of the callback)
 * \param ulDataLen               [in]  length of the data read, given in bytes
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
typedef void (APIENTRY* NPX_HOST_READ_OBJECT_ELEMENT_CBK_T)(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulObjectInstance,
  uint32_t   ulElementNumber,
  void*      pvBuffer,
  uint32_t   ulDataLen);


/** Confirmation callback for NpxHost_WriteObjectElementAsync().
 *
 * \param ulNpxResult             [in]  netPROXY error code (taken from the confirmation packet)
 * \param pvDoneParam             [in]  user-defined callback parameter supplied when invoking the service
 * \param ulGroupId               [in]  group ID supplied when invoking the service
 * \param ulObjectId              [in]  object ID supplied when invoking the service
 * \param ulObjectInstance        [in]  object instance number supplied when invoking the service
 * \param ulElementNumber         [in]  object element number supplied when invoking the service
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
typedef void (APIENTRY* NPX_HOST_WRITE_OBJECT_ELEMENT_CBK_T)(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulObjectInstance,
  uint32_t   ulElementNumber);

/*************************************************************************************/

/** Confirmation callback for NpxHost_GetElementByteSizeAsync().
 *
 * \param ulNpxResult             [in]  netPROXY error code (taken from the confirmation packet)
 * \param pvDoneParam             [in]  user-defined callback parameter supplied when invoking the service
 * \param ulObjectId              [in]  object ID supplied when invoking the service
 * \param ulElementNumber         [in]  object element number supplied when invoking the service
 * \param ulByteSize              [in]  size of the object or object element, given in bytes
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
typedef void (APIENTRY* NPX_HOST_GET_ELEMENT_BYTESIZE_CBK_T)(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulObjectId,
  uint32_t   ulElementNumber,
  uint32_t   ulByteSize);

/*************************************************************************************/

/** Confirmation callback for NpxHost_AddObjectDescriptionAsync().
 *
 * \param ulNpxResult             [in]  netPROXY error code (taken from the confirmation packet)
 * \param pvDoneParam             [in]  user-defined callback parameter supplied when invoking the service
 * \param ulObjectId              [in]  object ID supplied when invoking the service
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
typedef void (APIENTRY* NPX_HOST_ADD_OBJECT_DESCRIPTION_CBK_T)(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulObjectId);


/** Confirmation callback for NpxHost_DeleteObjectDescriptionAsync().
 *
 * \param ulNpxResult             [in]  netPROXY error code (taken from the confirmation packet)
 * \param pvDoneParam             [in]  user-defined callback parameter supplied when invoking the service
 * \param ulObjectId              [in]  object ID supplied when invoking the service
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
typedef void (APIENTRY* NPX_HOST_DELETE_OBJECT_DESCRIPTION_CBK_T)(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulObjectId);


/** Confirmation callback for NpxHost_GetObjectDescriptionAsync().
 *
 * \param ulNpxResult               [in]  netPROXY error code (taken from the confirmation packet)
 * \param pvDoneParam               [in]  user-defined callback parameter supplied when invoking the service
 * \param ptObjectDescriptionBuffer [in]  buffer containing the object description (valid until the end of the callback)
 * \param ulDataLen                 [in]  length of the object description data, given in bytes
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
typedef void (APIENTRY* NPX_HOST_GET_OBJECT_DESCRIPTION_CBK_T)(
  uint32_t                              ulNpxResult,
  void*                                 pvDoneParam,
  NPX_HOST_OBJECT_DESCRIPTION_BUFFER_T* ptObjectDescriptionBuffer,
  uint32_t                              ulDataLen);

/*************************************************************************************/

/** Confirmation callback for NpxHost_AddVolatileObjectAsync().
 *
 * \param ulNpxResult             [in]  netPROXY error code (taken from the confirmation packet)
 * \param pvDoneParam             [in]  user-defined callback parameter supplied when invoking the service
 * \param ulGroupId               [in]  group ID supplied when invoking the service
 * \param ulObjectId              [in]  object ID supplied when invoking the service
 * \param ulNumberOfInstances     [in]  number of new object instances supplied when invoking the service
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
typedef void (APIENTRY* NPX_HOST_ADD_VOLATILE_OBJECT_CBK_T)(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulNumberOfInstances);


/** Confirmation callback for NpxHost_DeleteObjectAsync().
 *
 * \param ulNpxResult             [in]  netPROXY error code (taken from the confirmation packet)
 * \param pvDoneParam             [in]  user-defined callback parameter supplied when invoking the service
 * \param ulGroupId               [in]  group ID supplied when invoking the service
 * \param ulObjectId              [in]  object ID supplied when invoking the service
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
typedef void (APIENTRY* NPX_HOST_DELETE_OBJECT_CBK_T)(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId);

/*************************************************************************************/

/** Confirmation callback for NpxHost_GetNumberOfInstancesAsync().
 *
 * \param ulNpxResult             [in]  netPROXY error code (taken from the confirmation packet)
 * \param pvDoneParam             [in]  user-defined callback parameter supplied when invoking the service
 * \param ulGroupId               [in]  group ID supplied when invoking the service
 * \param ulObjectId              [in]  object ID supplied when invoking the service
 * \param ulNumberOfInstances     [in]  current number of object instances
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
typedef void (APIENTRY* NPX_HOST_GET_NUMBER_OF_INSTANCES_CBK_T)(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulNumberOfInstances);

/*************************************************************************************/

/** Confirmation callback for NpxHost_RegisterUpdateNotificationAsync().
 *
 * \param ulNpxResult             [in]  netPROXY error code (taken from the confirmation packet)
 * \param pvDoneParam             [in]  user-defined callback parameter supplied when invoking the service
 * \param ulGroupId               [in]  group ID supplied when invoking the service
 * \param ulObjectId              [in]  object ID supplied when invoking the service
 * \param ulObjectInstance        [in]  object instance number supplied when invoking the service
 * \param ulElementNumber         [in]  object element number supplied when invoking the service
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
typedef void (APIENTRY* NPX_HOST_REGISTER_UPDATE_NOTIFICATION_CBK_T)(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulObjectInstance,
  uint32_t   ulElementNumber);


/** Confirmation callback for NpxHost_UnregisterUpdateNotificationAsync().
 *
 * \param ulNpxResult             [in]  netPROXY error code (taken from the confirmation packet)
 * \param pvDoneParam             [in]  user-defined callback parameter supplied when invoking the service
 * \param ulGroupId               [in]  group ID supplied when invoking the service
 * \param ulObjectId              [in]  object ID supplied when invoking the service
 * \param ulObjectInstance        [in]  object instance number supplied when invoking the service
 * \param ulElementNumber         [in]  object element number supplied when invoking the service
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
typedef void (APIENTRY* NPX_HOST_UNREGISTER_UPDATE_NOTIFICATION_CBK_T)(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulObjectInstance,
  uint32_t   ulElementNumber);

/*************************************************************************************/

/** Confirmation callback for NpxHost_AddBehaviorObjectAsync().
 *
 * \param ulNpxResult             [in]  netPROXY error code (taken from the confirmation packet)
 * \param pvDoneParam             [in]  user-defined callback parameter supplied when invoking the service
 * \param ulGroupId               [in]  group ID supplied when invoking the service
 * \param ulObjectId              [in]  object ID supplied when invoking the service
 * \param ulNumberOfInstances     [in]  number of new object instances supplied when invoking the service
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
typedef void (APIENTRY* NPX_HOST_ADD_BEHAVIOR_OBJECT_CBK_T)(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulNumberOfInstances);


/** Confirmation callback for NpxHost_SetBehaviorObjectNumInstAsync().
 *
 * \param ulNpxResult             [in]  netPROXY error code (taken from the confirmation packet)
 * \param pvDoneParam             [in]  user-defined callback parameter supplied when invoking the service
 * \param ulGroupId               [in]  group ID supplied when invoking the service
 * \param ulObjectId              [in]  object ID supplied when invoking the service
 * \param ulNumberOfInstances     [in]  number of new object instances supplied when invoking the service
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
typedef void (APIENTRY* NPX_HOST_SET_BEHAVIOR_OBJECT_NUM_INST_CBK_T)(
  uint32_t   ulNpxResult,
  void*      pvDoneParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulNumberOfInstances);

/*************************************************************************************/

/** Read an object or object element.
 * (Non-blocking variant with user-defined confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param ulObjectInstance        [in]  object instance number
 * \param ulElementNumber         [in]  object element number (NPX_HOST_ALL_ELEMENTS: the complete object)
 * \param pfnDone                 [in]  address of a user callback function to be invoked when the service is confirmed
 * \param pvDoneParam             [in]  address of a user parameter to be passed to the user confirmation callback function
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_ReadObjectElementAsync(
  NPX_HOST_IF_H                      hInterface,
  uint32_t                           ulGroupId,
  uint32_t                           ulObjectId,
  uint32_t                           ulObjectInstance,
  uint32_t                           ulElementNumber,
  NPX_HOST_READ_OBJECT_ELEMENT_CBK_T pfnDone,
  void*                              pvDoneParam);


/** Write an object or object element.
 * (Non-blocking variant with user-defined confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param ulObjectInstance        [in]  object instance number
 * \param ulElementNumber         [in]  object element number (NPX_HOST_ALL_ELEMENTS: the complete object)
 * \param pvBuffer                [in]  address of a buffer holding the object data or object element data to be written
 * \param ulDataLen               [in]  length of the object data or object element data to be written, given in bytes
 * \param pfnDone                 [in]  address of a user callback function to be invoked when the service is confirmed
 * \param pvDoneParam             [in]  address of a user parameter to be passed to the user confirmation callback function
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_WriteObjectElementAsync(
  NPX_HOST_IF_H                       hInterface,
  uint32_t                            ulGroupId,
  uint32_t                            ulObjectId,
  uint32_t                            ulObjectInstance,
  uint32_t                            ulElementNumber,
  const void*                         pvBuffer,
  uint32_t                            ulDataLen,
  NPX_HOST_WRITE_OBJECT_ELEMENT_CBK_T pfnDone,
  void*                               pvDoneParam);

/*************************************************************************************/

/** Retrieve the data size of an object or object element.
 * (Non-blocking variant with user-defined confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulObjectId              [in]  object ID of the object
 * \param ulElementNumber         [in]  object element number (NPX_HOST_ALL_ELEMENTS: the complete object)
 * \param pfnDone                 [in]  address of a user callback function to be invoked when the service is confirmed
 * \param pvDoneParam             [in]  address of a user parameter to be passed to the user confirmation callback function
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_GetElementByteSizeAsync(
  NPX_HOST_IF_H                       hInterface,
  uint32_t                            ulObjectId,
  uint32_t                            ulElementNumber,
  NPX_HOST_GET_ELEMENT_BYTESIZE_CBK_T pfnDone,
  void*                               pvDoneParam);

/*************************************************************************************/

/** Create/add the description of an object.
 * (Non-blocking variant with user-defined confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ptObjectDescription     [in]  buffer containing the object description
 * \param pfnDone                 [in]  address of a user callback function to be invoked when the service is confirmed
 * \param pvDoneParam             [in]  address of a user parameter to be passed to the user confirmation callback function
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_AddObjectDescriptionAsync(
  NPX_HOST_IF_H                         hInterface,
  const NPX_HOST_OBJECT_DESCRIPTION_T*  ptObjectDescription,
  NPX_HOST_ADD_OBJECT_DESCRIPTION_CBK_T pfnDone,
  void*                                 pvDoneParam);


/** Delete the description of an object.
 * (Non-blocking variant with user-defined confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulObjectId              [in]  object ID
 * \param pfnDone                 [in]  address of a user callback function to be invoked when the service is confirmed
 * \param pvDoneParam             [in]  address of a user parameter to be passed to the user confirmation callback function
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_DeleteObjectDescriptionAsync(
  NPX_HOST_IF_H                            hInterface,
  uint32_t                                 ulObjectId,
  NPX_HOST_DELETE_OBJECT_DESCRIPTION_CBK_T pfnDone,
  void*                                    pvDoneParam);


/** Retrieve the description of an object or object element.
 * (Non-blocking variant with user-defined confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulObjectId              [in]  object ID
 * \param pfnDone                 [in]  address of a user callback function to be invoked when the service is confirmed
 * \param pvDoneParam             [in]  address of a user parameter to be passed to the user confirmation callback function
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_GetObjectDescriptionAsync(
  NPX_HOST_IF_H                         hInterface,
  uint32_t                              ulObjectId,
  NPX_HOST_GET_OBJECT_DESCRIPTION_CBK_T pfnDone,
  void*                                 pvDoneParam);

/*************************************************************************************/

/** Create/add one or more object instances.
 * (Non-blocking variant with user-defined confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param ulNumberOfInstances     [in]  number of new object instances to create/add
 * \param pfnDone                 [in]  address of a user callback function to be invoked when the service is confirmed
 * \param pvDoneParam             [in]  address of a user parameter to be passed to the user confirmation callback function
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_AddVolatileObjectAsync(
  NPX_HOST_IF_H                      hInterface,
  uint32_t                           ulGroupId,
  uint32_t                           ulObjectId,
  uint32_t                           ulNumberOfInstances,
  NPX_HOST_ADD_VOLATILE_OBJECT_CBK_T pfnDone,
  void*                              pvDoneParam);


/** Delete an object.
 * (Non-blocking variant with user-defined confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param pfnDone                 [in]  address of a user callback function to be invoked when the service is confirmed
 * \param pvDoneParam             [in]  address of a user parameter to be passed to the user confirmation callback function
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_DeleteObjectAsync(
  NPX_HOST_IF_H                hInterface,
  uint32_t                     ulGroupId,
  uint32_t                     ulObjectId,
  NPX_HOST_DELETE_OBJECT_CBK_T pfnDone,
  void*                        pvDoneParam);

/*************************************************************************************/

/** Retrieve the current number of instances of a given object.
 * (Non-blocking variant with user-defined confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param pfnDone                 [in]  address of a user callback function to be invoked when the service is confirmed
 * \param pvDoneParam             [in]  address of a user parameter to be passed to the user confirmation callback function
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_GetNumberOfInstancesAsync(
  NPX_HOST_IF_H                          hInterface,
  uint32_t                               ulGroupId,
  uint32_t                               ulObjectId,
  NPX_HOST_GET_NUMBER_OF_INSTANCES_CBK_T pfnDone,
  void*                                  pvDoneParam);

/*************************************************************************************/

/** Register for update notifications on an object or object element.
 * (Non-blocking variant with user-defined confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param ulObjectInstance        [in]  object instance number
 * \param ulElementNumber         [in]  object element number (NPX_HOST_ALL_ELEMENTS: the complete object)
 * \param pfnDone                 [in]  address of a user callback function to be invoked when the service is confirmed
 * \param pvDoneParam             [in]  address of a user parameter to be passed to the user confirmation callback function
 * \param pfnNotification         [in]  address of a user callback function to be invoked when the object or object element is updated
 * \param pvNotificationParam     [in]  address of a user parameter to be passed to the user notification callback function
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_RegisterUpdateNotificationAsync(
  NPX_HOST_IF_H                               hInterface,
  uint32_t                                    ulGroupId,
  uint32_t                                    ulObjectId,
  uint32_t                                    ulObjectInstance,
  uint32_t                                    ulElementNumber,
  NPX_HOST_REGISTER_UPDATE_NOTIFICATION_CBK_T pfnDone,
  void*                                       pvDoneParam,
  NPX_HOST_UPDATE_NOTIFICATION_CBK_T          pfnNotification,
  void*                                       pvNotificationParam);


/** Revoke an existing registration for update notifications on an object or object element.
 * (Non-blocking variant with user-defined confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param ulObjectInstance        [in]  object instance number
 * \param ulElementNumber         [in]  object element number (NPX_HOST_ALL_ELEMENTS: the complete object)
 * \param pfnDone                 [in]  address of a user callback function to be invoked when the service is confirmed
 * \param pvDoneParam             [in]  address of a user parameter to be passed to the user confirmation callback function
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_UnregisterUpdateNotificationAsync(
  NPX_HOST_IF_H                                 hInterface,
  uint32_t                                      ulGroupId,
  uint32_t                                      ulObjectId,
  uint32_t                                      ulObjectInstance,
  uint32_t                                      ulElementNumber,
  NPX_HOST_UNREGISTER_UPDATE_NOTIFICATION_CBK_T pfnDone,
  void*                                         pvDoneParam);

/*************************************************************************************/

/** Create/add one or more behavior object instances.
 * (Non-blocking variant with user-defined confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param ulNumberOfInstances     [in]  number of new object instances to create/add
 * \param pfnDone                 [in]  address of a user callback function to be invoked when the service is confirmed
 * \param pvDoneParam             [in]  address of a user parameter to be passed to the user confirmation callback function
 * \param pfnReadIndication       [in]  address of a user callback function to be invoked when the object is read
 * \param pfnWriteIndication      [in]  address of a user callback function to be invoked when the object is written
 * \param pvIndicationParam       [in]  address of a user parameter to be passed to the user indication callback functions
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_AddBehaviorObjectAsync(
  NPX_HOST_IF_H                        hInterface,
  uint32_t                             ulGroupId,
  uint32_t                             ulObjectId,
  uint32_t                             ulNumberOfInstances,
  NPX_HOST_ADD_BEHAVIOR_OBJECT_CBK_T   pfnDone,
  void*                                pvDoneParam,
  NPX_HOST_BEHAVIOR_OBJECT_READ_CBK_T  pfnReadIndication,
  NPX_HOST_BEHAVIOR_OBJECT_WRITE_CBK_T pfnWriteIndication,
  void*                                pvIndicationParam);


/** Set/adapt the number of behavior object instances.
 * (Non-blocking variant with user-defined confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param ulNumberOfInstances     [in]  number of new object instances to create/add
 * \param pfnDone                 [in]  address of a user callback function to be invoked when the service is confirmed
 * \param pvDoneParam             [in]  address of a user parameter to be passed to the user confirmation callback function
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_SetBehaviorObjectNumInstAsync(
  NPX_HOST_IF_H                               hInterface,
  uint32_t                                    ulGroupId,
  uint32_t                                    ulObjectId,
  uint32_t                                    ulNumberOfInstances,
  NPX_HOST_SET_BEHAVIOR_OBJECT_NUM_INST_CBK_T pfnDone,
  void*                                       pvDoneParam);


/*! @}*/

#ifdef __cplusplus
}
#endif  /* _cplusplus */

#endif /* __NPX_HOST_API_ASYNC_H */
