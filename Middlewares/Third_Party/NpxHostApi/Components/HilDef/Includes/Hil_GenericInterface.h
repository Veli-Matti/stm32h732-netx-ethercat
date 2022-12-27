/**********************************************************************************************************************
                 Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***********************************************************************************************************************
  $Id: Hil_GenericInterface.h 3816 2018-02-28 16:09:11Z dirk $: *//**

  \file Hil_GenericInterface.h
  Hilscher Generic Interface Definition between Application and Component.

  \note This interface is currently under examination, it is possible that the interface will be changed in the future!
        To avoid unexpected conflicts you have to set the definition HIL_GENERICINTERFACE_ENABLE_BETA1_API before
        including this header. The define will be change to the next number, if there is an incompatible change in
        the API. This will be removed on the fist official release.

***********************************************************************************************************************/
#ifndef HIL_GENERICINTERFACE_H_
#define HIL_GENERICINTERFACE_H_

#ifdef HIL_GENERICINTERFACE_ENABLE_BETA2_API

#include "Hil_Packet.h"


/*! Handle of component.
 *
 * This is the generic component handle which must be passed always as first parameter into the component function.
 * The internal implementation may differ from component to component.
 *
 * \note The actual structure definition is component specific. It has to be defined
 *       in a private header, where only the component has access.
 */
typedef struct HIL_GCI_COMPONENT_HANDLE_Ttag* HIL_GCI_COMPONENT_HANDLE_H;

/*! Handle of acyclic data.
 *
 * The handle is instantiated by the component and relates to the specific new data.
 * It has to be passed always to the component data read function to obtain selective the specific data.
 * The internal implementation may differ from component to component.
 *
 * \note The actual structure definition is component specific. It has to be defined
 *       in a private header, where only the component has access.
 *
 */
typedef struct HIL_GCI_ACYCLIC_DATA_HANDLE_Ttag*    HIL_GCI_ACYCLIC_DATA_HANDLE_H;

/*! Handle of Application.
 *
 * The handle is instantiated by the application and must be passed always as first parameter into the application function.
 * The internal structure implementation is defined by the application.

 * \note The actual structure definition is application specific. It has to be defined
 *       in a private header, where only the application has access.
 */
typedef struct HIL_GCI_APPLICATION_HANDLE_Ttag*     HIL_GCI_APPLICATION_HANDLE_H;


/*! \addtogroup HIL_GCI_Configuration Configuration
 *   GCI provides a unique interface to configure a protocol stack.
 *  \{ */

/*! Type name for HIL_GCI_APPLICATION_INTERFACE_Ttag. */
typedef struct HIL_GCI_APPLICATION_INTERFACE_Ttag HIL_GCI_APPLICATION_INTERFACE_T;

/*! Type name for HIL_GCI_COMPONENT_INTERFACE_Ttag. */
typedef struct HIL_GCI_COMPONENT_INTERFACE_Ttag HIL_GCI_COMPONENT_INTERFACE_T;



/*! Component configuration function.
 *
 * The caller will provide its application interface to the callee together with a component-specific configuration structure.
 * On successful component configuration, the application will receive the component interface.
 *
 * \note The function needs to be implemented by every component and is called by the application.
 * \note The component configuration structure is component-specific.
 *
 * \param ptApplication             [in]  Application interface that is used by component.
 * \param ptComponent               [out] Component interface used by application.
 * \param pvComponentConfiguration  [in] Component-specific configuration.
 *
 * \return SUCCESS_HIL_OK in case component is successfully configured, otherwise an error code is returned.
 */
typedef uint32_t (*HIL_GCI_COMPONENT_CONFIGURATION_FN)(
                                                                  const HIL_GCI_APPLICATION_INTERFACE_T*  ptApplication,
                                                                  HIL_GCI_COMPONENT_INTERFACE_T*          ptComponent,
                                                                  void*                                   pvComponentConfiguration
                                                                );

/*!  \} */

/*! \addtogroup HIL_GCI_AcyclicDataHandler Acyclic Data Handler
 * The Acyclic Data Handler is used for the acyclic communication, configuration and diagnostic.
 *  \{ */

