#include <Math/SpecFuncMathMore.h>
#include <TMath.h>

R__LOAD_LIBRARY(libMathMore.so);

// Resolution calculation
//S----------------------------------------------------------------
double GetRes(double _chi, double _harm){
  double con = TMath::Sqrt(TMath::Pi() / 2) / 2;
  double arg = _chi * _chi / 4.;
  double order1 = (_harm - 1) / 2.;
  double order2 = (_harm + 1) / 2.;
  double res = con * _chi * exp(-arg) * (ROOT::Math::cyl_bessel_i(order1, arg) + ROOT::Math::cyl_bessel_i(order2, arg));
  return res;
}
//E----------------------------------------------------------------


// Chi2 calculation
//S----------------------------------------------------------------
double GetChi(double _res, double _harm, int accuracy){
  double chi = 2.0;
  double delta = 1.0;
  for (int i = 0; i < accuracy; i++){
    if(GetRes(chi, _harm) < _res) chi = chi + delta;
    else chi = chi - delta;
    delta = delta / 2.;
  }
  return chi;
}
//E----------------------------------------------------------------

void ReadRes(const char *inFileName)
{
    TFile *fi = new TFile(inFileName,"read");
    TH1F *hRes[3][4][6];
    for (int ih=0; ih<3;ih++)
    {
        for (int icb=0;icb<4;icb++)
        {
            for (int ic=0; ic<6;ic++)
            {
                hRes[ih][icb][ic] = (TH1F*) fi->Get(Form("HRes_%i_%i_%i",ih,icb,ic));
            }
        }
    }

    std::vector<Double_t> vX, vY, vEX, vEY;
    int cb = 3;
    int h  = 0;
    double chi, chiF, res2, res, resF;
    std::cout << "Calculating resolution:" << std::endl;
    for (int ic=0; ic<6; ic++)
    {
        res2 = hRes[h][cb][ic]->GetMean();
        res = (res2>0) ? TMath::Sqrt(res2) : 0.;
        chi = GetChi(res,2.,50);
        chiF = TMath::Sqrt(2)*chi;
        resF = GetRes(chiF,2.);
        vX.push_back(10.*ic+5.);
        vEX.push_back(0.);
        if (res == 0){
            vY.push_back(0.);
            vEY.push_back(0.);
        }
        vY.push_back(resF);
        vEY.push_back( hRes[h][cb][ic]->GetMeanError() * (resF/res) );

        std::cout << "ic " << ic << ": " << resF << std::endl;
    }
    std::cout << std::endl;

    std::cout << "res2fhcal = {";
    for (int ic=0;ic<5;ic++)
    {
        std::cout << vY.at(ic) << ",";
    }
    std::cout << vY.at(5) << "};" << std::endl;

    TGraphErrors *gr = new TGraphErrors(vX.size(),&vX[0],&vY[0],&vEX[0],&vEY[0]);
    gr->SetMarkerStyle(21);
    gr->SetMarkerSize(1.6);
    gr->SetMarkerColor(1);
    gr->SetLineColor(1);
    
    gr->Draw("AP");
}