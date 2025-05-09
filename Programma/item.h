#ifndef ITEM_H
#define ITEM_H
#include <stdlib.h>

typedef struct prenotazione *item;
#endif

#define NULLITEM NULL

item input_item(); 
item creaItem();
void output_item(item x);

