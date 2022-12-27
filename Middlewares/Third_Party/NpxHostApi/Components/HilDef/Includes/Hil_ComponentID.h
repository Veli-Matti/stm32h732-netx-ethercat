#ifndef __HIL_TASK_IDENTIFIER_H
#define __HIL_TASK_IDENTIFIER_H

#include <stdint.h>

/////////////////////////////////////////////////////////////////////////////////////
// Hilscher TASKIDENTIFIER definitions
/////////////////////////////////////////////////////////////////////////////////////

//
// MessageId: HIL_TASK_ID_UNKNOWN_IDENTIFIER
//
// MessageText:
//
//  The task identifier is unknown.
//
#define HIL_TASK_ID_UNKNOWN_IDENTIFIER   ((uint32_t)0x00000000L)

/////////////////////////////////////////////////////////////////////////////////////
// TLR Timer identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_TIMER
//
// MessageText:
//
//  TLR Timer Task.
//
#define HIL_TASK_ID_TIMER                ((uint32_t)0x00020001L)

/////////////////////////////////////////////////////////////////////////////////////
// System task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_MID_SYS
//
// MessageText:
//
//  Middleware System Task.
//
#define HIL_TASK_ID_MID_SYS              ((uint32_t)0x00010001L)

//
// MessageId: HIL_TASK_ID_MID_DBG
//
// MessageText:
//
//  Middleware System Debug Backend Task.
//
#define HIL_TASK_ID_MID_DBG              ((uint32_t)0x00010002L)

//
// MessageId: HIL_TASK_ID_RX_IDLE
//
// MessageText:
//
//  RX IDLE Task.
//
#define HIL_TASK_ID_RX_IDLE              ((uint32_t)0x00010003L)

//
// MessageId: HIL_TASK_ID_IRQ_HANDLER
//
// MessageText:
//
//  IRQ Handler Task.
//
#define HIL_TASK_ID_IRQ_HANDLER          ((uint32_t)0x00010004L)

//
// MessageId: HIL_TASK_ID_IDLE
//
// MessageText:
//
//  Idle Task.
//
#define HIL_TASK_ID_IDLE                 ((uint32_t)0x00010005L)

//
// MessageId: HIL_TASK_ID_BOOTUP
//
// MessageText:
//
//  Bootup Task.
//
#define HIL_TASK_ID_BOOTUP               ((uint32_t)0x00010006L)

//
// MessageId: HIL_TASK_ID_RX_TIMER
//
// MessageText:
//
//  rcX Timer.
//
#define HIL_TASK_ID_RX_TIMER             ((uint32_t)0x00010007L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT Base stack task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ECAT
//
// MessageText:
//
//  EtherCAT Stack.
//
#define HIL_TASK_ID_ECAT                 ((uint32_t)0x00200000L)

//
// MessageId: HIL_TASK_ID_ECAT_ESM
//
// MessageText:
//
//  EtherCAT ESM Task.
//
#define HIL_TASK_ID_ECAT_ESM             ((uint32_t)0x00200001L)

//
// MessageId: HIL_TASK_ID_ECAT_MBX
//
// MessageText:
//
//  EtherCAT Mailbox Task.
//
#define HIL_TASK_ID_ECAT_MBX             ((uint32_t)0x00200002L)

//
// MessageId: HIL_TASK_ID_ECAT_CYCLIC_IN
//
// MessageText:
//
//  EtherCAT Cyclic Input Task.
//
#define HIL_TASK_ID_ECAT_CYCLIC_IN       ((uint32_t)0x00200003L)

//
// MessageId: HIL_TASK_ID_ECAT_CYCLIC_OUT
//
// MessageText:
//
//  EtherCAT Cyclic Output Task.
//
#define HIL_TASK_ID_ECAT_CYCLIC_OUT      ((uint32_t)0x00200004L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT CoE stack task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ECAT_COE
//
// MessageText:
//
//  EtherCAT CoE Task.
//
#define HIL_TASK_ID_ECAT_COE             ((uint32_t)0x00210001L)

//
// MessageId: HIL_TASK_ID_ECAT_COE_PDO
//
// MessageText:
//
//  EtherCAT CoE PDO Task.
//
#define HIL_TASK_ID_ECAT_COE_PDO         ((uint32_t)0x00210002L)

//
// MessageId: HIL_TASK_ID_ECAT_COE_SDO
//
// MessageText:
//
//  EtherCAT CoE SDO Task.
//
#define HIL_TASK_ID_ECAT_COE_SDO         ((uint32_t)0x00210003L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT VoE stack task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ECAT_VOE
//
// MessageText:
//
//  EtherCAT VoE Task.
//
#define HIL_TASK_ID_ECAT_VOE             ((uint32_t)0x00260001L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT FoE stack task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ECAT_FOE
//
// MessageText:
//
//  EtherCAT FoE Task.
//
#define HIL_TASK_ID_ECAT_FOE             ((uint32_t)0x00240001L)

//
// MessageId: HIL_TASK_ID_ECAT_FOE_FH
//
// MessageText:
//
//  EtherCAT FoE File Handler Task.
//
#define HIL_TASK_ID_ECAT_FOE_FH          ((uint32_t)0x00240002L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT EoE stack task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ECAT_EOE
//
// MessageText:
//
//  EtherCAT EoE Task.
//
#define HIL_TASK_ID_ECAT_EOE             ((uint32_t)0x00230001L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT SoE stack task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ECAT_SOE_SSC
//
// MessageText:
//
//  EtherCAT SoE SSC-Task.
//
#define HIL_TASK_ID_ECAT_SOE_SSC         ((uint32_t)0x00220001L)

//
// MessageId: HIL_TASK_ID_ECAT_SOE_IDN
//
// MessageText:
//
//  EtherCAT SoE IDN-Task.
//
#define HIL_TASK_ID_ECAT_SOE_IDN         ((uint32_t)0x00220002L)

/////////////////////////////////////////////////////////////////////////////////////
// Example Tasks
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_EXAMPLE_TASK1
//
// MessageText:
//
//  Example Task 1.
//
#define HIL_TASK_ID_EXAMPLE_TASK1        ((uint32_t)0x00030001L)

//
// MessageId: HIL_TASK_ID_EXAMPLE_TASK2
//
// MessageText:
//
//  Example Task 2.
//
#define HIL_TASK_ID_EXAMPLE_TASK2        ((uint32_t)0x00040001L)

//
// MessageId: HIL_TASK_ID_EXAMPLE_TASK3
//
// MessageText:
//
//  Example Task 3.
//
#define HIL_TASK_ID_EXAMPLE_TASK3        ((uint32_t)0x00050001L)

/////////////////////////////////////////////////////////////////////////////////////
// Ethernet/IP Encapsulation
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_EIP_ENCAP
//
// MessageText:
//
//  EthernetIP Encapsulation Task.
//
#define HIL_TASK_ID_EIP_ENCAP            ((uint32_t)0x001E0001L)

//
// MessageId: HIL_TASK_ID_EIP_CL1
//
// MessageText:
//
//  EthernetIP Encapsulation Task Class 1 services.
//
#define HIL_TASK_ID_EIP_CL1              ((uint32_t)0x001E0002L)

/////////////////////////////////////////////////////////////////////////////////////
// Ethernet/IP Object
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_EIP_OBJECT
//
// MessageText:
//
//  EthernetIP Object Task.
//
#define HIL_TASK_ID_EIP_OBJECT           ((uint32_t)0x001F0001L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherNet/Ip HAL EDD 2PS task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_EIP_EDD_LOW
//
// MessageText:
//
// EtherNet/Ip Low Priority EDD Task.
//
#define HIL_TASK_ID_EIP_EDD_LOW          ((uint32_t)0x00EF0001L)

//
// MessageId: HIL_TASK_ID_EIP_EDD_HIGH
//
// MessageText:
//
// EtherNet/Ip High Priority EDD Task.
//
#define HIL_TASK_ID_EIP_EDD_HIGH         ((uint32_t)0x00EE0001L)




/////////////////////////////////////////////////////////////////////////////////////
// PROFINET IO task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_PNIO_CMCTL
//
// MessageText:
//
//  PROFINET IO-Controller Context Management Task.
//
#define HIL_TASK_ID_PNIO_CMCTL           ((uint32_t)0x000A0001L)

//
// MessageId: HIL_TASK_ID_PNIO_CMDEV
//
// MessageText:
//
//  PROFINET IO-Device Context Management Task.
//
#define HIL_TASK_ID_PNIO_CMDEV           ((uint32_t)0x000B0001L)

//
// MessageId: HIL_TASK_ID_PNIO_ACP
//
// MessageText:
//
//  PROFINET IO ACP Task.
//
#define HIL_TASK_ID_PNIO_ACP             ((uint32_t)0x00110001L)

