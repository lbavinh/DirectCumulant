//----------------------------------------------------------------------------------------------------
// $Id: StRefMultCorr.cxx,v 1.1 2012/01/03 02:22:13 sss Exp $
// $Log: StRefMultCorr.cxx,v $
// Revision 1.1  2012/01/03 02:22:13  sss
// *** empty log message ***
//
// Revision 1.6  2011/11/08 19:11:05  hmasui
// Add luminosity corrections for 200 GeV
//
// Revision 1.5  2011/10/11 19:35:20  hmasui
// Fix typo. Add z-vertex check in getWeight() function
//
// Revision 1.4  2011/10/10 21:30:37  hmasui
// Replaced hard coded parameters for z-vertex and weight corrections by input parameters from text file
//
//
// Revision 1.3  2011/08/12 20:28:07  hmasui
// Avoid varying corrected refmult in the same event by random number
//
// Revision 1.2  2011/08/11 23:51:10  hmasui
// Suppress cout in the setParameterIndex function. Use TError for error messages.
//
// Revision 1.1  2011/08/11 18:38:28  hmasui
// First version of Refmult correction class
//
//----------------------------------------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <string>
#include "StRefMultCorr.h"
#include "TError.h"
#include "TRandom.h"
#include "TString.h"

ClassImp(StRefMultCorr)

using std::cout ;
using std::endl ;
using std::ifstream ;
using std::string ;
using std::vector ;

//____________________________________________________________________________________________________
// Default constructor
StRefMultCorr::StRefMultCorr()
{
  mRefMult = 0 ;
  mVz = -9999. ;
  mRefMult_corr = -1.0 ;

  // Clear all data members
  clear() ;

  // Read parameters
  read() ;
}

//____________________________________________________________________________________________________
// Default destructor
StRefMultCorr::~StRefMultCorr()
{
}

//____________________________________________________________________________________________________
void StRefMultCorr::clear()
{
  // Clear all arrays, and set parameter index = -1

  mStart_runId.clear() ;
  mStop_runId.clear() ;
  mStart_zvertex.clear() ;
  mStop_zvertex.clear() ;
  mNormalize_stop.clear() ;

  for(Int_t i=0;i<mNCentrality;i++) {
    mCentrality_bins[i].clear() ;
  }
  mParameterIndex = -1 ;

  for(Int_t i=0;i<mNPar_z_vertex;i++) {
      mPar_z_vertex[i].clear() ;
  }

  for(Int_t i=0;i<mNPar_weight;i++) {
      mPar_weight[i].clear();
  }

  for(Int_t i=0;i<mNPar_luminosity;i++) {
      mPar_luminosity[i].clear();
  }
}

//____________________________________________________________________________________________________
void StRefMultCorr::initEvent(const UShort_t RefMult, const Double_t z, const Double_t zdcCoincidenceRate)
{
  // Set refmult, vz and corrected refmult if current (refmult,vz) are different from inputs
  // User must call this function event-by-event before 
  // calling any other public functions
  if ( mRefMult != RefMult || mVz != z || mZdcCoincidenceRate != zdcCoincidenceRate ) {
    mRefMult            = RefMult ;
    mVz                 = z ;
    mZdcCoincidenceRate = zdcCoincidenceRate ;
    mRefMult_corr       = getRefMultCorr(mRefMult, mVz, mZdcCoincidenceRate) ;
  }
}

//____________________________________________________________________________________________________
Bool_t StRefMultCorr::isIndexOk() const
{
  // mParameterIndex not initialized (-1)
  if ( mParameterIndex == -1 ) {
    Error("StRefMultCorr::isNparSetOk", "mParameterIndex = -1. Call init(const Int_t RunId) function to initialize centrality bins, corrections");
    return kFALSE ;
  }

  // Out of bounds
  if ( mParameterIndex >= (Int_t)mStart_runId.size() ) {
    Error("StRefMultCorr::isNparSetOk",
        Form("mParameterIndex = %d > max number of parameter set = %d. Make sure you put correct index for this energy",
          mParameterIndex, mStart_runId.size()));
    return kFALSE ;
  }

  return kTRUE ;
}

//____________________________________________________________________________________________________
Bool_t StRefMultCorr::isZvertexOk() const
{
  // Primary z-vertex check
  return ( mVz > mStart_zvertex[mParameterIndex] && mVz < mStop_zvertex[mParameterIndex] ) ;
}

//____________________________________________________________________________________________________
Bool_t StRefMultCorr::isRefMultOk() const
{
  // Invalid index
  if ( !isIndexOk() ) return kFALSE ;

  // select 0-80%
  return (mRefMult_corr > mCentrality_bins[0][mParameterIndex] && mRefMult_corr < mCentrality_bins[mNCentrality][mParameterIndex]);
}

