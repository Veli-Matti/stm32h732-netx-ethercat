/**************************************************************************************
Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
$Id: NpxPck_Hif_Results.h 3816 2018-02-28 16:09:11Z dirk $:

Description:
  Result definitions for netPROXY Package HIF
**************************************************************************************/

#ifndef __NPXPACKAGE_HIF_RESULTS_H
#define __NPXPACKAGE_HIF_RESULTS_H

#include<stdint.h>

/////////////////////////////////////////////////////////////////////////////////////
// netPROXY HIF Package
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: ERR_NPXPACKAGE_HIF_STARTUP_PARAMETER_VERSION_INVALID
//
// MessageText:
//
// Startup parameter version is invalid.
//
#define ERR_NPXPACKAGE_HIF_STARTUP_PARAMETER_VERSION_INVALID ((uint32_t)0xC0C20001L)

//
// MessageId: ERR_NPXPACKAGE_HIF_INVALID_FUNCTION_PARAMETER
//
// MessageText:
//
// Invalid parameter passed to function.
//
#define ERR_NPXPACKAGE_HIF_INVALID_FUNCTION_PARAMETER ((uint32_t)0xC0C20002L)

//
// MessageId: ERR_NPXPACKAGE_HIF_RESOURCE_NOT_INITIALIZED
//
// MessageText:
//
// Resource not initialized.
//
#define ERR_NPXPACKAGE_HIF_RESOURCE_NOT_INITIALIZED ((uint32_t)0xC0C20003L)

//
// MessageId: ERR_NPXPACKAGE_HIF_DUPLICATE_RESOURCE
//
// MessageText:
//
// Duplicate resource.
//
#define ERR_NPXPACKAGE_HIF_DUPLICATE_RESOURCE ((uint32_t)0xC0C20004L)

//
// MessageId: ERR_NPXPACKAGE_HIF_NO_FREE_RESOURCE
//
// MessageText:
//
// No free resource available.
//
#define ERR_NPXPACKAGE_HIF_NO_FREE_RESOURCE ((uint32_t)0xC0C20005L)

//
// MessageId: ERR_NPXPACKAGE_HIF_INTERFACE_NOT_FOUND
//
// MessageText:
//
// Interface not found.
//
#define ERR_NPXPACKAGE_HIF_INTERFACE_NOT_FOUND ((uint32_t)0xC0C20006L)

//
// MessageId: ERR_NPXPACKAGE_HIF_CREATE_MUTEX
//
// MessageText:
//
// Failed to create Mutex.
//
#define ERR_NPXPACKAGE_HIF_CREATE_MUTEX  ((uint32_t)0xC0C20007L)

//
// MessageId: ERR_NPXPACKAGE_HIF_TRIGGER_CONFIGURATION_INVALID
//
// MessageText:
//
// Trigger configuration invalid.
//
#define ERR_NPXPACKAGE_HIF_TRIGGER_CONFIGURATION_INVALID ((uint32_t)0xC0C20008L)

//
// MessageId: ERR_NPXPACKAGE_HIF_MAPPING_EXCEEDS_BUFFER
//
// MessageText:
//
// Mapped entry exceeds buffer.
//
#define ERR_NPXPACKAGE_HIF_MAPPING_EXCEEDS_BUFFER ((uint32_t)0xC0C20009L)

//
// MessageId: ERR_NPXPACKAGE_HIF_NO_VALID_MAPPING
//
// MessageText:
//
// No valid mapping configured.
//
#define ERR_NPXPACKAGE_HIF_NO_VALID_MAPPING ((uint32_t)0xC0C2000AL)

//
// MessageId: ERR_NPXPACKAGE_HIF_MAPPING_ENTRY_NOT_FOUND
//
// MessageText:
//
// Mapping entry not found.
//
#define ERR_NPXPACKAGE_HIF_MAPPING_ENTRY_NOT_FOUND ((uint32_t)0xC0C2000BL)

