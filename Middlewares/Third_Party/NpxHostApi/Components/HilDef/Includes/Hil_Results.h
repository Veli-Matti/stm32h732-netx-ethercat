/**************************************************************************************
Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
$Id: Hil_Results.h 3816 2018-02-28 16:09:11Z dirk $:

Description:
  Hil_Results.h
**************************************************************************************/

#ifndef __HIL_RESULTS_H
#define __HIL_RESULTS_H

#include<stdint.h>

/////////////////////////////////////////////////////////////////////////////////////
// Hilscher RESULT definitions
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
// common status codes
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: SUCCESS_HIL_OK
//
// MessageText:
//
//  Operation succeeded.
//
#define SUCCESS_HIL_OK                   ((uint32_t)0x00000000L)

//
// MessageId: ERR_HIL_FAIL
//
// MessageText:
//
//  Common error, detailed error information optionally present in the data area of packet.
//
#define ERR_HIL_FAIL                     ((uint32_t)0xC0000001L)

//
// MessageId: ERR_HIL_UNEXPECTED
//
// MessageText:
//
//  Unexpected failure.
//
#define ERR_HIL_UNEXPECTED               ((uint32_t)0xC0000002L)

//
// MessageId: ERR_HIL_OUTOFMEMORY
//
// MessageText:
//
//  Out of memory.
//
#define ERR_HIL_OUTOFMEMORY              ((uint32_t)0xC0000003L)


/////////////////////////////////////////////////////////////////////////////////////
// Packet related errors
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: ERR_HIL_UNKNOWN_COMMAND
//
// MessageText:
//
//  Unknown Command
//
#define ERR_HIL_UNKNOWN_COMMAND          ((uint32_t)0xC0000004L)

//
// MessageId: ERR_HIL_UNKNOWN_DESTINATION
//
// MessageText:
//
//  Unknown Destination
//
#define ERR_HIL_UNKNOWN_DESTINATION      ((uint32_t)0xC0000005L)

//
// MessageId: ERR_HIL_UNKNOWN_DESTINATION_ID
//
// MessageText:
//
//  Unknown Destination Id
//
#define ERR_HIL_UNKNOWN_DESTINATION_ID   ((uint32_t)0xC0000006L)

//
// MessageId: ERR_HIL_INVALID_PACKET_LEN
//
// MessageText:
//
//  Packet length is invalid.
//
#define ERR_HIL_INVALID_PACKET_LEN       ((uint32_t)0xC0000007L)

//
// MessageId: ERR_HIL_INVALID_EXTENSION
//
// MessageText:
//
//  Invalid Extension in Packet received.
//
#define ERR_HIL_INVALID_EXTENSION        ((uint32_t)0xC0000008L)

//
// MessageId: ERR_HIL_INVALID_PARAMETER
//
// MessageText:
//
//  Invalid Parameter
//
#define ERR_HIL_INVALID_PARAMETER        ((uint32_t)0xC0000009L)

//
// MessageId: ERR_HIL_INVALID_ALIGNMENT
//
// MessageText:
//
//  Invalid alignment.
//
#define ERR_HIL_INVALID_ALIGNMENT        ((uint32_t)0xC000000AL)


//
// MessageId: ERR_HIL_WATCHDOG_TIMEOUT
//
// MessageText:
//
//  Watchdog error occurred.
//
#define ERR_HIL_WATCHDOG_TIMEOUT         ((uint32_t)0xC000000CL)

//
// MessageId: ERR_HIL_INVALID_LIST_TYPE
//
// MessageText:
//
//  List type is invalid.
//
#define ERR_HIL_INVALID_LIST_TYPE        ((uint32_t)0xC000000DL)

//
// MessageId: ERR_HIL_UNKNOWN_HANDLE
//
// MessageText:
//
//  Handle is unknown.
//
#define ERR_HIL_UNKNOWN_HANDLE           ((uint32_t)0xC000000EL)

