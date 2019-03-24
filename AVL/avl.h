// C++ program to insert a node in AVL tree  
//#include <bits/stdc++.h>
#include <iostream>
using namespace std; 
  
// An AVL tree node  
class avl_Node  
{  
    public: 
    int key;  
    avl_Node *left;  
    avl_Node *right;  
    int height;  
};  
  
// A utility function to get maximum 
// of two integers  
int max(int a, int b);  
  
// A utility function to get the  
// height of the tree  
int height(avl_Node *N); 
  
// A utility function to get maximum 
// of two integers  
int max(int a, int b); 
  
/* Helper function that allocates a  
   new node with the given key and  
   NULL left and right pointers. */
avl_Node* newNode(int key);  
  
// A utility function to right 
// rotate subtree rooted with y  
// See the diagram given above.  
avl_Node *rightRotate(avl_Node *y);  
  
// A utility function to left  
// rotate subtree rooted with x  
// See the diagram given above.  
avl_Node *leftRotate(avl_Node *x);  
  
// Get Balance factor of node N  
int getBalance(avl_Node *N);  
  
// Recursive function to insert a key 
// in the subtree rooted with node and 
// returns the new root of the subtree.  
avl_Node* insert(avl_Node* node, int key);  
  
// A utility function to print preorder  
// traversal of the tree.  
// The function also prints height  
// of every node  
void preOrder(avl_Node *root);