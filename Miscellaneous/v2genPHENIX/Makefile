CXXFLAGS = -I. -I$(ROOTSYS)/include -I$(OFFLINE_MAIN)/include
ROOTLIBS := $(shell root-config --libs)

LDFLAGS =


CXX = g++ 
FLAGS = -Wall -g -m32
hTana.so: hTana.C hTana_dict.C hTanaLinkDef.h
	$(CXX)  $(FLAGS)   $(CXXFLAGS) -o $@ -shared $< hTana_dict.C  -g $(ROOTLIBS)

hTana_dict.C : hTana.h hTanaLinkDef.h
	rootcint -f $@ -c $(CXXFLAGS) $(FLAGS) $^