/*! Handle new acyclic data.
 *
 * This function handles the given acyclic data from the caller.
 * After function return the data resources can be released by the caller. It is the responsibility of the callee to save the data before return.
 * All requests/responses will be handled over this callback.
 *
 * \note The function needs to be implemented by the component and is called by the application.
 * \note The function shall be called from one context only (IRQ context not allowed).
 * \note The function shall NOT wait for other events (e.g. on network), but may call task synchronization functions (e.g. Mutex, Triple buffer exchange)
 * \note The data available function callback may be called before the function returns.
 * \note The number of supported parallel acyclic data handling depends on the actual implementation, 8 parallel are recommended.
 *       If the number of parallel data handling is exceeded, the function returns with an error code.
 *       Acyclic data which can be handled directly may not be affected.
 *       (e.g. an 'read record' could be refused, but a 'stop communication' is still possible)
 * \note This interface does not support fragmentation of the individual service.
 *       The caller has to ensure to collect all data before this function is called.
 *
 * \param hComponent      [in] Handle of the component.
 * \param ptPacketHeader  [in] Packet header information about the acyclic data in pbData.
 * \param pabData         [in] Pointer to acyclic data buffer with length ptPacketHeader->ulLen.
 *                             \note The content is only valid until the function returns.
 * \return SUCCESS_HIL_OK in case callee is able to handle data, otherwise an error code is returned.
 *
 */
typedef uint32_t (*HIL_GCI_ACYCLIC_DATA_HANDLE_FN)
(
  HIL_GCI_COMPONENT_HANDLE_H    hComponent,
  HIL_PACKET_HEADER_T*          ptPacketHeader,
  uint8_t*                      pabData
);

/*! New acyclic data available callback.
 * All indications/confirmations will be handled over this callback.
 *
 * \note The function needs to be implemented by the application and is called by the component.
 * \note This callback can be called from any context (except IRQ).
 * \note The read data function callback may be called before the function returns.
 * \note The caller has to ensure to collect all data before this function is called.
 * \note The caller has to hold the acyclic data until the callee (application) reads the data completely.
 *
 * \param hApplication    [in] Application handle which was passed during component configuration. (ptApplication->hApplication)
 * \param hAcyclicData    [in] Data handle that relates to the new acyclic data.
 * \param ptPacketHeader  [in] Packet header information about the new data.
 *
 * \return SUCCESS_HIL_OK in case callee accepts the delivery of the new data, otherwise an error code is returned.
 *         \note In error case the application will not read out the data. The component will retry service as long as possible,
 *         retry interval depends on component. When retry is not possible, component will call error callback and enter faulty state.
 */
typedef uint32_t (*HIL_GCI_ACYCLIC_DATA_AVAILABLE_FN)
(
  HIL_GCI_APPLICATION_HANDLE_H    hApplication,
  HIL_GCI_ACYCLIC_DATA_HANDLE_H   hAcyclicData,
  HIL_PACKET_HEADER_T*            ptPacketHeader
);

/*! Read new acyclic data from component.
 *
 * \note The function needs to be implemented by the component and is called by the application.
 * \note The function shall NOT wait for other events (e.g. on network), but may call task synchronization functions (e.g. Mutex, Triple buffer exchange)
 * \note The caller has to provide a proper data buffer to store the new data.
 * \note The function has an iterative property. Thus, the callee has to hold the data until completely read by the caller.
 * \note The function is also called with ulBufferSize = 0. In this case the callee must not write into the data buffer.
 *       Though, the callee can release the data here.
 *
 * \param hAcyclicData [in]   Data handle that relates to the new acyclic data.
 * \param pvBuffer     [out]  Data buffer to store new acyclic data (4 byte aligned).
 * \param ulBufferSize [in]   Size of the data buffer ( 64 <= ulBufferSize <= ptPacketHeader.ulLen ) in Bytes.
 *
 * \return Size in Bytes that has been written into pbBuffer.
 */
typedef uint32_t (*HIL_GCI_ACYCLIC_DATA_READ_FN)
(
  HIL_GCI_ACYCLIC_DATA_HANDLE_H hAcyclicData,
  void*                         pvBuffer,
  uint32_t                      ulBufferSize
);

/*!  \} */

/*! \addtogroup HIL_GCI_CyclicDataHandler Cyclic Data Handler
 *  The Cyclic Data Handler is used for process data exchange.
 *  \{ */

