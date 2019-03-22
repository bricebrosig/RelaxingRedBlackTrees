
CP=g++
OUTDIR=bin/
OBJDIR=obj/
CPFLAGS=-Wall -pedantic -std=c++14

main: main.cpp redblack
	$(CP) -o proj2 $(CPFLAGS) main.cpp redblack.o node.o

redblack: redblack.cpp redblack.h node
	$(CP) -c redblack.cpp $(CPFLAGS) -o redblack.o node.o

node: node.cpp node.h
	$(CP) -c node.cpp $(CPFLAGS) -o node.o

clean:
	$(RM) *.o proj2