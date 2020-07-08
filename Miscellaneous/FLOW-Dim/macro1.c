
#include "/home/dim2/FLOW2/MyClass11.C"

void start(){
MyClass t("/home/dim2/FLOW2/100k/file20_pt.root");
t.Book();t.Loop();t.SaveData("~/FLOW2/10k/OUT20_1.root");
}
void macro1(){ start(); }
