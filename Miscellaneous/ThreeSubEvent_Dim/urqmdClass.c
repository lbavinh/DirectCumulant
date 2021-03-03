
#define urqmdClass_cxx
#include "urqmdClass.h"

#include <TStopwatch.h>
#include <TChain.h>
#include <TFile.h>
#include <TClonesArray.h>
#include <TDatabasePDG.h>
#include <TVector3.h>

#include "/weekly/idrisov/UrQMD11/Init.C"

void urqmdClass::Loop(const char *inputFileName, const char *outputFileName)
{
    Book();
    TStopwatch timer;
    timer.Start();

    // Configure input information
    TChain *chain = new TChain("mctree");
    std::ifstream file(inputFileName);
    std::string line;
    while (std::getline(file, line))
    {
        chain->Add(line.c_str());
    }

    //Обнуление всех переменных
    for (int k = 0; k < Nb; k++)
    {
        ClearVar(k);
    }

    int bin_b = -1;
    float Vpt, Veta, Vphi;
    Init(chain);
    // Start event loop
    Long64_t n_entries = chain->GetEntries();
    Long64_t div_entries = n_entries / 10;

    for (Long64_t iEv = 0; iEv < n_entries; iEv++)
    {
        if (iEv % div_entries == 0)
            std::cout << "Event [" << iEv << "/" << n_entries << "]" << std::endl;
        chain->GetEntry(iEv);

        bin_b = GetBinb(bimp);
        hNpart->Fill(nh);
        if (bin_b == -1)
            continue;

        for (int i = 0; i < nh; i++)
        {

            // PID-related cut (or to cut out neutral particles)
            auto particle = (TParticlePDG *)TDatabasePDG::Instance()->GetParticle(pdg[i]);
            if (!particle)
                continue;

            float charge = 1. / 3. * particle->Charge();
            if (charge == 0)
                continue;

            TVector3 vect(momx[i], momy[i], momz[i]);

            Vpt = vect.Pt();
            Veta = vect.Eta();
            Vphi = vect.Phi();
            
            LoopVarFHCal(bin_b, Vpt, Veta, Vphi);
            
            if (Vpt > pt_max)
                continue;
            if (Vpt < pt_min)
                continue;
            if (fabs(Veta) > eta_max)
                continue;

            //LoopVar1ch(bin_b, Vpt, Veta, Vphi,charge);
            LoopVar1(bin_b, Vpt, Veta, Vphi);
        }

        //hNpart->Fill((Mplus[bin_b] + Mminus[bin_b]));

        for (int i = 0; i < nh; i++)
        {

            // PID-related cut (or to cut out neutral particles)
            auto particle = (TParticlePDG *)TDatabasePDG::Instance()->GetParticle(pdg[i]);
            if (!particle)
                continue;

            float charge = 1. / 3. * particle->Charge();
            if (charge == 0)
                continue;

            TVector3 vect(momx[i], momy[i], momz[i]);

            Vpt = vect.Pt();
            Veta = vect.Eta();
            Vphi = vect.Phi();

            if (Vpt > pt_max)
                continue;
            if (Vpt < pt_min)
                continue;
            if (fabs(Veta) > eta_max)
                continue;

            //LoopVar2ch(bin_b, Vpt, Veta, Vphi,charge);
            //LoopVarEPch(bin_b, Vpt, Veta, Vphi,charge);
            LoopVar2(bin_b, Vpt, Veta, Vphi);
            LoopVarEP(bin_b, Vpt, Veta, Vphi);
        }

        //Loop histogram
        FiilHist(bin_b);

        //Обнуление переменных
        ClearVar(bin_b);

    } // end event loop
    SaveData(outputFileName);
    timer.Stop();
    timer.Print();
}
