PACKAGES = glu gtkglextmm-1.2 gtkmm-2.4 bullet
CXXFLAGS += -std=c++14 -Wall -Wextra 
MAINSRC = ./src/petanqulator.cpp 
ifeq ($(DEBUG), 1)
	override CXXFLAGS += -O0 -g
else
	override CXXFLAGS += -O2 -DNDEBUG
endif

override CXXFLAGS += `pkg-config --cflags $(PACKAGES)`
override LDFLAGS +=`pkg-config --libs-only-L --libs-only-other $(PACKAGES)`
override LIBS +=`pkg-config --libs-only-l $(PACKAGES)`
BINDIR = ./bin
OBJDIR = ./obj
SRCDIR = ./src
SRC = $(filter-out $(MAINSRC), $(shell find $(SRCDIR) -name "*.cpp"))
OBJ = $(subst $(SRCDIR)/, $(OBJDIR)/, $(SRC:.cpp=.o))
BIN = $(subst $(SRCDIR)/, $(BINDIR)/, $(MAINSRC:.cpp=.out))

.PHONY : all clean cppcheck 
.SECONDARY:

ALL: tags $(BIN)
	@echo ""
$(BINDIR)/%.out: $(OBJ) $(OBJDIR)/%.o
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(BIN) tags test.out
	find $(OBJDIR) -name "*.o" | xargs rm

# build ctags data (code navigation)
tags: $(SRC) $(MAINSRC)
	ctags -R

# static analysis
cppcheck:
	cppcheck --enable=all --inconclusive src/*pp


