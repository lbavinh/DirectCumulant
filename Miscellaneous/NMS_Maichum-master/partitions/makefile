CXXFLAGS=-ansi -Wall -pedantic -O3

.PHONY: all clean

all: user stirling

partition.o: partition.C partition.h
user.o: user.C partition.h

stirling.o: stirling.C

user: user.o partition.o
	$(CXX) $(CXXFLAGS) -o $@ $^
	strip -s $@

stirling: stirling.o
	$(CXX) $(CXXFLAGS) -o $@ $^
	strip -s $@

clean:
	-rm *.o *.rpo user stirling
