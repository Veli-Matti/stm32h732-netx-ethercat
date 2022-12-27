/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id: npx_sync_api.h 3816 2018-02-28 16:09:11Z dirk $

  Description:
    netPROXY - Synchronous object accessing

  NOTE:
    Do not include this file separate. This file will included in the correct order
    by using netPROXY.h

**************************************************************************************/
#ifndef __NPX_SYNC_API_H
#define __NPX_SYNC_API_H

#ifdef __cplusplus
extern "C" {
#endif  /* _cplusplus */


/*! Read of an element or object, with object handle.
 *
 * \param hObj          [in]  Handle to netPROXY object
 * \param ulObjInstance [in]  Instance of netPROXY object to be read
 * \param ulElementNo   [in]  Element number, or ::NPX_ELEMENT_NO_OBJECT_INSTANCE to read complete object instance
 * \param pvBuffer      [out] Buffer to be filled. <b>Note:</b> The caller of the function must ensure that the provided buffer
 *                            have sufficient size, The size can be determined by using the Npx_GetElementByteSize() function
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_SyncReadObjectElementByHandle(
  NPX_OBJ_H hObj,
  uint32_t ulObjInstance,
  uint32_t ulElementNo,
  void* pvBuffer);

/*! Write of an element or object, with object handle.
 *
 * \param hObj          [in]  Handle to netPROXY object
 * \param ulObjInstance [in] Instance of netPROXY object to be written
 * \param ulElementNo   [in] Element number, or ::NPX_ELEMENT_NO_OBJECT_INSTANCE to write complete object instance
 * \param pvBuffer      [in] Buffer that holds the data which should be written to the object.
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_SyncWriteObjectElementByHandle(
  NPX_OBJ_H hObj,
  uint32_t ulObjInstance,
  uint32_t ulElementNo,
  const void* pvBuffer);

/*! Read of an element or object.
 *
 * \param hInterface          [in]  Handle to netPROXY interface
 * \param ulGroupID           [in]  Group ID of object to be read
 * \param ulObjectID          [in]  Object ID of object to be read
 * \param ulObjInstance       [in]  Instance of netPROXY object to be read
 * \param ulElementNo         [in]  Element number, or ::NPX_ELEMENT_NO_OBJECT_INSTANCE to read complete object instance
 * \param pvBuffer            [out] Buffer to be filled. <b>Note:</b> The caller of the function must ensure that the provided buffer
 *                                  have sufficient size, The size can be determined by using the Npx_GetElementByteSize() function
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_SyncReadObjectElement(
  NPX_IF_H hInterface,
  uint32_t ulGroupID,
  uint32_t ulObjectID,
  uint32_t ulObjInstance,
  uint32_t ulElementNo,
  void* pvBuffer);

/*! Write of an element or object.
 *
 * \param hInterface          [in] Handle to netPROXY interface
 * \param ulGroupID           [in] Group ID of object to be written
 * \param ulObjectID          [in] Object ID of object to be written
 * \param ulObjInstance       [in] Instance of netPROXY object to be written
 * \param ulElementNo         [in] Element number, or ::NPX_ELEMENT_NO_OBJECT_INSTANCE to write complete object instance
 * \param pvBuffer            [in] Buffer that holds the data which should be written to the object.
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_SyncWriteObjectElement(
  NPX_IF_H hInterface,
  uint32_t ulGroupID,
  uint32_t ulObjectID,
  uint32_t ulObjInstance,
  uint32_t ulElementNo,
  const void* pvBuffer);


#ifdef __cplusplus
}
#endif  /* _cplusplus */

#endif /* __NPX_SYNC_API_H */
