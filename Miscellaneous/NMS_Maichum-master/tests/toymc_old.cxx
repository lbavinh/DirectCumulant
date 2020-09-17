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
#include "ToyMC/ToyMCGenerator.h"
#include "ToyMC/BranchReader.h"
#include "ToyMC/TClonesArrayReader.h"

#include <TFile.h>
#include <TDirectory.h>
#include <TH1.h>
#include <TSpline.h>
#include <TF1.h>

using namespace std;

void checkParam(int argc, char** argv);
void createDistributions();

void generate(std::string system,  std::string partDist, std::string vnDist,
              double ptMin,        double ptMax,
              double etaMin,       double etaMax,
              double multMin,      double multMax,
              int    nEvt,         bool   vnFluct,
              std::string version, std::string outFileName);
void genAndAnalyze(int harm,
                   std::string system,  std::string partDist, std::string vnDist,
                   double ptMin,        double ptMax,
                   double etaMin,       double etaMax,
                   double multMin,      double multMax,
                   int    nEvt,         bool   vnFluct,
                   std::string version, std::string outFileName);
void genAndAnalyzeTree(int harm,
                       std::string system,  std::string partDist, std::string vnDist,
                       double ptMin,        double ptMax,
                       double etaMin,       double etaMax,
                       double multMin,      double multMax,
                       int    nEvt,         bool   vnFluct,
                       std::string version, std::string outFileName);
void analyze(int harm,
             std::string version, std::string inFileName,
             std::string outFileName,
             int nEvt = -1);

void analyzeTree(std::string version, std::string inFileName,
                 std::string outFileName,
                 int nEvt = -1);

int 
main(int argc, char** argv) {

	checkParam(argc, argv);

	loguru::set_thread_name("MAIN");
	// logs everything to the debug.log file every run
	loguru::add_file("bin/debug.log", loguru::Truncate, loguru::Verbosity_MAX);

	// sometimes the "stream" form of the logger is more convenient, use LOG_S( LEVEL ) << "MESSAGE";
	// No need for an endl at the end of a line


	cmdline::parser parser;

	parser.add("generate", '\0', "generate ToyMc");
	parser.add("analyze", '\0', "analyze ToyMc output");
	parser.add("analyzeToyMCout", '\0', "analyze tree ToyMc output");
	parser.add<int>("nevents", '\0', "number of events to generate/analyze", false, -1);
	parser.add<int>("harm", '\0', "harmonic to generate/analyze", false, 2);
	parser.add<double>("ptmin", '\0', "ptmin to generate/analyze", false, 0.3);
	parser.add<double>("ptmax", '\0', "ptmax to generate/analyze", false, 3.0);
	parser.add<double>("etamin", '\0', "etamin to generate/analyze", false, -2.4);
	parser.add<double>("etamax", '\0', "etamax to generate/analyze", false, 2.4);
	parser.add<double>("multmin", '\0', "multmin to generate/analyze", false, 10.);
	parser.add<double>("multmax", '\0', "multmax to generate/analyze", false, 40.);
	parser.add<std::string>("system", '\0', "system to run", false, "PbPb");
	parser.add<std::string>("kindist", '\0', "particle kin distributions", false, "const");
	parser.add<std::string>("vndist", '\0', "vn distributions", false, "const");
	parser.add<std::string>("version", '\0', "version", false, "v6");
	parser.add<std::string>("output", '\0', "output file name", false, "output_toymc");
	parser.add<std::string>("input", '\0', "input file name", false, "");
	parser.add<bool>("isVnfluct", '\0', "etamax to generate/analyze", false, false);

	parser.parse_check( argc, argv );

	if ( parser.exist( "generate" ) && !parser.exist( "analyze" )  ){
		generate( parser.get<std::string>( "system" ),
                          parser.get<std::string>( "kindist" ),
                          parser.get<std::string>( "vndist" ),
                          parser.get<double>( "ptmin" ),
                          parser.get<double>( "ptmax" ),
                          parser.get<double>( "etamin" ),
                          parser.get<double>( "etamax" ),
                          parser.get<double>( "multmin" ),
                          parser.get<double>( "multmax" ),
                          parser.get<int>( "nevents" ),
                          parser.get<bool>( "isVnfluct" ),
                          parser.get<std::string>( "version" ),
                          parser.get<std::string>( "output" ) );
        }
	else if ( parser.exist( "analyze" ) && !parser.exist( "generate" ) ){
                if( parser.exist( "analyzeToyMCout" ) ){
			analyze( parser.get<int>( "harm" ),
	                         parser.get<std::string>( "version" ),
	                         parser.get<std::string>( "input" ),
	                         parser.get<std::string>( "output" ),
	                         parser.get<int>( "nevents" ) );
                }	
                else {
			analyzeTree( parser.get<std::string>( "version" ),
	                             parser.get<std::string>( "input" ),
	                             parser.get<std::string>( "output" ),
	                             parser.get<int>( "nevents" ) );
                }	
        }
	else if ( parser.exist( "generate" ) && parser.exist( "analyze" ) ){
        	genAndAnalyzeTree( parser.get<int>( "harm" ),
		                   parser.get<std::string>( "system" ),
                                   parser.get<std::string>( "kindist" ),
                                   parser.get<std::string>( "vndist" ),
                                   parser.get<double>( "ptmin" ),
                                   parser.get<double>( "ptmax" ),
                                   parser.get<double>( "etamin" ),
                                   parser.get<double>( "etamax" ),
                                   parser.get<double>( "multmin" ),
                                   parser.get<double>( "multmax" ),
                                   parser.get<int>( "nevents" ),
                                   parser.get<bool>( "isVnfluct" ),
                                   parser.get<std::string>( "version" ),
                                   parser.get<std::string>( "output" ) );
        }
	else {
		std::cout << parser.usage() << endl;
	}
        return 0; 

        //analyze(2,"v6","ToyMCTTree_constVn_const_FlowFluct_ntrk200_10k",
        //        "ToyMCREsults_v2_flowfluc");
        //analyze(2,"v5","ToyMCTTree_constVn_const_full",
        //        "ToyMCREsults_v5_noflowfluc_full_test2");

        //analyze(2,"v6","ToyMCTTree_constVn_const_FlowFluct_full",
        //        "ToyMCREsults_v6_flowfluc_full",10);

        //generate("PbPb", "const", "const", 0.3, 3.0, -2.4, 2.4, 10, 50, 10, true, "v6", "10k_newEvt_vnFluct_1050");
        //generate("PbPb", "const", "const", 0.3, 3.0, -2.4, 2.4, 10, 50, 200000, false, "v5", "200k_newEvt_NovnFluct_1050");
        //generate("PbPb", "const", "const", 0.3, 3.0, -2.4, 2.4, 10, 200, 200000, true, "v6", "200k_newEvt_vnFluct_10200");
        //generate("PbPb", "const", "const", 0.3, 3.0, -2.4, 2.4, 10, 200, 200000, false, "v5", "200k_newEvt_NovnFluct_10200");

        //genAndAnalyze(2,
        //              "PbPb", "const", "const", 
        //              0.3, 3.0, 
        //              -2.4, 2.4, 
        //              10, 40, 
        //              10000, true, "v6", "10k_test_genAnalyze");
 
        //genAndAnalyzeTree(2,
        //              "PbPb", "const", "const", 
        //              0.3, 3.0, 
        //              -2.4, 2.4, 
        //              10, 40, 
        //              10, true, "v6", "10k_test_genAnalyzeTree");
 
        //analyzeTree("v6", "100k_test_genAnalyzeTree",
        //            "100k_test_genAnalyzeHist",
        //            -1);
}
//
void checkParam(int argc, char** argv)
{
        LOG_S(INFO) << "Number of parameters: " << argc;
        for(int ip=0; ip<argc; ++ip) 
        LOG_S(INFO) << "Argument " << ip << ": " << argv[ip];
}

void generate(std::string system,  std::string partDist, std::string vnDist,
              double ptMin,        double ptMax,
              double etaMin,       double etaMax,
              double multMin,      double multMax,
              int    nEvt,         bool   vnFluct,
              std::string version, std::string outFileName)
{
	toymc::ToyMCGenerator g(system, partDist, vnDist);
        g.setRanges(ptMin, ptMax, etaMin, etaMax, multMin, multMax);
	LOG_S(INFO) << g.toString();
	if(vnFluct) g.setFlowFluctuations();
	g.generate(nEvt, Form("/Volumes/Elements/ToyMCdata/datafiles/cumulant/%s/%s.root",version.c_str(), outFileName.c_str()));
	//g.generate(nEvt, Form("%s.root", outFileName.c_str()));
}

