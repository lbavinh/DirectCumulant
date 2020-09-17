/// \file
/// \ingroup Tutorials
/// Example of `rootlogon.C`.
/// The macro `rootlogon.C` in the current working directory, is executed when
/// `root` starts unless the option `-n` is used.
///
/// \macro_code
///
/// \author Rene Brun

{
   gStyle->SetMarkerStyle(20);
   gStyle->SetMarkerSize(1);
   gStyle->SetMarkerColor(1);
   gStyle->SetLineColor(1);
   gStyle->SetDrawOption("ep");
   gROOT->ForceStyle();
}