//
// MessageId: HIL_TASK_ID_PNIO_DCP
//
// MessageText:
//
//  PROFINET IO DCP Task.
//
#define HIL_TASK_ID_PNIO_DCP             ((uint32_t)0x00120001L)

//
// MessageId: HIL_TASK_ID_PNIO_EDD
//
// MessageText:
//
//  PROFINET IO EDD Task.
//
#define HIL_TASK_ID_PNIO_EDD             ((uint32_t)0x000E0001L)

//
// MessageId: HIL_TASK_ID_PNIO_MGT
//
// MessageText:
//
//  PROFINET IO Management Task.
//
#define HIL_TASK_ID_PNIO_MGT             ((uint32_t)0x00130001L)

//
// MessageId: HIL_TASK_ID_PNIO_APCTL
//
// MessageText:
//
//  PROFINET IO-Controller Application Task.
//
#define HIL_TASK_ID_PNIO_APCTL           ((uint32_t)0x000C0001L)

//
// MessageId: HIL_TASK_ID_PNIO_APDEV
//
// MessageText:
//
//  PROFINET IO-Device Application Task.
//
#define HIL_TASK_ID_PNIO_APDEV           ((uint32_t)0x000D0001L)

//
// MessageId: HIL_TASK_ID_PNIO_APCFG
//
// MessageText:
//
//  PROFINET IO-Controller Configuration Task.
//
#define HIL_TASK_ID_PNIO_APCFG           ((uint32_t)0x00140001L)

//
// MessageId: HIL_TASK_ID_PNS_IF
//
// MessageText:
//
//  PROFINET IO-Device Interface Task.
//
#define HIL_TASK_ID_PNS_IF               ((uint32_t)0x00300001L)

//
// MessageId: HIL_TASK_ID_PNIOD_16BITIO
//
// MessageText:
//
//  PROFINET IO-Device 16Bit IO Application Task.
//
#define HIL_TASK_ID_PNIOD_16BITIO        ((uint32_t)0x003A0001L)

//
// MessageId: HIL_TASK_ID_PNS_32BITIO
//
// MessageText:
//
//  PROFINET IO-Device 32Bit IO Application Task.
//
#define HIL_TASK_ID_PNS_32BITIO          ((uint32_t)0x005E0001L)

//
// MessageId: HIL_TASK_ID_PNS_4BITIO
//
// MessageText:
//
//  PROFINET IO-Device 4Bit IO Application Task.
//
#define HIL_TASK_ID_PNS_4BITIO           ((uint32_t)0x00450001L)

//
// MessageId: HIL_TASK_ID_PNS_SOCKET_SRV
//
// MessageText:
//
//  PROFINET IO-Device Socket Server Task.
//
#define HIL_TASK_ID_PNS_SOCKET_SRV       ((uint32_t)0x00520001L)

//
// MessageId: HIL_TASK_ID_PNS_EDD_HIGH
//
// MessageText:
//
//  PROFINET IO-Device High Priority EDD Task.
//
#define HIL_TASK_ID_PNS_EDD_HIGH         ((uint32_t)0x00530001L)

//
// MessageId: HIL_TASK_ID_PNS_EDD_LOW
//
// MessageText:
//
//  PROFINET IO-Device Low Priority EDD Task.
//
#define HIL_TASK_ID_PNS_EDD_LOW          ((uint32_t)0x00540001L)

//
// MessageId: HIL_TASK_ID_PNS_SOCKET
//
// MessageText:
//
//  PROFINET IO-Device Socket Task.
//
#define HIL_TASK_ID_PNS_SOCKET           ((uint32_t)0x00550001L)

//
// MessageId: HIL_TASK_ID_PNS_DCP
//
// MessageText:
//
//  PROFINET IO-Device DCP Task.
//
#define HIL_TASK_ID_PNS_DCP              ((uint32_t)0x00560001L)

//
// MessageId: HIL_TASK_ID_PNS_CLRPC
//
// MessageText:
//
//  PROFINET IO-Device Connectionless RPC Task.
//
#define HIL_TASK_ID_PNS_CLRPC            ((uint32_t)0x00570001L)

//
// MessageId: HIL_TASK_ID_PNS_IF_INTERN
//
// MessageText:
//
//  PROFINET IO-Device Stack internal Interface Task.
//
#define HIL_TASK_ID_PNS_IF_INTERN        ((uint32_t)0x00580001L)

//
// MessageId: HIL_TASK_ID_PNIO_IRT_SCHEDULER
//
// MessageText:
//
//  PROFINET IO IRT Scheduler Task.
//
#define HIL_TASK_ID_PNIO_IRT_SCHEDULER   ((uint32_t)0x00810001L)

//
// MessageId: HIL_TASK_ID_PNIO_RTA
//
// MessageText:
//
//  PROFINET IO RTA Task.
//
#define HIL_TASK_ID_PNIO_RTA             ((uint32_t)0x00A70001L)

//
// MessageId: HIL_TASK_ID_PNIO_RTC
//
// MessageText:
//
//  PROFINET IO RTC Task.
//
#define HIL_TASK_ID_PNIO_RTC             ((uint32_t)0x00A80001L)

//
// MessageId: HIL_TASK_ID_FODMI_TASK
//
// MessageText:
//
//  PROFINET IO FODMI (FiberOptic Diagnosis) Task.
//
#define HIL_TASK_ID_FODMI_TASK           ((uint32_t)0x00A90001L)

//
// MessageId: HIL_TASK_ID_PNIO_HAL_COMPUTE
//
// MessageText:
//
//  PROFINET IO HAL protocol Task.
//
#define HIL_TASK_ID_PNIO_HAL_COMPUTE     ((uint32_t)0x00AA0001L)

//
// MessageId: HIL_TASK_ID_PNIO_HAL_IRQ
//
// MessageText:
//
//  PROFINET IO HAL interrupt Task.
//
#define HIL_TASK_ID_PNIO_HAL_IRQ         ((uint32_t)0x00AB0001L)

/////////////////////////////////////////////////////////////////////////////////////
// RPC task
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_RPC_TASK
//
// MessageText:
//
//  RPC Task.
//
#define HIL_TASK_ID_RPC_TASK             ((uint32_t)0x002E0001L)

/////////////////////////////////////////////////////////////////////////////////////
// Router tasks
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ROUTER_OS_CONSOLE32
//
// MessageText:
//
//  TLR-Router OS_Console32.
//
#define HIL_TASK_ID_ROUTER_OS_CONSOLE32  ((uint32_t)0x002F0000L)

//
// MessageId: HIL_TASK_ID_ROUTER_ECAT_VOE
//
// MessageText:
//
//  TLR-Router EtherCAT VoE.
//
#define HIL_TASK_ID_ROUTER_ECAT_VOE      ((uint32_t)0x002F0001L)

//
// MessageId: HIL_TASK_ID_ROUTER_HIF_PACKET
//
// MessageText:
//
//  TLR-Router DPM.
//
#define HIL_TASK_ID_ROUTER_HIF_PACKET    ((uint32_t)0x002F0002L)

/////////////////////////////////////////////////////////////////////////////////////
// PowerLink tasks
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_EPL_NMT
//
// MessageText:
//
//  Ethernet PowerLink NMT Task.
//
#define HIL_TASK_ID_EPL_NMT              ((uint32_t)0x00170000L)

//
// MessageId: HIL_TASK_ID_EPL_PCK
//
// MessageText:
//
//  Ethernet PowerLink Packet Task.
//
#define HIL_TASK_ID_EPL_PCK              ((uint32_t)0x00170001L)

//
// MessageId: HIL_TASK_ID_EPL_DPM
//
// MessageText:
//
//  Ethernet PowerLink DPM Task.
//
#define HIL_TASK_ID_EPL_DPM              ((uint32_t)0x00170002L)

//
// MessageId: HIL_TASK_ID_PLSV3_AP
//
// MessageText:
//
//  Ethernet PowerLink AP Task.
//
#define HIL_TASK_ID_PLSV3_AP             ((uint32_t)0x00E10000L)

//
// MessageId: HIL_TASK_ID_PLSV3_IF
//
// MessageText:
//
//  Ethernet PowerLink CN IF Task.
//
#define HIL_TASK_ID_PLSV3_IF             ((uint32_t)0x00E30000L)

//
// MessageId: HIL_TASK_ID_PLSV3_NMT
//
// MessageText:
//
//  Ethernet PowerLink CN NMT Task.
//
#define HIL_TASK_ID_PLSV3_NMT            ((uint32_t)0x00E60000L)