void genAndAnalyze(int harm,
                   std::string system,  std::string partDist, std::string vnDist,
                   double ptMin,        double ptMax,
                   double etaMin,       double etaMax,
                   double multMin,      double multMax,
                   int    nEvt,         bool   vnFluct,
                   std::string version, std::string outFileName)
{

	toymc::ToyMCGenerator g(system, partDist, vnDist);
        g.setRanges(ptMin, ptMax, etaMin, etaMax, multMin, multMax);
	LOG_S(INFO) << g.toString();
	if(vnFluct) g.setFlowFluctuations();

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
        sub1.set(1, "eta", -2.4, 0.);
        cumulant::Subset sub2(2);
        sub2.set(0, "pt", 0.3, 3.0);
        sub2.set(1, "eta", -2.4, 0.);
        cumulant::Subset sub3(2);
        sub3.set(0, "pt", 0.3, 3.0);
        sub3.set(1, "eta", 0., 2.4);
        cumulant::Subset sub4(2);
        sub4.set(0, "pt", 0.3, 3.0);
        sub4.set(1, "eta", 0., 2.4);

        //Init 2-p sub-event method
        cumulant::Set set2(2);
        set2.setSubsetParams(0, sub1);
        set2.setSubsetParams(1, sub3);

        //Init 4-p sub-event method
        cumulant::Set set4(4);
        set4.setSubsetParams(0, sub1);
        set4.setSubsetParams(1, sub2);
        set4.setSubsetParams(2, sub3);
        set4.setSubsetParams(3, sub4);

        //Init 2-p method with subset
        HarmonicVector h(2);
        h[0] =  1*harm;
        h[1] = -1*harm;
        //cumulant::QVectorSet q(h, set2, false);
        //cumulant::impl1::QVectorSet q(h, set2, false);
        cumulant::QVectorSet q(h, set2, false);
        //Init 4-p method with subset
        HarmonicVector h4(4);
        h4[0] =  1*harm;
        h4[1] =  1*harm;
        h4[2] = -1*harm;
        h4[3] = -1*harm;
        //cumulant::QVectorSet q4(h4, set4, false);
        //cumulant::impl1::QVectorSet q4(h4, set4, false);
        cumulant::QVectorSet q4(h4, set4, false);

        //Histograms
        //Global
        TH1I* hmult = new TH1I("hmult", "hmult", 1000,   0,             1000);
        TH1D* hpt   = new TH1D("hpt",   "hpt",   2000,   0,             20);
        TH1D* heta  = new TH1D("heta",  "heta",  2000,  -10,            10);
        TH1D* hphi  = new TH1D("hphi",  "hphi",  60000, -1*TMath::Pi(), TMath::Pi());
        hmult->AddDirectory(kFALSE);
        hphi ->AddDirectory(kFALSE);
        heta ->AddDirectory(kFALSE);
        hpt  ->AddDirectory(kFALSE);
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

        if(nEvt < 1) return;

        std::vector< double > val(2, 0.); //std::cout << val[0] << " " << val[1] << std::endl;

        std::vector< double > c22std(600, 0.);
        std::vector< double > w22std(600, 0.);
        std::vector< double > c24std(600, 0.);
        std::vector< double > w24std(600, 0.);

        std::vector< std::vector< double > > c22std_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w22std_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > c24std_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w24std_err(10, std::vector<double>(600, 0.));

        std::vector< double > c22gap(600, 0.);
        std::vector< double > w22gap(600, 0.);
        std::vector< double > c24gap(600, 0.);
        std::vector< double > w24gap(600, 0.);

        std::vector< std::vector< double > > c22gap_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w22gap_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > c24gap_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w24gap_err(10, std::vector<double>(600, 0.));


        std::vector< double > c22stdx(120, 0.);
        std::vector< double > w22stdx(120, 0.);
        std::vector< double > c24stdx(120, 0.);
        std::vector< double > w24stdx(120, 0.);

        std::vector< std::vector< double > > c22std_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w22std_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > c24std_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w24std_errx(10, std::vector<double>(120, 0.));

        std::vector< double > c22gapx(120, 0.);
        std::vector< double > w22gapx(120, 0.);
        std::vector< double > c24gapx(120, 0.);
        std::vector< double > w24gapx(120, 0.);

        std::vector< std::vector< double > > c22gap_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w22gap_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > c24gap_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w24gap_errx(10, std::vector<double>(120, 0.));


        correlations::Result rN2;
        correlations::Result rN4;

        cumulant::Correlator c2;
        cumulant::Correlator c4;

        //#####################################
        // Loop over events
        //#####################################
	for(int ievt = 0; ievt < nEvt; ++ievt)
	{
              int nparticles = 0;

              TRandom3 r2(0);
              nparticles = g.getMultHist()->GetRandom();
              //Number of particles entering the correlations *TO BE IMPLEMENTED CORRECTLY*
              unsigned int mult = 0.;
              //Number of particles to define the event class *TO BE IMPLEMENTED CORRECTLY*
              //unsigned int noff = 0.;
        
              //std::cout <<
              //"\rToyMCGenerator::INFO:: ievt = " << ievt
              //<<
              //" ~~~> " << std::setprecision(3) << (double)((double)ievt / (double)nEvt)*100  << " %"
              //<< std::flush;

              for(size_t iharm = 2; iharm < 3; ++iharm) 
              {
                 g.isFlowFluct(iharm);
              }
        
              qN.reset();
              q.reset();
              q4.reset();

              //Define weights to be always 1
              double w = 1.;

              //#####################################
              // Loop over particles
              //#####################################
	      for(int ipart = 0; ipart < nparticles; ++ipart)
	      {
                 g.generatePart(nparticles);
                 ++mult;

                 double pt  = g.getPlcPt() ;    
                 double eta = g.getPlcEta();
                 double phi = g.getPlcPhi();

                 hpt ->Fill(pt);
                 heta->Fill(eta);
                 hphi->Fill(phi);

                 //Cumulant
                 qN.fill(phi, w);

                 val[0] = pt;
                 val[1] = eta;
                 q.fill(val, phi, w);
                 q4.fill(val, phi, w);
              } //######## end loop particles

              hmult->Fill(mult);

              //With gap
	      cumulant::QVectorMap& qmap = q.getQ();
              c2 = cumulant::Correlator(3, 2, qmap);
              double c22n = c2.v.real();
              double c22d = c2.w.real();

	      cumulant::QVectorMap& q4map = q4.getQ();
              c4 = cumulant::Correlator(15, 2, q4map);
              double c24n = c4.v.real();
              double c24d = c4.w.real();

              c22gap[mult] += c22n;
              w22gap[mult] += c22d;
              c24gap[mult] += c24n;
              w24gap[mult] += c24d;

              //Bilandzic code
              rN2 = cqN->calculate(2, hcN);
              rN4 = cqN->calculate(4, hcN);          

              c22std[mult] += rN2.corr(); 
              w22std[mult] += rN2.weight(); 
              c24std[mult] += rN4.corr(); 
              w24std[mult] += rN4.weight(); 

            // --- Variance
              int ntest = rand() % 10;
              for(int itest = 0; itest < 10; ++itest)
              {
                 if(itest != ntest)
                 {
                    c22gap_err[itest][mult] += c22n;
                    w22gap_err[itest][mult] += c22d;
                    c24gap_err[itest][mult] += c24n;
                    w24gap_err[itest][mult] += c24d;
      
                    c22std_err[itest][mult] += rN2.corr(); 
                    w22std_err[itest][mult] += rN2.weight(); 
                    c24std_err[itest][mult] += rN4.corr(); 
                    w24std_err[itest][mult] += rN4.weight(); 
                 }
              }
        } //######## end loop events

          //standard method
          for(int ibin = 0; ibin < hV22std->GetNbinsX(); ++ibin)
          {
             hV22std_num->SetBinContent(ibin+1, c22std[ibin]);
             hV22std_den->SetBinContent(ibin+1, w22std[ibin]);
             if(w22std[ibin] != 0.) c22std[ibin] = c22std[ibin]/w22std[ibin];
             else                   c22std[ibin] = 0.;
             if(c22std[ibin] >= 0.) hV22std->SetBinContent(ibin+1, TMath::Sqrt(c22std[ibin]));

             c22stdx[ibin/5] += c22std[ibin] * w22std[ibin];
             w22stdx[ibin/5] += w22std[ibin];
          }
          for(int ibin = 0; ibin < hV24std->GetNbinsX(); ++ibin)
          {
             hV24std_num->SetBinContent(ibin+1, -2*c22std[ibin]*c22std[ibin] + c24std[ibin]);
             hV24std_den->SetBinContent(ibin+1, w24std[ibin]);
             if(w24std[ibin+1] != 0.) c24std[ibin] = c24std[ibin]/w24std[ibin];
             else                     c24std[ibin] = 0.;
             if(2*c22std[ibin]*c22std[ibin] - c24std[ibin] >= 0.) hV24std->SetBinContent(ibin+1, pow(2*c22std[ibin]*c22std[ibin] - c24std[ibin],1./4.));

             c24stdx[ibin/5] += c24std[ibin] * w24std[ibin];
             w24stdx[ibin/5] += w24std[ibin];
          }

          //gap method
          for(int ibin = 0; ibin < hV22gap->GetNbinsX(); ++ibin)
          {
             hV22gap_num->SetBinContent(ibin+1, c22gap[ibin]);
             hV22gap_den->SetBinContent(ibin+1, w22gap[ibin]);
             if(w22gap[ibin] != 0.) c22gap[ibin] = c22gap[ibin]/w22gap[ibin];
             else                   c22gap[ibin] = 0.;
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
             if(2*c22gap[ibin]*c22gap[ibin] - c24gap[ibin] >= 0.)  hV24gap->SetBinContent(ibin+1, pow(2*c22gap[ibin]*c22gap[ibin] - c24gap[ibin],1./4.));

             c24gapx[ibin/5] += c24gap[ibin] * w24gap[ibin];
             w24gapx[ibin/5] += w24gap[ibin];
          }

      
////////  ///REBIN
          //standard method
          for(int ibin = 0; ibin < hV22stdx->GetNbinsX(); ++ibin)
          {
             if(w22stdx[ibin] != 0.) c22stdx[ibin] = c22stdx[ibin]/w22stdx[ibin];
             else                    c22stdx[ibin] = 0.;
             if(c22stdx[ibin] >= 0.) hV22stdx->SetBinContent(ibin+1, TMath::Sqrt(c22stdx[ibin]));
          }
          for(int ibin = 0; ibin < hV24stdx->GetNbinsX(); ++ibin)
          {
             if(w24stdx[ibin+1] != 0.) c24stdx[ibin] = c24stdx[ibin]/w24stdx[ibin];
             else                      c24stdx[ibin] = 0.;
             if(2*c22stdx[ibin]*c22stdx[ibin] - c24stdx[ibin] >= 0.) hV24stdx->SetBinContent(ibin+1, pow(2*c22stdx[ibin]*c22stdx[ibin] - c24stdx[ibin],1./4.));
          }

          //gap method
          for(int ibin = 0; ibin < hV22gapx->GetNbinsX(); ++ibin)
          {
             if(w22gapx[ibin] != 0.) c22gapx[ibin] = c22gapx[ibin]/w22gapx[ibin];
             else                    c22gapx[ibin] = 0.;
             if(c22gapx[ibin] >= 0.) hV22gapx->SetBinContent(ibin+1, TMath::Sqrt(c22gapx[ibin]));
          }
          for(int ibin = 0; ibin < hV24gapx->GetNbinsX(); ++ibin)
          {
             if(w24gapx[ibin] != 0.) c24gapx[ibin] = c24gapx[ibin]/w24gapx[ibin];
             else                    c24gapx[ibin] = 0.;
             if(2*c22gapx[ibin]*c22gapx[ibin] - c24gapx[ibin] >= 0.)  hV24gapx->SetBinContent(ibin+1, pow(2*c22gapx[ibin]*c22gapx[ibin] - c24gapx[ibin],1./4.));
          }
////////  ///

          double varC22std = 0.;
          double varC24std = 0.;
          double varC22gap = 0.;
          double varC24gap = 0.;
          double varV22std = 0.;
          double varV24std = 0.;
          double varV22gap = 0.;
          double varV24gap = 0.;

          double varC22stdx = 0.;
          double varC24stdx = 0.;
          double varC22gapx = 0.;
          double varC24gapx = 0.;
          double varV22stdx = 0.;
          double varV24stdx = 0.;
          double varV22gapx = 0.;
          double varV24gapx = 0.;

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
                if(w24std_err[itest][ibin+1] != 0.) c24std_err[itest][ibin] = c24std_err[itest][ibin]/w24std_err[itest][ibin];
                else                                c24std_err[itest][ibin] = 0.;
                c24std_err[itest][ibin] -= 2*c22std_err[itest][ibin]*c22std_err[itest][ibin];

                c24std_errx[itest][ibin/5] += c24std_err[itest][ibin] * w24std_err[itest][ibin];
                w24std_errx[itest][ibin/5] += w24std_err[itest][ibin];
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
          }

          for(int itest = 0; itest < 10; ++itest)
          {
             for(int ibin = 0; ibin < hV22stdx->GetNbinsX(); ++ibin)
             {
                 if(w22std_errx[itest][ibin] != 0.) c22std_errx[itest][ibin] /= w22std_errx[itest][ibin];
                 if(w24std_errx[itest][ibin] != 0.) c24std_errx[itest][ibin] /= w24std_errx[itest][ibin];
                 if(w22gap_errx[itest][ibin] != 0.) c22gap_errx[itest][ibin] /= w22gap_errx[itest][ibin];
                 if(w24gap_errx[itest][ibin] != 0.) c24gap_errx[itest][ibin] /= w24gap_errx[itest][ibin];
             }
          }

          for(int ibin = 0; ibin < hV24gap->GetNbinsX(); ++ibin)
          {
             varC22std = 0.;
             varC24std = 0.;
             varC22gap = 0.;
             varC24gap = 0.;
             varV22std = 0.;
             varV24std = 0.;
             varV22gap = 0.;
             varV24gap = 0.;
             for(int itest = 0; itest < 10; ++itest)
             {
                varC22std += TMath::Power(c22std_err[itest][ibin] - c22std[ibin],2);   
                varC24std += TMath::Power(c24std_err[itest][ibin] - (c24std[ibin] - 2*c22std[ibin]*c22std[ibin]), 2); 
                varC22gap += TMath::Power(c22gap_err[itest][ibin] - c22gap[ibin],2); 
                varC24gap += TMath::Power(c24gap_err[itest][ibin] - (c24gap[ibin] - 2*c22gap[ibin]*c22gap[ibin]), 2);

                if(c22std_err[itest][ibin] >= 0. && c22std[ibin] >= 0.) 
                   varV22std += TMath::Power(TMath::Sqrt(c22std_err[itest][ibin]) - TMath::Sqrt(c22std[ibin]),2);   
                if(c24std_err[itest][ibin] <= 0. && c24std[ibin] - 2*c22std[ibin]*c22std[ibin] <= 0.) 
                   varV24std += TMath::Power(TMath::Power(-1*c24std_err[itest][ibin],1./4.) 
                                            -TMath::Power(-1*c24std[ibin] + 2*c22std[ibin]*c22std[ibin],1./4.), 2); 
                if(c22gap_err[itest][ibin] >= 0. && c22gap[ibin] >= 0.) 
                   varV22gap += TMath::Power(TMath::Sqrt(c22gap_err[itest][ibin]) - TMath::Sqrt(c22gap[ibin]),2); 
                if(c24gap_err[itest][ibin] <= 0. && c24gap[ibin] - 2*c22gap[ibin]*c22gap[ibin] <= 0.) 
                   varV24gap += TMath::Power(TMath::Power(-1*c24gap_err[itest][ibin],1./4.)
                                            -TMath::Power(-1*c24gap[ibin] + 2*c22gap[ibin]*c22gap[ibin], 1./4.), 2);
             }

             varC22std *= (10.-1.)/10.;
             varC24std *= (10.-1.)/10.;
             varC22gap *= (10.-1.)/10.;
             varC24gap *= (10.-1.)/10.;
             varV22std *= (10.-1.)/10.;
             varV24std *= (10.-1.)/10.;
             varV22gap *= (10.-1.)/10.;
             varV24gap *= (10.-1.)/10.;


             hV22std->SetBinError(ibin+1,TMath::Sqrt(varV22std)); 
             hV24std->SetBinError(ibin+1,TMath::Sqrt(varV24std));
             hV22gap->SetBinError(ibin+1,TMath::Sqrt(varV22gap));
             hV24gap->SetBinError(ibin+1,TMath::Sqrt(varV24gap));
             hV22std_num->SetBinError(ibin+1,TMath::Sqrt(varC22std)); 
             hV24std_num->SetBinError(ibin+1,TMath::Sqrt(varC24std));
             hV22gap_num->SetBinError(ibin+1,TMath::Sqrt(varC22gap));
             hV24gap_num->SetBinError(ibin+1,TMath::Sqrt(varC24gap));
          }
          for(int ibin = 0; ibin < hV24gapx->GetNbinsX(); ++ibin)
          {
             varC22stdx = 0.;
             varC24stdx = 0.;
             varC22gapx = 0.;
             varC24gapx = 0.;
             varV22stdx = 0.;
             varV24stdx = 0.;
             varV22gapx = 0.;
             varV24gapx = 0.;
             for(int itest = 0; itest < 10; ++itest)
             {
                varC22stdx += TMath::Power(c22std_errx[itest][ibin]/w22std_errx[itest][ibin] - c22stdx[ibin],2);   
                varC24stdx += TMath::Power(c24std_errx[itest][ibin]/w24std_errx[itest][ibin] - (c24stdx[ibin] - 2*c22stdx[ibin]*c22stdx[ibin]), 2); 
                varC22gapx += TMath::Power(c22gap_errx[itest][ibin]/w22gap_errx[itest][ibin] - c22gapx[ibin],2); 
                varC24gapx += TMath::Power(c24gap_errx[itest][ibin]/w24gap_errx[itest][ibin] - (c24gapx[ibin] - 2*c22gapx[ibin]*c22gapx[ibin]), 2);


                if(c22std_errx[itest][ibin] >= 0. && c22stdx[ibin] >= 0.) 
                   varV22stdx += TMath::Power(TMath::Sqrt(c22std_errx[itest][ibin]) - TMath::Sqrt(c22stdx[ibin]),2);   
                if(c24std_errx[itest][ibin] <= 0. && c24stdx[ibin] - 2*c22stdx[ibin]*c22stdx[ibin] <= 0.) 
                   varV24stdx += TMath::Power(TMath::Power(-1*c24std_errx[itest][ibin],1./4.) 
                                             -TMath::Power(-1*c24stdx[ibin] + 2*c22stdx[ibin]*c22stdx[ibin],1./4.), 2); 
                if(c22gap_errx[itest][ibin] >= 0. && c22gapx[ibin] >= 0.) 
                   varV22gapx += TMath::Power(TMath::Sqrt(c22gap_errx[itest][ibin]) - TMath::Sqrt(c22gapx[ibin]),2); 
                if(c24gap_errx[itest][ibin] <= 0. && c24gapx[ibin] - 2*c22gapx[ibin]*c22gapx[ibin] <= 0.) 
                   varV24gapx += TMath::Power(TMath::Power(-1*c24gap_errx[itest][ibin],1./4.)
                                             -TMath::Power(-1*c24gapx[ibin] + 2*c22gapx[ibin]*c22gapx[ibin], 1./4.), 2);
             }

             varC22stdx *= (10.-1.)/10.;
             varC24stdx *= (10.-1.)/10.;
             varC22gapx *= (10.-1.)/10.;
             varC24gapx *= (10.-1.)/10.;
             varV22stdx *= (10.-1.)/10.;
             varV24stdx *= (10.-1.)/10.;
             varV22gapx *= (10.-1.)/10.;
             varV24gapx *= (10.-1.)/10.;

             hV22stdx->SetBinError(ibin+1,TMath::Sqrt(varV22stdx)); 
             hV24stdx->SetBinError(ibin+1,TMath::Sqrt(varV24stdx));
             hV22gapx->SetBinError(ibin+1,TMath::Sqrt(varV22gapx));
             hV24gapx->SetBinError(ibin+1,TMath::Sqrt(varV24gapx));
          }

          std::cout << std::endl;
          std::cout << "Writting..." << std::endl;
          TFile* fout = new TFile(Form("%s/%s.root", getenv("OUTPUTDIR"), outFileName.c_str()), "recreate");
          hmult->Write();
          hpt  ->Write();
          heta ->Write();
          hphi ->Write();

          hV22std    ->Write();
          hV22stdx   ->Write();
          hV22std_den->Write();
          hV22std_num->Write();
          hV22gap    ->Write();
          hV22gapx   ->Write();
          hV22gap_den->Write();
          hV22gap_num->Write();

          hV24std    ->Write();
          hV24stdx   ->Write();
          hV24std_den->Write();
          hV24std_num->Write();
          hV24gap    ->Write();
          hV24gapx   ->Write();
          hV24gap_den->Write();
          hV24gap_num->Write();

          fout->Close();

          delete fout;
}