//
// MessageId: ERR_HIL_PACKET_OUT_OF_SEQ
//
// MessageText:
//
//  A packet index has been not in the expected sequence.
//
#define ERR_HIL_PACKET_OUT_OF_SEQ        ((uint32_t)0xC000000FL)

//
// MessageId: ERR_HIL_PACKET_OUT_OF_MEMORY
//
// MessageText:
//
//  The amount of fragmented data contained the packet sequence has been too large.
//
#define ERR_HIL_PACKET_OUT_OF_MEMORY     ((uint32_t)0xC0000010L)

//
// MessageId: ERR_HIL_QUE_PACKETDONE
//
// MessageText:
//
//  The packet done function has failed.
//
#define ERR_HIL_QUE_PACKETDONE           ((uint32_t)0xC0000011L)

//
// MessageId: ERR_HIL_QUE_SENDPACKET
//
// MessageText:
//
//  The sending of a packet has failed.
//
#define ERR_HIL_QUE_SENDPACKET           ((uint32_t)0xC0000012L)

//
// MessageId: ERR_HIL_POOL_PACKET_GET
//
// MessageText:
//
//  The request of a packet from packet pool has failed.
//
#define ERR_HIL_POOL_PACKET_GET          ((uint32_t)0xC0000013L)

//
// MessageId: ERR_HIL_POOL_PACKET_RELEASE
//
// MessageText:
//
//  The release of a packet to packet pool has failed.
//
#define ERR_HIL_POOL_PACKET_RELEASE      ((uint32_t)0xC0000014L)

//
// MessageId: ERR_HIL_POOL_GET_LOAD
//
// MessageText:
//
//  The get packet pool load function has failed.
//
#define ERR_HIL_POOL_GET_LOAD            ((uint32_t)0xC0000015L)

//
// MessageId: ERR_HIL_QUE_GET_LOAD
//
// MessageText:
//
//  The get queue load function has failed.
//
#define ERR_HIL_QUE_GET_LOAD             ((uint32_t)0xC0000016L)

//
// MessageId: ERR_HIL_QUE_WAITFORPACKET
//
// MessageText:
//
//  The waiting for a packet from queue has failed.
//
#define ERR_HIL_QUE_WAITFORPACKET        ((uint32_t)0xC0000017L)

//
// MessageId: ERR_HIL_QUE_POSTPACKET
//
// MessageText:
//
//  The posting of a packet has failed.
//
#define ERR_HIL_QUE_POSTPACKET           ((uint32_t)0xC0000018L)

//
// MessageId: ERR_HIL_QUE_PEEKPACKET
//
// MessageText:
//
//  The peek of a packet from queue has failed.
//
#define ERR_HIL_QUE_PEEKPACKET           ((uint32_t)0xC0000019L)

//
// MessageId: ERR_HIL_REQUEST_RUNNING
//
// MessageText:
//
//  Request is already running.
//
#define ERR_HIL_REQUEST_RUNNING          ((uint32_t)0xC000001AL)

//
// MessageId: ERR_HIL_CREATE_TIMER
//
// MessageText:
//
//  Creating a timer failed.
//
#define ERR_HIL_CREATE_TIMER             ((uint32_t)0xC000001BL)

//
// MessageId: ERR_HIL_BUFFER_TO_SHORT
//
// MessageText:
//
//  Supplied buffer too short for the data
//
#define ERR_HIL_BUFFER_TOO_SHORT         ((uint32_t)0xC000001CL)

//
// MessageId: ERR_HIL_NAME_ALREADY_EXIST
//
// MessageText:
//
//  Supplied name alreday exists
//
#define ERR_HIL_NAME_ALREADY_EXIST       ((uint32_t)0xC000001DL)


/////////////////////////////////////////////////////////////////////////////////////
// General Protocol Stack Errors
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: ERR_HIL_INIT_FAULT
//
// MessageText:
//
//  General initialization fault.
//
#define ERR_HIL_INIT_FAULT               ((uint32_t)0xC0000100L)

