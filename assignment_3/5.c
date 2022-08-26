#include <stdio.h>
#include <stdlib.h>
/* macro definition */
typedef char bool;
#define TRUE (1)
#define FALSE (0)
#define RED 'r'
#define BLACK 'b'

/* type definition for node */
typedef struct node *nodePtr;
typedef struct node {
	int data;
	char color;
	nodePtr left;
	nodePtr right;
	nodePtr parent;
} node;

/* make new node */
nodePtr newNode(int data) {
	nodePtr newnode = (nodePtr)malloc(sizeof(node));
	newnode->data = data;
	newnode->color = RED; // default color red
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = NULL;
	return newnode;
}

/* in-order traversal */
void inOrderTraverse(nodePtr tree, bool color) {
	if(tree==NULL) {
		return;
	}
	inOrderTraverse(tree->left, color);
	if(color) { printf("%c ", tree->color); }
	else { printf("%d ", tree->data); }
	inOrderTraverse(tree->right, color);
	return;
}
/* pre-order traversal */
void preOrderTraverse(nodePtr tree, bool color) {
	if(tree==NULL) {
		return;
	}
	if(color) { printf("%c ", tree->color); }
	else { printf("%d ", tree->data); }
	preOrderTraverse(tree->left, color);
	preOrderTraverse(tree->right, color);
	return;
}
/* post-order traversal */
void postOrderTraverse(nodePtr tree, bool color) {
	if(tree==NULL) {
		return;
	}
	postOrderTraverse(tree->left, color);
	postOrderTraverse(tree->right, color);
	if(color) { printf("%c ", tree->color); }
	else { printf("%d ", tree->data); }
	return;
}

/* normal binary search tree insertion */
nodePtr treeInsert(nodePtr tree, nodePtr newnode) {
	nodePtr initialTree = tree;
	if(tree==NULL) {
		return newnode;
	}
	while(1) {
		if(tree->data > newnode->data) {
			if(tree->left == NULL) { 
				tree->left = newnode;
				newnode->parent = tree;
				break;
			}
			tree = tree->left; 
		}
		else {
			if(tree->right == NULL) { 
				tree->right = newnode;
				newnode->parent = tree;
				break;
			}
			tree = tree->right;
		}
	}
	return initialTree;
}

/* left rotate */
void leftRotate(nodePtr rnode) {
	nodePtr rchild = rnode->right;
	char rcolor = rnode->color;
	/* move left subtree of right child */
	rnode->right = rchild->left;
	if(rnode->right!=NULL) {
		rchild->left->parent = rnode;
	}
	/* make right child as parent */
	rchild->left = rnode;
	rchild->parent = rnode->parent;
	rnode->parent = rchild;
	if(rchild->parent!=NULL) {
		if(rchild->parent->left == rnode) {
			rchild->parent->left = rchild;
		}
		else {
			rchild->parent->right = rchild;
		}
	}
}

/* right rotate */
void rightRotate(nodePtr rnode) {
	nodePtr lchild = rnode->left;
	char rcolor = rnode->color;
	/* move right subtree of left child */
	rnode->left = lchild->right;
	if(rnode->left != NULL) {
		lchild->right->parent = rnode;
	}
	/* make left child as parent */
	lchild->right = rnode;
	lchild->parent = rnode->parent;
	rnode->parent = lchild;
	if(lchild->parent!=NULL) {
		if(lchild->parent->left == rnode) {
			lchild->parent->left = lchild;
		}
		else {
			lchild->parent->right = lchild;
		}
	}
}

/* red-black tree insertion */
nodePtr rbInsert(nodePtr rbtree, int data) {
	nodePtr x = newNode(data);
	nodePtr y = NULL;
	/* normal bst insert */
	rbtree = treeInsert(rbtree, x);
	/* handle property 3 violation */
	while(rbtree != x) {
		if(x->parent->color == RED) {
			if(x->parent->parent != NULL) {
				if(x->parent == x->parent->parent->left) {
					y = x->parent->parent->right;
					if(y!=NULL) {
						if(y->color == RED) {
							/* Case 1 */
							x->parent->color = BLACK;
							y->color = BLACK;
							x->parent->parent->color = RED;
							x = x->parent->parent;
							continue;
						}
					}
					else {
						if(x == x->parent->right) {
							/* Case 2 */
							x = x->parent;
							leftRotate(x);
						}
						/* recolor */
						x->parent->color = BLACK;
						x->parent->parent->color = RED;
						/* Case 3 */
						rightRotate(x->parent->parent);
						if(x->parent->parent == NULL) {
							rbtree = x->parent;
						}
						break;
					}
				}
				else {
					/* Opposite Case */
					y = x->parent->parent->left;
					if(y!=NULL) {
						if(y->color == RED) {
							/* Case 1 */
							x->parent->color = BLACK;
							y->color = BLACK;
							x->parent->parent->color = RED;
							x = x->parent->parent;
							continue;
						}
					}
					else {
						if(x == x->parent->left) {
							/* Case 2 */
							x = x->parent;
							rightRotate(x);
						}
						/* recolor */
						x->parent->color = BLACK;
						x->parent->parent->color = RED;
						/* Case 3 */
						leftRotate(x->parent->parent);
						if(x->parent->parent == NULL) {
							rbtree = x->parent;
						}
						break;	
					}
					
				}
			}
		} else {
			break;
		}
	}
	rbtree->color = BLACK;
	return rbtree;
}

int main() {
	nodePtr rbTree = NULL;
	int insertList[6] = {41, 38, 31, 12, 19, 8};
	int i=0;

	for(i=0;i<6;i++) {
		rbTree = rbInsert(rbTree, insertList[i]);
	}
	printf("in-order traversal\n");
	inOrderTraverse(rbTree, FALSE); printf("\n");
	inOrderTraverse(rbTree, TRUE); printf("\n");
	printf("pre-order traversal\n");
	preOrderTraverse(rbTree, FALSE); printf("\n");
	preOrderTraverse(rbTree, TRUE); printf("\n");
	printf("post-order traversal\n");
	postOrderTraverse(rbTree, FALSE); printf("\n");
	postOrderTraverse(rbTree, TRUE); printf("\n");
	return 0;
}
