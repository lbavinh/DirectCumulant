void makeFlow(Char_t* inFileName  = "test.hist.root") {
    //Load all the System libraries
    gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
    loadSharedLibraries();
    gSystem->Load("StPicoDstMaker");
    gSystem->Load("StMyDCumulantsMaker");

    const Int_t nCentBins  = 9; // 9 centrality bins in total
    const Int_t centLow    = 0;
    const Int_t centUp     = 8;
    const Int_t nChAsymBins = 4;
    
    TFile* inFile = new TFile(inFileName);
    if (NULL == inFile) {
        cerr << "Error: Can not open file: " << inFileName << endl;
    }

    TString outFileName(inFileName);
    outFileName.ReplaceAll(".hist.root", ".flow.root");
    TFile* outFile = new TFile(outFileName.Data(), "RECREATE");
    if (NULL==outFile) {
        cerr << "Error: Can not create file: " << outFileName << endl;
    }

    for (Int_t i = centLow; i <= centUp; ++i) {
        DCCorrelatioinSet correlations;
        TString pfix("_cent"); pfix += i; 
        cout << pfix << endl;
        correlations.ReadHistograms(inFile, pfix);
        correlations.CalculateDiffFlow(outFile);
    }
    
    outFile->Close();
    inFile->Close();
    return;
}


// void makeFlow(Char_t* inFileName  = "test.hist.root") {
//     //Load all the System libraries
//     gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
//     loadSharedLibraries();

//     gSystem->Load("StPicoDstMaker");
//     gSystem->Load("StMyDCumulantsMaker");

//     const Int_t nCentBins  = 9; // 9 centrality bins in total
//     const Int_t centLow    = 0;
//     const Int_t centUp     = 8;
//     const Int_t nNetChBins = 4;
    
//     TFile* inFile = new TFile(inFileName);
//     if (NULL == inFile) {
//         cerr << "Error: Can not open file: " << inFileName << endl;
//     }

//     TString outFileName(inFileName);
//     outFileName.ReplaceAll(".hist.root", ".flow.root");
//     TFile* outFile = new TFile(outFileName.Data(), "RECREATE");
//     if (NULL==outFile) {
//         cerr << "Error: Can not create file: " << outFileName << endl;
//     }

//     for (Int_t i = centLow; i <= centUp; ++i) {
//         for (Int_t j = 0; j < nNetChBins; ++j) {
//             DCCorrelatioinSet correlations;
//             TString pfix("_cent");
//             pfix += i; pfix += "_chAsym"; pfix += j;
//             cout << pfix << endl;
//             correlations.ReadHistograms(inFile, pfix);
//             correlations.CalculateDiffFlow(outFile);
//         }
//     }
    
//     outFile->Close();
//     inFile->Close();
//     return;
// }
