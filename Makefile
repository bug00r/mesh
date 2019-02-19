MAKE?=mingw32-make
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
	export outimg=-Doutput=1
endif

CFLAGS=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra -O1 $(debug)
#-ggdb
#-pg for profiling 
SRC=mesh.c mesh_builder.c mesh_tree.c

INCLUDEDIR=-I./../math/vec -I./../math/mat -I./../math/utils -I./../color -I./../shape -I.

LIBNAME=libmesh.a
OBJS=$(BUILDPATH)mesh.o $(BUILDPATH)mesh_tree.o $(BUILDPATH)mesh_builder.o

TESTSRC=test_mesh.c
TESTBIN=test_mesh.exe
TESTLIB=-lmesh -lshape -lcolor -lutilsmath -lmat -lvec  
TESTLIBDIR=-L$(BUILDDIR) \
		   -L./../shape/$(BUILDDIR) \
		   -L./../color/$(BUILDDIR) \
		   -L./../math/utils/$(BUILDDIR) \
		   -L./../math/mat/$(BUILDDIR) \
		   -L./../math/vec/$(BUILDDIR) 

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
	