//
// MessageId: HIL_TASK_ID_PLV3_COMMON
//
// MessageText:
//
//  Ethernet PowerLink Common Task.
//
#define HIL_TASK_ID_PLV3_COMMON          ((uint32_t)0x00E70000L)

//
// MessageId: HIL_TASK_ID_PLSV3_DRVETH
//
// MessageText:
//
//  Ethernet Powerlink DrvEth Adapter Task.
//
#define HIL_TASK_ID_PLSV3_DRVETH         ((uint32_t)0x00E80000L)

/////////////////////////////////////////////////////////////////////////////////////
// PowerLink PDO task
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_EPL_PDO
//
// MessageText:
//
//  Ethernet PowerLink PDO Task.
//
#define HIL_TASK_ID_EPL_PDO              ((uint32_t)0x00150000L)

/////////////////////////////////////////////////////////////////////////////////////
// PowerLink SDO task
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_EPL_SDO
//
// MessageText:
//
//  Ethernet PowerLink SDO Task.
//
#define HIL_TASK_ID_EPL_SDO              ((uint32_t)0x00160000L)

/////////////////////////////////////////////////////////////////////////////////////
// PowerLink MN task
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_EPL_MN
//
// MessageText:
//
//  Ethernet PowerLink MN Task.
//
#define HIL_TASK_ID_EPL_MN               ((uint32_t)0x003D0000L)

/////////////////////////////////////////////////////////////////////////////////////
// AS-Interface task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ASI_ECTRL
//
// MessageText:
//
//  AS-Interface ECTRL task (ASi stack).
//
#define HIL_TASK_ID_ASI_ECTRL            ((uint32_t)0x00320000L)

//
// MessageId: HIL_TASK_ID_ASI_AP
//
// MessageText:
//
//  AS-Interface Application task (example).
//
#define HIL_TASK_ID_ASI_AP               ((uint32_t)0x00000002L)

/////////////////////////////////////////////////////////////////////////////////////
// TCPUDP task identifiers (TCP/IP stack)
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_TCPUDP
//
// MessageText:
//
//  TCPUDP task (TCP/IP stack).
//
#define HIL_TASK_ID_TCPUDP               ((uint32_t)0x00080000L)

//
// MessageId: HIL_TASK_ID_TCPIP_AP
//
// MessageText:
//
//  TCP/IP stack Application task.
//
#define HIL_TASK_ID_TCPIP_AP             ((uint32_t)0x00000001L)

//
// MessageId: HIL_TASK_ID_TCPIP_SOCKIF
//
// MessageText:
//
//  TCP/IP Socket Interface.
//
#define HIL_TASK_ID_TCPIP_SOCKIF         ((uint32_t)0x00740002L)

/////////////////////////////////////////////////////////////////////////////////////
// SERCOS III task identifiers (Slave)
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SERCOSIII_API
//
// MessageText:
//
//  SERCOSIII API task.
//
#define HIL_TASK_ID_SERCOSIII_API        ((uint32_t)0x00340000L)

//
// MessageId: HIL_TASK_ID_SERCOSIII_DL
//
// MessageText:
//
//  SERCOSIII DL task.
//
#define HIL_TASK_ID_SERCOSIII_DL         ((uint32_t)0x00350000L)

//
// MessageId: HIL_TASK_ID_SERCOSIII_SVC
//
// MessageText:
//
//  SERCOSIII SVC task.
//
#define HIL_TASK_ID_SERCOSIII_SVC        ((uint32_t)0x00330000L)

//
// MessageId: HIL_TASK_ID_SERCOSIII_ETH
//
// MessageText:
//
//  SERCOSIII ETH task.
//
#define HIL_TASK_ID_SERCOSIII_ETH        ((uint32_t)0x00360000L)

//
// MessageId: HIL_TASK_ID_SERCOSIII_NRT
//
// MessageText:
//
//  SERCOSIII NRT task.
//
#define HIL_TASK_ID_SERCOSIII_NRT        ((uint32_t)0x00360001L)

//
// MessageId: HIL_TASK_ID_SERCOSIII_CYCLIC
//
// MessageText:
//
//  SERCOSIII cyclic task.
//
#define HIL_TASK_ID_SERCOSIII_CYCLIC     ((uint32_t)0x00370000L)




/////////////////////////////////////////////////////////////////////////////////////
// PROFIBUS task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_PROFIBUS_DL
//
// MessageText:
//
//  PROFIBUS Data Link Layer Task.
//
#define HIL_TASK_ID_PROFIBUS_DL          ((uint32_t)0x00060000L)

//
// MessageId: HIL_TASK_ID_PROFIBUS_FSPMS
//
// MessageText:
//
//  PROFIBUS Slave Fieldbus Service Protocol Machine Task.
//
#define HIL_TASK_ID_PROFIBUS_FSPMS       ((uint32_t)0x00090000L)

//
// MessageId: HIL_TASK_ID_PROFIBUS_APS
//
// MessageText:
//
//  PROFIBUS Slave Application Task.
//
#define HIL_TASK_ID_PROFIBUS_APS         ((uint32_t)0x001D0000L)

/////////////////////////////////////////////////////////////////////////////////////
// PROFIBUS Master task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_PROFIBUS_FSPMM
//
// MessageText:
//
//  PROFIBUS Master Fieldbus Service Protocol Machine Task.
//
#define HIL_TASK_ID_PROFIBUS_FSPMM       ((uint32_t)0x00380000L)

//
// MessageId: HIL_TASK_ID_PROFIBUS_APM
//
// MessageText:
//
//  PROFIBUS Master Application Task.
//
#define HIL_TASK_ID_PROFIBUS_APM         ((uint32_t)0x00390000L)

/////////////////////////////////////////////////////////////////////////////////////
// PROFIBUS Master task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SNMP_SERVER
//
// MessageText:
//
//  SNMP Server Task.
//
#define HIL_TASK_ID_SNMP_SERVER          ((uint32_t)0x003B0000L)

//
// MessageId: HIL_TASK_ID_MIB_DATABASE
//
// MessageText:
//
//  MIB Database for SNMP and LLDP.
//
#define HIL_TASK_ID_MIB_DATABASE         ((uint32_t)0x003C0000L)

//
// MessageId: HIL_TASK_ID_ICONL_TIMER
//
// MessageText:
//
//  Icon-L Timer Task for iCon-L@netX.
//
#define HIL_TASK_ID_ICONL_TIMER          ((uint32_t)0x002A0000L)

//
// MessageId: HIL_TASK_ID_ICONL_RUN
//
// MessageText:
//
//  Icon-L Run Task for iCon-L@netX.
//
#define HIL_TASK_ID_ICONL_RUN            ((uint32_t)0x00290000L)

//
// MessageId: HIL_TASK_ID_LLDP
//
// MessageText:
//
//  LLDP protocol task
//
#define HIL_TASK_ID_LLDP                 ((uint32_t)0x003E0000L)

/////////////////////////////////////////////////////////////////////////////////////
// CAN task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_CAN_DL
//
// MessageText:
//
//  CAN DL Task (Data Link Layer).
//
#define HIL_TASK_ID_CAN_DL               ((uint32_t)0x003F0000L)

/////////////////////////////////////////////////////////////////////////////////////
// DDL task identifiers (J060219 Bosch Rexroth DDL mit netX)
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_DDL_ENPDDL
//
// MessageText:
//
//  ENPDDL gateway task.
//
#define HIL_TASK_ID_DDL_ENPDDL           ((uint32_t)0x00400000L)

//
// MessageId: HIL_TASK_ID_DDL_DDL
//
// MessageText:
//
//  DDL protocol task.
//
#define HIL_TASK_ID_DDL_DDL              ((uint32_t)0x00410000L)

/////////////////////////////////////////////////////////////////////////////////////
// CANopen Master task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_CANOPEN_MASTER
//
// MessageText:
//
//  CANopen Master task (CANopen Master stack).
//
#define HIL_TASK_ID_CANOPEN_MASTER       ((uint32_t)0x00420000L)

/////////////////////////////////////////////////////////////////////////////////////
// CANopen Slave task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_CANOPEN_SLAVE
//
// MessageText:
//
//  CANopen Slave task (CANopen Slave stack).
//
#define HIL_TASK_ID_CANOPEN_SLAVE        ((uint32_t)0x00430000L)

/////////////////////////////////////////////////////////////////////////////////////
// UsbTLRRouter identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_USB_TLRROUTER
//
// MessageText:
//
//  Usb-TLR-Router Task (Usb-TLRRouter).
//
#define HIL_TASK_ID_USB_TLRROUTER        ((uint32_t)0x00440000L)

