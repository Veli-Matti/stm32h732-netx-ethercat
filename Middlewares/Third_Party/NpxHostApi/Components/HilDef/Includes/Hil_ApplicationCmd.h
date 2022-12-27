/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: Hil_ApplicationCmd.h 3816 2018-02-28 16:09:11Z dirk $:

  Description:
    Hilscher Packet Command Codes Handled by the Application Task

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2017-01-31  File created.

**************************************************************************************/


#ifndef __HIL_APPLICATIONCMD_H
#define __HIL_APPLICATIONCMD_H

#include "Hil_Packet.h"

#ifdef __HIL_PRAGMA_PACK_ENABLE
  #pragma __HIL_PRAGMA_PACK_1(HIL_APPLICATIONCMD)
#endif

/***************************************************************************************/
/* Common global stack commands */

#define HIL_GET_WATCHDOG_TIME_REQ                     0x00002F02
#define HIL_GET_WATCHDOG_TIME_CNF                     0x00002F03

#define HIL_SET_WATCHDOG_TIME_REQ                     0x00002F04
#define HIL_SET_WATCHDOG_TIME_CNF                     0x00002F05

#define HIL_GET_SLAVE_HANDLE_REQ                      0x00002F08
#define HIL_GET_SLAVE_HANDLE_CNF                      0x00002F09

#define HIL_GET_SLAVE_CONN_INFO_REQ                   0x00002F0A
#define HIL_GET_SLAVE_CONN_INFO_CNF                   0x00002F0B

#define HIL_GET_DPM_IO_INFO_REQ                       0x00002F0C
#define HIL_GET_DPM_IO_INFO_CNF                       0x00002F0D

#define HIL_REGISTER_APP_REQ                          0x00002F10
#define HIL_REGISTER_APP_CNF                          0x00002F11

#define HIL_UNREGISTER_APP_REQ                        0x00002F12
#define HIL_UNREGISTER_APP_CNF                        0x00002F13

#define HIL_DELETE_CONFIG_REQ                         0x00002F14
#define HIL_DELETE_CONFIG_CNF                         0x00002F15

#define HIL_READ_IO_DATA_IMAGE_REQ                    0x00002F20
#define HIL_READ_IO_DATA_IMAGE_CNF                    0x00002F21

#define HIL_BUSSCAN_REQ                               0x00002f22
#define HIL_BUSSCAN_CNF                               0x00002f23

#define HIL_GET_DEVICE_INFO_REQ                       0x00002f24
#define HIL_GET_DEVICE_INFO_CNF                       0x00002f25

#define HIL_START_STOP_COMM_REQ                       0x00002F30
#define HIL_START_STOP_COMM_CNF                       0x00002F31

#define HIL_LOCK_UNLOCK_CONFIG_REQ                    0x00002F32
#define HIL_LOCK_UNLOCK_CONFIG_CNF                    0x00002F33

#define HIL_SET_HANDSHAKE_CONFIG_REQ                  0x00002F34
#define HIL_SET_HANDSHAKE_CONFIG_CNF                  0x00002F35

#define HIL_CHANNEL_INIT_REQ                          0x00002F80
#define HIL_CHANNEL_INIT_CNF                          0x00002F81

#define HIL_VERIFY_DATABASE_REQ                       0x00002F82
#define HIL_VERIFY_DATABASE_CNF                       0x00002F83

#define HIL_ACTIVATE_DATABASE_REQ                     0x00002F84
#define HIL_ACTIVATE_DATABASE_CNF                     0x00002F85

#define HIL_SET_FW_PARAMETER_REQ                      0x00002F86
#define HIL_SET_FW_PARAMETER_CNF                      0x00002F87

#define HIL_GET_FW_PARAMETER_REQ                      0x00002F88
#define HIL_GET_FW_PARAMETER_CNF                      0x00002F89

#define HIL_LINK_STATUS_CHANGE_IND                    0x00002F8A
#define HIL_LINK_STATUS_CHANGE_RES                    0x00002F8B

