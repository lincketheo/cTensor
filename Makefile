######################################################################
# @author      : theo (theo.j.lincke@gmail.com)
# @file        : Makefile
# @created     : Wednesday Dec 23, 2020 09:25:54 MST
######################################################################

CC=g++

IDIR =./include
ODIR=./obj
SDIR=./src

CFLAGS=-I$(IDIR)

LIBS=

_DEPS = Matrix.hpp
DEPS = $(patsubst %,$(IDIR)/%,(_DEPS))

_OBJ = main.o Matrix.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o

