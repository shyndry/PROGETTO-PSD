#include "veicolo.h"

typedef struct node *list;

list newList(void);

int emptyList(list l);

list consList(Veicolo val, list l);

list tailList(list l);

Veicolo getFirst (list l);

int sizeList (list l);

int posItem (list l, Veicolo val);

Veicolo getItem (list l, int pos);

list reverseList (list l);

void outputList (list l);
