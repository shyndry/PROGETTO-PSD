#ifndef VEICOLO_H
#define VEICOLO_H
#define NULLITEM 0

#include <time.h>
#include "list.h"

typedef struct veicolo *Veicolo;

typedef struct nodo_veicolo {
    Veicolo veicolo;
    struct nodo_veicolo *prossimo;
} *ListaVeicoli;

Veicolo crea_veicolo(char *targa, char *modello, float costo_giornaliero);
void stampa_veicolo(Veicolo veicolo);
char *prendi_targa(Veicolo veicolo);
float prendi_costo_giornaliero(Veicolo veicolo);
int verifica_disponibilita(Veicolo veicolo);
void imposta_disponibilita(Veicolo veicolo, int stato);
time_t prendi_fine_noleggio(Veicolo veicolo);
void imposta_fine_noleggio(Veicolo veicolo, time_t fine);
ListaVeicoli carica_veicoli_da_file(const char *nome_file);
void aggiorna_disponibilita(ListaVeicoli lista);

#endif