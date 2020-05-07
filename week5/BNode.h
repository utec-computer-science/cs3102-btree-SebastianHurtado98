#ifndef BNODE_H
#define BNODE_H

#include <iostream>
#include <vector>
#include "Macros.h"
using namespace std;

template<typename T>
class BNode {
  public: 
  typedef T value_t ;
  typedef vector<value_t> container_t;
  typedef vector<BNode*> pcontainer_t;

  unsigned int order;
  container_t data;
  //BNode** children;
  pcontainer_t children;
  size_t sizeOfContainer;
  BNode** parent;
  int childrenCount;

  BNode( unsigned int order = 4)
  :order(order){
    //children = new BNode*[B_NODE_ORDER];
    children.resize(order,nullptr);
    data.resize(order, 0);
    sizeOfContainer = 0;
    parent = nullptr;
    childrenCount = 0;
  }
  
  int insertToContainer(value_t value){

    int index = sizeOfContainer - 1;

    while(index >= 0 && data[index] > value){
      data[index + 1] = data[index];
      index--;
    }
    data[++index] = value;
    sizeOfContainer++;
    return index;
  }

  value_t get_pivot() {
    return this->data[1];
  }


  void get_left(BNode* &newNode) {
    newNode->insertToContainer(this->data[0]);
    if (this->children[0] != nullptr) newNode->children[0] = this->children[0];
    if (this->children[1] != nullptr) newNode->children[1] = this->children[1];

  }
  void get_right(BNode* &newNode) {
    newNode->insertToContainer(this->data[2]);
    newNode->insertToContainer(this->data[3]); 
    if (this->children[2] != nullptr) newNode->children[0] = this->children[2];
    if (this->children[3] != nullptr) newNode->children[1] = this->children[3];
  }


  bool isContainerFull(){
    return sizeOfContainer == order;
  }

  
  
  BNode* getNextChild(value_t value){
    int j=0;
    for(int i = 0; i < sizeOfContainer; i++){
      if (value <= data[i]) {
        j = i;
        return children[i];
      }
    }
    return children[sizeOfContainer];
  }

  



  ~BNode(void){}
};


#endif