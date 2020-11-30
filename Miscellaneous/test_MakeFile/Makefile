# Define C++ compiler
CXX = g++

# Define linker
LINKER = g++

# Debug flag: either nothing or -ggdb
DEBUGFLAG =

# Opitmization flag
OPTFLAG = -O2

# Path to PicoDst (either absolute or relative)
PICODSTPATH = /mnt/pool/2/lbavinh/Soft/PicoDst/include

# ROOT flag: -D__ROOT__
ROOTFLAG = /mnt/pool/4/anikeev/root-6.18.02/builddir/bin

# Define C++ flags
CXXFLAGS = $(shell root-config --cflags) -I. -I$(PICODSTPATH) $(OPTFLAG) -fPIC -Wall -pipe -std=c++11
CXXFLAGS += $(DEBUGFLAG)

# Define libraries to be added
LIBS = $(shell root-config --libs) -lEG
LIBS += -L$(PICODSTPATH) -lPicoDst

# Define path to include directories
INCS = $(shell root-config --incdir)

# Linker flags
LDFLAGS = $(shell root-config --cflags) -I. -I$(PICODSTPATH) $(OPTFLAG) -fPIC -Wall -pipe

all: processPicoDstStandalone

# Compile C++ files
processPicoDstStandalone: processPicoDstStandalone.o
	$(LINKER) $< $(LDFLAGS) $(LIBS) $(GLIBS) -o $@

# Compile C++ files
%.o: %.C
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	@echo 'Compiling: $@ $<'

# PHONY options
.PHONY: clean distclean

# Remove object files and dictionary
clean:
	rm -vf *.o

# Remove object files, dictionary and library
distclean:
	rm -vf *.o processPicoDstStandalone