//
// MessageId: ERR_NPXPACKAGE_HIF_DATA_BLOCK_CONFIGURATION_INVALID
//
// MessageText:
//
// Configuration for data block is invalid.
//
#define ERR_NPXPACKAGE_HIF_DATA_BLOCK_CONFIGURATION_INVALID ((uint32_t)0xC0C2000CL)

//
// MessageId: ERR_NPXPACKAGE_HIF_DATA_IMAGE_EXCEEDS_BUFFER_SIZE
//
// MessageText:
//
// Data image size exceeds buffer size.
//
#define ERR_NPXPACKAGE_HIF_DATA_IMAGE_EXCEEDS_BUFFER_SIZE ((uint32_t)0xC0C2000DL)

//
// MessageId: ERR_NPXPACKAGE_HIF_BUFFER_POINTER_INVALID
//
// MessageText:
//
// Buffer pointer invalid.
//
#define ERR_NPXPACKAGE_HIF_BUFFER_POINTER_INVALID ((uint32_t)0xC0C2000EL)

//
// MessageId: ERR_NPXPACKAGE_HIF_INVALID_DPM_CHANNEL_CONFIGURED
//
// MessageText:
//
// Invalid dual-port-memory channel configured.
//
#define ERR_NPXPACKAGE_HIF_INVALID_DPM_CHANNEL_CONFIGURED ((uint32_t)0xC0C2000FL)

//
// MessageId: ERR_NPXPACKAGE_HIF_HANDSHAKE_CONFIGURATION_INVALID
//
// MessageText:
//
// Handshake configuration invalid.
//
#define ERR_NPXPACKAGE_HIF_HANDSHAKE_CONFIGURATION_INVALID ((uint32_t)0xC0C20010L)

//
// MessageId: ERR_NPXPACKAGE_HIF_CREATE_THREAD
//
// MessageText:
//
// Failed to create thread.
//
#define ERR_NPXPACKAGE_HIF_CREATE_THREAD ((uint32_t)0xC0C20011L)

//
// MessageId: ERR_NPXPACKAGE_HIF_NO_CONFIGURATION_PARAMETER
//
// MessageText:
//
// No configuration.
//
#define ERR_NPXPACKAGE_HIF_NO_CONFIGURATION_PARAMETER ((uint32_t)0xC0C20012L)

//
// MessageId: ERR_NPXPACKAGE_HIF_MISSING_WORKER_HANDLES
//
// MessageText:
//
// Worker handles are not configured.
//
#define ERR_NPXPACKAGE_HIF_MISSING_WORKER_HANDLES ((uint32_t)0xC0C20013L)

//
// MessageId: ERR_NPXPACKAGE_HIF_MISSING_FIRMWARE_IDENTIFICATION
//
// MessageText:
//
// Firmware identification is not configured.
//
#define ERR_NPXPACKAGE_HIF_MISSING_FIRMWARE_IDENTIFICATION ((uint32_t)0xC0C20014L)

//
// MessageId: ERR_NPXPACKAGE_HIF_CREATE_TIMER
//
// MessageText:
//
// Failed to create timer.
//
#define ERR_NPXPACKAGE_HIF_CREATE_TIMER  ((uint32_t)0xC0C20015L)

//
// MessageId: ERR_NPXPACKAGE_HIF_OBJECT_LIST_ALREADY_CONFIGURED
//
// MessageText:
//
// Object list is already configured.
//
#define ERR_NPXPACKAGE_HIF_OBJECT_LIST_ALREADY_CONFIGURED ((uint32_t)0xC0C20016L)

//
// MessageId: ERR_NPXPACKAGE_HIF_OBJECT_SIZE_ECXEEDS_MAX_SIZE
//
// MessageText:
//
// Object size exceeds maximum size.
//
#define ERR_NPXPACKAGE_HIF_OBJECT_SIZE_ECXEEDS_MAX_SIZE ((uint32_t)0xC0C20017L)

