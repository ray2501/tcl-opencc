/*
 * For C++ compilers, use extern "C"
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <tcl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opencc.h>

/*
 * Only the _Init function is exported.
 */

extern DLLEXPORT int    Opencc_Init(Tcl_Interp * interp);

/*
 * end block for C++
 */

#ifdef __cplusplus
}
#endif


typedef struct OpenccData OpenccData;

struct OpenccData {
  opencc_t handle;
  Tcl_Interp *interp;
};


static int OpenccObjCmd(void *cd, Tcl_Interp *interp, int objc,Tcl_Obj *const*objv){
  OpenccData *pData = (OpenccData *) cd;
  int choice;
  int rc = TCL_OK;

  static const char *Openccstrs[] = {
    "convert",
    "close",
    0
  };

  enum Openccenum {
    OpenccCONVERT,
    OpenccCLOSE,
  };

  if( objc < 2 ){
    Tcl_WrongNumArgs(interp, 1, objv, "SUBCOMMAND ...");
    return TCL_ERROR;
  }

  if( Tcl_GetIndexFromObj(interp, objv[1], Openccstrs, "option", 0, &choice) ){
    return TCL_ERROR;
  }

  switch( (enum Openccenum)choice ){

    case OpenccCONVERT: {
      char *inputstring = NULL;
      Tcl_Size len = 0;
      char *outputstring = NULL;
      Tcl_Obj *return_obj = NULL;

      if( objc != 3 ){
        Tcl_WrongNumArgs(interp, 2, objv, "utf8_string");
        return TCL_ERROR;
      }

      inputstring = Tcl_GetStringFromObj(objv[2], &len);
      if( !inputstring || len < 1 ){
        return TCL_ERROR;
      }

      outputstring = opencc_convert_utf8(pData->handle, inputstring, len);
      if( !outputstring ){
        return TCL_ERROR;
      }

      return_obj = Tcl_NewStringObj(outputstring, -1);
      opencc_convert_utf8_free(outputstring);

      Tcl_SetObjResult(interp, return_obj);
      break;
    }

    case OpenccCLOSE: {
      int result = 0;
      Tcl_Obj *return_obj = NULL;

      if( objc != 2 ){
        Tcl_WrongNumArgs(interp, 2, objv, 0);
        return TCL_ERROR;
      }

      result = opencc_close(pData->handle);

      Tcl_Free((char *)pData);
      pData = NULL;

      Tcl_DeleteCommand(interp, Tcl_GetStringFromObj(objv[0], 0));

      return_obj = Tcl_NewIntObj(result);
      Tcl_SetObjResult(interp, return_obj);
      break;
    }

  } /* End of the SWITCH statement */

  return rc;
}


static int OpenccMain(void *cd, Tcl_Interp *interp, int objc,Tcl_Obj *const*objv){
  OpenccData *p;
  const char *zArg = NULL;  
  const char *zFile = NULL;
  Tcl_Size len;

  if( objc != 3 ){
    Tcl_WrongNumArgs(interp, 1, objv,
      "HANDLE configFileName "
    );
    return TCL_ERROR;
  }

  p = (OpenccData *)Tcl_Alloc( sizeof(*p) );
  if( p==0 ){
    Tcl_SetResult(interp, (char *)"malloc failed", TCL_STATIC);
    return TCL_ERROR;
  }

  memset(p, 0, sizeof(*p));
  p->interp = interp;

  zFile = Tcl_GetStringFromObj(objv[2], &len);
  if( !zFile || len < 1 ){
    Tcl_Free((char *)p);
    return TCL_ERROR;
  }


  p->handle = opencc_open(zFile);
  if(p->handle==NULL || p->handle==(opencc_t) -1) {
      Tcl_Free((char *)p);  //open fail, so we need free our memory
      p = NULL;

      Tcl_SetResult(interp, (char *)"open failed", TCL_STATIC);
      return TCL_ERROR;
  }

  zArg = Tcl_GetStringFromObj(objv[1], 0);
  Tcl_CreateObjCommand(interp, zArg, OpenccObjCmd, (char*)p, (Tcl_CmdDeleteProc *)NULL);

  return TCL_OK;
}


/*
 *----------------------------------------------------------------------
 *
 * Opencc_Init --
 *
 *	Initialize the new package.
 *
 * Results:
 *	A standard Tcl result
 *
 * Side effects:
 *	The Opencc package is created.
 *
 *----------------------------------------------------------------------
 */

int
Opencc_Init(Tcl_Interp *interp)
{
    if (Tcl_InitStubs(interp, "8.4", 0) == NULL) {
	return TCL_ERROR;
    }
    if (Tcl_PkgProvide(interp, PACKAGE_NAME, PACKAGE_VERSION) != TCL_OK) {
	return TCL_ERROR;
    }

    Tcl_CreateObjCommand(interp, "opencc", (Tcl_ObjCmdProc *) OpenccMain,
        (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);    

    return TCL_OK;
}
