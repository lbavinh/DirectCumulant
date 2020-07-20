//double* test(){double *a=new double[2];a[0]=1;a[1]=3;return a;}

double start(double N0){TFile *f = TFile::Open("~/FLOW5/OUT/OUT2M.root");
TH1I *hNpart, *hNcoll;hNpart = (TH1I *)f->Get("hNpart");double c;c=hNpart->Integral(N0,500)/hNpart->Integral();hNpart->Draw();
return c;}
