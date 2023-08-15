PROGRAMS = printx dumpx intsort $(patsubst %.cc,%,$(wildcard intsort[1-6].cc)) intgen
all: $(PROGRAMS)

include ../common/rules.mk

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

printx dumpx intsort intsort1 intsort2 intsort3 intsort4 intsort5 intsort6 intgen: \
%: %.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^


clean:
	rm -rf $(PROGRAMS) $(wildcard intsort[1-6]) *.o $(DEPSDIR)

.PHONY: all clean
