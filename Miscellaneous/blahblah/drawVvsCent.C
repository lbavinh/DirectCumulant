#include "TStyle.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TFile.h"
#include "TProfile.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TROOT.h"
#include <cstdio>
#include <fstream>
#include "TSystem.h"
#include "PhenixConstants.h"

TStyle* makeplotstyle()
{
	TStyle *style = new TStyle("style", "Style for Summary Plots");
	//style->SetCanvasBorderMode(0);//removes the yellow frame around the canvas
	style->SetFrameBorderMode(0);//removes red highlighting
	style->SetPadTickX(1);//ticks on both pad sides 
	style->SetPadTickY(1);
	style->SetNdivisions(508, "X");
	style->SetNdivisions(508, "Y");

	return style;
}

//ix==0 for centrality on the x; ix==1 for Npart
void drawVvsCent(int ix = 0, int imeth=1)
{
	const int NG = 3;
	const int N_EN = 3;
	TFile *file[N_EN];
	TProfile *prof[N_EN][NHARM][NCENT5];
	char ch[200];
	const int energies[N_EN] = {39, 62, 200};
	Double_t widePtBins[4] = {0.3, 1.0, 2.0, 3.6};
	Double_t npart[N_EN][NCENT5] = {342.2, 290.5, 246.3, 208.5, 176.6, 148.0, 122.8, 101.5, 81.72, 64.98, 50.66, 38.51,
									345.7, 293.2, 248.6, 211.0, 178.6, 149.9, 124.5, 102.4, 83.43, 66.56, 51.40, 38.80,
									350.8, 301.7, 255.7, 216.4, 182.4, 152.7, 126.8, 104.2, 84.59, 67.73, 53.16, 40.96};

		
	//open the files
	sprintf(ch, "./%s/chHSum.root", "./39");
	file[0] = new TFile(ch);
	sprintf(ch, "./%s/chHSum.root", "./62");
	file[1] = new TFile(ch);
	sprintf(ch, "./%s/chHSum.root", "./200");
	file[2] = new TFile(ch);	
		
	TGraphErrors* gr[NG][NHARM][N_EN];
	Float_t y[NG][NHARM][N_EN][NCENT5];
	Float_t ey[NG][NHARM][N_EN][NCENT5];
	Float_t x[N_EN][NCENT5];
	Float_t ex[NCENT5];
	
	for (int ic = 0; ic<NCENT5; ic++) {
		ex[ic] = 0;
		for (int ien = 0; ien<N_EN; ien++) {
			x[ien][ic] = (ix==0) ? ic*5.+2.5 : npart[ien][ic];
		}
	}

	//parse profiles
	for (int ien = 0; ien<N_EN; ien++) {
		for (int iharm = 0; iharm<NHARM; iharm++) {
			for (int ic = 0; ic<NCENT5; ic++) {
				sprintf(ch, "pFlow%s_h%i_%s_%s_xy_c%i_s0", GetMethodName(imeth).c_str(), iharm+2,
					GetRingName(2).c_str(),	GetArmrName(2).c_str(), ic);
				prof[ien][iharm][ic] = (TProfile*)(file[ien]->Get(ch));
				sprintf(ch, "%s_rebin", ch);
				prof[ien][iharm][ic] = (TProfile*) prof[ien][iharm][ic]->Rebin(3, ch, widePtBins);
				for (int ig = 0; ig<NG; ig++) {//ipt
					y[ig][iharm][ien][ic] = prof[ien][iharm][ic]->GetBinContent(ig+1);
					ey[ig][iharm][ien][ic] = prof[ien][iharm][ic]->GetBinError(ig+1);
				}
			}		
		}
	}
	
	for (int ien = 0; ien<N_EN; ien++) {
		for (int ig = 0; ig<NG; ig++) {
			for (int iharm = 0; iharm<NHARM; iharm++) {
				gr[ig][iharm][ien] = new TGraphErrors(NCENT5, &x[ien][0], &y[ig][iharm][ien][0], ex, &ey[ig][iharm][ien][0]);
			}
		}
	}
	
	//20(24) - circle;  21(25) - square;  31 - *
	//22(26) - up-tri;  23(32) - dw-tri;   5 - x
	//29(30) - star;   33(27) - diamond;  34(28) - cross;
	int markerStyle[NG][NHARM] = {20, 20,
								  26, 26,
								  23, 23};

	Float_t markerSize[NHARM] = {1., 1.};
	
	Color_t markerColor[NG] = {kAzure+2, kRed+1, kGreen+1};	
	
	TStyle *tsty = makeplotstyle();
	tsty->cd();
	gROOT->ForceStyle();
	
	TPad* pad[NHARM][N_EN];
	char padname[10];
	Float_t padXL[NHARM][N_EN] = {0, 0.4, 0.7,   0, 0.4, 0.7};
	Float_t padXR[NHARM][N_EN] = {0.4, 0.7, 1.,   0.4, 0.7, 1.0};
	Float_t padYD[NHARM][N_EN] = {0.55, 0.55, 0.55,   0.0, 0.0, 0.0};
	Float_t padYU[NHARM][N_EN] = {1.0, 1.0, 1.,   0.55, 0.55, 0.55};
	//margins
	Float_t padLM[NHARM][N_EN] = {0.26, 0, 0,   0.26, 0, 0};
	Float_t padBM[NHARM][N_EN] = {0., 0., 0.,   0.2, 0.2, 0.2};	
	
	TMultiGraph *mg;
	TCanvas *c1;
	TLatex *tex[NHARM][N_EN];
    TLine *line;
    TLegend* legend;
	
	float size;
	int energy;
	unsigned char abcChar[NHARM][N_EN] = {'a','b','c',   'd','e','f'}; // 2 hang arm 3 cot energy
	
	c1 = new TCanvas("c1", "title", 500, 370);
	c1->SetFillColor(0);

	for (int iharm=0; iharm<NHARM; iharm++){ // loop over arms - 2 arms
		for (int ien = 0; ien < N_EN; ien++){ // loop over energy - 3 energy
			c1->cd();
			sprintf(ch, "pad%i_%i", iharm, ien);
			pad[iharm][ien] = new TPad(ch, ch, padXL[iharm][ien], padYD[iharm][ien], padXR[iharm][ien], padYU[iharm][ien]);
			Float_t rightMargin = (ien==2) ? 0.01 : 0.0;
			pad[iharm][ien]->SetMargin(padLM[iharm][ien], rightMargin, padBM[iharm][ien], 0);
			pad[iharm][ien]->SetFillColor(0);
			pad[iharm][ien]->Draw();
			pad[iharm][ien]->Clear();
			pad[iharm][ien]->cd();

			mg = new TMultiGraph();
			
			for (int ig=0; ig<NG; ig++) { // loop over pt bin
				gr[ig][iharm][ien]->SetMarkerSize(markerSize[iharm]);
				gr[ig][iharm][ien]->SetMarkerColor(markerColor[ig]);
				gr[ig][iharm][ien]->SetMarkerStyle(markerStyle[ig][iharm]);
				gr[ig][iharm][ien]->SetLineWidth(1);
				gr[ig][iharm][ien]->SetDrawOption("P");
				mg->Add(gr[ig][iharm][ien]);
			}
			mg->Draw("AP");
			mg->SetTitle("");

			if (ien == 0)	{
				mg->GetYaxis()->SetLabelFont(43);
				mg->GetYaxis()->SetLabelSize(15);
				mg->GetYaxis()->SetTitleFont(43);
				mg->GetYaxis()->SetTitleSize(18);
				mg->GetYaxis()->SetTitleOffset(2.2);
				mg->GetYaxis()->CenterTitle(true);
				sprintf(ch, "v_{%i}", iharm+2);
				mg->GetYaxis()->SetTitle(ch);
			}
			else {
				mg->GetYaxis()->SetTitle("");
				mg->GetYaxis()->SetLabelSize(0);
			}
			
			if (iharm==0) {
				mg->GetXaxis()->SetLabelSize(0);
			}			
			else {
				mg->GetXaxis()->SetLabelFont(43);
				mg->GetXaxis()->SetLabelSize(15);
			}

			if (iharm==1&&ien==1) {
				mg->GetXaxis()->SetTitleFont(43);
				mg->GetXaxis()->SetTitleSize(17);
				mg->GetXaxis()->SetTitleOffset(1.8);
				mg->GetXaxis()->CenterTitle(true);
				if (ix==0) mg->GetXaxis()->SetTitle("centrality (%)");
				else mg->GetXaxis()->SetTitle("N_{part}");
			}
			int xndiv = (ix==0) ? 407 : 204;
			mg->GetXaxis()->SetNdivisions(xndiv);
			mg->GetYaxis()->SetNdivisions(503);
			
			mg->SetMinimum(-0.01);
			mg->SetMaximum(0.28);
			double xleft = (ix==0) ? -2 : 20;
			double xright = (ix==0) ? 59.99 : 365;
			mg->GetXaxis()->SetLimits(xleft, xright);

			if (iharm==1&&ien==0) {
				TLatex* auAuMark = new TLatex((xright-xleft)*0.09+xleft, 0.213,"Au+Au");
				auAuMark->SetTextFont(43);
				auAuMark->SetTextSize(15);
				auAuMark->Draw("same");
			}

			if (iharm==1&&ien==0) {
				legend = new TLegend(0.31,0.58,0.65,0.78);
				legend->SetBorderSize(0);
				legend->SetTextFont(43);
				legend->SetTextSize(15);
				legend->SetFillColor(0);
				legend->AddEntry(gr[2][0][ien], "2.0<p_{T}<3.6", "p"); // l -line, f - box, p - marker
				legend->AddEntry(gr[1][0][ien], "1.0<p_{T}<2.0", "p"); // l -line, f - box, p - marker
				legend->AddEntry(gr[0][0][ien], "0.3<p_{T}<1.0", "p"); // l -line, f - box, p - marker
				legend->Draw("same");
			}

			sprintf(ch, "(%c) %i GeV", abcChar[iharm][ien], energies[ien]);
			tex[iharm][ien] = new TLatex((xright-xleft)*0.09+xleft, 0.245, ch);
			tex[iharm][ien]->SetTextFont(43);
			tex[iharm][ien]->SetTextSize(13);
			tex[iharm][ien]->Draw("same");
            
            line = new TLine(xleft,0,xright,0);
            line->SetLineStyle(2);
            line->Draw("same");
		} // end of loop over energy
	} // end of loop over arms
	if (ix==0) sprintf(ch, "./pics/VvsCent.png");
	else sprintf(ch, "./pics/VvsNpart.png");
	c1->Print(ch);		
	
	delete c1;
}