/////////////////////////////////////////////////////////////////////////////////////
// CAN DL AP sample identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_CANDL_APSAMPLE
//
// MessageText:
//
//  CAN DL application sample Task.
//
#define HIL_TASK_ID_CANDL_APSAMPLE       ((uint32_t)0x00460000L)

/////////////////////////////////////////////////////////////////////////////////////
// DeviceNet FAL (Fieldbus Application Layer) task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_DEVNET_FAL
//
// MessageText:
//
//  DeviceNet FAL Task (Fieldbus Application Layer).
//
#define HIL_TASK_ID_DEVNET_FAL           ((uint32_t)0x00470000L)

/////////////////////////////////////////////////////////////////////////////////////
// DeviceNet AP task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_DEVNET_AP
//
// MessageText:
//
//  DeviceNet AP Task (Application).
//
#define HIL_TASK_ID_DEVNET_AP            ((uint32_t)0x005B0000L)

/////////////////////////////////////////////////////////////////////////////////////
// ObjectDictionary V2 DPM Adapter
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_DPM_OD2
//
// MessageText:
//
//  Object Dictionary DPM-Adapter Task.
//
#define HIL_TASK_ID_DPM_OD2              ((uint32_t)0x00480000L)

/////////////////////////////////////////////////////////////////////////////////////
// CANopen Master application task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_CANOPEN_APM
//
// MessageText:
//
//  CANopen Master Application Task.
//
#define HIL_TASK_ID_CANOPEN_APM          ((uint32_t)0x00490000L)

/////////////////////////////////////////////////////////////////////////////////////
// CANopen Slave application task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_CANOPEN_APS
//
// MessageText:
//
//  CANopen Slave Application Task.
//
#define HIL_TASK_ID_CANOPEN_APS          ((uint32_t)0x004A0000L)

/////////////////////////////////////////////////////////////////////////////////////
// Sercos3 Slave application task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SERCOS_SL
//
// MessageText:
//
//  Sercos3 Slave Task.
//
#define HIL_TASK_ID_SERCOS_SL            ((uint32_t)0x004B0000L)

/////////////////////////////////////////////////////////////////////////////////////
// ECAT Slave DPM application task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ECAT_DPM
//
// MessageText:
//
//  EtherCAT Slave DPM Task.
//
#define HIL_TASK_ID_ECAT_DPM             ((uint32_t)0x004C0000L)

/////////////////////////////////////////////////////////////////////////////////////
// ECAT Slave InxAp application task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ECAT_INXAP
//
// MessageText:
//
//  EtherCAT Slave InxAp Task.
//
#define HIL_TASK_ID_ECAT_INXAP           ((uint32_t)0x004C0001L)

/////////////////////////////////////////////////////////////////////////////////////
// SercosIII Slave Communication task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SERCOSIII_SL_COM
//
// MessageText:
//
//  Sercos III Slave Communication Task.
//
#define HIL_TASK_ID_SERCOSIII_SL_COM     ((uint32_t)0x004E0000L)

/////////////////////////////////////////////////////////////////////////////////////
// SercosIII Slave Sercice Channel task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SERCOSIII_SL_SVC
//
// MessageText:
//
//  Sercos III Slave Service Channel Task.
//
#define HIL_TASK_ID_SERCOSIII_SL_SVC     ((uint32_t)0x004F0000L)

/////////////////////////////////////////////////////////////////////////////////////
// SercosIII Slave Real Time Data task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SERCOSIII_SL_RTD
//
// MessageText:
//
//  Sercos III Slave Real Time Data Task.
//
#define HIL_TASK_ID_SERCOSIII_SL_RTD     ((uint32_t)0x00500000L)

/////////////////////////////////////////////////////////////////////////////////////
// SercosIII Slave Application task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SERCOSIII_SL_AP
//
// MessageText:
//
//  Sercos III Slave Application Task.
//
#define HIL_TASK_ID_SERCOSIII_SL_AP      ((uint32_t)0x00510000L)

/////////////////////////////////////////////////////////////////////////////////////
// SercosIII Slave IDN task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SERCOSIII_SL_IDN
//
// MessageText:
//
//  Sercos III Slave IDN Task.
//
#define HIL_TASK_ID_SERCOSIII_SL_IDN     ((uint32_t)0x00850000L)

/////////////////////////////////////////////////////////////////////////////////////
// Ethernet/Ip Adapter Application task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_EIP_APS
//
// MessageText:
//
//  EtherNet/Ip Adapter Application-Task.
//
#define HIL_TASK_ID_EIP_APS              ((uint32_t)0x00590000L)

/////////////////////////////////////////////////////////////////////////////////////
// Ethernet/Ip Scanner Application task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_EIP_APM
//
// MessageText:
//
//  EtherNet/Ip Scanner Application-Task.
//
#define HIL_TASK_ID_EIP_APM              ((uint32_t)0x005A0000L)

/////////////////////////////////////////////////////////////////////////////////////
// Ethernet Interface Task
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ETH_INTF
//
// MessageText:
//
//  Ethernet Interface Task.
//
#define HIL_TASK_ID_ETH_INTF             ((uint32_t)0x005D0000L)

/////////////////////////////////////////////////////////////////////////////////////
// MID Startup Task
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_MID_STARTUP
//
// MessageText:
//
//  MID Startup Task.
//
#define HIL_TASK_ID_MID_STARTUP          ((uint32_t)0x005F0000L)

/////////////////////////////////////////////////////////////////////////////////////
// OMB task identifiers (Open Modbus TCP)
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_OMB_OMBTASK
//
// MessageText:
//
//  OMB task (Open Modbus TCP).
//
#define HIL_TASK_ID_OMB_OMBTASK          ((uint32_t)0x00600000L)

//
// MessageId: HIL_TASK_ID_OMB_OMBAPTASK
//
// MessageText:
//
//  OMB task (Open Modbus TCP) Application task.
//
#define HIL_TASK_ID_OMB_OMBAPTASK        ((uint32_t)0x00610001L)

/////////////////////////////////////////////////////////////////////////////////////
// DNS task identifiers (DeviceNet Slave)
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_DNS_FAL
//
// MessageText:
//
//  DeviceNet Slave FAL Task (Fieldbus Application Layer).
//
#define HIL_TASK_ID_DNS_FAL              ((uint32_t)0x00620000L)

//
// MessageId: HIL_TASK_ID_DNS_AP
//
// MessageText:
//
//  DeviceNet Slave AP Task (Dualport Application).
//
#define HIL_TASK_ID_DNS_AP               ((uint32_t)0x00630000L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT Master AP Task identifiers (EtherCAT Master AP Task)
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ETHERCAT_MASTER_AP
//
// MessageText:
//
//  EtherCAT Master AP Task.
//
#define HIL_TASK_ID_ETHERCAT_MASTER_AP   ((uint32_t)0x00640000L)

//
// MessageId: HIL_TASK_ID_ETHERCAT_MASTER
//
// MessageText:
//
//  EtherCAT Master Stack Task.
//
#define HIL_TASK_ID_ETHERCAT_MASTER      ((uint32_t)0x00650000L)

/////////////////////////////////////////////////////////////////////////////////////
// Ethernet Analyzer Transfer Task identifiers (Ethernet Analyzer Transfer Task)
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_AN_TRANS
//
// MessageText:
//
//  Ethernet Analyzer Transfer Task.
//
#define HIL_TASK_ID_AN_TRANS             ((uint32_t)0x00660000L)

/////////////////////////////////////////////////////////////////////////////////////
// Profibus MPI
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_PROFIBUS_MPI
//
// MessageText:
//
//  PROFIBUS MPI Task.
//
#define HIL_TASK_ID_PROFIBUS_MPI         ((uint32_t)0x00670000L)

//
// MessageId: HIL_TASK_ID_PROFIBUS_MPI_AP
//
// MessageText:
//
//  PROFIBUS MPI Application Task.
//
#define HIL_TASK_ID_PROFIBUS_MPI_AP      ((uint32_t)0x00680000L)

//
// MessageId: HIL_TASK_ID_PROFIBUS_MPI_RFC
//
// MessageText:
//
//  PROFIBUS MPI Task.
//
#define HIL_TASK_ID_PROFIBUS_MPI_RFC     ((uint32_t)0x00730000L)

/////////////////////////////////////////////////////////////////////////////////////
// Profibus FSPMM2
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_PROFIBUS_FSPMM2
//
// MessageText:
//
//  PROFIBUS FSPMM2 Task.
//
#define HIL_TASK_ID_PROFIBUS_FSPMM2      ((uint32_t)0x00690000L)

/////////////////////////////////////////////////////////////////////////////////////
// CC-Link Slave
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_CCLINK_SLAVE
//
// MessageText:
//
//  CC-Link Slave Task.
//
#define HIL_TASK_ID_CCLINK_SLAVE         ((uint32_t)0x006A0000L)

