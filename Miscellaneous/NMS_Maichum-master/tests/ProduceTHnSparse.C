void ProduceTHnSparse() 
{

double minv[4] = {0,-10,0,3.14159};
double maxv[4] = {1000,10,20,3.14159};
int nbinsv[4] = {1000,2000,2000,6143};

THnSparseD* h = new THnSparseD("hvnMod", "hvnMod", 4, nbinsv, minv, maxv);
cout << h->GetNbins() << endl;

double vn[9] = {0.1,0.03,0.015,0.01,0.005,0.005, 0.001, 0.0005, 0.0001};
Int_t *bins = new Int_t[4];

double x[4];

for( int mult = minv[0]; mult < maxv[0]; ++mult )
{
   x[0] = minv[0] + mult*(maxv[0]-minv[0])/(double)nbinsv[0];
   for( int eta = minv[1]; eta < maxv[1]; ++eta )
   {
      x[1] = minv[1] + mult*(maxv[1]-minv[1])/(double)nbinsv[1];
      for( int pt = minv[0]; pt < maxv[0]; ++pt )
      {
         x[2] = minv[2] + mult*(maxv[2]-minv[2])/(double)nbinsv[2];
         for( int phi = minv[0]; phi < maxv[0]; ++phi )
         {
            x[3] = minv[3] + mult*(maxv[3]-minv[3])/(double)nbinsv[3];
            double weight = 1;
            for(int n = 0; n < 9; ++n)
            {
               weight += vn[n]*TMath::Cos((n+2)*x[3]);
            }
            h->Fill(x,weight);       
         }
      }
   }
}
cout << h->GetNbins() << endl;

}
