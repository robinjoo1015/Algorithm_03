#include <stdio.h>

/* recursive binary search function returns index of target value */
int binarySearch(int *list, int target, int left, int right) {
    int mid = (left + right) / 2;
    if(list[mid]==target) {
        return mid;
    } else {
        if(list[mid]<target) {
            return binarySearch(list, target, mid+1, right);
        } else {
            return binarySearch(list, target, left, mid-1);
        }
    }
}

int main() {
    int list[] = {12,34,37,45,57,82,99,120,134};
    int target = 120;
    printf("%d is at index %d", target, binarySearch(list, target, 0, sizeof(list)/sizeof(int)-1));
    return 0;
}
