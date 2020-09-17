#ifndef MULTICUMULANTS_TOYMCDISTGENERATOR_H
#define MULTICUMULANTS_TOYMCDISTGENERATOR_H

#ifndef __CINT__
	#include "vendor/loguru/loguru.hpp"
#endif

#include "TF1.h"
#include "TH1D.h"
#include "TFile.h"
#include <string>

/**
 * Class to define Sets and subsets
 * 
 */
namespace toymc
{

class ToyMCDistGenerator
{
public:
	virtual const char* name() const { return "ToyMCDistGenerator"; }
	virtual const char* classname() const { return "ToyMCDistGenerator"; }
	
	/**
	 * Constructor - 
	 */
	ToyMCDistGenerator( )
	{
                LOG_SCOPE_FUNCTION( INFO );
                formula_ = "";
                function_ = 0x0;
                histo_ = new TH1D("histo", "", 10, 0., 10.);
	}

	ToyMCDistGenerator( int nbins, double min, double max, std::string title )
	{
                LOG_SCOPE_FUNCTION( INFO );
                formula_ = "";
                function_ = 0x0;
                histo_ = new TH1D(title.c_str(), "", nbins, min, max);
	}

        ~ToyMCDistGenerator()
        {
                LOG_SCOPE_FUNCTION( 9 );
                if( function_ ) delete function_;
                if( histo_ )    delete histo_;
        }

        void setFunction( std::string formula )
        {
           formula_ = formula;
        }

        void generate() 
        {
           if( formula_ == "" )
           {
               LOG_S(ERROR) << "ToyMCDistGenerator::Please provide a formula before going further";
               return;
           }

           function_ = new TF1("function", formula_.c_str(), histo_->GetXaxis()->GetXmin(), histo_->GetXaxis()->GetXmax());
           function_->SetNpx( histo_->GetNbinsX() );

           for(int ibin = 0; ibin < histo_->GetNbinsX(); ++ibin)
           {
              histo_->SetBinContent(ibin+1, function_->Eval(histo_->GetBinLowEdge(ibin+1))); 
           }
        }      

        void setHistoParam( int nbins, double min, double max, std::string title )
        {
                LOG_SCOPE_FUNCTION( INFO );
                histo_ = new TH1D(title.c_str(), "", nbins, min, max);
        }

        void saveHist( std::string fileName )
        {
           if( fileName == "" )
           {
               LOG_S(ERROR) << "ToyMCDistGenerator::Please provide a file name";
               return;
           }

           TFile* fout = new TFile(fileName.c_str(), "RECREATE");
           histo_->Write();

           fout->Close();
           delete fout;
        }

        TF1*  getFunction() { return function_; }
        TH1D* getHisto()    { return histo_; }

        void printFormula()
        {
               LOG_S(INFO) << "ToyMCDistGenerator::Printing current formula...";
               LOG_S(INFO) << formula_.c_str();
        }

private:
        TH1D* histo_;

        std::string formula_;
        TF1* function_;
};

}

#endif
