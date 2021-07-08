#MAKE?=mingw32-make
AR?=ar
ARFLAGS?=rcs
PATHSEP?=/
CC=gcc
BUILDROOT?=build

ifeq ($(CLANG),1)
	export CC=clang
endif

BUILDDIR?=$(BUILDROOT)$(PATHSEP)$(CC)
BUILDPATH?=$(BUILDDIR)$(PATHSEP)

INSTALL_ROOT?=$(BUILDPATH)

ifeq ($(DEBUG),1)
	export debug=-ggdb -Ddebug=1
	export isdebug=1
endif

ifeq ($(ANALYSIS),1)
	export analysis=-Danalysis=1
	export isanalysis=1
endif

ifeq ($(DEBUG),2)
	export debug=-ggdb -Ddebug=2
	export isdebug=1
endif

ifeq ($(DEBUG),3)
	export debug=-ggdb -Ddebug=3
	export isdebug=1
endif

ifeq ($(OUTPUT),1)
	export outimg= -Doutput=1
endif

BIT_SUFFIX=

ifeq ($(M32),1)
	CFLAGS+=-m32
	BIT_SUFFIX+=32
endif

CFLAGS+=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra $(debug)
#-ggdb
#-pg for profiling 

LIB?=-L/c/dev/lib$(BIT_SUFFIX)
INCLUDE?=-I/c/dev/include -I.

SRC=mesh.c mesh_builder.c mesh_tree.c

INCLUDEDIR=$(INCLUDE) -I.

LIBNAME=libmesh.a
OBJS=$(BUILDPATH)mesh.o $(BUILDPATH)mesh_tree.o $(BUILDPATH)mesh_builder.o

TESTSRC=test_mesh.c
TESTBIN=test_mesh.exe
TESTLIB=-lmesh -lshape -lcolor -lutilsmath -lmat -lvec  
TESTLIBDIR=-L$(BUILDDIR) $(LIB)

all: mkbuilddir $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(TESTBIN) test

$(BUILDPATH)$(LIBNAME): $(OBJS)
	$(AR) $(ARFLAGS) $(BUILDPATH)$(LIBNAME) $(OBJS)

$(BUILDPATH)mesh_builder.o: mesh_builder.c mesh_builder.h
	$(CC) $(CFLAGS) -c mesh_builder.c -o $(BUILDPATH)mesh_builder.o  $(INCLUDEDIR) 

$(BUILDPATH)mesh_tree.o: mesh_tree.c mesh_tree.h
	$(CC) $(CFLAGS) -c mesh_tree.c -o $(BUILDPATH)mesh_tree.o  $(INCLUDEDIR)
	
$(BUILDPATH)mesh.o: mesh.c mesh.h
	$(CC) $(CFLAGS) -c mesh.c -o $(BUILDPATH)mesh.o $(INCLUDEDIR)
	
$(BUILDPATH)$(TESTBIN):
	$(CC) $(CFLAGS) $(TESTSRC) -o $(BUILDPATH)$(TESTBIN) $(INCLUDEDIR) $(TESTLIBDIR) $(TESTLIB)

.PHONY: clean mkbuilddir test

test:
	./$(BUILDPATH)$(TESTBIN)

mkbuilddir:
	mkdir -p $(BUILDDIR)

clean:
	-rm -dr $(BUILDROOT)

install:
	mkdir -p $(INSTALL_ROOT)include
	mkdir -p $(INSTALL_ROOT)lib$(BIT_SUFFIX)
	cp ./mesh.h $(INSTALL_ROOT)include/mesh.h
	cp ./mesh_builder.h $(INSTALL_ROOT)include/mesh_builder.h
	cp ./mesh_tree.h $(INSTALL_ROOT)include/mesh_tree.h
	cp $(BUILDPATH)$(LIBNAME) $(INSTALL_ROOT)lib$(BIT_SUFFIX)/$(LIBNAME)
	