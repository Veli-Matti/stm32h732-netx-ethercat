/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id: npx_eventlog_api.h 3816 2018-02-28 16:09:11Z dirk $

  Description:
    netPROXY event log

  NOTE:
    Do not include this file separate. This file will included in the correct order
    by using netPROXY.h

**************************************************************************************/
#ifndef __NPX_EVENTLOG_API_H
#define __NPX_EVENTLOG_API_H

//#include "NpxObj_netPROXY_EventLog.h"

#ifdef __cplusplus
extern "C" {
#endif  /* _cplusplus */


/*! Event data data structure */
typedef struct NPX_EVENTLOG_DATA_Ttag
{
  uint8_t     bSeverity;        /*!< Severity level: see NPX_OBJ_NETPROXY_EVENT_LOG_SEVERITY_E  */
  uint8_t     bMarker;          /*!< Marker                                                     */
  uint16_t    usFacility;       /*!< Facility: see NPX_OBJ_NETPROXY_EVENT_LOG_FACILITY_E        */
  uint32_t    ulErrorCode;      /*!< Generic Error code                                         */
  uint32_t    ulData;           /*!< Additional data                                            */
} NPX_EVENTLOG_DATA_T;

/*! Event log meta data, this data is added within the event log automatically */
typedef struct NPX_EVENTLOG_METADATA_Ttag
{
  uint32_t    ulEntryID;        /*!< Unique entry ID                                                */
  uint32_t    ulTimeStamp;      /*!< Time stamp in ms since system start, when the enrty was stored */

} NPX_EVENTLOG_METADATA_T;

/*! Npx_EventLog_AddEntry.
 *
 * Store a entry in the event log.
 *
 * \param ptData [in] Entry data which should be added Event log object is installed.
 */
void Npx_AddEventLogEntry(
  const NPX_EVENTLOG_DATA_T *ptData);


/*! Npx_EventLog_GetEntry.
 *
 * Get entry from the event log.
 *
 * \param ulEntryPos  [in] Entry position that should be read
 * \param ptData      [out] Pointer to a event log data structure where the data should be stored
 * \param ptMeta      [out] Pointer to a event log meta data structure where the data should be stored
 *
 * \return ::SUCCESS_NET_PROXY_OK on success, otherwise an ::NPX_RESULT error code
 */
NPX_RESULT Npx_GetEventLogEntry(
  uint32_t ulEntryPos,
  NPX_EVENTLOG_DATA_T *ptData,
  NPX_EVENTLOG_METADATA_T *ptMeta);


/*! Npx_EventLog_GetNumberOfEntries
 *
 * \return Maximum number of entries
 */
uint32_t Npx_GetNumberOfEventLogEntries();


#ifdef __cplusplus
}
#endif  /* _cplusplus */

#endif /* __NPX_EVENTLOG_API_H */