/******************************************************************************
 * Packet Definition
 ******************************************************************************/



/******************************************************************************
 * Packet: HIL_GET_WATCHDOG_TIME_REQ/HIL_GET_WATCHDOG_TIME_CNF
 *
 *          This packet allows retrieving the actual watchdog time
 */

/***** request packet *****/

typedef HIL_EMPTY_PACKET_T HIL_GET_WATCHDOG_TIME_REQ_T;

/***** confirmation packet *****/
typedef __HIL_PACKED_PRE struct HIL_GET_WATCHDOG_TIME_CNF_DATA_Ttag
{
  /** watchdog time in us */
  uint32_t ulWdgTime;
} __HIL_PACKED_POST HIL_GET_WATCHDOG_TIME_CNF_DATA_T;

typedef __HIL_PACKED_PRE struct HIL_GET_WATCHDOG_TIME_CNF_Ttag
{
  HIL_PACKET_HEADER_T                     tHead;
  HIL_GET_WATCHDOG_TIME_CNF_DATA_T  tData;
} __HIL_PACKED_POST HIL_GET_WATCHDOG_TIME_CNF_T;

/******************************************************************************
 * Packet: HIL_SET_WATCHDOG_TIME_REQ/HIL_SET_WATCHDOG_TIME_CNF
 *
 *          This packet allows setting the actual watchdog time
 */

/***** request packet *****/
typedef __HIL_PACKED_PRE  struct HIL_SET_WATCHDOG_TIME_REQ_DATA_Ttag
{
  /** watchdog time in us */
  uint32_t ulWdgTime;
} __HIL_PACKED_POST HIL_SET_WATCHDOG_TIME_REQ_DATA_T;

typedef __HIL_PACKED_PRE struct HIL_SET_WATCHDOG_TIME_REQ_Ttag
{
  HIL_PACKET_HEADER_T                     tHead;
  HIL_SET_WATCHDOG_TIME_REQ_DATA_T  tData;
} __HIL_PACKED_POST HIL_SET_WATCHDOG_TIME_REQ_T;

/***** confirmation packet *****/
typedef HIL_EMPTY_PACKET_T HIL_SET_WATCHDOG_TIME_CNF_T;

/******************************************************************************
 * Packet: HIL_PACKET_GET_SLAVE_HANDLE_REQ/HIL_PACKET_GET_SLAVE_HANDLE_CNF
 *
 *          This packet allows retrieving diagnostic information of the
 *          connected devices
 */

/***** request packet *****/
typedef __HIL_PACKED_PRE  struct HIL_PACKET_GET_SLAVE_HANDLE_REQ_DATA_Tag
{
  uint32_t ulParam;
} __HIL_PACKED_POST  HIL_PACKET_GET_SLAVE_HANDLE_REQ_DATA_T;

#define HIL_LIST_CONF_SLAVES                0x00000001
#define HIL_LIST_ACTV_SLAVES                0x00000002
#define HIL_LIST_FAULTED_SLAVES             0x00000003

typedef __HIL_PACKED_PRE struct HIL_PACKET_GET_SLAVE_HANDLE_REQ_Tag
{
  HIL_PACKET_HEADER_T                     tHead;
  HIL_PACKET_GET_SLAVE_HANDLE_REQ_DATA_T  tData;
} __HIL_PACKED_POST HIL_PACKET_GET_SLAVE_HANDLE_REQ_T;

/***** confirmation packet *****/
typedef __HIL_PACKED_PRE  struct HIL_PACKET_GET_SLAVE_HANDLE_CNF_DATA_Tag
{
  uint32_t ulParam;
  uint32_t aulHandle[1];
} __HIL_PACKED_POST  HIL_PACKET_GET_SLAVE_HANDLE_CNF_DATA_T;

