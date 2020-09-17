#ifndef MULTICUMULANTS_TOYMCFLOWDISTGENERATOR_H
#define MULTICUMULANTS_TOYMCFLOWDISTGENERATOR_H

#ifndef __CINT__
	#include "vendor/loguru/loguru.hpp"
#endif

#include "ToyMCDistGenerator.h"

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

class ToyMCFlowDistGenerator : public ToyMCDistGenerator
{
public:
	virtual const char* name() const { return "ToyMCFlowDistGenerator"; }
	virtual const char* classname() const { return "ToyMCFlowDistGenerator"; }
	
	/**
	 * Constructor - 
	 */
	ToyMCFlowDistGenerator( )
	{
                LOG_SCOPE_FUNCTION( INFO );
                mean_  = 0.1;
                width_ = 0.4;
	}

	ToyMCFlowDistGenerator( int nbins, std::string title )
	{
                LOG_SCOPE_FUNCTION( INFO );
                mean_  = 0.1;
                width_ = 0.4;
                setHistoParam( nbins, 0., 1., title );
	}

	ToyMCFlowDistGenerator( double mean, double width, int nbins, std::string title )
	{
                LOG_SCOPE_FUNCTION( INFO );
                mean_  = mean;
                width_ = width;
                setHistoParam( nbins, 0., 1., title );
	}

	ToyMCFlowDistGenerator( double mean, double width)
	{
                LOG_SCOPE_FUNCTION( INFO );
                mean_  = mean;
                width_ = width;
	}

        ~ToyMCFlowDistGenerator()
        {
                LOG_SCOPE_FUNCTION( 9 );
        }

        void setBGParam(double mean, double width)
        {
                mean_  = mean;
                width_ = width;
        }

        void generateFormula()
        {
                setFunction( Form("x/TMath::Power(%f,2)*TMath::Exp(-1.*(x*x + %f*%f)/2./TMath::Power(%f,2))*TMath::BesselI0(x*%f/TMath::Power(%f,2))",
                            width_, mean_, mean_, width_, mean_, width_));
        }

        void setHistoFlowDistParam( int nbins, std::string title )
        {
             setHistoParam( nbins, 0., 1., title );
        }

private:
        double mean_;
        double width_;
};

}

#endif
