/******************** MODULE.C **************************/
/*
 * Rory Barnes, Mon Jan 19 13:00:54 PST 2015
 *
 * Functions to manipulate the MODULE struct.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vplanet.h"

/* NULL functions for all module function pointer matrices. All pointers are 
   initialized to point to these functions. Modules that require them reset
   the pointers in AddModuleX. */

void  InitializeControlNULL(CONTROL *control) {
  // Nothing
}

void InitializeBodyNULL(BODY *body,CONTROL *control,UPDATE *update,int iBody,int iModule) {
}

void InitializeModuleNULL(CONTROL *control,MODULE *module) {
}

void InitializeUpdateTmpBodyNULL(BODY *body,CONTROL *control,UPDATE *update,int iBody) {
}

void FinalizeUpdateNULL(BODY *body,UPDATE *update,int *iEqn,int iVar,int iBody,int iFoo) {
  /* Nothing */
}

void PropsAuxNULL(BODY *body,EVOLVE *evolve,UPDATE *update,int iFoo) {
}

// Functions that are helpful for integrations

double fdReturnOutputZero(BODY *body,SYSTEM *system,UPDATE *update,int iBody,int iBody1) {
  return 0;
}

double fdUpdateFunctionTiny(BODY *body,SYSTEM *system,int *iaBody) {
  return TINY;
}

// Reset function pointer to return TINY
void SetDerivTiny(fnUpdateVariable ***fnUpdate,int iBody,int iVar,int iEqn) {
  fnUpdate[iBody][iVar][iEqn] = &fdUpdateFunctionTiny;
}

