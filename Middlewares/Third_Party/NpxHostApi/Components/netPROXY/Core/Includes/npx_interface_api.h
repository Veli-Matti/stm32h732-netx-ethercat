/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id: npx_interface_api.h 3816 2018-02-28 16:09:11Z dirk $

  Description:
    netPROXY Interface API

  NOTE:
    Do not include this file separate. This file will included in the correct order
    by using netPROXY.h

**************************************************************************************/
#ifndef __NPX_INTERFACE_API_H
#define __NPX_INTERFACE_API_H
/*! \addtogroup npx_sys_functions
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif  /* _cplusplus */

/*! netPROXY interface handle.
 * The handle is used to access a specific netPROXY interface.
 * */
typedef struct NPX_INTERFACE_HANDLE_Ttag* NPX_IF_H;

/*! Create a netPROXY interface.
 *
 * \note The current version of netPROXY server only support one interface on one system.
 *
 * \param hNpx              [in] Handle to netPROXY
 * \param pszInterfaceName  [in] Pointer to name of newly created interface
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_CreateInterface(
  NPX_H hNpx,
  const char* pszInterfaceName);


/*! Delete an interface
 *
 * \note The interface can only be deleted if all Interface handles (::NPX_IF_H) are closed.
 * Also all object handles (::NPX_OBJ_H) have to be closed before calling this function.
 *
 * \param hNpx              [in] handle to netPROXY
 * \param pszInterfaceName  [in] pointer to name of interface to be deleted
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_DeleteInterface(
  NPX_H       hNpx,
  const char* pszInterfaceName);


/*! Enumerate interfaces.
 *
 * \param hNpx                    [in]      Handle to netPROXY
 * \param ulInterfaceIdx          [in]      Interface number to return Name for.
 * \param pszInterfaceNameBuffer  [out]     Pointer to a buffer where the interface name is copy to
 * \param pulBufferLen            [in,out]  Length of the given buffer, respectively the needed/used buffer size
 *                                          to hold the interface name
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_EnumInterfaces(
  NPX_H       hNpx,
  uint32_t    ulInterfaceIdx,
  char*       pszInterfaceNameBuffer,
  uint32_t*   pulBufferLen);


/*! Open an interface handle.
 *
 * \note It is not allowed to use the interface handle in different
 *       contexts (tasks), if the handle must be shared the handle
 *       must be duplicated.
 *
 * \param hNpx              [in] Handle to netPROXY
 * \param pszInterfaceName  [in] Pointer to name of interface to be opened
 * \param phInterface       [in] Pointer to variable to store interface handle to
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_OpenInterfaceHandle(
  NPX_H       hNpx,
  const char* pszInterfaceName,
  NPX_IF_H*   phInterface);


/*! Duplicate an interface handle.
 *
 * Duplicate the given interface handle, by open a new handle. Which can be used in oter contexts.
 *
 * \note It is not allowed to use the interface handle in different
 *       contexts (tasks).
 *
 * \note The duplicated interface handle must also be closed if not longer needed.
 *
 * \param hInterface      [in] Handle to netPROXY interface
 * \param phNewInterface  [in] Pointer to variable to store new netPROXY interface handle to
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_DuplicateInterfaceHandle(
  NPX_IF_H hInterface,
  NPX_IF_H* phNewInterface);

/*! Compare interfaces.
 *
 * Compares the given interfaces if they are pointing to the same interface
 * (Interfaces on the system with the same identifier name).
 *
 * \param hInterfaceA [in] Handle to netPROXY interface
 * \param hInterfaceB [in] Handle to netPROXY interface
 *
 * \return true if both handles are of same netPROXY interface otherwise false
 */
bool APIENTRY
Npx_CompareInterfaceHandles(
  NPX_IF_H hInterfaceA,
  NPX_IF_H hInterfaceB);

/*! Close an interface handle.
 *
 * \note Freeing the same handle twice is not allowed, the function will not check the handle again.
 *       Doing so will invoke undefined behavior!
 *
 * \param hInterface [in] Handle to netPROXY interface
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_CloseInterfaceHandle(
  NPX_IF_H  hInterface);


/*! Get Interface name.
 *
 * Get the name of the given interface name from interface handle.
 *
 * \param hInterface              [in]      Handle to netPROXY interface
 * \param pszInterfaceNameBuffer  [out]     Pointer to a buffer where the interface name is copy to
 * \param pulBufferLen            [in,out]  Length of the given buffer, respectively the needed/used buffer size
 *                                          to hold the interface name
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_GetInterfaceName(
  NPX_IF_H hInterface,
  char* pszInterfaceNameBuffer,
  uint32_t* pulBufferLen);


#ifdef __cplusplus
}
#endif  /* _cplusplus */

/*! @}*/
#endif /* __NPX_INTERFACE_API_H */
