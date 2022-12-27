/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: Hil_DeviceProductionData.h 3816 2018-02-28 16:09:11Z dirk $:

  Description:
    Structure definition for the Device Production Data for the netX90 and netX400.

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2017-09-04  File created.

**************************************************************************************/
#ifndef __HIL_DEVICEPRODUCTIONDATA_H
#define __HIL_DEVICEPRODUCTIONDATA_H

#include <stdint.h>

typedef struct HIL_PRODUCT_DATA_LLICENSE_FLAGS_Ttag
{
  uint32_t  ulLicenseId;            /*!< netX license ID/Flags */
  uint32_t  ulLicenseFlags1;        /*!< netX license flags 1 */
  uint32_t  ulLicenseFlags2;        /*!< netX license flags 2 */
} HIL_PRODUCT_DATA_LICENSE_FLAGS_T;

/*------------------------------------------------------------*/
/*! Basic device data.
 * Those information may be different to the OEM values       */
/*------------------------------------------------------------*/
typedef struct HIL_PRODUCT_DATA_BASIC_DEVICE_DATA_Ttag
{
  /*! Manufacturer ID.
   * 0 = Undefined; 1 - 255 = Hilscher GmbH; 256 - x = OEM
   * \note All numbers are managed and assigned by Hilscher GmbH. */
  uint16_t  usManufacturer;

  /*! Device classification number.
   * Possible values are defined in the dual port memory definitions (see HIL_HW_DEV_CLASS_*). */
  uint16_t  usDeviceClass;

  /*! Device number.
   * For usManufacturer 1-255 the numbers are managed by Hilscher GmbH. */
  uint32_t  ulDeviceNumber;

  /*! Serial number.
   * Serial number of the device. */
  uint32_t  ulSerialNumber;

  /*! Hardware compatibility number.
   * This number indicates an incompatible hardware change */
  uint8_t   bHwCompatibility;

  /*! Hardware revision number.
   * Production related hardware revision number */
  uint8_t   bHwRevision;

  /*! Production date
   * Format is 0xYYWW:
   * Year = ((usProductionDate >> 8) & 0x00ff) + 2000
   * Week = ((usProductionDate >> 0) & 0x00ff)
   * e.g. 0C2Bh, where 0Ch is year 2012 and 2Bh is week 43.*/
  uint16_t  usProductionDate;

  uint8_t   bReserved1;       /* Changed: bHostInterfaceType is depricated */
  uint8_t   bReserved2;       /* Changed: bHwAssemblyFeatures is depricated */

  /*! Reserved area, Currently not used set to 0 */
  uint8_t   abReserved[14];

} HIL_PRODUCT_DATA_BASIC_DEVICE_DATA_T;


/*------------------------------------------------------------*/
/*! MAC Address information                                   */
/*------------------------------------------------------------*/
#define HIL_PRODUCT_NUMBER_OF_MAC_ADDRESSES   8

typedef struct HIL_PRODUCT_DATA_MAC_ADDRESS_Ttag
{
  /*! MAC address. */
  uint8_t abMacAddress[6];

  /*! Reserved fields related to the MAC address above.
   * \note Alignment, currently not used set to 0 */
  uint8_t abReserved[2];

} HIL_PRODUCT_DATA_MAC_ADDRESS_T;

typedef struct HIL_PRODUCT_DATA_MAC_ADDRESSES_T
{
  /*! MAC address array. */
  HIL_PRODUCT_DATA_MAC_ADDRESS_T atMAC[HIL_PRODUCT_NUMBER_OF_MAC_ADDRESSES];

} HIL_PRODUCT_DATA_MAC_ADDRESSES_T;


