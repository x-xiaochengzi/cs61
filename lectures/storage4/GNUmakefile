PROGRAMS = accessor list-inserter \
	matrixmultiply \
	$(filter-out matrixmultiply-blas,$(patsubst %.cc,%,$(wildcard matrixmultiply-*.cc)))

all: $(PROGRAMS)

ALLPROGRAMS = $(PROGRAMS) matrixmultiply-blas
CONFIGMK ?= config.mk

O ?= 3
include ../common/rules.mk
-include $(CONFIGMK)

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

accessor list-inserter: \
%: %.o hexdump.o
	$(CXX) $(CXXFLAGS) $(O) $(LDFLAGS) -o $@ $^ $(LIBS)

matrixmultiply: matrixmultiply.o hexdump.o
	$(CXX) $(CXXFLAGS) $(O) $(LDFLAGS) -o $@ $^ $(LIBS)

matrixmultiply-%: matrixmultiply-%.o hexdump.o
	$(CXX) $(CXXFLAGS) $(O) $(LDFLAGS) -o $@ $^ $(LIBS)

matrixmultiply-blas: matrixmultiply-blas.o hexdump.o
	$(CXX) $(CXXFLAGS) $(O) $(LDFLAGS) -o $@ $^ $(LIBS) -lblas


clean:
	rm -f $(ALLPROGRAMS) *.o
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all always clean
