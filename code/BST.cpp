/* Note: refer to the header file (BST.h) for documentation of each method. */

#include "BST.h"

BST::BST() {
  // Here is one way to implement the constructor. Keep or change it, up to you.
  root = new bst_node*;
  *root = NULL;
}

BST::~BST() {
  delete(*root);

}

// Helper function to delete nodes with null data
void BST::delete_null_nodes(bst_node* subtree) {
    if (subtree != nullptr) {
        // Recursively delete left subtree
        delete_null_nodes(subtree->left);
        // Recursively delete right subtree
        delete_null_nodes(subtree->right);
        // Delete the current node if data is null
        if (subtree == NULL) {
            delete subtree;
        }
    }
}

 

bst_node* BST::init_node(int data) { 
  bst_node* new_node = new bst_node; //allocate new memory for new node
  new_node->data = data; //copy the data, set left and right children to null
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
  }

void BST::insert(bst_node* new_node) {
  // Check base case: empty tree
  if (*root == NULL){ 
    *root = new_node;
  }
  else {
    currentNode = *root; // start at the root
    while (currentNode != NULL){ //base case
      if (new_node->data < currentNode->data){ //check to see if it should a left child
        if (currentNode->left == NULL){ //if true, and no left child, place in left child spot
          currentNode->left = new_node;
          currentNode = NULL; //stops the loop
        }
        else {
          currentNode = currentNode->left; //else, change current node pointer to the left child
        }
      }
      //otherwise, must be a right child
      else { 
        if (currentNode->right == NULL){ 
          currentNode->right = new_node;
          currentNode = NULL;
        }
        else {
          currentNode = currentNode->right;
        }
      }
    }
  }
}

void BST::insert_data(int data) {
  bst_node* node = init_node(data); //initalize a new node
  insert(node); //use the insert function
}

void BST::remove(int data) {
  parent_node = nullptr;
  currentNode = *root;
  //initalize base case, start search 
  while (currentNode != nullptr) {
    if (currentNode->data == data){ //data found
        if (currentNode->left == nullptr && currentNode->right == nullptr){
          if (parent_node == nullptr){ //the node is the root
            *root = nullptr;
          }
          else if (parent_node->left == currentNode){
            parent_node->left = nullptr;
          }
          else{
            parent_node->right = nullptr;
          }
        }
        else if (currentNode->right == nullptr){ //remove node with only left child
          if (parent_node == nullptr){
            *root = currentNode->left;
          }
          else if (parent_node->left == currentNode){
            parent_node->left = currentNode->left;
          }
          else{
            parent_node->right = currentNode->right;
          }
        }
        else if (currentNode->left == nullptr){
          if(parent_node == nullptr){
            *root= currentNode->right;
          }
          else if (parent_node->left == currentNode){ //Remove node with right child
            parent_node->left = currentNode->right;
          }
          else{
            parent_node->right = currentNode->right;
          }
        }
        else{
          suc_node = currentNode->right;
          while (suc_node->left != nullptr){
            suc_node = suc_node->left;
          }
          suc_copy = suc_node;
          remove(suc_node->data);
          currentNode = suc_copy;
        }
        return; //node found and removed
    }
    else if (currentNode->data < data){
      parent_node = currentNode;
      currentNode = currentNode->right;
    }
    else {
      parent_node = currentNode;
      currentNode = currentNode->left;
    }
  }
  return; //node not found
}
        


bool BST::contains(bst_node* subt, int data) {
  // Base case
    if (subt == nullptr) {
        return false;
    }
    // If current node contains the data, return true
    if (subt->data == data) {
        return true;
    }
    // search the left 
    if (data < subt->data) {
        return contains(subt->left, data);
    }
    // search the right
    else {
        return contains(subt->right, data);
    }
  return false;
}

bst_node* BST::get_node(bst_node* subt, int data){
  if (subt == nullptr) {
    return NULL; 
  }
  
  if (subt->data == data) {
    return subt; // Base case: node found
  }
    
  if (subt->data > data) {
    // Recursively search in the left
     return get_node(subt->left, data);
  }
  else {
      // Recursively search in the right 
      return get_node(subt->right, data);
  }
  return NULL;
}

int BST::size(bst_node* subt) {
    // Base case: if the subtree pointer is null, return 0
    if (subt == nullptr) {
        return 0;
    }
    
    // Recursive step: return the sum of sizes of left and right subtrees
    return 1 + size(subt->left) + size(subt->right);
  return 0;
}

void BST::to_vector(bst_node* subt, vector<int>& vec) {
    // Base case
    if (subt == nullptr) {
        return;
    }

    // Recursively traverse the left subtree
    to_vector(subt->left, vec);

    // Add current node's data to the vector
    vec.push_back(subt->data);

    // Recursively traverse the right subtree
    to_vector(subt->right, vec);
}



bst_node* BST::get_root() {
  // This function is implemented for you
  if (*root == NULL)
    return NULL;
  return *root;
}

void BST::set_root(bst_node** new_root) {
  // This function is implemented for you
  root = new_root;
}
