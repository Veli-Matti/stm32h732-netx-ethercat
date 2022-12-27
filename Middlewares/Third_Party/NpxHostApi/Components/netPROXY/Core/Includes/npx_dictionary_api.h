/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id: npx_dictionary_api.h 3816 2018-02-28 16:09:11Z dirk $

  Description:
    netPROXY dictionary related functions

  NOTE:
    Do not include this file separate. This file will included in the correct order
    by using netPROXY.h

**************************************************************************************/
#ifndef __NPX_DICTIONARY_API_H
#define __NPX_DICTIONARY_API_H
/*! \addtogroup npx_dir_functions
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif  /* _cplusplus */


/*! Access to all elements of an object instance.
 * This magic number is used to address the whole object instance, instead of a single element.
 * All functions with a 'ulElementNo' parameter will accept this value. **/
#define NPX_ELEMENT_NO_OBJECT_INSTANCE  0xFFFFFFFF

#define NPX_MAX_DESCRIPTION_STRING_LEN  (127+1)

/*! NetPROXY element description.
 * The element description structure is part of the ::NPX_OBJECT_DESCRIPTION_T structure **/
typedef struct
{
  const char*         pszElementName;     /*!< Name of the element **/
  void*               pvReserved;         /*!< Currently unused, set to NULL **/
  NPX_ELEMENT_TYPE_T  tElementType;       /*!< Type of element (ref ::NPX_ELEMENT_TYPE_T) **/
  uint16_t            usElementByteSize;  /*!< Size of the element in bytes **/
} NPX_ELEMENT_DESCRIPTION_T;

/*! NetPROXY object description **/
typedef struct
{
  uint32_t ulObjectID;                                    /*!< Object ID of the object **/
  const char* pszObjectName;                              /*!< Name of the object **/
  uint32_t ulNumberOfElements;                            /*!< Number of element wich this object has **/
  const NPX_ELEMENT_DESCRIPTION_T* patElementDefinitions; /*!< The size of the pointer array is defined by the member ulNumberOfElements **/
} NPX_OBJECT_DESCRIPTION_T;

/*! NetPROXY get element description **/
typedef struct
{
  char                szElementName[NPX_MAX_DESCRIPTION_STRING_LEN];
  NPX_ELEMENT_TYPE_T  tElementType;
  uint16_t            usElementByteSize;
} NPX_GET_ELEMENT_DESCRIPTION_T;


/*! NetPROXY get object description **/
typedef struct
{
  uint32_t ulObjectID;
  char     szObjectName[NPX_MAX_DESCRIPTION_STRING_LEN];
  uint32_t ulNumberOfElements;
} NPX_GET_OBJECT_DESCRIPTION_T;


/*! Add an object description.
 *
 * \param hInterface          [in] Handle to interface
 * \param ptObjectDescription [in] Detailed description of object
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_AddObjectDescription(
  NPX_IF_H hInterface,
  const NPX_OBJECT_DESCRIPTION_T* ptObjectDescription);


/*! Delete an object description.
 *
 * \param hInterface [in] Handle to interface
 * \param ulObjectID [in] Object ID of description to be deleted
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_DeleteObjectDescription(
  NPX_IF_H hInterface,
  uint32_t  ulObjectID);


/*! Get object description
 *
 *  To get an object description fill out ulObjectID
 *  of the NPX_GET_OBJECT_DESCRIPTION_T structure
 *
 * \param hInterface             [in]      Handle to interface
 * \param ptGetObjectDescription [in, out] Get object description structure
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_GetObjectDescription(
  NPX_IF_H hInterface,
  NPX_GET_OBJECT_DESCRIPTION_T* ptGetObjectDescription);


/*! Get element description
 *
 * \param hInterface              [in]  Handle to interface
 * \param ulObjectID              [in]  Object ID of description to be deleted
 * \param ulElementNo             [in]  Element to get its size
 * \param ptGetElementDescription [out] Get element description structure
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_GetElementDescription(
  NPX_IF_H hInterface,
  uint32_t ulObjectID,
  uint32_t ulElementNo,
  NPX_GET_ELEMENT_DESCRIPTION_T* ptGetElementDescription);


/*! Get byte size of an element.
 *
 * \param hInterface  [in] Handle to interface
 * \param ulObjectID  [in] Object ID of description to be deleted
 * \param ulElementNo [in] Element to get its size
 *
 * \return == 0 on error, != 0 size of Element/Object in bytes
 */
