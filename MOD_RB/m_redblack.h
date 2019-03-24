#include <iostream>
#include "../node.h"
#include <queue>
using namespace std;

class mod_RBTree
{
  Node *root;

  void leftRotate(Node *x); // left rotates the given node
  void rightRotate(Node *x);
  void swapColors(Node *x1, Node *x2);
  void swapValues(Node *u, Node *v);
  void fixRedRed(Node *x);   // fix red red at given node
  Node *successor(Node *x);  // in the subtree of the given node find node that do not have a left child
  void levelOrder(Node *x); // prints level order for given node
  void inorder(Node *x);    // prints inorder recursively

public:
  mod_RBTree() { root = NULL; }
  Node *getRoot() { return root; }

  // searches for given value
  // if found returns the node (used for delete)
  // else returns the last node while traversing (used in insert)
  Node *search(int n);
  void insert(int n);      // inserts the given value to tree
  void printInOrder();     // prints inorder of the tree
  void printLevelOrder();
  // prints level order of the tree
};