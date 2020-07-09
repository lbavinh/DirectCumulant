#include "/home/dim2/FLOW2/generator.C"

void start(){
generator("~/FLOW2/10k/Test20NEW_V2pt_1.root",10000);
generator("~/FLOW2/10k/Test20NEW_V2pt_2.root",10000);
/*generator("~/FLOW2/20k/Test20_V2pt_2.root",20000);
generator("~/FLOW2/20k/Test20_V2pt_3.root",20000);
generator("~/FLOW2/20k/Test20_V2pt_4.root",20000);
generator("~/FLOW2/20k/Test20_V2pt_5.root",20000)*/;
}
void macroGen(){ start(); }

