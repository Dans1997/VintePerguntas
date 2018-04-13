IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR= ./obj
LDIR= ../lib

_DEPS=funcoes.h catch.hpp
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=main.o funcoes.o 
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o:%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: jogo test

jogo:	$(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

test: testa_arvore.cpp funcoes.c
	g++ -std=c++11 -o test -ftest-coverage -fprofile-arcs testa_arvore.cpp funcoes.c -I../include

.PHONY:	clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
