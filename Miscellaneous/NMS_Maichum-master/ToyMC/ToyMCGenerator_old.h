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

#include "ToyMC/BranchWriter.h"
#include "ToyMC/TClonesArrayWriter.h"

#ifndef __CINT__
	#include "vendor/loguru/loguru.hpp"
#endif


/**
 * Class to define Sets and subsets
 * 
 */
namespace toymc
{

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
		this->_nevts = 0;

		commonSetup("PbPb", "const", "");
	}

	ToyMCGenerator( std::string system, std::string fctname, std::string afterburnersetting = "" )
	{
		LOG_SCOPE_FUNCTION( INFO );
		this->_nevts = 0;

		commonSetup(system, fctname, afterburnersetting);
	}

	~ToyMCGenerator()
	{
		LOG_SCOPE_FUNCTION( 9 );
                //if(this->_output) delete this->_output;

                if( this->_hmult ) delete this->_hmult;
                if( this->_heta  ) delete this->_heta;
                if( this->_hpt   ) delete this->_hpt;
                if( this->_hphi  ) delete this->_hphi;

                if( this->_hvnMod_mult ) delete this->_hvnMod_mult;
                if( this->_hvnMod_eta  ) delete this->_hvnMod_eta;
                if( this->_hvnMod_pt   ) delete this->_hvnMod_pt;

                if( this->_fvn ) delete this->_fvn;
                if( this->_hvn ) delete this->_hvn;
	}

	void commonSetup( std::string system, std::string fctname, std::string afterburnersetting ){
		LOG_SCOPE_FUNCTION( INFO );

                this->_hmult = 0x0;
                this->_heta  = 0x0;
                this->_hpt   = 0x0;
                this->_hphi  = 0x0;
                this->_hmult->AddDirectory(kFALSE);
                this->_heta ->AddDirectory(kFALSE);
                this->_hpt  ->AddDirectory(kFALSE);
                this->_hphi ->AddDirectory(kFALSE);

                this->_multmin = 0.;
                this->_multmax = 0.;
                this->_etamin  = 0.;
                this->_etamin  = 0.;
                this->_ptmin   = 0.;
                this->_ptmin   = 0.;

                this->_isVnFluct = false;
                this->_fvn = new TF1("fvn", "x/TMath::Power([0],2) *TMath::Exp(-1.*(x*x + [1]*[1])/2./TMath::Power([0],2)) *TMath::BesselI0(x*[1]/TMath::Power([0],2))", 0., .25);
                this->_fvn->SetNpx(10000);
                this->_hvn = 0x0;

                std::string filename = std::string(getenv("DATADIR")) + "/ToyMCdistribution_" + fctname + ".root";
                //TFile *f = TFile::Open(filename.c_str());
                TFile f(filename.c_str());

                this->_hmult = dynamic_cast<TH1I*>( f.Get(  (system + "/hmult" ).c_str() )->Clone() );
                this->_multmin = this->_hmult->GetXaxis()->GetXmin();
                this->_multmax = this->_hmult->GetXaxis()->GetXmax();
                this->_heta  = dynamic_cast<TH1D*>( f.Get( ( system + "/heta"  ).c_str() )->Clone());
                this->_etamin = this->_heta->GetXaxis()->GetXmin();
                this->_etamax = this->_heta->GetXaxis()->GetXmax();
                this->_hpt   = dynamic_cast<TH1D*>( f.Get( ( system + "/hpt"   ).c_str() )->Clone());
                this->_ptmin = this->_hpt->GetXaxis()->GetXmin();
                this->_ptmax = this->_hpt->GetXaxis()->GetXmax();
                this->_hphi  = dynamic_cast<TH1D*>( f.Get( ( system + "/hphi"  ).c_str() )->Clone());
                f.Close();
 
                afterBurnerSetting( system, afterburnersetting );
	}

        void setRanges(double ptmin, double ptmax, double etamin, double etamax, int multmin, int multmax)
        {
                this->_multmin = multmin;
                this->_multmax = multmax;
                for(int ibin = 0; ibin < this->_hmult->GetNbinsX(); ++ibin) 
                {
                    int val = this->_hmult->GetBinCenter(ibin+1);
                    if( val < this->_multmin || val >= this->_multmax ) this->_hmult->SetBinContent(ibin+1, 0);
                }
                this->_etamin  = etamin;
                this->_etamax  = etamax;
                for(int ibin = 0; ibin < this->_heta->GetNbinsX(); ++ibin) 
                {
                    double val = this->_heta->GetBinCenter(ibin+1);
                    if( val < this->_etamin || val >= this->_etamax ) this->_heta->SetBinContent(ibin+1, 0.);
                }
                this->_ptmin   = ptmin;
                this->_ptmax   = ptmax;
                for(int ibin = 0; ibin < this->_hpt->GetNbinsX(); ++ibin) 
                {
                    double val = this->_hpt->GetBinCenter(ibin+1);
                    if( val < this->_ptmin || val >= this->_ptmax ) this->_hpt->SetBinContent(ibin+1, 0.);
                }
        }

        void afterBurnerSetting( std::string system, std::string afterburnersetting )
        {
                this->_hvnMod_mult = 0x0;
                this->_hvnMod_eta  = 0x0;
                this->_hvnMod_pt   = 0x0;
                this->_hvnMod_mult->AddDirectory(kFALSE);
                this->_hvnMod_eta ->AddDirectory(kFALSE);
                this->_hvnMod_pt  ->AddDirectory(kFALSE);

                if(afterburnersetting == "") this->_isVnSet = false;
                else                         this->_isVnSet = true;

                if(this->_isVnSet)
                {
                   std::string filename = std::string(getenv("DATADIR")) + "/ToyMCVn_" + afterburnersetting + ".root";
                   TFile f(filename.c_str());

                   this->_hvnMod_mult = dynamic_cast<TH1D*>( f.Get( (system + "/hvnMod_mult").c_str() )->Clone());
                   this->_hvnMod_eta  = dynamic_cast<TH1D*>( f.Get( (system + "/hvnMod_eta" ).c_str() )->Clone());
                   this->_hvnMod_pt   = dynamic_cast<TH1D*>( f.Get( (system + "/hvnMod_pt"  ).c_str() )->Clone());

                   TH1D* hvn = dynamic_cast<TH1D*>( f.Get( (system + "/hvnMod_mag"  ).c_str() )->Clone());
                   for(int ibin = 0; ibin < hvn->GetNbinsX(); ++ibin) this->_vn.push_back(hvn->GetBinContent(ibin+1));
                   delete hvn;

                   //TODO: Generalize to all harmonics
                   this->_fvn->SetParameter(1,this->_vn[2]);
                   this->_fvn->SetParameter(0,0.046);

                   this->_hvn = new TH1D("h","",1000,0.,1.); 
                   for(int ibin = 0; ibin < this->_hvn->GetNbinsX(); ++ibin)
                      this->_hvn->SetBinContent(ibin+1, this->_fvn->Eval(this->_hvn->GetXaxis()->GetBinCenter(ibin+1)));

                   f.Close();
                }
        }

	void makeTree( std::string filename = "ToyMc.root" )
	{
		LOG_SCOPE_FUNCTION( INFO );
		this->_output = new TFile( filename.c_str(), "RECREATE" );
		// if you open the file first then the TTree can do buffered outputs

		this->_tree = new TTree("ToyMCTree", "Toy MC Tree");
		this->_eventWriter.createBranch( this->_tree, "Event" );
		this->_plcsWriter.createBranch( this->_tree, "Particles" );
	}

        std::string fourierFormula(double mult, double eta, double pt)
        {
            double pi = TMath::Pi();
            std::string formula = Form("%f/2./%f*(1", mult, pi);
            for(size_t iharm = 1; iharm < this->_vn.size(); ++iharm) 
            {
               double vn = this->_vn[iharm];
               //vn  *= this->_hvnMod_mult->GetBinContent(this->_hvnMod_mult->GetXaxis()->FindBin(mult));
               //vn  *= this->_hvnMod_eta ->GetBinContent(this->_hvnMod_eta ->GetXaxis()->FindBin(eta));
               //vn  *= this->_hvnMod_pt  ->GetBinContent(this->_hvnMod_pt  ->GetXaxis()->FindBin(pt));
               ////if(vn == 0. && this->_vn[iharm] != 0.) std::cout << "ZERO!!! pt = " << pt << " " << this->_vn[iharm] << std::endl;
               formula += Form("+2*%f*cos(%zu*x)",vn,iharm);

               //if(vn == 0. && this->_vn[iharm] != 0.) std::cout << "ZERO!!! " << mult << " " << eta << " " << pt << " " << this->_vn[iharm] << std::endl;
            }
            formula += ")";
            //std::cout << formula << std::endl;
            return formula;
        }

        void printFourierFormula()
        {
           std::cout << fourierFormula(1.,1.,1.).c_str() << std::endl;
        } 

        double flowFluctuation()
        {
           TRandom3 r(0);
           return this->_hvn->GetRandom();
        }

        double generatePDF(double mult, double eta, double pt, double phi)
        {
                std::string formula = fourierFormula(mult,eta,pt);
                TF1 *fPDF = new TF1("fPDF", formula.c_str(), -1*TMath::Pi(), 1*TMath::Pi());
                
                TRandom3 r1(0);
                double pdfVal = fPDF->GetRandom();
                delete fPDF;

                return pdfVal;
        }

        void generatePart(int nparticles)
        {
		//LOG_SCOPE_FUNCTION( INFO );
		// make sure we start fresh
		// reusing the same object is a huge performance boost inside loops
		this->_plc.reset();

		double pt  = this->_hpt->GetRandom();
		double eta = this->_heta->GetRandom();
		double phi = this->_hphi->GetRandom(); 

                //convulte vn distribution
                if(this->_isVnSet)
                {
                    phi = generatePDF(nparticles, eta, pt, phi);
                }

		this->_plc.set(pt, eta, phi);
        }

	void generate( int nevts = -1, std::string filename = "ToyMC.root" )
	{
		LOG_SCOPE_FUNCTION( INFO );

		if ( nevts > 0 )
			this->_nevts = nevts;

		makeTree( filename );
		for(int ievt = 0; ievt<this->_nevts; ++ievt)
		{
                        //get the number of particles in this event
                        int nparticles = 0;

                        TRandom3 r2(0);
                        nparticles = this->_hmult->GetRandom();

                        //Number of particles entering the correlations *TO BE IMPLEMENTED CORRECTLY*
                        unsigned int mult = 0.;
                        //Number of particles to define the event class *TO BE IMPLEMENTED CORRECTLY*
                        unsigned int noff = 0.;
                        //Event plane *TO BE IMPLEMENTED CORRECTLY*
                        //unsigned int psi = 0.;

                        //std::cout <<
                        //"\rToyMCGenerator::INFO:: ievt = " << ievt
                        //<<
                        //" ~~~> " << std::setprecision(3) << (double)((double)ievt / (double)this->_nevts)*10000  << " %"
                        //<< std::flush;

			this->_plcsWriter.reset();

                        for(size_t iharm = 1; iharm < this->_vn.size(); ++iharm) 
                        {
                           isFlowFluct(iharm);
                           //if(this->_isVnFluct && this->_isVnSet) this->_vn[iharm] = flowFluctuation();
                        }

			for(int ipart = 0; ipart < nparticles; ++ipart)
			{
                                generatePart(nparticles);
                                ++mult;
				this->_plcsWriter.add( this->_plc );
			}

                        //Writting events
			this->_event.set(mult, noff);
			this->_eventWriter.set( this->_event );

			//Fill TTree
			this->_tree->Fill(); 
		}
                //std::cout << std::endl;

		this->_tree->Write();
		this->_output->Write();
		this->_output->Close();

	}

        TH1I* getMultHist() { return this->_hmult; }

        void isFlowFluct(int iharm) 
        {
                if(this->_isVnFluct && this->_isVnSet && iharm == 2)
                        this->_vn[iharm] = flowFluctuation();
        }

        void setFlowFluctuations(bool flowFluct = true) { this->_isVnFluct = flowFluct; }

        double getPlcPt() 
        {
                return this->_plc.getpt();
        }
	
        double getPlcEta() 
        {
                return this->_plc.geteta();
        }
	
        double getPlcPhi() 
        {
                return this->_plc.getphi();
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

protected:
	int _nevts;
	TFile*_output;
	TTree* _tree;
	ToyMCEvent _event;
	ToyMCParticle _plc;

	#ifndef __CINT__
	BranchWriter<ToyMCEvent> _eventWriter;
	TClonesArrayWriter<ToyMCParticle> _plcsWriter;
	#endif

        TH1I* _hmult;
        TH1D* _heta;
        TH1D* _hpt;
        TH1D* _hphi;

        TH1D* _hvnMod_mult;
        TH1D* _hvnMod_eta;
        TH1D* _hvnMod_pt;

        double _ptmin;
        double _ptmax;
        double _etamin;
        double _etamax;
        int _multmin;
        int _multmax;

        bool _isVnSet;
        bool _isVnFluct;

        TF1*  _fvn;
        TH1D* _hvn;

        std::vector<double> _vn;

	ClassDef( ToyMCGenerator, 1 )
};
}	// toymc NAMESPACE
#endif
