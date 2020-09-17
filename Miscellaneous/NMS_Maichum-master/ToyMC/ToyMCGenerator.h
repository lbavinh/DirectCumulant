#ifndef MULTICUMULANTS_TOYMCGENERATOR_H
#define MULTICUMULANTS_TOYMCGENERATOR_H

#include <string>
#include <iomanip>  // setprecision
#include <stdlib.h> // getenv

// ROOT
#include <TTree.h>
#include <TF1.h>
#include <TMath.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TObject.h>
#include <TRandom3.h>

#include "ToyMC/ToyMCEvent.h"
#include "ToyMC/ToyMCParticle.h"

#ifndef __CINT__
	#include "vendor/loguru/loguru.hpp"
#endif


/**
 * Class to define Sets and subsets
 * 
 */
namespace toymc
{
//Particle distribution enum
enum PartDist
{
   kConst = 0,
   kPtDep
};


//Particle distribution parameters
class ParticleDistParam 
{
public:
        ParticleDistParam()
	{
		LOG_SCOPE_FUNCTION( INFO );
                setParam( PartDist::kConst );
	}

        ParticleDistParam( PartDist partdist )
	{
		LOG_SCOPE_FUNCTION( INFO );
                setParam( partdist );
	}

        void setParam( PartDist partdist )
        {
             switch( partdist )
             {
                case PartDist::kConst :
                  _multPDF = "0.*x + 1";
                  _phiPDF  = "0.*x + 1";
                  _ptPDF   = "0.*x + 1";
                  _etaPDF  = "0.*x + 1";
                  break;
                case PartDist::kPtDep :
                  _multPDF = "0.*x + 1";
                  _phiPDF  = "0.*x + 1";
                  _ptPDF   = "0.*x + 1";
                  _etaPDF  = "0.*x + 1";
                  break;
                default :
                  _multPDF = "0.*x + 1";
                  _phiPDF  = "0.*x + 1";
                  _ptPDF   = "0.*x + 1";
                  _etaPDF  = "0.*x + 1";
                  break;
             }        
        }

        std::string getMultDist() { return this->_multPDF; }
        std::string getPhiDist()  { return this->_phiPDF; }
        std::string getPtDist()   { return this->_ptPDF; }
        std::string getEtaDist()  { return this->_etaPDF; }

protected:
        std::string _multPDF;
        std::string _phiPDF;
        std::string _ptPDF;
        std::string _etaPDF;
};

//Toy MC generator class
class ToyMCGenerator : public TObject
{
public:
	virtual const char* name() const { return "ToyMCGenerator"; }
	virtual const char* classname() const { return "ToyMCGenerator"; }
	
	/**
	 * Constructor - 
	 */
	ToyMCGenerator()
	{
                LOG_SCOPE_FUNCTION( INFO );
                LOG_F( WARNING, "NO RANDOM SEED GIVEN!" );
		commonPartDistSetup( PartDist::kConst, 0, 1000, 0., 10., -10., 10.);
                commonVnSetup();
	}

        ToyMCGenerator( size_t seed,
                        PartDist partdist, 
                        int multmin, int multmax,
                        double ptmin,  double ptmax,
                        double etamin, double etamax )
	{
                LOG_SCOPE_FUNCTION( INFO );
                LOG_F( INFO, "RANDOM SEED=%lu", seed );
                gRandom->SetSeed( seed );
		commonPartDistSetup( partdist, multmin, multmax, ptmin, ptmax, etamin, etamax );
                commonVnSetup();
	}

	~ToyMCGenerator()
	{
		LOG_SCOPE_FUNCTION( 9 );
                if( this->_fpartMult ) delete this->_fpartMult;
                if( this->_fpartPhi )  delete this->_fpartPhi ;
                if( this->_fpartPt )   delete this->_fpartPt  ;
                if( this->_fpartEta )  delete this->_fpartEta ;

                for(size_t ivn = 0; ivn < this->_fvn.size(); ++ivn )
                   if( this->_fvn[ivn] ) 
                      delete this->_fvn[ivn];

                this->_fvn.clear();
                std::vector<TF1*>().swap(this->_fvn);
	}