void InitializeModule(MODULE *module,int iNumBodies) {
  int iBody;

  module->iNumModules = malloc(iNumBodies*sizeof(int));
  module->iaModule = malloc(iNumBodies*sizeof(int*));  
  module->iBitSum = malloc(iNumBodies*sizeof(int*));

  // Function pointer vectors
  module->fnInitializeUpdate = malloc(iNumBodies*sizeof(fnInitializeUpdateModule));
  module->fnInitializeOutput = malloc(iNumBodies*sizeof(fnInitializeOutputModule*));
  module->fnFinalizeOutputFunction = malloc(iNumBodies*sizeof(fnFinalizeOutputFunctionModule*));

  // Finalize Primary Variable Functions
  //module->fnFinalizeUpdateEcc = malloc(iNumBodies*sizeof(fnFinalizeUpdateEccModule));
  module->fnFinalizeUpdate26AlNumCore = malloc(iNumBodies*sizeof(fnFinalizeUpdate26AlNumCoreModule));
  module->fnFinalizeUpdate26AlNumMan = malloc(iNumBodies*sizeof(fnFinalizeUpdate26AlNumManModule));
  module->fnFinalizeUpdate40KNumCore = malloc(iNumBodies*sizeof(fnFinalizeUpdate40KNumCoreModule));
  module->fnFinalizeUpdate40KNumCrust = malloc(iNumBodies*sizeof(fnFinalizeUpdate40KNumCrustModule));
  module->fnFinalizeUpdate40KNumMan = malloc(iNumBodies*sizeof(fnFinalizeUpdate40KNumManModule));
  module->fnFinalizeUpdate232ThNumCore = malloc(iNumBodies*sizeof(fnFinalizeUpdate232ThNumCoreModule));
  module->fnFinalizeUpdate232ThNumCrust = malloc(iNumBodies*sizeof(fnFinalizeUpdate232ThNumCrustModule));
  module->fnFinalizeUpdate232ThNumMan = malloc(iNumBodies*sizeof(fnFinalizeUpdate232ThNumManModule));
  module->fnFinalizeUpdate235UNumCore = malloc(iNumBodies*sizeof(fnFinalizeUpdate235UNumCoreModule));
  module->fnFinalizeUpdate235UNumCrust = malloc(iNumBodies*sizeof(fnFinalizeUpdate235UNumCrustModule));
  module->fnFinalizeUpdate235UNumMan = malloc(iNumBodies*sizeof(fnFinalizeUpdate235UNumManModule)); 
  module->fnFinalizeUpdate238UNumCore = malloc(iNumBodies*sizeof(fnFinalizeUpdate238UNumCoreModule));
  module->fnFinalizeUpdate238UNumCrust = malloc(iNumBodies*sizeof(fnFinalizeUpdate238UNumCrustModule));
  module->fnFinalizeUpdate238UNumMan = malloc(iNumBodies*sizeof(fnFinalizeUpdate238UNumManModule));

  module->fnFinalizeUpdateCBPR = malloc(iNumBodies*sizeof(fnFinalizeUpdateCBPRModule));
  module->fnFinalizeUpdateCBPZ = malloc(iNumBodies*sizeof(fnFinalizeUpdateCBPZModule));
  module->fnFinalizeUpdateCBPPhi = malloc(iNumBodies*sizeof(fnFinalizeUpdateCBPPhiModule));
  module->fnFinalizeUpdateCBPRDot = malloc(iNumBodies*sizeof(fnFinalizeUpdateCBPRDotModule));
  module->fnFinalizeUpdateCBPZDot = malloc(iNumBodies*sizeof(fnFinalizeUpdateCBPZDotModule));
  module->fnFinalizeUpdateCBPPhiDot = malloc(iNumBodies*sizeof(fnFinalizeUpdateCBPPhiDotModule));

  module->fnFinalizeUpdateDynEllip = malloc(iNumBodies*sizeof(fnFinalizeUpdateDynEllipModule));
  module->fnFinalizeUpdateEnvelopeMass = malloc(iNumBodies*sizeof(fnFinalizeUpdateEnvelopeMassModule));
  module->fnFinalizeUpdateHecc = malloc(iNumBodies*sizeof(fnFinalizeUpdateHeccModule));
  module->fnFinalizeUpdateIceMass = malloc(iNumBodies*sizeof(fnFinalizeUpdateIceMassModule));
  module->fnFinalizeUpdateKecc = malloc(iNumBodies*sizeof(fnFinalizeUpdateKeccModule));
  module->fnFinalizeUpdateLuminosity = malloc(iNumBodies*sizeof(fnFinalizeUpdateLuminosityModule));
  module->fnFinalizeUpdateLXUV = malloc(iNumBodies*sizeof(fnFinalizeUpdateIceMassModule));

  module->fnFinalizeUpdateMass = malloc(iNumBodies*sizeof(fnFinalizeUpdateMassModule));
  module->fnFinalizeUpdateOxygenMass = malloc(iNumBodies*sizeof(fnFinalizeUpdateOxygenMassModule));
  module->fnFinalizeUpdateOxygenMantleMass = malloc(iNumBodies*sizeof(fnFinalizeUpdateOxygenMantleMassModule));
  module->fnFinalizeUpdatePinc = malloc(iNumBodies*sizeof(fnFinalizeUpdatePincModule));
  module->fnFinalizeUpdateQinc = malloc(iNumBodies*sizeof(fnFinalizeUpdateQincModule));
  module->fnFinalizeUpdateRadius = malloc(iNumBodies*sizeof(fnFinalizeUpdateRadiusModule));
  module->fnFinalizeUpdateRot = malloc(iNumBodies*sizeof(fnFinalizeUpdateRotModule));
  module->fnFinalizeUpdateSemi = malloc(iNumBodies*sizeof(fnFinalizeUpdateSemiModule ));

  module->fnFinalizeUpdateSurfaceWaterMass = malloc(iNumBodies*sizeof(fnFinalizeUpdateSurfaceWaterMassModule));
  module->fnFinalizeUpdateTemperature = malloc(iNumBodies*sizeof(fnFinalizeUpdateTemperatureModule));
  module->fnFinalizeUpdateTMan = malloc(iNumBodies*sizeof(fnFinalizeUpdateTManModule));
  module->fnFinalizeUpdateTCore = malloc(iNumBodies*sizeof(fnFinalizeUpdateTCoreModule));
  module->fnFinalizeUpdateXobl = malloc(iNumBodies*sizeof(fnFinalizeUpdateXoblModule));
  module->fnFinalizeUpdateYobl = malloc(iNumBodies*sizeof(fnFinalizeUpdateYoblModule));
  module->fnFinalizeUpdateZobl = malloc(iNumBodies*sizeof(fnFinalizeUpdateZoblModule));
  
  module->fnFinalizeUpdateEccX = malloc(iNumBodies*sizeof(fnFinalizeUpdateEccXModule));
  module->fnFinalizeUpdateEccY = malloc(iNumBodies*sizeof(fnFinalizeUpdateEccYModule));
  module->fnFinalizeUpdateEccZ = malloc(iNumBodies*sizeof(fnFinalizeUpdateEccZModule));
  module->fnFinalizeUpdateAngMX = malloc(iNumBodies*sizeof(fnFinalizeUpdateAngMXModule));
  module->fnFinalizeUpdateAngMY = malloc(iNumBodies*sizeof(fnFinalizeUpdateAngMYModule));
  module->fnFinalizeUpdateAngMZ = malloc(iNumBodies*sizeof(fnFinalizeUpdateAngMZModule));

  
  // Function Pointer Matrices
  module->fnLogBody = malloc(iNumBodies*sizeof(fnLogBodyModule*));
  module->fnInitializeBody = malloc(iNumBodies*sizeof(fnInitializeBodyModule*));
  module->fnInitializeControl = malloc(iNumBodies*sizeof(fnInitializeControlModule*));
  module->fnInitializeUpdateTmpBody = malloc(iNumBodies*sizeof(fnInitializeUpdateTmpBodyModule*));
  module->fnCountHalts = malloc(iNumBodies*sizeof(fnCountHaltsModule*));
  module->fnReadOptions = malloc(iNumBodies*sizeof(fnReadOptionsModule*));
  module->fnVerify = malloc(iNumBodies*sizeof(fnVerifyModule*));
  module->fnVerifyHalt = malloc(iNumBodies*sizeof(fnVerifyHaltModule*));

  /* Assume no modules per body to start */
  for (iBody=0;iBody<iNumBodies;iBody++) 
    module->iNumModules[iBody]=0;
}

