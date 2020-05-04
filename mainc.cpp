#include <iostream>
#include <vector>
#include <stack>
#include <time.h>
#include <chrono> 
#include <stdio.h>
#include <unistd.h>
 
#include "Tree.h"


// CHICOS UNANSE AL ZOOM
// ZOOM: https://utec.zoom.us/j/815711285

int main() {
  typedef BSTNode<float> bst_node;
  typedef BNode<int> b_node;
  typedef Tree<bst_node> bst_tree;

  bst_tree tree(4); 
  tree.insert(30);
  tree.insert(10);
  tree.insert(60);
  
  cout << tree << endl;
}
