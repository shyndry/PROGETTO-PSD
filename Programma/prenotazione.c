/**
 * Implementazione dell'ADT Prenotazione per gestire il noleggio di veicoli.
 * 
 * Questo file implementa le funzionalità definite in prenotazione.h per la
 * creazione, gestione e terminazione delle prenotazioni di veicoli.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazione.h"
#include "veicolo.h"
#include "list.h"
#include <time.h>

/**
 * Struttura interna di una prenotazione.
 * Contiene tutti i dati relativi a una prenotazione di un veicolo.
 */
struct prenotazione {
    char email[100];        /* Email dell'utente che ha effettuato la prenotazione */
    Veicolo veicolo;        /* Veicolo associato alla prenotazione */
    time_t inizio;          /* Timestamp di inizio prenotazione */
    time_t fine;            /* Timestamp di fine prenotazione */
    float costo_totale;     /* Costo totale della prenotazione */
};

/**
 * Funzione: calcola_costo
 * ---
 * Calcola il costo totale di una prenotazione in base al periodo e al prezzo giornaliero.
 * 
 * Parametri:
 * inizio: data di inizio del noleggio (tipo time_t)
 * fine: data di fine del noleggio (tipo time_t)
 * costo: prezzo per giorno (float >= 0)
 * 
 * Pre-condizione:
 * - inizio e fine devono essere date valide
 * - fine >= inizio
 * - costo >= 0
 * 
 * Post-condizione:
 * - Ritorna il costo totale: numero di giorni * costo al giorno
 * - Se il noleggio dura almeno 30 giorni, applica uno sconto del 20%
 * 
 * Ritorna:
 * float: costo finale della prenotazione
 */

float calcola_costo(time_t inizio, time_t fine, float costo){
    int giorni;
    float prezzo;
    giorni=((fine-inizio)/86400)+1;
    prezzo= giorni*costo;
    if(giorni<30){
        return prezzo;
    }else{
        return prezzo-=(prezzo/100)*20;
    }
    
}

/**
 * Funzione: crea_prenotazione
 * ---
 * Crea una nuova prenotazione per un veicolo, calcolandone costo e durata.
 * 
 * Parametri:
 * email: indirizzo email del cliente
 * veicolo: struttura contenente i dati del veicolo prenotato
 * inizio: data di inizio della prenotazione
 * fine: data di fine della prenotazione
 * 
 * Pre-condizione:
 * - email != NULL && strlen(email) > 0
 * - veicolo != NULL
 * - inizio <= fine
 * 
 * Post-condizione:
 * - Viene allocata e restituita una nuova struttura Prenotazione
 * - Il veicolo viene segnato come non disponibile
 * - Viene calcolato e salvato il costo totale
 * 
 * Ritorna:
 * Puntatore a struttura Prenotazione (non NULL)
 */

Prenotazione crea_prenotazione(char *email, Veicolo veicolo, time_t inizio, time_t fine) {
    Prenotazione prenotazione = malloc(sizeof(struct prenotazione));
    if (prenotazione == NULL) {
        fprintf(stderr, "Errore di allocazione memoria per prenotazione\n");
        exit(EXIT_FAILURE);
    }
    
    strcpy(prenotazione->email, email);
    prenotazione->veicolo = veicolo;

    /* Imposta il periodo della prenotazione */
    prenotazione->inizio=inizio;
    prenotazione->fine = fine;
    
    
    /* Calcola il costo totale in base al costo giornaliero del veicolo */
    prenotazione->costo_totale = calcola_costo(inizio, fine, prendi_costo_giornaliero(veicolo));


    /* Segna il veicolo come non disponibile e imposta la fine del noleggio */
    imposta_disponibilita(veicolo, 0);

    return prenotazione;
}

/**
 * Funzione: prendi_costo
 * ---
 * Restituisce il costo totale di una prenotazione.
 * 
 * Parametri:
 * prenotazione: struttura Prenotazione da cui ottenere il costo
 * 
 * Pre-condizione:
 * - prenotazione != NULL
 * 
 * Post-condizione:
 * - Ritorna il costo totale salvato nella prenotazione
 * 
 * Ritorna:
 * float: costo totale della prenotazione
 */

