
#include "MyClass.C"
#include "READ.C"
/*void start(){
MyClass t("~/FLOW4/5k/Test.root");
t.Book();t.Loop();t.SaveData("~/FLOW3/OUTNEW.root");
}
void macroLoop(){ start();read("~/FLOW3/OUTNEW.root"); }
*/
void start(){
MyClass t("~/FLOW5/OUT/file5M.root");
t.Book();t.Loop();t.SaveData("~/FLOW5/OUT/OUT2M.root");
}
void macroLoop(){ start();read("~/FLOW5/OUT/OUT2M.root"); }
