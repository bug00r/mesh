_CFLAGS:=$(CFLAGS)
CFLAGS:=$(_CFLAGS)
_LDFLAGS:=$(LDFLAGS)
LDFLAGS:=$(_LDFLAGS)

ARFLAGS?=rcs
PATHSEP?=/
BUILDROOT?=build

BUILDDIR?=$(BUILDROOT)$(PATHSEP)$(CC)
BUILDPATH?=$(BUILDDIR)$(PATHSEP)

ifndef PREFIX
	INSTALL_ROOT=$(BUILDPATH)
else
	INSTALL_ROOT=$(PREFIX)$(PATHSEP)
	ifeq ($(INSTALL_ROOT),/)
	INSTALL_ROOT=$(BUILDPATH)
	endif
endif

ifdef DEBUG
	CFLAGS+=-ggdb
	ifeq ($(DEBUG),)
	CFLAGS+=-Ddebug=1
	else 
	CFLAGS+=-Ddebug=$(DEBUG)
	endif
endif

ifeq ($(M32),1)
	CFLAGS+=-m32
	BIT_SUFFIX+=32
endif

override CFLAGS+=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra
#-ggdb
#-pg for profiling 

override LDFLAGS+=-L/c/dev/lib$(BIT_SUFFIX)
override CFLAGS+=-I. -I/c/dev/include

SRC=mesh.c mesh_builder.c mesh_tree.c

NAME=mesh
LIBNAME=lib$(NAME).a
LIB=$(BUILDPATH)$(LIBNAME)
OBJS=$(BUILDPATH)$(NAME).o $(BUILDPATH)mesh_tree.o $(BUILDPATH)mesh_builder.o

TESTSRC=test_$(NAME).c
TESTBIN=$(BUILDPATH)test_$(NAME).exe
TESTLIB=-l$(NAME) -lshape -lcolor -lgeometry -lutilsmath -lmat -lvec -ldl_list
TESTLIBDIR=-L$(BUILDDIR) $(LIBSDIR)

override LDFLAGS+=$(TESTLIBDIR) $(TESTLIB)

all: mkbuilddir $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJS):
	$(CC) $(CFLAGS) -c $(@F:.o=.c) -o $@
	
$(TESTBIN): $(LIB)
	$(CC) $(CFLAGS) $(@F:.exe=.c) -o $@ $(LDFLAGS)

.PHONY: clean mkbuilddir test

test: mkbuilddir $(TESTBIN)
	./$(TESTBIN)

mkbuilddir:
	mkdir -p $(BUILDDIR)

clean:
	-rm -dr $(BUILDROOT)

install:
	mkdir -p $(INSTALL_ROOT)include
	mkdir -p $(INSTALL_ROOT)lib$(BIT_SUFFIX)
	cp ./$(NAME).h $(INSTALL_ROOT)include$(PATHSEP)$(NAME).h
	cp ./$(NAME)_builder.h $(INSTALL_ROOT)include$(PATHSEP)$(NAME)_builder.h
	cp ./$(NAME)_tree.h $(INSTALL_ROOT)include$(PATHSEP)$(NAME)_tree.h
	cp $(LIB) $(INSTALL_ROOT)lib$(BIT_SUFFIX)$(PATHSEP)$(LIBNAME)
	