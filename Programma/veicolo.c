#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veicolo.h"
#include "list.h"

struct veicolo {
    char targa[20];
    char modello[50];
    float costoGiornaliero;
    int disponibile;
    time_t fineNoleggio;
};

Veicolo creaVeicolo(char *targa, char *modello, float costoGiornaliero) {
    Veicolo v = malloc(sizeof(struct veicolo));
    strcpy(v->targa, targa);
    strcpy(v->modello, modello);
    v->costoGiornaliero = costoGiornaliero;
    v->disponibile = 1;
    v->fineNoleggio = 0;
    return v;
}

void stampaVeicolo(Veicolo v) {
    printf("Targa: %s | Modello: %s | Costo: %.2f€/giorno | Disponibile: %s\n",
           v->targa, v->modello, v->costoGiornaliero, v->disponibile ? "Sì" : "No");
}

char *infoTarga(Veicolo v) {
    return v->targa;
}

float infoCostoGiornaliero(Veicolo v) {
    return v->costoGiornaliero;
}

int infoDisponibilita(Veicolo v) {
    return v->disponibile;
}

void impostaDisponibilita(Veicolo v, int stato) {
    v->disponibile = stato;
}

time_t fineNoleggio(Veicolo v) {
    return v->fineNoleggio;
}

void impostaFineNoleggio(Veicolo v, time_t fine) {
    v->fineNoleggio = fine;
}

ListaVeicoli caricaVeicoliDaFile(const char *nomefile) {
    FILE *fp = fopen(nomefile, "r");
    if (!fp) return NULL;

    ListaVeicoli testa = NULL;
    char targa[20], modello[50];
    float costo;

    while (fscanf(fp, "%s %s %f", targa, modello, &costo) == 3) {
        Veicolo v = creaVeicolo(targa, modello, costo);
        ListaVeicoli nuovo = malloc(sizeof(struct NodoVeicolo));
        nuovo->v = v;
        nuovo->next = testa;
        testa = nuovo;
    }

    fclose(fp);
    return testa;
}

void aggiornaDisponibilita(ListaVeicoli lista) {
    time_t now;
    time(&now);
    while (lista) {
        if (!infoDisponibilita(lista->v) && now >= fineNoleggio(lista->v)) {
            impostaDisponibilita(lista->v, 1);
        }
        lista = tailList(lista);
    }
}
