/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: Hil_CommandRange.h 3816 2018-02-28 16:09:11Z dirk $:

  Description:
    HIL commands

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2016-11-30  File created.

**************************************************************************************/


#ifndef __HIL_COMMANDS_H
#define __HIL_COMMANDS_H

/****************************************************************************************
* commands */

enum HIL_COMMAND_Etag
{
  /* Command number 0 to 0x80 reserved, don't use it */

  HIL_COMMAND_INVALID = 0,

  /* Summary of the HIL global commands used in every Task */
  HIL_PACKET_COMMAND_START                        = 0x080,

  HIL_CMD_END_PROCESS_REQ                         = 0x080,
  HIL_CMD_END_PROCESS_CNF                         = 0x081,

  HIL_CMD_START_PROCESS_REQ                       = 0x082,
  HIL_CMD_START_PROCESS_CNF                       = 0x083,

  HIL_CMD_STOP_PROCESS_REQ                        = 0x084,
  HIL_CMD_STOP_PROCESS_CNF                        = 0x085,

  HIL_CMD_CYCLE_EVENT_REQ                         = 0x086,
  HIL_CMD_CYCLE_EVENT_CNF                         = 0x087,


  /* Summary of the Profibus DL (Datalink Layer Protocol) service commands and primitives */
  PROFIBUS_DL_PACKET_COMMAND_START                = 0x100,


  /* Summary of the TCP/IP IP service commands and primitives             */
  TCPIP_IP_PACKET_COMMAND_START               = 0x200,

  /* Summary of the TCP/IP TCP_UDP (TCP | TCP_UDP | UDP) service commands */
  /* and primitives                                                       */
  TCPIP_TCP_UDP_PACKET_COMMAND_START          = 0x300,


  /* Summary of the Profibus FSPMS (Fieldbus Service Protocol Machine - Slave) service commands and primitives */
  PROFIBUS_FSPMS_PACKET_COMMAND_START             = 0x400,


  /* Summary of the RPC service commands and primitives */
  RPC_PACKET_COMMAND_START                        = 0x00000500,

  /* Summary of the PROFINET IO common service commands and primitives */
  PNIO_COMMON_PACKET_COMMAND_START            = 0x00000600,

  /* Summary of the PROFINET ACP service commands and primitives */
  PNIO_ACP_PACKET_COMMAND_START               = 0x00000800,

  /* Summary of the PROFINET DCP service commands and primitives */
  PNIO_DCP_PACKET_COMMAND_START               = 0x00000900,

  /* Summary of the PROFINET EDD service commands and primitives */
  PNIO_EDD_PACKET_COMMAND_START               = 0x00000A00,

  /* Summary of the Lenze PROFINET IO-Device service commands and primitives */
  PNIOD_LENZE_PACKET_COMMAND_START            = 0xb00,

  PNIOD_LENZE_CMD_END_PROCESS_REQ             = 0xb00,
  PNIOD_LENZE_CMD_END_PROCESS_CNF             = 0xb01,

  /* Summary of the Lenze PROFINET IO-Device service commands and primitives */
  PNIOD_LENZE_INIT_PACKET_COMMAND_START       = 0xb80,

  /* Summary of the PROFINET IO-Controller application service commands and primitives */
  PNIO_APCTL_PACKET_COMMAND_START             = 0x00000C00,

  /* Summary of the PROFINET IO-Device application service commands and primitives */
  PNIO_APDEV_PACKET_COMMAND_START             = 0x00000D00,

  /* Summary of the PROFINET CMCTL service commands and primitives */
  PNIO_CMCTL_PACKET_COMMAND_START             = 0x00000E00,

  /* Summary of the PROFINET CMDEV service commands and primitives */
  PNIO_CMDEV_PACKET_COMMAND_START             = 0x00000F00,

  /*
   * Summary of POWERLINK EPL PDO service commands and primitives
   */
  EPL_PDO_PACKET_COMMAND_START                = 0x1000,

  /*
   * Summary of POWERLINK EPL SDO service commands and primitives
   */
  EPL_SDO_PACKET_COMMAND_START                = 0x1100,

  /*
   * Summary of POWERLINK EPL MN service commands and primitives
   */
  EPL_MN_PACKET_COMMAND_START                 = 0x1200,

  /*
   * Summary of POWERLINK EPL NMT service commands and primitives
   */
  EPL_NMT_PACKET_COMMAND_START                = 0x1300,

  /*
   * Summary of POWERLINK MN Packet Timer service commands and primitives
   */
  EPL_MN_TIMER_PACKET_COMMAND_START                = 0x1400,
  /* no commands here those are used internally by EplMn for timing */

  /*
  **  Summary of PROFINET IO-Device DPM Interface service commands and primitives
  */
  PNIOD_DPMIF_PACKET_COMMAND_START            = 0x1500,

  PNIOD_DPMIF_CMD_END_PROCESS_REQ             = 0x1500,
  PNIOD_DPMIF_CMD_END_PROCESS_CNF             = 0x1501,

