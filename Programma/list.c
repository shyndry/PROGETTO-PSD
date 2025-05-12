#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "list.h"

struct node {
    item value;
    struct node *next;
};

list newList(void) {
    return NULL;
}

int emptyList(list l) {
    return l == NULL;
}

list consList(item val, list l) {
    list node = malloc(sizeof(struct node));
    node->value = val;
    node->next = l;
    return node;
}

list tailList(list l) {
    list temp = l;
    if (emptyList(l)) {
        return NULL;
    }
    if (l != NULL) {
        temp = l->next;
    } else {
        temp = NULL;
    }
    return temp;
}

item getFirst(list l) {
    item obj;
    if (emptyList(l)) {
        return NULL;
    }
    if (l != NULL) {
        obj = l->value;
    } else {
        obj = NULLITEM;
    }
    return obj;
}

int sizeList(list l) {
    int n = 0;
    list temp = l;
    while (!emptyList(temp)) {
        n++;
        temp = tailList(temp);
    }
    return n;
}

void outputList(list l) {
    int i = 0;
    item val;
    list temp = l;

    while (!emptyList(temp)) {
        val = getFirst(temp);
        printf("Elemento di posizione %d: ", i);
        output_item(val);
        printf("\n");
        temp = tailList(temp);
        i++;
    }
}

int posItem(list l, item val) {
    int count = 0;
    int PosNum = 0;
    list temp = l;
    if (emptyList(l)) {
        return -1;
    }
    while (temp != NULL) {
        if (val == temp->value) {
            PosNum = count;
        }
        count++;
    }
    return PosNum;
}

item getItem(list l, int pos) {
    int count = 0;
    item obj;
    list temp = l;
    if (emptyList(l)) {
        return NULL;
    }
    while (temp != NULL && count < pos) {
        count++;
        temp = tailList(temp);
    }
    if (!emptyList(temp)) {
        obj = getFirst(temp);
    } else {
        obj = NULLITEM;
    }
   