//
// MessageId: ERR_NPXPACKAGE_HIF_MAXIMUM_MAPPING_OBJECT_ECXEEDED
//
// MessageText:
//
// Number of mapped object exceeds number of possible objects.
//
#define ERR_NPXPACKAGE_HIF_MAXIMUM_MAPPING_OBJECT_ECXEEDED ((uint32_t)0xC0C20018L)

//
// MessageId: ERR_NPXPACKAGE_HIF_SIZE_OF_OBJECT_NOT_FIT_IN_BUFFER
//
// MessageText:
//
// Size of object exceeds size of buffer.
//
#define ERR_NPXPACKAGE_HIF_SIZE_OF_OBJECT_NOT_FIT_IN_BUFFER ((uint32_t)0xC0C20019L)

//
// MessageId: ERR_NPXPACKAGE_HIF_STRING_NOT_FIT_IN_BUFFER
//
// MessageText:
//
// String does not fit in buffer.
//
#define ERR_NPXPACKAGE_HIF_STRING_NOT_FIT_IN_BUFFER ((uint32_t)0xC0C2001AL)

//
// MessageId: ERR_NPXPACKAGE_HIF_FRAGMENTATION_BUFFER_SIZE_CONFIG
//
// MessageText:
//
// Invalid configuration for fragmentation buffer size.
//
#define ERR_NPXPACKAGE_HIF_FRAGMENTATION_BUFFER_SIZE_CONFIG ((uint32_t)0xC0C2001BL)

//
// MessageId: ERR_NPXPACKAGE_HIF_FRAGMENTATION_TIMEOUT_CONFIG
//
// MessageText:
//
// Invalid configuration for fragmentation timeout supervision.
//
#define ERR_NPXPACKAGE_HIF_FRAGMENTATION_TIMEOUT_CONFIG ((uint32_t)0xC0C2001CL)

//
// MessageId: ERR_NPXPACKAGE_HIF_OBJECT_SIZE_DOES_NOT_MATCH
//
// MessageText:
//
// Object size does not match.
//
#define ERR_NPXPACKAGE_HIF_OBJECT_SIZE_DOES_NOT_MATCH ((uint32_t)0xC0C2001DL)

//
// MessageId: ERR_NPXPACKAGE_HIF_BEHAVIOROBJECT_RESPONSE_TIMEOUT_CONFIG
//
// MessageText:
//
// Invalid configuration for response timeout supervision in the behavior object.
//
#define ERR_NPXPACKAGE_HIF_BEHAVIOROBJECT_RESPONSE_TIMEOUT_CONFIG ((uint32_t)0xC0C2001EL)

//
// MessageId: ERR_NPXPACKAGE_HIF_BEHAVIOROBJECT_TIMEOUT
//
// MessageText:
//
// Timeout has occurred while waiting for response to read or write the behavior object indication.
//
#define ERR_NPXPACKAGE_HIF_BEHAVIOROBJECT_TIMEOUT ((uint32_t)0xC0C2001FL)

//
// MessageId: ERR_NPXPACKAGE_HIF_BEHAVIOROBJECT_ACCESS_LOCKED
//
// MessageText:
//
// Access to the behavior object is temporarily locked by another application.
//
#define ERR_NPXPACKAGE_HIF_BEHAVIOROBJECT_ACCESS_LOCKED ((uint32_t)0xC0C20020L)

//
// MessageId: ERR_NPXPACKAGE_HIF_FRAGMENTATION_SIMULTANEOUS_SERVICES_CONFIG
//
// MessageText:
//
// Invalid configuration for simultaneous fragmentation services.
//
#define ERR_NPXPACKAGE_HIF_FRAGMENTATION_SIMULTANEOUS_SERVICES_CONFIG ((uint32_t)0xC0C20021L)

#endif  /* __NPXPACKAGE_HIF_RESULTS_H */