  PNIOD_DPMIF_PROCESS_ALARM_REQ               = 0x1502,
  PNIOD_DPMIF_PROCESS_ALARM_CNF               = 0x1503,

  PNIOD_DPMIF_ADD_CHANNEL_DIAG_REQ            = 0x1504,
  PNIOD_DPMIF_ADD_CHANNEL_DIAG_CNF            = 0x1505,

  PNIOD_DPMIF_ADD_GENERIC_DIAG_REQ            = 0x1506,
  PNIOD_DPMIF_ADD_GENERIC_DIAG_CNF            = 0x1507,

  PNIOD_DPMIF_REMOVE_DIAG_REQ                 = 0x1508,
  PNIOD_DPMIF_REMOVE_DIAG_CNF                 = 0x1509,

  PNIOD_DPMIF_SET_CONFIG_REQ                  = 0x150a,
  PNIOD_DPMIF_SET_CONFIG_CNF                  = 0x150b,

  PNIOD_DPMIF_CBF_READ_RECORD_REQ             = 0x1580,
  PNIOD_DPMIF_CBF_READ_RECORD_CNF             = 0x1581,

  PNIOD_DPMIF_CBF_WRITE_RECORD_REQ            = 0x1582,
  PNIOD_DPMIF_CBF_WRITE_RECORD_CNF            = 0x1583,

  PNIOD_DPMIF_ALARM_IND                       = 0x1584,
  PNIOD_DPMIF_ALARM_RES                       = 0x1585,

  PNIOD_DPMIF_CBF_STATION_NAME_IND            = 0x1586,
  PNIOD_DPMIF_CBF_STATION_NAME_RES            = 0x1587,

  PNIOD_DPMIF_CBF_STATION_TYPE_IND            = 0x1588,
  PNIOD_DPMIF_CBF_STATION_TYPE_RES            = 0x1589,
  /*
  **  Summary of UDP Debug Client service commands and primiives
  */
  DEBUG_CLIENT_PACKET_COMMAND_START           = 0x1600,

  DEBUG_CLIENT_CMD_END_PROCESS_REQ            = 0x1600,
  DEBUG_CLIENT_CMD_END_PROCESSS_CNF           = 0x1601,

  DEBUG_CLIENT_CMD_SEND_DEBUG_STRING_REQ      = 0x1602,
  DEBUG_CLIENT_CMD_SEND_DEBUG_STRING_CNF      = 0x1603,


/* Summary of the example Example Task 1 service commands and primitives */
  EXAMPLETASK1_PACKET_COMMAND_START           = 0x1700,

  EXAMPLETASK1_CMD_END_PROCESS_REQ            = 0x1700,
  EXAMPLETASK1_CMD_END_PROCESS_CNF            = 0x1701,  /* only for correct handling in list */
  EXAMPLETASK1_CMD_TEST_REQ                   = 0x1702,
  EXAMPLETASK1_CMD_TEST_CNF                   = 0x1703,

  /* Summary of the example Example Task 2 service commands and primitives */
  EXAMPLETASK2_PACKET_COMMAND_START           = 0x1720,

  EXAMPLETASK2_CMD_END_PROCESS_REQ            = 0x1720,
  EXAMPLETASK2_CMD_END_PROCESS_CNF            = 0x1721,  /* only for correct handling in list */
  EXAMPLETASK2_CMD_TEST_REQ                   = 0x1722,
  EXAMPLETASK2_CMD_TEST_CNF                   = 0x1723,

  /* Summary of the example Example Task 3 service commands and primitives */
  EXAMPLETASK3_PACKET_COMMAND_START           = 0x1740,

  EXAMPLETASK3_CMD_END_PROCESS_REQ            = 0x1740,
  EXAMPLETASK3_CMD_END_PROCESS_CNF            = 0x1741,  /* only for correct handling in list */
  EXAMPLETASK3_CMD_TEST_REQ                   = 0x1742,
  EXAMPLETASK3_CMD_TEST_CNF                   = 0x1743,

  /* Summary of the Ethernet/IP Encapsulation Task service commands and primitives   */
  EIP_ENCAP_PACKET_COMMAND_START              =  0x00001800 ,

  /*
  ** Summary of EtherCAT commands */
  ECAT_PACKET_COMMAND_START                     =  0x00001900,

  /*  Summary of the Ethernet/IP Object task service commands and primitives   */
  EIP_OBJECT_PACKET_COMMAND_START             =  0x00001A00 ,


  /*
  ** Summary of EtherCAT commands part 2
  */

  ECAT_2_PACKET_COMMAND_START                 =   0x00001B00,

  /*
  ** Summary of iCon-L Main-Task commands
  */

  ICONL_RUN_PACKET_COMMAND_START              =   0x00001C00,

  /* Run Main-Function and Communication */
  ICONL_RUN_DSPSRUN_REQ                       =   0x00001C00,
  ICONL_RUN_DSPSRUN_CNF                       =   0x00001C01,

  /*
  ** Summary of iCon-L Timer-Task commands
  */

  ICONL_TIMER_PACKET_COMMAND_START            =   0x00001D00,

