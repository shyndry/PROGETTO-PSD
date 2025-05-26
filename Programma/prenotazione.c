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
 * Calcola il costo totale di una prenotazione in base al periodo e al prezzo giornaliero.
 * 
 * Pre-condizioni: inizio e fine sono valori `time_t` validi, con fine >= inizio,
 *                 costo è un valore float >= 0 che rappresenta il prezzo per giorno
 * 
 * Post-condizioni:  Ritorna il prezzo totale calcolato come (numero di giorni * costo al giorno),
 *                   Se il noleggio dura almeno 30 giorni, applica uno sconto del 20%
 *
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
 * Crea una nuova prenotazione per un veicolo.
 * 
 * Questa funzione alloca e inizializza una nuova prenotazione con i dati forniti,
 * calcolando automaticamente il periodo e il costo in base al numero di giorni.
 * Imposta anche lo stato del veicolo come non disponibile.
 * 
 * Pre-condizione: email != NULL && strlen(email) > 0, veicolo != NULL, giorni > 0
 * Post-condizione: La prenotazione viene creata con i dati specificati
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
    prenotazione->costo_totale = calcola_costo(inizio, fine, infoCostoGiornaliero(veicolo));


    /* Segna il veicolo come non disponibile e imposta la fine del noleggio */
    imposta_disponibilita(veicolo, 0);
    imposta_fine_noleggio(veicolo, prenotazione->fine);

    return prenotazione;
}

/**
 * Calcola il costo totale di una prenotazione.
 * 
 * Pre-condizione: prenotazione != NULL, fine(p) > inizio(p)
 * Post-condizione: Ritorna il costo totale della prenotazione
 */
float prendi_costo(Prenotazione prenotazione) {
    return prenotazione->costo_totale;
}

/**
 * Stampa i dettagli di una prenotazione in modo leggibile.
 * 
 * Visualizza tutte le informazioni di una prenotazione: email dell'utente,
 * veicolo noleggiato, date di inizio e fine, e costo totale.
 * 
 * Pre-condizione: prenotazione != NULL
 * Post-condizione: Vengono mostrate tutte le informazioni della prenotazione a video
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
 * Restituisce l'email dell'utente associato alla prenotazione.
 * 
 * Pre-condizione: prenotazione != NULL
 * Post-condizione: Ritorna un puntatore alla stringa email della prenotazione
 */
char *prendi_email(Prenotazione prenotazione) {
    return prenotazione->email;
}

/**
 * Restituisce il veicolo associato alla prenotazione.
 * 
 * Pre-condizione: prenotazione != NULL
 * Post-condizione: Ritorna un puntatore al veicolo della prenotazione
 */
Veicolo prendi_veicolo(Prenotazione prenotazione) {
    return prenotazione->veicolo;
}

/**
 * Restituisce il timestamp di inizio della prenotazione.
 * 
 * Pre-condizione: prenotazione != NULL
 * Post-condizione: Ritorna il valore timestamp dell'inizio della prenotazione
 */
time_t prendi_inizio(Prenotazione prenotazione) {
    return prenotazione->inizio;
}

/**
 * Restituisce il timestamp di fine della prenotazione.
 * 
 * Pre-condizione: prenotazione != NULL
 * Post-condizione: Ritorna il valore timestamp della fine della prenotazione
 */
time_t prendi_fine(Prenotazione prenotazione) {
    return prenotazione->fine;
}

/**
 * Restituisce  la targa del veicolo prenotato.
 * 
 * Pre-condizione: prenotazione != NULL
 * Post-condizione: Ritorna una stirnga contente la targa del 
 *                  veicolo prenotato.
 */
char *prendi_targa_veicolo(Prenotazione p){
    return prendi_targa(prendi_veicolo(p));
}



