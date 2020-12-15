{
 gSystem->Load("./hTana.so");
 hTana *ana=new hTana();
 ana->ana_init("v2hadron.root"); // name for root file with results 
 ana->v2gen(400000,500,100);
 ana->ana_end();
 cout<<"histfile written"<<endl;
}