  /* Run iCon-L Timer (Scheduler) */
  ICONL_TIMER_DSPSTIMER_REQ                   =   0x00001D00,
  ICONL_TIMER_DSPSTIMER_CNF                   =   0x00001D01,

  /*
  **  Summary of MID_SYS task commands
   */
  MID_SYS_PACKET_COMMAND_START                =   0x00001E00,

  /*
  ** Summary of the PROFINET IO-Device Interface task service commands
  */
  PNS_IF_PACKET_COMMAND_START               =   0x00001F00,

  /*
  ** Summary of the Mid_Dbg task (backend task)
  */

  MID_DBG_PACKET_COMMAND_START                =  0x00002000,

  /* Memory access */
  MID_DBG_READ_MEMORY_REQ                     =  0x00002000,
  MID_DBG_READ_MEMORY_CNF                     =  0x00002001,
  MID_DBG_WRITE_MEMORY_REQ                    =  0x00002002,
  MID_DBG_WRITE_MEMORY_CNF                    =  0x00002003,

  /* OS call access */
  MID_DBG_CALL_FUNC_REQ                       =  0x00002020,
  MID_DBG_CALL_FUNC_CNF                       =  0x00002021,

  /* Breakpoints */
  MID_DBG_SET_SW_BREAKPOINT_REQ               =  0x00002040,
  MID_DBG_SET_SW_BREAKPOINT_CNF               =  0x00002041,
  MID_DBG_CLR_SW_BREAKPOINT_REQ               =  0x00002042,
  MID_DBG_CLR_SW_BREAKPOINT_CNF               =  0x00002043,
  MID_DBG_SET_HW_BREAKPOINT_REQ               =  0x00002044,
  MID_DBG_SET_HW_BREAKPOINT_CNF               =  0x00002045,
  MID_DBG_CLR_HW_BREAKPOINT_REQ               =  0x00002046,
  MID_DBG_CLR_HW_BREAKPOINT_CNF               =  0x00002047,
  MID_DBG_GET_SW_BREAKPOINT_IDX_REQ           =  0x00002048,
  MID_DBG_GET_SW_BREAKPOINT_IDX_CNF           =  0x00002049,
  MID_DBG_GET_HW_BREAKPOINT_IDX_REQ           =  0x0000204A,
  MID_DBG_GET_HW_BREAKPOINT_IDX_CNF           =  0x0000204B,

  MID_DBG_REACHED_HW_BREAKPOINT_IND           =  0x0000204C,
  MID_DBG_REACHED_HW_BREAKPOINT_RES           =  0x0000204D,
  MID_DBG_REACHED_SW_BREAKPOINT_IND           =  0x0000204E,
  MID_DBG_REACHED_SW_BREAKPOINT_RES           =  0x0000204F,

  /* access to task registers */
  MID_DBG_READ_REGS_REQ                       =  0x00002060,
  MID_DBG_READ_REGS_CNF                       =  0x00002061,
  MID_DBG_WRITE_REG_REQ                       =  0x00002062,
  MID_DBG_WRITE_REG_CNF                       =  0x00002063,

  /* suspending & resuming tasks */
  MID_DBG_SUSPEND_TASK_REQ                    =  0x00002080,
  MID_DBG_SUSPEND_TASK_CNF                    =  0x00002081,
  MID_DBG_CONTINUE_TASK_REQ                   =  0x00002082,
  MID_DBG_CONTINUE_TASK_CNF                   =  0x00002083,

  /* indication connect for debugger frontend */
  MID_DBG_CONNECT_REQ                         =  0x000020A0,
  MID_DBG_CONNECT_CNF                         =  0x000020A1,
  MID_DBG_DISCONNECT_REQ                      =  0x000020A2,
  MID_DBG_DISCONNECT_CNF                      =  0x000020A3,


  /*
  ** Summary of the AS-Interface ECTRL-Task
  */

  ASI_ECTRL_PACKET_COMMAND_START              =  0x2100,

  /* Set general AS-Interface network parameter */
  ASI_ECTRL_CMD_SET_OFF_PHASE_REQ             =  0x2100,
  ASI_ECTRL_CMD_SET_OFF_PHASE_CNF             =  0x2101,

  ASI_ECTRL_CMD_SET_OP_MODE_REQ               =  0x2102,
  ASI_ECTRL_CMD_SET_OP_MODE_CNF               =  0x2103,

  ASI_ECTRL_CMD_SET_DATA_EXCH_REQ             =  0x2104,
  ASI_ECTRL_CMD_SET_DATA_EXCH_CNF             =  0x2105,

  ASI_ECTRL_CMD_SET_AUTO_ADDR_REQ             =  0x2106,
  ASI_ECTRL_CMD_SET_AUTO_ADDR_CNF             =  0x2107,


  /* Single transactions on AS-Interface network */
  ASI_ECTRL_CMD_WRITE_PARAM_REQ               =  0x2108,
  ASI_ECTRL_CMD_WRITE_PARAM_CNF               =  0x2109,

  ASI_ECTRL_CMD_WRITE_ID1_CODE_REQ            =  0x210A,
  ASI_ECTRL_CMD_WRITE_ID1_CODE_CNF            =  0x210B,