/*------------------------------------------------------------*/
/*! Hardware information                                      */
/*------------------------------------------------------------*/
typedef struct HIL_PRODUCT_DATA_HARDWARE_INFORMATION_T
{
  /*! Hardware assembly options for XC units.
   * Hardware which is equipped for the related XC units (0-3). Possible values are defined
   * in the dual port memory definitions (see HIL_HW_ASSEMBLY_*). */
  uint16_t    ausHwOptionXc[4];

  /*! Hardware assembly options for xPIC units.
   * Hardware which is equipped for the related communication side xPIC units (0-3). On
   * netX90 the "Com xPIC" is located in option 0 all other options are not used. Possible
   * values are defined in the dual port memory definitions (see HIL_HW_ASSEMBLY_*). */
  uint16_t    ausHwOptionsXpic[4];

  /*! Reserved field.
     * \note Currently not used set to 0 */
  uint8_t     abReserved1[16];

} HIL_PRODUCT_DATA_HARDWARE_INFORMATION_T;


/*------------------------------------------------------------*/
/*! Product Identification information.                       */
/*------------------------------------------------------------*/
#define HIL_PRODUCT_USB_VENDOR_NAME_SIZE    16
#define HIL_PRODUCT_USB_PRODUCT_NAME_SIZE   16

typedef struct HIL_PRODUCT_DATA_USB_Ttag
{
  /*! USB Device vendor ID (VID). */
  uint16_t    usUSBVendorID;

  /*! USB Device product ID (PID). */
  uint16_t    usUSBProductID;

  /*! USB Product name.
   * \note Byte array */
  uint8_t     abUSBVendorName[HIL_PRODUCT_USB_VENDOR_NAME_SIZE];

  /*! USB Product name string.
   * \note Byte array */
  uint8_t     abUSBProductName[HIL_PRODUCT_USB_PRODUCT_NAME_SIZE];

  /* Structure size = 36 Byte */
} HIL_PRODUCT_DATA_USB_T;


typedef struct HIL_PRODUCT_DATA_PRODUCT_IDENTIFICATION_Ttag
{
  /*! USB product data (36Byte) */
  HIL_PRODUCT_DATA_USB_T  tUSBInfo;

  /*! Reserved field.
     * \note Currently not used set to 0 */
  uint8_t                 abReserved[76];

} HIL_PRODUCT_DATA_PRODUCT_IDENTIFICATION_T;


/*------------------------------------------------------------*/
/*! OEM product specific device data.                         */
/*------------------------------------------------------------*/
typedef struct HIL_PRODUCT_DATA_OEM_IDENTIFICATION_Ttag
{
  /*! OEM Data Option Flags.
   * TBD e.g. 0 = parameter will ignored by firmware, 1= parameter will be used by firmware ...*/
  uint32_t    ulOemDataOptionFlags;

  /*! Serial number.
   * Serial number of the device as string (e.g. "20053" or "SC-D5SF5005")
   * \note Null terminated c string */
  char        szSerialNumber[28];

  /*! Order number.
   * Order number of the device as string (e.g. "1544.100" or "6ES7 511-1AK00-0AB0")
   * \note Null terminated c string */
  char        szOrderNumber[32];

  /*! Hardware revision.
   * Hardware revision as string (e.g. "3" or "V1.5")
   * \note Null terminated c string */
  char        szHardwareRevision[16];

  /*! Production date/time.
   * UTC (Universal Time Coordinated) without TZD (time zone designator, always 'Z') and no fraction of a second
   * E.g "2012-10-24T07:36:17Z"
   * \note Null terminated c string */
  char        szProductionDate[32];

  /*! Reserved fields.
   * \note Currently not used set to 0 */
  uint8_t     abReserved[12];

  /*! Vendor specific data.
   * This field can be used to store any kind of information to this device label. */
  uint8_t     abVendorData[112];

} HIL_PRODUCT_DATA_OEM_IDENTIFICATION_T;


/*------------------------------------------------------------*/
/*! PRODUCTION Data Header and Footer                         */
/*------------------------------------------------------------*/
#define HIL_PRODUCT_DATA_START_TOKEN  'ProductData>'
#define HIL_PRODUCT_DATA_END_TOKEN    '<ProductData'

