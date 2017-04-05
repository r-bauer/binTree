# makefile for generic binary search tree 

IDIR=./include
SDIR=./src
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR=./lib

LIBS=-lm

_DEPS=	btapp.h \
	btdriver.h \
	btgen.h \
	main.h
DEPS=$(addprefix $(IDIR)/, $(_DEPS))

_OBJ=	main.o \
	btdriver.o \
	btapp.o \
	btgen.o
 
#OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))
OBJ=$(addprefix $(ODIR)/, $(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

binTree: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# https://www.gnu.org/software/make/manual/make.html#Prerequisite-Types
all: $(OBJ)

$(OBJ): | $(ODIR)

$(ODIR):
	mkdir -p $(ODIR)

.PHONY:	clean

clean: 
	rm -fr $(ODIR) binTree* *~ $(IDIR)/*~ $(SDIR)/*~

