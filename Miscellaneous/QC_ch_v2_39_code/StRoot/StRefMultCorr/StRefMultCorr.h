//----------------------------------------------------------------------------------------------------
// $Id: StRefMultCorr.h,v 1.1 2012/01/03 02:22:14 sss Exp $
// $Log: StRefMultCorr.h,v $
// Revision 1.1  2012/01/03 02:22:14  sss
// *** empty log message ***
//
// Revision 1.5  2011/11/08 19:11:03  hmasui
// Add luminosity corrections for 200 GeV
//
// Revision 1.4  2011/10/11 19:35:18  hmasui
// Fix typo. Add z-vertex check in getWeight() function
//
// Revision 1.3  2011/10/10 21:30:34  hmasui
// Replaced hard coded parameters for z-vertex and weight corrections by input parameters from text file
//
// Revision 1.2  2011/08/12 20:28:04  hmasui
// Avoid varying corrected refmult in the same event by random number
//
// Revision 1.1  2011/08/11 18:38:36  hmasui
// First version of Refmult correction class
//
//----------------------------------------------------------------------------------------------------
//  StRefMultCorr class
//   - Provide centrality bins based on reference multiplicity (refmult) measured in the TPC
//     * 5% increment centrality bins (16 bins)
//     * 5% increment in 0-10%, and 10% increment in 10-80% (9 bins)
//   - Provide corrected refmult (z-vertex dependence)
//   - Provide "re-weighting" correction, only relevant to the peripheral bins
//
//  Centrality binning:
//     Bin       Centrality (16)   Centrality (9)
//     0            75-80%            70-80%
//     1            70-75%            60-70%
//     2            65-70%            50-60%
//     3            60-65%            40-50%
//     4            55-60%            30-40%
//     5            50-55%            20-30%
//     6            45-50%            10-20%
//     7            40-45%             5-10%
//     8            35-40%             0- 5%
//     9            30-35%
//    10            25-30%
//    11            20-25%
//    12            15-20%
//    13            10-15%
//    14             5-10%
//    15             0- 5%
//
//  See how to use this class in StRefMultCorr/macros/getCentralityBins.C
//
//  authors: Alexander Schmah, Hiroshi Masui
//----------------------------------------------------------------------------------------------------

#ifndef __StRefMultCorr_h__
#define __StRefMultCorr_h__

#include <vector>
#include "Rtypes.h"

//____________________________________________________________________________________________________
// Class to correct z-vertex dependence of refmult
class StRefMultCorr {
  public:
    StRefMultCorr();
    virtual ~StRefMultCorr(); /// Default destructor

    // Event-by-event initialization. Call this function event-by-event
    //   * Default ZDC coincidence rate = 0 to make the function backward compatible 
    //   --> i.e. no correction will be applied unless users set the values for 200 GeV
    void initEvent(const UShort_t RefMult, const Double_t z,
        const Double_t zdcCoincidenceRate=0.0) ; // Set refmult, vz and zdc coincidence rate

    /// Get corrected refmult, correction as a function of primary z-vertex
    Double_t getRefMultCorr() const;

    /// Get 16 centrality bins (5% increment, 0-5, 5-10, ..., 75-80)
    Int_t getCentralityBin16() const;

    /// Get 9 centrality bins (10% increment except for 0-5 and 5-10)
    Int_t getCentralityBin9() const;

    /// Re-weighting correction, correction is only applied up to mNormalize_step (energy dependent)
    Double_t getWeight() const;

    // Initialization of centrality bins etc
    void init(const Int_t RunId);

private:
    // Functions
    void read() ; /// Read input parameters from text file StRoot/StRefMultCorr/Centrality_def.txt
    void clear() ; /// Clear all arrays
    Bool_t isIndexOk() const ; /// 0 <= mParameterIndex < maxArraySize
    Bool_t isZvertexOk() const ; /// mStart_zvertex < z < mStop_zvertex
    Bool_t isRefMultOk() const ; /// 0-80%, (corrected refmult) > mCentrality_bins[0]
    Bool_t isCentralityOk(const Int_t icent) const ; /// centrality bin check
    Int_t setParameterIndex(const Int_t RunId) ; /// Parameter index from run id (return mParameterIndex)

    // Corrected refmult
    Double_t getRefMultCorr(const UShort_t RefMult, const Double_t z, const Double_t zdcCoincidenceRate) const ;


    // Data members
    enum {
        mNCentrality   = 16, /// 16 centrality bins, starting from 75-80% with 5% bin width
        mNPar_z_vertex = 8,
        mNPar_weight   = 6,
        mNPar_luminosity = 2
    };

    // Use these variables to avoid varying the corrected refmult
    // in the same event by random numbers
    UShort_t mRefMult ;     /// Current reference multiplicity
    Double_t mVz ;          /// Current primary z-vertex
    Double_t mZdcCoincidenceRate ; /// Current ZDC coincidence rate
    Double_t mRefMult_corr; /// Corrected refmult

    std::vector<Int_t> mStart_runId       ; /// Start run id
    std::vector<Int_t> mStop_runId        ; /// Stop run id
    std::vector<Double_t> mStart_zvertex  ; /// Start z-vertex (cm)
    std::vector<Double_t> mStop_zvertex   ; /// Stop z-vertex (cm)
    std::vector<Double_t> mNormalize_stop ; /// Normalization between MC and data (normalized in refmult>mNormalize_stop)
    std::vector<Int_t> mCentrality_bins[mNCentrality+1] ; /// Centrality bins (last value is set to 5000)
    std::vector<Double_t> mPar_z_vertex[mNPar_z_vertex] ; /// parameters for z-vertex correction
    std::vector<Double_t> mPar_weight[mNPar_weight] ; /// parameters for weight correction
    std::vector<Double_t> mPar_luminosity[mNPar_luminosity] ; /// parameters for luminosity correction (valid only for 200 GeV)
    Int_t mParameterIndex; /// Index of correction parameters

    ClassDef(StRefMultCorr, 0)
};
#endif

