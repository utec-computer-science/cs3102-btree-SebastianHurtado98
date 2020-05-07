#include <iostream>
#include <vector>
#include <stack>
#include <time.h>
#include <chrono> 
#include <stdio.h>
#include <unistd.h>
 
#include "Tree.h"

int main() {
  typedef BSTNode<float> bst_node;
  typedef BNode<int> b_node;
  typedef Tree<bst_node> bst_tree;
  typedef Tree<b_node> b_tree;

  bst_tree tree(4); 
  tree.insert(30);
  tree.insert(10);
  tree.insert(60);
  
  cout << tree << endl;


  b_tree btree(4); 
  btree.insert(30);
  btree.insert(10);
  btree.insert(60);
  btree.insert(90);
  btree.insert(100);
  cout << btree << endl;
}