//
// MessageId: HIL_TASK_ID_CCLINK_APS
//
// MessageText:
//
//  CC-Link Slave Application Task.
//
#define HIL_TASK_ID_CCLINK_APS           ((uint32_t)0x006B0000L)

/////////////////////////////////////////////////////////////////////////////////////
// Lenze EtherCAT Slave Anbindung
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ECS_LENZE_MAIN
//
// MessageText:
//
//  Lenze EtherCAT slave interface for 9400, main task.
//
#define HIL_TASK_ID_ECS_LENZE_MAIN       ((uint32_t)0x006C0000L)

//
// MessageId: HIL_TASK_ID_ECS_LENZE_BRIDGE
//
// MessageText:
//
//  Lenze EtherCAT slave interface for 9400, bus bridge.
//
#define HIL_TASK_ID_ECS_LENZE_BRIDGE     ((uint32_t)0x006C0001L)

/////////////////////////////////////////////////////////////////////////////////////
// IO-Link Master Task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_IOLINK_MASTER
//
// MessageText:
//
//  IO-Link Master Task.
//
#define HIL_TASK_ID_IOLINK_MASTER        ((uint32_t)0x006D0000L)

//
// MessageId: HIL_TASK_ID_IOLINK_APPLICATION
//
// MessageText:
//
// IO-Link Application and Application Layer Task.
//
#define HIL_TASK_ID_IOLINK_APPLICATION   ((uint32_t)0x00A50000L)

/////////////////////////////////////////////////////////////////////////////////////
// MODBUS RTU
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_MODBUS_RTU
//
// MessageText:
//
//  MODBUS RTU Task.
//
#define HIL_TASK_ID_MODBUS_RTU           ((uint32_t)0x006E0000L)

/////////////////////////////////////////////////////////////////////////////////////
// MODBUS RTU AP
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_MODBUS_RTU_AP
//
// MessageText:
//
//  MODBUS RTU Application Task.
//
#define HIL_TASK_ID_MODBUS_RTU_AP        ((uint32_t)0x006F0000L)

/////////////////////////////////////////////////////////////////////////////////////
// SercosIII Master stack task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SIII_MA_CP
//
// MessageText:
//
//  Sercos III Communication Phase Task
//
#define HIL_TASK_ID_SIII_MA_CP           ((uint32_t)0x00700000L)

/////////////////////////////////////////////////////////////////////////////////////
// SercosIII Master stack task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SIII_MA_AP
//
// MessageText:
//
//  Sercos III DPM AP Task
//
#define HIL_TASK_ID_SIII_MA_AP           ((uint32_t)0x00720000L)

/////////////////////////////////////////////////////////////////////////////////////
// SercosIII Master stack task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SERCOSIIIMASTER_SVC
//
// MessageText:
//
//  Sercos III Service Channel Task
//
#define HIL_TASK_ID_SERCOSIIIMASTER_SVC  ((uint32_t)0x00710000L)

/////////////////////////////////////////////////////////////////////////////////////
// SercosIII Master stack task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SERCOSIIIMASTER_ACFG
//
// MessageText:
//
//  Sercos III Auto-Configure Task
//
#define HIL_TASK_ID_SERCOSIIIMASTER_ACFG ((uint32_t)0x00B70000L)

/////////////////////////////////////////////////////////////////////////////////////
// SercosIII Master stack task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SERCOSIIIMASTER_SIP_CLIENT
//
// MessageText:
//
//  Sercos III S/IP Client Task
//
#define HIL_TASK_ID_SERCOSIIIMASTER_SIP_CLIENT ((uint32_t)0x00BA0000L)

//
// MessageId: HIL_TASK_ID_SERCOSIIIMASTER_SIP_SERVER
//
// MessageText:
//
//  Sercos III S/IP Server Task
//
#define HIL_TASK_ID_SERCOSIIIMASTER_SIP_SERVER ((uint32_t)0x00BA0001L)

/////////////////////////////////////////////////////////////////////////////////////
// SSIO task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SSIO
//
// MessageText:
//
//  Serial Shift IO Task
//
#define HIL_TASK_ID_SSIO                 ((uint32_t)0x00750000L)

/////////////////////////////////////////////////////////////////////////////////////
// SSIO AP task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SSIO_AP
//
// MessageText:
//
//  Serial Shift IO Application Task
//
#define HIL_TASK_ID_SSIO_AP              ((uint32_t)0x00760000L)

/////////////////////////////////////////////////////////////////////////////////////
// MAP NIC task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_MEMORY_MAP
//
// MessageText:
//
//  netIC Mapping Task
//
#define HIL_TASK_ID_MEMORY_MAP           ((uint32_t)0x00770000L)

/////////////////////////////////////////////////////////////////////////////////////
// MPI Gateway task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_MPI_GATEWAY
//
// MessageText:
//
//  MPI Gateway Task
//
#define HIL_TASK_ID_MPI_GATEWAY          ((uint32_t)0x00780000L)

/////////////////////////////////////////////////////////////////////////////////////
// SercosIII Master stack NRT task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SERCOSIIIMASTER_NRT
//
// MessageText:
//
//  Sercos III NRT Channel Task
//
#define HIL_TASK_ID_SERCOSIIIMASTER_NRT  ((uint32_t)0x00790000L)

/////////////////////////////////////////////////////////////////////////////////////
// AS-Interface Master task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ASI_MASTER
//
// MessageText:
//
//  AS-Interface Master Task (AS-Interface Master stack).
//
#define HIL_TASK_ID_ASI_MASTER           ((uint32_t)0x007A0000L)

/////////////////////////////////////////////////////////////////////////////////////
// AS-Interface Master application task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ASI_APM
//
// MessageText:
//
//  AS-Interface Master Application Task.
//
#define HIL_TASK_ID_ASI_APM              ((uint32_t)0x007B0000L)

/////////////////////////////////////////////////////////////////////////////////////
// CompoNet Slave task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_COMPONET_SLAVE
//
// MessageText:
//
//  CompoNet Slave Task.
//
#define HIL_TASK_ID_COMPONET_SLAVE       ((uint32_t)0x007C0000L)

//
// MessageId: HIL_TASK_ID_COMPONET_SLAVE_AP
//
// MessageText:
//
//  CompoNet Slave Application Task.
//
#define HIL_TASK_ID_COMPONET_SLAVE_AP    ((uint32_t)0x007D0000L)

/////////////////////////////////////////////////////////////////////////////////////
// ASCII task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ASCII
//
// MessageText:
//
//  ASCII Protocol Task.
//
#define HIL_TASK_ID_ASCII                ((uint32_t)0x007E0000L)

//
// MessageId: HIL_TASK_ID_ASCII_AP
//
// MessageText:
//
//  ASCII Application Task.
//
#define HIL_TASK_ID_ASCII_AP             ((uint32_t)0x007F0000L)

/////////////////////////////////////////////////////////////////////////////////////
// netscript task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_NETSCRIPT
//
// MessageText:
//
//  netScript Task.
//
#define HIL_TASK_ID_NETSCRIPT            ((uint32_t)0x00800000L)

/////////////////////////////////////////////////////////////////////////////////////
// Marshaller task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_MARSHALLER
//
// MessageText:
//
//  Marshaller: Main Task.
//
#define HIL_TASK_ID_MARSHALLER           ((uint32_t)0x00820000L)

//
// MessageId: HIL_TASK_ID_PACKET_ROUTER
//
// MessageText:
//
//  Marshaller: Packet Router Task.
//
#define HIL_TASK_ID_PACKET_ROUTER        ((uint32_t)0x00830000L)

//
// MessageId: HIL_TASK_ID_TCP_CONNECTOR
//
// MessageText:
//
//  Marshaller: TCP Connection Task.
//
#define HIL_TASK_ID_TCP_CONNECTOR        ((uint32_t)0x00860000L)

/////////////////////////////////////////////////////////////////////////////////////
// netTAP 100 Gateway task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_NT100_GATEWAY
//
// MessageText:
//
//  netTAP Gateway Task.
//
#define HIL_TASK_ID_NT100_GATEWAY        ((uint32_t)0x00840000L)

/////////////////////////////////////////////////////////////////////////////////////
// Item Server task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ITEM_SERVER
//
// MessageText:
//
//  Item Server Task.
//
#define HIL_TASK_ID_ITEM_SERVER          ((uint32_t)0x00870000L)

/////////////////////////////////////////////////////////////////////////////////////
// ISaGRAF task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ISAGRAF_LOG
//
// MessageText:
//
//  telnet task for ISaGRAF log.
//
#define HIL_TASK_ID_ISAGRAF_LOG          ((uint32_t)0x008C0000L)