typedef __HIL_PACKED_PRE struct HIL_PACKET_GET_SLAVE_HANDLE_CNF_Tag
{
  HIL_PACKET_HEADER_T                     tHead;
  HIL_PACKET_GET_SLAVE_HANDLE_CNF_DATA_T  tData;
} __HIL_PACKED_POST HIL_PACKET_GET_SLAVE_HANDLE_CNF_T;

/******************************************************************************
 * Packet: HIL_PACKET_GET_SLAVE_CONN_INFO_REQ/HIL_PACKET_GET_SLAVE_CONN_INFO_CNF
 *
 *          This packet allows retrieving detail information of a slave
 */

/***** request packet *****/

typedef __HIL_PACKED_PRE  struct HIL_PACKET_GET_SLAVE_CONN_INFO_REQ_DATA_Tag
{
  uint32_t ulHandle;
} __HIL_PACKED_POST  HIL_PACKET_GET_SLAVE_CONN_INFO_REQ_DATA_T;

typedef __HIL_PACKED_PRE struct HIL_PACKET_GET_SLAVE_CONN_INFO_REQ_Tag
{
  HIL_PACKET_HEADER_T                        tHead;
  HIL_PACKET_GET_SLAVE_CONN_INFO_REQ_DATA_T  tData;
} __HIL_PACKED_POST HIL_PACKET_GET_SLAVE_CONN_INFO_REQ_T;

/***** confirmation packet *****/
typedef __HIL_PACKED_PRE  struct HIL_PACKET_GET_SLAVE_CONN_INFO_CNF_DATA_Tag
{
  uint32_t ulHandle;
  uint32_t ulStructID;
  /*
    Feldbus specific structure
  */
} __HIL_PACKED_POST HIL_PACKET_GET_SLAVE_CONN_INFO_CNF_DATA_T;

typedef __HIL_PACKED_PRE struct HIL_PACKET_GET_SLAVE_CONN_INFO_CNF_Tag
{
  HIL_PACKET_HEADER_T                        tHead;
  HIL_PACKET_GET_SLAVE_CONN_INFO_CNF_DATA_T  tData;
} __HIL_PACKED_POST  HIL_PACKET_GET_SLAVE_CONN_INFO_CNF_T;


/******************************************************************************
 * Packet: HIL_GET_DPM_IO_INFO__REQ/HIL_GET_DPM_IO_INFO__CNF
 *
 *          This packet allows retrieving the used I/O length
 */

/***** request packet *****/
typedef HIL_EMPTY_PACKET_T          HIL_GET_DPM_IO_INFO_REQ_T;

/***** confirmation packet *****/
typedef __HIL_PACKED_PRE struct HIL_DPM_IO_BLOCK_INFO_Ttag
{
  uint32_t    ulSubblockIndex;        /* number of sub block  */
  uint32_t    ulType;                 /* type of sub block    */
  uint16_t    usFlags;                  /* flags of the sub block */
  uint16_t    usReserved;           /* reserved */
  uint32_t    ulOffset;               /* start offset of the IO data  */
  uint32_t    ulLength;               /* length of used IO data   */
} __HIL_PACKED_POST HIL_DPM_IO_BLOCK_INFO_T;

typedef __HIL_PACKED_PRE struct HIL_GET_DPM_IO_INFO_CNF_DATA_Ttag
{
  uint32_t    ulNumIOBlockInfo;                   /* Number of IO Block Info  */
  HIL_DPM_IO_BLOCK_INFO_T atIOBlockInfo[2]; /* Array of I/O Block information */
} __HIL_PACKED_POST HIL_GET_DPM_IO_INFO_CNF_DATA_T;

typedef __HIL_PACKED_PRE struct HIL_GET_DPM_IO_INFO_CNF_Ttag
{
  HIL_PACKET_HEADER_T   tHead;  /* packer header    */
  HIL_GET_DPM_IO_INFO_CNF_DATA_T    tData;  /* packet header    */
} __HIL_PACKED_POST HIL_GET_DPM_IO_INFO_CNF_T;



