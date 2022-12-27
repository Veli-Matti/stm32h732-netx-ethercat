/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id: netPROXY_Results.h 3816 2018-02-28 16:09:11Z dirk $:

  Description:
    Result codes for netPROXY core runtime.

    The first 512 (0x0000-0x01FF) result codes are reserved for netPROXY V1. Message
    definitions can be found down below.

**************************************************************************************/
#ifndef __NET_PROXY_RESULTS_H
#define __NET_PROXY_RESULTS_H

#include <stdint.h>

//
// MessageId: SUCCESS_NET_PROXY_OK
//
// MessageText:
//
// Operation succeeded.
//
#define SUCCESS_NET_PROXY_OK             ((uint32_t)0x00000000L)

//
// MessageId: ERR_NET_PROXY_UNEXPECTED
//
// MessageText:
//
// Unexpected failure.
//
#define ERR_NET_PROXY_UNEXPECTED         ((uint32_t)0xC0B50200L)

//
// MessageId: ERR_NET_PROXY_OUT_OF_MEMORY
//
// MessageText:
//
// Out of memory.
//
#define ERR_NET_PROXY_OUT_OF_MEMORY      ((uint32_t)0xC0B50201L)

//
// MessageId: ERR_NET_PROXY_RESOURCE_CREATE_FAILED
//
// MessageText:
//
// Out of resources, the creation of a resource has failed.
//
#define ERR_NET_PROXY_RESOURCE_CREATE_FAILED ((uint32_t)0xC0B50202L)

//
// MessageId: ERR_NET_PROXY_INVALID_HANDLE
//
// MessageText:
//
// Invalid handle.
//
#define ERR_NET_PROXY_INVALID_HANDLE     ((uint32_t)0xC0B50203L)

//
// MessageId: ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER
//
// MessageText:
//
// The function call contains invalid parameters.
//
#define ERR_NET_PROXY_INVALID_FUNCTION_PARAMETER ((uint32_t)0xC0B50204L)

//
// MessageId: ERR_NET_PROXY_FUNCTION_PARAMETER_OUT_OF_RANGE
//
// MessageText:
//
// A given function parameters is out of range.
//
#define ERR_NET_PROXY_FUNCTION_PARAMETER_OUT_OF_RANGE ((uint32_t)0xC0B50205L)

//
// MessageId: ERR_NET_PROXY_INITIALIZE_FAILED
//
// MessageText:
//
// Initialization failed.
//
#define ERR_NET_PROXY_INITIALIZE_FAILED  ((uint32_t)0xC0B50206L)

//
// MessageId: ERR_NET_PROXY_ALREADY_INITIALIZE
//
// MessageText:
//
// Already initialized.
//
#define ERR_NET_PROXY_ALREADY_INITIALIZE ((uint32_t)0xC0B50207L)

//
// MessageId: ERR_NET_PROXY_INTERACE_ALREADY_EXISTS
//
// MessageText:
//
// Interface already exists.
//
#define ERR_NET_PROXY_INTERACE_ALREADY_EXISTS ((uint32_t)0xC0B50208L)

//
// MessageId: ERR_NET_PROXY_INTERFACE_DOES_NOT_EXIST
//
// MessageText:
//
// Interface does not exist.
//
#define ERR_NET_PROXY_INTERFACE_DOES_NOT_EXIST ((uint32_t)0xC0B50209L)

//
// MessageId: ERR_NET_PROXY_INTERFACE_IS_IN_USE
//
// MessageText:
//
// Interface is in use.
//
#define ERR_NET_PROXY_INTERFACE_IS_IN_USE ((uint32_t)0xC0B5020AL)

//
// MessageId: ERR_NET_PROXY_INTERFACE_HANDLE_IS_IN_USE
//
// MessageText:
//
// Interface handle is in use.
//
#define ERR_NET_PROXY_INTERFACE_HANDLE_IS_IN_USE ((uint32_t)0xC0B5020BL)

//
// MessageId: ERR_NET_PROXY_OBJECT_ALREADY_EXISTS
//
// MessageText:
//
// Object already exists.
//
#define ERR_NET_PROXY_OBJECT_ALREADY_EXISTS ((uint32_t)0xC0B5020CL)

//
// MessageId: ERR_NET_PROXY_OBJECT_DOES_NOT_EXIST
//
// MessageText:
//
// Object does not exist.
//
#define ERR_NET_PROXY_OBJECT_DOES_NOT_EXIST ((uint32_t)0xC0B5020DL)

//
// MessageId: ERR_NET_PROXY_OBJECT_IS_IN_USE
//
// MessageText:
//
// Object is in use.
//
#define ERR_NET_PROXY_OBJECT_IS_IN_USE   ((uint32_t)0xC0B5020EL)