//
// MessageId: HIL_TASK_ID_ISAGRAF_VM
//
// MessageText:
//
//  Virtual Machine ISaGRAF task.
//
#define HIL_TASK_ID_ISAGRAF_VM           ((uint32_t)0x008B0000L)

//
// MessageId: HIL_TASK_ID_ISAGRAF
//
// MessageText:
//
//  ISaGRAF command task.
//
#define HIL_TASK_ID_ISAGRAF              ((uint32_t)0x008A0000L)

//
// MessageId: HIL_TASK_ID_ISAGRAF_ETCP
//
// MessageText:
//
//  Ethernet ISaGRAF interface.
//
#define HIL_TASK_ID_ISAGRAF_ETCP         ((uint32_t)0x00890000L)

//
// MessageId: HIL_TASK_ID_ISAGRAF_ISARSI
//
// MessageText:
//
//  RS232 ISaGRAF interface.
//
#define HIL_TASK_ID_ISAGRAF_ISARSI       ((uint32_t)0x00880000L)

//
// MessageId: HIL_TASK_ID_ISAGRAF_MAINTENANCE
//
// MessageText:
//
//  ISaGRAF maintenance task.
//
#define HIL_TASK_ID_ISAGRAF_MAINTENANCE  ((uint32_t)0x008A0001L)

//
// MessageId: HIL_TASK_ID_ISAGRAF_NTP
//
// MessageText:
//
//  ISaGRAF NTP task.
//
#define HIL_TASK_ID_ISAGRAF_NTP          ((uint32_t)0x008A0002L)

//
// MessageId: HIL_TASK_ID_ISAGRAF_AP
//
// MessageText:
//
//  ISaGRAF AP task.
//
#define HIL_TASK_ID_ISAGRAF_AP           ((uint32_t)0x008A0003L)

//
// MessageId: HIL_TASK_ID_ISAGRAF_FTP
//
// MessageText:
//
//  ISaGRAF FTP task.
//
#define HIL_TASK_ID_ISAGRAF_FTP          ((uint32_t)0x008A0004L)

//
// MessageId: HIL_TASK_ID_ISAGRAF_DS
//
// MessageText:
//
//  ISaGRAF DS task.
//
#define HIL_TASK_ID_ISAGRAF_DS           ((uint32_t)0x008A0005L)

/////////////////////////////////////////////////////////////////////////////////////
// DF1 task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_DF1
//
// MessageText:
//
//  DF1 Protocol Task.
//
#define HIL_TASK_ID_DF1                  ((uint32_t)0x008D0000L)

//
// MessageId: HIL_TASK_ID_DF1_AP
//
// MessageText:
//
//  DF1 Application Task.
//
#define HIL_TASK_ID_DF1_AP               ((uint32_t)0x008E0000L)

/////////////////////////////////////////////////////////////////////////////////////
// 3964R task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_3964R
//
// MessageText:
//
//  3964R Protocol Task.
//
#define HIL_TASK_ID_3964R                ((uint32_t)0x008F0000L)

//
// MessageId: HIL_TASK_ID_3964R_AP
//
// MessageText:
//
//  3964R Application Task.
//
#define HIL_TASK_ID_3964R_AP             ((uint32_t)0x00900000L)

/////////////////////////////////////////////////////////////////////////////////////
// IO Signals task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_IO_SIGNAL
//
// MessageText:
//
//  IO Signal Task.
//
#define HIL_TASK_ID_IO_SIGNAL            ((uint32_t)0x00910000L)

/////////////////////////////////////////////////////////////////////////////////////
// ServX task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SERVX
//
// MessageText:
//
//  servX HTTP Server.
//
#define HIL_TASK_ID_SERVX                ((uint32_t)0x00920000L)

/////////////////////////////////////////////////////////////////////////////////////
// TCPIP Application task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_TCPIP_TCP_AP
//
// MessageText:
//
//  TCPUDP application task (TCP/IP stack).
//
#define HIL_TASK_ID_TCPIP_TCP_AP         ((uint32_t)0x00940000L)

/////////////////////////////////////////////////////////////////////////////////////
// DLR task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_EIP_DLR
//
// MessageText:
//
//  EthernetIP DLR task.
//
#define HIL_TASK_ID_EIP_DLR              ((uint32_t)0x00950000L)

/////////////////////////////////////////////////////////////////////////////////////
// FODMI task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_FODMI
//
// MessageText:
//
//  Fibre optic diagnostic monitoring interface task.
//
#define HIL_TASK_ID_FODMI                ((uint32_t)0x00960000L)

/////////////////////////////////////////////////////////////////////////////////////
// PROFIDRIVE task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_PROFIDRIVE
//
// MessageText:
//
//  PROFIDRIVE task.
//
#define HIL_TASK_ID_PROFIDRIVE           ((uint32_t)0x00970000L)

/////////////////////////////////////////////////////////////////////////////////////
// PROFIDRIVE - PA task identifier     // not used //
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_PROFIDRIVE_PA
//
// MessageText:
//
//  PROFIDRIVE parameter Access interface task.
//
#define HIL_TASK_ID_PROFIDRIVE_PA        ((uint32_t)0x00980000L)

/////////////////////////////////////////////////////////////////////////////////////
// PROFIDRIVE - AP task identifier     // not used //
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_PROFIDRIVE_AP
//
// MessageText:
//
//  PROFIDRIVE user application task.
//
#define HIL_TASK_ID_PROFIDRIVE_AP        ((uint32_t)0x009A0000L)

/////////////////////////////////////////////////////////////////////////////////////
// PROFIDRIVE - OD task identifier      // not used //
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_PROFIDRIVE_OD
//
// MessageText:
//
//  PROFIDRIVE Object Dictionary task.
//
#define HIL_TASK_ID_PROFIDRIVE_OD        ((uint32_t)0x00990000L)

/////////////////////////////////////////////////////////////////////////////////////
// CANopen Object Dictionary
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ODV3
//
// MessageText:
//
//  CANopen Object Dictionary task.
//
#define HIL_TASK_ID_ODV3                 ((uint32_t)0x009B0000L)

/////////////////////////////////////////////////////////////////////////////////////
// VARAN Client Application
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_VARAN_CLIENT_AP
//
// MessageText:
//
//  VARAN Client application task.
//
#define HIL_TASK_ID_VARAN_CLIENT_AP      ((uint32_t)0x009D0000L)

/////////////////////////////////////////////////////////////////////////////////////
// VARAN Client
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_VARAN_CLIENT
//
// MessageText:
//
//  VARAN Client task.
//
#define HIL_TASK_ID_VARAN_CLIENT         ((uint32_t)0x009C0000L)

/////////////////////////////////////////////////////////////////////////////////////
// Modbus RTU Peripheral Task
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_MODBUS_RTU_PERIPH
//
// MessageText:
//
//  Modbus RTU Peripheral Task.
//
#define HIL_TASK_ID_MODBUS_RTU_PERIPH    ((uint32_t)0x009E0000L)

/////////////////////////////////////////////////////////////////////////////////////
// Profinet RTA Task
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_PROFINET_RTA
//
// MessageText:
//
//  Profinet RTA (RealTime Acyclic) Task.
//
#define HIL_TASK_ID_PROFINET_RTA         ((uint32_t)0x009F0000L)

/////////////////////////////////////////////////////////////////////////////////////
// SercosIII Internet Protocol Service(SIP) task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SIII_SIP
//
// MessageText:
//
//  SercosIII Internet Protocol Service Task.
//
#define HIL_TASK_ID_SIII_SIP             ((uint32_t)0x00A00000L)

/////////////////////////////////////////////////////////////////////////////////////
// 3S CodeSys PLC Handler task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_3S_PLC_HANDLER
//
// MessageText:
//
//  3S CodeSys PLC Handler Task.
//
#define HIL_TASK_ID_3S_PLC_HANDLER       ((uint32_t)0x00A10000L)

/////////////////////////////////////////////////////////////////////////////////////
// 3S CodeSys PLC Handler AP task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_3S_PLC_HANDLER_AP
//
// MessageText:
//
//  3S CodeSys PLC Handler AP Task.
//
#define HIL_TASK_ID_3S_PLC_HANDLER_AP    ((uint32_t)0x00A20000L)

/////////////////////////////////////////////////////////////////////////////////////
// netPLC I/O Handler task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_NETPLC_IO_HANDLER
//
// MessageText:
//
//  netPLC I/O Handler.
//
#define HIL_TASK_ID_NETPLC_IO_HANDLER    ((uint32_t)0x00A30000L)