/*! Update provider and consumer data size.
 *
 * The component calls this function when data size of provider and/or consumer has changed.
 *
 * \note The function needs to be implemented by the application and is called by the component.
 *
 * \param hComponent     [in] Handle of the application.
 * \param ulProviderSize [in] Provider size in bytes.
 * \param ulConsumerSize [in] Consumer size in bytes.
 *
 * \return SUCCESS_HIL_OK in case the application accepts data sizes, otherwise at least one data size is not accepted
*/
typedef uint32_t (*HIL_GCI_UPDATE_CONSUMER_PROVIDER_DATA_SIZE_FN)
(
  HIL_GCI_APPLICATION_HANDLE_H hApplication,
  uint32_t ulProviderSize,
  uint32_t ulConsumerSize
);

/*! Update cyclic provider data.
 *
 * The application calls this function when provider data has to be updated.
 *
 * \note The function needs to be implemented by the component and is called by the application.
 * \note This callback can be called from any context (including IRQ).
 *       Thus, the callee takes the responsibility to enforce a context switch.
 *
 * \param hComponent [in] Handle of the component.
 *
 * \return SUCCESS_HIL_OK in case callee accepts the update request, otherwise an error code is returned.
 *         \note  If accepted, the component has to call the done-function after provider data has been updated.
 *                Therefore, the application has not to access provider data until the done-function is called.
*/
typedef uint32_t (*HIL_GCI_CYCLIC_PROVIDER_DATA_UPDATE_FN)
(
  HIL_GCI_COMPONENT_HANDLE_H hComponent
);

/*! Update cyclic provider data done.
 *
 * The component calls this function after provider data has been updated.
 *
 * \note This function has to be implemented by the application and is called by the component.
 *
 * \param hApplication [in] Handle of the application.
 *
 * \return This function has no return code
 *         \note After calling this function, the component must not access the provided buffer
*/
typedef void (*HIL_GCI_CYCLIC_PROVIDER_DATA_UPDATE_DONE_FN)
(
  HIL_GCI_APPLICATION_HANDLE_H hApplication
);

/*! Update cyclic consumer data.
 *
 * The application calls this function when consumer data has to be updated.
 *
 * \note The function needs to be implemented by the component and is called by the application.
 * \note This callback can be called from any context (including IRQ).
 *       Thus, the callee takes the responsibility to enforce a context switch.
 *
 * \param hComponent  [in] Handle of the component.
 *
 * \return SUCCESS_HIL_OK in case callee accepts the update request, otherwise an error code is returned.
 *         \note  If accepted, the component has to call the done-function after consumer data has been updated.
 *                Therefore, the application has not to access consumer data until the done-function is called.
*/
typedef uint32_t (*HIL_GCI_CYCLIC_CONSUMER_DATA_UPDATE_FN)
(
  HIL_GCI_COMPONENT_HANDLE_H hComponent
);

/*! Update cyclic consumer data done.
 *
 * The component calls this function after consumer data has been updated.
 *
 * \note This function has to be implemented by the application and is called by the component.
 *
 * \param hApplication [in] Handle of the application.
 *
 * \return This function has no return code
 *         \note After calling this function, the component must not access the provided buffer
*/
typedef void (*HIL_GCI_CYCLIC_CONSUMER_DATA_UPDATE_DONE_FN)
(
  HIL_GCI_APPLICATION_HANDLE_H hApplication
);

/*! Process SYNC event.
 *
 * The application calls this function when the SYNC event shall be processed.
 *
 * \note The function needs to be implemented by the component and is called by the application.
 *
 * \param hComponent [in] Handle of the component.
 *
 * \return SUCCESS_HIL_OK in case callee accepts the request, otherwise an error code is returned.
 *         \note If accepted, the component has to call the done-function after event has been processed.
*/
typedef uint32_t (*HIL_GCI_PROCESS_SYNC_FN)
(
  HIL_GCI_COMPONENT_HANDLE_H hComponent
);

/*! Process SYNC event done.
 *
 * The component calls this function after SYNC event has been processed.
 *
 * \note This function has to be implemented by the application and is called by the component.
 *
 * \param hApplication [in] Handle of the application.
 *
 * \return This function has no return code
*/
typedef void (*HIL_GCI_PROCESS_SYNC_DONE_FN)
(
  HIL_GCI_APPLICATION_HANDLE_H hApplication
);

