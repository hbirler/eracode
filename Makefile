CC := gcc
SRCDIR := src
BUILDDIR := build
TARGETDIR := bin
TARGET := $(TARGETDIR)/project
INCDIR := include
 
SRCEXT := c
ASMEXT := asm
INCEXT := h
SOURCES := $(wildcard $(SRCDIR)/*.$(SRCEXT)) $(wildcard $(SRCDIR)/*.$(ASMEXT))
HEADERS := $(wildcard $(INCDIR)/*.$(INCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%.o,$(SOURCES))
CFLAGS := -Wall -std=c99
LIB := -lm
INC := -I include

all: compile

compile: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	$(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.asm.o: $(SRCDIR)/%.$(ASMEXT) $(HEADERS)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(TARGETDIR)
	nasm -f elf64 -o $@ $<

$(BUILDDIR)/%.c.o: $(SRCDIR)/%.$(SRCEXT) $(HEADERS)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(TARGETDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

$(REQDIRS):
	@mkdir -p $(REQDIRS)

clean:
	@echo " Cleaning...";
	$(RM) -r $(BUILDDIR) $(TARGET)

# Tests
bench: $(TARGET)
	$(TARGET) bench

test: $(TARGET)
	$(TARGET) test