//
// MessageId: ERR_NET_PROXY_OBJECT_DESCRIPTION_ALREADY_EXISTS
//
// MessageText:
//
// Object description already exists.
//
#define ERR_NET_PROXY_OBJECT_DESCRIPTION_ALREADY_EXISTS ((uint32_t)0xC0B5020FL)

//
// MessageId: ERR_NET_PROXY_OBJECT_DESCRIPTION_DOES_NOT_EXIST
//
// MessageText:
//
// Object description does not exist.
//
#define ERR_NET_PROXY_OBJECT_DESCRIPTION_DOES_NOT_EXIST ((uint32_t)0xC0B50210L)

//
// MessageId: ERR_NET_PROXY_OBJECT_DESCRIPTION_IS_IN_USE
//
// MessageText:
//
// Object description is in use.
//
#define ERR_NET_PROXY_OBJECT_DESCRIPTION_IS_IN_USE ((uint32_t)0xC0B50211L)

//
// MessageId: ERR_NET_PROXY_ELEMENT_DOES_NOT_EXIST
//
// MessageText:
//
// Element does not exist.
//
#define ERR_NET_PROXY_ELEMENT_DOES_NOT_EXIST ((uint32_t)0xC0B50212L)

//
// MessageId: ERR_NET_PROXY_ELEMENT_READ_ACCESS_DENIED
//
// MessageText:
//
// Element/Object could not be read, access was denied. Refer object documentation for more information.
//
#define ERR_NET_PROXY_ELEMENT_READ_ACCESS_DENIED ((uint32_t)0xC0B50213L)

//
// MessageId: ERR_NET_PROXY_ELEMENT_WRITE_ACCESS_DENIED
//
// MessageText:
//
// Element/Object could not be written, access was denied. Refer object documentation for more information.
//
#define ERR_NET_PROXY_ELEMENT_WRITE_ACCESS_DENIED ((uint32_t)0xC0B50214L)

//
// MessageId: ERR_NET_PROXY_INSTANCE_DOES_NOT_EXIST
//
// MessageText:
//
// Instance does not exist.
//
#define ERR_NET_PROXY_INSTANCE_DOES_NOT_EXIST ((uint32_t)0xC0B50215L)

//
// MessageId: ERR_NET_PROXY_ELEMENT_READ_NOT_POSSIBLE_INVALID_STATE
//
// MessageText:
//
// Element/Object could not be read, invalid state. Refer object documentation for more information.
//
#define ERR_NET_PROXY_ELEMENT_READ_NOT_POSSIBLE_INVALID_STATE ((uint32_t)0xC0B50216L)

//
// MessageId: ERR_NET_PROXY_ELEMENT_WRITE_NOT_POSSIBLE_INVALID_STATE
//
// MessageText:
//
// Element/Object could not be written, invalid state. Refer object documentation for more information.
//
#define ERR_NET_PROXY_ELEMENT_WRITE_NOT_POSSIBLE_INVALID_STATE ((uint32_t)0xC0B50217L)

//
// MessageId: ERR_NET_PROXY_ELEMENT_READ_ONLY
//
// MessageText:
//
// Element/Object could not be written, object/element is read only.
//
#define ERR_NET_PROXY_ELEMENT_READ_ONLY  ((uint32_t)0xC0B50218L)

//
// MessageId: INFO_NET_PROXY_NOT_IMPLEMENTED
//
// MessageText:
//
// The requested functionality is not implemented.
//
#define INFO_NET_PROXY_NOT_IMPLEMENTED   ((uint32_t)0x40B50219L)

//
// MessageId: ERR_NET_PROXY_PACKAGE_ALREADY_EXISTS
//
// MessageText:
//
// Package already exists.
//
#define ERR_NET_PROXY_PACKAGE_ALREADY_EXISTS ((uint32_t)0xC0B5021AL)

/**************************************************************************************
  netPROXY V1 result codes
**************************************************************************************/

//
// MessageId: 0xC0B50001L (No symbolic name defined)
//
// MessageText:
//
// Element not available.
//


//
// MessageId: 0xC0B50002L (No symbolic name defined)
//
// MessageText:
//
// Instance not available.
//


//
// MessageId: 0xC0B50003L (No symbolic name defined)
//
// MessageText:
//
// Object not available.
//


//
// MessageId: 0xC0B50004L (No symbolic name defined)
//
// MessageText:
//
// Module not available.
//


//
// MessageId: 0xC0B50005L (No symbolic name defined)
//
// MessageText:
//
// Database not available.
//


//
// MessageId: 0xC0B50006L (No symbolic name defined)
//
// MessageText:
//
// The Callback is not registered.
//


//
// MessageId: 0xC0B50007L (No symbolic name defined)
//
// MessageText:
//
// The Modul is already in the Database
//


//
// MessageId: 0xC0B50008L (No symbolic name defined)
//
// MessageText:
//
// The Object is already in the Database
//