/******************************************************************************
 * Packet: HIL_REGISTER_APP_REQ/HIL_REGISTER_APP_CNF
 *
 *          This packet allows to register a application
 */

/***** request packet *****/
typedef HIL_EMPTY_PACKET_T          HIL_REGISTER_APP_REQ_T;

/***** confirmation packet *****/
typedef HIL_EMPTY_PACKET_T          HIL_REGISTER_APP_CNF_T;


/******************************************************************************
 * Packet: HIL_UNREGISTER_APP_REQ/HIL_UNREGISTER_APP_CNF
 *
 *          This packet allows to unregister a application
 */

/***** request packet *****/
typedef HIL_EMPTY_PACKET_T          HIL_UNREGISTER_APP_REQ_T;

/***** confirmation packet *****/
typedef HIL_EMPTY_PACKET_T          HIL_UNREGISTER_APP_CNF_T;


/******************************************************************************
 * Packet: HIL_DELETE_CONFIG_REQ/HIL_DELETE_CONFIG_CNF
 *
 *          This packet allows to delete the actual configuration
 */

/***** request packet *****/
typedef HIL_EMPTY_PACKET_T          HIL_DELETE_CONFIG_REQ_T;

/***** confirmation packet *****/
typedef HIL_EMPTY_PACKET_T          HIL_DELETE_CONFIG_CNF_T;

/******************************************************************************
 * HIL_BUSSCAN_REQ
 ******************************************************************************/
#define HIL_BUSSCAN_CMD_START    0x01
#define HIL_BUSSCAN_CMD_STATUS   0x02
#define HIL_BUSSCAN_CMD_ABORT    0x03

/***** request packet *****/
typedef __HIL_PACKED_PRE struct HIL_BUSSCAN_REQ_DATA_Ttag
{
  uint32_t ulAction;
} __HIL_PACKED_POST HIL_BUSSCAN_REQ_DATA_T;

typedef __HIL_PACKED_PRE struct HIL_BUSSCAN_REQ_Ttag
{
  HIL_PACKET_HEADER_T tHead;
  HIL_BUSSCAN_REQ_DATA_T tData;
} __HIL_PACKED_POST HIL_BUSSCAN_REQ_T;

#define HIL_BUSSCAN_REQ_SIZE     (sizeof(HIL_BUSSCAN_REQ_DATA_T))

/***** confirmation packet *****/

typedef __HIL_PACKED_PRE struct HIL_BUSSCAN_CNF_DATA_Ttag
{
  uint32_t ulMaxProgress;
  uint32_t ulActProgress;
  uint8_t  abDeviceList[4];
} __HIL_PACKED_POST HIL_BUSSCAN_CNF_DATA_T;

typedef __HIL_PACKED_PRE struct HIL_BUSSCAN_CNF_Ttag
{
  HIL_PACKET_HEADER_T tHead;
  HIL_BUSSCAN_CNF_DATA_T tData;
} __HIL_PACKED_POST HIL_BUSSCAN_CNF_T;

#define HIL_BUSSCAN_CNF_SIZE     (sizeof(HIL_BUSSCAN_CNF_DATA_T) - 4)


/******************************************************************************
 * HIL_GET_DEVICE_INFO_REQ
 ******************************************************************************/
/***** request packet *****/
typedef __HIL_PACKED_PRE struct HIL_GET_DEVICE_INFO_REQ_DATA_Ttag
{
  uint32_t ulDeviceIdx;
} __HIL_PACKED_POST HIL_GET_DEVICE_INFO_REQ_DATA_T;

typedef __HIL_PACKED_PRE struct HIL_GET_DEVICE_INFO_REQ_Ttag
{
  HIL_PACKET_HEADER_T            tHead;
  HIL_GET_DEVICE_INFO_REQ_DATA_T tData;
} __HIL_PACKED_POST HIL_GET_DEVICE_INFO_REQ_T;