//
// MessageId: ERR_HIL_DATABASE_ACCESS_FAILED
//
// MessageText:
//
//  Database access failure.
//
#define ERR_HIL_DATABASE_ACCESS_FAILED   ((uint32_t)0xC0000101L)

//
// MessageId: ERR_HIL_CIR_MASTER_PARAMETER_FAILED
//
// MessageText:
//
//  Master parameter can not activated at state operate.
//
#define ERR_HIL_CIR_MASTER_PARAMETER_FAILED ((uint32_t)0xC0000102L)

//
// MessageId: ERR_HIL_CIR_SLAVE_PARAMTER_FAILED
//
// MessageText:
//
//  Slave parameter can not activated at state operate.
//
#define ERR_HIL_CIR_SLAVE_PARAMTER_FAILED ((uint32_t)0xC0000103L)

//
// MessageId: ERR_HIL_NOT_CONFIGURED
//
// MessageText:
//
//  Configuration not available
//
#define ERR_HIL_NOT_CONFIGURED           ((uint32_t)0xC0000119L)

//
// MessageId: ERR_HIL_CONFIGURATION_FAULT
//
// MessageText:
//
//  General configuration fault.
//
#define ERR_HIL_CONFIGURATION_FAULT      ((uint32_t)0xC0000120L)

//
// MessageId: ERR_HIL_INCONSISTENT_DATA_SET
//
// MessageText:
//
//  Inconsistent configuration data.
//
#define ERR_HIL_INCONSISTENT_DATA_SET    ((uint32_t)0xC0000121L)

//
// MessageId: ERR_HIL_DATA_SET_MISMATCH
//
// MessageText:
//
//  Configuration data set mismatch.
//
#define ERR_HIL_DATA_SET_MISMATCH        ((uint32_t)0xC0000122L)

//
// MessageId: ERR_HIL_INSUFFICIENT_LICENSE
//
// MessageText:
//
//  Insufficient license.
//
#define ERR_HIL_INSUFFICIENT_LICENSE     ((uint32_t)0xC0000123L)

//
// MessageId: ERR_HIL_PARAMETER_ERROR
//
// MessageText:
//
//  Parameter error.
//
#define ERR_HIL_PARAMETER_ERROR          ((uint32_t)0xC0000124L)

//
// MessageId: ERR_HIL_INVALID_NETWORK_ADDRESS
//
// MessageText:
//
//  Network address invalid.
//
#define ERR_HIL_INVALID_NETWORK_ADDRESS  ((uint32_t)0xC0000125L)

//
// MessageId: ERR_HIL_NO_SECURITY_MEMORY
//
// MessageText:
//
//  Security memory chip missing or broken.
//
#define ERR_HIL_NO_SECURITY_MEMORY       ((uint32_t)0xC0000126L)

//
// MessageId: ERR_HIL_NO_MAC_ADDRESS_AVAILABLE
//
// MessageText:
//
//  no MAC address available.
//
#define ERR_HIL_NO_MAC_ADDRESS_AVAILABLE ((uint32_t)0xC0000127L)

//
// MessageId: ERR_HIL_NETWORK_FAULT
//
// MessageText:
//
//  General communication fault.
//
#define ERR_HIL_NETWORK_FAULT            ((uint32_t)0xC0000140L)

//
// MessageId: ERR_HIL_CONNECTION_CLOSED
//
// MessageText:
//
//  Connection closed.
//
#define ERR_HIL_CONNECTION_CLOSED        ((uint32_t)0xC0000141L)

//
// MessageId: ERR_HIL_CONNECTION_TIMEOUT
//
// MessageText:
//
//  Connection timeout.
//
#define ERR_HIL_CONNECTION_TIMEOUT       ((uint32_t)0xC0000142L)