  ASI_ECTRL_CMD_CHANGE_ADDR_REQ               =  0x210C,
  ASI_ECTRL_CMD_CHANGE_ADDR_CNF               =  0x210D,

  ASI_ECTRL_CMD_EXECUTE_CMD_REQ               =  0x210E,
  ASI_ECTRL_CMD_EXECUTE_CMD_CNF               =  0x210F,


  /* Get/Set Master state and Slave config */
  ASI_ECTRL_CMD_GET_STATE_REQ                 =  0x2110,
  ASI_ECTRL_CMD_GET_STATE_CNF                 =  0x2111,

  ASI_ECTRL_CMD_GET_ACT_CONFIG_REQ            =  0x2112,
  ASI_ECTRL_CMD_GET_ACT_CONFIG_CNF            =  0x2113,

  ASI_ECTRL_CMD_GET_PERM_CONFIG_REQ           =  0x2114,
  ASI_ECTRL_CMD_GET_PERM_CONFIG_CNF           =  0x2115,

  ASI_ECTRL_CMD_SET_PERM_PARAM_REQ            =  0x2116,
  ASI_ECTRL_CMD_SET_PERM_PARAM_CNF            =  0x2117,

  ASI_ECTRL_CMD_STORE_ACT_PARAM_REQ           =  0x2118,
  ASI_ECTRL_CMD_STORE_ACT_PARAM_CNF           =  0x2119,

  ASI_ECTRL_CMD_SET_PERM_CONFIG_REQ           =  0x211A,
  ASI_ECTRL_CMD_SET_PERM_CONFIG_CNF           =  0x211B,

  ASI_ECTRL_CMD_STORE_ACT_CONFIG_REQ          =  0x211C,
  ASI_ECTRL_CMD_STORE_ACT_CONFIG_CNF          =  0x211D,


  /* Acyclic Read/Write request via combined transaction type 1 */
  ASI_ECTRL_CMD_READ_ID_STR_REQ               =  0x211E,
  ASI_ECTRL_CMD_READ_ID_STR_CNF               =  0x211F,

  ASI_ECTRL_CMD_READ_PARAM_STR_REQ            =  0x2120,
  ASI_ECTRL_CMD_READ_PARAM_STR_CNF            =  0x2121,

  ASI_ECTRL_CMD_READ_DIAG_STR_REQ             =  0x2122,
  ASI_ECTRL_CMD_READ_DIAG_STR_CNF             =  0x2123,

  ASI_ECTRL_CMD_WRITE_PARAM_STR_REQ           =  0x2124,
  ASI_ECTRL_CMD_WRITE_PARAM_STR_CNF           =  0x2125,


  /* Get/Set cyclic I/O data */
  ASI_ECTRL_CMD_READ_IN_DATA_REQ              =  0x2126,
  ASI_ECTRL_CMD_READ_IN_DATA_CNF              =  0x2127,

  ASI_ECTRL_CMD_WRITE_OUT_DATA_REQ            =  0x2128,
  ASI_ECTRL_CMD_WRITE_OUT_DATA_CNF            =  0x2129,

  ASI_ECTRL_CMD_READ_ANLG_IN_DATA_REQ         =  0x212A,
  ASI_ECTRL_CMD_READ_ANLG_IN_DATA_CNF         =  0x212B,

  ASI_ECTRL_CMD_WRITE_ANLG_OUT_DATA_REQ       =  0x212C,
  ASI_ECTRL_CMD_WRITE_ANLG_OUT_DATA_CNF       =  0x212D,


  /*Serial stringtransfer via combined transaction type 2 */
  ASI_ECTRL_CMD_READ_SERIAL_STRING_REQ        =  0x212E,
  ASI_ECTRL_CMD_READ_SERIAL_STRING_CNF        =  0x212F,

  ASI_ECTRL_CMD_WRITE_SERIAL_STRING_REQ       =  0x2130,
  ASI_ECTRL_CMD_WRITE_SERIAL_STRING_CNF       =  0x2131,


  /* Special Task internal commands */
  ASI_ECTRL_CMD_CYCLE_EVENT_REQ               =  0x21F0,
  ASI_ECTRL_CMD_CYCLE_EVENT_CNF               =  0x21F1,

  /*
  ** Summary of the Profibus FSPMM (Fieldbus Service Protocol Machine - Master) service commands and primitives
  */
  /* PROFIBUS_FSPMM_PACKET_COMMAND_START      = 0x00002200, */

  /*
  ** Summary of the LLDP service commands and primitives
  */
  LLDP_PACKET_COMMAND_START                   = 0x00002300,

  /*
  ** Summary of the MibDatabase-Task (part of the SNMP-Implementation) service commands and primitives
  */

  MIB_DATABASE_COMMAND_START                  = 0x00002400,

  /*
  ** Summary of the SnmpServer-Task (part of the SNMP-Implementation) service commands and primitives
  */
  SNMP_SERVER_COMMAND_START                   = 0x00002500,

