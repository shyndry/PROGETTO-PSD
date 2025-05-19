#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazione.h"
#include "veicolo.h"
#include "list.h"
#include <time.h>

struct prenotazione {
    char email[100];
    Veicolo veicolo;
    time_t inizio;
    time_t fine;
    float costo_totale;
};

Prenotazione crea_prenotazione(char *email, Veicolo veicolo, int giorni) {
    Prenotazione prenotazione = malloc(sizeof(struct prenotazione));
    strcpy(prenotazione->email, email);
    prenotazione->veicolo = veicolo;

    time(&prenotazione->inizio);
    prenotazione->fine = prenotazione->inizio + (time_t)giorni * 86400;
    prenotazione->costo_totale = giorni * prendi_costo_giornaliero(veicolo);

    imposta_disponibilita(veicolo, 0);
    imposta_fine_noleggio(veicolo, prenotazione->fine);

    return prenotazione;
}

float calcola_costo(Prenotazione prenotazione) {
    return prenotazione->costo_totale;
}

void salva_storico(Prenotazione prenotazione) {
    FILE *file = fopen("storico_noleggi.txt", "a");
    if (!file) {
        perror("Errore nell'apertura del file storico_noleggi.txt");
        return;
    }

    fprintf(file, "Email: %s | Targa: %s | Inizio: %ld | Fine: %ld | Costo: %.2f\n",
            prendi_email(prenotazione),
            prendi_targa(prenotazione->veicolo),
            prenotazione->inizio,
            prenotazione->fine,
            calcola_costo(prenotazione));

    fclose(file);
}

void termina_prenotazione(Prenotazione prenotazione, Veicolo veicolo) {
    time_t ora_corrente;
    time(&ora_corrente);
    if (ora_corrente >= prenotazione->fine) {
        imposta_disponibilita(veicolo, 1);
        imposta_fine_noleggio(veicolo, 0);
        salva_storico(prenotazione);
    }
}