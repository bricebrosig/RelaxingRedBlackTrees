
CP=g++
OUTDIR=bin/
OBJDIR=obj/
CPFLAGS=-Wall -pedantic -std=c++14

main: main.cpp redblack_mod avl
	$(CP) -o proj2 $(CPFLAGS) main.cpp redblack.o rb_node.o avl_node.o

redblack_mod: MOD_RB/redblack.cpp MOD_RB/redblack.h node_mod
	$(CP) -c MOD_RB/redblack.cpp $(CPFLAGS) -o redblack.o node.o

node_mod: MOD_RB/node.cpp MOD_RB/node.h
	$(CP) -c MOD_RB/node.cpp $(CPFLAGS) -o rb_node.o

avl: AVL/avl.cpp AVL/avl.h
	$(CP) -c AVL/avl.cpp $(CPFLAGS) -o avl_node.o

clean:
	$(RM) *.o proj2