  /*
  ** Summary of the Ecat Cyclic Commands: service commands and primitives
  */
  ECAT_CYCLIC_COMMAND_START                   = 0x00002600,

  /*
  ** Summary of the DDL ENPDDL task service commands and primitives
  ** Project: J060219 Bosch Rexroth DDL mit netX
  */
  DDL_ENPDDL_PACKET_COMMAND_START             = 0x00002700,

  DDL_ENPDDL_CMD_CYCLE_EVENT_REQ              = 0x00002700,
  DDL_ENPDDL_CMD_CYCLE_EVENT_CNF              = 0x00002701,

  DDL_ENPDDL_CMD_TIMEOUT_AUTO_ADR_REQ         = 0x00002702,
  DDL_ENPDDL_CMD_TIMEOUT_AUTO_ADR_CNF         = 0x00002703,

  DDL_ENPDDL_CMD_TIMEOUT_MANUAL_ADR_REQ       = 0x00002704,
  DDL_ENPDDL_CMD_TIMEOUT_MANUAL_ADR_CNF       = 0x00002705,

  DDL_ENPDDL_CMD_TIMEOUT_PARAMETER_REQ        = 0x00002706,
  DDL_ENPDDL_CMD_TIMEOUT_PARAMETER_CNF        = 0x00002707,

  DDL_ENPDDL_CMD_TIMEOUT_DATA_REQ             = 0x00002708,
  DDL_ENPDDL_CMD_TIMEOUT_DATA_CNF             = 0x00002709,

  DDL_ENPDDL_CMD_TIMEOUT_WAIT_SEND_REQ        = 0x0000270A,
  DDL_ENPDDL_CMD_TIMEOUT_WAIT_SEND_CNF        = 0x0000270B,

  DDL_ENPDDL_CMD_TIMEOUT_ERROR_REQ            = 0x0000270C,
  DDL_ENPDDL_CMD_TIMEOUT_ERROR_CNF            = 0x0000270D,

  DDL_ENPDDL_CMD_CAN_DL_BUS_OFF_DELAY_REQ     = 0x0000270E,
  DDL_ENPDDL_CMD_CAN_DL_BUS_OFF_DELAY_CNF     = 0x0000270F,


  /*
  ** Summary of the CANopen Master Task
  */
  CANOPEN_MASTER_PACKET_COMMAND_START         = 0x00002800,

  /*
  ** Summary of the CANopen Slave Task
  */
  CANOPEN_SLAVE_PACKET_COMMAND_START          = 0x00002900,

  /* Special Task internal commands */
  CANOPEN_SLAVE_CMD_CYCLE_EVENT_REQ           = 0x000029F0,
  CANOPEN_SLAVE_CMD_CYCLE_EVENT_CNF           = 0x000029F1,


  /*
  ** Summary of the CAN DL Task service commands and primitives
  */
  CAN_DL_PACKET_COMMAND_START                 = 0x00002A00,

  /*
  ** Commands used by Mid_Sys and routers to specify message routing for applications not knowing the instance
  */
  MID_SYS_LOG_PACKET_COMMAND_START            = 0x00002B00,

  /*
  ** Commands used by the Object Dictionary DPM adapter to initialize the link between stack and DPM
  * (used by EcatDPM task as well)
  */

  DPM_OD2_PACKET_COMMAND_START                = 0x00002C00,

  /*
  ** Summary of the DeviceNet Slave Filedbus Application Layer Task
  */
  DNS_FAL_PACKET_COMMAND_START                = 0x00002D00,

  /*
  ** Summary of the CANopen Slave Application Task
  */
  CANOPEN_APS_PACKET_COMMAND_START            = 0x00002E00,

  CANOPEN_APS_CMD_CYCLE_EVENT_REQ             = 0x00002E00,
  CANOPEN_APS_CMD_CYCLE_EVENT_CNF             = 0x00002E01,

  /*
  ** Summary of stack common application packets
  */

  DIAG_INFO_PACKET_COMMAND_START              = 0x00002F00,

  /*
  ** Summary of Profibus APM Task commands
  */
  PROFIBUS_APM_PACKET_COMMAND_START           = 0x00003000,

  /*
  ** Summary of Profibus APM Task commands
  */
  PROFIBUS_APS_PACKET_COMMAND_START           = 0x00003100,

  /*
  ** Summary of Profibus APM Task commands
  */
  SERCOSIII_SL_COM_PACKET_COMMAND_START       = 0x00003200,
  SERCOSIII_SL_RTD_PACKET_COMMAND_START       = 0x00003300,
  SERCOSIII_SL_SVC_PACKET_COMMAND_START       = 0x00003400,
  SERCOSIII_SL_AP_PACKET_COMMAND_START        = 0x00003500,

  /*
  ** Summary of the Ethernet/IP APS (Slave/Adapter) task service commands and primitives
  */
  EIP_APS_PACKET_COMMAND_START                = 0x00003600,

  /*
  ** Summary of the Ethernet/IP APM (Master/Scanner) task service commands and primitives
  */
  EIP_APM_PACKET_COMMAND_START                = 0x00003700,

