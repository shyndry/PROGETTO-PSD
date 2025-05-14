#ifndef VEICOLO_H
#define VEICOLO_H
#define NULLITEM 0

#include <time.h>
#include "list.h"

typedef struct veicolo *Veicolo;

typedef struct NodoVeicolo {
    Veicolo v;
    struct NodoVeicolo *next;
} *ListaVeicoli;

Veicolo creaVeicolo(char *targa, char *modello, float costoGiornaliero);
void stampaVeicolo(Veicolo v);
char *infoTarga(Veicolo v);
float infoCostoGiornaliero(Veicolo v);
int infoDisponibilita(Veicolo v);
void impostaDisponibilita(Veicolo v, int stato);
time_t fineNoleggio(Veicolo v);
void impostaFineNoleggio(Veicolo v, time_t fine);
ListaVeicoli caricaVeicoliDaFile(const char *NomeFILE);
void aggiornaDisponibilita(ListaVeicoli lista);

#endif
