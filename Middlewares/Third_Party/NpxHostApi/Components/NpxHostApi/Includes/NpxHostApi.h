/**********************************************************************************************************************
                 Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***********************************************************************************************************************
  $Id: NpxHostApi.h 3816 2018-02-28 16:09:11Z dirk $ *//**

  \file NpxHostApi.h
  \brief Master include file for the netPROXY host functionality when accessed via DPM.

  \note Exclusion of Liability for this demo software:\n
    The following software is intended for and must only be used for reference and in an evaluation laboratory
    environment. It is provided without charge and is subject to alterations. There is no warranty for the software,
    to the extent permitted by applicable law. Except when otherwise stated in writing the copyright holders and/or
    other parties provide the software "as is" without warranty of any kind, either expressed or implied.\n
    Please refer to the Agreement in \ref disclaimer, provided  together with this file! By installing or otherwise
    using the software, you accept the terms of this Agreement. If you do not agree to the terms of this Agreement,
    then do not install or use the Software!

***********************************************************************************************************************/
#ifndef __NPX_HOST_API_H
#define __NPX_HOST_API_H

#if defined(__cplusplus)
extern "C" {
#endif


/* C library dependencies */
#include <stdint.h>

/* cifX dependencies */
#include "cifXUser.h"           /* cifX driver functions, data types, and symbol definitions */
#include "cifXErrors.h"         /* cifX error codes */
#include "OS_Dependent.h"       /* OS abstraction */


#include "NpxHostApiBasics.h" /* netPROXY host API common definitions and basic services */
#include "NpxHostApiAsync.h"  /* netPROXY host API non-blocking mode services */
#include "NpxHostApiSync.h"   /* netPROXY host API blocking mode services */



#ifdef __cplusplus
}
#endif  /* _cplusplus */

#endif /* __NPX_HOST_API_H */
