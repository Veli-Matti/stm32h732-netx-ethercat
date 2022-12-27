/**************************************************************************************
  Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.
***************************************************************************************
  $Id: netPROXY.h 3816 2018-02-28 16:09:11Z dirk $

  Description:
    netPROXY Core (runtime) main header file.

  NOTE:
    Include this file to all c modules which use netPROXY.

**************************************************************************************/
#ifndef __NETPROXY_H
#define __NETPROXY_H

#include <string.h>
#include <stdint.h>   /* ISO/IEC 9899:1999 fixed width data types */
#include <stdbool.h>  /* ISO/IEC 9899:1999 bool data type */

#include "npx_types.h"
#include "netPROXY_Results.h"

#include "npx_core_api.h"
#include "npx_interface_api.h"
#include "npx_dictionary_api.h"
#include "npx_object_api.h"
#include "npx_async_api.h"
#include "npx_sync_api.h"
#include "npx_package_api.h"
#include "npx_eventlog_api.h"
#include "npx_extensions_api.h"

/*!

\mainpage netPROXY server API manual

netPROXY server API manual
========================

The netPROXY server API cna be subdivided into the following modules
- \ref npx_types "General netPROXY types"
- \ref npx_sys_functions "System and interface functions"
- \ref npx_dir_functions "Object directory functions"
- \ref npx_obj_functions "Object functions"
- \ref npx_result "netPROXY result codes"

*/

/*! \defgroup npx_types General netPROXY types

General netPROXY types
=======================

All generic netPROXY data types are defined in the npx_types.h header file. All other types are grouped directly
to the related functions.

*/


/*! \defgroup npx_sys_functions System and interface functions

System and interface functions
===============================

This chapter describes the system and interface functions of the netPROXY Function API. such functions are defined
in the following npx_core_api.h header file.

*/


/*! \defgroup npx_dir_functions Object directory functions

Object directory functions
===============================

The object directory functions are used to manage all object description and registered object entities all functions
are defined in the in the npx_dictionary_api.h header file.

*/


/*! \defgroup npx_obj_functions Object functions

Object functions
===============================

Object functions are used to manage existing object entities, e.g. register a update notification to the object.

*/


/*! \defgroup npx_result netPROXY result codes

netPROXY result codes
======================

NetPROXY uses the standard Hilscher result codes. Such codes are Hilscher wide unique beside from the standard code
defined in the general error header file, netPROXY specific codes are defined and described in the netPROXY_Results.

*/


#endif /* __NETPROXY_H */
