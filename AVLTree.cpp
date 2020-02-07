//Hunter Vaccaro
//hpv8hf
//10/17/2019
//AVLTree.cpp
#include "AVLTree.h"
#include <string>
#include "AVLNode.h"
#include <iostream>
using namespace std;

AVLTree::AVLTree() { root = NULL; }

AVLTree::~AVLTree() {
  delete root;
  root = NULL;
}

// insert finds a position for x in the tree and places it there, rebalancing
// as necessary.
void AVLTree::insert(const string& x) {
  root = insert(x,root);
}

AVLNode* AVLTree::insert(const string& x, AVLNode*& root){ //NOT DONE NOT DONE
  if(find(x,root)){
  }
  else {
    if(root == NULL){
      AVLNode* temp = new AVLNode();
      temp -> value = x;
      temp -> height = 0;
      root = temp;
      return root;
    }
    else if(root->value < x) {
      if(root->right == NULL){
	AVLNode* temp = new AVLNode();
	temp -> value = x;
	temp -> height = 0;
	root -> right = temp;
	root -> height = 1 + max(height(root->left), height(root->right));
	balance(root);
	return root;
      }
      insert(x, root->right);
      root -> height = 1 + max(height(root->left) , height(root -> right));
      balance(root);
    }
    else {
      if(root -> left == NULL){
	AVLNode* temp = new AVLNode();
	temp -> value = x;
	temp -> height = 0;
	root ->left = temp;
	root -> height = 1 + max(height(root->left), height(root->right));
	balance(root);
	return root;
      }
      insert(x, root->left);
      root -> height = 1 + max(height(root->left) , height(root -> right));
      balance(root);
    }
  }
  root -> height = 1 + max(height(root->left) , height(root -> right));
  balance(root);
  return root;
}

// remove finds x's position in the tree and removes it, rebalancing as
// necessary.
void AVLTree::remove(const string& x) { root = remove(root, x); }

// pathTo finds x in the tree and returns a string representing the path it
// took to get there.
string AVLTree::pathTo(const string& x) const {
  // YOUR IMPLEMENTATION GOES HERE
  return pathTo(x, root);
}

string AVLTree::pathTo(const string& x, AVLNode* root) const {
 if(root == NULL){
    return "";
  }
  else if(!find(x,root)){
    return "";
  }
  else if(root->value > x){
    return ""+root->value+" "+pathTo(x,root->left);
  }
  else if(root->value < x){
    return ""+root->value+" "+pathTo(x,root->right);
  }
  else {
    return ""+root->value;
  } 
}

// find determines whether or not x exists in the tree.
bool AVLTree::find(const string& x) const {
  // YOUR IMPLEMENTATION GOES HERE
  return find(x,root);
}

bool AVLTree::find(const string& x, AVLNode* root) const {
  if(root == NULL){
    return false;
  }
  else if(root->value == x){
    return true;
  }
  else {
    return (find(x,root->left) || find(x,root->right));
  }
}

// numNodes returns the total number of nodes in the tree.
int AVLTree::numNodes() const {
  return numNodes(root);
}

int AVLTree::numNodes(AVLNode* root) const {
  if(root == NULL){
    return 0;
  }
  else {
    return 1 + numNodes(root->left) + numNodes(root->right);
  }
}

// balance makes sure that the subtree with root n maintains the AVL tree
// property, namely that the balance factor of n is either -1, 0, or 1.
void AVLTree::balance(AVLNode*& n) {
  // YOUR IMPLEMENTATION GOES HERE
  int check = height(n->right) - height(n->left);
  if(check >= 2){
    int checker = height(n->right->right) - height(n->right->left);
    if(checker<0){
      n->right = rotateRight(n->right);
    }
    n = rotateLeft(n);
  }
  if(check <= -2){
    int checkerz = height(n->left->right) - height(n->left->left);
    if(checkerz>0){
      n->left = rotateLeft(n->left);
    }
    n = rotateRight(n);
  }
}

// rotateLeft performs a single rotation on node n with its right child.
AVLNode* AVLTree::rotateLeft(AVLNode*& n) {
  // YOUR IMPLEMENTATION GOES HERE
  AVLNode* temp = n->right;
  n -> right = temp -> left;
  temp -> left = n;
  n -> height = 1 + max(height(n -> right), height(n -> left));
  temp -> height = 1 + max(height(temp -> left), height(temp -> right));
  return temp;
}

// rotateRight performs a single rotation on node n with its left child.
AVLNode* AVLTree::rotateRight(AVLNode*& n) {
  // YOUR IMPLEMENTATION
  AVLNode* temp = n -> left;
  n -> left = temp -> right;
  temp -> right = n;
  n -> height = 1 + max(height(n -> left),  height(n -> right));
  temp -> height = 1 + max(height(temp->left), height(temp->right));
  return temp;
}

// private helper for remove to allow recursion over different nodes. returns
// an AVLNode* that is assigned to the original node.
AVLNode* AVLTree::remove(AVLNode*& n, const string& x) {
  if (n == NULL) {
    return NULL;
  }
  // first look for x
  if (x == n->value) {
    // found
    // no children
    if (n->left == NULL && n->right == NULL) {
      delete n;
      n = NULL;
      return NULL;
    }
    // single child
    if (n->left == NULL) {
      AVLNode* temp = n->right;
      n->right = NULL;
      delete n;
      n = NULL;
      return temp;
    }
    if (n->right == NULL) {
      AVLNode* temp = n->left;
      n->left = NULL;
      delete n;
      n = NULL;
      return temp;
    }
    // two children -- tree may become unbalanced after deleting n
    string sr = min(n->right);
    n->value = sr;
    n->right = remove(n->right, sr);
  } else if (x < n->value) {
    n->left = remove(n->left, x);
  } else {
    n->right = remove(n->right, x);
  }
  n->height = 1 + max(height(n->left), height(n->right));
  balance(n);
  return n;
}

// min finds the string with the smallest value in a subtree.
string AVLTree::min(AVLNode* node) const {
  // go to bottom-left node
  if (node->left == NULL) {
    return node->value;
  }
  return min(node->left);
}

// height returns the value of the height field in a node. If the node is
// null, it returns -1.
int AVLTree::height(AVLNode* node) const {
  if (node == NULL) {
    return -1;
  }
  return node->height;
}

// max returns the greater of two integers.
int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

// Helper function to print branches of the binary tree
void showTrunks(Trunk* p) {
  if (p == nullptr) return;
  showTrunks(p->prev);
  cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
void AVLTree::printTree(AVLNode* root, Trunk* prev, bool isLeft) {
  if (root == NULL) return;

  string prev_str = "    ";
  Trunk* trunk = new Trunk(prev, prev_str);

  printTree(root->left, trunk, true);

  if (!prev)
    trunk->str = "---";
  else if (isLeft) {
    trunk->str = ".---";
    prev_str = "   |";
  } else {
    trunk->str = "`---";
    prev->str = prev_str;
  }

  showTrunks(trunk);
  cout << root->value << endl;

  if (prev) prev->str = prev_str;
  trunk->str = "   |";

  printTree(root->right, trunk, false);
}

void AVLTree::printTree() { printTree(root, NULL, false); }