//____________________________________________________________________________________________________
Bool_t StRefMultCorr::isCentralityOk(const Int_t icent) const
{
  // Invalid centrality id
  if ( icent < -1 || icent >= mNCentrality+1 ) return kFALSE ;

  // Invalid index
  if ( !isIndexOk() ) return kFALSE ;

  // Special case
  // 1. 80-100% for icent=-1
  if ( icent == -1 ) return (mRefMult_corr <= mCentrality_bins[0][mParameterIndex]);

  // 2. icent = mNCentrality
  if ( icent == mNCentrality ) return (mRefMult_corr <= mCentrality_bins[mNCentrality][mParameterIndex]);

  const Bool_t ok = (mRefMult_corr > mCentrality_bins[icent][mParameterIndex] && mRefMult_corr <= mCentrality_bins[icent+1][mParameterIndex]);
//  if(ok){
//    cout << "StRefMultCorr::isCentralityOk  refmultcorr = " << mRefMult_corr
//      << "  min. bin = " << mCentrality_bins[icent][mParameterIndex]
//      << "  max. bin = " << mCentrality_bins[icent+1][mParameterIndex]
//      << endl;
//  }
  return ok ;
}

//____________________________________________________________________________________________________
void StRefMultCorr::init(const Int_t RunId)
{
  // Initialization

  // call setParameterIndex
  setParameterIndex(RunId) ;
}

//____________________________________________________________________________________________________
Int_t StRefMultCorr::setParameterIndex(const Int_t RunId)
{
  // Determine the corresponding parameter set for the input RunId
  for(UInt_t npar = 0; npar < mStart_runId.size(); npar++)
  {
    if(RunId >= mStart_runId[npar] && RunId <= mStop_runId[npar])
    {
      mParameterIndex = npar ;
//      cout << "StRefMultCorr::setParameterIndex  Parameter set = " << mParameterIndex << " for RUN " << RunId << endl;
      break ;
    }
  }

  if(mParameterIndex == -1){
    Error("StRefMultCorr::setParameterIndex", "Parameter set does not exist for RUN %d", RunId);
  }
  //else cout << "Parameter set = " << npar_set << endl;

  return mParameterIndex ;
}


//____________________________________________________________________________________________________
Double_t StRefMultCorr::getRefMultCorr() const
{
  // Call initEvent() first
  return mRefMult_corr ;
}

