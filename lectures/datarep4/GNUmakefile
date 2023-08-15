PROGRAMS = $(patsubst %.cc,%,$(wildcard passing[0-9].cc)) \
	vector union segments stack stackrecurse stackmulti stacklayout
all: $(PROGRAMS)

ALLPROGRAMS = $(PROGRAMS)

# Default to no optimization
O ?= 0

include ../common/rules.mk


# Rules for making object files (i.e., parts of executables)
# from source files

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<


# Rules for making executables (runnable programs) from object files

$(PROGRAMS): \
%: %.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^


clean:
	rm -rf $(ALLPROGRAMS) *.o $(DEPSDIR)

.PHONY: all clean
.PRECIOUS: addf%.o