	void commonPartDistSetup( PartDist partdist, 
                                  int multmin,   int multmax,
                                  double ptmin,  double ptmax,
                                  double etamin, double etamax )
        {
		LOG_SCOPE_FUNCTION( INFO );

                ParticleDistParam params( partdist );
                                
                this->_fpartMult = new TF1("fmult", params.getMultDist().c_str(), multmin, multmax);
                this->_fpartPhi  = new TF1("fphi" , params.getPhiDist().c_str(),  0,       2.0 * TMath::Pi());
                this->_fpartPt   = new TF1("fpt"  , params.getPtDist().c_str(),   ptmin,   ptmax);
                this->_fpartEta  = new TF1("feta" , params.getEtaDist().c_str(),  etamin,  etamax);

                this->_fpartMult->SetNpx(300);             
                this->_fpartPhi ->SetNpx(300);  
                this->_fpartPt  ->SetNpx(300); 
                this->_fpartEta ->SetNpx(300); 
	}

        void commonVnSetup( )
        {
                double pi = TMath::Pi();
                this->_sPDF = Form("[0]/2./%f*( 1 + 2*[1]*cos(2*x) + 2*[2]*cos(3*x) + 2*[3]*cos(4*x) )", pi);

                this->_fvn.resize(3);
                for(size_t ivn = 0; ivn < _fvn.size(); ++ivn)
                {  
                          _fvn[ivn] = new TF1("fvn", "x/TMath::Power([0],2)*TMath::Exp(-1.*(x*x + [1]*[1])/2./TMath::Power([0],2))*TMath::BesselI0(x*[1]/TMath::Power([0],2))", 0., 1.);
                          this->_fvn[ivn]->SetNpx(1000);
                }

                this->_isvnfluct = false;
        }

        double generatePDF()
        {
                return 0.;
        }

        void generatePart(TF1* fpdf)
        {
		//LOG_SCOPE_FUNCTION( INFO );
		// make sure we start fresh
		// reusing the same object is a huge performance boost inside loops
		this->_plc.reset();

		double pt  = this->_fpartPt->GetRandom();
		double eta = this->_fpartEta->GetRandom();
		double phi = fpdf->GetRandom(); 

		this->_plc.set(pt, eta, phi);
        }

	void generate( int nevts = -1)
	{
		LOG_SCOPE_FUNCTION( INFO );

                TF1* fvn = new TF1("fvn", this->_sPDF.c_str(), 0., 2*TMath::Pi());

		for(int ievt = 0; ievt<nevts; ++ievt)
		{
                    int mult = (int) this->_fpartMult->GetRandom();
                    fvn->SetParameter(0, static_cast<double>(mult));
                    if(this->_isvnfluct)
                    {
                       this->_fvn[0]->SetParameter(1,0.01);
                       this->_fvn[0]->SetParameter(0,0.046);

                       fvn->SetParameter(1, this->_fvn[0]->GetRandom());
                       fvn->SetParameter(2, 0.0);
                       fvn->SetParameter(3, 0.0);
                    }
                    else
                    {
                       fvn->SetParameter(1, 0.1);
                       fvn->SetParameter(2, 0.0);
                       fvn->SetParameter(3, 0.0);
                    }
		    for(int ipart = 0; ipart < mult; ++ipart)
		    {
                            generatePart(fvn);
		    }
                }
                delete fvn;
         }

         void isVnFluct( bool answer )
         {
            this->_isvnfluct = answer;         
         }

	/**
	 * builds the string representation of the object
	 *
	 * @return String representation of this
	 */
	std::string toString(){
		std::string s = "";
		s += this->classname(); 
		return s; 
	}

public:
//protected:
	ToyMCParticle _plc;

        bool _isvnfluct;

        TF1* _fpartMult;
        TF1* _fpartPhi;
        TF1* _fpartPt;
        TF1* _fpartEta;

        std::vector<TF1*> _fvn;

        std::string _sPDF;

	ClassDef( ToyMCGenerator, 1 )
};
}	// toymc NAMESPACE
#endif
