#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

#include <time.h>
#include "veicolo.h"
#include "list.h"

typedef struct prenotazione *Prenotazione;

typedef struct NodoPrenotazione {
    Prenotazione p;
    struct NodoPrenotazione *next;
} *ListaPrenotazioni;

Prenotazione creaPrenotazione(char *email, Veicolo v, int giorni);
void finePrenotazione(Prenotazione p);

float calcoloCosto(Prenotazione p);
void stampaPrenotazione(Prenotazione p);

char *prendiEmailUtente(Prenotazione p);
Veicolo infoVeicolo(Prenotazione p);
time_t prendiOrarioInizio(Prenotazione p);
time_t prendiOrarioFine(Prenotazione p);

int Disponibile(ListaPrenotazioni lista, Veicolo v, time_t inizio, time_t fine);
void salvaStorico(Prenotazione p);

#endif
