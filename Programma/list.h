#ifndef LIST_H
#define LIST_H

/**
 * Tipo di riferimento lista - ADT per gestire liste di veicoli.
 * Implementa una lista concatenata di elementi di tipo Veicolo.
 */
typedef struct nodo *lista;

/**
 * Crea una nuova lista vuota.
 *
 * Post-condizione: l = NIL, lista vuota inizializzata.
 *
 * Ritorna: Una lista vuota (NULL).
 */
lista nuova_lista(void);

/**
 * Verifica se una lista è vuota.
 *
 * Pre-condizione: l != NULL
 * Post-condizione: vuota = 1 se la lista è vuota, vuota = 0 altrimenti.
 *
 * Ritorna: 1 se vuota, 0 altrimenti.
 */
int lista_vuota(lista lista_corrente);

/**
 * Aggiunge un elemento in testa alla lista.
 *
 * Pre-condizione: v != NULL, l != NULL
 * Post-condizione: l1 è la lista ottenuta aggiungendo v in testa a l.
 *
 * Ritorna: La lista aggiornata con il nuovo elemento in testa.
 */
lista aggiungi_a_lista(void *elemento, lista lista_corrente);

/**
 * Ottiene la coda della lista (tutti gli elementi tranne il primo).
 *
 * Pre-condizione: l != NULL e l non vuota
 * Post-condizione: l1 è la lista ottenuta rimuovendo il primo elemento di l.
 *
 * Ritorna: La lista senza il primo elemento.
 */
lista ottieni_coda_lista(lista lista_corrente);

/**
 * Ottiene il primo elemento della lista.
 *
 * Pre-condizione: l != NULL e l non vuota
 * Post-condizione: v è il primo elemento di l.
 *
 * Ritorna: Il primo veicolo della lista, NULL se la lista è vuota.
 */
void* ottieni_primo_elemento(lista lista_corrente);

/**
 * Calcola la dimensione (numero di elementi) della lista.
 *
 * Pre-condizione: l != NULL
 * Post-condizione: dim = numero di elementi in l.
 *
 * Ritorna: Il numero di elementi nella lista.
 */
int dimensione_lista(lista lista_corrente);

/**
 * Ottiene l'elemento alla posizione specificata.
 *
 * Pre-condizione: l != NULL, 0 <= pos < dimensione_lista(l)
 * Post-condizione: v = elemento alla posizione pos in l.
 *
 * Ritorna: Il veicolo alla posizione specificata, NULL se non esistente.
 */
void *ottieni_elemento(lista lista_corrente, int posizione);

/**
 * Inverte l'ordine degli elementi nella lista.
 *
 * Pre-condizione: l != NULL
 * Post-condizione: l1 è la lista l con l'ordine degli elementi invertito.
 *
 * Ritorna: Una nuova lista con gli elementi in ordine invertito.
 */
lista inverti_lista(lista lista_corrente);
