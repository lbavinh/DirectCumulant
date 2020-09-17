// logging library
#define LOGURU_IMPLEMENTATION 1
#include "vendor/loguru/loguru.hpp"
#include "vendor/cmdline.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <random>
#include <vector>

#include <correlations/Types.hh>
#include <correlations/Result.hh>
#include <correlations/QVector.hh>
#include <correlations/recursive/FromQVector.hh>
#include <correlations/recurrence/FromQVector.hh>

#include "MultiCumulants/Types.h"
#include "MultiCumulants/Subsets.h"
#include "MultiCumulants/QVector.h"
#include "MultiCumulants/QVectorSet.h"
#include "MultiCumulants/Correlator.h"
#include "ToyMC/ToyMCFlowDistGenerator.h"
#include "ToyMC/ToyMCDistGenerator.h"
#include "ToyMC/ToyMCGenerator.h"
#include "ToyMC/BranchReader.h"
#include "ToyMC/TClonesArrayReader.h"

#include <TFile.h>
#include <TDirectory.h>
#include <TH1.h>
#include <TSpline.h>
#include <TF1.h>

using namespace std;

void genAndAnalyzeTree(size_t seed,
                       int harm,
                       double ptMin,   double ptMax,
                       double etaMin,  double etaMax,
                       double multMin, double multMax,
                       int    nEvt,    bool isVnFluct,
                       std::string outFileName);

void analyzeTree(std::string inFileName,
                 std::string outFileName,
                 int nEvt = -1);

void distributionProd( double multmin,
                       double multmax,
                       std::string multformula,
                       double ptmin,
                       double ptmax,  
                       std::string ptformula,
                       double etamin,
                       double etamax,
                       std::string etaformula, 
                       std::string outFileName);

void distFlowProd( std::string outFileName );

int 
main(int argc, char** argv) {
	loguru::set_thread_name("MAIN");
	// logs everything to the debug.log file every run
	loguru::add_file("bin/debug.log", loguru::Truncate, loguru::Verbosity_MAX);

	// sometimes the "stream" form of the logger is more convenient, use LOG_S( LEVEL ) << "MESSAGE";
	// No need for an endl at the end of a line


	cmdline::parser parser;

	parser.add("flowdist", '\0', "generate flow distribution for ToyMC");
	parser.add("partdist", '\0', "generate particle distribution for ToyMC");
	parser.add("real", '\0', "generate realistic particle distribution for ToyMC");
	parser.add("generate", '\0', "generate ToyMc");
	parser.add("analyze", '\0', "analyze ToyMc output");
        parser.add<size_t>("seed", '\0', "seed for all random number generators", false );
        parser.add<int>("nevents", '\0', "number of events to generate/analyze", false, -1);
	parser.add<int>("harm", '\0', "harmonic to generate/analyze", false, 2);
	parser.add<double>("ptmin", '\0', "ptmin to generate/analyze", false, 0.3);
	parser.add<double>("ptmax", '\0', "ptmax to generate/analyze", false, 3.0);
	parser.add<double>("etamin", '\0', "etamin to generate/analyze", false, -2.4);
	parser.add<double>("etamax", '\0', "etamax to generate/analyze", false, 2.4);
	parser.add<double>("multmin", '\0', "multmin to generate/analyze", false, 10.);
	parser.add<double>("multmax", '\0', "multmax to generate/analyze", false, 40.);
	parser.add<std::string>("output", '\0', "output file name", false, "output_toymc");
	parser.add<std::string>("input", '\0', "input file name", false, "");
	parser.add<bool>("isVnfluct", '\0', "vn fluctuations", false, false);

	parser.parse_check( argc, argv );

        if ( parser.exist( "flowdist" ) )
        {
            distFlowProd( parser.get<std::string>( "output" ) );
        }
        if ( parser.exist( "partdist" ) )
        {
                if ( parser.exist( "real" ) )
                {
                   distributionProd( parser.get<double>( "multmin" ),
                                     parser.get<double>( "multmax" ),
                                     "exp(log(0.569982) + TMath::LnGamma(2.799728+x) - TMath::LnGamma(2.799728) - TMath::LnGamma(x+1) + log(31.995258 / (31.995258+2.799728)) * x + log(1.0 + 31.995258/2.799728) * -2.799728)",
                                     parser.get<double>( "ptmin" ),
                                     parser.get<double>( "ptmax" ),
                                     "x*exp(-1*(sqrt(pow(2.5,2)+pow(x,2)))/(5))",
                                     parser.get<double>( "etamin" ),
                                     parser.get<double>( "etamax" ),
                                     "5.1*exp(-0.5*x*x/3.11/3.11)-5*exp(-0.5*x*x/3.06/3.06)", 
                                     parser.get<std::string>( "output" ) );
                }
                else
                {
                   distributionProd( parser.get<double>( "multmin" ),
                                     parser.get<double>( "multmax" ),
                                     "0*x+1",
                                     parser.get<double>( "ptmin" ),
                                     parser.get<double>( "ptmax" ),
                                     "0*x+1",
                                     parser.get<double>( "etamin" ),
                                     parser.get<double>( "etamax" ),
                                     "0*x+1", 
                                     parser.get<std::string>( "output" ) );
                 }
        }
	else if ( parser.exist( "generate" ) && !parser.exist( "analyze" )  ){
        	genAndAnalyzeTree( parser.get<size_t>( "seed" ),
                                   parser.get<int>( "harm" ),
                                   parser.get<double>( "multmin" ),
                                   parser.get<double>( "multmax" ),
                                   parser.get<double>( "ptmin" ),
                                   parser.get<double>( "ptmax" ),
                                   parser.get<double>( "etamin" ),
                                   parser.get<double>( "etamax" ),
                                   parser.get<int>( "nevents" ),
                                   parser.get<bool>( "isVnfluct" ),
                                   parser.get<std::string>( "output" ) );
        }
	else if ( parser.exist( "analyze" ) && !parser.exist( "generate" ) ){
                
		analyzeTree( parser.get<std::string>( "input" ),
	                     parser.get<std::string>( "output" ),
	                     parser.get<int>( "nevents" ) );
                
        }
	else {
		std::cout << parser.usage() << endl;
	}
        return 0; 
}
//

void distFlowProd( std::string outFileName )
{
        //generate the first flow distribution
        toymc::ToyMCFlowDistGenerator flow_dist;
        flow_dist.setBGParam(0.1,0.04);
        flow_dist.generateFormula();
        flow_dist.printFormula();

        flow_dist.setHistoFlowDistParam( 1000, "flowdist_test" );
        flow_dist.generate();

        //generate a second flow distribution
        toymc::ToyMCFlowDistGenerator flow_dist2;
        flow_dist2.setBGParam(0.01,0.04);
        flow_dist2.generateFormula();
        flow_dist2.printFormula();

        flow_dist2.setHistoFlowDistParam( 1000, "flowdist_test2" );
        flow_dist2.generate();


        //save all flow distribution in a root file
        TFile* fout = new TFile(Form("%s/%s.root", getenv("OUTPUTDIR"), outFileName.c_str()), "recreate");
        TH1D* hflow  = flow_dist.getHisto();  hflow->Write();
        TH1D* hflow2 = flow_dist2.getHisto(); hflow2->Write();
        fout->Close();
        delete fout;
}

void distributionProd( double multmin,
                       double multmax,
                       std::string multformula,
                       double ptmin,
                       double ptmax,  
                       std::string ptformula,
                       double etamin,
                       double etamax,
                       std::string etaformula, 
                       std::string outFileName)
{
        toymc::ToyMCDistGenerator gmult(static_cast<int>(multmax-multmin), 
                                        multmin, 
                                        multmax, 
                                        "multDist");
        gmult.setFunction(multformula);
        gmult.generate();

        toymc::ToyMCDistGenerator geta(static_cast<int>((etamax-etamin)*100), 
                                        etamin, 
                                        etamax, 
                                        "etaDist");
        geta.setFunction(etaformula);
        geta.generate();

        toymc::ToyMCDistGenerator gpt(static_cast<int>((ptmax-ptmin)*100), 
                                        ptmin, 
                                        ptmax, 
                                        "ptDist");
        gpt.setFunction(ptformula);
        gpt.generate();

        toymc::ToyMCDistGenerator gphi(static_cast<int>(2.*TMath::Pi()*100), 
                                        0., 
                                        2.*TMath::Pi(), 
                                        "phiDist");
        gphi.setFunction("0*x+1");
        gphi.generate();

        TFile* fout = new TFile(Form("%s/%s.root", getenv("OUTPUTDIR"), outFileName.c_str()), "recreate");
        TH1D* hmult = gmult.getHisto(); hmult->Write();
        TH1D* heta  = geta.getHisto();  heta->Write();
        TH1D* hpt   = gpt.getHisto() ;  hpt ->Write();
        TH1D* hphi  = gphi.getHisto();  hphi->Write();
        fout->Close();
        delete fout;
}

