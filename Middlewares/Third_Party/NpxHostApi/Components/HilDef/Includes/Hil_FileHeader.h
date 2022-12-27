/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: Hil_FileHeader.h 3816 2018-02-28 16:09:11Z dirk $:

  Description:
    Definition for the universal Hilscher File Header

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2010-03-23  File created.

**************************************************************************************/


#ifndef __HILFILEHEADER__H
#define __HILFILEHEADER__H

#include <stdint.h>
#include "Hil_Compiler.h"

#ifdef __HIL_PRAGMA_PACK_ENABLE
  #pragma __HIL_PRAGMA_PACK_1(HIL_FILEHEADER)
#endif

/*****************************************************************************/
/*! \file HilFileHeader.h
*  Definition for the universal Hilscher File Header                         */
/*****************************************************************************/

#define HIL_FILE_HEADER_MODULE_COOKIE       0x4D584E2E
#define HIL_FILE_HEADER_DATABASE_COOKIE     0x44584E2E
#define HIL_FILE_HEADER_LICENSE_COOKIE      0x4C584E2E
#define HIL_FILE_HEADER_BINARY_COOKIE       0x42584E2E

#define HIL_FILE_HEADER_FIRMWARE_COOKIE     0xF8BEAF00
#define HIL_FILE_HEADER_FIRMWARE_8_COOKIE   0xF8BEAF08
#define HIL_FILE_HEADER_FIRMWARE_16_COOKIE  0xF8BEAF16
#define HIL_FILE_HEADER_FIRMWARE_32_COOKIE  0xF8BEAF32

/* Valid Hilscher file extensions */
#define HIL_FILE_EXTENSION_FIRMWARE         ".NXF"
#define HIL_FILE_EXTENSION_MODULE           ".NXM"
#define HIL_FILE_EXTENSION_LICENSE          ".NXL"
#define HIL_FILE_EXTENSION_DATABASE         ".NXD"
#define HIL_FILE_EXTENSION_BINARY           ".NXB"

/*****************************************************************************/
/*! File structure preceeding every Hilscher generated file                  */
/*****************************************************************************/
/*-------------------------------------------------------*/
/* 64 Byte DEFAULT FILE HEADER                           */
/*-------------------------------------------------------*/
typedef __HIL_PACKED_PRE struct HIL_FILE_DEFAULT_HEADER_Ttag
{
  uint32_t   ulMagCookie;                  /**< Magic cookie                                   */
  uint32_t   tReserved[15];                /**< Reserved area                                  */
} __HIL_PACKED_POST HIL_FILE_DEFAULT_HEADER_T, *PHIL_FILE_DEFAULT_HEADER_T;

#define HIL_FILE_COMMON_HEADER_VERSION_1    0x00010000 /**< High Word = Major, Low Word = Minor Version */
#define HIL_FILE_COMMON_HEADER_VERSION_2    0x00020000 /**< High Word = Major, Low Word = Minor Version */

/*-------------------------------------------------------*/
/* 64 Byte COMMON FILE HEADER                            */
/*-------------------------------------------------------*/
typedef __HIL_PACKED_PRE struct HIL_FILE_COMMON_HEADER_Ttag
{
  uint32_t   ulHeaderVersion;              /**< Header version (over all)                      */
  uint32_t   ulHeaderLength;               /**< Header length (over all)                       */
  uint32_t   ulFileSize;                   /**< File Size in Bytes                             */
  uint32_t   ulDataStartOffset;            /**< Start of the binary data                       */
  uint32_t   ulTagListOffset;              /**< Start of the tag list                          */
  uint32_t   aulMD5[4];                    /**< MD5 checksum                                   */
  uint16_t   usManufacturer;               /**< Hardware Manufacturer identification           */
  uint16_t   usReserved;                   /**< reserved                                       */
  uint32_t   aulReserved[5];               /**< reserved / unused                              */
  uint32_t   ulChksum;                     /**< CRC-32 checksum (common header)                */
} __HIL_PACKED_POST HIL_FILE_COMMON_HEADER_T, *PHIL_FILE_COMMON_HEADER_T;

