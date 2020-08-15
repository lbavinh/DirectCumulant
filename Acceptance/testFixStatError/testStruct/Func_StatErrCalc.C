Double_t Vn2(Double_t cor2){ 
  // cor2 - all-event average 2-particle azimuthal correlations (<<2>>)
  Double_t vn2; // reference flow estimate from 2-nd order cumulant (2QC)
  vn2 = sqrt(cor2);
  return vn2;
}

Double_t Vn4(Double_t cor2, Double_t cor4){
  // cor4 - all-event average 4-particle azimuthal correlations (<<4>>)
  Double_t vn4;  // reference flow estimate from 4-th order cumulant (4QC)
  vn4 = pow(2*cor2*cor2-cor4,0.25); 
  return vn4;
}

Double_t Evn2(Double_t cor2, Double_t cor2E, Double_t sumwcor2, Double_t sumw2cor2){
  Double_t eVn2; // stat. error of n-th harmonic from 2QC
  eVn2 = 0.5*pow(cor2,-0.5)*sqrt(sumw2cor2)/sumwcor2*cor2E;
  return eVn2;
}

Double_t Evn4(Double_t cor2, Double_t cor2E, Double_t sumwcor2, Double_t sumw2cor2,
              Double_t cor4, Double_t cor4E, Double_t sumwcor4, Double_t sumw2cor4,
              Double_t cov24, Double_t sumwcor24){
  Double_t eVn4; // stat. error of n-th harmonic from 4QC
  eVn4 = pow(2*cor2*cor2-cor4,-1.5)*(sumw2cor2*pow(cor2*cor2E/sumwcor2,2)
          + 1./16.*sumw2cor4*pow(cor4E/sumwcor4,2) - 0.5*cor2*sumwcor24*cov24/sumwcor2/sumwcor4);
  return sqrt(eVn4);
}

Double_t Vn2Dif(Double_t cor2Red, Double_t cor2){
  Double_t vn2dif;
  vn2dif = cor2Red / sqrt(cor2);
  return vn2dif;
}

Double_t Evn2dif(Double_t cor2, Double_t cor2E, Double_t sumwcor2, Double_t sumw2cor2,
                 Double_t cor2Red, Double_t cor2RedE, Double_t sumwcor2red, Double_t sumw2cor2red,
                 Double_t cov22prime, Double_t sumwcor22prime){
  Double_t evn2dif;                 
  evn2dif = 0.25*pow(cor2,-3.)*(cor2Red*cor2Red*sumw2cor2/sumwcor2/sumwcor2*cor2E*cor2E
          + 4.*cor2*cor2*sumw2cor2red*pow(cor2RedE/sumwcor2red,2.) - 4.*cor2*cor2Red
          * sumwcor22prime/sumwcor2/sumwcor2red*cov22prime);
  return sqrt(evn2dif);
}

Double_t Vn4Dif(Double_t cor2Red, Double_t cor2, Double_t cor4Red, Double_t cor4){
  Double_t vn4dif;
  vn4dif = (2.*cor2*cor2Red-cor4Red)*pow(2.*cor2*cor2-cor4,-0.75);
  return vn4dif;
}

Double_t Evn4dif(Double_t cor2, Double_t cor2E, Double_t sumwcor2, Double_t sumw2cor2,
                 Double_t cor2Red, Double_t cor2RedE, Double_t sumwcor2red, Double_t sumw2cor2red,
                 Double_t cor4, Double_t cor4E, Double_t sumwcor4, Double_t sumw2cor4,
                 Double_t cor4Red, Double_t cor4RedE, Double_t sumwcor4red, Double_t sumw2cor4red,
                 Double_t cov24, Double_t sumwcor24, Double_t cov22prime, Double_t sumwcor22prime,
                 Double_t cov2prime4prime, Double_t sumwcor2prime4prime, Double_t cov44prime, Double_t sumwcor44prime,
                 Double_t cov24prime, Double_t sumwcor24prime, Double_t cov42prime, Double_t sumwcor42prime){
  Double_t evn4dif;                 
  evn4dif = pow(2.*cor2*cor2-cor4,-3.5)
          * (pow(2.*cor2*cor2*cor2Red-3*cor2*cor4Red+2.*cor4*cor2Red,2.)
          * sumw2cor2*pow(cor2E/sumwcor2,2.)
          + 9./16.*pow(2.*cor2*cor2Red-cor4Red,2.)*sumw2cor4*pow(cor4E/sumwcor4,2.)
          + 4.*cor2*cor2*pow(2*cor2*cor2-cor4,2.)*sumw2cor2red*pow(cor2RedE/sumwcor2red,2.)
          + pow(2*cor2*cor2-cor4,2.)*sumw2cor4red*pow(cor4RedE/sumwcor4red,2.)
          - 1.5*(2*cor2*cor2Red-cor4Red)
          * (2.*cor2*cor2*cor2Red-3.*cor2*cor4Red+2.*cor4*cor2Red)
          * sumwcor24/sumwcor2/sumwcor4*cov24
          - 4.*cor2*(2.*cor2*cor2-cor4)
          * (2.*cor2*cor2*cor2Red-3.*cor2*cor4Red+2*cor4*cor2Red)
          * sumwcor22prime/sumwcor2/sumwcor2red*cov22prime
          + 2.*(2.*cor2*cor2-cor4)
          * (2.*cor2*cor2*cor2Red-3.*cor2*cor4Red+2.*cor4*cor2Red)
          * sumwcor24prime/sumwcor2/sumwcor4red*cov24prime
          + 3.*cor2*(2.*cor2*cor2-cor4)*(2.*cor2*cor2Red-cor4Red)
          * sumwcor42prime/sumwcor4/sumwcor2red*cov42prime
          - 1.5*(2*cor2*cor2-cor4)*(2.*cor2*cor2Red-cor4Red)
          * sumwcor44prime/sumwcor4/sumwcor4red*cov44prime
          - 4.*cor2*pow(2.*cor2*cor2-cor4,2.)*sumwcor2prime4prime/sumwcor2red/sumwcor4red*cov2prime4prime);
  return sqrt(evn4dif);
}

Double_t sx(TProfile *const &pr){ // Unbiased estimator for the root of variance (C.3)
  Double_t temp=0;
  Double_t stats[6];
  pr -> GetStats(stats);
  Double_t sumw = stats[0];
  Double_t sumw2 = stats[1];
  pr -> SetErrorOption("s");
  Double_t stdevw = pr -> GetBinError(1);

  temp = stdevw*stdevw/(1-sumw2/sumw/sumw);
  return sqrt(temp);
}

Double_t Cov(TProfile *const &prxy, TProfile *const &prx, TProfile *const &pry){
  Double_t temp=0;
  Double_t stats[6];
  prxy -> GetStats(stats);
  Double_t sumwxy = stats[0];
  Double_t meanxy = prxy -> GetBinContent(1);

  prx -> GetStats(stats);
  Double_t sumwx = stats[0];
  Double_t meanx = prx -> GetBinContent(1);

  pry -> GetStats(stats);
  Double_t sumwy = stats[0];
  Double_t meany = pry -> GetBinContent(1);
  temp = (meanxy-meanx*meany)/(1-sumwxy/sumwx/sumwy);
  return temp;
}

Double_t Sumwxwy(TProfile *const &prxy){
  Double_t temp = 0;
  Double_t stats[6];
  prxy -> GetStats(stats);
  temp = stats[0];
  return temp;
}