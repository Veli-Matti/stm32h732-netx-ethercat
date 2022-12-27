/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id: npx_types.h 3816 2018-02-28 16:09:11Z dirk $

  Description:
    netPROXY specific type definition

  NOTE:
    Do not include this file separate. This file will included in the correct order
    by using netPROXY.h

**************************************************************************************/
#ifndef __NPX_TYPES_H
#define __NPX_TYPES_H
/*! \addtogroup npx_types
 * @{
 */

#ifndef APIENTRY
#define APIENTRY
#endif

/*! netPROXY uses the standard Hilscher result code data type uint32_t. The netPROXY specific error codes are listed
 * in the netPROXY_Results.h header file */
typedef uint32_t NPX_RESULT;


/*! Element data types enumeration.
 * members of the data type ::NPX_ELEMENT_TYPE_T hold the values of this enumeration. */
enum NPX_ELEMENT_TYPE_Ttag
{
  /*! Unknown, this data type should not be used. */
  NPX_TYPE_UNKNOWN          = 0,

  /*! Boolean, to hold "True" and "False" values.
   * This data type can be only used with the following byte sizes 1 (uint8_t), 2 (uint16_t), 4 (uint32_t) and 8 (uint64_t).
   * The value 0 is 'false' all other values are 'true'  */
  NPX_TYPE_BOOLEAN          = 1,

  /*! Binary data blob, that not belongs to an other type.
   * The byte size of the element can be chosen freely, the data type it defined as uint8[] */
  NPX_TYPE_BINARY           = 2,

  /*! Integer number, without fraction.
   * This data type can be only used with the following byte sizes 1 (int8_t), 2 (int16_t), 4 (int32_t) and 8 (int64_t) */
  NPX_TYPE_INTEGER          = 3,

  /*! Unsigned Integer number, positive without fraction.
   * This data type can be only used with the following byte sizes 1 (uint8_t), 2 (uint16_t), 4 (uint32_t) and 8 (uint64_t) */
  NPX_TYPE_UNSIGNED         = 4,

  /*! Floating point number (IEEE 754).
   * This data type can be only used with the following byte sizes 4 (float) and 8 (double) */
  NPX_TYPE_REAL             = 5,

  /*! C String, must be terminated with zero.
   * Datatype is char[] */
  NPX_TYPE_STRING           = 6,

  /*! NetPROXY object reference.
   * This data type has a fixed byte size of sizeof (::NPX_OBJECT_REFERENCE_T) bytes */
  NPX_TYPE_OBJREF           = 7,

  /*! Element for flags.
   * This data type can be only used with the following byte sizes 1 (uint8_t), 2 (uint16_t), 4 (uint32_t) and 8 (uint64_t) */
  NPX_TYPE_BITFIELD         = 8,

  /*! Enumeration element.
   * This data type can be only used with the following byte sizes 1 (uint8_t), 2 (uint16_t), 4 (uint32_t) and 8 (uint64_t) */
  NPX_TYPE_ENUMERATION      = 9,

  /*! Binary data blob, which contain the information how many bytes are valid.
   * This type is represented by ::NPX_VARIABLE_BINARY_T */
  NPX_TYPE_VARIABLE_BINARY  = 10

};
/*! Element type members will hold one value from the ::NPX_ELEMENT_TYPE_Ttag enumneration. */
typedef uint16_t NPX_ELEMENT_TYPE_T;


/*! netPROXY Object reference.
 * This structure is the related element to enumeration value ::NPX_TYPE_OBJREF */
struct NPX_OBJECT_REFERENCE_Ttag
{
  /*! Group number where the reference is pointing to. */
  uint32_t ulGroupID;
  /*! Object ID where the reference is pointing to. */
  uint32_t ulObjectID;
  /*! Instance number where the reference is pointing to. */
  uint32_t ulInstance;
  /*! Element where the reference is pointing to.
   * When the element has the value ::NPX_ELEMENT_NO_OBJECT_INSTANCE, the hole object is referenced. */
  uint32_t ulElement;
};
typedef struct NPX_OBJECT_REFERENCE_Ttag NPX_OBJECT_REFERENCE_T;


/*! Data elements with a variable binary data size.
 * This structure is the related element to enumeration value ::NPX_TYPE_VARIABLE_BINARY.
 * The buffer size which is needed to read out this element type must be determined with the function
 * Npx_GetElementDescription() or Npx_GetElementByteSize() */
struct NPX_VARIABLE_BINARY_Ttag
{
  uint16_t usValidDataSize;    /*!< Amount of byts which are valid in the member abData */
  uint8_t  abData[];           /*!< Binary data */
};
typedef struct NPX_VARIABLE_BINARY_Ttag NPX_VARIABLE_BINARY_T;


/*! @}*/
#endif /* __NPX_TYPES_H */