//____________________________________________________________________________________________________
Double_t StRefMultCorr::getRefMultCorr(const UShort_t RefMult, const Double_t z,
    const Double_t zdcCoincidenceRate) const
{
  // Apply correction if parameter index & z-vertex are ok
  if (!isIndexOk() || !isZvertexOk()) return RefMult ;

  // Correction function for RefMult, takes into account z_vertex dependence

  // Luminosity corrections
  // 200 GeV only. correction = 1 for all the other energies
  const Double_t par0l = mPar_luminosity[0][mParameterIndex] ;
  const Double_t par1l = mPar_luminosity[1][mParameterIndex] ;
  const Double_t correction_luminosity = (par0l==0.0) ? 1.0 : 1.0/(1.0 + par1l/par0l*zdcCoincidenceRate/1000.);

  // par0 to par5 define the parameters of a polynomial to parametrize z_vertex dependence of RefMult
  const Double_t par0 = mPar_z_vertex[0][mParameterIndex];
  const Double_t par1 = mPar_z_vertex[1][mParameterIndex];
  const Double_t par2 = mPar_z_vertex[2][mParameterIndex];
  const Double_t par3 = mPar_z_vertex[3][mParameterIndex];
  const Double_t par4 = mPar_z_vertex[4][mParameterIndex];
  const Double_t par5 = mPar_z_vertex[5][mParameterIndex];
  const Double_t par6 = mPar_z_vertex[6][mParameterIndex];
  const Double_t par7 = mPar_z_vertex[7][mParameterIndex]; // this parameter is usually 0, it takes care for an additional efficiency, usually difference between phase A and phase B parameter 0

  const Double_t  RefMult_ref = par0; // Reference mean RefMult at z=0
  const Double_t  RefMult_z = par0 + par1*z + par2*z*z + par3*z*z*z + par4*z*z*z*z + par5*z*z*z*z*z + par6*z*z*z*z*z*z; // Parametrization of mean RefMult vs. z_vertex position
  Double_t  Hovno = 1.0; // Correction factor for RefMult, takes into account z_vertex dependence

  if(RefMult_z > 0.0)
  {
    Hovno = (RefMult_ref + par7)/RefMult_z;
  }

  Double_t RefMult_d = (Double_t)(RefMult)+gRandom->Rndm(); // random sampling over bin width -> avoid peak structures in corrected distribution
  const Double_t RefMult_corr  = RefMult_d*Hovno*correction_luminosity;
//  cout << "Input RefMult = " << RefMult << ", input z = " << z << ", RefMult_corr = " << RefMult_corr << endl;
  return RefMult_corr ;
}
/*
//____________________________________________________________________________________________________
Double_t StRefMultCorr::getRefMultCorr(const UShort_t RefMult, const Double_t z) const
{
  // Apply correction if parameter index & z-vertex are ok
  if (!isIndexOk() || !isZvertexOk(z)) return RefMult ;

  // Correction function for RefMult, takes into account z_vertex dependence

// par0 to par5 define the parameters of a polynomial to parametrize z_vertex dependence of RefMult
  const Double_t par0 = 1.14384e+02;
  const Double_t par1 = 9.65079e-02;
  const Double_t par2 = 2.00631e-03;
  const Double_t par3 = 5.92159e-05;
  const Double_t par4 = -5.53470e-07;
  const Double_t par5 = -7.02779e-08;

  const Double_t  RefMult_ref = par0; // Reference mean RefMult at z=0
  const Double_t  RefMult_z = par0 + par1*z + par2*z*z + par3*z*z*z + par4*z*z*z*z + par5*z*z*z*z*z; // Parametrization of mean RefMult vs. z_vertex position
  Double_t  Hovno = 1.0; // Correction factor for RefMult, takes into account z_vertex dependence

  if(RefMult_z > 0.0)
  {
    Hovno = RefMult_ref/RefMult_z;
  }

  Double_t RefMult_d = (Double_t)(RefMult)+ran.Rndm()-0.5; // random sampling over bin width -> avoid peak structures in corrected distribution
  const Double_t RefMult_corr  = RefMult_d*Hovno;
//  cout << "Input RefMult = " << RefMult << ", input z = " << z << ", RefMult_corr = " << RefMult_corr << endl;
  return RefMult_corr ;
}
*/
//____________________________________________________________________________________________________
Double_t StRefMultCorr::getWeight() const
{
  Double_t Weight = 1.0;

  // Invalid index
  if( !isIndexOk() ) return Weight ;

  // Invalid z-vertex
  if( !isZvertexOk() ) return Weight ;

  const Double_t par0 =   mPar_weight[0][mParameterIndex];
  const Double_t par1 =   mPar_weight[1][mParameterIndex];
  const Double_t par2 =   mPar_weight[2][mParameterIndex];
  const Double_t par3 =   mPar_weight[3][mParameterIndex];
  const Double_t par4 =   mPar_weight[4][mParameterIndex];
  const Double_t A    =   mPar_weight[5][mParameterIndex];

  // Additional z-vetex dependent correction
  //const Double_t A = ((1.27/1.21))/(30.0*30.0); // Don't ask...
  //const Double_t A = (0.05/0.21)/(30.0*30.0); // Don't ask...

  if(isRefMultOk() // 0-80%
      && mRefMult_corr < mNormalize_stop[mParameterIndex] // re-weighting only apply up to normalization point
      && mRefMult_corr != -(par3/par2) // avoid denominator = 0
    )
  {
    Weight = par0 + par1/(par2*mRefMult_corr + par3) + par4*(par2*mRefMult_corr + par3); // Parametrization of MC/data RefMult ratio
    Weight = Weight + (Weight-1.0)*(A*mVz*mVz); // z-dependent weight correction
  }

  return Weight;
}

//____________________________________________________________________________________________________
Int_t StRefMultCorr::getCentralityBin16() const
{
  Int_t CentBin16 = -1;

  // Invalid index
  if( !isIndexOk() ) return CentBin16 ;

  while(CentBin16 < mNCentrality && !isCentralityOk(CentBin16) )
  {
    CentBin16++;
  }

  // return -1 if CentBin16 = 16 (very large refmult, refmult>5000)
  return (CentBin16==16) ? -1 : CentBin16;
}

//____________________________________________________________________________________________________
Int_t StRefMultCorr::getCentralityBin9() const
{
  Int_t CentBin9 = -1;

  // Invalid index
  if ( !isIndexOk() ) return CentBin9 ;

  const Int_t CentBin16 = getCentralityBin16(); // Centrality bin 16
  const Bool_t isCentralityOk = CentBin16 >= 0 && CentBin16 < mNCentrality ;

  // No centrality is defined
  if (!isCentralityOk) return CentBin9 ;

  // First handle the exceptions
  if(mRefMult_corr > mCentrality_bins[15][mParameterIndex] && mRefMult_corr <= mCentrality_bins[16][mParameterIndex])
  {
    CentBin9 = 8; // most central 5%
  }
  else if(mRefMult_corr > mCentrality_bins[14][mParameterIndex] && mRefMult_corr <= mCentrality_bins[15][mParameterIndex])
  {
    CentBin9 = 7; // most central 5-10%
  }
  else
  {
    CentBin9 = (Int_t)(0.5*CentBin16);
  }

  return CentBin9;
}

