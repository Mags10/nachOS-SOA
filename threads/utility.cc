// utility.cc 
//	Debugging routines.  Allows users to control whether to 
//	print DEBUG statements, based on a command line argument.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "utility.h"

// this seems to be dependent on how the compiler is configured.
// if you have problems with va_start, try both of these alternatives
#ifdef HOST_SNAKE
#include <stdarg.h>
#else
#ifdef HOST_SPARC
#include <stdarg.h>
#else
#include "stdarg.h"
#endif
#endif

static char *enableFlags = NULL; // controls which DEBUG messages are printed 
static bool dprint = FALSE; // controls which DPRINT messages are printed

//----------------------------------------------------------------------
// DebugInit
//      Initialize so that only DEBUG messages with a flag in flagList 
//	will be printed.
//
//	If the flag is "+", we enable all DEBUG messages.
//
// 	"flagList" is a string of characters for whose DEBUG messages are 
//		to be enabled.
// 
//  Aditionally, if the flag is #, means that print from dev are allowed
//----------------------------------------------------------------------

void
DebugInit(char *flagList, bool prn)
{
    enableFlags = flagList;
    dprint = prn;
}

//----------------------------------------------------------------------
// DebugIsEnabled
//      Return TRUE if DEBUG messages with "flag" are to be printed.
//----------------------------------------------------------------------

bool
DebugIsEnabled(char flag)
{
    if (dprint) return FALSE;
    if (enableFlags != NULL)
       return (strchr(enableFlags, flag) != 0) 
		|| (strchr(enableFlags, '+') != 0);
    else
      return FALSE;
}

//----------------------------------------------------------------------
// DEBUG
//      Print a debug message, if flag is enabled.  Like printf,
//	only with an extra argument on the front.
//----------------------------------------------------------------------

void 
DEBUG(char flag, char *format, ...)
{
    if (DebugIsEnabled(flag)) {
	va_list ap;
	// You will get an unused variable message here -- ignore it.
	va_start(ap, format);
	vfprintf(stdout, format, ap);
	va_end(ap);
	fflush(stdout);
    }
}

//----------------------------------------------------------------------
// DPRINT IsEnabled
//      Return TRUE if DEBUG PRINT messages with "flag" are to be printed.
//----------------------------------------------------------------------

bool
DPrintIsEnabled(char flag)
{
    if (!dprint) return FALSE;
    if (enableFlags != NULL)
       return (strchr(enableFlags, flag) != 0) 
		|| (strchr(enableFlags, '+') != 0);
    else
      return FALSE;
}

//----------------------------------------------------------------------

// DPRINT
//      Print a debug message, if flag is enabled.  Like printf,
//      only with an extra argument on the front.
//----------------------------------------------------------------------

void
DPRINT(char flag, char *format, ...)
{
    if (DPrintIsEnabled(flag)) {
    va_list ap;
    // You will get an unused variable message here -- ignore it.
    va_start(ap, format);
    vfprintf(stdout, format, ap);
    va_end(ap);
    fflush(stdout);
    }
}