/////////////////////////////////////////////////////////////////////////////////////
// PowerLink MN task identifiers
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_POWERLINK_MN_TASK
//
// MessageText:
//
//  PowerLink MN Task
//
#define HIL_TASK_ID_POWERLINK_MN_TASK    ((uint32_t)0x00A40000L)

//
// MessageId: HIL_TASK_ID_POWERLINK_MN_AP_TASK
//
// MessageText:
//
//  PowerLink MN AP Task
//
#define HIL_TASK_ID_POWERLINK_MN_AP_TASK ((uint32_t)0x00A40001L)

//
// MessageId: HIL_TASK_ID_POWERLINK_MN_NEW_DATA_TASK
//
// MessageText:
//
//  PowerLink MN NewData Task
//
#define HIL_TASK_ID_POWERLINK_MN_NEW_DATA_TASK ((uint32_t)0x00A40002L)

//
// MessageId: HIL_TASK_ID_POWERLINK_MN_SDO_UDP_SOCK_TASK
//
// MessageText:
//
//  PowerLink MN SDO UDP Socket Task
//
#define HIL_TASK_ID_POWERLINK_MN_SDO_UDP_SOCK_TASK ((uint32_t)0x00A40003L)

//
// MessageId: HIL_TASK_ID_POWERLINK_MN_VETH_TASK
//
// MessageText:
//
//  PowerLink MN VirtualEthernet Task
//
#define HIL_TASK_ID_POWERLINK_MN_VETH_TASK ((uint32_t)0x00A40004L)

//
// MessageId: HIL_TASK_ID_POWERLINK_MN_JOB_TOKEN_TASK
//
// MessageText:
//
//  PowerLink MN JobToken Task
//
#define HIL_TASK_ID_POWERLINK_MN_JOB_TOKEN_TASK ((uint32_t)0x00A40005L)

/////////////////////////////////////////////////////////////////////////////////////
// Recording task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_RECORDING
//
// MessageText:
//
//  Recording and logging Task.
//
#define HIL_TASK_ID_RECORDING            ((uint32_t)0x00A60000L)

/////////////////////////////////////////////////////////////////////////////////////
// Insight Debug task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_INSIGHT
//
// MessageText:
//
//  Insight task.
//
#define HIL_TASK_ID_INSIGHT              ((uint32_t)0x00AC0000L)

/////////////////////////////////////////////////////////////////////////////////////
// SmartWire Master Task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_SMARTWIRE_MASTER
//
// MessageText:
//
//  SmartWire master task.
//
#define HIL_TASK_ID_SMARTWIRE_MASTER     ((uint32_t)0x00AD0000L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherCAT Slave V4 Task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ECSV4_ESM
//
// MessageText:
//
//  EtherCAT Slave V4 ESM Task.
//
#define HIL_TASK_ID_ECSV4_ESM            ((uint32_t)0x00AF0000L)

//
// MessageId: HIL_TASK_ID_ECSV4_MBX
//
// MessageText:
//
//  EtherCAT Slave V4 MBX Task.
//
#define HIL_TASK_ID_ECSV4_MBX            ((uint32_t)0x00B00000L)

//
// MessageId: HIL_TASK_ID_ECSV4_COE
//
// MessageText:
//
//  EtherCAT Slave V4 COE Task.
//
#define HIL_TASK_ID_ECSV4_COE            ((uint32_t)0x00B10000L)

//
// MessageId: HIL_TASK_ID_ECSV4_SDO
//
// MessageText:
//
//  EtherCAT Slave V4 SDO Task.
//
#define HIL_TASK_ID_ECSV4_SDO            ((uint32_t)0x00B10001L)

//
// MessageId: HIL_TASK_ID_ECSV4_EOE
//
// MessageText:
//
//  EtherCAT Slave V4 EOE Task.
//
#define HIL_TASK_ID_ECSV4_EOE            ((uint32_t)0x00B20000L)

//
// MessageId: HIL_TASK_ID_ECSV4_FOE
//
// MessageText:
//
//  EtherCAT Slave V4 FOE Task.
//
#define HIL_TASK_ID_ECSV4_FOE            ((uint32_t)0x00B30000L)

//
// MessageId: HIL_TASK_ID_ECSV4_FOE_FH
//
// MessageText:
//
//  EtherCAT Slave V4 FOE FH Task.
//
#define HIL_TASK_ID_ECSV4_FOE_FH         ((uint32_t)0x00C40000L)

//
// MessageId: HIL_TASK_ID_ECSV4_SOE_SSC
//
// MessageText:
//
//  EtherCAT Slave V4 SOE_SSC Task.
//
#define HIL_TASK_ID_ECSV4_SOE_SSC        ((uint32_t)0x00B40000L)

//
// MessageId: HIL_TASK_ID_ECSV4_SOE_IDN
//
// MessageText:
//
//  EtherCAT Slave V4 SOE_IDN Task.
//
#define HIL_TASK_ID_ECSV4_SOE_IDN        ((uint32_t)0x00B40001L)

//
// MessageId: HIL_TASK_ID_ECSV4_DPM
//
// MessageText:
//
//  EtherCAT Slave V4 DPM Task.
//
#define HIL_TASK_ID_ECSV4_DPM            ((uint32_t)0x00AE0000L)

//
// MessageId: HIL_TASK_ID_NET_PROXY
//
// MessageText:
//
//  netPROXY.
//
#define HIL_TASK_ID_NET_PROXY            ((uint32_t)0x00B50000L)

//
// MessageId: HIL_TASK_ID_ECSV4_AOE
//
// MessageText:
//
//  EtherCAT Slave V4 AoE Task.
//
#define HIL_TASK_ID_ECSV4_AOE            ((uint32_t)0x00BB0000L)

/////////////////////////////////////////////////////////////////////////////////////
// netSMART Gateway Task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_NET_SMART_GATEWAY
//
// MessageText:
//
//  netSMART Gateway.
//
#define HIL_TASK_ID_NET_SMART_GATEWAY    ((uint32_t)0x00B60000L)

/////////////////////////////////////////////////////////////////////////////////////
// TFTP Stack Task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_TFTP
//
// MessageText:
//
//  TFTP Stack Task.
//
#define HIL_TASK_ID_TFTP                 ((uint32_t)0x00B80000L)

/////////////////////////////////////////////////////////////////////////////////////
// TFTP App Task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_TFTP_AP
//
// MessageText:
//
//  TFTP Application Task.
//
#define HIL_TASK_ID_TFTP_AP              ((uint32_t)0x00B90000L)

/////////////////////////////////////////////////////////////////////////////////////
// PTP Task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_PTP
//
// MessageText:
//
//  PTP Task.
//
#define HIL_TASK_ID_PTP                  ((uint32_t)0x00BD0000L)

/////////////////////////////////////////////////////////////////////////////////////
// User Area
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_USER_AREA
//
// MessageText:
//
//  User Area.
//
#define HIL_TASK_ID_USER_AREA            ((uint32_t)0x0FF00000L)

/////////////////////////////////////////////////////////////////////////////////////
// User Area
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_NETPROXY_S3S
//
// MessageText:
//
//  S3S netProxy adaptation task
//
#define HIL_TASK_ID_NETPROXY_S3S         ((uint32_t)0x00BC0000L)

/////////////////////////////////////////////////////////////////////////////////////
// EtherNet/IP DLR IRQ Task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_EIP_DLR_IRQ
//
// MessageText:
//
//  PTP Task.
//
#define HIL_TASK_ID_EIP_DLR_IRQ          ((uint32_t)0x00BE0000L)

/////////////////////////////////////////////////////////////////////////////////////
// FTP Server Stack Task
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_FTP_SERVER
//
// MessageText:
//
//  FTP Stack Task
//
#define HIL_TASK_ID_FTP_SERVER           ((uint32_t)0x00BF0000L)

/////////////////////////////////////////////////////////////////////////////////////
// FTP Server Application Task
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_FTP_SERVER_AP
//
// MessageText:
//
//  FTP Application Task.
//
#define HIL_TASK_ID_FTP_SERVER_AP        ((uint32_t)0x00C00000L)

/////////////////////////////////////////////////////////////////////////////////////
// netPROXY HIF Adapter Task
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_NPXHIFADAPTER
//
// MessageText:
//
//  netPROXY HIF Adapter Task.
//
#define HIL_TASK_ID_NPXHIFADAPTER        ((uint32_t)0x00C20000L)

/////////////////////////////////////////////////////////////////////////////////////
// netPROXY package EtherNetIP Slave
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_NPXPACKAGE_EIS
//
// MessageText:
//
//  netPROXY package EtherNetIP Slave.
//
#define HIL_TASK_ID_NPXPACKAGE_EIS       ((uint32_t)0x00C30000L)

