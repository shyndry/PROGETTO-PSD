#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

#include <time.h>
#include "veicolo.h"
#include "list.h"

typedef struct prenotazione *Prenotazione;

typedef struct nodo_prenotazione {
    Prenotazione prenotazione;
    struct nodo_prenotazione *prossimo;
} *ListaPrenotazioni;

Prenotazione crea_prenotazione(char *email, Veicolo veicolo, int giorni);
void termina_prenotazione(Prenotazione prenotazione, Veicolo veicolo);

float calcola_costo(Prenotazione prenotazione);
void stampa_prenotazione(Prenotazione prenotazione);

char *prendi_email(Prenotazione prenotazione);
Veicolo prendi_veicolo(Prenotazione prenotazione);
time_t prendi_inizio(Prenotazione prenotazione);
time_t prendi_fine(Prenotazione prenotazione);

int verifica_disponibilita(ListaPrenotazioni lista, Veicolo veicolo, time_t inizio, time_t fine);
void salva_storico(Prenotazione prenotazione);

#endif