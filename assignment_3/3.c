#include <stdio.h>
#include <stdlib.h>

typedef char bool;
#define TRUE (1)
#define FALSE (0)
#define BST_SIZE 8

/* in-order traversal of given bst, save result at result array */
void inOrderTraverse(int* tree, int index, int size, int* result) {
	if(size>2) {
		/* use index and size */
		inOrderTraverse(tree, index*2, size/2, result);
		inOrderTraverse(tree, index*2+1, size/2, result+(size/2));
	}
	result[size/2] = tree[index];
	return;
}

/* check whether array is ascending order */
bool isAscendingOrder(int* array, int size) {
	int i=0;
	for(i=0;i<size-1;i++) {
		if(array[i]==NULL||array[i+1]==NULL) { continue; }
		else {
			if(array[i]>array[i+1]) {
				return FALSE;
			}
		}
	}
	return TRUE;
}

/* check whether bst is valid */
bool isValidBST(int* tree, int size) {
	int* traversed;
	bool ascending;
	int i=0;
	
	/* additional array to save in-order traverse */
	traversed = (int*)malloc(size*sizeof(int));
	for(i=0;i<size;i++) {
		traversed[i] = NULL;
	}
	/* in-order traversal */
	inOrderTraverse(tree, 1, size, traversed);
	/* print in-order traversal */
	printf("In-order Traverse: ");
	for(i=1;i<size;i++) {
		if(traversed[i]!=NULL) { printf("%d ", traversed[i]); }
		else { printf("null "); }
	}
	printf("\n");
	
	/* check in-order traversal is ascending order */
	ascending = isAscendingOrder(traversed, size);
	free(traversed);
	return ascending;
}

int main() {
	/* given bst from index 1 */
	int bst[BST_SIZE] = {0, 8, 3, 9, NULL, NULL, 4, 7};
	
	/* check if bst is valid */
	if(isValidBST(bst, BST_SIZE)) {
		printf("BST is Valid!\n");
	} else {
		printf("BST is not Valid!!\n");
	}
	
	return 0;
}
