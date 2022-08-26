#include <stdio.h>
#include <stdlib.h>

#define MAX_RANGE 50

/* type and struct for linked list */
typedef struct listNode *nodePtr;
typedef struct listNode {
    int data;
    nodePtr next;
} listNode;

/* memory allocation of new node */
nodePtr newNode(int data) {
    nodePtr node = (nodePtr)malloc(sizeof(listNode));
    node->data = data;
    node->next = NULL;
    return node;
}

/* append new node to linked list */
nodePtr appendNode(nodePtr list, int data) {
    nodePtr tempList = list;
    nodePtr node = newNode(data);
    if(list == NULL) {
        return node;
    }
    while(list->next != NULL) { list = list->next; }
    list->next = node;
    return tempList;
}

/* free all memory of linked list */
void removeList(nodePtr list) {
    nodePtr tempNode;
    if(list == NULL) {
        return;
    }
    while(list != NULL) {
        tempNode = list;
        list = list->next;
        free(tempNode);
    }
    return;
}

/* traverse and print linked list from start to end */
void traverseList(nodePtr list) {
    if(list == NULL) {
        printf("empty linked list\n");
        return;
    }
    while(list != NULL) {
        printf("%d ", list->data);
        list = list->next;
    }
    printf("\n");
    return;
}

/* remove duplicate data in linked list */
void removeDuplicate(nodePtr list, int range) {
    int *count;
    int i;
    nodePtr prev = NULL;
    /* array that counts data */
    count = (int*)malloc(sizeof(int)*(range+1));
    /* initialize array */
    for(i=0;i<=range;i++) {
        count[i]=0;
    }
    /* check linked list */
    while(list!=NULL) {
        /* if duplicate data, remove node */
        if(count[list->data]>0) {
            printf("%d ", list->data);
            prev->next = list->next;
            free(list);
            list=prev->next;
        }
        /* if not, count */
        else {
            count[list->data]++;
            prev = list;
            list = list->next;
        }
    }
    printf("removed\n");
    /* free memory of couning array */
    free(count);
    return;
}

int main() {
    nodePtr linkedList = NULL;
    int i=0, j=0;

    linkedList = NULL;
    
    for(i=0;i<20;i++) {
        if(j<=0) { j=i; }
        linkedList = appendNode(linkedList, (j--/2+1)*5);
    }
    printf("Before remove duplicate: ");
    traverseList(linkedList);

    removeDuplicate(linkedList, MAX_RANGE);
    printf("After remove duplicate: ");
    traverseList(linkedList);

    removeList(linkedList);

    return 0;
}