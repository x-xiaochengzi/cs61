PROGRAMS = manyfloat copytest
BASEPROGRAMS = manyfloat copytest
BUILDABLEASM := $(patsubst asmsrc/%.cc,%.s,$(wildcard asmsrc/*.cc))
all: $(PROGRAMS) $(BUILDABLEASM)

ALLPROGRAMS = $(PROGRAMS)

variants = $(1) $(addsuffix -san,$(1)) $(addsuffix -noopt,$(1)) \
	$(addsuffix -clang,$(1)) $(addsuffix -clang-noopt,$(1)) \
	$(addsuffix -gcc,$(1)) $(addsuffix -gcc-noopt,$(1))

NEED_CXX_GCC = 1
CXXFLAGS += -march=x86-64-v2
O ?= 1
include ../common/rules.mk

UNSAFEFLAGS := -U_FORTIFY_SOURCE -fno-stack-protector


# Rules for making object files (i.e., parts of executables)
# from source files

%.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

%-san.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SANFLAGS) $(DEPCFLAGS) $(O) -o $@ -c $<

%-clang.o: %.cc $(BUILDSTAMP)
	clang++ $(CPPFLAGS) $(CXXFLAGS) $(O) $(DEPCFLAGS) -o $@ -c $<

%-gcc.o: %.cc $(BUILDSTAMP)
	$(CXX_GCC) $(CPPFLAGS) $(CXXFLAGS) $(O) $(DEPCFLAGS) -o $@ -c $<

%-noopt.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -O0 $(DEPCFLAGS) -o $@ -c $<

%-clang-noopt.o: %.cc $(BUILDSTAMP)
	clang++ $(CPPFLAGS) $(CXXFLAGS) -O0 $(DEPCFLAGS) -o $@ -c $<

%-gcc-noopt.o: %.cc $(BUILDSTAMP)
	$(CXX_GCC) $(CPPFLAGS) $(CXXFLAGS) -O0 $(DEPCFLAGS) -o $@ -c $<

%-unsafe.o: %.cc $(BUILDSTAMP)
	$(CXX) $(CPPFLAGS) $(UNSAFEFLAGS) $(CXXFLAGS) -O1 $(DEPCFLAGS) -o $@ -c $<


# Rules for making assembly files from source files
%.s: %.cc GNUmakefile $(BUILDSTAMP)
	$(call flagged_compile_S,$<,$@,$(CXXFLAGS))

%-san.s: %.cc GNUmakefile $(BUILDSTAMP)
	$(call flagged_compile_S,$<,$@,$(CXXFLAGS) $(SANFLAGS))

%.s: src/%.cc GNUmakefile $(BUILDSTAMP)
	$(call flagged_compile_S,$<,$@,-I. $(CXXFLAGS))

%-unsafe.s: %.cc GNUmakefile $(BUILDSTAMP)
	$(call flagged_compile_S,$<,$@,$(UNSAFEFLAGS) $(CXXFLAGS))

%-unsafe.s: src/%.cc GNUmakefile $(BUILDSTAMP)
	$(call flagged_compile_S,$<,$@,-I. $(UNSAFEFLAGS) $(CXXFLAGS))

%.asm: %.o
	objdump -d $< > $@


# Rules for making executables (runnable programs) from object files

$(BASEPROGRAMS): \
%: %.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

$(addsuffix -san,$(BASEPROGRAMS)): \
%: %.o hexdump.o
	$(CXX) $(CXXFLAGS) $(SANFLAGS) $(LDFLAGS) $(O) -o $@ $^

$(addsuffix -clang,$(BASEPROGRAMS)): \
%: %.o hexdump.o
	clang++ $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

$(addsuffix -gcc,$(BASEPROGRAMS)): \
%: %.o hexdump.o
	$(CXX_GCC) $(CXXFLAGS) $(LDFLAGS) $(O) -o $@ $^

$(addsuffix -noopt,$(BASEPROGRAMS)): \
%: %.o hexdump.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -O0 -o $@ $^

$(addsuffix -gcc-noopt,$(BASEPROGRAMS)): \
%: %.o hexdump.o
	$(CXX_GCC) $(CXXFLAGS) $(LDFLAGS) -O0 -o $@ $^

$(addsuffix -clang-noopt,$(BASEPROGRAMS)): \
%: %.o hexdump.o
	clang++ $(CXXFLAGS) $(LDFLAGS) -O0 -o $@ $^


asmsrc.txt: always
	for i in $(foreach src,$(patsubst %.s,%,$(BUILDABLEASM)),$(wildcard $(src).cc src/$(src).cc)); do echo $$i; echo ====================; cat $$i; echo; echo; echo; done > $@

asms.txt: $(BUILDABLEASM) always
	for i in $(BUILDABLEASM); do echo $$i; echo ====================; cat $$i; echo; echo; echo; done > $@



clean:
	rm -rf $(call variants,$(ALLPROGRAMS)) *.o $(DEPSDIR) \
		$(BUILDABLEASM) $(patsubst %.cc,%.s,$(wildcard *.cc)) \
		asmsrc.txt asms.txt

.PHONY: all clean
