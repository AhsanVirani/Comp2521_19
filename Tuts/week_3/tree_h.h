// tree.h ... interface to set of ADT
// Written by Ahsan Muhammad, June 2020

#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdbool.h>

typedef struct Node *Tree;

// Create new empty tree
Tree
Tree_new();

// Check member in a given tree
bool
TreeContains(Tree, int);

// Insert in tree
Tree
TreeInsert(Tree, int);

// Set tree node data
void
set_Tree_node(Tree, int);

// Print in preorder format
void
tree_preorder(Tree);

// Print in inorder format
void
tree_inorder(Tree);

// Print in postorder format
void
tree_postorder(Tree);

// Join two trees
Tree
tree_join(Tree, Tree);

// Rotate the tree left
Tree
rotateLeft(Tree);

// Rotate the tree right
Tree
rotateRight(Tree);

// Insert at root in a tree
Tree
insert_root(Tree, int);

// Partition the tree by making the index new root
Tree
tree_partition(Tree, int);

// takes the left of root and returns the size of left subtree
int
size_leftSubtree(Tree);

// Count the numbers of nodes in the tree
int BSTreeNumNodes(Tree);

// Height of tree
int BSTreeHeight(Tree);

// Maximum of two values
int
max(int, int);

// Count the internal nodes of a tree
int 
countInternal(Tree);

// Counts depth of tree from given node
int 
nodeDepth(Tree, int);

// Counts width of tree
int 
BSTWidth(Tree t);

int 
BSTLeaves(Tree);

#endif