#define HIL_GET_DEVICE_INFO_REQ_SIZE     (sizeof(HIL_GET_DEVICE_INFO_REQ_DATA_T))

/***** confirmation packet *****/
typedef __HIL_PACKED_PRE struct HIL_GET_DEVICE_INFO_CNF_DATA_Ttag
{
  uint32_t ulDeviceIdx;
  uint32_t ulStructId;
  /* uint8_t  tStruct; Fieldbus specific structure */
} __HIL_PACKED_POST HIL_GET_DEVICE_INFO_CNF_DATA_T;

typedef struct HIL_GET_DEVICE_INFO_CNF_Ttag
{
  HIL_PACKET_HEADER_T            tHead;
  HIL_GET_DEVICE_INFO_CNF_DATA_T tData;
} __HIL_PACKED_POST HIL_GET_DEVICE_INFO_CNF_T;

#define HIL_GET_DEVICE_INFO_CNF_SIZE     (sizeof(HIL_GET_DEVICE_INFO_CNF_DATA_T))

/******************************************************************************
 * Packet: HIL_START_STOP_COMM_REQ/HIL_START_STOP_COMM_CNF
 *
 *          This packet allows start and stop bus communication
 */
#define HIL_START_STOP_COMM_PARAM_START     0x00000001
#define HIL_START_STOP_COMM_PARAM_STOP      0x00000002

/***** request packet *****/
typedef __HIL_PACKED_PRE struct HIL_START_STOP_COMM_REQ_DATA_Ttag
{
  uint32_t    ulParam;                    /* Boolean to set Start(1) or Stop(2) Communication */
} __HIL_PACKED_POST HIL_START_STOP_COMM_REQ_DATA_T;

typedef __HIL_PACKED_PRE struct HIL_START_STOP_COMM_REQ_Ttag
{
  HIL_PACKET_HEADER_T   tHead;  /* packer header    */
  HIL_START_STOP_COMM_REQ_DATA_T    tData;  /* packet header    */
} __HIL_PACKED_POST HIL_START_STOP_COMM_REQ_T;


/***** confirmation packet *****/
typedef HIL_EMPTY_PACKET_T          HIL_START_STOP_COMM_CNF_T;

/******************************************************************************
 * Packet: HIL_LOCK_UNLOCK_CONFIG_REQ/HIL_LOCK_UNLOCK_CONFIG_CNF
 *
 *          This packet allows lock and unlock the configuration settings
 */

#define HIL_LOCK_UNLOCK_CONFIG_PARAM_LOCK     0x00000001
#define HIL_LOCK_UNLOCK_CONFIG_PARAM_UNLOCK   0x00000002

/***** request packet *****/
typedef __HIL_PACKED_PRE struct HIL_LOCK_UNLOCK_CONFIG_REQ_DATA_Ttag
{
  uint32_t    ulParam;                    /* Boolean to set Lock(1) or Unlock(2) config */
} __HIL_PACKED_POST HIL_LOCK_UNLOCK_CONFIG_REQ_DATA_T;

typedef __HIL_PACKED_PRE struct HIL_LOCK_UNLOCK_CONFIG_REQ_Ttag
{
  HIL_PACKET_HEADER_T   tHead;  /* packer header    */
  HIL_LOCK_UNLOCK_CONFIG_REQ_DATA_T tData;  /* packet header    */
} __HIL_PACKED_POST HIL_LOCK_UNLOCK_CONFIG_REQ_T;


/***** confirmation packet *****/
typedef HIL_EMPTY_PACKET_T          HIL_LOCK_UNLOCK_CONFIG_CNF_T;


/******************************************************************************
 * HIL_SET_HANDSHAKE_CONFIG_REQ
 ******************************************************************************/
