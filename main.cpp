#include "MOD_RB/m_redblack.h"
#include "AVL/avl.h"
#include "RB/redblack.h"
using namespace std;

int main()
{
  /*
  Modifed RB Tree
  */
  mod_RBTree tree;

  tree.insert(7);
  tree.insert(3);
  tree.insert(18);
  tree.insert(10);
  tree.insert(22);
  tree.insert(8);
  tree.insert(11);
  tree.insert(26);
  tree.insert(2);
  tree.insert(6);
  tree.insert(13);

  tree.printInOrder();
  tree.printLevelOrder();

  tree.printInOrder();
  tree.printLevelOrder();

  /*
  AVL TREE STUFF BELOW
  */

  avl_Node *root = NULL;
  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 30);
  root = insert(root, 40);
  root = insert(root, 50);
  root = insert(root, 25);

  std::cout << "Preorder traversal of the "
               "constructed AVL tree is \n";
  preOrder(root);

  /*
  Normal RBTree stuff below
  */

  RBTree rb;

  rb.insert(7);
  rb.insert(3);
  rb.insert(18);
  rb.insert(10);
  rb.insert(22);
  rb.insert(8);
  rb.insert(11);
  rb.insert(26);
  rb.insert(2);
  rb.insert(6);
  rb.insert(13);

  rb.printInOrder();
  rb.printLevelOrder();

  rb.printInOrder();
  rb.printLevelOrder();

  return 0;
}