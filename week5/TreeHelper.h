#ifndef TREE_HELPER_H
#define TREE_HELPER_H

#include <iostream>
#include "BNode.h"
#include "BPlusNode.h"
#include "BSTNode.h"
using namespace std;

template<typename  Node, typename  ValueNode, int Flag>
struct TreeHelper{
  typedef Node  node_t;
  typedef typename node_t::value_t value_t;
  
  static void  insert (node_t** head, const value_t& val, unsigned int order){
    cout << "el tipo de dato no es compatible" << endl;
  }

  static void  print (node_t** head, std::ostream &out){
  }
};


template<typename  ValueNode>
struct TreeHelper<BSTNode<ValueNode>,ValueNode,BST_NODE_FLAGXX>{
  typedef BSTNode<ValueNode>  node_t;
  typedef typename node_t::value_t value_t;
  
  static void  insert (node_t** head, const value_t& val, unsigned int order){
    auto temp = new node_t(val);
    
    if ((*head)== nullptr) {
      (*head) = temp;     
      return;
    }
    
    if ((*head)->data > val){
     insert(&(*head)->children[0], val, order);
     return;
    }

    if ((*head)->data < val){
      insert(&(*head)->children[1], val, order);
      return;
    }
    cout << "Duplicates not allowed" << endl;
  }

  //BST Print
  static void  print (node_t** head, std::ostream &out){
    std::stack<node_t*> nodes;
    node_t *curr = *head;
    
    while(curr) {
      out << "Node: " << curr->data << endl;
      if (curr->children[1]) {
        nodes.push(curr->children[1]);
      }
      if (curr->children[0]) {
        curr = curr->children[0];
      } else {
        if (!nodes.empty()) {
          curr = nodes.top(); 
          nodes.pop();
        } else {
          curr = nullptr;
        }
      } 
    }
  }
};

template<typename ValueNode>
struct TreeHelper<BNode<ValueNode>,ValueNode,B_NODE_FLAGXX>{
  typedef BNode<ValueNode>  node_t;
  typedef typename node_t::value_t value_t;

  static int find (node_t *&current, const value_t& val) {
    int index = 0;
    for (int i = 0; i < current->sizeOfContainer; i++) {
      if(current->data[i] < val) index++; 
    }
    return index;
  }
  
  static void  insert (node_t** head, const value_t& val, unsigned int order){
    auto current = head;
    auto next = head;
    auto current_index = 0;
    if ((*head) == nullptr) {
      *head = new node_t;
      (*head)->insertToContainer(val);
    }
    else {
      while((*next) != nullptr) {
        current = next;
        current_index = find((*current), val);
        next = &((*current)->children[current_index]);
      }
      
      if (!(*current)->isContainerFull()) {
        (*current)->insertToContainer(val);
      } else {
        (*current)->insertToContainer(val);
        auto pivot = (*current)->get_pivot();
        std::cout << pivot << std::endl;

        node_t *left_node = new node_t;
        node_t *right_node = new node_t;

        (*current)->get_left(left_node);
        (*current)->get_right(right_node);
        
      
        if ((*current)->parent==nullptr) {
          std::cout << "vacio " << std::endl;
          node_t *new_parent = new node_t;
          new_parent->insertToContainer(pivot);
          new_parent->children[0] = left_node;
          new_parent->children[1] = right_node;
          new_parent->childrenCount = 2;
          *head = &*new_parent;
          left_node->parent = head;
          right_node->parent = head;
        } else {
          auto parent = (*current)->parent;
          auto index = (*parent)->insertToContainer(pivot);
          (*parent)->children[index++] = &*left_node;
          (*parent)->children[index] = &*right_node;
          (*parent)->childrenCount++;
          
        }
        
      } 
    
  }
  }

  static void  print (node_t** head, std::ostream &out){
    auto current_node = *head;
    auto current_children = current_node->children;
    out << "Container: " << endl;
    out << "(";

    for (int i = 0; i < (*head)->sizeOfContainer; i++) {
        out << (*head)->data[i] << ", ";
    }

    out << ")" << endl;
    
    out << "children: " << (*head)->childrenCount << endl;

    for (int i =0; i < (*head)->childrenCount; i++) {
      if ((*head)->children[i] != nullptr) {
        print(&((*head)->children[i]), out);
      }
    }
    
  }
};

#endif