//
// MessageId: 0xC0B50009L (No symbolic name defined)
//
// MessageText:
//
// Mutex error.
//


//
// MessageId: 0xC0B5000AL (No symbolic name defined)
//
// MessageText:
//
// Out of Memory.
//


//
// MessageId: 0xC0B5000BL (No symbolic name defined)
//
// MessageText:
//
// Data buffer too small.
//


//
// MessageId: 0x40B5000CL (No symbolic name defined)
//
// MessageText:
//
// Read or write request active.
//


//
// MessageId: 0xC0B5000DL (No symbolic name defined)
//
// MessageText:
//
// Too many acyclic jobs.
//


//
// MessageId: 0xC0B5000EL (No symbolic name defined)
//
// MessageText:
//
// netPROXY Function is not Available.
//


//
// MessageId: 0xC0B5000FL (No symbolic name defined)
//
// MessageText:
//
// There is already one Callback registered on this Object
//


//
// MessageId: 0xC0B50010L (No symbolic name defined)
//
// MessageText:
//
// This Application is already registered
//


//
// MessageId: 0xC0B5001AL (No symbolic name defined)
//
// MessageText:
//
// Name of Database String is to Long.
//


//
// MessageId: 0xC0B5001BL (No symbolic name defined)
//
// MessageText:
//
// netPROXY Initialization Failure.
//


//
// MessageId: 0xC0B5001CL (No symbolic name defined)
//
// MessageText:
//
// No CONFIG.DBM File Found.
//


//
// MessageId: 0xC0B5001DL (No symbolic name defined)
//
// MessageText:
//
// Object Size does not fit to Database Object Size.
//


//
// MessageId: 0xC0B50100L (No symbolic name defined)
//
// MessageText:
//
// Invalid handle.
//


//
// MessageId: 0xC0B50101L (No symbolic name defined)
//
// MessageText:
//
// Object Handle is limited access.
//


//
// MessageId: 0xC0B50102L (No symbolic name defined)
//
// MessageText:
//
// Invalid buffer pointer.
//


//
// MessageId: 0xC0B50103L (No symbolic name defined)
//
// MessageText:
//
// Invalid done callback pointer.
//


//
// MessageId: 0xC0B50104L (No symbolic name defined)
//
// MessageText:
//
// Interface is deletion pending.
//


//
// MessageId: 0xC0B50105L (No symbolic name defined)
//
// MessageText:
//
// Object is deletion pending.
//


//
// MessageId: 0xC0B50106L (No symbolic name defined)
//
// MessageText:
//
// Offset and/or Length invalid.
//


//
// MessageId: 0xC0B50107L (No symbolic name defined)
//
// MessageText:
//
// Interface already exists.
//


//
// MessageId: 0xC0B50108L (No symbolic name defined)
//
// MessageText:
//
// Not enough memory.
//


//
// MessageId: 0xC0B50109L (No symbolic name defined)
//
// MessageText:
//
// Interface does not exist.
//


//
// MessageId: 0xC0B5010AL (No symbolic name defined)
//
// MessageText:
//
// Use count limit reached.
//


//
// MessageId: 0xC0B5010BL (No symbolic name defined)
//
// MessageText:
//
// Use count limit reached.
//


//
// MessageId: 0xC0B5010CL (No symbolic name defined)
//
// MessageText:
//
// Invalid callback pointer.
//


//
// MessageId: 0xC0B5010DL (No symbolic name defined)
//
// MessageText:
//
// Invalid object-ID.
//


//
// MessageId: 0xC0B5010EL (No symbolic name defined)
//
// MessageText:
//
// Number of instances cannot be 0.
//


//
// MessageId: 0xC0B5010FL (No symbolic name defined)
//
// MessageText:
//
// Request/response model not supported on object.
//


//
// MessageId: 0xC0B50110L (No symbolic name defined)
//
// MessageText:
//
// Byte-Offset is not aligned to an element.
//


//
// MessageId: 0xC0B50111L (No symbolic name defined)
//
// MessageText:
//
// Byte-Length is not aligned to an element end.
//


//
// MessageId: 0xC0B50112L (No symbolic name defined)
//
// MessageText:
//
// Scalar element has only one index.
//


//
// MessageId: 0xC0B50113L (No symbolic name defined)
//
// MessageText:
//
// Element Array Index exceeded.
//


//
// MessageId: 0xC0B50114L (No symbolic name defined)
//
// MessageText:
//
// Element Array count exceeded.
//


//
// MessageId: 0xC0B50115L (No symbolic name defined)
//
// MessageText:
//
// Object is busy.
//


//
// MessageId: 0xC0B50116L (No symbolic name defined)
//
// MessageText:
//
// Self reference is not possible.
//


//
// MessageId: 0xC0B50117L (No symbolic name defined)
//
// MessageText:
//
// Referenced object is not available.
//


#endif  /* __NET_PROXY_RESULTS_H */
