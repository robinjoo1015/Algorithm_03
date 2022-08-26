#include <stdio.h>
#define BST_SIZE 8

/* find lowest common ancestor using index */
int findLowestCommonAncestor(int* tree, int size, int a, int b) {
	int indexA=0, indexB=0, i;
	/* find each index of number */
	for(i=1;i<size;i++) {
		if(tree[i]==a) { indexA = i; }
		if(tree[i]==b) { indexB = i; }
	}
	/* if not in tree return minus */
	if(indexA==0) { return -1; }
	if(indexB==0) { return -2; }
	/* divide larger index by 2 until same */
	while(indexA!=indexB) {
		if(indexA<indexB) { indexB/=2; }
		else { indexA/=2; }
	}
	return tree[indexA];
}

int main() {
	int bst[BST_SIZE] = {0, 6, 2, 8, 1, 3, 7, 9};
	int i=0, a, b, lca;
	/* print bst */
	printf("BST: ");
	for(i=1;i<BST_SIZE;i++) {
		if(bst[i]!=NULL) { printf("%d ", bst[i]); }
		else { printf("null "); }
	}
	printf("\n");

	while(1) {
		/* get 2 input */
		printf("Input 2 nodes: ");
		scanf("%d %d", &a, &b);
		/* if contains 0, exit */
		if(a==0 || b==0) { break; }
		/* find lowest common ancestor */
		lca = findLowestCommonAncestor(bst, BST_SIZE, a, b);
		if(lca<0) {
			/* if no element in tree, print element */
			printf("%d not in BST!\n", (lca==-1)?a:b);
			continue;
		}
		/* print lowest common ancestor */
		printf("Lowest Common Ancestor of %d %d is %d\n", a, b, lca);
	}
	return 0;
}
