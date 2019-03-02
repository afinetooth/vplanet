/***************** MAGMOC.H ***********************
 *
 * Patrick Barth, THursday May 17 14:41 PDT 2018
 *
 * This header file contains all the subroutines in
 * file magmoc.c.
 *
*/


/* Parameter */
// mantle parameters
#define SILICATEHEATCAP           1.2e3  //silicate heat capacity (J/kg/K)
#define HEATFUSIONSILICATE        4e5    //heat of fusion of soliciates (J/kg)
#define THERMALCONDUC             4.2    //thermal conductivity mantle (W/m/K)
#define THERMALDIFFUS             1e-6   //thermal diffusivity mantle (m^2/s)
#define CRITRAYLEIGHNO            1.1e3  //critical Rayleigh number
#define THERMALEXPANCOEFF         2e-5   //thermal expansion coefficient (1/K)
#define ALBEDOWATERATMOS          0.75   //albedo 100% water atmosphere
#define ALBEDOROCK                0.3    //albedo bare rock
#define WATERPARTCOEFF            0.01   //partition coeff. water between melt & solid
#define CRITMELTFRAC              0.4    //critical melt fraction
#define DYNVISCLIQUID             0.01   //dynamic viscosity of liquid melt
#define DYNVISCSOLID              3.8e9  //dynamic viscosity of solid
#define ACTIVENERGY               3.5e5  //activation energy viscosity
#define RADCOREEARTH              3.4e6  //core radius Earth (m)

// molar masses of volatiles
#define MOLWEIGHTWATER            18.01528e-3 //molar weight water
#define MOLWEIGHTHYDROGEN         1.00794e-3  //molar weight hydrogen
#define MOLWEIGHTOXYGEN           15.999e-3   //molar weight oxygen
#define MOLWEIGHTFEO15            79.844e-3   //molar weight FeO_1.5
#define MOLWEIGHTFEO              71.844e-3   //molar weight FeO

// prefactors for linear solidus (Hirschmann 2000)
#define ALOWPRESSURE              1.0442e-7 //low pressure (K/Pa)
#define BLOWPRESSURE              1420      // (K)
#define AHIGHPRESSURE             0.2653E-7 //high pressure (K/Pa)
#define BHIGHPRESSURE             1825      // (K)

// mantle composition (mole fractions)
#define MOLFRACAL2O3              2.433e-2
#define MOLFRACFEO                5.791e-2
#define MOLFRACCAO                3.506e-2
#define MOLFRACNA2O               2.937e-3
#define MOLFRACK2O                2.209e-4
#define AVEMOLMASS                52.833 // average molar mass of mantle
#define TOTMASSFRACFEO            0.0788 // total mass fraction of FeO in mantle

// OLR Elkins-Tanton 2008
#define ABSORPCOEFFH2O            0.01 // absorp. coeff. of water at ref. press.
#define REFPRESSUREOPACITY        101325 // reference pressure (Pa)
#define WATERHEATCAP              3.2e3 //water heat capacity (J/kg/K)

// Atmospheric escape (double to ATMESC)
#define ATMESCTHERMT              500 //average atmospheric temp. (K)
#define ATMESCBDIFF               4.8e19 * pow(THERMT, 0.75) // Binary diffusion coefficient of H through O (/m/s)
#define ATMESCQOH                 16. // Atomic mass ratio oxygen/hydrogen

/* Options Info */

#define OPTSTARTMAGMOC            2300 /* Start of Magmoc options */
#define OPTENDMAGMOC              2400 /* End of Magmoc options */

#define OPT_FEO                   2310
#define OPT_WATERMASSATM          2311
#define OPT_SURFTEMP              2312
#define OPT_MANMELTDENSITY        2313
#define OPT_HALTMANTLESOLIDIFIED  2314

void AddModuleMagmOc(MODULE*,int,int);
void BodyCopyMagmOc(BODY*,BODY*,int,int,int);

/* Options Functions */
void HelpOptionsMagmOc(OPTIONS*);
void InitializeOptionsMagmOc(OPTIONS*,fnReadOption[]);
void ReadFeO(BODY*,CONTROL*,FILES*,OPTIONS*,SYSTEM*,int) ;
void ReadWaterMassAtm(BODY*,CONTROL*,FILES*,OPTIONS*,SYSTEM*,int);
void ReadSurfTemp(BODY*,CONTROL*,FILES*,OPTIONS*,SYSTEM*,int);
void ReadManMeltDensity(BODY*,CONTROL*,FILES*,OPTIONS*,SYSTEM*,int);
void ReadOptionsMagmOc(BODY*,CONTROL*,FILES*,OPTIONS*,SYSTEM*,fnReadOption[],int);

/* Halt Functions */
#define MAGMOCHALTSYSEND       5
#define MAGMOCHALTBODYEND      5

int fbHaltMantleSolidifed(BODY*,EVOLVE*,HALT*,IO*,UPDATE*,int);
void CountHaltsMagmOc(HALT*,int*);

/* Verify Functions */
void VerifyMagmOc(BODY*,CONTROL*,FILES*,OPTIONS*,OUTPUT*,SYSTEM*,UPDATE*,int,int);
void VerifyRotationMagmOc(BODY*,CONTROL*,OPTIONS*,char[],int);
void InitializeVplanetMagmOc(CONTROL*,MODULE*);
void PropsAuxMagmOc(BODY*,EVOLVE*,UPDATE*,int);
void VerifyHaltMagmOc(BODY*,CONTROL*,OPTIONS*,int,int*);
void VerifyRotationMagmOc(BODY*,CONTROL*,OPTIONS*,char[],int);