  /*
  ** Summary of DeviceNet FAL Task commands
  */
  DEVNET_FAL_PACKET_COMMAND_START             = 0x00003800,

  /*
  ** Summary of DeviceNet APM Task commands
  */
  DEVNET_AP_PACKET_COMMAND_START              = 0x00003900,

  /*
  ** Summary of the CANopen Master Application Task
  */
  CANOPEN_APM_PACKET_COMMAND_START            = 0x00003A00,


  /*
  ** Summary of the Ethernet Interface Task
  */
  ETH_INTF_PACKET_COMMAND_START               = 0x00003B00,


  /*
  ** Summary of the PNS_32BITIO AP Task
  */
  PNS_32BITIO_PACKET_COMMAND_START            = 0x00003C00,


  /*
  ** Summary of the PNS_4BITIO AP Task
  */
  PNS_4BITIO_PACKET_COMMAND_START             = 0x00003D00,

  /*
  ** Mid Startup Task
  */
  MID_STARTUP_PACKET_COMMAND_START            = 0x00003E00,


  /*
  ** Start value of OMB OMBTASK
  */
  OMB_OMBTASK_PACKET_COMMAND_START            = 0x00003F00,


  /*
  ** Start value of OMB OMBAPTASK
  */
  OMB_OMBAPTASK_PACKET_COMMAND_START          = 0x00004000,

  /*
  ** Summary of the DeviceNet Slave Application Layer Task
  */
  DNS_APS_PACKET_COMMAND_START                = 0x00004100,

  /*
  ** Summary of the Profibus MPI Application Layer Task
  */
  PROFIBUS_MPI_AP_PACKET_COMMAND_START        = 0x00004200,

  /*
  ** Summary of the Profibus MPI Layer Task
  */
  PROFIBUS_MPI_PACKET_COMMAND_START           = 0x00004300,

  /*
  ** Summary of the Profibus FSPMM2 Layer Task
  */
  PROFIBUS_FSPMM2_PACKET_COMMAND_START        = 0x00004400,

  /*
  ** Summary of the CC-Link Slave Task
  */
  CCLINK_SLAVE_PACKET_COMMAND_START           = 0x00004500,

  /*
  ** Summary of the CC-Link Slave Application Task
  */
  CCLINK_APS_PACKET_COMMAND_START             = 0x00004600,

  /*
  ** Summary of the Modbus RTU Task
  */
  MODBUS_RTU_PACKET_COMMAND_START             = 0x00004700,

  /*
  ** Summary of the Sercos III Master CP Task
  */
  SIII_MA_CP_PACKET_COMMAND_START             = 0x00004800,

  /*
  ** Summary of the Sercos III Master Svc Task
  */
  SIII_MA_SVC_PACKET_COMMAND_START            = 0x00004900,

  /*
  ** Summary of the Sercos III Master AP Task
  */
  SIII_MA_AP_PACKET_COMMAND_START             = 0x00004A00,

  /*
  ** Summary of module load packets
  */
  RCX_MODLOAD_PACKET_COMMAND_START            = 0x00004B00,

  /*
  ** Summary of SSIO packets
  */
  SSIO_COMMAND_START                          = 0x00004C00,

  /*
  ** Summary of SSIO packets
  */
  SSIO_AP_COMMAND_START                       = 0x00004D00,

  /*
  ** Summary of Memory Mapping packets
  */
  MEMORY_MAP_COMMAND_START                    = 0x00004E00,

  /*
  ** Summary of TCPIP SOCKIF packets
  */
  TCPIP_SOCKIF_PACKET_COMMAND_START           = 0x00004F00,

  /*
  ** Summary of the Sercos III Master NRT Task
  */
  SIII_MA_NRT_PACKET_COMMAND_START            = 0x00005000,

  /*
  ** Summary of the NetScript task
  */
  NETSCRIPT_COMMAND_START                     = 0x00005100,

  /*
  ** Summary of the AS-Interface Master Task
  */
  ASI_MASTER_PACKET_COMMAND_START             = 0x00005200,

  /*
  ** Summary of the AS-Interface Master Application Task
  */
  ASI_APM_PACKET_COMMAND_START                = 0x00005300,

  /*
  ** Summary of the CompoNet Slave Task
  */
  COMPONET_SLAVE_COMMAND_START                = 0x00005400,

  /*
  ** Summary of the CompoNet Slave Applicatition Task
  */
  COMPONET_SLAVE_AP_COMMAND_START             = 0x00005500,

  /*
  ** Summary of the ASCII Protocol Task
  */
  ASCII_COMMAND_START                         = 0x00005600,

  /*
  ** Summary of the ASCII Application Task
  */
  ASCII_AP_COMMAND_START                      = 0x00005700,

  /*
  ** Summary of Ecs SoE commands
  */
  ECAT_SOE_COMMAND_START                      = 0x00005800,

  /*
  ** Summary of netPLC (Codesys Variant) commands
  */
  NPLC_CODESYS_AP_COMMAND_START               = 0x00005900,


