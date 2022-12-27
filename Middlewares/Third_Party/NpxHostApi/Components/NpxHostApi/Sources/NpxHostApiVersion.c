/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id: NpxHostApiVersion.c 3816 2018-02-28 16:09:11Z dirk $

  \file NpxHostApiVersion.c
  \brief Provides hilscher version information section.

  \note Exclusion of Liability for this demo software:\n
    The following software is intended for and must only be used for reference and in an evaluation laboratory
    environment. It is provided without charge and is subject to alterations. There is no warranty for the software,
    to the extent permitted by applicable law. Except when otherwise stated in writing the copyright holders and/or
    other parties provide the software "as is" without warranty of any kind, either expressed or implied.\n
    Please refer to the Agreement in \ref disclaimer, provided  together with this file! By installing or otherwise
    using the software, you accept the terms of this Agreement. If you do not agree to the terms of this Agreement,
    then do not install or use the Software!

**************************************************************************************/
#include "NpxHostApiVersion.h"

/* number-to-string conversion macros */
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

/* the library version string */
#define LIB_VERSION_TEXT "netPROXY host API library V" \
                         TOSTRING(NPX_HOST_API_VERSION_MAJOR) "." \
                         TOSTRING(NPX_HOST_API_VERSION_MINOR) "." \
                         TOSTRING(NPX_HOST_API_VERSION_BUILD) "." \
                         TOSTRING(NPX_HOST_API_VERSION_REVISION)

const char g_szNpxHostApiLibVersion[] __attribute__ ((section (".hilscher_version"), used)) = LIB_VERSION_TEXT;
