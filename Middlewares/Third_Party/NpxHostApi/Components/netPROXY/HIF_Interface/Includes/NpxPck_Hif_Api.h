/**************************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************************
  $Id: NpxPck_Hif_Api.h 3816 2018-02-28 16:09:11Z dirk $

  Description:
    Version header

**************************************************************************************************/
#ifndef __NPXPCK_HIF_API_H
#define __NPXPCK_HIF_API_H

#include "npx_types.h"

typedef struct NPXPCK_HIF_RSC_Ttag* NPXPCK_HIF_H;

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t
NpxPck_Hif_OpenHandle(NPX_IF_H hNpxIf,
                      uint32_t ulNpxGroupID,
                      NPXPCK_HIF_H* phNpxHif);

void
NpxPck_Hif_CloseHandle(NPXPCK_HIF_H hNpxHif);

uint32_t
NpxPck_Hif_GetBufSize(NPXPCK_HIF_H hNpxHif,
                      uint32_t* pulHifToNetBufSize,
                      uint32_t* pulNetToHifBufSize);

uint32_t
NpxPck_Hif_GetImageSize(NPXPCK_HIF_H hNpxHif,
                        uint32_t* pulHifToNetImageSize,
                        uint32_t* pulNetToHifImageSize);

uint32_t
NpxPck_Hif_GetInputMappingInfo(NPXPCK_HIF_H hNpxHif,
                               NPX_OBJECT_REFERENCE_T* ptObjectReference,
                               uint32_t* pulDataOffset,
                               uint32_t* pulDataSize,
                               uint32_t* pulStatusOffset);

uint32_t
NpxPck_Hif_GetOutputMappingInfo(NPXPCK_HIF_H hNpxHif,
                                NPX_OBJECT_REFERENCE_T* ptObjectReference,
                                uint32_t* pulDataOffset,
                                uint32_t* pulDataSize,
                                uint32_t* pulStatusOffset);

uint32_t
NpxPck_Hif_GetHifToNetBuf(NPXPCK_HIF_H hNpxHif,
                          const uint8_t** ppabHifToNetBuf);

uint32_t
NpxPck_Hif_ReleaseHifToNetBuf(NPXPCK_HIF_H hNpxHif,
                              const uint8_t* pabHifToNetBuf);

uint32_t
NpxPck_Hif_GetNetToHifBuf(NPXPCK_HIF_H hNpxHif,
                          uint8_t** ppabNetToHifBuf);

uint32_t
NpxPck_Hif_UpdateNetToHifBuf(NPXPCK_HIF_H hNpxHif,
                             uint8_t* pabNetToHifBuf);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef __NPXPCK_HIF_API_H */
/*************************************************************************************************/
/*-----------------------------------------------------------------------------------------------*/
/*-------------------------------- EOF ----------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------*/
/*************************************************************************************************/
