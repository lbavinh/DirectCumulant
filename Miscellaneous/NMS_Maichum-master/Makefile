

NAME            := multicumulants
#http://semver.org/
VERSION         := 0.1.1


########################################## 
# ROOT
ROOT            := root
ROOTFLAGS       := -l -b -q 

ROOTCFLAGS      = $(shell root-config --cflags)
ROOTLDFLAGS     = $(shell root-config --ldflags)
ROOTLIBS        = $(shell root-config --libs)
ROOTLDFLAGS     = $(shell root-config --ldflags)
ROOT_ARCH       = $(shell root-config --arch)


CXX             := g++ -c  -std=c++11 -g
CXXFLAGS        := -fPIC -Wall -Wextra -pedantic $(ROOTCFLAGS)
CPPFLAGS        := -I. -I./vendor/loguru

LD              := g++
LDFLAGS         := $(ROOTCFLAGS)
#LDFLAGS         := -Wl $(ROOTCFLAGS)
SOFLAGS         := -shared

MINGXXVERSION := 4.1
GXXVERSION := $(shell g++ -dumpversion | cut -f1,2,3 -d.)
GXXVERSIONGTEQ4 := $(shell expr `g++ -dumpversion | cut -f1,2 -d.` \>= $(MINGXXVERSION))


#------------------------------------------------------------------------------
HEADERS         :=      MultiCumulants/QVector.h \
			MultiCumulants/QVectorSet.h \
			MultiCumulants/NativeMaskLUT.h \
			MultiCumulants/QTerms.h \
			MultiCumulants/Subsets.h \
			MultiCumulants/Algorithm.h \
			MultiCumulants/Correlator.h \
			MultiCumulants/Cumulant.h \
			ToyMC/ToyMCEvent.h \
			ToyMC/ToyMCGenerator.h \
			ToyMC/ToyMCParticle.h \
                        ToyMC/ToyMCDistGenerator.h \
                        ToyMC/ToyMCFlowDistGenerator.h \
			correlations/Correlator.hh \
			correlations/FromQVector.hh \
			correlations/NestedLoops.hh \
			correlations/QVector.hh \
			correlations/Result.hh \
			correlations/Types.hh \
			correlations/closed/FromQVector.hh \
			correlations/recurrence/FromQVector.hh \
			correlations/recursive/FromQVector.hh \
			correlations/recursive/NestedLoops.hh

# Objects to compile into ToyMc binary
TOYMC           := tests/toymc.o



# this works for make v 3.8 and newer
.DEFAULT_GOAL := toymc

# 
check_gcc:
ifeq "$(GXXVERSIONGTEQ4)" "1"
	@echo "Using g++ version: $(GXXVERSION)"
else 
	$(error ERROR: must use g++ version $(MINGXXVERSION) or newer)
endif


include ToyMC/Makefile



###########################################################################
# Generic development testing binary
tests/development.o: tests/development.cxx $(HEADERS) check_gcc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

bin/dev.app: tests/development.o
	@mkdir -p bin
	$(LD) $(LDFLAGS) ${ROOTGLIBS} ${ROOTLIBS} -o $@ $^

.PHONY: dev
dev:bin/dev.app
# Generic development testing binary
###########################################################################


############################################################################
# Generic partition testing binary
tests/partition.o: tests/partition.cxx $(HEADERS) check_gcc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

bin/part.app: tests/partition.o
	@mkdir -p bin
	$(LD) $(LDFLAGS) ${ROOTGLIBS} ${ROOTLIBS} -o $@ $^

.PHONY: part
part:bin/part.app
# Generic development testing binary
###########################################################################


.PHONY: clean
clean: clean_toymc
	@rm -f bin/*.app
	@rm -f tests/*.o
	@rm -f .depend_*



# DO NOT DELETE