float prendi_costo(Prenotazione prenotazione) {
    return prenotazione->costo_totale;
}

/**
 * Funzione: stampa_prenotazione
 * ---
 * Stampa a video tutti i dettagli di una prenotazione in formato leggibile.
 * 
 * Parametri:
 * prenotazione: struttura contenente i dettagli della prenotazione
 * 
 * Pre-condizione:
 * - prenotazione != NULL
 * 
 * Post-condizione:
 * - Stampa su stdout email, veicolo, date e costo totale della prenotazione
 * 
 * Effetti collaterali:
 * - Output su schermo
 */

void stampa_prenotazione(Prenotazione prenotazione) {
    char inizio_str[30], fine_str[30];
    struct tm *tm_info;
    
    /* Converte i timestamp in stringhe leggibili */
    tm_info = localtime(&prenotazione->inizio);
    strftime(inizio_str, sizeof(inizio_str), "%d/%m/%Y", tm_info);
    
    tm_info = localtime(&prenotazione->fine);
    strftime(fine_str, sizeof(fine_str), "%d/%m/%Y", tm_info);
    
    printf("\n==== DETTAGLI PRENOTAZIONE ====\n");
    printf("Email: %s\n", prenotazione->email);
    printf("Veicolo: ");
    stampa_veicolo(prenotazione->veicolo);
    printf("Data inizio: %s\n", inizio_str);
    printf("Data fine: %s\n", fine_str);
    printf("Costo totale: %.2f€\n", prenotazione->costo_totale);
    printf("==============================\n\n");
}

/**
 * Funzione: prendi_email
 * ---
 * Restituisce l’email associata alla prenotazione.
 * 
 * Parametri:
 * prenotazione: prenotazione da cui recuperare l’email
 * 
 * Pre-condizione:
 * - prenotazione != NULL
 * 
 * Post-condizione:
 * - Ritorna il campo email della prenotazione
 * 
 * Ritorna:
 * Puntatore a char (stringa email)
 */

char *prendi_email(Prenotazione prenotazione) {
    return prenotazione->email;
}

/**
 * Funzione: prendi_veicolo
 * ---
 * Restituisce il veicolo associato alla prenotazione.
 * 
 * Parametri:
 * prenotazione: prenotazione da cui ottenere il veicolo
 * 
 * Pre-condizione:
 * - prenotazione != NULL
 * 
 * Post-condizione:
 * - Ritorna il veicolo contenuto nella prenotazione
 * 
 * Ritorna:
 * Struttura Veicolo
 */

Veicolo prendi_veicolo(Prenotazione prenotazione) {
    return prenotazione->veicolo;
}

/**
 * Funzione: prendi_inizio
 * ---
 * Restituisce la data di inizio della prenotazione.
 * 
 * Parametri:
 * prenotazione: struttura prenotazione da cui estrarre la data
 * 
 * Pre-condizione:
 * - prenotazione != NULL
 * 
 * Post-condizione:
 * - Ritorna il timestamp dell’inizio del noleggio
 * 
 * Ritorna:
 * time_t: data di inizio
 */

time_t prendi_inizio(Prenotazione prenotazione) {
    return prenotazione->inizio;
}

/**
 * Funzione: prendi_fine
 * ---
 * Restituisce la data di fine della prenotazione.
 * 
 * Parametri:
 * prenotazione: struttura prenotazione da cui estrarre la data
 * 
 * Pre-condizione:
 * - prenotazione != NULL
 * 
 * Post-condizione:
 * - Ritorna il timestamp della fine del noleggio
 * 
 * Ritorna:
 * time_t: data di fine
 */

time_t prendi_fine(Prenotazione prenotazione) {
    return prenotazione->fine;
}

/**
 * Funzione: prendi_targa_veicolo
 * ---
 * Restituisce la targa del veicolo associato alla prenotazione.
 * 
 * Parametri:
 * p: struttura prenotazione da cui ottenere la targa
 * 
 * Pre-condizione:
 * - p != NULL
 * 
 * Post-condizione:
 * - Ritorna una stringa contenente la targa del veicolo prenotato
 * 
 * Ritorna:
 * Puntatore a char (stringa targa)
 */

char *prendi_targa_veicolo(Prenotazione p){
    return prendi_targa(prendi_veicolo(p));
}



