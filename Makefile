PACKAGES = glu gtkglextmm-1.2 gtkmm-2.4 bullet
CXXFLAGS += -std=c++14 -Wall -Wextra 
MAINSRC = ./src/petanqulator.cpp 

ifeq ($(DEBUG), 1)
	CXXFLAGS += -DDEBUG -O0 -g
else
	CXXFLAGS += -DNDEBUG -O2
endif

CXXFLAGS += `pkg-config --cflags $(PACKAGES)`
LDFLAGS +=`pkg-config --libs-only-L --libs-only-other $(PACKAGES)`
LIBS +=`pkg-config --libs-only-l $(PACKAGES)`
BINDIR = ./bin
OBJDIR = ./obj
SRCDIR = ./src
SRC = $(filter-out $(MAINSRC), $(shell find $(SRCDIR) -name "*.cpp"))
OBJ = $(subst $(SRCDIR)/, $(OBJDIR)/, $(SRC:.cpp=.o))
BIN = $(subst $(SRCDIR)/, $(BINDIR)/, $(MAINSRC:.cpp=.out))
UNIT_TESTS_BIN = $(BINDIR)/unit_tests.out 
UNIT_TESTS_TMP = unit_tests.cpp

.PHONY: all clean unit_tests cppcheck
.SECONDARY:

all: $(BIN)
$(BINDIR)/%.out: $(OBJ) $(OBJDIR)/%.o
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	find $(OBJDIR) -name "*.o" | xargs rm -rf $(BIN) tags $(UNIT_TESTS_BIN)

# build ctags data (code navigation)
tags: $(SRC) $(MAINSRC)
	ctags -R

# build unit tests (using the cxxtest framework)
# unit tests should be written in $(SRCDIR)/*_test.hpp files
# execute $(UNIT_TESTS_BIN) to run unit tests
UNIT_TESTS_SRC = $(shell find $(SRCDIR) -name "*_test.hpp")
unit_tests: $(UNIT_TESTS_BIN)
$(UNIT_TESTS_BIN): $(UNIT_TESTS_SRC) $(OBJ)
	cxxtestgen --error-printer -o $(UNIT_TESTS_TMP) $(UNIT_TESTS_SRC)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(UNIT_TESTS_TMP) $(OBJ) $(LIBS)
	rm $(UNIT_TESTS_TMP)

# static analysis
cppcheck:
	cppcheck --enable=all --inconclusive src/*pp

