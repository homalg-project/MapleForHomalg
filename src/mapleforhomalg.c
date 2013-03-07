/***************************************************************************
**
**  mapleforhomalg.c               MapleForHomalg package    Thomas Bächler
**
*/

const char * Revision_mapleforhomalg_c =
   "mapleforhomalg.c, V0.1";

/* Try to use as much of the GNU C library as possible: */
#define _GNU_SOURCE

#include "src/compiled.h"          /* GAP headers                */

/* The following seems to be necessary to run under modern gcc compilers
 * which have the ssp stack checking enabled. Hopefully this does not
 * hurt in future or other versions... */
#ifdef __GNUC__
#if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1))
extern void __stack_chk_fail();
void __stack_chk_fail_local (void)
{
  __stack_chk_fail ();
}
#endif
#endif

#include <maplec.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static MKernelVector kv = NULL;
static char *errptr = NULL;

static void NullCallback( void *data, int tag, char *output ) {
}

static void errorCallBack(void *data, M_INT offset, char *msg ) {
  /*fprintf(stderr, "%s\n", msg);*/
  if(errptr == NULL) {
    errptr = malloc(strlen(msg)+1);
    errptr[0] = '\0';
  }
  else {
    errptr = realloc(errptr, strlen(errptr)+strlen(msg)+2);
    strcat(errptr, "\n");
  }
  strcat(errptr, msg);
}

Obj FuncSTART_MAPLE_KERNEL( Obj self ) {
  MCallBackVectorDesc cb = {
    .textCallBack = &NullCallback,
    .errorCallBack = &errorCallBack,
    .statusCallBack = NULL,
    .readLineCallBack = NULL,
    .redirectCallBack = NULL,
    .streamCallBack = NULL,
    .queryInterrupt = NULL,
    .callBackCallBack = NULL
  };
  char maple_error[2048];

  maple_error[0] = '\0';
  if(kv != NULL)
    return False;

  kv = StartMaple(0, NULL, &cb, NULL, NULL, maple_error);

  if(kv == NULL) {
    fprintf(stderr, "%s\n", maple_error);
    return False;
  }
  else {
    return True;
  }
}

Obj FuncEXECUTE_MAPLE_COMMAND( Obj self, Obj cmd ) {
  char *str;
  Obj g_str, g_err, ret;
  ALGEB m;
  size_t i;

  if(kv == NULL) {
    fprintf(stderr, "No Maple kernel is running.\n");
    return NULL;
  }

  str = CSTR_STRING(cmd);
  m = EvalMapleStatement(kv, str);
  i = strlen(str)-1;
  while(i>=0 && (str[i] == '\n' || str[i] == '\r' || str[i] == ' ' || str[i] == '\t'))
    --i;
  if(i >= 0 && str[i] != ':' && m != NULL && !IsMapleNULL(kv, m)) {
    str = MapleToString(kv, EvalMapleProc(kv, ToMapleName(kv, "sprintf", 1), 2, ToMapleString(kv, "%Q"), m));
  }
  else {
    str = NULL;
  }

  if(str != NULL) {
    g_str = NEW_STRING(strlen(str));
    COPY_CHARS(g_str, str, strlen(str));
  }
  else {
    g_str = NEW_STRING(0);
  }

  if(errptr != NULL) {
    g_err = NEW_STRING(strlen(errptr));
    COPY_CHARS(g_err, errptr, strlen(errptr));
    free(errptr);
    errptr = NULL;
  }
  else {
    g_err = NEW_STRING(0);
  }

  ret = NEW_PLIST(T_PLIST, 2);
  SET_LEN_PLIST(ret, 2);
  SET_ELM_PLIST(ret, 1, g_str);
  SET_ELM_PLIST(ret, 2, g_err);
  return ret;
}

Obj FuncSTOP_MAPLE_KERNEL( Obj self ) {
  if(kv != NULL) {
    StopMaple(kv);
    kv = NULL;
  }
  return NULL;
}


/*F * * * * * * * * * * * * * initialize package * * * * * * * * * * * * * * */

/******************************************************************************
*V  GVarFuncs . . . . . . . . . . . . . . . . . . list of functions to export
*/
static StructGVarFunc GVarFuncs [] = {

  { "START_MAPLE_KERNEL", 0, "",
    FuncSTART_MAPLE_KERNEL,
    "mapleforhomalg.c:START_MAPLE_KERNEL" },

  { "EXECUTE_MAPLE_COMMAND", 1, "cmd",
    FuncEXECUTE_MAPLE_COMMAND,
    "mapleforhomalg.c:EXECUTE_MAPLE_COMMAND" },

  { "STOP_MAPLE_KERNEL", 0, "",
    FuncSTOP_MAPLE_KERNEL,
    "mapleforhomalg.c:STOP_MAPLE_KERNEL" },

  { 0 }

};

/******************************************************************************
*F  InitKernel( <module> )  . . . . . . . . initialise kernel data structures
*/
static Int InitKernel ( StructInitInfo *module )
{
    /* init filters and functions                                          */
    InitHdlrFuncsFromTable( GVarFuncs );

    /* return success                                                      */
    return 0;
}

/******************************************************************************
*F  InitLibrary( <module> ) . . . . . . .  initialise library data structures
*/
static Int InitLibrary ( StructInitInfo *module )
{
    /* init functions */
    InitGVarFuncsFromTable(GVarFuncs);

    /* return success                                                      */
    return 0;
}

/******************************************************************************
*F  InitInfopl()  . . . . . . . . . . . . . . . . . table of init functions
*/
static StructInitInfo module = {
 /* type        = */ MODULE_DYNAMIC,
 /* name        = */ "mapleforhomalg",
 /* revision_c  = */ 0,
 /* revision_h  = */ 0,
 /* version     = */ 0,
 /* crc         = */ 0,
 /* initKernel  = */ InitKernel,
 /* initLibrary = */ InitLibrary,
 /* checkInit   = */ 0,
 /* preSave     = */ 0,
 /* postSave    = */ 0,
 /* postRestore = */ 0
};

StructInitInfo * Init__Dynamic ( void )
{
  module.revision_c = Revision_mapleforhomalg_c;
  return &module;
}

StructInitInfo * Init__mapleforhomalg ( void )
{
  module.revision_c = Revision_mapleforhomalg_c;
  return &module;
}


/*
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