/*!  \} */


/*! \addtogroup HIL_GCI_Error Error
 * GCI provides an interface to report errors to application.
 *  \{ */

/*! Report an implementation error.
 *
 * The component calls this function when a critical problem is detected. This includes
 * use case of critical runtime failures and invalid usage of the GCI interface.
 *
 * \note The function needs to be implemented by the application and is called by the component.
 *
 * \param hComponent     [in] Handle of the application.
 * \param ulErrorCode    [in] The error code indicating the problem occured.
*/
typedef void (*HIL_GCI_ERROR_OCCURED_FN)
(
  HIL_GCI_APPLICATION_HANDLE_H hApplication,
  uint32_t ulErrorCode
);

/*!  \} */

/*! \addtogroup HIL_GCI_Configuration
 *  \{ */

/*! The structure defines the command range for acyclic data.
 * During configuration phase the component registers for one or several command ranges.
 *
 * \note This structure is filled with life during the configuration phase by the component.
 */
typedef struct
{
  /*! Starting command number within the command range. */
  uint32_t ulCommandDomain;
  /*! The mask represents the command number filter to determine the membership within a domain.
   * Example: The command range shall be [0x2F30, 0x2F33]
   * The range is determined by the two lower bits. Neglecting the two lower bits is done by Mask = 0xFFFC.
   * After applying the filter (command number & mask), the domain is determined to be Domain = 0x2F30.
   * */
  uint32_t ulCommandMask;
  /*! In case of fragmented service, this flag indicates if service fragment shall be forwarded to component,
   * i.e. fragmentation will be not applied by application.
   * values: true in case fragment shall be forwarded to component, otherwise false.
   * \note Fragment forwarding shall be done in rare cases only. */
  uint8_t bDisableFragmentation;
} HIL_GCI_COMMAND_RANGE_T;

/*! \struct HIL_GCI_APPLICATION_INTERFACE_Ttag
 *  This interface structure is filled by the application and given to the component within the component configuration phase.
 */
struct HIL_GCI_APPLICATION_INTERFACE_Ttag
{
  /*! Application handle. */
  HIL_GCI_APPLICATION_HANDLE_H      hApplication;
  /*! Acyclic Data available callback.
    \note This callback is used to receive indications and confirmations. */
  HIL_GCI_ACYCLIC_DATA_AVAILABLE_FN fnDataAvailable;
  /*! Cyclic data provider data update done callback.
    \note The application will be informed about finished provider data update. */
  HIL_GCI_CYCLIC_PROVIDER_DATA_UPDATE_DONE_FN fnProviderDataUpdateDone;
  /*! Cyclic data consumer data update done callback.
    \note The application will be informed about finished consumer data update. */
  HIL_GCI_CYCLIC_CONSUMER_DATA_UPDATE_DONE_FN fnConsumerDataUpdateDone;
  /*! Update provider and consumer data size callback.
    \note The application will be informed about changed consumer/provider data size. */
  HIL_GCI_UPDATE_CONSUMER_PROVIDER_DATA_SIZE_FN fnUpdateConsumerProviderDataSize;
  /*! SYNC event process done callback. */
  HIL_GCI_PROCESS_SYNC_DONE_FN                  fnSyncProcessDone;
  /*! Error occurred callback. */
  HIL_GCI_ERROR_OCCURED_FN                      fnErrorOccured;
  /*! Pointer to provider data buffer. */
  uint8_t*  pabProviderData;
  /*! Provider data total size in bytes. */
  uint32_t  ulMaxProviderDataSize;
  /*! Pointer to consumer data buffer.
   * \note  The application has to ensure to not change the consumer buffer.
   *        Otherwise inconsistent/invalid data might be observed. */
  uint8_t*  pabConsumerData;
  /*! Consumer data total size in bytes. */
  uint32_t  ulMaxConsumerDataSize;
};

/*! \struct HIL_GCI_COMPONENT_INTERFACE_Ttag
 * This interface structure is filled with life during the configuration phase by the component.
 */
