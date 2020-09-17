


###########################################################################
# TOY MonteCarlo binary

.PHONY: toymc

toymc:bin/toymc.app

bin/toymc.app: $(TOYMC) ToyMC/cint_dictionary.o
	@mkdir -p bin
	$(LD) $(LDFLAGS) ${ROOTGLIBS} ${ROOTLIBS} -o $@ $^

# Produces .o files for ToyMC
$(TOYMC) : %.o: %.cxx check_gcc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@

-include .depend_toymc

toymc_depend: .depend_toymc

.depend_toymc: $(TOYMC:%.o=%.cxx) 
	rm -f ./.depend_toymc
	$(CXX) $(CPPFLAGS) $(ROOTCFLAGS) -MM $^ -MT $(TOYMC) > ./.depend_toymc


ToyMC/cint_dictionary.cxx: ToyMC/LinkDef.h
	rootcint -v4 -f $@ -c ToyMC/ToyMCEvent.h ToyMC/ToyMCGenerator.h $<
	-@[ -e "ToyMC/cint_dictionary_rdict.pcm" ] && mv -f ToyMC/cint_dictionary_rdict.pcm bin/        # ROOT 6

ToyMC/cint_dictionary.o: ToyMC/cint_dictionary.cxx
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(ROOTCFLAGS) $< -o $@

# include the toymc.o because it has the implementation of the logger
lib/ToyMC.so: ToyMC/cint_dictionary.o $(TOYMC)
	@mkdir -p lib
	$(LD) $(SOFLAGS) $(LDFLAGS) $(ROOTLIBS) $^ -o $@

.PHONY: rootlib
rootlib: lib/ToyMC.so


clean_toymc:
	@rm -f ToyMC/*.o
	@rm -f ToyMC/cint_dictionary.*
	@rm -f ToyMC/*.pcm


# TOY MonteCarlo binary
###########################################################################