/* Update functions */
void InitializeUpdateMagmOc(BODY*,UPDATE*,int);
void FinalizeUpdatePotTemp(BODY*,UPDATE*,int*,int,int,int);
void FinalizeUpdateSurfTemp(BODY*,UPDATE*,int*,int,int,int);
void FinalizeUpdateSolidRadius(BODY*,UPDATE*,int*,int,int,int);
void FinalizeUpdateWaterMassMOAtm(BODY*,UPDATE*,int*,int,int,int);
void FinalizeUpdateWaterMassSol(BODY*,UPDATE*,int*,int,int,int);
void FinalizeUpdateOxygenMassMOAtm(BODY*,UPDATE*,int*,int,int,int);
void FinalizeUpdateOxygenMassSol(BODY*,UPDATE*,int*,int,int,int);
/* Output Functions */

/* MagmOc 1100 - 1199 */
#define OUTSTARTMAGMOC         2300
#define OUTENDMAGMOC           2400

#define OUT_FE2O3              2310
#define OUT_WATERMASSMOATM     2311
#define OUT_POTTEMP            2312
#define OUT_SURFTEMP           2313
#define OUT_WATERMASSSOL       2314
#define OUT_SOLIDRADIUS        2315
#define OUT_OXYGENMASSMOATM    2316
#define OUT_OXYGENMASSSOL      2317
#define OUT_PRESSWATERATM      2318
#define OUT_PRESSOXYGENATM     2319
#define OUT_NUMHYDROSPACE      2320
#define OUT_NUMOXYSPACE        2321
#define OUT_NUMHYDROMO         2322
#define OUT_FRACFE2O3MAN       2323

void HelpOutputMagmOc(OUTPUT*);
void InitializeOutputMagmOc(OUTPUT*,fnWriteOutput[]);
void InitializeOutputFunctionMagmOc(OUTPUT*,int,int);
void FinalizeOutputFunctionMagmOc(OUTPUT*,int,int);

void WritePotTemp(BODY*,CONTROL*,OUTPUT*,SYSTEM*,UNITS*,UPDATE*,int,double*,char[]);
void WriteSurfTemp(BODY*,CONTROL*,OUTPUT*,SYSTEM*,UNITS*,UPDATE*,int,double*,char[]);
void WriteSolidRadius(BODY*,CONTROL*,OUTPUT*,SYSTEM*,UNITS*,UPDATE*,int,double*,char[]);
void WriteWaterMassMOAtm(BODY*,CONTROL*,OUTPUT*,SYSTEM*,UNITS*,UPDATE*,int,double*,char[]);
void WriteWaterMassSol(BODY*,CONTROL*,OUTPUT*,SYSTEM*,UNITS*,UPDATE*,int,double*,char[]);
void WriteOxygenMassMOAtm(BODY*,CONTROL*,OUTPUT*,SYSTEM*,UNITS*,UPDATE*,int,double*,char[]);
void WriteOxygenMassSol(BODY*,CONTROL*,OUTPUT*,SYSTEM*,UNITS*,UPDATE*,int,double*,char[]);
void WritePressWaterAtm(BODY*,CONTROL*,OUTPUT*,SYSTEM*,UNITS*,UPDATE*,int,double*,char[]);
void WritePressOxygenAtm(BODY*,CONTROL*,OUTPUT*,SYSTEM*,UNITS*,UPDATE*,int,double*,char[]);
void WriteNumHydroSpace(BODY*,CONTROL*,OUTPUT*,SYSTEM*,UNITS*,UPDATE*,int,double*,char[]);
void WriteNumOxySpace(BODY*,CONTROL*,OUTPUT*,SYSTEM*,UNITS*,UPDATE*,int,double*,char[]);
void WriteNumHydroMO(BODY*,CONTROL*,OUTPUT*,SYSTEM*,UNITS*,UPDATE*,int,double*,char[]);
void WriteFracFe2O3Man(BODY*,CONTROL*,OUTPUT*,SYSTEM*,UNITS*,UPDATE*,int,double*,char[]);

/* Logging Functions */
void LogOptionsMagmOc(CONTROL*,FILE*);
void LogMagmOc(BODY*,CONTROL*,OUTPUT*,SYSTEM*,UPDATE*,fnWriteOutput[],FILE*);
void LogBodyMagmOc(BODY*,CONTROL*,OUTPUT*,SYSTEM*,UPDATE*,fnWriteOutput[],FILE*,int);

/* MagmOc functions */
void fnForceBehaviorMagmOc(BODY*,MODULE*,EVOLVE*,IO*,SYSTEM*,UPDATE*,fnUpdateVariable ***fnUpdate,int,int);
double fdDPotTemp(BODY*, SYSTEM*, int*);
double fdDSurfTemp(BODY*, SYSTEM*, int*);
double fdDSolidRadius(BODY*, SYSTEM*, int*);
double fdDWaterMassSol(BODY*, SYSTEM*, int*);
double fdDWaterMassMOAtm(BODY*, SYSTEM*, int*);
double fdDOxygenMassSol(BODY*, SYSTEM*, int*);
double fdDOxygenMassMOAtm(BODY*, SYSTEM*, int*);
