#include "FlowANA.C"
void macro( char* inFile="urqmd_1033721.mcpico.root",  char* outFile="test.root") {
  FlowANA *ana = new FlowANA();
  ana->ana_init(outFile);
  ana->loop_a_file(inFile);
  ana->ana_end();
  cout << "Histfile written. Congratz!" << endl;
}