uint32_t APIENTRY
Npx_GetElementByteSize(
  NPX_IF_H hInterface,
  uint32_t  ulObjectID,
  uint32_t  ulElementNo);


/*! netPROXY Object entity handle **/
typedef struct NPX_OBJECT_HANDLE_Ttag* NPX_OBJ_H;

/*! netPROXY Object reference **/
typedef struct NPX_OBJECT_Ttag*        NPX_OBJ_PT;


/*! Asynchronous done callback (read/write) */
typedef void (APIENTRY *Npx_AsyncObjectDoneCallback)(
  void* pvDoneCallbackParam,
  NPX_RESULT iResult
);

/*! Asynchronous read callback of an object */
typedef void (APIENTRY *Npx_AsyncReadObjectCallback)(
  void*                       pvCreatorCallbackParam,
  uint32_t                    ulObjInstance,
  uint32_t                    ulElementNo,
  void*                       pvBuffer,
  Npx_AsyncObjectDoneCallback pfnDone,
  void*                       pvDoneCallbackParam
);

/*! Asynchronous write callback of an object */
typedef void (APIENTRY *Npx_AsyncWriteObjectCallback)(
  void*                       pvCreatorCallbackParam,
  NPX_OBJ_PT                  ptObject,
  uint32_t                    ulObjInstance,
  uint32_t                    ulElementNo,
  const void*                 pvBuffer,
  Npx_AsyncObjectDoneCallback pfnDone,
  void*                       pvDoneCallbackParam
);

/*! Number of Instances */
typedef uint32_t (APIENTRY *Npx_NumberOfInstancesCallback)(
  void*                       pvCreatorCallbackParam
);

/*! Free callback of an object, called when object gets deleted */
typedef void (APIENTRY *Npx_FreeObjectCallback)(
    void* pvCreatorCallbackParam
);

/*! NetPROXY object creator block **/
typedef struct NPX_OBJECT_CREATOR_INFO_Ttag
{
  Npx_AsyncReadObjectCallback   pfnReadCallback;
  Npx_AsyncWriteObjectCallback  pfnWriteCallback;
  Npx_NumberOfInstancesCallback pfnNumberOfInstancesCallback;

  Npx_FreeObjectCallback        pfnFreeCallback;

  /*! user parameter for all three call backs */
  void* pvCreatorCallbackParam;
} NPX_OBJECT_CREATOR_INFO_T;


/*! Add an object entity.
 *
 * \param hInterface          [in] Handle to interface
 * \param ulGroupID           [in] Group ID
 * \param ulObjectID          [in] Object ID
 * \param ptCreatorInfo       [in] Callback information for object creation
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_AddObjectEntity(
  NPX_IF_H hInterface,
  uint32_t ulGroupID,
  uint32_t ulObjectID,
  const NPX_OBJECT_CREATOR_INFO_T* ptCreatorInfo);


/*! Add volatile storage object.
 *
 * \param hInterface          [in] Handle to interface
 * \param ulGroupID           [in] Group ID
 * \param ulObjectID          [in] Object ID
 * \param ulNumberOfInstances [in] Number of instances
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_AddVolatileStorageObjectEntity(
    NPX_IF_H hInterface,
    uint32_t ulGroupID,
    uint32_t ulObjectID,
    uint32_t ulNumberOfInstances);


/*! Delete an object.
 *
 * \param hInterface  [in] Handle to interface
 * \param ulGroupID   [in] Group ID
 * \param ulObjectID  [in] Object ID
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_DeleteObjectEntity(
  NPX_IF_H hInterface,
  uint32_t ulGroupID,
  uint32_t ulObjectID);


/*! Open an object handle.
 *
 * \param hInterface  [in]  Handle to interface
 * \param ulGroupID   [in]  Group ID of object to be opened
 * \param ulObjectID  [in]  Object ID of object to be opened
 * \param phObjHandle [out] Pointer to variable to store object handle to
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_OpenObjectHandle(
  NPX_IF_H hInterface,
  uint32_t ulGroupID,
  uint32_t ulObjectID,
  NPX_OBJ_H* phObjHandle);


/*! Close an object handle.
 *
 * \note Freeing the same handle twice is not allowed, the function will not check the handle again.
 *       Doing so will invoke undefined behavior!
 *
 * \param hObjHandle [in] Handle to object to be closed
 */
void APIENTRY
Npx_CloseObjectHandle(
  NPX_OBJ_H hObjHandle);


#ifdef __cplusplus
}
#endif  /* _cplusplus */

/*! @}*/
#endif /* __NPX_DICTIONARY_API_H */
