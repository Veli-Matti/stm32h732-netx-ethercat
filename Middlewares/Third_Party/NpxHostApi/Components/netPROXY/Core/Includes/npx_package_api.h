/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id: npx_package_api.h 3816 2018-02-28 16:09:11Z dirk $

  Description:
    netPROXY package handling

  NOTE:
    Do not include this file separate. This file will included in the correct order
    by using netPROXY.h

**************************************************************************************/
#ifndef __NPX_PACKAGE_API_H
#define __NPX_PACKAGE_API_H

#ifdef __cplusplus
extern "C" {
#endif  /* _cplusplus */


/*! netPROXY package handle **/
typedef struct NPX_PACKAGE_HANDLE_Ttag* NPX_PACKAGE_H;

/*! package constructor */
typedef NPX_RESULT (APIENTRY *Npx_PackageConstructorCallback)(
  NPX_IF_H hNpxIf,
  uint32_t ulNpxGroupID,
  const void* pvConfigParameters,
  NPX_PACKAGE_H* phPackageHandle);

/*! netPROXY package configuration structure */
typedef struct NPX_PACKAGE_DESCRIPTION_Ttag
{
  const char* pszPackageName;

  /*! package constructor */
  Npx_PackageConstructorCallback pfnCreate;

} NPX_PACKAGE_DESCRIPTION_T;

/*! Add a package.
 *
 * Install a new package to a dedicated group.
 *
 * \note The returned ::NPX_PACKAGE_H handle can than be used to delete (uninstall)
 *       the package by calling the ::Npx_DeletePackage() function. Or the resource can
 *       be freed without uninstall by calling the ::Npx_DeletePackageHandle() function,
 *       in this case it is impossible to remove the installed package without a power cycle!
 *
 * \param hNpxIf              [in]  Handle to netPROXY interface
 * \param ulNpxGroupID        [in]  netPROXY Group the package will be added to
 * \param ptPkgDesc           [in]  Package description of package to be added
 * \param pvConfigParameters  [in]  Package-specific configuration parameters
 * \param phPackageHandle     [out] Pointer to variable to store package handle to on success
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_AddPackage(
  NPX_IF_H hNpxIf,
  uint32_t ulNpxGroupID,
  const NPX_PACKAGE_DESCRIPTION_T* ptPkgDesc,
  const void* pvConfigParameters,
  NPX_PACKAGE_H* phPackageHandle);

/*! Delete a package.
 *
 * \note Freeing the same handle twice is not allowed, the function will not check the handle again.
 *       Doing so will invoke undefined behavior!
 *
 * \param hPackageHandle package handle
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_DeletePackage(
  NPX_PACKAGE_H hPackageHandle);


/*! package destructor */
typedef NPX_RESULT (APIENTRY *Npx_PackageDestructorCallback)(void* pvRsc);

/*! Create a package handle.
 *
 * The function creates a package handle which is initialized with the parameters
 * and will be returned by package create function ::Npx_AddPackage().
 *
 * \note This function is normal only used inside a package creation context.
 *
 * \param pszPackageName  [in]  Package name
 * \param ulNpxGroupID    [in]  netPROXY group id
 * \param pfnDelete       [in]  Function to be called on ::Npx_DeletePackage() call
 * \param pvRsc           [in]  Pointer to resources; passed as parameter to pfnDelete
 * \param phHandle        [out] Pointer to variable to store handle to
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_CreatePackageHandle(
  const char* pszPackageName,
  uint32_t ulNpxGroupID,
  Npx_PackageDestructorCallback pfnDelete,
  void* pvRsc,
  NPX_PACKAGE_H* phHandle);


/*! Delete a package handle.
 *
 * The function deletes a package handle. See notes of ::Npx_AddPackage() function.
 *
 * \note Freeing the same handle twice is not allowed, the function will not check the handle again.
 *       Doing so will invoke undefined behavior!
 *
 * \param phHandle  [in] package handle
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT APIENTRY
Npx_DeletePackageHandle(
  NPX_PACKAGE_H phHandle);


#ifdef __cplusplus
}
#endif  /* _cplusplus */

#endif /* __NPX_PACKAGE_API_H */
