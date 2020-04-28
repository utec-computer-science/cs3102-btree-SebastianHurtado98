#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>  
#include <math.h>  
#define BST_NODE_FLAGXX 1
#define B_NODE_FLAGXX 2

class BSTNodeTraits{
  public:
    typedef int value_t;
};

class BSTNode : public BSTNodeTraits{
  public: 
  typedef typename  BSTNodeTraits::value_t value_t;

  value_t data;
  BSTNode ** children;

  BSTNode(value_t data){
    this->data = data;
    children = new BSTNode*[2];
    children[0] = nullptr;
    children[1] = nullptr;
  }

  ~BSTNode(void){}

};

class BSTNodeTraitsF: public BSTNodeTraits{
  public:
    typedef int value_t;

    class functor{
      void operator()(){
        return;
      }
    };

    typedef functor functor_t;
};

class BSTNodeF : public BSTNodeTraitsF{
  public: 
  typedef typename  BSTNodeTraitsF::value_t value_t;

  value_t data;
  BSTNode ** children;

  BSTNodeF(value_t data){
    children = new BSTNode*[2];
  }

  ~BSTNodeF(void){}

};

class BNodeTraits{
  public:
    typedef int value_t;
    typedef std::vector<value_t> container_t;
};

class BNode : public BNodeTraits{
  public: 
  typedef typename  BNodeTraits::value_t value_t;
  typedef typename  BNodeTraits::container_t container_t;

  container_t data;
  BNode** children;
  bool full, isLeaf;
  BNode** parent;
  int max_size, current_size;

  BNode(){
    children = new BNode*[4];
    children[0] = nullptr;
    children[1] = nullptr;
    children[2] = nullptr;
    children[3] = nullptr;
    parent = nullptr;
    max_size = 3;
    current_size = 0;
    isLeaf = false;
    full = false;
  }
  int insert(const value_t &val) {
    int index = 0;
    this->data.push_back(val);
    sort(this->data.begin(), this->data.end());
    this->current_size++;
    if (this->current_size >= this->max_size) {
        this->full = true;
        std::cout << "FULL";
    } 
    for (auto x : this->data) {
      if (val>x) {
        index++;
      }
    }
    return index;
  }
  value_t get_pivot() {
    return this->data[1];
  }
  void get_left(BNode* &newNode) {
    newNode->insert(this->data[0]);
    if (this->children[0] != nullptr) newNode->children[0] = this->children[0];
    if (this->children[1] != nullptr) newNode->children[1] = this->children[1];

  }
  void get_right(BNode* &newNode) {
    newNode->insert(this->data[2]);
    newNode->insert(this->data[3]); 
    if (this->children[2] != nullptr) newNode->children[0] = this->children[2];
    if (this->children[3] != nullptr) newNode->children[1] = this->children[3];
  }
  ~BNode(void){}

};

template <typename Node>
struct NodeTraits{
  static const int  flag_type = 0;
};

template <>
struct NodeTraits< BSTNode >{
  static const int  flag_type = BST_NODE_FLAGXX;
};


template <> 
struct NodeTraits< BNode >{
  static const int  flag_type = B_NODE_FLAGXX;
};

template<typename  Node, int Flag>
struct TreeHelper{
  typedef Node  node_t;
  typedef typename node_t::value_t value_t;
  
  static void  insert (node_t** head, const value_t& val){
    std::cout << "el tipo de dato no es compatible" << std::endl;
  }

  static void  print (node_t** head){
  }
};

template<>
struct TreeHelper<BSTNode,BST_NODE_FLAGXX>{
  typedef BSTNode  node_t;
  typedef typename node_t::value_t value_t;
  
  static void  insert (node_t** head, const value_t& val){
    auto current = head;
    auto next = head;
    
    if ((*head) == nullptr) {
      *head = new node_t(val);
    }
    else {

      while((*next) != nullptr) {
        current = next;
        ((*current)->data > val) ? (next = &((*current)->children[0])) : (next = &((*current)->children[1]));
      }

      ((*current)->data > val) ? ( ((*current)->children[0]) = &(**next) ) : ( ((*current)->children[1]) = &(**next) );
      
      *next = new node_t(val);

    }  
      std::cout << (*next)->data << std::endl;
      std::cout << "Insertando nodo BST hoja" << std::endl;
  }