struct HIL_GCI_COMPONENT_INTERFACE_Ttag
{
  /*! Component handle.  */
  HIL_GCI_COMPONENT_HANDLE_H      hComponent;
  /*! Command ranges of interest.
   *  If (ulCommand & ulCommandMask) == ulCommandDomain is valid, the acyclic data shall be handled by this interface. */
  const HIL_GCI_COMMAND_RANGE_T*  ptCommandRange;
  /*! The total amount of different command ranges stored in ptCommandRange. */
  uint32_t                        ulNumOfCommandRanges;
  /*! Acyclic data handle callback. */
  HIL_GCI_ACYCLIC_DATA_HANDLE_FN  fnDataHandler;
  /*! Acyclic data read callback. */
  HIL_GCI_ACYCLIC_DATA_READ_FN    fnDataRead;
  /*! Update cyclic consumer data callback. */
  HIL_GCI_CYCLIC_CONSUMER_DATA_UPDATE_FN fnUpdateConsumerData;
  /*! Update cyclic provider data callback. */
  HIL_GCI_CYCLIC_PROVIDER_DATA_UPDATE_FN fnUpdateProviderData;
  /*! Process SYNC event callback. */
  HIL_GCI_PROCESS_SYNC_FN fnProcessSync;
  /*! Total amount of required remanent data in bytes. */
  uint32_t ulRemanentDataSize;
  /*! The maximum fragmentation data length in bytes. */
  uint32_t ulMaxFragDataSize;
};

/*!  \} */

/*** Following definitions are prototypes which will be moved to another location after approval. ***/
#define HIL_LOAD_REMANENT_DATA_IND                    0x00002F8C
#define HIL_LOAD_REMANENT_DATA_RES                    0x00002F8D

#define HIL_STORE_REMANENT_DATA_IND                   0x00002F8E
#define HIL_STORE_REMANENT_DATA_RES                   0x00002F8F

#define HIL_COMMUNICATION_STATE_IND                   0x00002F90
#define HIL_COMMUNICATION_STATE_RES                   0x00002F91

#define HIL_SET_MASTER_STATUS_IND                     0x00002F92
#define HIL_SET_MASTER_STATUS_RES                     0x00002F93



/******************************************************************************/
/*! \defgroup HIL_GCI_Packets Generic Services
 * @{*/


/******************************************************************************/
/*! \defgroup HIL_LOAD_REMANENT_DATA_IND Load remanent data indication
 *
 * This service is used by the protocol stacks in order to load protocol specific
 * remanent data from the application.
 * This service is only generated once (usually in the startup phase).
 * If the stack is started the first time, the application has no remanent data
 * stored. In this case the response have to be generated anyway, with no error
 * and a data size (abData) of 0. If a error is generated in the response the
 * stack will also start without remanent data.
 *
 * \note Todo Info bzg. FSU und QuickConnect
 * @{*/

/*! Load remanent indication data structure. */
typedef __HIL_PACKED_PRE struct HIL_LOAD_REMANENT_DATA_IND_DATA_Ttag
{
  /*! Unique component identifier HIL_COMPONENT_ID_*. */
  uint32_t  ulComponentId;
} __HIL_PACKED_POST HIL_LOAD_REMANENT_DATA_IND_DATA_T;

/*! Load remanent indication structure. */
typedef __HIL_PACKED_PRE struct HIL_LOAD_REMANENT_DATA_IND_Ttag
{
  HIL_PACKET_HEADER_T               tHead;
  HIL_LOAD_REMANENT_DATA_IND_DATA_T tData;
} __HIL_PACKED_POST HIL_LOAD_REMANENT_DATA_IND_T;

#define HIL_LOAD_REMANENT_DATA_IND_SIZE (sizeof(HIL_LOAD_REMANENT_DATA_IND_DATA_T))


/*! Load remanent response data structure. */
typedef __HIL_PACKED_PRE struct HIL_LOAD_REMANENT_DATA_RES_DATA_Ttag
{
  /*! Unique component identifier HIL_COMPONENT_ID_*. */
  uint32_t  ulComponentId;
  /*! Remanent data buffer. */
  uint8_t   abData[];
} __HIL_PACKED_POST HIL_LOAD_REMANENT_DATA_RES_DATA_T;

