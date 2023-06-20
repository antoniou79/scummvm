/***************************************************************************/
/*                                                                         */
/*  ftconfig.h                                                             */
/*                                                                         */
/*    VMS-specific configuration file (specification only).                */
/*                                                                         */
/*  Copyright 1996-2001, 2002 by                                           */
/*  David Turner, Robert Wilhelm, and Werner Lemberg.                      */
/*                                                                         */
/*  This file is part of the FreeType project, and may only be used,       */
/*  modified, and distributed under the terms of the FreeType project      */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */
/*  understand and accept it fully.                                        */
/*                                                                         */
/***************************************************************************/


  /*************************************************************************/
  /*                                                                       */
  /* This header file contains a number of macro definitions that are used */
  /* by the rest of the engine.  Most of the macros here are automatically */
  /* determined at compile time, and you should not need to change it to   */
  /* port FreeType, except to compile the library with a non-ANSI          */
  /* compiler.                                                             */
  /*                                                                       */
  /* Note however that if some specific modifications are needed, we       */
  /* advise you to place a modified copy in your build directory.          */
  /*                                                                       */
  /* The build directory is usually `freetype/builds/<system>', and        */
  /* contains system-specific files that are always included first when    */
  /* building the library.                                                 */
  /*                                                                       */
  /*************************************************************************/


#ifndef FTCONFIG_H
#define FTCONFIG_H


  /* Include the header file containing all developer build options */
#include "engines/ags/lib/freetype-2.1.3/include/ft2build.h"
#include FT2_1_3_CONFIG_OPTIONS_H
#include FT2_1_3_CONFIG_STANDARD_LIBRARY_H

FT2_1_3_BEGIN_HEADER

  /*************************************************************************/
  /*                                                                       */
  /*               PLATFORM-SPECIFIC CONFIGURATION MACROS                  */
  /*                                                                       */
  /* These macros can be toggled to suit a specific system.  The current   */
  /* ones are defaults used to compile FreeType in an ANSI C environment   */
  /* (16bit compilers are also supported).  Copy this file to your own     */
  /* `freetype/builds/<system>' directory, and edit it to port the engine. */
  /*                                                                       */
  /*************************************************************************/


#define HAVE_UNISTD_H  1
#define HAVE_FCNTL_H   1

#define SIZEOF_INT   4
#define SIZEOF_LONG  4

#define FT2_1_3_SIZEOF_INT   4
#define FT2_1_3_SIZEOF_LONG  4


  /* Preferred alignment of data */
#define FT2_1_3_ALIGNMENT  8


  /* FT2_1_3_UNUSED is a macro used to indicate that a given parameter is not  */
  /* used -- this is only used to get rid of unpleasant compiler warnings */
#ifndef FT2_1_3_UNUSED
#define FT2_1_3_UNUSED( arg )  ( (arg) = (arg) )
#endif


  /*************************************************************************/
  /*                                                                       */
  /*                     AUTOMATIC CONFIGURATION MACROS                    */
  /*                                                                       */
  /* These macros are computed from the ones defined above.  Don't touch   */
  /* their definition, unless you know precisely what you are doing.  No   */
  /* porter should need to mess with them.                                 */
  /*                                                                       */
  /*************************************************************************/


  /*************************************************************************/
  /*                                                                       */
  /* IntN types                                                            */
  /*                                                                       */
  /*   Used to guarantee the size of some specific integers.               */
  /*                                                                       */
  typedef signed short    FT2_1_3_Int16;
  typedef unsigned short  FT2_1_3_UInt16;

#if FT2_1_3_SIZEOF_INT == 4

  typedef signed int      FT2_1_3_Int32;
  typedef unsigned int    FT2_1_3_UInt32;

#elif FT2_1_3_SIZEOF_LONG == 4

  typedef signed long     FT2_1_3_Int32;
  typedef unsigned long   FT2_1_3_UInt32;

#else
#error "no 32bit type found -- please check your configuration files"
#endif

