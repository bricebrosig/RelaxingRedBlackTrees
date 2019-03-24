#include <iostream>
#include <queue>
using namespace std;

enum COLOR { RED, BLACK };

class Node
{
  public:
    int val;
    COLOR color;
    Node *left, *right, *parent;

    Node(int val);

    // returns pointer to uncle
    Node *uncle();

    // check if node is left child of parent
    bool isOnLeft() { return this == parent->left; }

    // returns pointer to sibling
    Node *sibling();

    // moves node down and moves given node in its place
    void moveDown(Node *nParent);

    bool hasRedChild();
};