  static void  print (node_t** head){
    std::stack <node_t*> s; 
    auto current = *head;
    while(current != nullptr) {
      std::cout << current->data << std::endl;
      
      if (current->children[1] != nullptr) s.push(current->children[1]);
      if (current->children[0] != nullptr) current = current->children[0];
      else {
        if (!s.empty())
          {current = s.top(); s.pop();}
        else {
          current = nullptr;
        }
        } 
        
    
    }
  }
};

template<>
struct TreeHelper<BNode,B_NODE_FLAGXX>{
  typedef BNode  node_t;
  typedef typename node_t::value_t value_t;
  typedef typename node_t::container_t container_t;
  
  static int find (const container_t& container, const value_t& val) {
    int index = 0;
    for (auto x: container) {
      if (x < val) index++; 
    }
    return index;
  }
  static void  insert (node_t** head, const value_t& val){
    auto current = head;
    auto next = head;
    auto current_index = 0;
    if ((*head) == nullptr) {
      *head = new node_t;
      (*head)->insert(val);
    }
    else {
      while((*next) != nullptr) {
        current = next;
        current_index = find((*current)->data, val);
        next = &((*current)->children[current_index]);
      }
      
      if (!(*current)->full) {
        (*current)->insert(val);
      } else {
        (*current)->insert(val);
        auto pivot = (*current)->get_pivot();
        std::cout << pivot << std::endl;

        node_t *left_node = new node_t;
        node_t *right_node = new node_t;

        (*current)->get_left(left_node);
        (*current)->get_right(right_node);
        
      
        if ((*current)->parent==nullptr) {
          std::cout << "vacio " << std::endl;
          node_t *new_parent = new node_t;
          new_parent->insert(pivot);
          new_parent->children[0] = left_node;
          new_parent->children[1] = right_node;
          new_parent->isLeaf = false;
          *head = &*new_parent;
          left_node->parent = head;
          right_node->parent = head;
        } else {
          auto parent = (*current)->parent;
          auto index = (*parent)->insert(pivot);
          (*parent)->children[index++] = &*left_node;
          (*parent)->children[index] = &*right_node;
          
        }
        
      } 
    
  }
  }

  static void  print (node_t** head){
    auto current_node = *head;
    auto current_container = current_node->data;
    auto current_children = current_node->children;
    std::cout << "Container: " << std::endl;
    std::cout << "(";
    for (auto x: current_container) {
      std::cout << x << ", ";
    }
    std::cout << ")" << std::endl;
    for (int i =0; i < 4; i++) {
      if (current_children[i] != nullptr) {
        print(&((*head)->children[i]));
      }
    }
  }
};

template <typename Node>
class Tree{
  public:
  typedef Node node_t;
  typedef typename node_t::value_t value_t;

  node_t* root;

  Tree(void):root(nullptr){
    std::cout << NodeTraits<node_t>::flag_type << std::endl;
  }

  void insert(const value_t& val){
    add<NodeTraits<node_t>::flag_type>(&root,val);
  }
  
  void print() {
    show<NodeTraits<node_t>::flag_type>(&root);
  }

  template <int Flag> 
  void add(node_t**, const value_t&);

  template <int Flag>
  void show(node_t**);

  ~Tree(void){}
};

template<typename Node> template <int Flag>
void Tree<Node>::add(
  typename Tree<Node>::node_t ** root, 
  const typename Tree<Node>::value_t & val){
  TreeHelper<Tree<Node>::node_t,Flag>::insert(root,val);
}

template<typename Node> template <int Flag>
void Tree<Node>::show(typename Tree<Node>::node_t **root) {
  TreeHelper<Tree<Node>::node_t,Flag>::print(root);
}

int main() {
  typedef BSTNode bst_int_node;
  typedef BNode b_int_node;
  typedef Tree<bst_int_node> bst_tree;
  typedef Tree<b_int_node> b_tree;

  bst_tree bsttree;
  b_tree btree;

  bsttree.insert(20);
  bsttree.insert(30);
  bsttree.insert(40);
  bsttree.insert(10);
  bsttree.insert(15);
  bsttree.print();
  btree.insert(20);
  btree.insert(30);
  btree.insert(40);
  btree.insert(10);
  btree.insert(90);
  btree.insert(5);
  btree.insert(15);
  btree.insert(150);
  btree.print();
}