#include <iostream>
#include <vector> 
#include <math.h>  
#include <algorithm>  
template <typename T>
class SS_Traits{
public:
  typedef T  value_t;
  typedef std::vector<value_t> container_t;
  typedef typename container_t::iterator iterator_t;
  
  class simple_search{
  public:
    bool operator() (container_t a, const value_t v, int &aux){
      aux = 0;

      for (auto x: a) {
        if (x==v) return true;
        if (x < v) aux++;
        if (x > v) return false;
      }
      return false;
    }
  };

  class post_order_print{
  public:
    void operator() (void){
      std::cout << "post order" << std::endl;
    }
  };

  typedef simple_search functor_t;
  typedef post_order_print print_t;
};

template <typename T>
class BS_Traits{
public:
  typedef T  value_t;
  typedef std::vector<value_t> container_t;
  typedef typename container_t::iterator iterator_t;
  
  class binary_search{
  public:
    bool operator() (container_t a, const value_t v){
      return std::binary_search(a.begin(), a.end(), v)
    }
  };

  class pre_order_print{
  public:
    void operator() (void){
      std::cout << "pre order" << std::endl;
    }
  };

  typedef binary_search functor_t;
  typedef pre_order_print print_t;
};

template <typename T, int S> 
class BNode {
public:
  typedef typename T::value_t value_t;
  typedef typename T::container_t container_t;
  typedef std::vector<BNode*> ptr_children;
  bool isLeaf;


  container_t keys;
  ptr_children ptrs;
  std::size_t  order;
  BNode* parent;

  BNode(void):order(S){
    keys=container_t(order,0);
    ptrs=ptr_children(order,NULL);
    isLeaf = true;
  }

  ~BNode(void){}
};

template <typename T, int S>
class BTree {
public: 
  typedef typename T::value_t value_t;
  typedef typename T::functor_t functor_t;
  typedef typename T::print_t print_t;
  typedef BNode<T,S> Node;
  
  Node* root;
  print_t print;
  functor_t search;

//aux for searching
  Node* ptr_aux;
  int pos_aux;


  BTree(void):root(NULL){
  }

  ~BTree(void){}

  void insert(const value_t& val = 0){
      pos_aux = 0;
      Node* current = root;
      Node* next = root;

      if (current == nullptr) {
        root = new Node(S);
        root->isLeaf=true;
        root->keys.push_back(val);
        current->parent = nullptr;
        return;
      }

      while(next != nullptr) {
        current = next;
        if (search(current->keys, val, pos_aux)) return;
        next = current->ptrs[pos_aux]
      } 
      if (!current->full) {
        current->keys.push_back(val);
        current->keys.sort();
      } else {
        auto parent = current->parent;
        if (parent==nullptr) {
          parent = new Node(S);
          parent->isLeaf = false;
          parent->parent = nullptr;
          current->parent = parent;
        }
        search(current->keys, val, pos_aux)
        current->keys.push_back(val);
        current->keys.sort();
        Node* new_left = new Node;
        Node* new_right = new Node;
        int curr_pos = 0;
        int middle = std::ceil(S/2)
        while (curr_pos < middle) {
          new_left->keys.push_back(current[curr_pos++]);
        } 
        value_t goes_up = current[curr_pos++];
        while (curr_pos < S) {
          new_right->keys.push_back(current[curr_pos++]);
        }
        search(parent->keys, goes_up, pos_aux);
        parent->keys.push_back(goes_up);
        parent->keys.sort()
        std::vector<Node*> new_ptrs;
        int curr_pos = 0;
        while (curr_pos < pos_aux) {
          new_ptrs.push_back(parent->ptrs[curr_pos++]);
        }
        curr_pos++;
        new_ptrs.push_back(new_left);
        new_ptrs.push_back(new_right);
        while(curr_pos < S) {
          new_ptrs.push_back(parent->ptrs[curr_pos++]);
        }
        parent->ptrs = new_ptrs;
      } 
      
  }

  bool find(const value_t& val = 0) const{
    pos_aux = 0;
    Node* current = root;
    while (current !=  nullptr) {
      if (search(current->keys, val, pos_aux)) return true;
      current = current->ptrs[pos_aux]
    }
    return false;
  }

  template <typename _T, int _S>
  friend std::ostream& operator<<(std::ostream& out, BTree<_T,_S> tree){
    tree.print();// (out)
    // IN PRE POST LEVEL ORDER
    return out;
  }

};

int main() {
  typedef BS_Traits<int> btrait_t;
  BTree<btrait_t,4> tree;
  tree.find(10);
  std::cout<<tree<< std::endl;


  typedef SS_Traits<float> strait_t;
  BTree<strait_t,10> stree; 
  std::cout<<stree<< std::endl;
}