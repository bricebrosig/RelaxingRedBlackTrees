
CP=g++
OUTDIR=bin/
OBJDIR=obj/
CPFLAGS=-Wall -pedantic -std=c++14

main: main.cpp redblack_mod avl redblack
	$(CP) -o proj2 $(CPFLAGS) main.cpp m_redblack.o node.o avl.o redblack.o

redblack_mod: MOD_RB/m_redblack.cpp MOD_RB/m_redblack.h node
	$(CP) -c MOD_RB/m_redblack.cpp $(CPFLAGS) -o m_redblack.o

node: node.cpp node.h
	$(CP) -c node.cpp $(CPFLAGS) -o node.o

avl: AVL/avl.cpp AVL/avl.h
	$(CP) -c AVL/avl.cpp $(CPFLAGS) -o avl.o

redblack: RB/redblack.cpp RB/redblack.h
	$(CP) -c RB/redblack.cpp $(CPFLAGS) -o redblack.o

clean:
	$(RM) *.o proj2