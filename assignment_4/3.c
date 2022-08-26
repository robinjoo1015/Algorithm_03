#include <stdio.h>
#include <stdlib.h>
/* number of item, maximum capacity constant */
#define NUM_ITEM 6
#define MAX_WEIGHT 16

/* item struct containing weight and value */
typedef struct item {
    int weight;
    int value;
} item;
/* struct containing index of item and value per weight */
typedef struct weightValue {
    int index;
    float valuePerWeight;
} weightValue;

/* compare weightValue function for sorting */
int compareWeightValue(const void *s1, const void *s2) {
    weightValue *wv1 = (weightValue*)s1;
    weightValue *wv2 = (weightValue*)s2;
    if(wv1->valuePerWeight>=wv2->valuePerWeight) { return 0; }
    else { return 1; }
}

/* fractional knapsack function with greedy algorithm */
float fractionalKnapsack(item *itemList, int itemNum, int capacity) {
    weightValue weightValueList[itemNum];
    int i;
    float maxValue=0;
    /* calculate value per weight of items */
    for(i=0;i<itemNum;i++) {
        weightValueList[i].index = i+1;
        weightValueList[i].valuePerWeight = ((float)itemList[i+1].value)/((float)itemList[i+1].weight);
    }
    /* sort value per weight list */
    qsort(weightValueList, itemNum, sizeof(weightValue), compareWeightValue);
    printf(" index weight  value fraction\n");
    for(i=0;i<itemNum;i++) {
        if(capacity>0) {
            if(capacity>itemList[weightValueList[i].index].weight) {
                /* take whole item */
                maxValue += itemList[weightValueList[i].index].value;
                printf("     %d      %d     %d      %d/%d\n", 
                weightValueList[i].index, 
                itemList[weightValueList[i].index].weight, 
                itemList[weightValueList[i].index].value, 
                itemList[weightValueList[i].index].weight, 
                itemList[weightValueList[i].index].weight);
                capacity -= itemList[weightValueList[i].index].weight;
            }
            else {
                /* take fraction of last selected item */
                maxValue += weightValueList[i].valuePerWeight * capacity;
                printf("     %d      %d   %.2f      %d/%d\n", 
                weightValueList[i].index, 
                capacity, 
                weightValueList[i].valuePerWeight * capacity, 
                capacity, 
                itemList[weightValueList[i].index].weight);
                capacity = 0;
            }
        } 
        else { 
            /* no more capacity */
            break;
        }
    }
    return maxValue;
}

int main() {
    float maxValue = 0;
    item itemList[NUM_ITEM+1];
    /* initialize item info */
    itemList[1].weight = 6; itemList[1].value = 60;
    itemList[2].weight = 10; itemList[2].value = 20;
    itemList[3].weight = 3; itemList[3].value = 12;
    itemList[4].weight = 5; itemList[4].value = 80;
    itemList[5].weight = 1; itemList[5].value = 30;
    itemList[6].weight = 3; itemList[6].value = 60;
    /* calculate maximum value */
    printf("Maximum Value = %f\n", fractionalKnapsack(itemList, NUM_ITEM, MAX_WEIGHT));
    return 0;
}