void FinalizeModule(BODY *body,MODULE *module,int iBody) {
  int iModule=0,iNumModules = 0;

  /************************
   * ADD NEW MODULES HERE *
   ************************/

  if (body[iBody].bEqtide)
    iNumModules++;
  if (body[iBody].bDistOrb)
    iNumModules++;
  if (body[iBody].bDistRot)
    iNumModules++;
  if (body[iBody].bRadheat)
    iNumModules++;
  if (body[iBody].bThermint)
    iNumModules++;
  if (body[iBody].bAtmEsc)
    iNumModules++;
  if (body[iBody].bStellar)
    iNumModules++;
  if (body[iBody].bPoise)
    iNumModules++;
  if (body[iBody].bBinary)
    iNumModules++;
  if (body[iBody].bFlare)
    iNumModules++;
  if (body[iBody].bGalHabit)
    iNumModules++;

  module->iNumModules[iBody] = iNumModules;
  module->iaModule[iBody] = malloc(iNumModules*sizeof(int));

  module->fnLogBody[iBody] = malloc(iNumModules*sizeof(fnLogBodyModule));
  module->fnInitializeControl[iBody] = malloc(iNumModules*sizeof(fnInitializeControlModule));
  module->fnInitializeOutput[iBody] = malloc(iNumModules*sizeof(fnInitializeOutputModule));
  module->fnInitializeUpdateTmpBody[iBody] = malloc(iNumModules*sizeof(fnInitializeUpdateTmpBodyModule));

  module->fnFinalizeOutputFunction[iBody] = malloc(iNumModules*sizeof(fnInitializeOutputFunctionModule));

  module->fnCountHalts[iBody] = malloc(iNumModules*sizeof(fnCountHaltsModule));
  module->fnReadOptions[iBody] = malloc(iNumModules*sizeof(fnReadOptionsModule));
  module->fnVerify[iBody] = malloc(iNumModules*sizeof(fnVerifyModule));
  module->fnVerifyHalt[iBody] = malloc(iNumModules*sizeof(fnVerifyHaltModule));

  module->fnInitializeBody[iBody] = malloc(iNumModules*sizeof(fnInitializeBodyModule));
  module->fnInitializeUpdate[iBody] = malloc(iNumModules*sizeof(fnInitializeUpdateModule));

  // Finalize Primary Variable Functions
  module->fnFinalizeUpdate26AlNumCore[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate26AlNumCoreModule));
  module->fnFinalizeUpdate26AlNumMan[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate26AlNumManModule));
  module->fnFinalizeUpdate40KNumCore[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate40KNumCoreModule));
  module->fnFinalizeUpdate40KNumCrust[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate40KNumCrustModule));
  module->fnFinalizeUpdate40KNumMan[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate40KNumManModule));
  module->fnFinalizeUpdate232ThNumCore[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate232ThNumCoreModule));
  module->fnFinalizeUpdate232ThNumCrust[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate232ThNumCrustModule));
  module->fnFinalizeUpdate232ThNumMan[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate232ThNumManModule));
  module->fnFinalizeUpdate235UNumCore[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate235UNumCoreModule));
  module->fnFinalizeUpdate235UNumCrust[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate235UNumCrustModule));
  module->fnFinalizeUpdate235UNumMan[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate235UNumManModule));  
  module->fnFinalizeUpdate238UNumCore[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate238UNumCoreModule));
  module->fnFinalizeUpdate238UNumCrust[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate238UNumCrustModule));
  module->fnFinalizeUpdate238UNumMan[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdate238UNumManModule));

  module->fnFinalizeUpdateCBPR[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateCBPRModule));
  module->fnFinalizeUpdateCBPZ[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateCBPZModule));
  module->fnFinalizeUpdateCBPPhi[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateCBPPhiModule));
  module->fnFinalizeUpdateCBPRDot[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateCBPRDotModule));
  module->fnFinalizeUpdateCBPZDot[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateCBPZDotModule));
  module->fnFinalizeUpdateCBPPhiDot[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateCBPPhiDotModule));

  module->fnFinalizeUpdateDynEllip[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateDynEllipModule));
  module->fnFinalizeUpdateEnvelopeMass[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateEnvelopeMassModule));
  module->fnFinalizeUpdateHecc[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateHeccModule));
  module->fnFinalizeUpdateIceMass[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateIceMassModule));
  module->fnFinalizeUpdateKecc[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateKeccModule));
  module->fnFinalizeUpdateLuminosity[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateLuminosityModule));
  module->fnFinalizeUpdateLXUV[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateMassModule));
  module->fnFinalizeUpdateMass[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateMassModule));
  module->fnFinalizeUpdateOxygenMass[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateOxygenMassModule));
  module->fnFinalizeUpdateOxygenMantleMass[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateOxygenMantleMassModule));
  module->fnFinalizeUpdatePinc[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdatePincModule));
  module->fnFinalizeUpdateQinc[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateQincModule));

  module->fnFinalizeUpdateRadius[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateRadiusModule));
  module->fnFinalizeUpdateRot[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateRotModule));
  module->fnFinalizeUpdateSemi[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateSemiModule));
  module->fnFinalizeUpdateSurfaceWaterMass[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateSurfaceWaterMassModule));
  module->fnFinalizeUpdateTCore[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateTCoreModule));
  module->fnFinalizeUpdateTMan[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateTManModule));
  module->fnFinalizeUpdateXobl[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateXoblModule));
  module->fnFinalizeUpdateYobl[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateYoblModule));
  module->fnFinalizeUpdateZobl[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateZoblModule));
  module->fnFinalizeUpdateTemperature[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateTemperatureModule));
  
  module->fnFinalizeUpdateEccX[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateEccXModule));
  module->fnFinalizeUpdateEccY[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateEccYModule));
  module->fnFinalizeUpdateEccZ[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateEccZModule));
  module->fnFinalizeUpdateAngMX[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateAngMXModule));
  module->fnFinalizeUpdateAngMY[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateAngMYModule));
  module->fnFinalizeUpdateAngMZ[iBody] = malloc(iNumModules*sizeof(fnFinalizeUpdateAngMZModule));


  for(iModule = 0; iModule < iNumModules; iModule++) {
    /* Initialize all module functions pointers to point to their respective
       NULL function. The modules that need actual function will replace them 
       in AddModule. */

    module->fnInitializeControl[iBody][iModule] = &InitializeControlNULL;
    module->fnInitializeUpdateTmpBody[iBody][iModule] = &InitializeUpdateTmpBodyNULL;
    module->fnInitializeBody[iBody][iModule] = &InitializeBodyNULL;

    module->fnFinalizeUpdate26AlNumCore[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate26AlNumMan[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate40KNumCore[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate40KNumCrust[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate40KNumMan[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate232ThNumCore[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate232ThNumCrust[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate232ThNumMan[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate235UNumCore[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate235UNumCrust[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate235UNumMan[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate238UNumCore[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate238UNumCrust[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdate238UNumMan[iBody][iModule] = &FinalizeUpdateNULL;

    module->fnFinalizeUpdateCBPR[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateCBPZ[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateCBPPhi[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateCBPRDot[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateCBPZDot[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateCBPPhiDot[iBody][iModule] = &FinalizeUpdateNULL;

    module->fnFinalizeUpdateDynEllip[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateEnvelopeMass[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateHecc[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateIceMass[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateKecc[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateLuminosity[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateLXUV[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateMass[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateOxygenMass[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateOxygenMantleMass[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdatePinc[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateQinc[iBody][iModule] = &FinalizeUpdateNULL;

    module->fnFinalizeUpdateRadius[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateRot[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateSemi[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateSurfaceWaterMass[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateTemperature[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateTMan[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateTCore[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateXobl[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateYobl[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateZobl[iBody][iModule] = &FinalizeUpdateNULL;
    
    module->fnFinalizeUpdateEccX[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateEccY[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateEccZ[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateAngMX[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateAngMY[iBody][iModule] = &FinalizeUpdateNULL;
    module->fnFinalizeUpdateAngMZ[iBody][iModule] = &FinalizeUpdateNULL;


  }

  /************************
   * ADD NEW MODULES HERE *
   ************************/

  iModule = 0;
  if (body[iBody].bEqtide) {
    AddModuleEqtide(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = EQTIDE;
  }
  if (body[iBody].bDistOrb) {
    AddModuleDistOrb(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = DISTORB;
  }
   if (body[iBody].bDistRot) {
    AddModuleDistRot(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = DISTROT;
  }
  if (body[iBody].bRadheat) {
    AddModuleRadheat(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = RADHEAT;
  }
  if (body[iBody].bThermint) {
      AddModuleThermint(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = THERMINT;
  }
  if (body[iBody].bAtmEsc) {
    AddModuleAtmEsc(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = ATMESC;
  }
  if (body[iBody].bStellar) {
    AddModuleStellar(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = STELLAR;
  }
  if (body[iBody].bPoise) {
    AddModulePoise(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = POISE;
  }
  if (body[iBody].bBinary) {
    AddModuleBinary(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = BINARY;
  }
  if (body[iBody].bFlare) {
    AddModuleFlare(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = FLARE;
  }
  if (body[iBody].bGalHabit) {
    AddModuleGalHabit(module,iBody,iModule);
    module->iaModule[iBody][iModule++] = GALHABIT;
  }
}

void ReadModules(BODY *body,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iFile){
  int iNumIndices=0,iNumLines=0,iModule;
  int *lTmp;
  char saTmp[MAXARRAY][OPTLEN];

  lTmp=malloc(MAXLINES*sizeof(int));

  AddOptionStringArray(files->Infile[iFile].cIn,options->cName,saTmp,&iNumIndices,&iNumLines,lTmp,control->Io.iVerbose);
  if (lTmp[0] >= 0) {
    NotPrimaryInput(iFile,options->cName,files->Infile[iFile].cIn,lTmp[0],control->Io.iVerbose);
    if (iNumIndices == 0) {
      if (control->Io.iVerbose >= VERBERR)
        fprintf(stderr,"ERROR: No modules input to option %s.\n",options->cName);
      LineExit(files->Infile[iFile].cIn,lTmp[0]);
    }

    /* The iBitSum field is to check that every output parameter is part
       of the input modules. The variables EQTIDE, RADHEAT, etc. are set
       in vpanet.h. Each module-specific parameter is given the appropriate
       bit in InitializeOutput. In ReadOutputOrder the field 
       output->iModuleBit is compared bitwise to module->iBitSum. 
       Parameters that can be specified for multiple modules are set to 1. 
    */

    // Allow parameters that require no module
    module->iBitSum[iFile-1] = 1;

    for (iModule=0;iModule<iNumIndices;iModule++) {

      /************************
       * ADD NEW MODULES HERE *
       ************************/

      if (memcmp(sLower(saTmp[iModule]),"eqtide",6) == 0) {
        body[iFile-1].bEqtide = 1;
	module->iBitSum[iFile-1] += EQTIDE;
      } else if (memcmp(sLower(saTmp[iModule]),"radheat",7) == 0) {
        body[iFile-1].bRadheat = 1;
	module->iBitSum[iFile-1] += RADHEAT;
      } else if (memcmp(sLower(saTmp[iModule]),"distorb",8) == 0) {
        body[iFile-1].bDistOrb = 1;
	module->iBitSum[iFile-1] += DISTORB;
      } else if (memcmp(sLower(saTmp[iModule]),"distrot",6) == 0) {
        body[iFile-1].bDistRot = 1;
	module->iBitSum[iFile-1] += DISTROT;
      } else if (memcmp(sLower(saTmp[iModule]),"thermint",8) == 0) {
	body[iFile-1].bThermint = 1;
	module->iBitSum[iFile-1] += THERMINT;
      } else if (memcmp(sLower(saTmp[iModule]),"atmesc",6) == 0) {
        body[iFile-1].bAtmEsc = 1;
	module->iBitSum[iFile-1] += ATMESC;
      } else if (memcmp(sLower(saTmp[iModule]),"stellar",7) == 0) {
	body[iFile-1].bStellar = 1;
	module->iBitSum[iFile-1] += STELLAR;
      } else if (memcmp(sLower(saTmp[iModule]),"poise",5) == 0) {
	body[iFile-1].bPoise = 1;
	module->iBitSum[iFile-1] += POISE;
      } else if (memcmp(sLower(saTmp[iModule]),"binary",6) == 0) {
        body[iFile-1].bBinary = 1;
	module->iBitSum[iFile-1] += BINARY;
      } else if (memcmp(sLower(saTmp[iModule]),"flare",5) == 0) {
	body[iFile-1].bFlare = 1;
	module->iBitSum[iFile-1] += FLARE;
	    } else if (memcmp(sLower(saTmp[iModule]),"galhabit",5) == 0) {
	body[iFile-1].bGalHabit = 1;
	module->iBitSum[iFile-1] += GALHABIT;
      } else {
        if (control->Io.iVerbose >= VERBERR)
          fprintf(stderr,"ERROR: Unknown Module %s provided to %s.\n",saTmp[iModule],options->cName);
        LineExit(files->Infile[iFile].cIn,lTmp[0]);
      }
    }
    UpdateFoundOptionMulti(&files->Infile[iFile],options,lTmp,iNumLines,iFile);
  
    } else {
    if (control->Io.iVerbose >= VERBERR && iFile > 0) 
      fprintf(stderr,"WARNING: %s not present in file %s. No evolution will occur for this body.\n",options->cName,files->Infile[iFile].cIn);
  }
  free(lTmp);
}

void PrintModuleList(FILE *file,int iBitSum) {

  if (iBitSum & ATMESC)
    fprintf(file,"ATMESC ");
  if (iBitSum & BINARY)
    fprintf(file,"BINARY ");
  if (iBitSum & DISTORB)
    fprintf(file,"DISTORB ");
  if (iBitSum & DISTROT)
    fprintf(file,"DISTROT ");
  if (iBitSum & EQTIDE) 
    fprintf(file,"EQTIDE ");
  if (iBitSum & FLARE)
    fprintf(file,"FLARE ");
  if (iBitSum & GALHABIT)
    fprintf(file,"GALHABIT ");
  if (iBitSum & POISE)
    fprintf(file,"POISE ");
  if (iBitSum & RADHEAT)
    fprintf(file,"RADHEAT ");
  if (iBitSum & STELLAR)
    fprintf(file,"STELLAR ");
  if (iBitSum & THERMINT)
    fprintf(file,"THERMINT ");
    
}

void InitializeBodyModules(BODY **body,int iNumBodies) {
  int iBody;

  for (iBody=0;iBody<iNumBodies;iBody++) {
      (*body)[iBody].bAtmEsc = 0;
      (*body)[iBody].bBinary = 0;
      (*body)[iBody].bDistOrb = 0;
      (*body)[iBody].bDistRot = 0;
      (*body)[iBody].bEqtide = 0;
      (*body)[iBody].bFlare = 0;
      (*body)[iBody].bGalHabit = 0;
      (*body)[iBody].bPoise = 0;
      (*body)[iBody].bRadheat = 0;
      (*body)[iBody].bStellar = 0;
      (*body)[iBody].bThermint = 0;
  }
}

/*
 * Verify multi-module dependencies
 */

void VerifyModuleMultiDistOrbDistRot(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {

  if (body[iBody].bDistRot) {
    if (!body[iBody].bDistOrb) {
      fprintf(stderr,"ERROR: Module DISTROT selected for %s, but DISTORB not selected.\n",body[iBody].cName);
      exit(EXIT_INPUT);
    }
  }
}

void VerifyModuleMultiRadheatThermint(BODY *body,CONTROL *control,FILES *files,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {

  /* This will need modification if material can move between layers */

  if (body[iBody].bThermint) {
    if (!body[iBody].bRadheat) {
      if (control->Io.iVerbose > VERBINPUT)
        fprintf(stderr,"WARNING: Module THERMINT selected for %s, but RADHEAT not selected.\n",body[iBody].cName);
      body[iBody].dRadPowerCore = 0.;
      body[iBody].dRadPowerCrust = 0.;
      body[iBody].dRadPowerMan = 0.;
    } else
      control->fnPropsAuxMulti[iBody][(*iModuleProps)++] = &PropsAuxRadheatThermint;
  }
}

void VerifyModuleMultiEqtideThermint(BODY *body,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {
  int iEqtide;

  if (body[iBody].bEqtide) {
    if (!body[iBody].bThermint) {
      // Set Im(k_2) here
      body[iBody].dImK2=body[iBody].dK2/body[iBody].dTidalQ;
      // Now set the "Man" functions as the WriteTidalQ uses them
      // This ensures that the write function works
      body[iBody].dImk2Man = body[iBody].dImK2;
      body[iBody].dK2Man = body[iBody].dK2;
    } else { // Thermint and Eqtide called
      /* When Thermint and Eqtide are called together, care must be taken as 
         Im(k_2) must be known in order to calculate TidalZ. As the individual 
         module PropsAux are called prior to PropsAuxMulti, we must call the 
         "PropsAuxEqtide" function after Im(k_2) is called. Thus, we replace
         "PropsAuxEqtide" with PropsAuxNULL and call "PropsAuxEqtide" in
         PropsAuxEqtideThermint. */
      iEqtide = fiGetModuleIntEqtide(module,iBody);
      control->fnPropsAux[iBody][iEqtide] = &PropsAuxNULL;
      control->fnPropsAuxMulti[iBody][(*iModuleProps)++] = &PropsAuxEqtideThermint;
    }
  }
  
  /*
  else if (body[iBody].bThermint) { // eqtide not called, but thermint is
    //exit(1);
  
    printf("%d\n",iBody);
    fflush(stdout);
    body[iBody].dImk2Man = fdImk2Man(body,iBody);
  }
  */
}

void VerifyModuleMultiEqtideDistOrb(BODY *body,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {
  if (body[iBody].bEqtide) {
    if (body[iBody].bDistOrb) {
      control->fnForceBehaviorMulti[iBody][(*iModuleForce)++] = &ForceBehaviorEqtideDistOrb;
    }
  }
}

void VerifyModuleMultiFlareStellar(BODY *body,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce) {

  if (body[iBody].bFlare) {
    if (!body[iBody].bStellar) {
      fprintf(stderr,"ERROR: Must include module STELLAR ro run module FLARE.\n");
      LineExit(files->Infile[iBody+1].cIn,options[OPT_MODULES].iLine[iBody+1]);
    } else
      control->fnPropsAuxMulti[iBody][(*iModuleProps)++] = &PropsAuxFlareStellar;
  }
}

 void VerifyModuleMultiBinaryEqtide(BODY *body,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iBody,int *iModuleProps,int *iModuleForce)
{
  // If binary AND eqtide are called for a body, the body MUST be a star
  if(body[iBody].bBinary) {
    if(body[iBody].bEqtide) {
      if(body[iBody].iBodyType != 1) { // Body isn't a star!
        fprintf(stderr,"ERROR: If both binary AND eqtide are used for a body, the body MUST be a star.\n");
        fprintf(stderr,"Errant body iBody, bBinary, bEqtide: %d, %d, %d.\n",iBody,body[iBody].bBinary,body[iBody].bEqtide);
        LineExit(files->Infile[iBody+1].cIn,options[OPT_MODULES].iLine[iBody+1]);
      }
    }
  }

}

void VerifyModuleMulti(BODY *body,CONTROL *control,FILES *files,MODULE *module,OPTIONS *options,int iBody) {
  int iNumMultiProps=0,iNumMultiForce=0;

  if (module->iNumModules[iBody] > 1) {
    /* XXX Note that the number of elements here is really a permutation, 
       but this should work for a while. */
    control->fnPropsAuxMulti[iBody] = malloc(2*module->iNumModules[iBody]*sizeof(fnPropsAuxModule*));
    control->fnForceBehaviorMulti[iBody] = malloc(2*module->iNumModules[iBody]*sizeof(fnForceBehaviorModule*));
  }

  /* Now verify. Even if only module is called, we still need to call
     these functions as some default behavior is set if other modules aren't
     called. */
  VerifyModuleMultiDistOrbDistRot(body,control,files,options,iBody,&iNumMultiProps,&iNumMultiForce);
  
  VerifyModuleMultiRadheatThermint(body,control,files,options,iBody,&iNumMultiProps,&iNumMultiForce);
  
  VerifyModuleMultiEqtideDistOrb(body,control,files,module,options,iBody,&iNumMultiProps,&iNumMultiForce);

  VerifyModuleMultiEqtideThermint(body,control,files,module,options,iBody,&iNumMultiProps,&iNumMultiForce);
  
  VerifyModuleMultiFlareStellar(body,control,files,module,options,iBody,&iNumMultiProps,&iNumMultiForce);

  VerifyModuleMultiBinaryEqtide(body,control,files,module,options,iBody,&iNumMultiProps,&iNumMultiForce);

  control->iNumMultiProps[iBody] = iNumMultiProps;
  control->iNumMultiForce[iBody] = iNumMultiForce;
  if (control->Io.iVerbose >= VERBALL)
    fprintf(stdout,"All of %s's modules verified.\n",body[iBody].cName);
}

/*
 * Auxiliary Properties for multi-module calculations
 */

void PropsAuxEqtideThermint(BODY *body,EVOLVE *evolve,UPDATE *update,int iBody) {
  /* RB- These first 3 lines were taken from PropsAuxThermint, but 
   as they rely on eqtide being called, they belong here.*/
  body[iBody].dK2Man=fdK2Man(body,iBody);
  body[iBody].dImk2Man=fdImk2Man(body,iBody);

  // Maybe don't call? XXX
  //body[iBody].dTidalPowMan=fdTidalPowMan(body,iBody);


  body[iBody].dImK2 = fdImk2Man(body,iBody);
  PropsAuxCPL(body,evolve,update,iBody);
  // Call dTidePowerMan
  body[iBody].dTidalPowMan = fdCPLTidePower(body,iBody);
}

/* This does not seem to be necessary
void PropertiesDistOrbDistRot(BODY *body,UPDATE *update,int iBody) {
  body[iBody].dEccSq = body[iBody].dHecc*body[iBody].dHecc + body[iBody].dKecc*body[iBody].dKecc;
}
*/

void PropsAuxRadheatThermint(BODY *body,EVOLVE *evolve,UPDATE *update,int iBody) {
  body[iBody].dRadPowerCore = fdRadPowerCore(update,iBody);
  body[iBody].dRadPowerCrust = fdRadPowerCrust(update,iBody);
  body[iBody].dRadPowerMan = fdRadPowerMan(update,iBody);
}

void PropsAuxFlareStellar(BODY *body,EVOLVE *evolve,UPDATE *update,int iBody) {
  SYSTEM system; // dummy for LXUVStellar
  //body[iBody].dLXUV = fdLXUVStellar(body,&system,update,iBody,iBody) + body[iBody].dLXUVFlare;
}

/*
 * Force Behavior for multi-module calculations
 */

void ForceBehaviorEqtideDistOrb(BODY *body,EVOLVE *evolve,IO *io,SYSTEM *system,UPDATE *update,fnUpdateVariable ***fnUpdate,int iFoo,int iBar) {
  if (evolve->iDistOrbModel == RD4) {
    RecalcLaplace(body,evolve,system,io->iVerbose);
  } else if (evolve->iDistOrbModel == LL2) {
    RecalcEigenVals(body,evolve,system);
  }
} 
