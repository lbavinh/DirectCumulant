void compileSimRP()
{
gROOT->Reset();
cout <<"loading GENERAL libraries ... " << endl;  
	gSystem->Load("libCint");
	gSystem->Load("libTable");
	gSystem->Load("libPhysics");
cout << "loading GENERAL libraries done " << endl << endl;  

cout << "trying to COMPILE and LOAD LambdaDst library ..." << endl;
	gSystem->CompileMacro("StRoot/macros/simulateRP.C");
cout << "LambdaDst library has been COMPILED and LOADED" << endl;
}