/*! Load remanent response structure. */
typedef __HIL_PACKED_PRE struct HIL_LOAD_REMANENT_DATA_RES_Ttag
{
  HIL_PACKET_HEADER_T               tHead;
  HIL_LOAD_REMANENT_DATA_RES_DATA_T tData;
} __HIL_PACKED_POST HIL_LOAD_REMANENT_DATA_RES_T;

#define HIL_LOAD_REMANENT_DATA_RES_SIZE   (sizeof(HIL_LOAD_REMANENT_DATA_RES_DATA_T))


/*! @}*************************************************************************/




/******************************************************************************/
/*! \defgroup HIL_STORE_REMANENT_DATA_IND Store remanent data indication
 *
 * This indication is generated if some data in the protocol stack has been
 * changed, which must be stored remanent.
 * The remanent indication always contain the complete data which must be stored
 * even if only one byte has been changed. It is also possible that the new
 * provided data has no change at all, it is up to the application to consider
 * the wear of the storage device.
 *
 * \note As soon the protocol stack has received the response it assumes that
 *       the data was stored. To avoid unpredictable behavior the response shall
 *       be generated within one second.
 * \note The service will not be send a second time if the first request is not
 *       responded.
 *
 * @{*/

/*! Store remanent indication data structure. */
typedef __HIL_PACKED_PRE struct HIL_STORE_REMANENT_DATA_IND_DATA_Ttag
{
  /*! Unique component identifier HIL_COMPONENT_ID_*. */
  uint32_t  ulComponentId;
  /*! Remanent data buffer. */
  uint8_t   abData[];
} __HIL_PACKED_POST HIL_STORE_REMANENT_DATA_IND_DATA_T;

/*! Store remanent indication structure. */
typedef __HIL_PACKED_PRE struct HIL_STORE_REMANENT_DATA_IND_Ttag
{
  HIL_PACKET_HEADER_T                 tHead;
  HIL_STORE_REMANENT_DATA_IND_DATA_T  tData;
} __HIL_PACKED_POST HIL_STORE_REMANENT_DATA_IND_T;

#define HIL_STORE_REMANENT_DATA_IND_SIZE (sizeof(HIL_STORE_REMANENT_DATA_IND_DATA_T))


/*! Store remanent response data structure. */
typedef __HIL_PACKED_PRE struct HIL_STORE_REMANENT_DATA_RES_DATA_Ttag
{
  /*! Unique component identifier HIL_COMPONENT_ID_*. */
  uint32_t  ulComponentId;
} __HIL_PACKED_POST HIL_STORE_REMANENT_DATA_RES_DATA_T;

/*! Store remanent response structure. */
typedef __HIL_PACKED_PRE struct HIL_STORE_REMANENT_DATA_RES_Ttag
{
  HIL_PACKET_HEADER_T                 tHead;
  HIL_STORE_REMANENT_DATA_RES_DATA_T  tData;
} __HIL_PACKED_POST HIL_STORE_REMANENT_DATA_RES_T;

#define HIL_STORE_REMANENT_DATA_RES_SIZE   (sizeof(HIL_STORE_REMANENT_DATA_RES_DATA_T))

/*! @}*************************************************************************/




/******************************************************************************/
/*! \defgroup HIL_COMMUNICATION_STATE_IND Communication Status indication
 *
 * This service provides a basic but general status of the stack. Note that
 * the meaning of the fields is still protocol specific.
 *
 * @{*/

