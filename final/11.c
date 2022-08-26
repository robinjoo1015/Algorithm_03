#include <stdio.h>
#include <stdlib.h>
#define X_LEN 7
#define Y_LEN 6

/* type with 2 integer for coordinate */
typedef struct coord {
	int x;
	int y;
} coord;

/* print LCS recursively with coord array b */
void Print_LCS(coord** b, char *X, int i, int j) {
	if(i==0 || j==0) {
		return;
	}
	if(b[i][j].x==i-1 && b[i][j].y==j-1) {
		Print_LCS(b, X, i-1, j-1);
		printf("%c", X[i]);
	}
	else if(b[i][j].x==i-1 && b[i][j].y==j) {
		Print_LCS(b, X, i-1, j);
	}
	else {
		Print_LCS(b, X, i, j-1);
	}
}

/* calculate length of lcs */
int LCS_Length(char *X, char *Y, int x_len, int y_len) {
	int i, j;
	coord **b;
	int **c;
	
	b = (coord**)malloc((x_len+1)*sizeof(coord*));
	c = (int**)malloc((x_len+1)*sizeof(int*));
	for(i=0;i<=x_len;i++) {
		b[i] = (coord*)malloc((y_len+1)*sizeof(coord));
		c[i] = (int*)malloc((y_len+1)*sizeof(int));
	}
	
	for(i=1;i<=x_len;i++) { c[i][0] = 0; }
	for(j=0;j<=y_len;j++) { c[0][j] = 0; }
	
	for(i=1;i<=x_len;i++) {
		for(j=1;j<=y_len;j++) {
			if(X[i]==Y[j]) {
				c[i][j] = c[i-1][j-1] + 1;
				b[i][j].x = i-1;
				b[i][j].y = j-1;
			}
			else if(c[i-1][j]>=c[i][j-1]) {
				c[i][j] = c[i-1][j];
				b[i][j].x = i-1;
				b[i][j].y = j;
			}
			else {
				c[i][j] = c[i][j-1];
				b[i][j].x = i;
				b[i][j].y = j-1;
			}
		}
	}
	
	/* print lcs */
	printf("LCS: ");
	Print_LCS(b, X, x_len, y_len);
	printf("\n");
	return c[x_len][y_len];
}

int main() {
	char X[X_LEN+1] = {' ', 'A', 'B', 'C', 'B', 'D', 'A', 'B'};
	char Y[Y_LEN+1] = {' ', 'B', 'D', 'C', 'A', 'B', 'A'};
	
	int lcs = LCS_Length(X, Y, X_LEN, Y_LEN);
	printf("LCS length: %d\n", lcs);
}