void genAndAnalyzeTree(size_t seed,
                       int harm,
                       double multMin, double multMax,
                       double ptMin,   double ptMax,
                       double etaMin,  double etaMax,
                       int    nEvt,    bool isVnFluct,    
                       std::string outFileName)
{

	toymc::ToyMCGenerator g(seed, toymc::PartDist::kConst, multMin, multMax, ptMin, ptMax, etaMin, etaMax);
        TF1* fvn = new TF1("fvn", g._sPDF.c_str(), 0., 2*TMath::Pi());
        if(isVnFluct) g.isVnFluct(true);
	LOG_S(INFO) << g.toString();
	LOG_S(INFO) << "Flow fluctuations? " << isVnFluct;

        //Init standard method
        correlations::QVector qN(0, 0, false);
        correlations::HarmonicVector hcN;
        correlations::FromQVector *cqN;
        hcN = correlations::HarmonicVector(8);
        hcN[0] =  1*harm;
        hcN[1] = -1*harm;
        hcN[2] =  1*harm;
        hcN[3] = -1*harm;
        hcN[4] =  1*harm;
        hcN[5] = -1*harm;
        hcN[6] =  1*harm;
        hcN[7] = -1*harm;
        qN.resize(hcN);
        cqN = new correlations::recurrence::FromQVector(qN);


        //Init subset for subevent method
        cumulant::Subset sub1(2);
        sub1.set(0, "pt", 0.3, 3.0);
        sub1.set(1, "eta", -2.4, 2.4);
        cumulant::Subset sub2(2);
        sub2.set(0, "pt", 0.3, 3.0);
        sub2.set(1, "eta", -2.4, 2.4);
        cumulant::Subset sub3(2);
        sub3.set(0, "pt", 0.3, 3.0);
        sub3.set(1, "eta", -2.4, 2.4);
        cumulant::Subset sub4(2);
        sub4.set(0, "pt", 0.3, 3.0);
        sub4.set(1, "eta", -2.4, 2.4);

        cumulant::Subset sub5(2);
        sub5.set(0, "pt", 0.3, 3.0);
        sub5.set(1, "eta", -2.4, 2.4);
        cumulant::Subset sub6(2);
        sub6.set(0, "pt", 0.3, 3.0);
        sub6.set(1, "eta", -2.4, 2.4);
        cumulant::Subset sub7(2);
        sub7.set(0, "pt", 0.3, 3.0);
        sub7.set(1, "eta", -2.4, 2.4);
        cumulant::Subset sub8(2);
        sub8.set(0, "pt", 0.3, 3.0);
        sub8.set(1, "eta", -2.4, 2.4);

        ////Init 2-p sub-event method
        //cumulant::Set set2(2);
        //set2.setSubsetParams(0, sub1);
        //set2.setSubsetParams(1, sub5);

        ////Init 4-p sub-event method
        //cumulant::Set set4(4);
        //set4.setSubsetParams(0, sub1);
        //set4.setSubsetParams(1, sub2);
        //set4.setSubsetParams(2, sub5);
        //set4.setSubsetParams(3, sub6);

        ////Init 6-p sub-event method
        //cumulant::Set set6(6);
        //set6.setSubsetParams(0, sub1);
        //set6.setSubsetParams(1, sub2);
        //set6.setSubsetParams(2, sub3);
        //set6.setSubsetParams(3, sub5);
        //set6.setSubsetParams(4, sub6);
        //set6.setSubsetParams(5, sub7);

        //Init 8-p sub-event method
        cumulant::Set set8(8);
        set8.setSubsetParams(0, sub1);
        set8.setSubsetParams(1, sub2);
        set8.setSubsetParams(2, sub3);
        set8.setSubsetParams(3, sub4);
        set8.setSubsetParams(4, sub5);
        set8.setSubsetParams(5, sub6);
        set8.setSubsetParams(6, sub7);
        set8.setSubsetParams(7, sub8);


        ////Init 2-p method with subset
        //HarmonicVector h2(2);
        //h2[0] =  1*harm;
        //h2[1] = -1*harm;
        //cumulant::QVectorSet q2(h2, set2, false);

        ////Init 4-p method with subset
        //HarmonicVector h4(4);
        //h4[0] =  1*harm;
        //h4[1] =  1*harm;
        //h4[2] = -1*harm;
        //h4[3] = -1*harm;
        //cumulant::QVectorSet q4(h4, set4, false);

        ////Init 6-p method with subset
        //HarmonicVector h6(6);
        //h6[0] =  1*harm;
        //h6[1] =  1*harm;
        //h6[2] =  1*harm;
        //h6[3] = -1*harm;
        //h6[4] = -1*harm;
        //h6[5] = -1*harm;
        //cumulant::QVectorSet q6(h6, set6, false);

        //Init 8-p method with subset
        HarmonicVector h8(8);
        h8[0] =  1*harm;
        h8[1] =  1*harm;
        h8[2] =  1*harm;
        h8[3] =  1*harm;
        h8[4] = -1*harm;
        h8[5] = -1*harm;
        h8[6] = -1*harm;
        h8[7] = -1*harm;
        cumulant::QVectorSet q8(h8, set8, false);

        //Histograms
        //Global
        TH1I* hmult = new TH1I("hmult", "hmult", 1000,   0,             1000);
        TH1D* hpt   = new TH1D("hpt",   "hpt",   2000,   0,             20);
        TH1D* heta  = new TH1D("heta",  "heta",  2000,  -10,            10);
        TH1D* hphi  = new TH1D("hphi",  "hphi",  300,     0, 2*TMath::Pi());
        hmult->AddDirectory(kFALSE);
        hphi ->AddDirectory(kFALSE);
        heta ->AddDirectory(kFALSE);
        hpt  ->AddDirectory(kFALSE);
        //TTree
        unsigned int mult = 0.;
        double C2Nstd = 0., C4Nstd = 0., C6Nstd = 0., C8Nstd = 0., wC2Nstd = 0., wC4Nstd = 0., wC6Nstd = 0., wC8Nstd = 0.;
        double C2Ngap = 0., C4Ngap = 0., C6Ngap = 0., C8Ngap = 0., wC2Ngap = 0., wC4Ngap = 0., wC6Ngap = 0., wC8Ngap = 0.;
        TTree* tree = new TTree("trFlow", "trFlow");
        tree->Branch("mult", &mult, "mult/s");
        tree->Branch("C2Nstd",  &C2Nstd,  "C2Nstd/D");
        tree->Branch("C4Nstd",  &C4Nstd,  "C4Nstd/D");
        tree->Branch("C6Nstd",  &C6Nstd,  "C6Nstd/D");
        tree->Branch("C8Nstd",  &C8Nstd,  "C8Nstd/D");
        tree->Branch("wC2Nstd", &wC2Nstd, "wC2Nstd/D");
        tree->Branch("wC4Nstd", &wC4Nstd, "wC4Nstd/D");
        tree->Branch("wC6Nstd", &wC6Nstd, "wC6Nstd/D");
        tree->Branch("wC8Nstd", &wC8Nstd, "wC8Nstd/D");
        tree->Branch("C2Ngap",  &C2Ngap,  "C2Ngap/D");
        tree->Branch("C4Ngap",  &C4Ngap,  "C4Ngap/D");
        tree->Branch("C6Ngap",  &C6Ngap,  "C6Ngap/D");
        tree->Branch("C8Ngap",  &C8Ngap,  "C8Ngap/D");
        tree->Branch("wC2Ngap", &wC2Ngap, "wC2Ngap/D");
        tree->Branch("wC4Ngap", &wC4Ngap, "wC4Ngap/D");
        tree->Branch("wC6Ngap", &wC6Ngap, "wC6Ngap/D");
        tree->Branch("wC8Ngap", &wC8Ngap, "wC8Ngap/D");

        if(nEvt < 1) return;

        std::vector< double > val(2, 0.); //std::cout << val[0] << " " << val[1] << std::endl;
        correlations::Result rN2;
        correlations::Result rN4;
        correlations::Result rN6;
        correlations::Result rN8;

        cumulant::Correlator c2;
        //cumulant::Correlator c2of4;
        cumulant::Correlator c4;
        //cumulant::Correlator c4of6;
        //cumulant::Correlator c4of8;
        cumulant::Correlator c6;
        cumulant::Correlator c8;

        //#####################################
        // Loop over events
        //#####################################
	for(int ievt = 0; ievt < nEvt; ievt++)
	{
              //std::cout <<
              //"\rToyMCGenerator::INFO:: ievt = " << ievt
              //<<
              //" ~~~> " << std::setprecision(3) << (double)((double)ievt / (double)nEvt)*100  << " %"
              //<< std::flush;

              qN.reset();
              //q2.reset();
              //q4.reset();
              //q6.reset();
              q8.reset();

              //Define weights to be always 1
              double w = 1.;

              mult = (unsigned int) g._fpartMult->GetRandom();
              fvn->SetParameter(0, static_cast<double>(mult));
              if(g._isvnfluct)
              {
                 g._fvn[0]->SetParameter(1,0.1);
                 g._fvn[0]->SetParameter(0,0.046);

                 double vn = g._fvn[0]->GetRandom();
                 fvn->SetParameter(1, vn);
                 fvn->SetParameter(2, 0.0);
                 fvn->SetParameter(3, 0.0);
              }
              else
              {
                 fvn->SetParameter(1, 0.1);
                 fvn->SetParameter(2, 0.0);
                 fvn->SetParameter(3, 0.0);
              }

              //#####################################
              // Loop over particles
              //#####################################
	      for(unsigned int ipart = 0; ipart < mult; ++ipart)
	      {
                 g.generatePart(fvn);

                 double pt  = g._plc.getpt() ;    
                 double eta = g._plc.geteta();
                 double phi = g._plc.getphi();

                 hpt ->Fill(pt);
                 heta->Fill(eta);
                 hphi->Fill(phi);

                 //Cumulant
                 qN.fill(phi, w);

                 val[0] = pt;
                 val[1] = eta;
                 //q2.fill(val, phi, w);
                 //q4.fill(val, phi, w);
                 //q6.fill(val, phi, w);
                 q8.fill(val, phi, w);
              } //######## end loop particles

              //std::cout << std::endl;
	      //LOG_S(INFO) << "2p QV" << "\n" << q2.print();
              //std::cout << std::endl;
	      //LOG_S(INFO) << "4p QV" << "\n" << q4.print();
              //std::cout << std::endl;
	      //LOG_S(INFO) << "6p QV" << "\n" << q6.print();
              //std::cout << std::endl;
	      //LOG_S(INFO) << "8p QV" << "\n" << q8.print();
              //std::cout << std::endl;
	      //LOG_S(INFO) << "Printing Ante's values";
              //qN.print();

              hmult->Fill(mult);

              //With gap
	      //cumulant::QVectorMap& q2map = q2.getQ();
	      //cumulant::QVectorMap& q4map = q4.getQ();
	      //cumulant::QVectorMap& q6map = q6.getQ();
	      cumulant::QVectorMap& q8map = q8.getQ();

              //LOG_S(INFO) << "c2";
              c2 = cumulant::Correlator(17, q8map);
              C2Ngap = c2.v.real();
              wC2Ngap = c2.w;

              //LOG_S(INFO) << "c2of4";
              //c2of4 = cumulant::Correlator(5, q4map);

              //LOG_S(INFO) << "c4";
              c4 = cumulant::Correlator(51, q8map);
              C4Ngap = c4.v.real();
              wC4Ngap = c4.w;

              //LOG_S(INFO) << "c4of6";
              //c4of6 = cumulant::Correlator(29, q6map);
              //LOG_S(INFO) << "c4of8";
              //c4of8 = cumulant::Correlator(101, q8map);

              //LOG_S(INFO) << "c6";
              c6 = cumulant::Correlator(119, q8map);
              C6Ngap = c6.v.real();
              wC6Ngap = c6.w;

              c8 = cumulant::Correlator(255, q8map);
              C8Ngap = c8.v.real();
              wC8Ngap = c8.w;

              //Bilandzic code
              rN2 = cqN->calculate(2, hcN);
              rN4 = cqN->calculate(4, hcN);          
              rN6 = cqN->calculate(6, hcN);          
              rN8 = cqN->calculate(8, hcN);          

              C2Nstd  = rN2.corr();
              C4Nstd  = rN4.corr();
              C6Nstd  = rN6.corr();
              C8Nstd  = rN8.corr();
              wC2Nstd = rN2.weight();
              wC4Nstd = rN4.weight();
              wC6Nstd = rN6.weight();
              wC8Nstd = rN8.weight();

              //LOG_S(INFO) << "###  Our code:   ###";
              //LOG_S(INFO) << "C2N = " << C2Ngap << ", wC2N = " <<  wC2Ngap << std::endl;
              //LOG_S(INFO) << "C4N = " << C4Ngap << ", wC4N = " <<  wC4Ngap << std::endl;
              //LOG_S(INFO) << "C6N = " << C6Ngap << ", wC6N = " <<  wC6Ngap << std::endl;
              //LOG_S(INFO) << "C8N = " << C8Ngap << ", wC8N = " <<  wC8Ngap << std::endl;
              //LOG_S(INFO) << "### Ante's code: ###";
              //LOG_S(INFO) << "C2N = " << C2Nstd << ", wC2N = " <<  wC2Nstd << std::endl;
              //LOG_S(INFO) << "C4N = " << C4Nstd << ", wC4N = " <<  wC4Nstd << std::endl;
              //LOG_S(INFO) << "C6N = " << C6Nstd << ", wC6N = " <<  wC6Nstd << std::endl;
              //LOG_S(INFO) << "C8N = " << C8Nstd << ", wC8N = " <<  wC8Nstd << std::endl;
              //LOG_S(INFO) << "c2     : " << c2.toString() << "\n" << c2.repr;
              //LOG_S(INFO) << "c2of4  : " << c2of4.toString()<< "\n" << c2of4.repr;
              //LOG_S(INFO) << "c4     : " << c4.toString()<< "\n" << c4.repr;
              //LOG_S(INFO) << "c4of6  : " << c4of6.toString()<< "\n" << c4of6.repr;
              //LOG_S(INFO) << "c4of8  : " << c4of8.toString()<< "\n" << c4of8.repr;
              //LOG_S(INFO) << "c6     : " << c6.toString()<< "\n" << c6.repr;
              //qN.print();
        //       LOG_S(INFO) << c8.toString() << std::endl;

              tree->Fill();
          } //######## end loop eventss

          std::cout << std::endl;
          std::cout << "Writting..." << std::endl;
          TFile* fout = new TFile(Form("%s/%s.root", getenv("OUTPUTDIR"), outFileName.c_str()), "recreate");
          hmult->Write();
          hpt  ->Write();
          heta ->Write();
          hphi ->Write();
          tree ->Write();
          fout->Close();

          delete fout;
}