/////////////////////////////////////////////////////////////////////////////////////
// netHost task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_NETHOST
//
// MessageText:
//
//  netHost Task.
//
#define HIL_TASK_ID_NETHOST              ((uint32_t)0x00C50000L)

/////////////////////////////////////////////////////////////////////////////////////
// CIP Handler task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_CIP_HANDLER
//
// MessageText:
//
//  CIP Handler Task.
//
#define HIL_TASK_ID_CIP_HANDLER          ((uint32_t)0x00C60000L)

/////////////////////////////////////////////////////////////////////////////////////
// CPX Driver task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_CPX_DRIVER
//
// MessageText:
//
//  CPX Driver Task.
//
#define HIL_TASK_ID_CPX_DRIVER           ((uint32_t)0x00C70000L)

/////////////////////////////////////////////////////////////////////////////////////
// CPX Exchange task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_CPX_EXCHANGE
//
// MessageText:
//
//  CPX Exchange Task.
//
#define HIL_TASK_ID_CPX_EXCHANGE         ((uint32_t)0x00C80000L)

/////////////////////////////////////////////////////////////////////////////////////
// OSAL
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_CPX_OSAL
//
// MessageText:
//
//  CPX Exchange Task.
//
#define HIL_TASK_ID_CPX_OSAL             ((uint32_t)0x00CA0000L)

/////////////////////////////////////////////////////////////////////////////////////
// PROFINET IO CONTROLLER V3
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_PNM_AP
//
// MessageText:
//
//  Profinet IO Controller V3 AP Task.
//
#define HIL_TASK_ID_PNM_AP               ((uint32_t)0x00CB0000L)

/////////////////////////////////////////////////////////////////////////////////////
// ECMv4
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_ECMV4_AP
//
// MessageText:
//
//  EtherCAT Master AP Task.
//
#define HIL_TASK_ID_ECMV4_AP             ((uint32_t)0x00D70000L)

//
// MessageId: HIL_TASK_ID_ECMV4_IF
//
// MessageText:
//
//  EtherCAT Master Interface Task.
//
#define HIL_TASK_ID_ECMV4_IF             ((uint32_t)0x00D60000L)

//
// MessageId: HIL_TASK_ID_ECMV4_LLD_SCHED
//
// MessageText:
//
//  LLD Scheduler.
//
#define HIL_TASK_ID_ECMV4_LLD_SCHED      ((uint32_t)0x00CC0000L)

//
// MessageId: HIL_TASK_ID_ECMV4_EMC
//
// MessageText:
//
//  EtherCAT Master Control Task.
//
#define HIL_TASK_ID_ECMV4_EMC            ((uint32_t)0x00CD0000L)

//
// MessageId: HIL_TASK_ID_ECMV4_EMC_LLD_IF
//
// MessageText:
//
//  EtherCAT Master Control Task LLD IF.
//
#define HIL_TASK_ID_ECMV4_EMC_LLD_IF     ((uint32_t)0x00CD0001L)

//
// MessageId: HIL_TASK_ID_ECMV4_COE_SDOCLIENT
//
// MessageText:
//
//  SDO Client Task.
//
#define HIL_TASK_ID_ECMV4_COE_SDOCLIENT  ((uint32_t)0x00CF0000L)

//
// MessageId: HIL_TASK_ID_ECMV4_COE_SDOINFOCLIENT
//
// MessageText:
//
//  SDOINFO Client Task.
//
#define HIL_TASK_ID_ECMV4_COE_SDOINFOCLIENT ((uint32_t)0x00CF0001L)

//
// MessageId: HIL_TASK_ID_ECMV4_EOE
//
// MessageText:
//
//  EoE Task.
//
#define HIL_TASK_ID_ECMV4_EOE            ((uint32_t)0x00D00000L)

//
// MessageId: HIL_TASK_ID_ECMV4_EOE_IF
//
// MessageText:
//
//  EoE Interface Task.
//
#define HIL_TASK_ID_ECMV4_EOE_IF         ((uint32_t)0x00D00001L)

//
// MessageId: HIL_TASK_ID_ECMV4_SOE_CLIENT
//
// MessageText:
//
//  SoE Client Task.
//
#define HIL_TASK_ID_ECMV4_SOE_CLIENT     ((uint32_t)0x00D20000L)

//
// MessageId: HIL_TASK_ID_ECMV4_FOE_CLIENT
//
// MessageText:
//
//  FoE Client Task.
//
#define HIL_TASK_ID_ECMV4_FOE_CLIENT     ((uint32_t)0x00D10000L)

//
// MessageId: HIL_TASK_ID_ECMV4_AOE_ROUTER
//
// MessageText:
//
//  AoE Router Task.
//
#define HIL_TASK_ID_ECMV4_AOE_ROUTER     ((uint32_t)0x00CE0000L)

/////////////////////////////////////////////////////////////////////////////////////
// netPROXY package ODV3
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_NPXPACKAGE_ODV3
//
// MessageText:
//
//  netPROXY package ODV3.
//
#define HIL_TASK_ID_NPXPACKAGE_ODV3      ((uint32_t)0x00D80000L)

/////////////////////////////////////////////////////////////////////////////////////
// netPROXY package EtherCAT Slave
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_NPXPACKAGE_ECS
//
// MessageText:
//
//  netPROXY package EtherCAT Slave.
//
#define HIL_TASK_ID_NPXPACKAGE_ECS       ((uint32_t)0x00D90000L)

/////////////////////////////////////////////////////////////////////////////////////
// netPROXY package IO-Link Master
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_NPXPACKAGE_IOLM
//
// MessageText:
//
//  netPROXY package IO-Link Master.
//
#define HIL_TASK_ID_NPXPACKAGE_IOLM      ((uint32_t)0x00DA0000L)

/////////////////////////////////////////////////////////////////////////////////////
// netPROXY Management task
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_NPXMGMT
//
// MessageText:
//
//  netPROXY management task.
//
#define HIL_TASK_ID_NPXMGMT              ((uint32_t)0x00E00000L)

/////////////////////////////////////////////////////////////////////////////////////
// Command Table task identifier
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_CMD_TABLE
//
// MessageText:
//
//  Command Table Task.
//
#define HIL_TASK_ID_CMD_TABLE            ((uint32_t)0x00E20000L)

/////////////////////////////////////////////////////////////////////////////////////
// netTap DPM Bridge Task
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_NT_DPM_BRIDGE
//
// MessageText:
//
//  netTap DPM Bridge Task.
//
#define HIL_TASK_ID_NT_DPM_BRIDGE        ((uint32_t)0x00E40000L)

/////////////////////////////////////////////////////////////////////////////////////
// netPROXY LED Handler /////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_NPXLEDHNDLR
//
// MessageText:
//
//  netPROXY LED Handler Task.
//
#define HIL_TASK_ID_NPXLEDHNDLR          ((uint32_t)0x00E50000L)

/////////////////////////////////////////////////////////////////////////////////////
// LWIP Task
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_LWIP
//
// MessageText:
//
//  LWIP Task.
//
#define HIL_TASK_ID_LWIP                 ((uint32_t)0x00E90000L)

/////////////////////////////////////////////////////////////////////////////////////
// OSAL Worker Thread
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_WORKER_THREAD
//
// MessageText:
//
//  OSAL Worker Thread.
//
#define HIL_TASK_ID_WORKER_THREAD        ((uint32_t)0x00EA0000L)

/////////////////////////////////////////////////////////////////////////////////////
// netPROXY package PROFINET IO-Device V4
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_NPXPACKAGE_PNS
//
// MessageText:
//
//  netPROXY package PROFINET IO-Device.
//
#define HIL_TASK_ID_NPXPACKAGE_PNS       ((uint32_t)0x00EB0000L)

/////////////////////////////////////////////////////////////////////////////////////
// Base Firmware Application Task
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_BASEFW_AP
//
// MessageText:
//
//  Base Firmware Application Task.
//
#define HIL_TASK_ID_BASEFW_AP            ((uint32_t)0x00EC0000L)

/////////////////////////////////////////////////////////////////////////////////////
// Config Manager Task
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_CONFIG_MANAGER
//
// MessageText:
//
//  Config Manager Task.
//
#define HIL_TASK_ID_CONFIG_MANAGER       ((uint32_t)0x00ED0000L)

/////////////////////////////////////////////////////////////////////////////////////
// netPROXY package Remanent
/////////////////////////////////////////////////////////////////////////////////////
//
// MessageId: HIL_TASK_ID_NPXPACKAGE_REMANENT
//
// MessageText:
//
// netPROXY package Remanent.
//
#define HIL_TASK_ID_NPXPACKAGE_REMANENT  ((uint32_t)0x00F20000L)




#endif  //__HIL_TASK_IDENTIFIER_H