/*! Communication status indication data structure. */
typedef __HIL_PACKED_PRE struct HIL_COMMUNICATION_STATE_IND_DATA_Ttag
{
  /*! Communication state.
   * Information about the current network state.
   *  - HIL_COMM_STATE_NOT_CONFIGURED = No valid configuration / no network communication
   *  - HIL_COMM_STATE_STOP           = Communication stopped by the user application or
   *                                    an error during the network communication
   *  - HIL_COMM_STATE_IDLE           = Protocol stack is configured but has not reached operating state.
   *                                    No cyclic data exchanged on the bus system
   *  - HIL_COMM_STATE_OPERATE        = Network communication is active, data exchange on the network
   *                                    is activated
   * \note Depending on field bus protocol, not all of the defined states are always available or may have
   *       different meanings.*/
  uint32_t ulCommunicationState;

  /*! Protocol Stack specific error code. */
  uint32_t ulError;
  /*! Error Counter.
   * Total number of errors detected by protocol stack since start, respectively since reset.
   * The protocol stack counts all sorts of errors in this field no matter if they were network
   * related or caused internally. */
  uint32_t ulErrorCounter;

  /*! Communicating Status.
   * This flag is set if the protocol stack has successfully opened a connection
   * to at least ONE of the configured network slaves (for master protocol stacks),
   * respectively has an open connection to the network master (for slave protocol stacks).
   * If cleared, the input data should not be evaluated, because it may be invalid,
   * old or both.
   *  - 0 = No communication (No connection).
   *  - 1 = Communicating (At least one connection).
   * \note Even if the stack reports "Communicating" the process data may not be valid. E.g.
   *       Open Modbus reports "Communicating" when a TCP connection is established, because
   *       this system works message based, no data must be transmitted. In addition most protocols
   *       provide a dedicated validation information together with the process data.
   * \note On slaves systems its highly recommended that the process data which is generated by the
   *       application is updated even if the connection is not active. */
  uint8_t  bCommunicating;
} __HIL_PACKED_POST HIL_COMMUNICATION_STATE_IND_DATA_T;

/*! Communication status indication structure. */
typedef __HIL_PACKED_PRE struct HIL_COMMUNICATION_STATE_IND_Ttag
{
  HIL_PACKET_HEADER_T                 tHead;
  HIL_COMMUNICATION_STATE_IND_DATA_T  tData;
} __HIL_PACKED_POST HIL_COMMUNICATION_STATE_IND_T;

#define HIL_COMMUNICATION_STATE_IND_SIZE  (sizeof(HIL_COMMUNICATION_STATE_IND_DATA_T))

/*! Communication status response structure. */
typedef HIL_EMPTY_PACKET_T      HIL_COMMUNICATION_STATE_RES_T;

#define HIL_COMMUNICATION_STATE_RES_SIZE  (0)

/*! @}*************************************************************************/




/******************************************************************************/

/*! \defgroup HIL_SET_MASTER_STATUS_IND Master status indication
 *
 * The master status indication service offers common information over all
 * configured slaves for all master protocol stacks. This indication will be
 * generated by master stacks if the status of one or more devices has changed.
 *
 * \note This service is only available for master protocols.
 * \note The Common Slave State field ulSlaveState in the DPM will not be
 *       transfered, therefore the Application must extract the information
 *       from the fields ulNumOfConfigSlaves, ulNumOfActiveSlaves and
 *       ulNumOfDiagSlaves. If there is at least one slave missing or one of
 *       the slaves has pending diagnostic information, the status is changed
 *       from HIL_SLAVE_STATE_OK to HIL_SLAVE_STATE_FAILED.
 *
 * @{*/

/*! Master status indication data structure. */
typedef __HIL_PACKED_PRE struct HIL_SET_MASTER_STATUS_IND_DATA_Ttag
{
  /*! Number of configured slave devices in the master configuration. */
  uint32_t ulNumOfConfigSlaves;
  /*! Number of activated slave devices, the master has an open connection to. */
  uint32_t ulNumOfActiveSlaves;
  /*! Number of slaves reporting diagnostic issues. */
  uint32_t ulNumOfDiagSlaves;
} __HIL_PACKED_POST HIL_SET_MASTER_STATUS_IND_DATA_T;

/*! Master status indication structure. */
typedef __HIL_PACKED_PRE struct HIL_SET_MASTER_STATUS_IND_Ttag
{
  HIL_PACKET_HEADER_T               tHead;
  HIL_SET_MASTER_STATUS_IND_DATA_T  tData;
} __HIL_PACKED_POST HIL_SET_MASTER_STATUS_IND_T;

#define HIL_SET_MASTER_STATUS_IND_SIZE (sizeof(HIL_SET_MASTER_STATUS_IND_DATA_T))


/*! Master status response structure. */
typedef HIL_EMPTY_PACKET_T      HIL_SET_MASTER_STATUS_RES_T;

#define HIL_SET_MASTER_STATUS_RES_SIZE   (0)
/*! @}*************************************************************************/




/*! @}*************************************************************************/


#endif /* HIL_GENERICINTERFACE_ENABLE_BETA2_API */

#endif /* HIL_GENERICINTERFACE_H_ */
