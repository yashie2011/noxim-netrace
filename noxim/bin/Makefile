##### LIBRARIES CONFIGURATION #####

SYSTEMC := /usr/local/systemc-2.3.1
YAML    := /usr


##### DIRECTORIES #####

SYSTEMC_LIBS := $(wildcard $(SYSTEMC)/lib-*)

SRCDIR  := ../src
SUBDIRS := $(filter %/,$(wildcard $(SRCDIR)/*/))
OBJDIR  := ./build

SRCS := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(addsuffix *.cpp,$(SUBDIRS))) 
CSOURCES := ../src/netrace.c
OBJS := $(subst $(SRCDIR),$(OBJDIR),$(CSOURCES:.c=.o)) $(subst $(SRCDIR),$(OBJDIR),$(SRCS:.cpp=.o))


MODULE := noxim


##### COMPILER OPTIONS #####

CXX      := g++
CC		 := gcc
OPT      := -O3
DEBUG    := # -g -DDEBUG
OTHER    := -Wall -DSC_NO_WRITE_CHECK --std=c++11 # -Wno-deprecated
CXXFLAGS := $(OPT) $(OTHER) $(DEBUG)

INCDIR := -I$(SRCDIR) -isystem $(SYSTEMC)/include -I$(YAML)/include
LIBDIR := -L$(SRCDIR) -L$(SYSTEMC_LIBS) -L$(YAML)/lib/x86_64-linux-gnu

LIBS := -lsystemc -lm -lyaml-cpp 

SPACE := $(subst ,, )
VPATH := $(SRCDIR):$(subst $(SPACE),:,$(SUBDIRS))

##### RULES #####

$(MODULE): $(OBJS)
	$(CXX) $(LIBDIR) $^ $(LIBS) -o $@ 2>&1 | c++filt

$(OBJDIR)/netrace.o: netrace.c
	$(CC) -c -o $@ $<

$(OBJDIR)/%.o: %.cpp 
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCDIR) -c $< -o $@

clean:
	rm -f $(OBJS) $(MODULE) *~

depend: 
	makedepend $(SRCS) -Y -f- 2>/dev/null | sed 's_$(SRCDIR)_$(OBJDIR)_' > Makefile.deps

-include Makefile.deps
