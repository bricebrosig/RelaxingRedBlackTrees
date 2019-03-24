#include <iostream>
#include "../node.h"
#include <queue>
using namespace std;

class RBTree
{
  Node *root;

  void leftRotate(Node *x); // left rotates the given node
  void rightRotate(Node *x);
  void swapColors(Node *x1, Node *x2);
  void swapValues(Node *u, Node *v);
  void fixRedRed(Node *x);   // fix red red at given node
  Node *successor(Node *x);  // in the subtree of the given node find node that do not have a left child
  Node *BSTreplace(Node *x); // find node that replaces a deleted node in BST
  void deleteNode(Node *v);  // deletes the given node
  void fixDoubleBlack(Node *x);
  void levelOrder(Node *x); // prints level order for given node
  void inorder(Node *x);    // prints inorder recursively

public:
  RBTree() { root = NULL; }
  Node *getRoot() { return root; }

  // searches for given value
  // if found returns the node (used for delete)
  // else returns the last node while traversing (used in insert)
  Node *search(int n);
  void insert(int n);      // inserts the given value to tree
  void deleteByVal(int n); // utility function that deletes the node with given value
  void printInOrder();     // prints inorder of the tree
  void printLevelOrder();
  // prints level order of the tree
};