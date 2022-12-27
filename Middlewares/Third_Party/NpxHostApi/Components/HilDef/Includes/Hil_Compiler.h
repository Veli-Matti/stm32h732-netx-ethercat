/**************************************************************************************

Copyright (c) Hilscher Gesellschaft fuer Systemautomation mbH. All Rights Reserved.

***************************************************************************************

  $Id: Hil_Compiler.h 3816 2018-02-28 16:09:11Z dirk $:

  Description:
    Definitions of Compiler Settings

  Changes:
    Date        Description
    -----------------------------------------------------------------------------------
    2016-11-30  File created.

**************************************************************************************/


#ifndef __HIL_COMPILER_H
#define __HIL_COMPILER_H


/*****************************************************************************/
/* Set byte alignment for structure members. */

#if defined (_MSC_VER) && !defined(USER_COMPILER)
/* support for MS Visual C++ compiler */
  #if _MSC_VER >= 1000
    #define __HIL_PACKED_PRE
    #define __HIL_PACKED_POST
    #define __HIL_PRAGMA_PACK_ENABLE
    #define __HIL_PRAGMA_PACK_1(label) pack(push, label, 1)
    #define __HIL_PRAGMA_UNPACK_1(label) pack(pop, label)
    #ifndef STRICT
      #define STRICT
    #endif
  #endif
#elif defined (__GNUC__) && !defined(USER_COMPILER)
/* support for GNU compiler */


  #define __HIL_PACKED_PRE
  #define __HIL_PACKED_POST    __attribute__((__packed__))

/* macro for setting DWORD alignment of a tag's beginning */
  #define __HIL_ALIGNED_DWORD__   __attribute__ ((aligned (4)))

#elif (defined (__ADS__) || defined (__REALVIEW__)) && !defined(USER_COMPILER)
/* support for REALVIEW ARM compiler */

  #define __HIL_PACKED_PRE   __packed
  #define __HIL_PACKED_POST

#else

  #include "User_Compiler.h"

#endif

/*****************************************************************************/

#endif /* __HIL_COMPILER_H */
