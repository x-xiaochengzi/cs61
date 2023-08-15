PROGRAMS = processex fork1 fork2 forkmix syscall-forkmix forkorder

all: $(PROGRAMS)

ALLPROGRAMS = $(PROGRAMS) matrixmultiply-blas
CONFIGMK ?= config.mk

O ?= 3
include ../common/rules.mk
-include $(CONFIGMK)

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

processex fork1 fork2 fork3 forkmix syscall-forkmix forkorder: \
%: %.o hexdump.o
	$(CXX) $(CXXFLAGS) $(O) $(LDFLAGS) -o $@ $^ $(LIBS)


clean:
	rm -f $(ALLPROGRAMS) *.o
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all always clean
