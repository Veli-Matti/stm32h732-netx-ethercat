/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id: npx_object_api.h 3816 2018-02-28 16:09:11Z dirk $

  Description:
    netPROXY object related functions

  NOTE:
    Do not include this file separate. This file will included in the correct order
    by using netPROXY.h

**************************************************************************************/
#ifndef __NPX_OBJECT_API_H
#define __NPX_OBJECT_API_H
/*! \addtogroup npx_obj_functions
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif  /* _cplusplus */


/*! netPROXY Object notification handle **/
typedef struct NPX_OBJECT_NOTIFY_Ttag* NPX_OBJ_NOTIFY_H;


/*! Write notify callback type. */
typedef void (APIENTRY *Npx_WriteNotifyCallback)(
  void*                       pvWriteNotifyCallbackParam,
  NPX_OBJ_H                   hObject);


/*! Get number of instances.
 *
 * Returns the actual number of instances which the object has. Some object may have a variable
 * number of instance.
 *
 * \param hInterface            [in]  Handle to netPROXY interface
 * \param ulGroupID             [in]  Group ID of object
 * \param ulObjectID            [in]  Object ID of object
 * \param pulNumberOfInstances  [out] Number of object instances
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_GetNumberOfObjectInstances(
  NPX_IF_H hInterface,
  uint32_t ulGroupID,
  uint32_t ulObjectID,
  uint32_t* pulNumberOfInstances);


/*! Register a update notify callback.
 *
 * The object owner will notify the client if there was a write request performed
 * on the object entity.
 *
 * \remarks The callback may be called before the function is actually returning.
 *
 * \param hInterface                  [in]  Handle to netPROXY interface
 * \param ulGroupID                   [in]  Group ID of object
 * \param ulObjectID                  [in]  Object ID of object
 * \param pfnWriteNotifyCallback      [in]  This callback will be called if an object entity was written
 * \param pvWriteNotifyCallbackParam  [in]  User data for callback specified by pfnWriteNotifyCallback
 * \param phObjNotifyHandle           [out] Pointer to store handle to netPROXY notify callback context
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_RegisterUpdateNotifyCallback(
  NPX_IF_H hInterface,
  uint32_t ulGroupID,
  uint32_t ulObjectID,
  Npx_WriteNotifyCallback pfnWriteNotifyCallback,
  void* pvWriteNotifyCallbackParam,
  NPX_OBJ_NOTIFY_H* phObjNotifyHandle);


/*! Unregister a update notify callback.
 *
 * \remarks The de-registration of the callback has to be expected to be finished when the
 *          unregister function returns. Before that, the callback may still be called.
 *
 * \note Freeing the same handle twice is not allowed, the function will not check the handle again.
 *       Doing so will invoke undefined behavior!
 *
 * \param hObjNotifyHandle [in] handle to netPROXY notify callback context
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_UnregisterUpdateNotifyCallback(
  NPX_OBJ_NOTIFY_H hObjNotifyHandle);


/*! Trigger a Update notification for an object.
 *
 * If this function is called all registered function to this object
 * will be informed over a change within the object when the ::Npx_ProcessUpdateNotifications
 * function is processed.
 *
 * \param hInterface  [in] Handle to netPROXY interface
 * \param ulGroupID   [in] Group ID of object
 * \param ulObjectID  [in] Object ID of object
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_TriggerUpdateNotification(
  NPX_IF_H hInterface,
  uint32_t ulGroupID,
  uint32_t ulObjectID);


/*! Trigger a Update notification for an object by handle.
 *
 * see ::Npx_TriggerUpdateNotification.
 *
 * \param hObj [in] Object handle
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_TriggerUpdateNotificationByHandle(
  NPX_OBJ_H hObj);


/*! Trigger a Update notification for an object by reference.
 *
 * see ::Npx_TriggerUpdateNotification.
 *
 * \note This function has no parameter checks! This function need an object
 *       reference (pointer to the internal object structure)
 *
 * \param ptObj [in] Object reference
 */
void APIENTRY
Npx_TriggerUpdateNotificationByRef(
  NPX_OBJ_PT ptObj);


/*! Process Update notifications to all registered applications.
 *
 * Process all as updated marked object of the interface.
 *
 * \note All registered callback will be called within this function. It is not
 *       allowed to call this functions from different contexts. Calling of this function
 *       is normal cyclicly processed by a device management task context.
 *
 * \param hInterface [in] handle to interface
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_ProcessUpdateNotifications(
  NPX_IF_H hInterface);


#ifdef __cplusplus
}
#endif  /* _cplusplus */

/*! @}*/
#endif /* __NPX_OBJECT_API_H */
