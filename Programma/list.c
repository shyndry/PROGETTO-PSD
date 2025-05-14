#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct node {
    Veicolo value;
    struct node *next;
};

list newList(void) {
    return NULL;
}

int emptyList(list l) {
    return l == NULL;
}

list consList(Veicolo val, list l) {
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

Veicolo getFirst(list l) {
    Veicolo obj;
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
    Veicolo val;
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

int posItem(list l, Veicolo val) {
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

Veicolo getItem(list l, int pos) {
    int count = 0;
    Veicolo obj;
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
}
