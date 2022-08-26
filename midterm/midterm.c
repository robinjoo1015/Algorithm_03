#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* define swapping macro function */
#define SWAP(x,y) {int t=x; x=y; y=t;}
#define FALSE 0
#define TRUE 1

/* dynamic array memory allocation function */
int* mallocArray(int n, int isWorst)
{
    int* array = (int*)malloc(n*sizeof(int));
    int i = 0;
    for(i=0; i<n; i++) {
        /* if TRUE for isWorst parameter */
    	if(isWorst) {
            /* assign element in decresing order*/
    		array[i] = n-i;
		}
        /* if FALSE assign 0 to every element */
        else {
        	array[i] = 0;
		}
    }
    return array;
}

/* function checking whether array is sorted */
int checkSorted(int *array, int n)
{
	int i=0;
	for(i=0;i<n;i++) {
		if(array[i] != i+1) {
            /* if not return FALSE*/
			return FALSE;
		}
	}
    /* if array is sorted return TRUE */
	return TRUE;
}

/* bubble sort function */
int* bubbleSort(int* arr, int n)
{
    int i=0, j=0;
    for(i=0;i<n-1;i++) {
        for(j=0;j<n-i-1;j++) {
            /* compare successive pair of elements */
            if(arr[j]>arr[j+1]) {
                /* swap if not in order */
                SWAP(arr[j],arr[j+1]);
            }
        }
    }
    return arr;
}

/* insertion sort function */
int* insertionSort(int* arr, int n)
{
    int i=0, key=0, j=0;
    /* from second element */
    for(i=1;i<n;i++) {
        key = arr[i];
        j = i-1;
        /* while left elements are bigger than key element */
        while(j>=0 && arr[j]>key) {
            /* shift each element to right */
            arr[j+1] = arr[j];
            j = j-1;
        }
        /* insert key element */
        arr[j+1] = key;
    }
    return arr;
}

/* merge sort function */
int* mergeSort(int* arr, int n)
{
    int i=0, m=0;
    int i1=0, i2=0;
    int *left, *right;
    /* if size of array is bigger than 1*/
    if(n>1) {
        m = n/2;
        /* allocate memory for subarrays */
        left = mallocArray(m, FALSE);
        right = mallocArray(n-m, FALSE);
        /* fill left and right array */
        for(i=0;i<m;i++) {
            left[i]=arr[i];
        }
        for(i=m;i<n;i++) {
            right[i-m]=arr[i];
        }
        /* recursively sort subarrays */
        left = mergeSort(left, m);
        right = mergeSort(right, n-m);

        /* merge sorted subarrays */
        for(;i1+i2<n;) {
            /* if there are no more elements to compare in left */
            if(i1==m) {
                /* assign first element of right */
                arr[i1+i2]=right[i2];
                i2++;
            }
            /* if there are no more elements to compare in right*/
            else if(i2==n-m) {
                /* get first element of left */
                arr[i1+i2]=left[i1];
                i1++;
            }
            /* if both subarrays have elements to compare */
			else {
                /* get smaller first element of subarray */
                if(left[i1]<right[i2]) {
                    arr[i1+i2]=left[i1];
                    i1++;
                }
                else {
                    arr[i1+i2]=right[i2];
                    i2++;
                }
            }
        }
        /* deallocate memory of subarrays */
        free(left);
        free(right);
    }
    return arr;
}

/* quick sort function */
int* quickSort(int* arr, int p, int q)
{
	int i=p, j=p+1;
    /* if start index is smaller than end index */
	if(p<q) {
        /* set first element as pivot */
		int pivot = arr[p];
		for(j=p+1;j<=q;j++) {
            /* if element of index j is smaller than pivot */
			if(pivot > arr[j]) {
				i++;
				if(i!=j) { 
                    /* swap with index i if i and j are not same */
					SWAP(arr[i],arr[j]);
				}
			}
		}
        /* swap pivot with index i */
		SWAP(arr[p],arr[i]);
        /* recursively sort subarrays */
		quickSort(arr, p, i-1);
		quickSort(arr, i+1, q);
	}
    return arr;
}

/* counting sort function for radix sort */
int* countingSort(int* arr, int n, int digit)
{
    /* allocate memory for sorted array */
	int *B = mallocArray(n, FALSE);
    /* allocate memory for counting array with size 10 */
	int *C = mallocArray(10, FALSE);
	int i=0, d=1;
    /* calculate number to divide element using digit */
	for(i=0;i<digit;i++) { d *= 10; }
    /* count number of given digit */
	for(i=0;i<n;i++) {
		C[(arr[i]/d)%10]+=1;
	}
    /* accumulation of counting array */
	for(i=1;i<=9;i++) {
		C[i]+=C[i-1];
	}
    /* sort array with counting array */
	for(i=n-1;i>=0;i--) {
		B[C[(arr[i]/d)%10]-1]=arr[i];
		C[(arr[i]/d)%10]--;
	}
    /* free memory of counting array and unsorted array */
	free(C);
	free(arr);
    /* return new sorted array */
	return B;
}

