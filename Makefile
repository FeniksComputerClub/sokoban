# Add .d to Make's recognized suffixes.
SUFFIXES = .o .cxx .h .d

# We don't need to clean up when we're making these targets.
NODEPS := clean tags

# Find all the C++ files.
SOURCES := $(shell find . -name "*.cxx")

# These are the dependency files, which make will clean up after it creates them.
DEPFILES := $(patsubst %.cxx,%.d,$(SOURCES))

# Set our flags.
CXXFLAGS = -std=c++11 -Wall -g

all: test

# Don't use/create dependencies when we're cleaning, for instance.
ifeq (0, $(words $(findstring $(MAKECMDGOALS), $(NODEPS))))
  -include $(DEPFILES)
endif

# Automatically create dependency files.
%.d: %.cxx
	$(CXX) $(CXXFLAGS) -MM -MT '$(patsubst %.cxx,%.o,$<)' $< -MF $@

# Compile .cxx source files into .o object files.
%.o: %.cxx %.d
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# Executables.

test: test.o Board.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Other targets

clean:
	rm -f *.o *.d test

tags:
	ctags -f tags *.h *.cxx cwchess/*.h

.PHONY: clean tags
