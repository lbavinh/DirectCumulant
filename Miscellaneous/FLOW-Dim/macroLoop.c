
#include "/home/dim2/FLOW2/MyClass.C"

void start(){
MyClass t("~/FLOW2/10k/Test20NEW_V2pt_1.root");
t.Book();t.Loop();t.SaveData("~/FLOW2/10k/OUT20exp.root");
}
void macroLoop(){ start(); }