void analyzeTree(std::string inFileName,
                 std::string outFileName,
                 int nEvt)
{
        //Histograms
        //Vn plots
        TH1D* hC22std     = new TH1D("hC22std",     "", 600, 0., 600.);
        TH1D* hC22stdx    = new TH1D("hC22stdx",    "", 120, 0., 600.);
        hC22std    ->AddDirectory(kFALSE);
        hC22stdx   ->AddDirectory(kFALSE);
        TH1D* hC22gap     = new TH1D("hC22gap",     "", 600, 0., 600.);
        TH1D* hC22gapx    = new TH1D("hC22gapx",    "", 120, 0., 600.);
        hC22gap    ->AddDirectory(kFALSE);
        hC22gapx   ->AddDirectory(kFALSE);
        TH1D* hC24std     = new TH1D("hC24std",     "", 600, 0., 600.);
        TH1D* hC24stdx    = new TH1D("hC24stdx",    "", 120, 0., 600.);
        hC24std    ->AddDirectory(kFALSE);
        hC24stdx   ->AddDirectory(kFALSE);
        TH1D* hC24gap     = new TH1D("hC24gap",     "", 600, 0., 600.);
        TH1D* hC24gapx    = new TH1D("hC24gapx",    "", 120, 0., 600.);
        hC24gap    ->AddDirectory(kFALSE);
        hC24gapx   ->AddDirectory(kFALSE);
        TH1D* hC26std     = new TH1D("hC26std",     "", 600, 0., 600.);
        TH1D* hC26stdx    = new TH1D("hC26stdx",    "", 120, 0., 600.);
        hC26std    ->AddDirectory(kFALSE);
        hC26stdx   ->AddDirectory(kFALSE);
        TH1D* hC26gap     = new TH1D("hC26gap",     "", 600, 0., 600.);
        TH1D* hC26gapx    = new TH1D("hC26gapx",    "", 120, 0., 600.);
        hC26gap    ->AddDirectory(kFALSE);
        hC26gapx   ->AddDirectory(kFALSE);
        TH1D* hC28std     = new TH1D("hC28std",     "", 600, 0., 600.);
        TH1D* hC28stdx    = new TH1D("hC28stdx",    "", 120, 0., 600.);
        hC28std    ->AddDirectory(kFALSE);
        hC28stdx   ->AddDirectory(kFALSE);
        TH1D* hC28gap     = new TH1D("hC28gap",     "", 600, 0., 600.);
        TH1D* hC28gapx    = new TH1D("hC28gapx",    "", 120, 0., 600.);
        hC28gap    ->AddDirectory(kFALSE);
        hC28gapx   ->AddDirectory(kFALSE);
        //Vn plots
        TH1D* hV22std     = new TH1D("hV22std",     "", 600, 0., 600.);
        TH1D* hV22stdx    = new TH1D("hV22stdx",    "", 120, 0., 600.);
        TH1D* hV22std_num = new TH1D("hV22std_num", "", 600, 0., 600.);
        TH1D* hV22std_den = new TH1D("hV22std_den", "", 600, 0., 600.);
        hV22std    ->AddDirectory(kFALSE);
        hV22stdx   ->AddDirectory(kFALSE);
        hV22std_num->AddDirectory(kFALSE);
        hV22std_den->AddDirectory(kFALSE);
        TH1D* hV22gap     = new TH1D("hV22gap",     "", 600, 0., 600.);
        TH1D* hV22gapx    = new TH1D("hV22gapx",    "", 120, 0., 600.);
        TH1D* hV22gap_num = new TH1D("hV22gap_num", "", 600, 0., 600.);
        TH1D* hV22gap_den = new TH1D("hV22gap_den", "", 600, 0., 600.);
        hV22gap    ->AddDirectory(kFALSE);
        hV22gapx   ->AddDirectory(kFALSE);
        hV22gap_num->AddDirectory(kFALSE);
        hV22gap_den->AddDirectory(kFALSE);
        TH1D* hV24std     = new TH1D("hV24std",     "", 600, 0., 600.);
        TH1D* hV24stdx    = new TH1D("hV24stdx",    "", 120, 0., 600.);
        TH1D* hV24std_num = new TH1D("hV24std_num", "", 600, 0., 600.);
        TH1D* hV24std_den = new TH1D("hV24std_den", "", 600, 0., 600.);
        hV24std    ->AddDirectory(kFALSE);
        hV24stdx   ->AddDirectory(kFALSE);
        hV24std_num->AddDirectory(kFALSE);
        hV24std_den->AddDirectory(kFALSE);
        TH1D* hV24gap     = new TH1D("hV24gap",     "", 600, 0., 600.);
        TH1D* hV24gapx    = new TH1D("hV24gapx",    "", 120, 0., 600.);
        TH1D* hV24gap_num = new TH1D("hV24gap_num", "", 600, 0., 600.);
        TH1D* hV24gap_den = new TH1D("hV24gap_den", "", 600, 0., 600.);
        hV24gap    ->AddDirectory(kFALSE);
        hV24gapx   ->AddDirectory(kFALSE);
        hV24gap_num->AddDirectory(kFALSE);
        hV24gap_den->AddDirectory(kFALSE);
        TH1D* hV26std     = new TH1D("hV26std",     "", 600, 0., 600.);
        TH1D* hV26stdx    = new TH1D("hV26stdx",    "", 120, 0., 600.);
        TH1D* hV26std_num = new TH1D("hV26std_num", "", 600, 0., 600.);
        TH1D* hV26std_den = new TH1D("hV26std_den", "", 600, 0., 600.);
        hV26std    ->AddDirectory(kFALSE);
        hV26stdx   ->AddDirectory(kFALSE);
        hV26std_num->AddDirectory(kFALSE);
        hV26std_den->AddDirectory(kFALSE);
        TH1D* hV26gap     = new TH1D("hV26gap",     "", 600, 0., 600.);
        TH1D* hV26gapx    = new TH1D("hV26gapx",    "", 120, 0., 600.);
        TH1D* hV26gap_num = new TH1D("hV26gap_num", "", 600, 0., 600.);
        TH1D* hV26gap_den = new TH1D("hV26gap_den", "", 600, 0., 600.);
        hV26gap    ->AddDirectory(kFALSE);
        hV26gapx   ->AddDirectory(kFALSE);
        hV26gap_num->AddDirectory(kFALSE);
        hV26gap_den->AddDirectory(kFALSE);
        TH1D* hV28std     = new TH1D("hV28std",     "", 600, 0., 600.);
        TH1D* hV28stdx    = new TH1D("hV28stdx",    "", 120, 0., 600.);
        TH1D* hV28std_num = new TH1D("hV28std_num", "", 600, 0., 600.);
        TH1D* hV28std_den = new TH1D("hV28std_den", "", 600, 0., 600.);
        hV28std    ->AddDirectory(kFALSE);
        hV28stdx   ->AddDirectory(kFALSE);
        hV28std_num->AddDirectory(kFALSE);
        hV28std_den->AddDirectory(kFALSE);
        TH1D* hV28gap     = new TH1D("hV28gap",     "", 600, 0., 600.);
        TH1D* hV28gapx    = new TH1D("hV28gapx",    "", 120, 0., 600.);
        TH1D* hV28gap_num = new TH1D("hV28gap_num", "", 600, 0., 600.);
        TH1D* hV28gap_den = new TH1D("hV28gap_den", "", 600, 0., 600.);
        hV28gap    ->AddDirectory(kFALSE);
        hV28gapx   ->AddDirectory(kFALSE);
        hV28gap_num->AddDirectory(kFALSE);
        hV28gap_den->AddDirectory(kFALSE);



        //Open in file and get TTree
        //TFile* fin = TFile::Open(Form("/Volumes/Elements/ToyMCdata/datafiles/cumulant/%s/%s.root",version.c_str(),inFileName.c_str()));
        UShort_t mult = 0;
        double C2Nstd = 0., C4Nstd = 0., C6Nstd = 0., C8Nstd = 0., wC2Nstd = 0., wC4Nstd = 0., wC6Nstd = 0., wC8Nstd = 0.;
        double C2Ngap = 0., C4Ngap = 0., C6Ngap = 0., C8Ngap = 0., wC2Ngap = 0., wC4Ngap = 0., wC6Ngap = 0., wC8Ngap = 0.;
        //TFile* fin = TFile::Open(Form("%s/%s.root", getenv("OUTPUTDIR"), inFileName.c_str()));
        TFile* fin = TFile::Open(Form("%s.root", inFileName.c_str()));
        //Global
        TH1I* hmult = dynamic_cast<TH1I*>(fin->Get("hmult")->Clone()); 
        TH1D* hpt   = dynamic_cast<TH1D*>(fin->Get("hpt")->Clone()); 
        TH1D* heta  = dynamic_cast<TH1D*>(fin->Get("heta")->Clone()); 
        TH1D* hphi  = dynamic_cast<TH1D*>(fin->Get("hphi")->Clone());
        hmult->AddDirectory(kFALSE);
        hphi ->AddDirectory(kFALSE);
        heta ->AddDirectory(kFALSE);
        hpt  ->AddDirectory(kFALSE);
        //Tree
        TTree* tr = (TTree*) fin->Get("trFlow");
        tr->SetBranchAddress("mult", &mult);
        tr->SetBranchAddress("C2Nstd",  &C2Nstd);
        tr->SetBranchAddress("C4Nstd",  &C4Nstd);
        tr->SetBranchAddress("C6Nstd",  &C6Nstd);
        tr->SetBranchAddress("C8Nstd",  &C8Nstd);
        tr->SetBranchAddress("C2Ngap",  &C2Ngap);
        tr->SetBranchAddress("C4Ngap",  &C4Ngap);
        tr->SetBranchAddress("C6Ngap",  &C6Ngap);
        tr->SetBranchAddress("C8Ngap",  &C8Ngap);
        tr->SetBranchAddress("wC2Nstd", &wC2Nstd);
        tr->SetBranchAddress("wC4Nstd", &wC4Nstd);
        tr->SetBranchAddress("wC6Nstd", &wC6Nstd);
        tr->SetBranchAddress("wC8Nstd", &wC8Nstd);
        tr->SetBranchAddress("wC2Ngap", &wC2Ngap);
        tr->SetBranchAddress("wC4Ngap", &wC4Ngap);
        tr->SetBranchAddress("wC6Ngap", &wC6Ngap);
        tr->SetBranchAddress("wC8Ngap", &wC8Ngap);

        int nentries = tr->GetEntries();
        if(nEvt != -1) nentries = nEvt;
        tr->Print();

        int ievt = 0;
        std::vector< double > val(2);


        std::vector< double > c22std(600, 0.);
        std::vector< double > w22std(600, 0.);
        std::vector< double > c24std(600, 0.);
        std::vector< double > w24std(600, 0.);
        std::vector< double > c26std(600, 0.);
        std::vector< double > w26std(600, 0.);
        std::vector< double > c28std(600, 0.);
        std::vector< double > w28std(600, 0.);

        std::vector< std::vector< double > > c22std_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w22std_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > c24std_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w24std_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > c26std_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w26std_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > c28std_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w28std_err(10, std::vector<double>(600, 0.));

        std::vector< double > c22gap(600, 0.);
        std::vector< double > w22gap(600, 0.);
        std::vector< double > c24gap(600, 0.);
        std::vector< double > w24gap(600, 0.);
        std::vector< double > c26gap(600, 0.);
        std::vector< double > w26gap(600, 0.);
        std::vector< double > c28gap(600, 0.);
        std::vector< double > w28gap(600, 0.);

        std::vector< std::vector< double > > c22gap_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w22gap_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > c24gap_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w24gap_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > c26gap_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w26gap_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > c28gap_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w28gap_err(10, std::vector<double>(600, 0.));


        std::vector< double > c22stdx(120, 0.);
        std::vector< double > w22stdx(120, 0.);
        std::vector< double > c24stdx(120, 0.);
        std::vector< double > w24stdx(120, 0.);
        std::vector< double > c26stdx(120, 0.);
        std::vector< double > w26stdx(120, 0.);
        std::vector< double > c28stdx(120, 0.);
        std::vector< double > w28stdx(120, 0.);

        std::vector< std::vector< double > > c22std_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w22std_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > c24std_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w24std_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > c26std_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w26std_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > c28std_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w28std_errx(10, std::vector<double>(120, 0.));

        std::vector< double > c22gapx(120, 0.);
        std::vector< double > w22gapx(120, 0.);
        std::vector< double > c24gapx(120, 0.);
        std::vector< double > w24gapx(120, 0.);
        std::vector< double > c26gapx(120, 0.);
        std::vector< double > w26gapx(120, 0.);
        std::vector< double > c28gapx(120, 0.);
        std::vector< double > w28gapx(120, 0.);

        std::vector< std::vector< double > > c22gap_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w22gap_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > c24gap_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w24gap_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > c26gap_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w26gap_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > c28gap_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w28gap_errx(10, std::vector<double>(120, 0.));

        correlations::Result rN2;
        correlations::Result rN4;
        correlations::Result rN6;
        correlations::Result rN8;

        cumulant::Correlator c2;
        cumulant::Correlator c4;
        cumulant::Correlator c6;
        cumulant::Correlator c8;

        //Loop over events
        while(ievt < nentries)
        {
           tr->GetEntry(ievt);
           std::cout <<
           "\rtoymc.cxx::INFO:: ievt = " << ievt
           <<
           " ~~~> " << std::setprecision(3) << (double)((double)ievt / (double)nentries)*100  << " %"
           << std::flush;

           c22std[mult] += C2Nstd; 
           w22std[mult] += wC2Nstd;  
           c24std[mult] += C4Nstd; 
           w24std[mult] += wC4Nstd;  
           c26std[mult] += C6Nstd; 
           w26std[mult] += wC6Nstd;  
           c28std[mult] += C8Nstd; 
           w28std[mult] += wC8Nstd;  

           c22gap[mult] += C2Ngap; 
           w22gap[mult] += wC2Ngap;
           c24gap[mult] += C4Ngap; 
           w24gap[mult] += wC4Ngap;
           c26gap[mult] += C6Ngap; 
           w26gap[mult] += wC6Ngap;
           c28gap[mult] += C8Ngap; 
           w28gap[mult] += wC8Ngap;

           // --- Variance
           int ntest = rand() % 10;
           for(int itest = 0; itest < 10; ++itest)
           {
              if(itest != ntest)
              {
                 c22std_err[itest][mult] += C2Nstd; 
                 w22std_err[itest][mult] += wC2Nstd;
                 c24std_err[itest][mult] += C4Nstd; 
                 w24std_err[itest][mult] += wC4Nstd;
                 c26std_err[itest][mult] += C6Nstd; 
                 w26std_err[itest][mult] += wC6Nstd;
                 c28std_err[itest][mult] += C8Nstd; 
                 w28std_err[itest][mult] += wC8Nstd;

                 c22gap_err[itest][mult] += C2Ngap; 
                 w22gap_err[itest][mult] += wC2Ngap;
                 c24gap_err[itest][mult] += C4Ngap; 
                 w24gap_err[itest][mult] += wC4Ngap;      
                 c26gap_err[itest][mult] += C6Ngap; 
                 w26gap_err[itest][mult] += wC6Ngap;      
                 c28gap_err[itest][mult] += C8Ngap; 
                 w28gap_err[itest][mult] += wC8Ngap;      
              }
           }

           ++ievt;
        }

        std::cout << std::endl;
        delete tr;
        fin->Close();
        delete fin;

        //standard method
        for(int ibin = 0; ibin < hV22std->GetNbinsX(); ++ibin)
        {
           hV22std_num->SetBinContent(ibin+1, c22std[ibin]);
           hV22std_den->SetBinContent(ibin+1, w22std[ibin]);
           if(w22std[ibin] != 0.) c22std[ibin] = c22std[ibin]/w22std[ibin];
           else                   c22std[ibin] = 0.;
           
           hC22std->SetBinContent(ibin+1, c22std[ibin]);
           if(c22std[ibin] >= 0.) 
              hV22std->SetBinContent(ibin+1, TMath::Sqrt(c22std[ibin]));

           c22stdx[ibin/5] += c22std[ibin] * w22std[ibin];
           w22stdx[ibin/5] += w22std[ibin];
        }
        for(int ibin = 0; ibin < hV24std->GetNbinsX(); ++ibin)
        {
           hV24std_num->SetBinContent(ibin+1, -2*c22std[ibin]*c22std[ibin] + c24std[ibin]);
           hV24std_den->SetBinContent(ibin+1, w24std[ibin]);
           if(w24std[ibin] != 0.) c24std[ibin] = c24std[ibin]/w24std[ibin];
           else                   c24std[ibin] = 0.;
           
           hC24std->SetBinContent(ibin+1, -2*c22std[ibin]*c22std[ibin] + c24std[ibin]);
           if(2*c22std[ibin]*c22std[ibin] - c24std[ibin] >= 0.) 
              hV24std->SetBinContent(ibin+1, pow(2*c22std[ibin]*c22std[ibin] - c24std[ibin],1./4.));

           c24stdx[ibin/5] += c24std[ibin] * w24std[ibin];
           w24stdx[ibin/5] += w24std[ibin];
        }
        for(int ibin = 0; ibin < hV26std->GetNbinsX(); ++ibin)
        {
           hV26std_num->SetBinContent(ibin+1, c26std[ibin] - 9*c24std[ibin]*c22std[ibin] + 12*c22std[ibin]*c22std[ibin]*c22std[ibin]);
           hV26std_den->SetBinContent(ibin+1, w26std[ibin]);
           if(w26std[ibin] != 0.) c26std[ibin] = c26std[ibin]/w26std[ibin];
           else                   c26std[ibin] = 0.;
 
           hC26std->SetBinContent(ibin+1, c26std[ibin] - 9*c24std[ibin]*c22std[ibin] + 12*c22std[ibin]*c22std[ibin]*c22std[ibin]);
           if(c26std[ibin] - 9*c24std[ibin]*c22std[ibin] + 12*c22std[ibin]*c22std[ibin]*c22std[ibin] >= 0.) 
              hV26std->SetBinContent(ibin+1, pow((c26std[ibin] - 9*c24std[ibin]*c22std[ibin] + 12*c22std[ibin]*c22std[ibin]*c22std[ibin])/4., 1./6.));

           c26stdx[ibin/5] += c26std[ibin] * w26std[ibin];
           w26stdx[ibin/5] += w26std[ibin];
        }
        for(int ibin = 0; ibin < hV28std->GetNbinsX(); ++ibin)
        {
           hV28std_num->SetBinContent(ibin+1, c28std[ibin] - 16*c26std[ibin]*c22std[ibin] - 18*c24std[ibin]*c24std[ibin] + 144*c24std[ibin]*c22std[ibin]*c22std[ibin] - 144*c22std[ibin]*c22std[ibin]*c22std[ibin]*c22std[ibin]);
           hV28std_den->SetBinContent(ibin+1, w28std[ibin]);
           if(w28std[ibin] != 0.) c28std[ibin] = c28std[ibin]/w28std[ibin];
           else                   c28std[ibin] = 0.;
             
           hC28std->SetBinContent(ibin+1, c28std[ibin] - 16*c26std[ibin]*c22std[ibin] - 18*c24std[ibin]*c24std[ibin] + 144*c24std[ibin]*c22std[ibin]*c22std[ibin] - 144*c22std[ibin]*c22std[ibin]*c22std[ibin]*c22std[ibin]);
           if(-1*c28std[ibin] + 16*c26std[ibin]*c22std[ibin] + 18*c24std[ibin]*c24std[ibin] - 144*c24std[ibin]*c22std[ibin]*c22std[ibin] + 144*c22std[ibin]*c22std[ibin]*c22std[ibin]*c22std[ibin] >= 0.) 
              hV28std->SetBinContent(ibin+1, pow((-1*c28std[ibin] + 16*c26std[ibin]*c22std[ibin] + 18*c24std[ibin]*c24std[ibin] - 144*c24std[ibin]*c22std[ibin]*c22std[ibin] + 144*c22std[ibin]*c22std[ibin]*c22std[ibin]*c22std[ibin])/33.,1./8.));

           c28stdx[ibin/5] += c28std[ibin] * w28std[ibin];
           w28stdx[ibin/5] += w28std[ibin];
        }

        //gap method
        for(int ibin = 0; ibin < hV22gap->GetNbinsX(); ++ibin)
        {
           hV22gap_num->SetBinContent(ibin+1, c22gap[ibin]);
           hV22gap_den->SetBinContent(ibin+1, w22gap[ibin]);
           if(w22gap[ibin] != 0.) c22gap[ibin] = c22gap[ibin]/w22gap[ibin];
           else                   c22gap[ibin] = 0.;

           hC22gap->SetBinContent(ibin+1, c22gap[ibin]);
           if(c22gap[ibin] >= 0.) hV22gap->SetBinContent(ibin+1, TMath::Sqrt(c22gap[ibin]));

           c22gapx[ibin/5] += c22gap[ibin] * w22gap[ibin];
           w22gapx[ibin/5] += w22gap[ibin];
        }
        for(int ibin = 0; ibin < hV24gap->GetNbinsX(); ++ibin)
        {
           hV24gap_num->SetBinContent(ibin+1, -2*c22gap[ibin]*c22gap[ibin] + c24gap[ibin]);
           hV24gap_den->SetBinContent(ibin+1, w24gap[ibin]);
           if(w24gap[ibin] != 0.) c24gap[ibin] = c24gap[ibin]/w24gap[ibin];
           else                   c24gap[ibin] = 0.;
           hC24gap->SetBinContent(ibin+1, -2*c22gap[ibin]*c22gap[ibin] + c24gap[ibin]);
           if(2*c22gap[ibin]*c22gap[ibin] - c24gap[ibin] >= 0.)  hV24gap->SetBinContent(ibin+1, pow(2*c22gap[ibin]*c22gap[ibin] - c24gap[ibin],1./4.));

           c24gapx[ibin/5] += c24gap[ibin] * w24gap[ibin];
           w24gapx[ibin/5] += w24gap[ibin];
        }
        for(int ibin = 0; ibin < hV26gap->GetNbinsX(); ++ibin)
        {
           hV26gap_num->SetBinContent(ibin+1, c26gap[ibin] - 9*c24gap[ibin]*c22gap[ibin] + 12*c22gap[ibin]*c22gap[ibin]*c22gap[ibin]);
           hV26gap_den->SetBinContent(ibin+1, w26gap[ibin]);
           if(w26gap[ibin] != 0.) c26gap[ibin] = c26gap[ibin]/w26gap[ibin];
           else                   c26gap[ibin] = 0.;

           hC26gap->SetBinContent(ibin+1, c26gap[ibin] - 9*c24gap[ibin]*c22gap[ibin] + 12*c22gap[ibin]*c22gap[ibin]*c22gap[ibin]);
           if(c26gap[ibin] - 9*c24gap[ibin]*c22gap[ibin] + 12*c22gap[ibin]*c22gap[ibin]*c22gap[ibin] >= 0.) hV26gap->SetBinContent(ibin+1, pow((c26gap[ibin] - 9*c24gap[ibin]*c22gap[ibin] + 12*c22gap[ibin]*c22gap[ibin]*c22gap[ibin])/4., 1./6.));

           c26gapx[ibin/5] += c26gap[ibin] * w26gap[ibin];
           w26gapx[ibin/5] += w26gap[ibin];
        }
        for(int ibin = 0; ibin < hV28gap->GetNbinsX(); ++ibin)
        {
           hV28gap_num->SetBinContent(ibin+1, c28gap[ibin] - 16*c26gap[ibin]*c22gap[ibin] - 18*c24gap[ibin]*c24gap[ibin] + 144*c24gap[ibin]*c22gap[ibin]*c22gap[ibin] - 144*c22gap[ibin]*c22gap[ibin]*c22gap[ibin]*c22gap[ibin]);
           hV28gap_den->SetBinContent(ibin+1, w28gap[ibin]);
           if(w28gap[ibin] != 0.) c28gap[ibin] = c28gap[ibin]/w28gap[ibin];
           else                   c28gap[ibin] = 0.;

           hC28gap->SetBinContent(ibin+1, c28gap[ibin] - 16*c26gap[ibin]*c22gap[ibin] - 18*c24gap[ibin]*c24gap[ibin] + 144*c24gap[ibin]*c22gap[ibin]*c22gap[ibin] - 144*c22gap[ibin]*c22gap[ibin]*c22gap[ibin]*c22gap[ibin]);
           if(-1*c28gap[ibin] + 16*c26gap[ibin]*c22gap[ibin] + 18*c24gap[ibin]*c24gap[ibin] - 144*c24gap[ibin]*c22gap[ibin]*c22gap[ibin] + 144*c22gap[ibin]*c22gap[ibin]*c22gap[ibin]*c22gap[ibin] >= 0.) 
              hV28gap->SetBinContent(ibin+1, pow((-1*c28gap[ibin] + 16*c26gap[ibin]*c22gap[ibin] + 18*c24gap[ibin]*c24gap[ibin] - 144*c24gap[ibin]*c22gap[ibin]*c22gap[ibin] + 144*c22gap[ibin]*c22gap[ibin]*c22gap[ibin]*c22gap[ibin])/33.,1./8.));

           c28gapx[ibin/5] += c28gap[ibin] * w28gap[ibin];
           w28gapx[ibin/5] += w28gap[ibin];
        }


      
///////////REBIN
        //standard method
        for(int ibin = 0; ibin < hV22stdx->GetNbinsX(); ++ibin)
        {
           if(w22stdx[ibin] != 0.) c22stdx[ibin] = c22stdx[ibin]/w22stdx[ibin];
           else                    c22stdx[ibin] = 0.;

           hC22stdx->SetBinContent(ibin+1, c22stdx[ibin]);
           if(c22stdx[ibin] >= 0.) 
              hV22stdx->SetBinContent(ibin+1, TMath::Sqrt(c22stdx[ibin]));
        }
        for(int ibin = 0; ibin < hV24stdx->GetNbinsX(); ++ibin)
        {
           if(w24stdx[ibin] != 0.) c24stdx[ibin] = c24stdx[ibin]/w24stdx[ibin];
           else                    c24stdx[ibin] = 0.;

           hC24stdx->SetBinContent(ibin+1, -2*c22stdx[ibin]*c22stdx[ibin] + c24stdx[ibin]);
           if(2*c22stdx[ibin]*c22stdx[ibin] - c24stdx[ibin] >= 0.) 
              hV24stdx->SetBinContent(ibin+1, pow(2*c22stdx[ibin]*c22stdx[ibin] - c24stdx[ibin],1./4.));
        }
        for(int ibin = 0; ibin < hV26stdx->GetNbinsX(); ++ibin)
        {
           if(w26stdx[ibin] != 0.) c26stdx[ibin] = c26stdx[ibin]/w26stdx[ibin];
           else                    c26stdx[ibin] = 0.;

           hC26stdx->SetBinContent(ibin+1, c26stdx[ibin] - 9*c24stdx[ibin]*c22stdx[ibin] + 12*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin]);
           if(c26stdx[ibin] - 9*c24stdx[ibin]*c22stdx[ibin] + 12*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin] >= 0.) 
              hV26stdx->SetBinContent(ibin+1, pow((c26stdx[ibin] - 9*c24stdx[ibin]*c22stdx[ibin] + 12*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin])/4.,1./6.));
        }
        for(int ibin = 0; ibin < hV28stdx->GetNbinsX(); ++ibin)
        {
           if(w28stdx[ibin] != 0.) c28stdx[ibin] = c28stdx[ibin]/w28stdx[ibin];
           else                    c28stdx[ibin] = 0.;

           hC28stdx->SetBinContent(ibin+1, c28stdx[ibin] - 16*c26stdx[ibin]*c22stdx[ibin] - 18*c24stdx[ibin]*c24stdx[ibin] + 144*c24stdx[ibin]*c22stdx[ibin]*c22stdx[ibin] - 144*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin]);
           if(-1*c28stdx[ibin] + 16*c26stdx[ibin]*c22stdx[ibin] + 18*c24stdx[ibin]*c24stdx[ibin] - 144*c24stdx[ibin]*c22stdx[ibin]*c22stdx[ibin] + 144*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin] >= 0.) 
              hV28stdx->SetBinContent(ibin+1, pow((-1*c28stdx[ibin] + 16*c26stdx[ibin]*c22stdx[ibin] + 18*c24stdx[ibin]*c24stdx[ibin] - 144*c24stdx[ibin]*c22stdx[ibin]*c22stdx[ibin] + 144*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin])/33.,1./8.));
        }

        //gap method
        for(int ibin = 0; ibin < hV22gapx->GetNbinsX(); ++ibin)
        {
           if(w22gapx[ibin] != 0.) c22gapx[ibin] = c22gapx[ibin]/w22gapx[ibin];
           else                    c22gapx[ibin] = 0.;

           hC22gapx->SetBinContent(ibin+1, c22gapx[ibin]);
           if(c22gapx[ibin] >= 0.) 
              hV22gapx->SetBinContent(ibin+1, TMath::Sqrt(c22gapx[ibin]));
        }
        for(int ibin = 0; ibin < hV24gapx->GetNbinsX(); ++ibin)
        {
           if(w24gapx[ibin] != 0.) c24gapx[ibin] = c24gapx[ibin]/w24gapx[ibin];
           else                    c24gapx[ibin] = 0.;

           hC24gapx->SetBinContent(ibin+1, -2*c22gapx[ibin]*c22gapx[ibin] + c24gapx[ibin]);
           if(2*c22gapx[ibin]*c22gapx[ibin] - c24gapx[ibin] >= 0.)  
              hV24gapx->SetBinContent(ibin+1, pow(2*c22gapx[ibin]*c22gapx[ibin] - c24gapx[ibin],1./4.));
        }
        for(int ibin = 0; ibin < hV26gapx->GetNbinsX(); ++ibin)
        {
           if(w26gapx[ibin] != 0.) c26gapx[ibin] = c26gapx[ibin]/w26gapx[ibin];
           else                    c26gapx[ibin] = 0.;

           hC26gapx->SetBinContent(ibin+1, c26gapx[ibin] - 9*c24gapx[ibin]*c22gapx[ibin] + 12*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin]);
           if(c26gapx[ibin] - 9*c24gapx[ibin]*c22gapx[ibin] + 12*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin] >= 0.) 
              hV26gapx->SetBinContent(ibin+1, pow((c26gapx[ibin] - 9*c24gapx[ibin]*c22gapx[ibin] + 12*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin])/4.,1./6.));
        }
        for(int ibin = 0; ibin < hV28gapx->GetNbinsX(); ++ibin)
        {
           if(w28gapx[ibin] != 0.) c28gapx[ibin] = c28gapx[ibin]/w28gapx[ibin];
           else                    c28gapx[ibin] = 0.;

           hC28gapx->SetBinContent(ibin+1, c28gapx[ibin] - 16*c26gapx[ibin]*c22gapx[ibin] - 18*c24gapx[ibin]*c24gapx[ibin] + 144*c24gapx[ibin]*c22gapx[ibin]*c22gapx[ibin] - 144*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin]);
           if(-1*c28gapx[ibin] + 16*c26gapx[ibin]*c22gapx[ibin] + 18*c24gapx[ibin]*c24gapx[ibin] - 144*c24gapx[ibin]*c22gapx[ibin]*c22gapx[ibin] + 144*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin] >= 0.) 
              hV28gapx->SetBinContent(ibin+1, pow((-1*c28gapx[ibin] + 16*c26gapx[ibin]*c22gapx[ibin] + 18*c24gapx[ibin]*c24gapx[ibin] - 144*c24gapx[ibin]*c22gapx[ibin]*c22gapx[ibin] + 144*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin])/33.,1./8.));
        }