//
// MessageId: ERR_HIL_LONELY_NETWORK
//
// MessageText:
//
//  Lonely network.
//
#define ERR_HIL_LONELY_NETWORK           ((uint32_t)0xC0000143L)

//
// MessageId: ERR_HIL_DUPLICATE_NODE
//
// MessageText:
//
//  Duplicate network address.
//
#define ERR_HIL_DUPLICATE_NODE           ((uint32_t)0xC0000144L)

//
// MessageId: ERR_HIL_CABLE_DISCONNECT
//
// MessageText:
//
//  Cable disconnected.
//
#define ERR_HIL_CABLE_DISCONNECT         ((uint32_t)0xC0000145L)

//
// MessageId: ERR_HIL_BUS_OFF
//
// MessageText:
//
//  Bus Off flag is set.
//
#define ERR_HIL_BUS_OFF                  ((uint32_t)0xC0000180L)

//
// MessageId: ERR_HIL_CONFIG_LOCK
//
// MessageText:
//
//  Changing configuration is not allowed.
//
#define ERR_HIL_CONFIG_LOCK              ((uint32_t)0xC0000181L)

//
// MessageId: ERR_HIL_APPLICATION_NOT_READY
//
// MessageText:
//
//  Application is not at ready state.
//
#define ERR_HIL_APPLICATION_NOT_READY    ((uint32_t)0xC0000182L)

//
// MessageId: ERR_HIL_RESET_IN_PROCESS
//
// MessageText:
//
//  Application is performing a reset.
//
#define ERR_HIL_RESET_IN_PROCESS         ((uint32_t)0xC0000183L)

//
// MessageId: ERR_HIL_WATCHDOG_TIME_INVALID
//
// MessageText:
//
//  Watchdog time is out of range.
//
#define ERR_HIL_WATCHDOG_TIME_INVALID    ((uint32_t)0xC0000200L)

//
// MessageId: ERR_HIL_APPLICATION_ALREADY_REGISTERED
//
// MessageText:
//
//  Application is already registered.
//
#define ERR_HIL_APPLICATION_ALREADY_REGISTERED ((uint32_t)0xC0000201L)

//
// MessageId: ERR_HIL_NO_APPLICATION_REGISTERED
//
// MessageText:
//
//  No application registered.
//
#define ERR_HIL_NO_APPLICATION_REGISTERED ((uint32_t)0xC0000202L)


/////////////////////////////////////////////////////////////////////////////////////
// General Driver Related Errors
/////////////////////////////////////////////////////////////////////////////////////
//
//  Driver not initialized
//
#define ERR_HIL_INVALID_HANDLE                    ((uint32_t)0xC0001000L)
#define ERR_HIL_UNKNOWN_DEVICE                    ((uint32_t)0xC0001001L)
#define ERR_HIL_RESOURCE_IN_USE                   ((uint32_t)0xC0001002L)
#define ERR_HIL_NO_MORE_RESOURCES                 ((uint32_t)0xC0001003L)

#define ERR_HIL_DRV_OPEN_FAILED                   ((uint32_t)0xC0001004L)
#define ERR_HIL_DRV_INITIALIZATION_FAILED         ((uint32_t)0xC0001005L)
#define ERR_HIL_DRV_NOT_INITIALIZED               ((uint32_t)0xC0001006L)
#define ERR_HIL_DRV_ALREADY_INITIALIZED           ((uint32_t)0xC0001007L)
#define ERR_HIL_CRC                               ((uint32_t)0xC0001008L)

//  Driver resources
#define ERR_HIL_DRV_INVALID_RESOURCE              ((uint32_t)0xC0001010L)
#define ERR_HIL_DRV_INVALID_MEM_RESOURCE          ((uint32_t)0xC0001011L)
#define ERR_HIL_DRV_INVALID_MEM_SIZE              ((uint32_t)0xC0001012L)
#define ERR_HIL_DRV_INVALID_PHYS_MEM_BASE         ((uint32_t)0xC0001013L)
#define ERR_HIL_DRV_INVALID_PHYS_MEM_SIZE         ((uint32_t)0xC0001014L)
#define ERR_HIL_DRV_UNDEFINED_HANDLER             ((uint32_t)0xC0001015L)