void genAndAnalyzeTree(int harm,
                       std::string system,  std::string partDist, std::string vnDist,
                       double ptMin,        double ptMax,
                       double etaMin,       double etaMax,
                       double multMin,      double multMax,
                       int    nEvt,         bool   vnFluct,
                       std::string version, std::string outFileName)
{

	toymc::ToyMCGenerator g(system, partDist, vnDist);
        g.setRanges(ptMin, ptMax, etaMin, etaMax, multMin, multMax);
	LOG_S(INFO) << g.toString();
	if(vnFluct) g.setFlowFluctuations();

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
        sub1.set(1, "eta", -2.4, 0.);
        cumulant::Subset sub2(2);
        sub2.set(0, "pt", 0.3, 3.0);
        sub2.set(1, "eta", -2.4, 0.);
        cumulant::Subset sub3(2);
        sub3.set(0, "pt", 0.3, 3.0);
        sub3.set(1, "eta", 0., 2.4);
        cumulant::Subset sub4(2);
        sub4.set(0, "pt", 0.3, 3.0);
        sub4.set(1, "eta", 0., 2.4);

        //Init 2-p sub-event method
        cumulant::Set set2(2);
        set2.setSubsetParams(0, sub1);
        set2.setSubsetParams(1, sub3);

        //Init 4-p sub-event method
        cumulant::Set set4(4);
        set4.setSubsetParams(0, sub1);
        set4.setSubsetParams(1, sub2);
        set4.setSubsetParams(2, sub3);
        set4.setSubsetParams(3, sub4);

        //Init 2-p method with subset
        HarmonicVector h(2);
        h[0] =  1*harm;
        h[1] = -1*harm;
        //cumulant::QVectorSet q(h, set2, false);
        //cumulant::impl1::QVectorSet q(h, set2, false);
        cumulant::QVectorSet q(h, set2, false);
        //Init 4-p method with subset
        HarmonicVector h4(4);
        h4[0] =  1*harm;
        h4[1] =  1*harm;
        h4[2] = -1*harm;
        h4[3] = -1*harm;
        //cumulant::QVectorSet q4(h4, set4, false);
        //cumulant::impl1::QVectorSet q4(h4, set4, false);
        cumulant::QVectorSet q4(h4, set4, false);

        //Histograms
        //Global
        TH1I* hmult = new TH1I("hmult", "hmult", 1000,   0,             1000);
        TH1D* hpt   = new TH1D("hpt",   "hpt",   2000,   0,             20);
        TH1D* heta  = new TH1D("heta",  "heta",  2000,  -10,            10);
        TH1D* hphi  = new TH1D("hphi",  "hphi",  60000, -1*TMath::Pi(), TMath::Pi());
        hmult->AddDirectory(kFALSE);
        hphi ->AddDirectory(kFALSE);
        heta ->AddDirectory(kFALSE);
        hpt  ->AddDirectory(kFALSE);
        //TTree
        unsigned int mult = 0.;
        double C2Nstd = 0., C4Nstd = 0., wC2Nstd = 0., wC4Nstd = 0.;
        double C2Ngap = 0., C4Ngap = 0., wC2Ngap = 0., wC4Ngap = 0.;
        TTree* tree = new TTree("trFlow", "trFlow");
        tree->Branch("mult", &mult, "mult/s");
        tree->Branch("C2Nstd",  &C2Nstd,  "C2Nstd/D");
        tree->Branch("C4Nstd",  &C4Nstd,  "C4Nstd/D");
        tree->Branch("wC2Nstd", &wC2Nstd, "wC2Nstd/D");
        tree->Branch("wC4Nstd", &wC4Nstd, "wC4Nstd/D");
        tree->Branch("C2Ngap",  &C2Ngap,  "C2Ngap/D");
        tree->Branch("C4Ngap",  &C4Ngap,  "C4Ngap/D");
        tree->Branch("wC2Ngap", &wC2Ngap, "wC2Ngap/D");
        tree->Branch("wC4Ngap", &wC4Ngap, "wC4Ngap/D");

        if(nEvt < 1) return;

        std::vector< double > val(2, 0.); //std::cout << val[0] << " " << val[1] << std::endl;
        correlations::Result rN2;
        correlations::Result rN4;

        cumulant::Correlator c2;
        cumulant::Correlator c4;

        //#####################################
        // Loop over events
        //#####################################
	for(int ievt = 0; ievt < nEvt; ievt++)
	{
              int nparticles = 0;

              TRandom3 r2(0);
              nparticles = g.getMultHist()->GetRandom();
              //Number of particles entering the correlations *TO BE IMPLEMENTED CORRECTLY*
              mult = 0.;
              //Number of particles to define the event class *TO BE IMPLEMENTED CORRECTLY*
              //unsigned int noff = 0.;
        
              std::cout <<
              "\rToyMCGenerator::INFO:: ievt = " << ievt
              <<
              " ~~~> " << std::setprecision(3) << (double)((double)ievt / (double)nEvt)*100  << " %"
              << std::flush;

              for(size_t iharm = 2; iharm < 3; ++iharm) 
              {
                 g.isFlowFluct(iharm);
              }
        
              qN.reset();
              q.reset();
              q4.reset();

              //Define weights to be always 1
              double w = 1.;

              //#####################################
              // Loop over particles
              //#####################################
	      for(int ipart = 0; ipart < nparticles; ++ipart)
	      {
                 g.generatePart(nparticles);
                 ++mult;

                 double pt  = g.getPlcPt() ;    
                 double eta = g.getPlcEta();
                 double phi = g.getPlcPhi();

                 hpt ->Fill(pt);
                 heta->Fill(eta);
                 hphi->Fill(phi);

                 //Cumulant
                 qN.fill(phi, w);

                 val[0] = pt;
                 val[1] = eta;
                 q.fill(val, phi, w);
                 q4.fill(val, phi, w);
              } //######## end loop particles

              hmult->Fill(mult);

              //With gap
	      cumulant::QVectorMap& qmap = q.getQ();
              c2 = cumulant::Correlator(3, 2, qmap);
              C2Ngap = c2.v.real();
              wC2Ngap = c2.w.real();

	      cumulant::QVectorMap& q4map = q4.getQ();
              c4 = cumulant::Correlator(15, 4, q4map);
              C4Ngap = c4.v.real();
              wC4Ngap = c4.w.real();

              //Bilandzic code
              rN2 = cqN->calculate(2, hcN);
              rN4 = cqN->calculate(4, hcN);          

              C2Nstd  = rN2.corr();
              C4Nstd  = rN4.corr();
              wC2Nstd = rN2.weight();
              wC4Nstd = rN4.weight();

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

void analyze(int harm,
             std::string version, std::string inFileName,
             std::string outFileName,
             int nEvt)
{
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
        sub1.set(1, "eta", -2.4, 0.);
        cumulant::Subset sub2(2);
        sub2.set(0, "pt", 0.3, 3.0);
        sub2.set(1, "eta", -2.4, 0.);
        cumulant::Subset sub3(2);
        sub3.set(0, "pt", 0.3, 3.0);
        sub3.set(1, "eta", 0., 2.4);
        cumulant::Subset sub4(2);
        sub4.set(0, "pt", 0.3, 3.0);
        sub4.set(1, "eta", 0., 2.4);

        //Init 2-p sub-event method
        cumulant::Set set2(2);
        set2.setSubsetParams(0, sub1);
        set2.setSubsetParams(1, sub3);

        //Init 4-p sub-event method
        cumulant::Set set4(4);
        set4.setSubsetParams(0, sub1);
        set4.setSubsetParams(1, sub2);
        set4.setSubsetParams(2, sub3);
        set4.setSubsetParams(3, sub4);

        //Init 2-p method with subset
        HarmonicVector h(2);
        h[0] =  1*harm;
        h[1] = -1*harm;
        //cumulant::QVectorSet q(h, set2, false);
        //cumulant::impl1::QVectorSet q(h, set2, false);
        cumulant::QVectorSet q(h, set2, false);
        //Init 4-p method with subset
        HarmonicVector h4(4);
        h4[0] =  1*harm;
        h4[1] =  1*harm;
        h4[2] = -1*harm;
        h4[3] = -1*harm;
        //cumulant::QVectorSet q4(h4, set4, false);
        //cumulant::impl1::QVectorSet q4(h4, set4, false);
        cumulant::QVectorSet q4(h4, set4, false);

        //Histograms
        //Global
        TH1I* hmult = new TH1I("hmult", "hmult", 1000,   0,             1000);
        TH1D* hpt   = new TH1D("hpt",   "hpt",   2000,   0,             20);
        TH1D* heta  = new TH1D("heta",  "heta",  2000,  -10,            10);
        TH1D* hphi  = new TH1D("hphi",  "hphi",  60000, -1*TMath::Pi(), TMath::Pi());
        hmult->AddDirectory(kFALSE);
        hphi ->AddDirectory(kFALSE);
        heta ->AddDirectory(kFALSE);
        hpt  ->AddDirectory(kFALSE);
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



        //Open in file and get TTree
        TFile* fin = TFile::Open(Form("/Volumes/Elements/ToyMCdata/datafiles/cumulant/%s/%s.root",version.c_str(),inFileName.c_str()));
        TTree* tr = (TTree*) fin->Get("ToyMCTree");
        //Setup the TTree for reading
        BranchReader<toymc::ToyMCEvent>          eventReader;
        TClonesArrayReader<toymc::ToyMCParticle> plcsReader;
        eventReader.setup(tr, "Event");
        plcsReader.setup(tr, "Particles");

        toymc::ToyMCEvent event;
        toymc::ToyMCParticle plc;

        int nentries = tr->GetEntries();
        if(nEvt != -1) nentries = nEvt;
        tr->Print();

        int ievt = 0;
        std::vector< double > val(2);


        std::vector< double > c22std(600, 0.);
        std::vector< double > w22std(600, 0.);
        std::vector< double > c24std(600, 0.);
        std::vector< double > w24std(600, 0.);

        std::vector< std::vector< double > > c22std_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w22std_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > c24std_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w24std_err(10, std::vector<double>(600, 0.));

        std::vector< double > c22gap(600, 0.);
        std::vector< double > w22gap(600, 0.);
        std::vector< double > c24gap(600, 0.);
        std::vector< double > w24gap(600, 0.);

        std::vector< std::vector< double > > c22gap_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w22gap_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > c24gap_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w24gap_err(10, std::vector<double>(600, 0.));


        std::vector< double > c22stdx(120, 0.);
        std::vector< double > w22stdx(120, 0.);
        std::vector< double > c24stdx(120, 0.);
        std::vector< double > w24stdx(120, 0.);

        std::vector< std::vector< double > > c22std_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w22std_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > c24std_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w24std_errx(10, std::vector<double>(120, 0.));

        std::vector< double > c22gapx(120, 0.);
        std::vector< double > w22gapx(120, 0.);
        std::vector< double > c24gapx(120, 0.);
        std::vector< double > w24gapx(120, 0.);

        std::vector< std::vector< double > > c22gap_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w22gap_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > c24gap_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w24gap_errx(10, std::vector<double>(120, 0.));


        correlations::Result rN2;
        correlations::Result rN4;

        cumulant::Correlator c2;
        cumulant::Correlator c4;

        //Define weights to be always 1
        double w = 1.;

        //Loop over events
        while(ievt < nentries)
        {
           plc.reset();

           tr->GetEntry(ievt);
           //std::cout <<
           //"\rtoymc.cxx::INFO:: ievt = " << ievt
           //<<
           //" ~~~> " << std::setprecision(3) << (double)((double)ievt / (double)nentries)*100  << " %"
           //<< std::flush;

           event = *eventReader.get();
           int mult = event.getMult();
           int npart = plcsReader.N();

           qN.reset();
           q.reset();
           q4.reset();

           //Loop over particles
           hmult->Fill(mult);
           for(int ip = 0; ip < npart; ++ip)
           {
              plc = *plcsReader.get(ip);
              double phi = plc.getphi();
              hpt->Fill(plc.getpt());
              heta->Fill(plc.geteta());
              hphi->Fill(phi);

              qN.fill(phi, w);

              val[0] = plc.getpt();
              val[1] = plc.geteta();

              //q.generateMask(val);
              q.fill(val, phi, w);

              //q4.generateMask(val);
              q4.fill(val, phi, w);
           }

           //With gap
	   cumulant::QVectorMap& qmap = q.getQ();
           c2 = cumulant::Correlator(3, 2, qmap);
           double c22n = c2.v.real();
           double c22d = c2.w.real();

	   cumulant::QVectorMap& q4map = q4.getQ();
           c4 = cumulant::Correlator(15, 4, q4map);
           double c24n = c4.v.real();
           double c24d = c4.w.real();

           c22gap[mult] += c22n;
           w22gap[mult] += c22d;
           c24gap[mult] += c24n;
           w24gap[mult] += c24d;

           //Bilandzic code
           rN2 = cqN->calculate(2, hcN);
           rN4 = cqN->calculate(4, hcN);          

           c22std[mult] += rN2.corr(); 
           w22std[mult] += rN2.weight(); 
           c24std[mult] += rN4.corr(); 
           w24std[mult] += rN4.weight(); 

           // --- Variance
           int ntest = rand() % 10;
           for(int itest = 0; itest < 10; ++itest)
           {
              if(itest != ntest)
              {
                 c22gap_err[itest][mult] += c22n;
                 w22gap_err[itest][mult] += c22d;
                 c24gap_err[itest][mult] += c24n;
                 w24gap_err[itest][mult] += c24d;
      
                 c22std_err[itest][mult] += rN2.corr(); 
                 w22std_err[itest][mult] += rN2.weight(); 
                 c24std_err[itest][mult] += rN4.corr(); 
                 w24std_err[itest][mult] += rN4.weight(); 
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
           if(c22std[ibin] >= 0.) hV22std->SetBinContent(ibin+1, TMath::Sqrt(c22std[ibin]));

           c22stdx[ibin/5] += c22std[ibin] * w22std[ibin];
           w22stdx[ibin/5] += w22std[ibin];
        }
        for(int ibin = 0; ibin < hV24std->GetNbinsX(); ++ibin)
        {
           hV24std_num->SetBinContent(ibin+1, -2*c22std[ibin]*c22std[ibin] + c24std[ibin]);
           hV24std_den->SetBinContent(ibin+1, w24std[ibin]);
           if(w24std[ibin+1] != 0.) c24std[ibin] = c24std[ibin]/w24std[ibin];
           else                     c24std[ibin] = 0.;
           if(2*c22std[ibin]*c22std[ibin] - c24std[ibin] >= 0.) hV24std->SetBinContent(ibin+1, pow(2*c22std[ibin]*c22std[ibin] - c24std[ibin],1./4.));

           c24stdx[ibin/5] += c24std[ibin] * w24std[ibin];
           w24stdx[ibin/5] += w24std[ibin];
        }

        //gap method
        for(int ibin = 0; ibin < hV22gap->GetNbinsX(); ++ibin)
        {
           hV22gap_num->SetBinContent(ibin+1, c22gap[ibin]);
           hV22gap_den->SetBinContent(ibin+1, w22gap[ibin]);
           if(w22gap[ibin] != 0.) c22gap[ibin] = c22gap[ibin]/w22gap[ibin];
           else                   c22gap[ibin] = 0.;
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
           if(2*c22gap[ibin]*c22gap[ibin] - c24gap[ibin] >= 0.)  hV24gap->SetBinContent(ibin+1, pow(2*c22gap[ibin]*c22gap[ibin] - c24gap[ibin],1./4.));

           c24gapx[ibin/5] += c24gap[ibin] * w24gap[ibin];
           w24gapx[ibin/5] += w24gap[ibin];
        }

      
///////////REBIN
        //standard method
        for(int ibin = 0; ibin < hV22stdx->GetNbinsX(); ++ibin)
        {
           if(w22stdx[ibin] != 0.) c22stdx[ibin] = c22stdx[ibin]/w22stdx[ibin];
           else                    c22stdx[ibin] = 0.;
           if(c22stdx[ibin] >= 0.) hV22stdx->SetBinContent(ibin+1, TMath::Sqrt(c22stdx[ibin]));
        }
        for(int ibin = 0; ibin < hV24stdx->GetNbinsX(); ++ibin)
        {
           if(w24stdx[ibin+1] != 0.) c24stdx[ibin] = c24stdx[ibin]/w24stdx[ibin];
           else                      c24stdx[ibin] = 0.;
           if(2*c22stdx[ibin]*c22stdx[ibin] - c24stdx[ibin] >= 0.) hV24stdx->SetBinContent(ibin+1, pow(2*c22stdx[ibin]*c22stdx[ibin] - c24stdx[ibin],1./4.));
        }

        //gap method
        for(int ibin = 0; ibin < hV22gapx->GetNbinsX(); ++ibin)
        {
           if(w22gapx[ibin] != 0.) c22gapx[ibin] = c22gapx[ibin]/w22gapx[ibin];
           else                    c22gapx[ibin] = 0.;
           if(c22gapx[ibin] >= 0.) hV22gapx->SetBinContent(ibin+1, TMath::Sqrt(c22gapx[ibin]));
        }
        for(int ibin = 0; ibin < hV24gapx->GetNbinsX(); ++ibin)
        {
           if(w24gapx[ibin] != 0.) c24gapx[ibin] = c24gapx[ibin]/w24gapx[ibin];
           else                    c24gapx[ibin] = 0.;
           if(2*c22gapx[ibin]*c22gapx[ibin] - c24gapx[ibin] >= 0.)  hV24gapx->SetBinContent(ibin+1, pow(2*c22gapx[ibin]*c22gapx[ibin] - c24gapx[ibin],1./4.));
        }
///////////

        double varC22std = 0.;
        double varC24std = 0.;
        double varC22gap = 0.;
        double varC24gap = 0.;
        double varV22std = 0.;
        double varV24std = 0.;
        double varV22gap = 0.;
        double varV24gap = 0.;

        double varC22stdx = 0.;
        double varC24stdx = 0.;
        double varC22gapx = 0.;
        double varC24gapx = 0.;
        double varV22stdx = 0.;
        double varV24stdx = 0.;
        double varV22gapx = 0.;
        double varV24gapx = 0.;

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
              if(w24std_err[itest][ibin+1] != 0.) c24std_err[itest][ibin] = c24std_err[itest][ibin]/w24std_err[itest][ibin];
              else                                c24std_err[itest][ibin] = 0.;
              c24std_err[itest][ibin] -= 2*c22std_err[itest][ibin]*c22std_err[itest][ibin];

              c24std_errx[itest][ibin/5] += c24std_err[itest][ibin] * w24std_err[itest][ibin];
              w24std_errx[itest][ibin/5] += w24std_err[itest][ibin];
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
        }

        for(int itest = 0; itest < 10; ++itest)
        {
           for(int ibin = 0; ibin < hV22stdx->GetNbinsX(); ++ibin)
           {
               if(w22std_errx[itest][ibin] != 0.) c22std_errx[itest][ibin] /= w22std_errx[itest][ibin];
               if(w24std_errx[itest][ibin] != 0.) c24std_errx[itest][ibin] /= w24std_errx[itest][ibin];
               if(w22gap_errx[itest][ibin] != 0.) c22gap_errx[itest][ibin] /= w22gap_errx[itest][ibin];
               if(w24gap_errx[itest][ibin] != 0.) c24gap_errx[itest][ibin] /= w24gap_errx[itest][ibin];
           }
        }

        for(int ibin = 0; ibin < hV24gap->GetNbinsX(); ++ibin)
        {
           varC22std = 0.;
           varC24std = 0.;
           varC22gap = 0.;
           varC24gap = 0.;
           varV22std = 0.;
           varV24std = 0.;
           varV22gap = 0.;
           varV24gap = 0.;
           for(int itest = 0; itest < 10; ++itest)
           {
              varC22std += TMath::Power(c22std_err[itest][ibin] - c22std[ibin],2);   
              varC24std += TMath::Power(c24std_err[itest][ibin] - (c24std[ibin] - 2*c22std[ibin]*c22std[ibin]), 2); 
              varC22gap += TMath::Power(c22gap_err[itest][ibin] - c22gap[ibin],2); 
              varC24gap += TMath::Power(c24gap_err[itest][ibin] - (c24gap[ibin] - 2*c22gap[ibin]*c22gap[ibin]), 2);

              if(c22std_err[itest][ibin] >= 0. && c22std[ibin] >= 0.) 
                 varV22std += TMath::Power(TMath::Sqrt(c22std_err[itest][ibin]) - TMath::Sqrt(c22std[ibin]),2);   
              if(c24std_err[itest][ibin] <= 0. && c24std[ibin] - 2*c22std[ibin]*c22std[ibin] <= 0.) 
                 varV24std += TMath::Power(TMath::Power(-1*c24std_err[itest][ibin],1./4.) 
                                          -TMath::Power(-1*c24std[ibin] + 2*c22std[ibin]*c22std[ibin],1./4.), 2); 
              if(c22gap_err[itest][ibin] >= 0. && c22gap[ibin] >= 0.) 
                 varV22gap += TMath::Power(TMath::Sqrt(c22gap_err[itest][ibin]) - TMath::Sqrt(c22gap[ibin]),2); 
              if(c24gap_err[itest][ibin] <= 0. && c24gap[ibin] - 2*c22gap[ibin]*c22gap[ibin] <= 0.) 
                 varV24gap += TMath::Power(TMath::Power(-1*c24gap_err[itest][ibin],1./4.)
                                          -TMath::Power(-1*c24gap[ibin] + 2*c22gap[ibin]*c22gap[ibin], 1./4.), 2);
           }

           varC22std *= (10.-1.)/10.;
           varC24std *= (10.-1.)/10.;
           varC22gap *= (10.-1.)/10.;
           varC24gap *= (10.-1.)/10.;
           varV22std *= (10.-1.)/10.;
           varV24std *= (10.-1.)/10.;
           varV22gap *= (10.-1.)/10.;
           varV24gap *= (10.-1.)/10.;


           hV22std->SetBinError(ibin+1,TMath::Sqrt(varV22std)); 
           hV24std->SetBinError(ibin+1,TMath::Sqrt(varV24std));
           hV22gap->SetBinError(ibin+1,TMath::Sqrt(varV22gap));
           hV24gap->SetBinError(ibin+1,TMath::Sqrt(varV24gap));
           hV22std_num->SetBinError(ibin+1,TMath::Sqrt(varC22std)); 
           hV24std_num->SetBinError(ibin+1,TMath::Sqrt(varC24std));
           hV22gap_num->SetBinError(ibin+1,TMath::Sqrt(varC22gap));
           hV24gap_num->SetBinError(ibin+1,TMath::Sqrt(varC24gap));
        }
        for(int ibin = 0; ibin < hV24gapx->GetNbinsX(); ++ibin)
        {
           varC22stdx = 0.;
           varC24stdx = 0.;
           varC22gapx = 0.;
           varC24gapx = 0.;
           varV22stdx = 0.;
           varV24stdx = 0.;
           varV22gapx = 0.;
           varV24gapx = 0.;
           for(int itest = 0; itest < 10; ++itest)
           {
              varC22stdx += TMath::Power(c22std_errx[itest][ibin]/w22std_errx[itest][ibin] - c22stdx[ibin],2);   
              varC24stdx += TMath::Power(c24std_errx[itest][ibin]/w24std_errx[itest][ibin] - (c24stdx[ibin] - 2*c22stdx[ibin]*c22stdx[ibin]), 2); 
              varC22gapx += TMath::Power(c22gap_errx[itest][ibin]/w22gap_errx[itest][ibin] - c22gapx[ibin],2); 
              varC24gapx += TMath::Power(c24gap_errx[itest][ibin]/w24gap_errx[itest][ibin] - (c24gapx[ibin] - 2*c22gapx[ibin]*c22gapx[ibin]), 2);


              if(c22std_errx[itest][ibin] >= 0. && c22stdx[ibin] >= 0.) 
                 varV22stdx += TMath::Power(TMath::Sqrt(c22std_errx[itest][ibin]) - TMath::Sqrt(c22stdx[ibin]),2);   
              if(c24std_errx[itest][ibin] <= 0. && c24stdx[ibin] - 2*c22stdx[ibin]*c22stdx[ibin] <= 0.) 
                 varV24stdx += TMath::Power(TMath::Power(-1*c24std_errx[itest][ibin],1./4.) 
                                           -TMath::Power(-1*c24stdx[ibin] + 2*c22stdx[ibin]*c22stdx[ibin],1./4.), 2); 
              if(c22gap_errx[itest][ibin] >= 0. && c22gapx[ibin] >= 0.) 
                 varV22gapx += TMath::Power(TMath::Sqrt(c22gap_errx[itest][ibin]) - TMath::Sqrt(c22gapx[ibin]),2); 
              if(c24gap_errx[itest][ibin] <= 0. && c24gapx[ibin] - 2*c22gapx[ibin]*c22gapx[ibin] <= 0.) 
                 varV24gapx += TMath::Power(TMath::Power(-1*c24gap_errx[itest][ibin],1./4.)
                                           -TMath::Power(-1*c24gapx[ibin] + 2*c22gapx[ibin]*c22gapx[ibin], 1./4.), 2);
           }

           varC22stdx *= (10.-1.)/10.;
           varC24stdx *= (10.-1.)/10.;
           varC22gapx *= (10.-1.)/10.;
           varC24gapx *= (10.-1.)/10.;
           varV22stdx *= (10.-1.)/10.;
           varV24stdx *= (10.-1.)/10.;
           varV22gapx *= (10.-1.)/10.;
           varV24gapx *= (10.-1.)/10.;

           hV22stdx->SetBinError(ibin+1,TMath::Sqrt(varV22stdx)); 
           hV24stdx->SetBinError(ibin+1,TMath::Sqrt(varV24stdx));
           hV22gapx->SetBinError(ibin+1,TMath::Sqrt(varV22gapx));
           hV24gapx->SetBinError(ibin+1,TMath::Sqrt(varV24gapx));
        }

        std::cout << "Writting..." << std::endl;
        TFile* fout = new TFile(Form("%s/%s.root", getenv("OUTPUTDIR"), outFileName.c_str()), "recreate");

        hmult->Write();
        hpt  ->Write();
        heta ->Write();
        hphi ->Write();

        hV22std    ->Write();
        hV22stdx   ->Write();
        hV22std_den->Write();
        hV22std_num->Write();
        hV22gap    ->Write();
        hV22gapx   ->Write();
        hV22gap_den->Write();
        hV22gap_num->Write();

        hV24std    ->Write();
        hV24stdx   ->Write();
        hV24std_den->Write();
        hV24std_num->Write();
        hV24gap    ->Write();
        hV24gapx   ->Write();
        hV24gap_den->Write();
        hV24gap_num->Write();

        fout->Close();

        delete fout;
}

void analyzeTree(std::string version, std::string inFileName,
                 std::string outFileName,
                 int nEvt)
{
        //Histograms
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



        //Open in file and get TTree
        //TFile* fin = TFile::Open(Form("/Volumes/Elements/ToyMCdata/datafiles/cumulant/%s/%s.root",version.c_str(),inFileName.c_str()));
        UShort_t mult = 0;
        double C2Nstd = 0., C4Nstd = 0., wC2Nstd = 0., wC4Nstd = 0.;
        double C2Ngap = 0., C4Ngap = 0., wC2Ngap = 0., wC4Ngap = 0.;
        TFile* fin = TFile::Open(Form("%s/%s.root", getenv("OUTPUTDIR"), inFileName.c_str()));
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
        tr->SetBranchAddress("C2Ngap",  &C2Ngap);
        tr->SetBranchAddress("C4Ngap",  &C4Ngap);
        tr->SetBranchAddress("wC2Nstd", &wC2Nstd);
        tr->SetBranchAddress("wC4Nstd", &wC4Nstd);
        tr->SetBranchAddress("wC2Ngap", &wC2Ngap);
        tr->SetBranchAddress("wC4Ngap", &wC4Ngap);

        int nentries = tr->GetEntries();
        if(nEvt != -1) nentries = nEvt;
        tr->Print();

        int ievt = 0;
        std::vector< double > val(2);


        std::vector< double > c22std(600, 0.);
        std::vector< double > w22std(600, 0.);
        std::vector< double > c24std(600, 0.);
        std::vector< double > w24std(600, 0.);

        std::vector< std::vector< double > > c22std_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w22std_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > c24std_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w24std_err(10, std::vector<double>(600, 0.));

        std::vector< double > c22gap(600, 0.);
        std::vector< double > w22gap(600, 0.);
        std::vector< double > c24gap(600, 0.);
        std::vector< double > w24gap(600, 0.);

        std::vector< std::vector< double > > c22gap_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w22gap_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > c24gap_err(10, std::vector<double>(600, 0.));
        std::vector< std::vector< double > > w24gap_err(10, std::vector<double>(600, 0.));


        std::vector< double > c22stdx(120, 0.);
        std::vector< double > w22stdx(120, 0.);
        std::vector< double > c24stdx(120, 0.);
        std::vector< double > w24stdx(120, 0.);

        std::vector< std::vector< double > > c22std_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w22std_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > c24std_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w24std_errx(10, std::vector<double>(120, 0.));

        std::vector< double > c22gapx(120, 0.);
        std::vector< double > w22gapx(120, 0.);
        std::vector< double > c24gapx(120, 0.);
        std::vector< double > w24gapx(120, 0.);

        std::vector< std::vector< double > > c22gap_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w22gap_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > c24gap_errx(10, std::vector<double>(120, 0.));
        std::vector< std::vector< double > > w24gap_errx(10, std::vector<double>(120, 0.));


        correlations::Result rN2;
        correlations::Result rN4;

        cumulant::Correlator c2;
        cumulant::Correlator c4;

        //Loop over events
        while(ievt < nentries)
        {
           tr->GetEntry(ievt);
           //std::cout <<
           //"\rtoymc.cxx::INFO:: ievt = " << ievt
           //<<
           //" ~~~> " << std::setprecision(3) << (double)((double)ievt / (double)nentries)*100  << " %"
           //<< std::flush;
//std::cout << "Nevt = " << ievt << std::endl;
//std::cout << "Mult = " << mult << std::endl;
//std::cout << "C2Nstd = " << C2Nstd << std::endl;
//std::cout << "C4Nstd = " << C4Nstd << std::endl;
//std::cout << "C2Ngap = " << C2Ngap << std::endl;
//std::cout << "C4Ngap = " << C4Ngap << std::endl;
           c22std[mult] += C2Nstd; 
           w22std[mult] += wC2Nstd;  
           c24std[mult] += C4Nstd; 
           w24std[mult] += wC4Nstd;  

           c22gap[mult] += C2Ngap; 
           w22gap[mult] += wC2Ngap;
           c24gap[mult] += C4Ngap; 
           w24gap[mult] += wC4Ngap;

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

                 c22gap_err[itest][mult] += C2Ngap; 
                 w22gap_err[itest][mult] += wC2Ngap;
                 c24gap_err[itest][mult] += C4Ngap; 
                 w24gap_err[itest][mult] += wC4Ngap;      
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
           if(c22std[ibin] >= 0.) hV22std->SetBinContent(ibin+1, TMath::Sqrt(c22std[ibin]));

           c22stdx[ibin/5] += c22std[ibin] * w22std[ibin];
           w22stdx[ibin/5] += w22std[ibin];
        }
        for(int ibin = 0; ibin < hV24std->GetNbinsX(); ++ibin)
        {
           hV24std_num->SetBinContent(ibin+1, -2*c22std[ibin]*c22std[ibin] + c24std[ibin]);
           hV24std_den->SetBinContent(ibin+1, w24std[ibin]);
           if(w24std[ibin+1] != 0.) c24std[ibin] = c24std[ibin]/w24std[ibin];
           else                     c24std[ibin] = 0.;
           if(2*c22std[ibin]*c22std[ibin] - c24std[ibin] >= 0.) hV24std->SetBinContent(ibin+1, pow(2*c22std[ibin]*c22std[ibin] - c24std[ibin],1./4.));

           c24stdx[ibin/5] += c24std[ibin] * w24std[ibin];
           w24stdx[ibin/5] += w24std[ibin];
        }

        //gap method
        for(int ibin = 0; ibin < hV22gap->GetNbinsX(); ++ibin)
        {
           hV22gap_num->SetBinContent(ibin+1, c22gap[ibin]);
           hV22gap_den->SetBinContent(ibin+1, w22gap[ibin]);
           if(w22gap[ibin] != 0.) c22gap[ibin] = c22gap[ibin]/w22gap[ibin];
           else                   c22gap[ibin] = 0.;
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
           if(2*c22gap[ibin]*c22gap[ibin] - c24gap[ibin] >= 0.)  hV24gap->SetBinContent(ibin+1, pow(2*c22gap[ibin]*c22gap[ibin] - c24gap[ibin],1./4.));

           c24gapx[ibin/5] += c24gap[ibin] * w24gap[ibin];
           w24gapx[ibin/5] += w24gap[ibin];
        }

      
///////////REBIN
        //standard method
        for(int ibin = 0; ibin < hV22stdx->GetNbinsX(); ++ibin)
        {
           if(w22stdx[ibin] != 0.) c22stdx[ibin] = c22stdx[ibin]/w22stdx[ibin];
           else                    c22stdx[ibin] = 0.;
           if(c22stdx[ibin] >= 0.) hV22stdx->SetBinContent(ibin+1, TMath::Sqrt(c22stdx[ibin]));
        }
        for(int ibin = 0; ibin < hV24stdx->GetNbinsX(); ++ibin)
        {
           if(w24stdx[ibin+1] != 0.) c24stdx[ibin] = c24stdx[ibin]/w24stdx[ibin];
           else                      c24stdx[ibin] = 0.;
           if(2*c22stdx[ibin]*c22stdx[ibin] - c24stdx[ibin] >= 0.) hV24stdx->SetBinContent(ibin+1, pow(2*c22stdx[ibin]*c22stdx[ibin] - c24stdx[ibin],1./4.));
        }

        //gap method
        for(int ibin = 0; ibin < hV22gapx->GetNbinsX(); ++ibin)
        {
           if(w22gapx[ibin] != 0.) c22gapx[ibin] = c22gapx[ibin]/w22gapx[ibin];
           else                    c22gapx[ibin] = 0.;
           if(c22gapx[ibin] >= 0.) hV22gapx->SetBinContent(ibin+1, TMath::Sqrt(c22gapx[ibin]));
        }
        for(int ibin = 0; ibin < hV24gapx->GetNbinsX(); ++ibin)
        {
           if(w24gapx[ibin] != 0.) c24gapx[ibin] = c24gapx[ibin]/w24gapx[ibin];
           else                    c24gapx[ibin] = 0.;
           if(2*c22gapx[ibin]*c22gapx[ibin] - c24gapx[ibin] >= 0.)  hV24gapx->SetBinContent(ibin+1, pow(2*c22gapx[ibin]*c22gapx[ibin] - c24gapx[ibin],1./4.));
        }
///////////

        double varC22std = 0.;
        double varC24std = 0.;
        double varC22gap = 0.;
        double varC24gap = 0.;
        double varV22std = 0.;
        double varV24std = 0.;
        double varV22gap = 0.;
        double varV24gap = 0.;

        double varC22stdx = 0.;
        double varC24stdx = 0.;
        double varC22gapx = 0.;
        double varC24gapx = 0.;
        double varV22stdx = 0.;
        double varV24stdx = 0.;
        double varV22gapx = 0.;
        double varV24gapx = 0.;

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
              if(w24std_err[itest][ibin+1] != 0.) c24std_err[itest][ibin] = c24std_err[itest][ibin]/w24std_err[itest][ibin];
              else                                c24std_err[itest][ibin] = 0.;
              c24std_err[itest][ibin] -= 2*c22std_err[itest][ibin]*c22std_err[itest][ibin];

              c24std_errx[itest][ibin/5] += c24std_err[itest][ibin] * w24std_err[itest][ibin];
              w24std_errx[itest][ibin/5] += w24std_err[itest][ibin];
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
        }

        for(int itest = 0; itest < 10; ++itest)
        {
           for(int ibin = 0; ibin < hV22stdx->GetNbinsX(); ++ibin)
           {
               if(w22std_errx[itest][ibin] != 0.) c22std_errx[itest][ibin] /= w22std_errx[itest][ibin];
               if(w24std_errx[itest][ibin] != 0.) c24std_errx[itest][ibin] /= w24std_errx[itest][ibin];
               if(w22gap_errx[itest][ibin] != 0.) c22gap_errx[itest][ibin] /= w22gap_errx[itest][ibin];
               if(w24gap_errx[itest][ibin] != 0.) c24gap_errx[itest][ibin] /= w24gap_errx[itest][ibin];
           }
        }

        for(int ibin = 0; ibin < hV24gap->GetNbinsX(); ++ibin)
        {
           varC22std = 0.;
           varC24std = 0.;
           varC22gap = 0.;
           varC24gap = 0.;
           varV22std = 0.;
           varV24std = 0.;
           varV22gap = 0.;
           varV24gap = 0.;
           for(int itest = 0; itest < 10; ++itest)
           {
              varC22std += TMath::Power(c22std_err[itest][ibin] - c22std[ibin],2);   
              varC24std += TMath::Power(c24std_err[itest][ibin] - (c24std[ibin] - 2*c22std[ibin]*c22std[ibin]), 2); 
              varC22gap += TMath::Power(c22gap_err[itest][ibin] - c22gap[ibin],2); 
              varC24gap += TMath::Power(c24gap_err[itest][ibin] - (c24gap[ibin] - 2*c22gap[ibin]*c22gap[ibin]), 2);

              if(c22std_err[itest][ibin] >= 0. && c22std[ibin] >= 0.) 
                 varV22std += TMath::Power(TMath::Sqrt(c22std_err[itest][ibin]) - TMath::Sqrt(c22std[ibin]),2);   
              if(c24std_err[itest][ibin] <= 0. && c24std[ibin] - 2*c22std[ibin]*c22std[ibin] <= 0.) 
                 varV24std += TMath::Power(TMath::Power(-1*c24std_err[itest][ibin],1./4.) 
                                          -TMath::Power(-1*c24std[ibin] + 2*c22std[ibin]*c22std[ibin],1./4.), 2); 
              if(c22gap_err[itest][ibin] >= 0. && c22gap[ibin] >= 0.) 
                 varV22gap += TMath::Power(TMath::Sqrt(c22gap_err[itest][ibin]) - TMath::Sqrt(c22gap[ibin]),2); 
              if(c24gap_err[itest][ibin] <= 0. && c24gap[ibin] - 2*c22gap[ibin]*c22gap[ibin] <= 0.) 
                 varV24gap += TMath::Power(TMath::Power(-1*c24gap_err[itest][ibin],1./4.)
                                          -TMath::Power(-1*c24gap[ibin] + 2*c22gap[ibin]*c22gap[ibin], 1./4.), 2);
           }

           varC22std *= (10.-1.)/10.;
           varC24std *= (10.-1.)/10.;
           varC22gap *= (10.-1.)/10.;
           varC24gap *= (10.-1.)/10.;
           varV22std *= (10.-1.)/10.;
           varV24std *= (10.-1.)/10.;
           varV22gap *= (10.-1.)/10.;
           varV24gap *= (10.-1.)/10.;


           hV22std->SetBinError(ibin+1,TMath::Sqrt(varV22std)); 
           hV24std->SetBinError(ibin+1,TMath::Sqrt(varV24std));
           hV22gap->SetBinError(ibin+1,TMath::Sqrt(varV22gap));
           hV24gap->SetBinError(ibin+1,TMath::Sqrt(varV24gap));
           hV22std_num->SetBinError(ibin+1,TMath::Sqrt(varC22std)); 
           hV24std_num->SetBinError(ibin+1,TMath::Sqrt(varC24std));
           hV22gap_num->SetBinError(ibin+1,TMath::Sqrt(varC22gap));
           hV24gap_num->SetBinError(ibin+1,TMath::Sqrt(varC24gap));
        }
        for(int ibin = 0; ibin < hV24gapx->GetNbinsX(); ++ibin)
        {
           varC22stdx = 0.;
           varC24stdx = 0.;
           varC22gapx = 0.;
           varC24gapx = 0.;
           varV22stdx = 0.;
           varV24stdx = 0.;
           varV22gapx = 0.;
           varV24gapx = 0.;
           for(int itest = 0; itest < 10; ++itest)
           {
              varC22stdx += TMath::Power(c22std_errx[itest][ibin]/w22std_errx[itest][ibin] - c22stdx[ibin],2);   
              varC24stdx += TMath::Power(c24std_errx[itest][ibin]/w24std_errx[itest][ibin] - (c24stdx[ibin] - 2*c22stdx[ibin]*c22stdx[ibin]), 2); 
              varC22gapx += TMath::Power(c22gap_errx[itest][ibin]/w22gap_errx[itest][ibin] - c22gapx[ibin],2); 
              varC24gapx += TMath::Power(c24gap_errx[itest][ibin]/w24gap_errx[itest][ibin] - (c24gapx[ibin] - 2*c22gapx[ibin]*c22gapx[ibin]), 2);


              if(c22std_errx[itest][ibin] >= 0. && c22stdx[ibin] >= 0.) 
                 varV22stdx += TMath::Power(TMath::Sqrt(c22std_errx[itest][ibin]) - TMath::Sqrt(c22stdx[ibin]),2);   
              if(c24std_errx[itest][ibin] <= 0. && c24stdx[ibin] - 2*c22stdx[ibin]*c22stdx[ibin] <= 0.) 
                 varV24stdx += TMath::Power(TMath::Power(-1*c24std_errx[itest][ibin],1./4.) 
                                           -TMath::Power(-1*c24stdx[ibin] + 2*c22stdx[ibin]*c22stdx[ibin],1./4.), 2); 
              if(c22gap_errx[itest][ibin] >= 0. && c22gapx[ibin] >= 0.) 
                 varV22gapx += TMath::Power(TMath::Sqrt(c22gap_errx[itest][ibin]) - TMath::Sqrt(c22gapx[ibin]),2); 
              if(c24gap_errx[itest][ibin] <= 0. && c24gapx[ibin] - 2*c22gapx[ibin]*c22gapx[ibin] <= 0.) 
                 varV24gapx += TMath::Power(TMath::Power(-1*c24gap_errx[itest][ibin],1./4.)
                                           -TMath::Power(-1*c24gapx[ibin] + 2*c22gapx[ibin]*c22gapx[ibin], 1./4.), 2);
           }

           varC22stdx *= (10.-1.)/10.;
           varC24stdx *= (10.-1.)/10.;
           varC22gapx *= (10.-1.)/10.;
           varC24gapx *= (10.-1.)/10.;
           varV22stdx *= (10.-1.)/10.;
           varV24stdx *= (10.-1.)/10.;
           varV22gapx *= (10.-1.)/10.;
           varV24gapx *= (10.-1.)/10.;

           hV22stdx->SetBinError(ibin+1,TMath::Sqrt(varV22stdx)); 
           hV24stdx->SetBinError(ibin+1,TMath::Sqrt(varV24stdx));
           hV22gapx->SetBinError(ibin+1,TMath::Sqrt(varV22gapx));
           hV24gapx->SetBinError(ibin+1,TMath::Sqrt(varV24gapx));
        }

        std::cout << "Writting..." << std::endl;
        TFile* fout = new TFile(Form("%s/%s.root", getenv("OUTPUTDIR"), outFileName.c_str()), "recreate");

        hmult->Write();
        hpt  ->Write();
        heta ->Write();
        hphi ->Write();

        hV22std    ->Write();
        hV22stdx   ->Write();
        hV22std_den->Write();
        hV22std_num->Write();
        hV22gap    ->Write();
        hV22gapx   ->Write();
        hV22gap_den->Write();
        hV22gap_num->Write();

        hV24std    ->Write();
        hV24stdx   ->Write();
        hV24std_den->Write();
        hV24std_num->Write();
        hV24gap    ->Write();
        hV24gapx   ->Write();
        hV24gap_den->Write();
        hV24gap_num->Write();

        fout->Close();

        delete fout;
}