  /*
  ** Summary of SercosIII Slave Stack IDN commands
  */
  SERCOSIII_SL_IDN_PACKET_COMMAND_START       = 0x00005A00,

  /*
  ** Summary of Item Server task commands
  */
  ITEM_SERVER_PACKET_COMMAND_START            = 0x00005B00,

  /*
  ** Summary of DF1 stack task commands
  */
  DF1_PACKET_COMMAND_START                     = 0x00005C00,

  /*
  ** Summary of DF1 AP task commands
  */
  DF1_AP_PACKET_COMMAND_START                  = 0x00005D00,

  /*
  ** Summary of 3964R stack task commands
  */
  P3964R_PACKET_COMMAND_START                  = 0x00005E00,

  /*
  ** Summary of 3964R AP task commands
  */
  P3964R_AP_PACKET_COMMAND_START               = 0x00005F00,

  /*
  ** Summary of ISAGraf AP task commands
  */
  ISAGRAF_AP_PACKET_COMMAND_START              = 0x00006000,

  /*
  ** Summary of IO Signals task commands
  */
  IO_SIGNALS_PACKET_COMMAND_START              = 0x00006100,

  /*
  ** RTR UART task commands
  */
  RTR_UART_PACKET_COMMAND_START                = 0x00006200,

  /*
  ** RFC1006 task commands
  */
  RFC1006_AP_PACKET_COMMAND_START              = 0x00006300,


  /*
  ** RFC1006 task commands
  */
  RFC1006_STACK_PACKET_COMMAND_START           = 0x00006400,

  /*
  ** Ethernet/IP DLR task commands
  */
  EIP_DLR_PACKET_COMMAND_START                 = 0x00006500,

  /*
  ** SERCOS III Slave NRT task commands
  */
  SERCOSIII_SL_NRT_PACKET_COMMAND_START        = 0x00006600,

  /*
  ** OEM Device - can be used for all customer specific tasks
  */
  OEM_DEVICE_PACKET_COMMAND_START              = 0x00006700,

  /*
  ** TCPIP AP Task
  */
  TCPIP_AP_PACKET_COMMAND_START                = 0x00006800,

  /*
  ** FODMI Task
  */
  FODMI_PACKET_COMMAND_START                   = 0x00006900,

  /*
  ** ODv3 Task
  */
  ODV3_PACKET_COMMAND_START                    = 0x00006A00,

  /*
  ** PROFIDRIVE - GSM  Task
  */
  PROFIDRIVE_PACKET_COMMAND_START              = 0x00006B00,

  /*
  ** PROFIDRIVE - PA  Task
  */
  PROFIDRIVE_PA_PACKET_COMMAND_START           = 0x00006C00,

  /*
  ** PROFIDRIVE - OD  Task
  */
  PROFIDRIVE_OD_PACKET_COMMAND_START           = 0x00006D00,

  /*
  ** PROFIDRIVE - AP Task
  */
  PROFIDRIVE_AP_PACKET_COMMAND_START           = 0x00006E00,


  /*
  ** VARAN Client - Task
  */
  VARAN_CLIENT_PACKET_COMMAND_START            = 0x00006F00,

  /*
  ** VARAN Client - AP Task
  */
  VARAN_CLIENT_AP_PACKET_COMMAND_START         = 0x00007000,


  /*
  ** PROFINET RTA Task
  */
  PROFINET_RTA_PACKET_COMMAND_START            = 0x00007100,

  /*
  ** Modbus RTU Peripheral Task
  */
  MBR_PERIPH_PACKET_COMMAND_START              = 0x00007200,

  /*
  ** CODE SYS PLC Handler AP Task
  */
  CODESYS_AP_PLCHANDLER_PACKET_COMMAND_START   = 0x00007300,

  /*
  ** CODE SYS PLC Handler Task
  */
  CODESYS_PLCHANDLER_PACKET_COMMAND_START      = 0x00007400,



  /*
  ** PNS INX AP Task
  */
  PNSINX_AP_PACKET_COMMAND_START               = 0x00007F00,

  /*
  ** SercosIII SIP Task
  */
  SIII_SIP_PACKET_COMMAND_START                = 0x00008000,

  /*
  ** Packets for sercos test master firmware
  */
  SIII_MA_TEST_PACKET_COMMAND_START            = 0x00008100,

  /*
  ** Packets for Powerlink MN Packet Task
  */
  EPLMN_PCK_PACKET_COMMAND_START               = 0x00008200,

  /*
  ** Packets for Powerlink MN AP Task
  */
  EPLMN_AP_PACKET_COMMAND_START                = 0x00008300,

  /*
  ** Packets for SmartWire Master Task
  */
  SMARTWIRE_MASTER_PACKET_COMMAND_START        = 0x00008400,

  /*
  ** Packets for POWERLINK TestMaster
  */
  POWERLINK_TEST_MASTER_PACKET_START           = 0x00008500,

  /*
   * Packets for PROFINET IO common
   */
  PNIO_COMMON_PACKET_START                     = 0x00008600,

  /*
   * Packets for Trivial File Server API
   */
  TRIVIAL_FILE_SERVER_API_PACKET_START         = 0x00008700,