//  Driver interrupt handling
#define ERR_HIL_DRV_ILLEGAL_VECTOR_ID             ((uint32_t)0xC0001020L)
#define ERR_HIL_DRV_ILLEGAL_IRQ_MASK              ((uint32_t)0xC0001021L)
#define ERR_HIL_DRV_ILLEGAL_SUBIRQ_MASK           ((uint32_t)0xC0001022L)

//  DPM-Driver specific errors
#define ERR_HIL_DPM_CHANNEL_UNKNOWN               ((uint32_t)0xC0001100L)
#define ERR_HIL_DPM_CHANNEL_INVALID               ((uint32_t)0xC0001101L)
#define ERR_HIL_DPM_CHANNEL_NOT_INITIALIZED       ((uint32_t)0xC0001102L)
#define ERR_HIL_DPM_CHANNEL_ALREADY_INITIALIZED   ((uint32_t)0xC0001103L)
//#define ERR_HIL_DPM_CHANNEL_IN_USE                ((uint32_t)0xC0001104L)

#define ERR_HIL_DPM_CHANNEL_LAYOUT_UNKNOWN        ((uint32_t)0xC0001120L)
#define ERR_HIL_DPM_CHANNEL_SIZE_INVALID          ((uint32_t)0xC0001121L)
#define ERR_HIL_DPM_CHANNEL_SIZE_EXCEEDED         ((uint32_t)0xC0001122L)
#define ERR_HIL_DPM_CHANNEL_TOO_MANY_BLOCKS       ((uint32_t)0xC0001123L)

#define ERR_HIL_DPM_BLOCK_UNKNOWN                 ((uint32_t)0xC0001130L)
#define ERR_HIL_DPM_BLOCK_SIZE_EXCEEDED           ((uint32_t)0xC0001131L)
#define ERR_HIL_DPM_BLOCK_CREATION_FAILED         ((uint32_t)0xC0001132L)
#define ERR_HIL_DPM_BLOCK_OFFSET_INVALID          ((uint32_t)0xC0001133L)

#define ERR_HIL_DPM_CHANNEL_HOST_MBX_FULL         ((uint32_t)0xC0001140L)
#define ERR_HIL_DPM_CHANNEL_SEGMENT_LIMIT         ((uint32_t)0xC0001141L)
#define ERR_HIL_DPM_CHANNEL_SEGMENT_UNUSED        ((uint32_t)0xC0001142L)

#define ERR_HIL_NAME_INVALID                      ((uint32_t)0xC0001143L)
#define ERR_HIL_UNEXPECTED_BLOCK_SIZE             ((uint32_t)0xC0001144L)

/////////////////////////////////////////////////////////////////////////////////////
// General SYSTEM Errors
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: SUCCESS_HIL_FRAGMENTED
//
// MessageText:
//
//  Fragment accepted.
//
#define SUCCESS_HIL_FRAGMENTED           ((uint32_t)0x0000F005L)

//
// MessageId: ERR_HIL_RESET_REQUIRED
//
// MessageText:
//
//  Reset required.
//
#define ERR_HIL_RESET_REQUIRED           ((uint32_t)0xC000F006L)

//
// MessageId: ERR_HIL_EVALUATION_TIME_EXPIRED
//
// MessageText:
//
//  Evaluation time expired. Reset required.
//
#define ERR_HIL_EVALUATION_TIME_EXPIRED  ((uint32_t)0xC000F007L)

/////////////////////////////////////////////////////////////////////////////////////
// User Area
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: SUCCESS_USER_AREA
//
// MessageText:
//
//  User code.
//
#define SUCCESS_USER_AREA                ((uint32_t)0x0FF00000L)

#endif  /* __HIL_RESULTS_H */