/*-------------------------------------------------------*/
/* FIRMWARE FILE HEADER                                  */
/*-------------------------------------------------------*/
/* FIRMWARE file specific header */
typedef __HIL_PACKED_PRE struct HIL_FILE_FIRMWARE_HEADER_Ttag
{
  HIL_FILE_DEFAULT_HEADER_T tDefaultHeader;       /**< Default File Header                            */
  HIL_FILE_COMMON_HEADER_T  tCommonHeader;        /**< Common File Header                             */
  uint16_t                  usDeviceClass;        /**< netX Device Class                              */
  uint8_t                   bHwCompatibility;     /**< Hardware Compatibility ID                      */
  uint16_t                  ausHwOptions[4];      /**< Hardware Assembly Option                       */
  uint32_t                  ulLicenseFlags1;      /**< NetX License Flags 1                           */
  uint32_t                  ulLicenseFlags2;      /**< NetX License Flags 2                           */
  uint16_t                  usNetXLicenseID;      /**< NetX License ID                                */
  uint16_t                  usNetXLicenseFlags;   /**< NetX License Flags                             */
  uint32_t                  aulSwRevision[3];     /**< Software Revision (major, minor, build)        */
  uint32_t                  ulSwNumber;           /**< Software Number                                */
  uint16_t                  usCommunicationClass; /**< Communication Class                            */
  uint16_t                  usProtocolClass;      /**< Protocol Class                                 */
  uint8_t                   abName[64];           /**< Readable Name                                  */
  uint32_t                  aulDBVersion[2];      /**< Version of DB structure                        */
  uint32_t                  ulSDN;                /**< SDN                                            */
} __HIL_PACKED_POST HIL_FILE_FIRMWARE_HEADER_T, *PHIL_FILE_FIRMWARE_HEADER_T;

/*-------------------------------------------------------*/
/* MODULE FILE HEADER                                    */
/*-------------------------------------------------------*/
/* MODULE file specific header */
typedef __HIL_PACKED_PRE struct HIL_FILE_MODULE_HEADER_Ttag
{
  HIL_FILE_DEFAULT_HEADER_T tDefaultHeader;       /**< Default File Header                            */
  HIL_FILE_COMMON_HEADER_T  tCommonHeader;        /**< Common File Header                             */
  uint16_t                  usDeviceClass;        /**< netX Device Class                              */
  uint8_t                   bHwCompatibility;     /**< Hardware Compatibility ID                      */
  uint16_t                  ausHwOptions[4];      /**< Hardware Assembly Option                       */
  uint32_t                  ulLicenseFlags1;      /**< NetX License Flags 1                           */
  uint32_t                  ulLicenseFlags2;      /**< NetX License Flags 2                           */
  uint16_t                  usNetXLicenseID;      /**< NetX License ID                                */
  uint16_t                  usNetXLicenseFlags;   /**< NetX License Flags                             */
  uint32_t                  aulSwRevision[3];     /**< Software Revision (major, minor, build)        */
  uint32_t                  ulSwNumber;           /**< Software Number                                */
  uint16_t                  usCommunicationClass; /**< Communication Class                            */
  uint16_t                  usProtocolClass;      /**< Protocol Class                                 */
  uint8_t                   abName[64];           /**< Readable Name                                  */
  uint32_t                  aulDBVersion[2];      /**< Version of DB structure                        */
  uint32_t                  ulSDN;                /**< SDN                                            */
} __HIL_PACKED_POST HIL_FILE_MODULE_HEADER_T, *PHIL_FILE_MODULE_HEADER_T;

