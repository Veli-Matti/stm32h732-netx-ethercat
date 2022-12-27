/**********************************************************************************************************************
                 Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***********************************************************************************************************************
  $Id: Hil_Logbook.h 3816 2018-02-28 16:09:11Z dirk $: *//**

  \file Hil_Logbook.h

  Definitions for Logbook (PS_LogBook). In this file the Type IDs will be managed PS_LOGBOOK_ENTRY_TYPE_* definitions
  are only made here.
  There is no structure to the type values, the next value is acquired directly after the last one. It is not desired
  to reserve numbers, this shall avoid dead number ranges and gaps between the types.

  This list is maintained by the protocol stack department (SPC).

***********************************************************************************************************************/
#ifndef __HIL_LOGBOOK_H
#define __HIL_LOGBOOK_H

#include <stdint.h>
#include "Hil_Compiler.h"

#ifdef __HIL_PRAGMA_PACK_ENABLE
  #pragma __HIL_PRAGMA_PACK_1(HIL_LOGBOOK)
#endif

enum {
  /*! The entry is not valid and shall not be evaluated */
  PS_LOGBOOK_ENTRY_TYPE_INVALID                       = 0x0000,
  /*! The first 16 codes are reserved for future use */
  PS_LOGBOOK_ENTRY_TYPE_RESERVED_BLOCK_END            = 0x000F,


  PS_LOGBOOK_ENTRY_TYPE_LABEL                         = 0x0010, /*!< ASCII label */
  PS_LOGBOOK_ENTRY_TYPE_DPM_COMMON_STATUS             = 0x0011, /*!< The common status block have been changed */
  PS_LOGBOOK_ENTRY_TYPE_DPM_MASTER_STATUS             = 0x0012, /*!< The master status block have been changed */


  /*! The entry is not valid and shall not be evaluated */
  PS_LOGBOOK_ENTRY_TYPE_UNKNOWN                       = 0xFFFF
} PS_LOGBOOK_ENTRY_TYPE_E;

/* Type definition for public APIs of the PS_LOGBOOK_ENTRY_TYPE_E enumeration. */
typedef int16_t PS_LOGBOOK_ENTRY_TYPE_T;


/*! Structure definition for PS_LOGBOOK_ENTRY_TYPE_LABEL entries */
typedef __HIL_PACKED_PRE struct {
  char  abLabel[14]; /*!< An ASCII label with fix length, not zero terminated. */

} __HIL_PACKED_POST PS_LOGBOOK_ENTRY_TYPE_LABEL_T;


/*! Structure definition for PS_LOGBOOK_ENTRY_TYPE_DPM_COMMON_STATUS entries.
 * A more detailed description of the values can be found in the DPM manual. */
typedef __HIL_PACKED_PRE struct {
  uint32_t  ulCommunicationCOS;   /*!< Communication channel "Change Of State" */
  uint32_t  ulCommunicationState; /*!< Actual communication state */
  uint32_t  ulCommunicationError; /*!< Actual communication error */

} __HIL_PACKED_POST PS_LOGBOOK_ENTRY_TYPE_DPM_COMMON_STATUS_T;


/*! Structure definition for PS_LOGBOOK_ENTRY_TYPE_DPM_MASTER_STATUS entries.
 * A more detailed description of the values can be found in the DPM manual. */
typedef __HIL_PACKED_PRE struct {
  uint32_t ulNumOfConfigSlaves; /*!< Number of configured slave devices in the master configuration. */
  uint32_t ulNumOfActiveSlaves; /*!< Number of activated slave devices, the master has an open connection to. */
  uint32_t ulNumOfDiagSlaves;   /*!< Number of slaves reporting diagnostic issues. */

} __HIL_PACKED_POST PS_LOGBOOK_ENTRY_TYPE_DPM_MASTER_STATUS_T;


#ifdef __HIL_PRAGMA_PACK_ENABLE
  #pragma __HIL_PRAGMA_UNPACK_1(HIL_LOGBOOK)
#endif

#endif /* __HIL_LOGBOOK_H */
