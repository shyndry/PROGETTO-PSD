#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veicolo.h"
#include "list.h"

struct veicolo {
    char targa[20];
    char modello[50];
    float costo_giornaliero;
    int disponibile;
    time_t fine_noleggio;
};

Veicolo crea_veicolo(char *targa, char *modello, float costo_giornaliero) {
    Veicolo veicolo = malloc(sizeof(struct veicolo));
    strcpy(veicolo->targa, targa);
    strcpy(veicolo->modello, modello);
    veicolo->costo_giornaliero = costo_giornaliero;
    veicolo->disponibile = 1;
    veicolo->fine_noleggio = 0;
    return veicolo;
}

void stampa_veicolo(Veicolo veicolo) {
    printf("Targa: %s | Modello: %s | Costo: %.2f€/giorno | Disponibile: %s\n",
           veicolo->targa, veicolo->modello, veicolo->costo_giornaliero, veicolo->disponibile ? "Sì" : "No");
}

char *prendi_targa(Veicolo veicolo) {
    return veicolo->targa;
}

float prendi_costo_giornaliero(Veicolo veicolo) {
    return veicolo->costo_giornaliero;
}

int verifica_disponibilita(Veicolo veicolo) {
    return veicolo->disponibile;
}

void imposta_disponibilita(Veicolo veicolo, int stato) {
    veicolo->disponibile = stato;
}

time_t prendi_fine_noleggio(Veicolo veicolo) {
    return veicolo->fine_noleggio;
}

void imposta_fine_noleggio(Veicolo veicolo, time_t fine) {
    veicolo->fine_noleggio = fine;
}

ListaVeicoli carica_veicoli_da_file(const char *nome_file) {
    FILE *fp = fopen(nome_file, "r");
    if (!fp) return NULL;

    ListaVeicoli testa = NULL;
    char targa[20], modello[50];
    float costo;

    while (fscanf(fp, "%s %s %f", targa, modello, &costo) == 3) {
        Veicolo veicolo = crea_veicolo(targa, modello, costo);
        ListaVeicoli nuovo = malloc(sizeof(struct nodo_veicolo));
        nuovo->veicolo = veicolo;
        nuovo->prossimo = testa;
        testa = nuovo;
    }

    fclose(fp);
    return testa;
}

void aggiorna_disponibilita(ListaVeicoli lista) {
    time_t ora_attuale;
    time(&ora_attuale);
    while (lista) {
        if (!verifica_disponibilita(lista->veicolo) && ora_attuale >= prendi_fine_noleggio(lista->veicolo)) {
            imposta_disponibilita(lista->veicolo, 1);
        }
        lista = ottieni_coda_lista(lista);
    }
}