#if FT2_1_3_SIZEOF_LONG == 8

  /* FT2_1_3_LONG64 must be defined if a 64-bit type is available */
#define FT2_1_3_LONG64
#define FT2_1_3_INT64   long

#else

  /*************************************************************************/
  /*                                                                       */
  /* Many compilers provide the non-ANSI `long long' 64-bit type.  You can */
  /* activate it by defining the FTCALC_USE_LONG_LONG macro in             */
  /* `ftoption.h'.                                                         */
  /*                                                                       */
  /* Note that this will produce many -ansi warnings during library        */
  /* compilation, and that in many cases,  the generated code will be      */
  /* neither smaller nor faster!                                           */
  /*                                                                       */
#ifdef FTCALC_USE_LONG_LONG

#define FT2_1_3_LONG64
#define FT2_1_3_INT64   long long

#endif /* FTCALC_USE_LONG_LONG */

#endif /* FT2_1_3_SIZEOF_LONG == 8 */


#ifdef FT2_1_3_MAKE_OPTION_SINGLE_OBJECT

#define FT2_1_3_LOCAL( x )      static  x
#define FT2_1_3_LOCAL_DEF( x )  static  x

#else

#ifdef __cplusplus
#define FT2_1_3_LOCAL( x )      extern "C"  x
#define FT2_1_3_LOCAL_DEF( x )  extern "C"  x
#else
#define FT2_1_3_LOCAL( x )      extern  x
#define FT2_1_3_LOCAL_DEF( x )  x
#endif

#endif /* FT2_1_3_MAKE_OPTION_SINGLE_OBJECT */

#ifndef FT2_1_3_BASE

#ifdef __cplusplus
#define FT2_1_3_BASE( x )  extern "C"  x
#else
#define FT2_1_3_BASE( x )  extern  x
#endif

#endif /* !FT2_1_3_BASE */

#ifndef BASE_DEF

#ifdef __cplusplus
#define BASE_DEF( x )  extern "C"  x
#else
#define BASE_DEF( x )  extern  x
#endif

#endif /* !BASE_DEF */


#ifndef FT2_1_3_EXPORT

#ifdef __cplusplus
#define FT2_1_3_EXPORT( x )  extern "C"  x
#else
#define FT2_1_3_EXPORT( x )  extern  x
#endif

#endif /* !FT2_1_3_EXPORT */

#ifndef FT2_1_3_EXPORT_DEF

#ifdef __cplusplus
#define FT2_1_3_EXPORT_DEF( x )  extern "C"  x
#else
#define FT2_1_3_EXPORT_DEF( x )  extern  x
#endif

#endif /* !FT2_1_3_EXPORT_DEF */


#ifndef FT2_1_3_EXPORT_VAR

#ifdef __cplusplus
#define FT2_1_3_EXPORT_VAR( x )  extern "C"  x
#else
#define FT2_1_3_EXPORT_VAR( x )  extern  x
#endif

#endif /* !FT2_1_3_EXPORT_VAR */


  /* This is special.  Within C++, you must specify `extern "C"' for */
  /* functions which are used via function pointers, and you also    */
  /* must do that for structures which contain function pointers to  */
  /* assure C linkage -- it's not possible to have (local) anonymous */
  /* functions which are accessed by (global) function pointers.     */
  /*                                                                 */
#ifdef __cplusplus

#define FT2_1_3_CALLBACK_DEF( x )        extern "C"  x
#define FT2_1_3_CALLBACK_TABLE           extern "C"
#define FT2_1_3_CALLBACK_TABLE_DEF       extern "C"

#else

#define FT2_1_3_CALLBACK_DEF( x )        static  x
#define FT2_1_3_CALLBACK_TABLE           extern
#define FT2_1_3_CALLBACK_TABLE_DEF

#endif /* __cplusplus */

FT2_1_3_END_HEADER

#endif /* FTCONFIG_H */


/* END */