///////////

        double varC22std = 0.;
        double varC24std = 0.;
        double varC26std = 0.;
        double varC28std = 0.;
        double varC22gap = 0.;
        double varC24gap = 0.;
        double varC26gap = 0.;
        double varC28gap = 0.;
        double varV22std = 0.;
        double varV24std = 0.;
        double varV26std = 0.;
        double varV28std = 0.;
        double varV22gap = 0.;
        double varV24gap = 0.;
        double varV26gap = 0.;
        double varV28gap = 0.;

        double varC22stdx = 0.;
        double varC24stdx = 0.;
        double varC26stdx = 0.;
        double varC28stdx = 0.;
        double varC22gapx = 0.;
        double varC24gapx = 0.;
        double varC26gapx = 0.;
        double varC28gapx = 0.;
        double varV22stdx = 0.;
        double varV24stdx = 0.;
        double varV26stdx = 0.;
        double varV28stdx = 0.;
        double varV22gapx = 0.;
        double varV24gapx = 0.;
        double varV26gapx = 0.;
        double varV28gapx = 0.;

        for(int itest = 0; itest < 10; ++itest)
        {
           for(int ibin = 0; ibin < hV22std->GetNbinsX(); ++ibin)
           {
              if(w22std_err[itest][ibin] != 0.) c22std_err[itest][ibin] = c22std_err[itest][ibin]/w22std_err[itest][ibin];
              else                              c22std_err[itest][ibin] = 0.;

              c22std_errx[itest][ibin/5] += c22std_err[itest][ibin] * w22std_err[itest][ibin];
              w22std_errx[itest][ibin/5] += w22std_err[itest][ibin];
           }
           for(int ibin = 0; ibin < hV24std->GetNbinsX(); ++ibin)
           {
              if(w24std_err[itest][ibin] != 0.) c24std_err[itest][ibin] = c24std_err[itest][ibin]/w24std_err[itest][ibin];
              else                              c24std_err[itest][ibin] = 0.;
              c24std_err[itest][ibin] -= 2*c22std_err[itest][ibin]*c22std_err[itest][ibin];

              c24std_errx[itest][ibin/5] += c24std_err[itest][ibin] * w24std_err[itest][ibin];
              w24std_errx[itest][ibin/5] += w24std_err[itest][ibin];
           }
           for(int ibin = 0; ibin < hV26std->GetNbinsX(); ++ibin)
           {
              if(w26std_err[itest][ibin] != 0.) c26std_err[itest][ibin] = c26std_err[itest][ibin]/w26std_err[itest][ibin];
              else                              c26std_err[itest][ibin] = 0.;
              c26std_err[itest][ibin] = c26std_err[itest][ibin] - 9*c24std_err[itest][ibin]*c22std_err[itest][ibin] + 12*c22std_err[itest][ibin]*c22std_err[itest][ibin]*c22std_err[itest][ibin];

              c26std_errx[itest][ibin/5] += c26std_err[itest][ibin] * w26std_err[itest][ibin];
              w26std_errx[itest][ibin/5] += w26std_err[itest][ibin];
           }
           for(int ibin = 0; ibin < hV28std->GetNbinsX(); ++ibin)
           {
              if(w28std_err[itest][ibin] != 0.) c28std_err[itest][ibin] = c28std_err[itest][ibin]/w28std_err[itest][ibin];
              else                              c28std_err[itest][ibin] = 0.;
              c28std_err[itest][ibin] = c28std_err[itest][ibin] - 16*c26std_err[itest][ibin]*c22std_err[itest][ibin] 
                                      - 18*c24std_err[itest][ibin]*c24std_err[itest][ibin] + 144*c24std_err[itest][ibin]*c22std_err[itest][ibin]*c22std_err[itest][ibin] 
                                      - 144*c22std_err[itest][ibin]*c22std_err[itest][ibin]*c22std_err[itest][ibin]*c22std_err[itest][ibin];

              c28std_errx[itest][ibin/5] += c28std_err[itest][ibin] * w28std_err[itest][ibin];
              w28std_errx[itest][ibin/5] += w28std_err[itest][ibin];
           }

           for(int ibin = 0; ibin < hV22gap->GetNbinsX(); ++ibin)
           {
              if(w22gap_err[itest][ibin] != 0.) c22gap_err[itest][ibin] = c22gap_err[itest][ibin]/w22gap_err[itest][ibin];
              else                              c22gap_err[itest][ibin] = 0.;

              c22gap_errx[itest][ibin/5] += c22gap_err[itest][ibin] * w22gap_err[itest][ibin];
              w22gap_errx[itest][ibin/5] += w22gap_err[itest][ibin];
           }
           for(int ibin = 0; ibin < hV24gap->GetNbinsX(); ++ibin)
           {
              if(w24gap_err[itest][ibin] != 0.) c24gap_err[itest][ibin] = c24gap_err[itest][ibin]/w24gap_err[itest][ibin];
              else                              c24gap_err[itest][ibin] = 0.;
              c24gap_err[itest][ibin] -= 2*c22gap_err[itest][ibin]*c22gap_err[itest][ibin];

              c24gap_errx[itest][ibin/5] += c24gap_err[itest][ibin] * w24gap_err[itest][ibin];
              w24gap_errx[itest][ibin/5] += w24gap_err[itest][ibin];
           }
           for(int ibin = 0; ibin < hV26gap->GetNbinsX(); ++ibin)
           {
              if(w26gap_err[itest][ibin] != 0.) c26gap_err[itest][ibin] = c26gap_err[itest][ibin]/w26gap_err[itest][ibin];
              else                              c26gap_err[itest][ibin] = 0.;
              c26gap_err[itest][ibin] = c26gap_err[itest][ibin] - 9*c24gap_err[itest][ibin]*c22gap_err[itest][ibin] + 12*c22gap_err[itest][ibin]*c22gap_err[itest][ibin]*c22gap_err[itest][ibin];

              c26gap_errx[itest][ibin/5] += c26gap_err[itest][ibin] * w26gap_err[itest][ibin];
              w26gap_errx[itest][ibin/5] += w26gap_err[itest][ibin];
           }
           for(int ibin = 0; ibin < hV28gap->GetNbinsX(); ++ibin)
           {
              if(w28gap_err[itest][ibin] != 0.) c28gap_err[itest][ibin] = c28gap_err[itest][ibin]/w28gap_err[itest][ibin];
              else                              c28gap_err[itest][ibin] = 0.;
              c28gap_err[itest][ibin] = c28gap_err[itest][ibin] - 16*c26gap_err[itest][ibin]*c22gap_err[itest][ibin] 
                                      - 18*c24gap_err[itest][ibin]*c24gap_err[itest][ibin] + 144*c24gap_err[itest][ibin]*c22gap_err[itest][ibin]*c22gap_err[itest][ibin] 
                                      - 144*c22gap_err[itest][ibin]*c22gap_err[itest][ibin]*c22gap_err[itest][ibin]*c22gap_err[itest][ibin];

              c28gap_errx[itest][ibin/5] += c28gap_err[itest][ibin] * w28gap_err[itest][ibin];
              w28gap_errx[itest][ibin/5] += w28gap_err[itest][ibin];
           }
        }

        for(int itest = 0; itest < 10; ++itest)
        {
           for(int ibin = 0; ibin < hV22stdx->GetNbinsX(); ++ibin)
           {
               if(w22std_errx[itest][ibin] != 0.) c22std_errx[itest][ibin] /= w22std_errx[itest][ibin];
               if(w24std_errx[itest][ibin] != 0.) c24std_errx[itest][ibin] /= w24std_errx[itest][ibin];
               if(w26std_errx[itest][ibin] != 0.) c26std_errx[itest][ibin] /= w26std_errx[itest][ibin];
               if(w28std_errx[itest][ibin] != 0.) c28std_errx[itest][ibin] /= w28std_errx[itest][ibin];

               if(w22gap_errx[itest][ibin] != 0.) c22gap_errx[itest][ibin] /= w22gap_errx[itest][ibin];
               if(w24gap_errx[itest][ibin] != 0.) c24gap_errx[itest][ibin] /= w24gap_errx[itest][ibin];
               if(w26gap_errx[itest][ibin] != 0.) c26gap_errx[itest][ibin] /= w26gap_errx[itest][ibin];
               if(w28gap_errx[itest][ibin] != 0.) c28gap_errx[itest][ibin] /= w28gap_errx[itest][ibin];
           }
        }

        for(int ibin = 0; ibin < hV24gap->GetNbinsX(); ++ibin)
        {
           varC22std = 0.;
           varC24std = 0.;
           varC26std = 0.;
           varC28std = 0.;
           varC22gap = 0.;
           varC24gap = 0.;
           varC26gap = 0.;
           varC28gap = 0.;
           varV22std = 0.;
           varV24std = 0.;
           varV26std = 0.;
           varV28std = 0.;
           varV22gap = 0.;
           varV24gap = 0.;
           varV26gap = 0.;
           varV28gap = 0.;
           for(int itest = 0; itest < 10; ++itest)
           {
              varC22std += TMath::Power(c22std_err[itest][ibin] - c22std[ibin],2);   
              varC24std += TMath::Power(c24std_err[itest][ibin] - (c24std[ibin] - 2*c22std[ibin]*c22std[ibin]), 2); 
              varC26std += TMath::Power(c26std_err[itest][ibin] - (c26std[ibin] - 9*c24std[ibin]*c22std[ibin] + 12*c22std[ibin]*c22std[ibin]*c22std[ibin]), 2); 
              varC28std += TMath::Power(c28std_err[itest][ibin] - (c28std[ibin] - 18*c24std[ibin]*c24std[ibin] + 144*c24std[ibin]*c22std[ibin]*c22std[ibin] - 144*c22std[ibin]*c22std[ibin]*c22std[ibin]*c22std[ibin]), 2);
 
              varC22gap += TMath::Power(c22gap_err[itest][ibin] - c22gap[ibin],2); 
              varC24gap += TMath::Power(c24gap_err[itest][ibin] - (c24gap[ibin] - 2*c22gap[ibin]*c22gap[ibin]), 2);
              varC26gap += TMath::Power(c26gap_err[itest][ibin] - (c26gap[ibin] - 9*c24gap[ibin]*c22gap[ibin] + 12*c22gap[ibin]*c22gap[ibin]*c22gap[ibin] ), 2); 
              varC28gap += TMath::Power(c28gap_err[itest][ibin] - (c28gap[ibin] - 18*c24gap[ibin]*c24gap[ibin] + 144*c24gap[ibin]*c22gap[ibin]*c22gap[ibin] - 144*c22gap[ibin]*c22gap[ibin]*c22gap[ibin]*c22gap[ibin]), 2);


              if(c22std_err[itest][ibin] >= 0. && c22std[ibin] >= 0.) 
                 varV22std += TMath::Power(TMath::Sqrt(c22std_err[itest][ibin]) - TMath::Sqrt(c22std[ibin]),2);   
              if(c24std_err[itest][ibin] <= 0. && c24std[ibin] - 2*c22std[ibin]*c22std[ibin] <= 0.) 
                 varV24std += TMath::Power(TMath::Power(-1*c24std_err[itest][ibin],1./4.) 
                                          -TMath::Power(-1*c24std[ibin] + 2*c22std[ibin]*c22std[ibin],1./4.), 2);
              if(c26std_err[itest][ibin] >= 0. && c26std[ibin] - 9*c24std[ibin]*c22std[ibin] + 12*c22std[ibin]*c22std[ibin]*c22std[ibin] >= 0.) 
                 varV26std += TMath::Power(TMath::Power(c26std_err[itest][ibin]/4.,1./6.) 
                                          -TMath::Power((c26std[ibin] - 9*c24std[ibin]*c22std[ibin] + 12*c22std[ibin]*c22std[ibin]*c22std[ibin])/4.,1./6.), 2);
              if(c28std_err[itest][ibin] <= 0. && c28std[ibin] - 18*c24std[ibin]*c24std[ibin] + 144*c24std[ibin]*c22std[ibin]*c22std[ibin] - 144*c22std[ibin]*c22std[ibin]*c22std[ibin]*c22std[ibin] <= 0.) 
                 varV28std += TMath::Power(TMath::Power(-1*c28std_err[itest][ibin]/33.,1./8.) 
                                          -TMath::Power(-1*(c28std[ibin] - 18*c24std[ibin]*c24std[ibin] + 144*c24std[ibin]*c22std[ibin]*c22std[ibin] - 144*c22std[ibin]*c22std[ibin]*c22std[ibin]*c22std[ibin])/33.,1./8.), 2);
 
              if(c22gap_err[itest][ibin] >= 0. && c22gap[ibin] >= 0.) 
                 varV22gap += TMath::Power(TMath::Sqrt(c22gap_err[itest][ibin]) - TMath::Sqrt(c22gap[ibin]),2); 
              if(c24gap_err[itest][ibin] <= 0. && c24gap[ibin] - 2*c22gap[ibin]*c22gap[ibin] <= 0.) 
                 varV24gap += TMath::Power(TMath::Power(-1*c24gap_err[itest][ibin],1./4.)
                                          -TMath::Power(-1*c24gap[ibin] + 2*c22gap[ibin]*c22gap[ibin], 1./4.), 2);
              if(c26gap_err[itest][ibin] >= 0. && c26gap[ibin] - 9*c24gap[ibin]*c22gap[ibin] + 12*c22gap[ibin]*c22gap[ibin]*c22gap[ibin] >= 0.) 
                 varV26gap += TMath::Power(TMath::Power(c26gap_err[itest][ibin]/4.,1./6.) 
                                          -TMath::Power((c26gap[ibin] - 9*c24gap[ibin]*c22gap[ibin] + 12*c22gap[ibin]*c22gap[ibin]*c22gap[ibin])/4.,1./6.), 2);
              if(c28gap_err[itest][ibin] <= 0. && c28gap[ibin] - 18*c24gap[ibin]*c24gap[ibin] + 144*c24gap[ibin]*c22gap[ibin]*c22gap[ibin] - 144*c22gap[ibin]*c22gap[ibin]*c22gap[ibin]*c22gap[ibin] <= 0.) 
                 varV28gap += TMath::Power(TMath::Power(-1*c28gap_err[itest][ibin]/33.,1./8.) 
                                          -TMath::Power(-1*(c28gap[ibin] - 18*c24gap[ibin]*c24gap[ibin] + 144*c24gap[ibin]*c22gap[ibin]*c22gap[ibin] - 144*c22gap[ibin]*c22gap[ibin]*c22gap[ibin]*c22gap[ibin])/33.,1./8.), 2);
           }

           varC22std *= (10.-1.)/10.;
           varC24std *= (10.-1.)/10.;
           varC26std *= (10.-1.)/10.;
           varC28std *= (10.-1.)/10.;
           varC22gap *= (10.-1.)/10.;
           varC24gap *= (10.-1.)/10.;
           varC26gap *= (10.-1.)/10.;
           varC28gap *= (10.-1.)/10.;
           varV22std *= (10.-1.)/10.;
           varV24std *= (10.-1.)/10.;
           varV26std *= (10.-1.)/10.;
           varV28std *= (10.-1.)/10.;
           varV22gap *= (10.-1.)/10.;
           varV24gap *= (10.-1.)/10.;
           varV26gap *= (10.-1.)/10.;
           varV28gap *= (10.-1.)/10.;


           hV22std->SetBinError(ibin+1,TMath::Sqrt(varV22std)); 
           hV24std->SetBinError(ibin+1,TMath::Sqrt(varV24std));
           hV26std->SetBinError(ibin+1,TMath::Sqrt(varV26std));
           hV28std->SetBinError(ibin+1,TMath::Sqrt(varV28std));
           hV22gap->SetBinError(ibin+1,TMath::Sqrt(varV22gap));
           hV24gap->SetBinError(ibin+1,TMath::Sqrt(varV24gap));
           hV26gap->SetBinError(ibin+1,TMath::Sqrt(varV26gap));
           hV28gap->SetBinError(ibin+1,TMath::Sqrt(varV28gap));

           hC22std->SetBinError(ibin+1,TMath::Sqrt(varC22std)); 
           hC24std->SetBinError(ibin+1,TMath::Sqrt(varC24std));
           hC26std->SetBinError(ibin+1,TMath::Sqrt(varC26std));
           hC28std->SetBinError(ibin+1,TMath::Sqrt(varC28std));
           hC22gap->SetBinError(ibin+1,TMath::Sqrt(varC22gap));
           hC24gap->SetBinError(ibin+1,TMath::Sqrt(varC24gap));
           hC26gap->SetBinError(ibin+1,TMath::Sqrt(varC26gap));
           hC28gap->SetBinError(ibin+1,TMath::Sqrt(varC28gap));

           hV22std_num->SetBinError(ibin+1,TMath::Sqrt(varC22std)); 
           hV24std_num->SetBinError(ibin+1,TMath::Sqrt(varC24std));
           hV26std_num->SetBinError(ibin+1,TMath::Sqrt(varC26std));
           hV28std_num->SetBinError(ibin+1,TMath::Sqrt(varC28std));
           hV22gap_num->SetBinError(ibin+1,TMath::Sqrt(varC22gap));
           hV24gap_num->SetBinError(ibin+1,TMath::Sqrt(varC24gap));
           hV26gap_num->SetBinError(ibin+1,TMath::Sqrt(varC26gap));
           hV28gap_num->SetBinError(ibin+1,TMath::Sqrt(varC28gap));

           hV22std_den->SetBinError(ibin+1,TMath::Sqrt(w22std[ibin])); 
           hV24std_den->SetBinError(ibin+1,TMath::Sqrt(w24std[ibin]));
           hV26std_den->SetBinError(ibin+1,TMath::Sqrt(w26std[ibin]));
           hV28std_den->SetBinError(ibin+1,TMath::Sqrt(w28std[ibin]));
           hV22gap_den->SetBinError(ibin+1,TMath::Sqrt(w22gap[ibin]));
           hV24gap_den->SetBinError(ibin+1,TMath::Sqrt(w24gap[ibin]));
           hV26gap_den->SetBinError(ibin+1,TMath::Sqrt(w26gap[ibin]));
           hV28gap_den->SetBinError(ibin+1,TMath::Sqrt(w28gap[ibin]));
        }
        for(int ibin = 0; ibin < hV24gapx->GetNbinsX(); ++ibin)
        {
           varC22stdx = 0.;
           varC24stdx = 0.;
           varC26stdx = 0.;
           varC28stdx = 0.;
           varC22gapx = 0.;
           varC24gapx = 0.;
           varC26gapx = 0.;
           varC28gapx = 0.;
           varV22stdx = 0.;
           varV24stdx = 0.;
           varV26stdx = 0.;
           varV28stdx = 0.;
           varV22gapx = 0.;
           varV24gapx = 0.;
           varV26gapx = 0.;
           varV28gapx = 0.;
           for(int itest = 0; itest < 10; ++itest)
           {
              varC22stdx += TMath::Power(c22std_errx[itest][ibin] - c22stdx[ibin],2);   
              varC24stdx += TMath::Power(c24std_errx[itest][ibin] - (c24stdx[ibin] - 2*c22stdx[ibin]*c22stdx[ibin]), 2);
              varC26stdx += TMath::Power(c26std_errx[itest][ibin] - (c26stdx[ibin] - 9*c24stdx[ibin]*c22stdx[ibin] + 12*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin]), 2); 
              varC28stdx += TMath::Power(c28std_errx[itest][ibin] - (c28stdx[ibin] - 18*c24stdx[ibin]*c24stdx[ibin] + 144*c24stdx[ibin]*c22stdx[ibin]*c22stdx[ibin] - 144*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin]), 2);
 
              varC22gapx += TMath::Power(c22gap_errx[itest][ibin] - c22gapx[ibin],2); 
              varC24gapx += TMath::Power(c24gap_errx[itest][ibin] - (c24gapx[ibin] - 2*c22gapx[ibin]*c22gapx[ibin]), 2);
              varC26gapx += TMath::Power(c26gap_errx[itest][ibin] - (c26gapx[ibin] - 9*c24gapx[ibin]*c22gapx[ibin] + 12*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin] ), 2); 
              varC28gapx += TMath::Power(c28gap_errx[itest][ibin] - (c28gapx[ibin] - 18*c24gapx[ibin]*c24gapx[ibin] + 144*c24gapx[ibin]*c22gapx[ibin]*c22gapx[ibin] - 144*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin]), 2);


              if(c22std_errx[itest][ibin] >= 0. && c22stdx[ibin] >= 0.) 
                 varV22stdx += TMath::Power(TMath::Sqrt(c22std_errx[itest][ibin]) - TMath::Sqrt(c22stdx[ibin]),2);   
              if(c24std_errx[itest][ibin] <= 0. && c24stdx[ibin] - 2*c22stdx[ibin]*c22stdx[ibin] <= 0.) 
                 varV24stdx += TMath::Power(TMath::Power(-1*c24std_errx[itest][ibin],1./4.) 
                                           -TMath::Power(-1*c24stdx[ibin] + 2*c22stdx[ibin]*c22stdx[ibin],1./4.), 2);
              if(c26std_errx[itest][ibin] >= 0. && c26stdx[ibin] - 9*c24stdx[ibin]*c22stdx[ibin] + 12*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin] >= 0.) 
                 varV26stdx += TMath::Power(TMath::Power(c26std_errx[itest][ibin]/4.,1./6.) 
                                          -TMath::Power((c26stdx[ibin] - 9*c24stdx[ibin]*c22stdx[ibin] + 12*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin])/4.,1./6.), 2);
              if(c28std_errx[itest][ibin] <= 0. && c28stdx[ibin] - 18*c24stdx[ibin]*c24stdx[ibin] + 144*c24stdx[ibin]*c22stdx[ibin]*c22stdx[ibin] - 144*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin] <= 0.) 
                 varV28stdx += TMath::Power(TMath::Power(-1*c28std_errx[itest][ibin]/33.,1./8.) 
                                          -TMath::Power(-1*(c28stdx[ibin] - 18*c24stdx[ibin]*c24stdx[ibin] + 144*c24stdx[ibin]*c22stdx[ibin]*c22stdx[ibin] - 144*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin]*c22stdx[ibin])/33.,1./8.), 2);
 
              if(c22gap_errx[itest][ibin] >= 0. && c22gapx[ibin] >= 0.) 
                 varV22gapx += TMath::Power(TMath::Sqrt(c22gap_errx[itest][ibin]) - TMath::Sqrt(c22gapx[ibin]),2); 
              if(c24gap_errx[itest][ibin] <= 0. && c24gapx[ibin] - 2*c22gapx[ibin]*c22gapx[ibin] <= 0.) 
                 varV24gapx += TMath::Power(TMath::Power(-1*c24gap_errx[itest][ibin],1./4.)
                                           -TMath::Power(-1*c24gapx[ibin] + 2*c22gapx[ibin]*c22gapx[ibin], 1./4.), 2);
              if(c26gap_errx[itest][ibin] >= 0. && c26gapx[ibin] - 9*c24gapx[ibin]*c22gapx[ibin] + 12*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin] >= 0.) 
                 varV26gapx += TMath::Power(TMath::Power(c26gap_errx[itest][ibin]/4.,1./6.) 
                                          -TMath::Power((c26gapx[ibin] - 9*c24gapx[ibin]*c22gapx[ibin] + 12*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin])/4.,1./6.), 2);
              if(c28gap_errx[itest][ibin] <= 0. && c28gapx[ibin] - 18*c24gapx[ibin]*c24gapx[ibin] + 144*c24gapx[ibin]*c22gapx[ibin]*c22gapx[ibin] - 144*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin] <= 0.) 
                 varV28gapx += TMath::Power(TMath::Power(-1*c28gap_errx[itest][ibin]/33.,1./8.) 
                                          -TMath::Power(-1*(c28gapx[ibin] - 18*c24gapx[ibin]*c24gapx[ibin] + 144*c24gapx[ibin]*c22gapx[ibin]*c22gapx[ibin] - 144*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin]*c22gapx[ibin])/33.,1./8.), 2);
           }

           varC22stdx *= (10.-1.)/10.;
           varC24stdx *= (10.-1.)/10.;
           varC26stdx *= (10.-1.)/10.;
           varC28stdx *= (10.-1.)/10.;
           varC22gapx *= (10.-1.)/10.;
           varC24gapx *= (10.-1.)/10.;
           varC26gapx *= (10.-1.)/10.;
           varC28gapx *= (10.-1.)/10.;
           varV22stdx *= (10.-1.)/10.;
           varV24stdx *= (10.-1.)/10.;
           varV26stdx *= (10.-1.)/10.;
           varV28stdx *= (10.-1.)/10.;
           varV22gapx *= (10.-1.)/10.;
           varV24gapx *= (10.-1.)/10.;
           varV26gapx *= (10.-1.)/10.;
           varV28gapx *= (10.-1.)/10.;


           hC22stdx->SetBinError(ibin+1,TMath::Sqrt(varC22stdx)); 
           hC24stdx->SetBinError(ibin+1,TMath::Sqrt(varC24stdx));
           hC26stdx->SetBinError(ibin+1,TMath::Sqrt(varC26stdx));
           hC28stdx->SetBinError(ibin+1,TMath::Sqrt(varC28stdx));
           hC22gapx->SetBinError(ibin+1,TMath::Sqrt(varC22gapx));
           hC24gapx->SetBinError(ibin+1,TMath::Sqrt(varC24gapx));
           hC26gapx->SetBinError(ibin+1,TMath::Sqrt(varC26gapx));
           hC28gapx->SetBinError(ibin+1,TMath::Sqrt(varC28gapx));

           hV22stdx->SetBinError(ibin+1,TMath::Sqrt(varV22stdx)); 
           hV24stdx->SetBinError(ibin+1,TMath::Sqrt(varV24stdx));
           hV26stdx->SetBinError(ibin+1,TMath::Sqrt(varV26stdx));
           hV28stdx->SetBinError(ibin+1,TMath::Sqrt(varV28stdx));
           hV22gapx->SetBinError(ibin+1,TMath::Sqrt(varV22gapx));
           hV24gapx->SetBinError(ibin+1,TMath::Sqrt(varV24gapx));
           hV26gapx->SetBinError(ibin+1,TMath::Sqrt(varV26gapx));
           hV28gapx->SetBinError(ibin+1,TMath::Sqrt(varV28gapx));
        }

        std::cout << "Writting..." << std::endl;
        TFile* fout = new TFile(Form("%s/%s.root", getenv("OUTPUTDIR"), outFileName.c_str()), "recreate");

        hmult->Write();
        hpt  ->Write();
        heta ->Write();
        hphi ->Write();

        hC22std    ->Write();
        hC22stdx   ->Write();
        hV22std    ->Write();
        hV22stdx   ->Write();
        hV22std_den->Write();
        hV22std_num->Write();
        hC22gap    ->Write();
        hC22gapx   ->Write();
        hV22gap    ->Write();
        hV22gapx   ->Write();
        hV22gap_den->Write();
        hV22gap_num->Write();

        hC24std    ->Write();
        hC24stdx   ->Write();
        hV24std    ->Write();
        hV24stdx   ->Write();
        hV24std_den->Write();
        hV24std_num->Write();
        hC24gap    ->Write();
        hC24gapx   ->Write();
        hV24gap    ->Write();
        hV24gapx   ->Write();
        hV24gap_den->Write();
        hV24gap_num->Write();

        hC26std    ->Write();
        hC26stdx   ->Write();
        hV26std    ->Write();
        hV26stdx   ->Write();
        hV26std_den->Write();
        hV26std_num->Write();
        hC26gap    ->Write();
        hC26gapx   ->Write();
        hV26gap    ->Write();
        hV26gapx   ->Write();
        hV26gap_den->Write();
        hV26gap_num->Write();

        hC28std    ->Write();
        hC28stdx   ->Write();
        hV28std    ->Write();
        hV28stdx   ->Write();
        hV28std_den->Write();
        hV28std_num->Write();
        hC28gap    ->Write();
        hC28gapx   ->Write();
        hV28gap    ->Write();
        hV28gapx   ->Write();
        hV28gap_den->Write();
        hV28gap_num->Write();

        fout->Close();

        delete fout;
}