/***** request packet *****/
typedef __HIL_PACKED_PRE struct HIL_SET_HANDSHAKE_CONFIG_REQ_DATA_Ttag
{
  /* Input process data handshake mode */
  uint8_t                           bPDInHskMode;
  /* Input process data trigger source. Currently unused, set to zero. */
  uint8_t                           bPDInSource;
  /* Threshold for input process data handshake handling errors */
  uint16_t                          usPDInErrorTh;

  /* Output process data handshake mode */
  uint8_t                           bPDOutHskMode;
  /* Output process data trigger source. Currently unused, set to zero. */
  uint8_t                           bPDOutSource;
  /* Threshold for output process data handshake handling errors */
  uint16_t                          usPDOutErrorTh;

  /* Synchronization handshake mode */
  uint8_t                           bSyncHskMode;
  /* Synchronization source */
  uint8_t                           bSyncSource;
  /* Threshold for synchronization handshake handling errors */
  uint16_t                          usSyncErrorTh;

  /* Reserved for future use. Set to zero. */
  uint32_t                          aulReserved[2];
} __HIL_PACKED_POST HIL_SET_HANDSHAKE_CONFIG_REQ_DATA_T;

typedef __HIL_PACKED_PRE struct HIL_SET_HANDSHAKE_CONFIG_REQ_Ttag
{
  HIL_PACKET_HEADER_T                 tHead;
  HIL_SET_HANDSHAKE_CONFIG_REQ_DATA_T tData;
} __HIL_PACKED_POST HIL_SET_HANDSHAKE_CONFIG_REQ_T;

#define HIL_SET_HANDSHAKE_CONFIG_REQ_SIZE     (sizeof(HIL_SET_HANDSHAKE_CONFIG_REQ_DATA_T))

/***** confirmation packet *****/
typedef HIL_EMPTY_PACKET_T  HIL_SET_HANDSHAKE_CONFIG_CNF_T;

#define HIL_SET_HANDSHAKE_CONFIG_CNF_SIZE     (0)


/******************************************************************************
 * Packet: HIL_CHANNEL_INIT_REQ/HIL_CHANNEL_INIT_CNF
 *
 *          This packet allows retrieving the used I/O length
 */

/***** request packet *****/
typedef HIL_EMPTY_PACKET_T          HIL_CHANNEL_INIT_REQ_T;

/***** confirmation packet *****/
typedef HIL_EMPTY_PACKET_T          HIL_CHANNEL_INIT_CNF_T;


/******************************************************************************
 * Packet: HIL_VERIFY_DATABASE_REQ /HIL_VERIFY_DATABASE_CNF
 *
 *          This packet adds new slaves to the database
 */
 /***** request packet *****/
typedef __HIL_PACKED_PRE struct HIL_VERIFY_DATABASE_REQ_Ttag
{
  HIL_PACKET_HEADER_T tHead;                    /* packet header */
} __HIL_PACKED_POST HIL_VERIFY_DATABASE_REQ_T;

#define HIL_VERIFY_DATABASE_REQ_SIZE 0


/***** confirmation packet *****/
typedef __HIL_PACKED_PRE struct HIL_VERIFY_SLAVE_DATABASE_LIST_Ttag
{
    uint32_t  ulLen;
    uint8_t  abData[16];
} __HIL_PACKED_POST HIL_VERIFY_SLAVE_DATABASE_LIST_T;

typedef __HIL_PACKED_PRE struct HIL_VERIFY_MASTER_DATABASE_Ttag
{
  uint32_t  ulMasterSettings;   /* field bus independent changes */
  uint32_t  ulMasterStatus;     /* field bus specific status */
  uint32_t  ulReserved[2];
} __HIL_PACKED_POST HIL_VERIFY_MASTER_DATABASE_T;


#define HIL_VERIFY_SLAVE_DATABASE_LIST_SIZE sizeof(HIL_VERIFY_SLAVE_DATABASE_LIST_T)
#define HIL_CIR_MST_SET_STARTUP       0x00000001
#define HIL_CIR_MST_SET_WATCHDOG      0x00000002
#define HIL_CIR_MST_SET_STATUSOFFSET  0x00000004
#define HIL_CIR_MST_SET_BUSPARAMETER  0x00000008

