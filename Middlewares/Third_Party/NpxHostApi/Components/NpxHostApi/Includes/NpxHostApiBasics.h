/**********************************************************************************************************************
                 Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***********************************************************************************************************************
  $Id: NpxHostApiBasics.h 3816 2018-02-28 16:09:11Z dirk $ *//**

  \file NpxHostApiBasics.h
  \brief Basic services of the netPROXY host functionality when accessed via DPM.

  \note Exclusion of Liability for this demo software:\n
    The following software is intended for and must only be used for reference and in an evaluation laboratory
    environment. It is provided without charge and is subject to alterations. There is no warranty for the software,
    to the extent permitted by applicable law. Except when otherwise stated in writing the copyright holders and/or
    other parties provide the software "as is" without warranty of any kind, either expressed or implied.\n
    Please refer to the Agreement in \ref disclaimer, provided  together with this file! By installing or otherwise
    using the software, you accept the terms of this Agreement. If you do not agree to the terms of this Agreement,
    then do not install or use the Software!

***********************************************************************************************************************/
#ifndef __NPX_HOST_API_BASICS_H
#define __NPX_HOST_API_BASICS_H

#if defined(__cplusplus)
extern "C" {
#endif


/*! \addtogroup npxhost_basic_doc
@{*/

/* netPROXY host API specific error codes */
#define NPX_HOST_ERR_TIMEOUT              0xC0B50220  /* service timeout exceeded */
#define NPX_HOST_ERR_FIFO_FULL            0xC0B50221  /* service request FIFO full */
#define NPX_HOST_ERR_MAX_OUTSTANDING      0xC0B50222  /* maximum of outstanding services reached */


/* access to the object as a whole instead of access to an element of the object */
#define NPX_HOST_ALL_ELEMENTS             0xFFFFFFFFUL


/* configuration parameters structure version */
#define NPX_HOST_CONFIG_VERSION_V2        2


/* number of interfaces */
#define NPX_HOST_NUM_INTERFACES_MIN       1
#define NPX_HOST_NUM_INTERFACES_MAX       10
#define NPX_HOST_NUM_INTERFACES_DEFAULT   1

/* send FIFO length, given in packets */
#define NPX_HOST_FIFO_LENGTH_MIN          1
#define NPX_HOST_FIFO_LENGTH_MAX          64
#define NPX_HOST_FIFO_LENGTH_DEFAULT      16

/* number of outstanding services */
#define NPX_HOST_OUTSTANDING_MIN          1
#define NPX_HOST_OUTSTANDING_MAX          64
#define NPX_HOST_OUTSTANDING_DEFAULT      16


/* interface default name and name template (replace the digits by the actual values) */
#define NPX_HOST_INTERFACE_NAME_DEFAULT   "Board0/Channel0"


/* buffer size for retrieving an object description */
#define NPX_HOST_BUFSIZE_OBJECT_DESCRIPTION 1540

/* buffer size for retrieving the data of an object or object element */
#define NPX_HOST_BUFSIZE_OBJECT_ELEMENT     1540



/* netPROXY host driver handle */
typedef void* NPX_HOST_DRIVER_H;

/* netPROXY host interface handle */
typedef void* NPX_HOST_IF_H;


/* API startup parameters passed to NpxHostApi_Init() */
typedef struct NPX_HOST_CONFIG_Ttag
{
  uint32_t ulParamVersion;        /* parameter structure version: see NPX_HOST_CONFIG_VERSION */
  uint32_t ulMaxInterfaces;       /* maximum number of interfaces (one for each communication channel) */
  uint32_t ulMaxOutstanding;      /* maximum number of outstanding services per interface */
  uint32_t ulFifoLength;          /* send FIFO length, given in packets */
} NPX_HOST_CONFIG_T;


/* object element description */
typedef struct NPX_HOST_ELEMENT_DESCRIPTION_Ttag
{
  char*    pszElementName;        /* name of the element, NUL-terminated ASCII string */
  uint32_t ulReserved;            /* currently unused, set to zero */
  uint16_t usElementType;         /* netPROXY element type (see NPX_TYPE_xxx definitions) */
  uint16_t usElementByteSize;     /* data size of the element, given in bytes */
} NPX_HOST_ELEMENT_DESCRIPTION_T;


/* object description */
typedef struct NPX_HOST_OBJECT_DESCRIPTION_tag
{
  uint32_t                        ulObjectId;                                  /* object ID */
  char*                           pszObjectName;                               /* pointer to the name of the object */
  uint32_t                        ulNumberOfElements;                          /* number of element descriptions */
  NPX_HOST_ELEMENT_DESCRIPTION_T* patElementDescriptions;                      /* pointer to the array of element descriptions */
} NPX_HOST_OBJECT_DESCRIPTION_T;


/* object description buffer */
typedef struct NPX_HOST_OBJECT_DESCRIPTION_BUFFER_Ttag
{
  uint32_t                        ulObjectId;                                  /* object ID */
  char*                           pszObjectName;                               /* pointer to the name of the object */
  uint32_t                        ulNumberOfElements;                          /* number of element descriptions */
  NPX_HOST_ELEMENT_DESCRIPTION_T* patElementDescriptions;                      /* pointer to the array of element descriptions */
  uint8_t                         abData[NPX_HOST_BUFSIZE_OBJECT_DESCRIPTION]; /* buffer for the element descriptions followed by the object name and the element names */
} NPX_HOST_OBJECT_DESCRIPTION_BUFFER_T;


/* convention for the sequence of data in an object description buffer assuming ulNumberOfElements = N:
       patElementDescriptions --> element description 0
+---------------------------------- pszElementName
|                                   ulReserved
|                                   usElementType
|                                   usElementByteSize
|                                         :
|                                         :
|                                 element description (N-1)
|   +------------------------------ pszElementName
|   |                               ulReserved
|   |                               usElementType
|   |                               usElementByteSize
|   |  pszObjectName -----------> object name (NUL-terminated)
+-------------------------------> element name 0 (NUL-terminated)
    |                                     :
    |                                     :
    +---------------------------> element name (N-1) (NUL-terminated)

  consequently the locations of the items in an NPX_HOST_OBJECT_DESCRIPTION_BUFFER_T are as follows:
    tObjectDescriptionBuffer.patElementDescriptions = (NPX_HOST_ELEMENT_DESCRIPTION_T*) tObjectDescriptionBuffer.abData;
    tObjectDescriptionBuffer.pszObjectName          = (char*) (tObjectDescriptionBuffer.patElementDescriptions + tObjectDescriptionBuffer.ulNumberOfElements);
    patElementDescriptions[i].pszElementName        = pszObjectName + strlen(pszObjectName) + 1 + sum(j=0..i-1, strlen(patElementDescriptions[j].pszElementName) + 1);
*/



/** Notification callback for update notifications on an object or object element.
 * Used with NpxHost_RegisterUpdateNotification() and NpxHost_RegisterUpdateNotificationAsync().
 *
 * \param pvIndicationParam       [in]  user-defined callback parameter supplied when invoking the register service
 * \param ulGroupId               [in]  group ID supplied when invoking the service
 * \param ulObjectId              [in]  object ID supplied when invoking the service
 * \param ulObjectInstance        [in]  object instance number supplied when invoking the service
 * \param ulElementNumber         [in]  object element number supplied when invoking the service
 * \param pabData                 [in]  buffer containing the updated data of the object or object element (valid only until the end of the callback)
 */
typedef void (APIENTRY* NPX_HOST_UPDATE_NOTIFICATION_CBK_T)(
  void*      pvIndicationParam,
  uint32_t   ulGroupId,
  uint32_t   ulObjectId,
  uint32_t   ulObjectInstance,
  uint32_t   ulElementNumber,
  uint8_t*   pabData);



/** Indication callback for reads on a behavior object or object element.
 * Used with NpxHost_AddBehaviorObject() and NpxHost_AddBehaviorObjectAsync().
 *
 * \param pvIndicationParam       [in]    user-defined callback parameter supplied when invoking the add-object service
 * \param ulGroupId               [in]    group ID supplied when invoking the service
 * \param ulObjectId              [in]    object ID supplied when invoking the service
 * \param ulObjectInstance        [in]    object instance number supplied when invoking the service
 * \param ulElementNumber         [in]    object element number supplied when invoking the service
 * \param pabData                 [in]    buffer for the read data of the object or object element (valid only until the end of the callback)
 * \param pulDataLen              [inout] in: length of the read data buffer, out: length of the data actually read
 * \param pulNpxResult            [out]   netPROXY error code (used in the response packet, SUCCESS_NET_PROXY_OK on success, a netPROXY error code otherwise)
 */
typedef void (APIENTRY* NPX_HOST_BEHAVIOR_OBJECT_READ_CBK_T)(
  void*       pvIndicationParam,
  uint32_t    ulGroupId,
  uint32_t    ulObjectId,
  uint32_t    ulObjectInstance,
  uint32_t    ulElementNumber,
  uint8_t*    pabData,
  uint32_t*   pulDataLen,
  uint32_t*   pulNpxResult);



/** Indication callback for writes on a behavior object or object element.
 * Used with NpxHost_AddBehaviorObject() and NpxHost_AddBehaviorObjectAsync().
 *
 * \param pvIndicationParam       [in]    user-defined callback parameter supplied when invoking the add-object service
 * \param ulGroupId               [in]    group ID supplied when invoking the service
 * \param ulObjectId              [in]    object ID supplied when invoking the service
 * \param ulObjectInstance        [in]    object instance number supplied when invoking the service
 * \param ulElementNumber         [in]    object element number supplied when invoking the service
 * \param pabData                 [in]    buffer for the write data of the object or object element (valid only until the end of the callback)
 * \param ulDataLen               [in]    length of the data to write
 * \param pulNpxResult            [out]   netPROXY error code (used in the response packet, SUCCESS_NET_PROXY_OK on success, a netPROXY error code otherwise)
 */
typedef void (APIENTRY* NPX_HOST_BEHAVIOR_OBJECT_WRITE_CBK_T)(
  void*       pvIndicationParam,
  uint32_t    ulGroupId,
  uint32_t    ulObjectId,
  uint32_t    ulObjectInstance,
  uint32_t    ulElementNumber,
  uint8_t*    pabData,
  uint32_t    ulDataLen,
  uint32_t*   pulNpxResult);



/** Initialize the netPROXY host driver.
 *
 * This function initialize the netPROXY host driver and must be called during
 * system initialization. This function has to be called before any other function
 * of this driver is called. The netPROXY host driver is a singleton and can only
 * initialized once in a system.
 *
 * \note To clean up and free all allocated resources occupied by netPROXY host driver
 *       The NpxHost_Reset() function can be called.
 *
 * \param ptConfig                [in] address of the startup configuration parameters
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_Init(const NPX_HOST_CONFIG_T* ptConfig);


/** Reset the netPROXY host driver.
 *
 * This function can be used gracefull shutdown of the driver e.g. at system shutdown time.
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_Reset(void);


/** Animate the netPROXY host driver.
 *
 * \note This function has to be called from cyclicly from a task context.
 *
 */
void APIENTRY NpxHost_Cyclic(void);

/*************************************************************************************/

/** Obtain a handle for the netPROXY host driver.
 *
 * \param phNpxDriver             [out] buffer for the netPROXY host interface driver handle
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_Open(NPX_HOST_DRIVER_H* phNpxDriver);


/** Release the handle for the netPROXY host driver.
 *
 *
 * \param hNpxDriver              [in] handle for the netPROXY host interface driver
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_Close(NPX_HOST_DRIVER_H hNpxDriver);

/*************************************************************************************/

/** Enumerate the available netPROXY host interfaces.
 *
 * \param hNpxDriver              [in]    handle for the netPROXY host interface driver
 * \param ulInterfaceIndex        [in]    index of the interface the name of which is to be retrieved
 * \param pszInterfaceNameBuffer  [in]    name of the interface to be opened
 * \param pulBufferLen            [inout] in: length of the buffer to receive the interface name, out: length of the name returned in the buffer
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_EnumInterfaces(
  NPX_HOST_DRIVER_H hNpxDriver,
  uint32_t          ulInterfaceIndex,
  char*             pszInterfaceNameBuffer,
  uint32_t*         pulBufferLen);

/*************************************************************************************/

/** Open a netPROXY host interface.
 *
 * \param hNpxDriver              [in]  handle for the netPROXY host interface driver
 * \param pszInterfaceName        [in]  name of the netPROXY interface (NUL-terminated ASCII string, see remark on NPX_HOST_INTERFACE_NAME_DEFAULT)
 * \param phInterface             [out] buffer for the interface handle
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_OpenInterface(
  NPX_HOST_DRIVER_H  hNpxDriver,
  const char*        pszInterfaceName,
  NPX_HOST_IF_H*     phInterface);


/** Close the netPROXY host interface referenced by the given interface handle.
 *
 * \param hInterface              [in]  handle for the netPROXY host interface
 *
 * \return NPX_OK on success, a netPROXY error code otherwise
 */
uint32_t APIENTRY NpxHost_CloseInterface(
  NPX_HOST_IF_H hInterface);


/*! @}*/

#ifdef __cplusplus
}
#endif  /* _cplusplus */

#endif /* __NPX_HOST_API_BASICS_H */