/*-------------------------------------------------------*/
/* DATABASE / CONFIGURATION FILE HEADER                  */
/*-------------------------------------------------------*/
/* DATABASE / CONFIGURATION file specific header */
typedef __HIL_PACKED_PRE struct HIL_FILE_DATABASE_HEADER_Ttag
{
  HIL_FILE_DEFAULT_HEADER_T tDefaultHeader;       /**< Default File Header                            */
  HIL_FILE_COMMON_HEADER_T  tCommonHeader;        /**< Common File Header                             */
  uint32_t                  aulDBVersion[2];      /**< Version of DB structure                        */
} __HIL_PACKED_POST HIL_FILE_DATABASE_HEADER_T, *PHIL_FILE_DATABASE_HEADER_T;


/*-------------------------------------------------------*/
/* LICENSE FILE HEADER                                   */
/*-------------------------------------------------------*/
/* LICENSE file specific header */

#define LICENSE_CHIPTYPE_NETX500   1            /* ARM code for netX500  */
#define LICENSE_CHIPTYPE_NETX100   2            /* ARM code for netX100  */
#define LICENSE_CHIPTYPE_NETX50    3            /* ARM code for netX50   */
#define LICENSE_CHIPTYPE_NETX51    4            /* ARM code for netX51   */
#define LICENSE_CHIPTYPE_NETX52    5            /* ARM code for netX52   */
#define LICENSE_CHIPTYPE_XPEC500   0x40         /* XPEC code for netX500 */
#define LICENSE_CHIPTYPE_XPEC100   0x41         /* XPEC code for netX100 */
#define LICENSE_CHIPTYPE_XPEC50    0x42         /* XPEC code for netX50  */
#define LICENSE_CHIPTYPE_XPEC51    0x43         /* XPEC code for netX51  */
#define LICENSE_CHIPTYPE_XPEC52    0x44         /* XPEC code for netX52  */

typedef __HIL_PACKED_PRE struct HIL_FILE_LICENSE_HEADER_Ttag
{
  HIL_FILE_DEFAULT_HEADER_T tDefaultHeader;       /**< Default File Header                            */
  HIL_FILE_COMMON_HEADER_T  tCommonHeader;        /**< Common File Header                             */
  uint32_t                  ulChipType;           /**< 1 = netX500, 2=netX100, 3=netX50, 0x40=xpec500, 0x41=xpec100, 0x42=xpec50 */
  uint32_t                  ulManufacturer;       /**< Manufacturer identification                    */
  uint32_t                  ulDeviceNr;           /**< Device number                                  */
  uint32_t                  ulSerialNr;           /**< Serial number                                  */
  uint32_t                  ulLicenseFlags1;      /**< License flags 1                                */
  uint32_t                  ulLicenseFlags2;      /**< License flags 2                                */
  uint32_t                  ulNetXLicense;        /**< netX license flags <<16 | netX license ID      */
  uint32_t                  ulXcUnit;             /**< Number of XC Unit the update will be performed */
  uint32_t                  aulReserved[8];       /**< reserved = {0,0,0,0,0,0,0,0,0};                */
} __HIL_PACKED_POST HIL_FILE_LICENSE_HEADER_T, *PHIL_FILE_LICENSE_HEADER_T;

/*-------------------------------------------------------*/
/* BINARY FILE HEADER                                    */
/*-------------------------------------------------------*/
/* BINARY file specific header */
typedef __HIL_PACKED_PRE struct HIL_FILE_BINARY_HEADER_Ttag
{
  HIL_FILE_DEFAULT_HEADER_T tDefaultHeader;       /**< Default File Header                            */
  HIL_FILE_COMMON_HEADER_T  tCommonHeader;        /**< Common File Header                             */
} __HIL_PACKED_POST HIL_FILE_BINARY_HEADER_T, *PHIL_FILE_BINARY_HEADER_T;

#ifdef __HIL_PRAGMA_PACK_ENABLE
  #pragma __HIL_PRAGMA_UNPACK_1(HIL_FILEHEADER)
#endif

#endif /*  __HILFILEHEADER__H */
