#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct nodo {
    Veicolo valore;
    struct nodo *prossimo;
};

lista nuova_lista(void) {
    return NULL;
}

int lista_vuota(lista lista_corrente) {
    return lista_corrente == NULL;
}

lista aggiungi_a_lista(Veicolo elemento, lista lista_corrente) {
    lista nodo = malloc(sizeof(struct nodo));
    nodo->valore = elemento;
    nodo->prossimo = lista_corrente;
    return nodo;
}

lista ottieni_coda_lista(lista lista_corrente) {
    if (lista_vuota(lista_corrente)) {
        return NULL;
    }
    return lista_corrente->prossimo;
}

Veicolo ottieni_primo_elemento(lista lista_corrente) {
    if (lista_vuota(lista_corrente)) {
        return NULL;
    }
    return lista_corrente->valore;
}

int dimensione_lista(lista lista_corrente) {
    int count = 0;
    while (!lista_vuota(lista_corrente)) {
        lista_corrente = ottieni_coda_lista(lista_corrente);
        count++;
    }
    return count;
}

void stampa_lista(lista lista_corrente) {
    while (!lista_vuota(lista_corrente)) {
        stampa_veicolo(ottieni_primo_elemento(lista_corrente));
        lista_corrente = ottieni_coda_lista(lista_corrente);
    }
}