/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id: npx_extensions_api.h 3816 2018-02-28 16:09:11Z dirk $

  Description:
    netPROXY extensions modules

  NOTE:
    Do not include this file separate. This file will included in the correct order
    by using netPROXY.h

**************************************************************************************/
#ifndef __NPX_EXTENSIONS_API_H
#define __NPX_EXTENSIONS_API_H

#ifdef __cplusplus
extern "C" {
#endif  /* _cplusplus */

/*! Install the netPROXY Event Log objects.
 *
 * The function will install the following objects into the group 0 of the given interface.
 * - ::NPX_OBJ_ID_NETPROXY_EVENT_LOG (0x00002000) Object representation of the event log function ::Npx_GetEventLogEntry()
 *
 * \note The eventlog API is independently working also if the objects are not installed.
 *
 * \param hNpxIf [in] Handle to interface, where the object should be installed
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT Npx_InstallEventLog(
  NPX_IF_H hNpxIf);


/*! Install the netPROXY Object list objects.
 *
 * The installed object ::NPX_OBJ_ID_NETPROXY_OBJECT_LIST (0x00001000) can be used to literate over all installed
 * object entities within the interface.
 *
 * \param hNpxIf [in] Handle to interface, where the object should be installed
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT Npx_InstallObjectList(
  NPX_IF_H hNpxIf);


/*! Get a previous stored object description strings.
 *
 * This is a reference implementation for handling object names in heap memory.
 * This function can be used for the pfnGetObjectDescriptionStr parameter of the ::NPX_CORE_CONFIG_T configuration.
 *
 * \note pvUserParameter is not used and can be set to NULL.
 *
 * \param pvUserParameter [in]  given user parameter
 * \param ulObjectID      [in]  Object ID of the requested string
 * \param ulElement       [in]  Element ID of requested string. 0xFFFFFFFF (::NPX_ELEMENT_NO_OBJECT_INSTANCE)
 *                              request the object name
 * \param szStringBuffer  [out] Pointer to a buffer which can hold up to ::NPX_MAX_DESCRIPTION_STRING_LEN Bytes.
 *
 * */
void Npx_GetObjectDescriptionString_HeapBased_Callback(
    void*       pvUserParameter,
    uint32_t    ulObjectID,
    uint32_t    ulElement,
    char*       szStringBuffer
);


/*! Stores the given string from a object description .
 *
 * This is a reference implementation for handling object names in heap memory.
 * This function can be used for the pfnSetObjectDescriptionStr parameter of the ::NPX_CORE_CONFIG_T configuration.
 *
 * \note pvUserParameter is not used and can be set to NULL.
 *
 * \param pvUserParameter [in]  given user parameter
 * \param ulObjectID      [in]  Object ID of the requested string
 * \param ulElement       [in]  Element ID of requested string. 0xFFFFFFFF (::NPX_ELEMENT_NO_OBJECT_INSTANCE)
 *                              request the object name
 * \param szStringBuffer  [in]  Pointer to a buffer with the new string.
 *
 * */
void Npx_SetObjectDescriptionString_HeapBased_Callback(
    void*       pvUserParameter,
    uint32_t    ulObjectID,
    uint32_t    ulElement,
    const char* szStringBuffer
);


/*! Delete all strings for a specific object.
 *
 * This is a reference implementation for handling object names in heap memory.
 * This function can be used for the pfnDelObjectDescriptionStr parameter of the ::NPX_CORE_CONFIG_T configuration.
 *
 * \note pvUserParameter is not used and can be set to NULL.
 *
 * \param pvUserParameter [in]  given user parameter
 * \param ulObjectID      [in]  Object ID of the requested string
 * \param szStringBuffer  [in]  Pointer to a buffer with the new string.
 *
 * */
void Npx_DelObjectDescriptionStrings_HeapBased_Callback(
    void*       pvUserParameter,
    uint32_t    ulObjectID
);


#ifdef __cplusplus
}
#endif  /* _cplusplus */

#endif /* __NPX_EXTENSIONS_API_H */

