/**********************************************************************************************************************
                 Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***********************************************************************************************************************
  $Id: NpxHostApiSync.h 3816 2018-02-28 16:09:11Z dirk $ *//**

  \file NpxHostApiSync.h
  \brief Host API providing synchronous access to netPROXY functionality via DPM.

  \note Exclusion of Liability for this demo software:\n
    The following software is intended for and must only be used for reference and in an evaluation laboratory
    environment. It is provided without charge and is subject to alterations. There is no warranty for the software,
    to the extent permitted by applicable law. Except when otherwise stated in writing the copyright holders and/or
    other parties provide the software "as is" without warranty of any kind, either expressed or implied.\n
    Please refer to the Agreement in \ref disclaimer, provided  together with this file! By installing or otherwise
    using the software, you accept the terms of this Agreement. If you do not agree to the terms of this Agreement,
    then do not install or use the Software!

***********************************************************************************************************************/
#ifndef __NPX_HOST_API_SYNC_H
#define __NPX_HOST_API_SYNC_H

#if defined(__cplusplus)
extern "C" {
#endif


/*! \addtogroup npxhost_sync_doc
@{*/

/** Read an object or object element.
 * (Blocking variant without confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param ulObjectInstance        [in]  object instance number
 * \param ulElementNumber         [in]  object element number (NPX_HOST_ALL_ELEMENTS: the complete object)
 * \param pvBuffer                [out] buffer to receive the object data or object element data read (see NPX_HOST_BUFSIZE_OBJECT_ELEMENT)
 * \param pulDataLen              [out] length of the object data or object element data read, given in bytes
 * \param ulTimeout               [in]  service timeout, given in ms (0: no timeout, wait time not limited)
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_ReadObjectElement(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulGroupId,
  uint32_t      ulObjectId,
  uint32_t      ulObjectInstance,
  uint32_t      ulElementNumber,
  void*         pvBuffer,
  uint32_t*     pulDataLen,
  uint32_t      ulTimeout);


/** Write an object or object element.
 * (Blocking variant without confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param ulObjectInstance        [in]  object instance number
 * \param ulElementNumber         [in]  object element number (NPX_HOST_ALL_ELEMENTS: the complete object)
 * \param pvBuffer                [in]  buffer holding the object data or object element data to be written
 * \param ulDataLen               [in]  length of the object data or object element data to be written, given in bytes
 * \param ulTimeout               [in]  service timeout, given in ms (0: no timeout, wait time not limited)
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_WriteObjectElement(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulGroupId,
  uint32_t      ulObjectId,
  uint32_t      ulObjectInstance,
  uint32_t      ulElementNumber,
  void*         pvBuffer,
  uint32_t      ulDataLen,
  uint32_t      ulTimeout);

/*************************************************************************************/

/** Retrieve the data size of an object or object element.
 * (Blocking variant without confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulObjectId              [in]  object ID of the object
 * \param ulElementNumber         [in]  object element number (NPX_HOST_ALL_ELEMENTS: the complete object)
 * \param pulByteSize             [out] buffer to receive the size of the object or object element, given in bytes
 * \param ulTimeout               [in]  service timeout, given in ms (0: no timeout, wait time not limited)
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_GetElementByteSize(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulObjectId,
  uint32_t      ulElementNumber,
  uint32_t*     pulByteSize,
  uint32_t      ulTimeout);

/*************************************************************************************/

/** Create/add the description of an object.
 * (Blocking variant without confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ptObjectDescription     [in]  buffer containing the object description
 * \param ulTimeout               [in]  service timeout, given in ms (0: no timeout, wait time not limited)
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_AddObjectDescription(
  NPX_HOST_IF_H                        hInterface,
  const NPX_HOST_OBJECT_DESCRIPTION_T* ptObjectDescription,
  uint32_t                             ulTimeout);


/** Delete the description of an object.
 * (Blocking variant without confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulObjectId              [in]  object ID
 * \param ulTimeout               [in]  service timeout, given in ms (0: no timeout, wait time not limited)
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_DeleteObjectDescription(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulObjectId,
  uint32_t      ulTimeout);


/** Retrieve the description of an object or object element.
 * (Blocking variant without confirmation callback.)
 *
 * \param hInterface                [in]    handle for the netPROXY host interface
 * \param ptObjectDescriptionBuffer [inout] buffer to receive the object description (member ulObjectId must have been set before invocation)
 * \param pulDataLen                [out]   length of the object description data, given in bytes
 * \param ulTimeout                 [in]    service timeout, given in ms (0: no timeout, wait time not limited)
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_GetObjectDescription(
  NPX_HOST_IF_H                         hInterface,
  NPX_HOST_OBJECT_DESCRIPTION_BUFFER_T* ptObjectDescriptionBuffer,
  uint32_t*                             pulDataLen,
  uint32_t                              ulTimeout);

/*************************************************************************************/

/** Create/add one or more object instances.
 * (Blocking variant without confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param ulNumberOfInstances     [in]  number of new object instances to create/add
 * \param ulTimeout               [in]  service timeout, given in ms (0: no timeout, wait time not limited)
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_AddVolatileObject(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulGroupId,
  uint32_t      ulObjectId,
  uint32_t      ulNumberOfInstances,
  uint32_t      ulTimeout);


/** Delete an object.
 * (Blocking variant without confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param ulTimeout               [in]  service timeout, given in ms (0: no timeout, wait time not limited)
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_DeleteObject(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulGroupId,
  uint32_t      ulObjectId,
  uint32_t      ulTimeout);

/*************************************************************************************/

/** Retrieve the current number of instances of a given object.
 * (Blocking variant without confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param pulNumberOfInstances    [out] buffer to receive the current number of object instances
 * \param ulTimeout               [in]  service timeout, given in ms (0: no timeout, wait time not limited)
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_GetNumberOfInstances(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulGroupId,
  uint32_t      ulObjectId,
  uint32_t*     pulNumberOfInstances,
  uint32_t      ulTimeout);

/*************************************************************************************/

/** Register for update notifications on an object or object element.
 * (Blocking variant without confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param ulObjectInstance        [in]  object instance number
 * \param ulElementNumber         [in]  object element number (NPX_HOST_ALL_ELEMENTS: the complete object)
 * \param pfnNotification         [in]  address of a user callback function to be invoked when the object or object element is updated
 * \param pvNotificationParam     [in]  address of a user parameter to be passed to the user notification callback function
 * \param ulTimeout               [in]  service timeout, given in ms (0: no timeout, wait time not limited)
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_RegisterUpdateNotification(
  NPX_HOST_IF_H                      hInterface,
  uint32_t                           ulGroupId,
  uint32_t                           ulObjectId,
  uint32_t                           ulObjectInstance,
  uint32_t                           ulElementNumber,
  NPX_HOST_UPDATE_NOTIFICATION_CBK_T pfnNotification,
  void*                              pvNotificationParam,
  uint32_t                           ulTimeout);


/** Revoke an existing registration for update notifications on an object or object element.
 * (Blocking variant without confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param ulObjectInstance        [in]  object instance number
 * \param ulElementNumber         [in]  object element number (NPX_HOST_ALL_ELEMENTS: the complete object)
 * \param ulTimeout               [in]  service timeout, given in ms (0: no timeout, wait time not limited)
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_UnregisterUpdateNotification(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulGroupId,
  uint32_t      ulObjectId,
  uint32_t      ulObjectInstance,
  uint32_t      ulElementNumber,
  uint32_t      ulTimeout);



/** Read data from the DPM input area.
 * (Blocking variant without confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param pvBuffer                [out] buffer to receive the object data or object element data read
 * \param ulDataLen               [in]  length of the object data or object element data to be read, given in bytes
 * \param ulOffset                [in]  offset of the data to be read in the I/O area, given in bytes
 * \param ulTimeout               [in]  service timeout, given in ms (0: no timeout, wait time not limited)
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_ReadInput(
  NPX_HOST_IF_H hInterface,
  void*         pvBuffer,
  uint32_t      ulDataLen,
  uint32_t      ulOffset,
  uint32_t      ulTimeout);



/** Write data to the DPM output area.
 * (Blocking variant without confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param pvBuffer                [in]  buffer holding the object data or object element data to be written
 * \param ulDataLen               [in]  length of the object data or object element data to be written, given in bytes
 * \param ulOffset                [in]  offset of the data to be written in the I/O area, given in bytes
 * \param ulTimeout               [in]  service timeout, given in ms (0: no timeout, wait time not limited)
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_WriteOutput(
  NPX_HOST_IF_H hInterface,
  void*         pvBuffer,
  uint32_t      ulDataLen,
  uint32_t      ulOffset,
  uint32_t      ulTimeout);

/*************************************************************************************/

/** Create/add one or more behavior object instances.
 * (Blocking variant without confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param ulNumberOfInstances     [in]  number of new object instances to create/add
 * \param pfnReadIndication       [in]  address of a user callback function to be invoked when the object is read
 * \param pfnWriteIndication      [in]  address of a user callback function to be invoked when the object is written
 * \param pvIndicationParam       [in]  address of a user parameter to be passed to the user indication callback functions
 * \param ulTimeout               [in]  service timeout, given in ms (0: no timeout, wait time not limited)
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_AddBehaviorObject(
  NPX_HOST_IF_H                        hInterface,
  uint32_t                             ulGroupId,
  uint32_t                             ulObjectId,
  uint32_t                             ulNumberOfInstances,
  NPX_HOST_BEHAVIOR_OBJECT_READ_CBK_T  pfnReadIndication,
  NPX_HOST_BEHAVIOR_OBJECT_WRITE_CBK_T pfnWriteIndication,
  void*                                pvIndicationParam,
  uint32_t                             ulTimeout);



/** Set/adapt the number of behavior object instances.
 * (Blocking variant without confirmation callback.)
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 * \param ulGroupId               [in]  group ID of the object
 * \param ulObjectId              [in]  object ID of the object
 * \param ulNumberOfInstances     [in]  number of new object instances to create/add
 * \param ulTimeout               [in]  service timeout, given in ms (0: no timeout, wait time not limited)
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_SetBehaviorObjectNumInst(
  NPX_HOST_IF_H hInterface,
  uint32_t      ulGroupId,
  uint32_t      ulObjectId,
  uint32_t      ulNumberOfInstances,
  uint32_t      ulTimeout);



/*! @}*/

#ifdef __cplusplus
}
#endif  /* _cplusplus */

#endif /* __NPX_HOST_API_SYNC_H */
