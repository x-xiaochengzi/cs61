PROGRAMS = makezombies pipesizer filtermultiples primesieve \
	timedwait-poll \
	timedwait-block \
	timedwait-blockvar timedwait-waitblockwait \
	timedwait-alarm \
	timedwait-selfpipe timedwait-selectpipe timedwait-signalfd \
	timedwait-threads

all: $(PROGRAMS)

ALLPROGRAMS = $(PROGRAMS)
CONFIGMK ?= config.mk

O ?= 3
PTHREAD ?= 1
include ../common/rules.mk
-include $(CONFIGMK)

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

$(PROGRAMS): \
%: %.o hexdump.o
	$(CXX) $(CXXFLAGS) $(O) $(LDFLAGS) -o $@ $^ $(LIBS)


clean:
	rm -f $(ALLPROGRAMS) *.o
	rm -rf $(DEPSDIR) *.dSYM

.PHONY: all always clean