typedef struct HIL_PRODUCT_DATA_HEADER_Ttag
{
  /*! Start token of the HIL_PRODUCT_DATA_LABEL_T. */
  uint8_t     abStartToken[12];
  /*! Size of the production label HIL_PRODUCT_DATA_LABEL_T.
   * \note This includes the Header and Footer */
  uint16_t    usLabelSize;
  /*! Size of the production data structure HIL_PRODUCT_DATA_T.
   * \note This does not include the Header and Footer (both are 16Byte) */
  uint16_t    usContentSize;

} HIL_PRODUCT_DATA_HEADER_T;

/*! PRODUCTION Data Footer */
typedef struct HIL_PRODUCT_DATA_FOOTER_Ttag
{
  /*! Checksum of the label array.
   * \note CRC-32 (IEEE 802.3) of HIL_PRODUCT_DATA_T */
  uint32_t    ulChecksum;
  /*! End token of the HIL_PRODUCT_DATA_LABEL_T. */
  uint8_t     abEndToken[12];

} HIL_PRODUCT_DATA_FOOTER_T;

/*------------------------------------------------------------*/
/*! LibStorage information                                    */
/*------------------------------------------------------------*/
typedef struct HIL_PRODUCT_DATA_LIBSTORAGE_AREAS_Ttag
{
  uint32_t                ulContentType;          /*!< Area content type */
  uint32_t                ulAreaStart;            /*!< Area start address */
  uint32_t                ulAreaSize;             /*!< Area size */
  uint32_t                ulChipNumber;           /*!< Chip number 0..n (Instance) */
  char                    szName[16];             /*!< Area name */
  uint8_t                 bAccessTyp;             /*!< Area access type */
  uint8_t                 abReserved[3];          /*!< Reserved */
} HIL_PRODUCT_DATA_LIBSTORAGE_AREAS_T;

typedef struct HIL_PRODUCT_DATA_LIBSTORAGE_CHIPS_Ttag
{
  uint32_t                ulChipNumber;           /*!< Chip number 0..n (Instance) */
  char                    szFlashName[16];        /*!< Flash driver name */
  uint32_t                ulBlockSize;            /*!< Block size */
  uint32_t                ulFlashSize;            /*!< Flash size */
  uint32_t                ulMaxEnduranceCycles;   /*!< Max. number of erase/write cycles */
} HIL_PRODUCT_DATA_LIBSTORAGE_CHIPS_T;

typedef struct HIL_PRODUCT_DATA_LIBSTORAGE_Ttag
{
  HIL_PRODUCT_DATA_LIBSTORAGE_AREAS_T atArea[10]; /*!< List of storage areas */
  HIL_PRODUCT_DATA_LIBSTORAGE_CHIPS_T atChip[4];  /*!< List of flash chips */
} HIL_PRODUCT_DATA_LIBSTORAGE_T;


/*------------------------------------------------------------*/
/*! PRODUCTION Data Structure                                 */
/*------------------------------------------------------------*/
/* Note: Structures should be aligned */
typedef struct HIL_PRODUCT_DATA_Ttag
{
  HIL_PRODUCT_DATA_BASIC_DEVICE_DATA_T      tBasicDeviceData;
  HIL_PRODUCT_DATA_MAC_ADDRESSES_T          tMACAddresses;
  HIL_PRODUCT_DATA_HARDWARE_INFORMATION_T   tHardwareInformation;
  HIL_PRODUCT_DATA_PRODUCT_IDENTIFICATION_T tProductIdentification;
  HIL_PRODUCT_DATA_OEM_IDENTIFICATION_T     tOEMIdentification;
  HIL_PRODUCT_DATA_LIBSTORAGE_T             tFlashLayout;

} HIL_PRODUCT_DATA_T;


/*============================================================*/
/*                                                            */
/*! PRODUCTION Data - Device Label                            */
/*                                                            */
/*============================================================*/
typedef struct HIL_PRODUCT_DATA_LABEL_Ttag
{

  HIL_PRODUCT_DATA_HEADER_T                 tHeader;
  HIL_PRODUCT_DATA_T                        tProductData;
  HIL_PRODUCT_DATA_FOOTER_T                 tFooter;

} HIL_PRODUCT_DATA_LABEL_T;

#endif /* __HIL_DEVICEPRODUCTIONDATA_H */

/**************************************************************************************
  End of file
**************************************************************************************/







