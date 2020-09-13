TProfile *pV2pt;      // TProfile for v2 vs pt (10-40% centrality) calculation
float v2[ncent][npt]; // differential flow
TH1F hPt[ncent][npt]; // pt distribution
for (int icent=0;icent<ncent;icent++){
  for (int ipt=0;ipt<npt;ipt++){
    pV2pt->Fill(ipt,v2[icent][ipt],hPt[icent][ipt]->GetEntries());
  }
}
...
for (int ipt=0;ipt<npt;ipt++){
  v2pt[ipt] = pV2pt->GetBinContent(ipt+1);
}


TProfile *pV2int; float v2[ncent][npt]; TH1F hPt[ncent][npt];
for (int icent=0;icent<ncent;icent++){…
for (int ipt=0;ipt<npt;ipt++){...
pV2int→Fill(icent,v2[icent][ipt],hPt[icent][ipt]→GetEntries());
}
}
...
for (int icent=0;icent<ncent;icent++){
v2int[icent] = pV2int->GetBinContent(icent+1);
    }