typedef __HIL_PACKED_PRE struct HIL_VERIFY_DATABASE_CNF_DATA_Ttag
{
    HIL_VERIFY_SLAVE_DATABASE_LIST_T                tNewSlaves;
    HIL_VERIFY_SLAVE_DATABASE_LIST_T                tDeactivatedSlaves;
    HIL_VERIFY_SLAVE_DATABASE_LIST_T                tChangedSlaves;
    HIL_VERIFY_SLAVE_DATABASE_LIST_T                tUnchangedSlaves;
    HIL_VERIFY_SLAVE_DATABASE_LIST_T                tImpossibleSlaveChanges;
    HIL_VERIFY_MASTER_DATABASE_T                    tMasterChanges;
} __HIL_PACKED_POST HIL_VERIFY_DATABASE_CNF_DATA_T;

#define HIL_VERIFY_DATABASE_CNF_DATA_SIZE sizeof(HIL_VERIFY_DATABASE_CNF_DATA_T)

typedef __HIL_PACKED_PRE struct HIL_VERIFY_DATABASE_CNF_Ttag
{
  HIL_PACKET_HEADER_T                       tHead;    /* packet header  */
  HIL_VERIFY_DATABASE_CNF_DATA_T            tData;    /* packet data    */
} __HIL_PACKED_POST HIL_VERIFY_DATABASE_CNF_T;

#define HIL_VERFIY_DATABASE_CNF_PACKET_SIZE sizeof(HIL_VERIFY_DATABASE_CNF_T)



/******************************************************************************
 * Packet: HIL_CHANNEL_ACTIVATE_REQ/HIL_CHANNEL_NEW_DATABASE_CNF
 *
 *          This packet activates the new configured slaves
  */
 /***** request packet *****/
typedef __HIL_PACKED_PRE struct HIL_ACTIVATE_DATABASE_REQ_Ttag
{
  HIL_PACKET_HEADER_T tHead;                    /* packet header */
} __HIL_PACKED_POST HIL_ACTIVATE_DATABASE_REQ_T;



 /***** confirmation packet *****/
typedef __HIL_PACKED_PRE struct HIL_ACTIVATE_DATABASE_CNF_DATA_Ttag
{
  uint8_t                 abSlvSt[16];                    /* State of the slaves after configuration */
} __HIL_PACKED_POST HIL_ACTIVATE_DATABASE_CNF_DATA_T;

#define HIL_ACTIVATE_DATABASE_CNF_DATA_SIZE sizeof(HIL_ACTIVATE_DATABASE_CNF_DATA_T)


typedef __HIL_PACKED_PRE struct HIL_ACTIVATE_DATABASE_CNF_Ttag
{
  HIL_PACKET_HEADER_T                       tHead;                   /* packet header */
  HIL_ACTIVATE_DATABASE_CNF_DATA_T          tData;
} __HIL_PACKED_POST HIL_ACTIVATE_DATABASE_CNF_T;

#define HIL_ACTIVATE_DATABASE_CNF_PACKET_SIZE sizeof(HIL_ACTIVATE_DATABASE_CNF_T)

/******************************************************************************
 * HIL_SET_FW_PARAMETER_REQ
 ******************************************************************************/

/***** PID defines    *****/

#define PID_STATION_ADDRESS     0x30000001 /* Station address of device*/
#define PID_BAUDRATE            0x30000002 /* Baudrate of device */
#define PID_PN_NAME_OF_STATION  0x30015001 /* PROFINET Name of Station String */


/***** request packet *****/

typedef __HIL_PACKED_PRE struct HIL_SET_FW_PARAMETER_REQ_DATA_Ttag
{
  uint32_t ulParameterID;
  uint32_t ulParameterLen;
  uint8_t  abParameter[4];  /* padded to DWORD boundary*/
} __HIL_PACKED_POST HIL_SET_FW_PARAMETER_REQ_DATA_T;