//____________________________________________________________________________________________________
void StRefMultCorr::read()
{
  // Open the parameter file and read the data
  // Assume input file "Centrality_def.txt" is placed under StRoot/StRefMultCorr
  //  const Char_t* inputFileName("/star/u/aschmah/glauber/RefMult_corr/StRoot/StRefMultCorr/Centrality_def.txt");
//  const Char_t* inputFileName("/u/aschmah/STAR/glauber/RefMultCorr/StRoot/StRefMultCorr/Centrality_def.txt");
  const Char_t* inputFileName("StRoot/StRefMultCorr/Centrality_def.txt");
  ifstream ParamFile(inputFileName);
  if(!ParamFile){
    cout << "StRefMultCorr::read  cannot open " << inputFileName << endl;
    return;
  }
  cout << "StRefMultCorr::read  Open " << inputFileName << endl;

//  Int_t input_counter = 0;
  string line ;
  getline(ParamFile,line);
//  cout << line << endl;

//  if(strcmp(line1,"Start_runId") == 0) // strcmp returns 0 if both string are identical
  if(line.find("Start_runId")!=string::npos)
  {
    //cout << "Initial line" << endl;
    while(ParamFile.good())
    {
      Int_t startRunId, stopRunId ;
      Double_t startZvertex, stopZvertex ;
      ParamFile >> startRunId >> stopRunId >> startZvertex >> stopZvertex ;
      mStart_runId.push_back( startRunId ) ;
      mStop_runId.push_back( stopRunId ) ;
      mStart_zvertex.push_back( startZvertex ) ;
      mStop_zvertex.push_back( stopZvertex ) ;
      for(Int_t i=0;i<mNCentrality;i++) {
        Int_t centralitybins;
        ParamFile >> centralitybins;
        mCentrality_bins[i].push_back( centralitybins );
      }
      Double_t normalize_stop ;
      ParamFile >> normalize_stop ;
      mNormalize_stop.push_back( normalize_stop );

      for(Int_t i=0;i<mNPar_z_vertex;i++) {
          Double_t param;
          ParamFile >> param;
          mPar_z_vertex[i].push_back( param );
      }

      for(Int_t i=0;i<mNPar_weight;i++) {
          Double_t param;
          ParamFile >> param;
          mPar_weight[i].push_back( param );
      }

      for(Int_t i=0;i<mNPar_luminosity;i++) {
          Double_t param;
          ParamFile >> param;
          mPar_luminosity[i].push_back( param );
      }
      mCentrality_bins[mNCentrality].push_back( 5000 );
      //cout << "Data line = " << input_counter << ", Start_runId = " << Start_runId[input_counter] << ", Stop_runId = " << Stop_runId[input_counter] << endl;
      const UInt_t id = mStart_runId.size()-1;
      cout << "StRefMultCorr::read  Index = " << id << endl;
      cout << "StRefMultCorr::read  Start_runId = " << mStart_runId[id] << ", Stop_runId = " << mStop_runId[id] << endl;
      cout << "StRefMultCorr::read  Start_zvertex = " << mStart_zvertex[id] << ", Stop_zvertex = " << mStop_zvertex[id] << endl;
      cout << "StRefMultCorr::read  Normalize_stop = " << mNormalize_stop[id] << endl;
      for(Int_t i=0;i<mNCentrality;i++){
        cout << Form("StRefMultCorr::read  Centrality %3d-%3d %%, refmult > %4d", 75-5*i, 80-5*i, mCentrality_bins[i][id]) << endl;
      }

      for(Int_t i=0;i<mNPar_z_vertex;i++) {
          cout << "mPar_z_vertex[" << i << "] = " << mPar_z_vertex[i][id] <<  endl;
      }
      for(Int_t i=0;i<mNPar_weight;i++) {
          cout << "mPar_weight[" << i << "] = " << mPar_weight[i][id] << endl;
      }
      for(Int_t i=0;i<mNPar_luminosity;i++) {
          cout << "mPar_luminosity[" << i << "] = " << mPar_luminosity[i][id] << endl;
      }
      cout << endl;
    }
  }
  else
  {
    cout << "StRefMultCorr::read  Input file is not correct! Wrong structure." << endl;
    return;
  }
  ParamFile.close();
}

