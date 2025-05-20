/**
 * Implementazione dell'ADT Lista di Veicoli
 *
 * Questo file contiene le implementazioni delle funzioni
 * dichiarate nell'header list.h per la gestione di liste di veicoli.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "veicolo.h"

/**
 * Struttura interna del nodo della lista.
 * Ogni nodo contiene un puntatore a un veicolo e un puntatore al nodo successivo.
 */
struct nodo {
    Veicolo valore;
    struct nodo *prossimo;
};

/**
 * Crea una nuova lista vuota.
 *
 * Post-condizione: Ritorna una lista vuota (NULL).
 */
lista nuova_lista(void) {
    return NULL;
}

/**
 * Verifica se una lista è vuota.
 *
 * Pre-condizione: lista_corrente è una lista valida
 * Post-condizione: Ritorna 1 se vuota, 0 altrimenti.
 */
int lista_vuota(lista lista_corrente) {
    return lista_corrente == NULL;
}

/**
 * Aggiunge un elemento in testa alla lista.
 *
 * Pre-condizione: elemento != NULL
 * Post-condizione: Ritorna una nuova lista con l'elemento aggiunto in testa.
 */
lista aggiungi_a_lista(Veicolo elemento, lista lista_corrente) {
    lista nodo = malloc(sizeof(struct nodo));
    if (nodo == NULL) {
        fprintf(stderr, "Errore di allocazione memoria\n");
        exit(EXIT_FAILURE);
    }
    nodo->valore = elemento;
    nodo->prossimo = lista_corrente;
    return nodo;
}

/**
 * Ottiene la coda della lista (tutti gli elementi tranne il primo).
 *
 * Pre-condizione: lista_corrente è una lista valida
 * Post-condizione: Ritorna la lista senza il primo elemento.
 */
lista ottieni_coda_lista(lista lista_corrente) {
    if (lista_vuota(lista_corrente)) {
        return NULL;
    }
    return lista_corrente->prossimo;
}

/**
 * Ottiene il primo elemento della lista.
 *
 * Pre-condizione: lista_corrente è una lista valida
 * Post-condizione: Ritorna il primo veicolo della lista o NULL se vuota.
 */
Veicolo ottieni_primo_elemento(lista lista_corrente) {
    if (lista_vuota(lista_corrente)) {
        return NULL;
    }
    return lista_corrente->valore;
}

/**
 * Calcola la dimensione (numero di elementi) della lista.
 *
 * Pre-condizione: lista_corrente è una lista valida
 * Post-condizione: Ritorna il numero di elementi nella lista.
 */
int dimensione_lista(lista lista_corrente) {
    int count = 0;
    while (!lista_vuota(lista_corrente)) {
        lista_corrente = ottieni_coda_lista(lista_corrente);
        count++;
    }
    return count;
}

/**
 * Trova la posizione di un elemento nella lista.
 *
 * Questa funzione scorre la lista cercando un veicolo corrispondente
 * a quello passato e ritorna la sua posizione (indice a base 0).
 * Il confronto avviene utilizzando la targa del veicolo.
 *
 * Pre-condizione: lista_corrente e elemento non sono NULL
 * Post-condizione: Ritorna l'indice dell'elemento se presente, -1 altrimenti.
 */
int posizione_elemento(lista lista_corrente, Veicolo elemento) {
    int pos = 0;

    if (elemento == NULL) {
        return -1;
    }

    /* Scorre la lista cercando l'elemento */
    while (!lista_vuota(lista_corrente)) {
        /* Confronta gli elementi in base alla targa */
        if (strcmp(prendi_targa(ottieni_primo_elemento(lista_corrente)),
                   prendi_targa(elemento)) == 0) {
            return pos;
        }

        lista_corrente = ottieni_coda_lista(lista_corrente);
        pos++;
    }

    /* Se l'elemento non è stato trovato */
    return -1;
}

/**
 * Ottiene l'elemento alla posizione specificata nella lista.
 *
 * Pre-condizione: lista_corrente è una lista valida, posizione >= 0
 * Post-condizione: Ritorna il veicolo alla posizione specificata,
 *                  o NULL se la posizione non è valida.
 */
Veicolo ottieni_elemento(lista lista_corrente, int posizione) {
    int i = 0;

    /* Controlla che la posizione sia valida */
    if (posizione < 0 || lista_vuota(lista_corrente)) {
        return NULL;
    }

    /* Scorre la lista fino alla posizione desiderata */
    while (i < posizione && !lista_vuota(lista_corrente)) {
        lista_corrente = ottieni_coda_lista(lista_corrente);
        i++;
    }

    /* Se abbiamo raggiunto la posizione desiderata */
    if (i == posizione && !lista_vuota(lista_corrente)) {
        return ottieni_primo_elemento(lista_corrente);
    }

    /* Se la posizione è oltre la fine della lista */
    return NULL;
}

/**
 * Inverte l'ordine degli elementi nella lista.
 *
 * Questa funzione crea una nuova lista con gli elementi
 * nell'ordine inverso rispetto alla lista originale.
 *
 * Pre-condizione: lista_corrente è una lista valida
 * Post-condizione: Ritorna una nuova lista con gli elementi in ordine invertito.
 */
lista inverti_lista(lista lista_corrente) {
    lista lista_invertita = nuova_lista();
    lista temp = lista_corrente;

    /* Scorre la lista originale e aggiunge ogni elemento in testa alla nuova lista */
    while (!lista_vuota(temp)) {
        lista_invertita = aggiungi_a_lista(ottieni_primo_elemento(temp), lista_invertita);
        temp = ottieni_coda_lista(temp);
    }

    return lista_invertita;
}

/**
 * Stampa tutti gli elementi della lista.
 *
 * Questa funzione scorre la lista e stampa le informazioni di ogni veicolo.
 *
 * Pre-condizione: lista_corrente è una lista valida
 * Post-condizione: Vengono visualizzate a video le informazioni di tutti i veicoli.
 */
void stampa_lista(lista lista_corrente) {
    if (lista_vuota(lista_corrente)) {
        printf("La lista è vuota\n");
        return;
    }

    printf("\n===== ELENCO VEICOLI =====\n");
    while (!lista_vuota(lista_corrente)) {
        stampa_veicolo(ottieni_primo_elemento(lista_corrente));
        lista_corrente = ottieni_coda_lista(lista_corrente);
    }
    printf("==========================\n\n");
}