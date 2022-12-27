/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id: npx_async_api.h 3816 2018-02-28 16:09:11Z dirk $

  Description:
    netPROXY Core asynchronous object accessing functions.

  NOTE:
    Do not include this file separate. This file will included in the correct order
    by using netPROXY.h

**************************************************************************************/
#ifndef __NPX_ASYNC_API_H
#define __NPX_ASYNC_API_H

#ifdef __cplusplus
extern "C" {
#endif  /* _cplusplus */


/*! Asynchronously read of an element or object.
 * Read an object without blocking the caller. The requested data is not valid before the pfnDone() callback returns successfully.
 *
 * \note The caller must ensure that the given buffer can be written exclusively form the requested object.
 * \note The function pfnDone may be called before the function Npx_AsyncReadObjectElementByHandle() returns.
 * \note If the given function pfnDone points to NULL, no read request is performed at all!
 *
 * \param hObj                [in]  Handle to a netPROXY object
 * \param ulObjInstance       [in]  Instance of netPROXY object to be read
 * \param ulElementNo         [in]  Element number, or ::NPX_ELEMENT_NO_OBJECT_INSTANCE to read complete object instance
 * \param pvBuffer            [out] Buffer to be filled. <b>Note:</b> The caller of the function must ensure that the provided buffer
 *                                  have sufficient size, The size can be determined by using the Npx_GetElementByteSize() function
 * \param pfnDone             [in]  Callback to be called after read of object was performed. The result of the call is given within this callback
 * \param pvDoneCallbackParam [in]  Callback user parameter of Npx_AsyncObjectDoneCallback() function
 *
 */
void APIENTRY
Npx_AsyncReadObjectElementByHandle(
  NPX_OBJ_H hObj,
  uint32_t ulObjInstance,
  uint32_t ulElementNo,
  void* pvBuffer,
  Npx_AsyncObjectDoneCallback pfnDone,
  void* pvDoneCallbackParam);

/*! Asynchronously write of an element or object.
 * Write an object without blocking the caller. The provided data must be stable till pfnDone() is called.
 *
 * \note The caller must ensure that the given buffer can be read exclusively form the requested object.
 * \note The function pfnDone may be called before the function Npx_AsyncWriteObjectElementByHandle() returns.
 * \note If the given function pfnDone points to NULL, no write request is performed at all!
 *
 * \param hObj                [in] Handle to a netPROXY object
 * \param ulObjInstance       [in] Instance of netPROXY object to be written
 * \param ulElementNo         [in] Element number, or ::NPX_ELEMENT_NO_OBJECT_INSTANCE to write complete object instance
 * \param pvBuffer            [in] Buffer that holds the data which should be written to the object.
 * \param pfnDone             [in] Callback to be called after read of object was performed. The result of the call is given within this callback
 * \param pvDoneCallbackParam [in] Callback user parameter of Npx_AsyncObjectDoneCallback() function
 *
 */
void APIENTRY
Npx_AsyncWriteObjectElementByHandle(
  NPX_OBJ_H hObj,
  uint32_t ulObjInstance,
  uint32_t ulElementNo,
  const void* pvBuffer,
  Npx_AsyncObjectDoneCallback pfnDone,
  void* pvDoneCallbackParam);


#ifdef __cplusplus
}
#endif  /* _cplusplus */

#endif /* __NPX_ASYNC_API_H */