  /*
   * Packets for netProxy API
   */
  NPX_API_PACKET_START                         = 0x00008800,

  /*
   * Second set of packets for sercos master CP task
   */
  SIII_MA_CP_PACKET_2ND_SET_COMMAND_START      = 0x00008900,

  /*
   * Commands for sercos master Auto configure task
   */
  SIII_MA_ACFG_PACKET_START                    = 0x00008A00,

  /*
   * Commands for TFTP Stack task
   */
  TFTP_STACK_PACKET_START                      = 0x00008B00,

  /*
   * Commands for TFTP Application task
   */
  TFTP_APP_PACKET_START                        = 0x00008C00,

  /*
   * Commands for ECS AOE task
   */
  ECS_AOE_PACKET_START                         = 0x00008D00,

  /*
   *  Commands for the PTP stack of EtherNet/IP
   */
  EIP_PTP_PACKET_COMMAND_START                 =  0x00008E00,

  /*
   * Commands for sercos master S/IP client task
   */
  SIII_MA_SIP_PACKET_START                     = 0x00008F00,

  /*
   * Commands for sercos master SMP task
   */
  SIII_MA_SMP_PACKET_START                     = 0x00009000,

  /*
   * Commands for IO-Link master DL task
   */
  IOLM_DL_PACKET_START                         = 0x00009100,

  /*
   * Commands for IO-Link master AL task
   */
  IOLM_AL_PACKET_START                         = 0x00009200,

  /*
   * Commands for SIF
   */
  SIF_PACKET_START                             = 0x00009300,

  /*
   * Commands for Profinet IO-Controller AP task
   */
  PNM_AP_CFG_PACKET_COMMAND_START              = 0x00009400,

  /*
   * Commands for ECS FoE
   */
  ECS_FOE_PACKET_COMMAND_START                 = 0x00009500,


  /** Socket Api Commands
   *
   */
  SOCK_PACKET_COMMAND_START                    = 0x00009600,

  /** ECMv4 API
   *
   */
  ECM_COMMAND_START                            = 0x00009700,

  /** ECMv4 API - MBX
   *
   */
  ECM_MBX_COMMAND_START                        = 0x00009800,

  /** ECMv4 API - FoE
   *
   */
  ECM_FOE_COMMAND_START                        = 0x00009900,

  /** ECMv4 API - CoE
   *
   */
  ECM_COE_COMMAND_START                        = 0x00009A00,

  /** ECMv4 API - SoE
   *
   */
  ECM_SOE_COMMAND_START                        = 0x00009B00,

  /** ECMv4 API - EoE
   *
   */
  ECM_EOE_COMMAND_START                        = 0x00009C00,

  /** ECMv4 API - AoE
   *
   */
  ECM_AOE_COMMAND_START                        = 0x00009D00,

  /** ECMv4 API - Interface
   *
   */
  ECM_IF_COMMAND_START                         = 0x00009E00,

  /** ECMv4 API - AP
   *
   */
  ECM_AP_COMMAND_START                         = 0x00009F00,

  /** Ethernet/IP Class1 Task
   *
   */
  EIP_CL1_PACKET_COMMAND_START                 = 0x0000A000,

  /** PLS AP Task
   *
   */
  PLS_AP_PACKET_COMMAND_START                  = 0x0000A100,

  /** PLS IF Task
   *
   */
  PLS_IF_PACKET_COMMAND_START                  = 0x0000A200,

  /** Command Table Task
   *
   */
  CMDTBL_COMMAND_START                         = 0x0000A300,

  /** DPM Bridge Task
   *
   */
  DPM_BRIDGE_PACKET_COMMAND_START              = 0x0000A400,

  /** Base Firmware Application Task
   *
   */
  BASEFW_AP_PACKET_COMMAND_START               = 0x0000A500,

  /** CCLink IE
   *
   */
  CCLIES_COMMAND_START                         = 0x0000A600,

  CCLIES_IF_COMMAND_START                      = 0x0000A700,

  CCLIES_AP_COMMAND_START                      = 0x0000A800,

  /*
   * IO-Link Test Protocol Task
   */
  IOLT_COMMAND_START                           = 0x0000A900,

  /*
   * CCLink IE Field Basic
   */

  CCLIEFB_COMMAND_START                         = 0x0000AA00,

  CCLIEFB_AP_COMMAND_START                      = 0x0000AB00,

  CCLIEFBM_COMMAND_START                        = 0x0000AC00,

  /*
   * Commands for EtherCAT master V2.X/V3.X
   */
  ETHERCAT_MASTER_V2_X_V3_X_AP_PACKET_START    = 0x00640000,
  ETHERCAT_MASTER_V2_X_V3_X_PACKET_START       = 0x00650000,

  /*
  ** Start value where a USER may define its own commands
  */
  USER_PACKET_COMMAND_START                    = 0x01000000,

};

typedef enum HIL_COMMAND_Etag       HIL_COMMAND_E;


/***************************************************************************************/


#endif  /* __HIL_COMMANDS_H */
