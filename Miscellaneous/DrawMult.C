/*

Прилагаю к письму простой Root макро, в котором реализовано более-менее реалистичная
генерация множественности и прицельного параметра на основе данных модели Глаубера
(файл /mnt/pool/nica/6/parfenovpeter/CentralityGlauber/merge_hist_glaub_200gev.root).

Запуск макро:
root -l -b -q DrawMult.C+'("<path>/merge_hist_glaub_200gev.root","<path>/output_multiplicity.root")'
тут первый аргумент - файл модели Глаубера, второй аргумент - выходной файл с гистограммой множественности.

В качестве параметров генерации в DrawMult.C есть 3 основных параметра:

    f - параметр вклада Npart и Ncoll в результирующую множественность
    (а именно то, как множественность загибается в центральной области):
        при f = 0 множественность будет схожа по форме с распределением Ncoll
        при f = 1 множественность будет схожа по форме с распределением Npart
    MeanMult - среднее значение множественности 
    (соответственно, оно влияет на максимальную множественность частиц в событии)
    Nevents - количество событий, которое будет симулировать генератор

По завершению генерации будет создан output_multiplicity.root, содержащий 2 гистограммы:

    hMult - гистограмма с распределением множественности (среднее значение гистограммы hMult->GetMean()
    должно быть близко к MeanMult, которую вы задали)
    hBimpvsMult - двумерная гистограмма с зависимостью множественности от прицельного параметра

*/

#include <TROOT.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH1I.h>
#include <TH2F.h>
#include <TF1.h>
#include <TRandom3.h>
#include <TStopwatch.h>

double GetProjectedRandom(double b, TH2F *const &hist);

void DrawMult(TString glauberFileName, TString outputFileName)
{
  //Set random seed so your random numbers don't repeat each time you run this macro
  TRandom3 rnd;
  gRandom->SetSeed(rnd.Uniform(0., 1000000.));

  // Start the timer: that way we can see how much time Nevents will be generated
  TStopwatch timer;
  timer.Start();

  // Main parameters:
  //  f - Npart to Ncoll contribution to multiplicity. Essentially, it reflects how multiplicity behaves near its maximum (in the most central region).
  //    f = 0 - Multiplicity is renormalized Ncoll
  //    f = 1 - Multiplicity is renormalized Npart
  //  MeanMult - mean value of the multiplicity
  //  Nevents - number of generated events
  const double f = 0.1, MeanMult = 50.;
  const int Nevents = 2e5;

  // Read histograms from the Glauber file
  TH1F *hBimp;
  TH1I *hNpart, *hNcoll;
  TH2F *hBimpvsNpart, *hBimpvsNcoll;

  TFile *fi = new TFile(glauberFileName.Data(), "read");

  hBimp = (TH1F *)fi->Get("hBimp");
  hNpart = (TH1I *)fi->Get("hNpart");
  hNcoll = (TH1I *)fi->Get("hNcoll");
  hBimpvsNpart = (TH2F *)fi->Get("hBimpvsNpart");
  hBimpvsNcoll = (TH2F *)fi->Get("hBimpvsNcoll");

  // Create output histograms

  TH1I *hMult = new TH1I("hMult", "Multiplicity", 2500, 0, 2500);
  TH2F *hBimpvsMult = new TH2F("hBimpvsMult", "Multiplicity vs b", 2500, 0, 2500, 200, 0., 20.);

  for (int i = 0; i < Nevents; i++)
  {
    if (i % 1000 == 0)
      std::cout << "Event [" << i << "/" << Nevents << "]" << std::endl;
    double b = hBimp->GetRandom();
    double Npart = GetProjectedRandom(b, hBimpvsNpart);
    double Ncoll = GetProjectedRandom(b, hBimpvsNcoll);
    double Na = f * Npart + (1 - f) * Ncoll;
    double NaNorm = (f * hNpart->GetMean() + (1 - f) * hNcoll->GetMean()) / MeanMult;
    int mult = (Na / NaNorm);
    hMult->Fill(mult);
    hBimpvsMult->Fill(Na / NaNorm, b);
  }

  TFile *fo = new TFile(outputFileName.Data(), "recreate");
  fo->cd();
  hMult->Write();
  hBimpvsMult->Write();
  fo->Close();

  // Stop the timer and print how much time it took to generate Nevents
  timer.Stop();
  timer.Print();
}

double GetProjectedRandom(double b, TH2F *const &hist)
// Projects Npart or Ncoll distribution for given impact parameter and gives you random Npart or Ncoll
// using the projected distribution as a probability function (i.e. gives you random number within RMS)
{
  TH1D *hist1D = hist->ProjectionY("tmp", hist->GetXaxis()->FindBin(b), hist->GetXaxis()->FindBin(b));
  double result = hist1D->GetRandom();
  return result;
}