/* radix sort function */
int* radixSort(int* arr, int n)
{
	int d=0, maxdigit=0;
	int i=n;
    /* calculate maximum digit of given input size */
	while(i>0) {
		i/=10;
		maxdigit++;
	}
    /* apply counting sort for each digit */
	for(d=0;d<maxdigit;d++) {
		arr = countingSort(arr, n, d);
	}
	return arr;
}

/* bucket sort function */
int* bucketSort(int* arr, int n)
{
    /* number of bucket is given input size divided by 20 */
    int bucketN=n/20, i=0, j=0, k=0;
    /* memory allocation for bucket */
    int **bucket = (int**)malloc(bucketN*sizeof(int*));
    /* memory allocation for array counting element of each bucket */
    int *bucketIdx = mallocArray(bucketN, FALSE);
    /* memory allocation for each bucket */
    for(i=0;i<bucketN;i++) {
    	bucket[i] = mallocArray(n, FALSE);
	}
    /* scatter elements to corresponding buckets */
	for(i=0;i<n;i++) {
        /* bucket index calculation with dividing element-1 to 20*/
		int a = (arr[i]-1)/20;
		bucket[a][bucketIdx[a]]=arr[i];
		bucketIdx[a]++;
	}
    /* sort each bucket with insertion sort */
	for(i=0;i<bucketN;i++) {
		bucket[i] = insertionSort(bucket[i], bucketIdx[i]);
	}
    /* merge buckets from first bucket to last bucket */
	for(i=0;i<bucketN;i++) {
		for(j=0;j<bucketIdx[i];j++) {
			arr[k]=bucket[i][j];
			k++;
		}
	}
    /* deallocate memory of buckets */
	for(i=0;i<bucketN;i++) {
		free(bucket[i]);
	}
	free(bucket);
    free(bucketIdx);
	return arr;
}

int main()
{
    int *bubble, *insertion, *merge, *quick, *radix, *bucket;
    /* list of input size */
    int nlist[3] = {1000, 5000, 10000};
    int n=0, i=0, j=0;
    time_t begin, end;
    double time;
    double timeList[18];

    for(i=0;i<3;i++) {
    	n=nlist[i];
        /* bubble sort */	
	    bubble = mallocArray(n, TRUE);
	    begin = clock();
	    bubble = bubbleSort(bubble, n);
	    end = clock();
	    time = (double)(end-begin)/CLOCKS_PER_SEC;
	    if(checkSorted(bubble, n)) {
	    	printf("Bubble Sort size %d completed at %lfs!\n", n, time);
	    	timeList[i*6+0]=time;
		}
        /* insertion sort */
	    insertion = mallocArray(n, TRUE);
	    begin = clock();
	    insertion = insertionSort(insertion, n);
	    end = clock();
	    time = (double)(end-begin)/CLOCKS_PER_SEC;
	    if(checkSorted(insertion, n)) {
	    	printf("Insertion Sort size %d completed at %lfs!\n", n, time);
	    	timeList[i*6+1]=time;
		}
        /* merge sort */
	    merge = mallocArray(n, TRUE);
	    begin = clock();
	    merge = mergeSort(merge, n);
	    end = clock();
	    time = (double)(end-begin)/CLOCKS_PER_SEC;
	    if(checkSorted(merge, n)) {
	    	printf("Merge Sort size %d completed at %lfs!\n", n, time);
	    	timeList[i*6+2]=time;
		}
	    
        /* quick sort */
	    quick = mallocArray(n, TRUE);
	    begin = clock();
	    quick = quickSort(quick, 0, n-1);
	    end = clock();
	    time = (double)(end-begin)/CLOCKS_PER_SEC;
	    if(checkSorted(quick, n)) {
	    	printf("Quick Sort size %d completed at %lfs!\n", n, time);
	    	timeList[i*6+3]=time;
		}
        /* radix sort */
	    radix = mallocArray(n, TRUE);
	    begin = clock();
	    radix = radixSort(radix, n);
	    end = clock();
	    time = (double)(end-begin)/CLOCKS_PER_SEC;
	    if(checkSorted(radix, n)) {
	    	printf("Radix Sort size %d completed at %lfs!\n", n, time);
	    	timeList[i*6+4]=time;
		}
        /* bucket sort */
    	bucket = mallocArray(n, TRUE);
    	begin = clock();
	    bucket = bucketSort(bucket, n);
	    end = clock();
	    time = (double)(end-begin)/CLOCKS_PER_SEC;
	    if(checkSorted(bucket, n)) {
	    	printf("Bucket Sort size %d completed at %lfs!\n", n, time);
	    	timeList[i*6+5]=time;
		}
	}
	
    /* display result table of input size and execution time */
	printf(" size     Bubble  Insertion      Merge      Quick      Radix     Bucket\n");
	for(i=0;i<3;i++) {
		printf("%5d", nlist[i]);
		for(j=0;j<6;j++) {
			printf("   %lf", timeList[i*6+j]);
		}
		printf("\n");
	}
    
	return 0;
}