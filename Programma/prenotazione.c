#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazioni.h"
#include "veicolo.h"
#include "list.h"
#include <time.h>

struct prenotazione {
    char email[100];
    Veicolo veicolo;
    time_t inizio;
    time_t fine;
    float costoTot;
};

Prenotazione creaPrenotazione(char *email, Veicolo v, int giorni) {
    Prenotazione p = malloc(sizeof(struct prenotazione));
    strcpy(p->email, email);
    p->veicolo = v;

    time(&p->inizio);
    p->fine = p->inizio + (time_t)giorni * 24 * 3600;

    p->costoTot = giorni * infoCostoGiornaliero(v);

    impostaDisponibilita(v, 0);
    impostaFineNoleggio(v, p->fine);

    return p;
}

float calcoloCosto(Prenotazione p) {
    return p->costoTot;
}

void salvaStorico(Prenotazione p) {
    FILE *f = fopen("StoricoNoleggi.txt", "a");
    if (!f) {
        perror("Impossibile aprire StoricoNoleggi.txt");
        return;
    }

    fprintf(f,
            "Email: %s | Targa: %s | Inizio: %ld | Fine: %ld | Costo: %.2f\n",
            prendiEmailUtente(p),
            infoTarga(infoVeicolo(p)),
            (long)prendiOrarioInizio(p),
            (long)prendiOrarioFine(p),
            calcoloCosto(p));

    fclose(f);
}

void finePrenotazione(Prenotazione p, Veicolo v) {
    time_t now;
    time(&now);
    if (now >= p->fine) {
        impostaDisponibilita(v, 1);
        impostaFineNoleggio(v, 0);
        salvaStorico(p);
    }
}

char *prendiEmailUtente(Prenotazione p) {
    return p->email;
}

Veicolo infoVeicolo(Prenotazione p) {
    return p->veicolo;
}

time_t prendiOrarioInizio(Prenotazione p) {
    return p->inizio;
}

time_t prendiOrarioFine(Prenotazione p) {
    return p->fine;
}

int Disponibile(ListaPrenotazioni lista, Veicolo v, time_t inizio, time_t fine) {
    while (lista) {
        if (infoVeicolo(lista->p) == v) {
            time_t i = prendiOrarioInizio(lista->p), f = prendiOrarioFine(lista->p);
            if (!(fine <= i || inizio >= f)) {
                return 0;
            }
        }
        lista = tailList(lista);
    }
    return 1;
}

void stampaPrenotazione(Prenotazione p) {
    printf("Email: %s\n", prendiEmailUtente(p));
    printf("Targa: %s\n", infoTarga(infoVeicolo(p)));
    printf("Inizio: %s", ctime(&p->inizio));
    printf("Fine: %s", ctime(&p->fine));
    printf("Costo totale: %.2f €\n", calcoloCosto(p));
}
