#include "veicolo.h"

typedef struct nodo *lista;

lista nuova_lista(void);

int lista_vuota(lista lista_corrente);

lista aggiungi_a_lista(Veicolo elemento, lista lista_corrente);

lista ottieni_coda_lista(lista lista_corrente);

Veicolo ottieni_primo_elemento(lista lista_corrente);

int dimensione_lista(lista lista_corrente);

int posizione_elemento(lista lista_corrente, Veicolo elemento);

Veicolo ottieni_elemento(lista lista_corrente, int posizione);

lista inverti_lista(lista lista_corrente);

void stampa_lista(lista lista_corrente);