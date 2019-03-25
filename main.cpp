#include "MOD_RB/m_redblack.h"
#include "AVL/avl.h"
#include "RB/redblack.h"
#include <random> //for the random gen
#include <chrono> //for seeding random time
#include <stdlib.h> //rand()
#include <stdio.h> //printf
#include "sys/time.h" //for timing the trees
using namespace std;

int main()
{
  std::vector<int> data;
  for(int i = 0; i < 100'000; i++)
    data.push_back(i);

  const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); //generate random value seed
  shuffle(data.begin(), data.end(), std::default_random_engine(seed));

  struct timeval begin, end, result; //hold the times for calculations

  /*
  Modifed RB Tree
  */

  std::cout << "\n\t==modified RBTree==\n" << std::endl;

  mod_RBTree tree;

  gettimeofday(&begin, NULL);
  for(auto d : data)
    tree.insert(d);
  gettimeofday(&end, NULL);
  timersub(&end, &begin, &result);
  //tree.printInOrder();
  //tree.printLevelOrder();

  int max = 0, tmp = 0;

  tree.getBlackHeights(tree.getRoot(), max, tmp);
  std::cout << "black Height: " << max << std::endl;
  std::cout << "total Height: " << tree.getHeights(tree.getRoot()) << std::endl;
  std::cout << "time to insert: " <<  (float)result.tv_sec + (float)result.tv_usec/1'000'000 << std::endl;

  /*
  AVL TREE STUFF BELOW
  */

  std::cout << "\n\t==AVL tree==\n" << std::endl;

  avl_Node *root = NULL;

  gettimeofday(&begin, NULL);
  for(auto d : data)
    root = avl_insert(root, d);
  gettimeofday(&end, NULL);
  timersub(&end, &begin, &result);

  std::cout << "total Height: " << avl_getHeight(root) << std::endl;
  std::cout << "time to insert: " <<  (float)result.tv_sec + (float)result.tv_usec/1'000'000 << std::endl;

  /*
    Normal BST
  */
 
  max = 0;
  tmp = 0;

  std::cout << "\n\t==Normal RBTree==\n " << std::endl;

  RBTree rb;
  
  gettimeofday(&begin, NULL);
  for(auto d : data)
    rb.insert(d);
  gettimeofday(&end, NULL);
  timersub(&end, &begin, &result);

  rb.getBlackHeights(rb.getRoot(), max, tmp);
  std::cout << "black Height: " << max << std::endl;
  std::cout << "total Height: " << rb.getHeights(rb.getRoot()) << std::endl;
  std::cout << "time to insert: " <<  (float)result.tv_sec + (float)result.tv_usec/1'000'000 << std::endl;

  return 0;
}