typedef __HIL_PACKED_PRE struct HIL_SET_FW_PARAMETER_REQ_Ttag
{
  HIL_PACKET_HEADER_T tHead;
  HIL_SET_FW_PARAMETER_REQ_DATA_T tData;
} __HIL_PACKED_POST HIL_SET_FW_PARAMETER_REQ_T;

#define HIL_SET_FW_PARAMETER_REQ_SIZE (sizeof(HIL_SET_FW_PARAMETER_REQ_DATA_T) - 4)


/***** confirmation packet *****/
typedef HIL_EMPTY_PACKET_T  HIL_SET_FW_PARAMETER_CNF_T;

#define HIL_SET_FW_PARAMETER_CNF_SIZE     (0)


/******************************************************************************
 * HIL_GET_FW_PARAMETER_REQ
 ******************************************************************************/

/***** request packet *****/

typedef __HIL_PACKED_PRE struct HIL_GET_FW_PARAMETER_REQ_DATA_Ttag
{
  uint32_t ulParameterID;
} __HIL_PACKED_POST HIL_GET_FW_PARAMETER_REQ_DATA_T;

typedef __HIL_PACKED_PRE struct HIL_GET_FW_PARAMETER_REQ_Ttag
{
  HIL_PACKET_HEADER_T tHead;
  HIL_GET_FW_PARAMETER_REQ_DATA_T tData;
} __HIL_PACKED_POST HIL_GET_FW_PARAMETER_REQ_T;

#define HIL_GET_FW_PARAMETER_REQ_SIZE (sizeof(HIL_GET_FW_PARAMETER_REQ_DATA_T))


/***** confirmation packet *****/

typedef HIL_SET_FW_PARAMETER_REQ_T   HIL_GET_FW_PARAMETER_CNF_T;

#define HIL_GET_FW_PARAMETER_CNF_SIZE HIL_SET_FW_PARAMETER_REQ_SIZE

/******************************************************************************
 * HIL_LINK_STATUS_CHANGE_IND
 ******************************************************************************/

/***** indication packet *****/

typedef __HIL_PACKED_PRE struct HIL_LINK_STATUS_Ttag
{

  uint32_t ulPort;           /*!< Port the link status is for */

  uint32_t fIsFullDuplex;    /*!< If a full duplex link is available on this port */

  uint32_t fIsLinkUp;        /*!< If a link is available on this port */

  uint32_t ulSpeed;          /*!< Speed of the link \n\n

                                     \valueRange
                                     0:   No link \n
                                     10:  10MBit  \n
                                     100: 100MBit \n */

} __HIL_PACKED_POST HIL_LINK_STATUS_T;


typedef __HIL_PACKED_PRE struct HIL_LINK_STATUS_CHANGE_IND_DATA_Ttag
{
  HIL_LINK_STATUS_T  atLinkData[2];
} __HIL_PACKED_POST HIL_LINK_STATUS_CHANGE_IND_DATA_T;

typedef __HIL_PACKED_PRE struct HIL_LINK_STATUS_CHANGE_IND_Ttag
{
  HIL_PACKET_HEADER_T               tHead;
  HIL_LINK_STATUS_CHANGE_IND_DATA_T tData;
} __HIL_PACKED_POST HIL_LINK_STATUS_CHANGE_IND_T;

#define HIL_LINK_STATUS_CHANGE_IND_SIZE (sizeof(HIL_LINK_STATUS_CHANGE_IND_DATA_T))

/***** response packet *****/

typedef HIL_EMPTY_PACKET_T      HIL_LINK_STATUS_CHANGE_RES_T;

#define HIL_LINK_STATUS_CHANGE_RES_SIZE   (0)

#ifdef __HIL_PRAGMA_PACK_ENABLE
  #pragma __HIL_PRAGMA_UNPACK_1(HIL_APPLICATIONCMD)
#endif

#endif
