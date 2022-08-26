#include <stdio.h>
#include <stdlib.h>

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

/* insert new node to linked list at index */
nodePtr insertNode(nodePtr list, int data, int index) {
    nodePtr node;
    nodePtr tempList = list;
    int i=0;
    if(index == 0) {
        node = newNode(data);
        node->next = list;
        return node;
    }
    if(list == NULL) {
        printf("index out of range\n");
        return tempList;
    }
    for(i=0;i<index-1;i++) {
        list = list->next;
        if(list == NULL) {
            printf("index out of range\n");
            return tempList;
        }
    }
    node = newNode(data);
    node->next = list->next;
    list->next = node;
    return tempList;
}

/* remove node at index from linked list */
nodePtr removeNode(nodePtr list, int index) {
    nodePtr tempList = list;
    nodePtr tempNode;
    int i=0;
    if(index == 0) {
        if(list == NULL) {
            printf("index out of range\n");
            return tempList;
        } else {
            list = list->next;
            free(tempList);
            return list;
        }
    }
    for(i=0;i<index-1;i++) { 
        if(list==NULL) {
            printf("index out of range\n");
            return tempList;
        }
        list = list->next;
    }
    tempNode = list->next;
    if(tempNode==NULL) {
        printf("index out of range\n");
        return tempList;
    }
    list->next = list->next->next;
    free(tempNode);
    return tempList;
}

/* reverse linked list */
nodePtr reverseList(nodePtr list) {
    if(list == NULL || list->next == NULL) {
        return list;
    }
    nodePtr A=NULL, B=list, C=list->next;
    while(B!=NULL) {
        B->next = A;
        A = B;
        B = C;
        if(C==NULL) { break; }
        C = C->next;
    }
    return A;
}

int main() {
    /* linked list for testing each function */
    nodePtr appendTestList = NULL;
    nodePtr insertTestList = NULL;
    nodePtr removeTestList = NULL;
    nodePtr reverseTestList = NULL;
    int i=0;
    
    printf("\nAppend Function Test\n");
    traverseList(appendTestList); //empty
    appendTestList = appendNode(appendTestList, 0);
    appendTestList = appendNode(appendTestList, 1);
    appendTestList = appendNode(appendTestList, 2);
    traverseList(appendTestList); // 0 1 2

    printf("\nInsert Function Test\n");
    traverseList(insertTestList); //empty
    insertTestList = insertNode(insertTestList, 0, 1); //error
    insertTestList = insertNode(insertTestList, 0, 0);
    insertTestList = insertNode(insertTestList, 1, 1);
    insertTestList = insertNode(insertTestList, 2, 2);
    insertTestList = insertNode(insertTestList, 4, 4); //error
    traverseList(insertTestList); // 0 1 2

    printf("\nRemove Function Test\n");
    removeTestList = insertTestList;
    traverseList(removeTestList); // 0 1 2
    removeTestList = removeNode(removeTestList, 3); //error
    removeTestList = removeNode(removeTestList, 1);
    traverseList(removeTestList); // 0 2
    removeTestList = removeNode(removeTestList, 1);
    traverseList(removeTestList); // 0
    removeTestList = removeNode(removeTestList, 0);
    removeTestList = removeNode(removeTestList, 0); //error
    traverseList(removeTestList); //empty

    printf("\nReverse Function Test\n");
    for(i=0;i<10;i++) {
        reverseTestList = appendNode(reverseTestList, rand()%100);
    }
    traverseList(reverseTestList);
    reverseTestList = reverseList(reverseTestList);
    traverseList(reverseTestList);

    free(appendTestList);
    free(insertTestList);
    free(removeTestList);
    free(reverseTestList);
    return 0;
}