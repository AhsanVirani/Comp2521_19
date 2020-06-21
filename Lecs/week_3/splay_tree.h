


#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H


#include "tree.h"



// insertion in a splay tree
Tree
insertSplay(Tree, int);

// search in a splay tree. Makes the searched item new root
Tree
search_splay(Tree, int);

Tree
splay(Tree, int);


#endif
