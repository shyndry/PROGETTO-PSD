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
    
    prenotazione->costo_totale = calcola_costo(inizio, fine, infoCostoGiornaliero(veicolo));

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
    strftime(inizio_str, sizeof(inizio_str), "%d/%m/%Y %H:%M", tm_info);
    
    tm_info = localtime(&prenotazione->fine);
    strftime(fine_str, sizeof(fine_str), "%d/%m/%Y %H:%M", tm_info);
    
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

char *prendi_targa_veicolo(Prenotazione p){
    return prendi_targa(prendi_veicolo(p));
}

/**
 * Salva i dettagli di una prenotazione nel file storico.
 * 
 * Pre-condizione: prenotazione != NULL, il file storico deve essere accessibile
 * Post-condizione: La prenotazione viene aggiunta al file di storico
 */
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
            prendi_costo(prenotazione));

    fclose(file);
}

/**
 * Termina una prenotazione esistente.
 * 
 * Verifica se la prenotazione è scaduta e, in tal caso,
 * rende nuovamente disponibile il veicolo e salva i dati nello storico.
 * 
 * Pre-condizione: prenotazione != NULL, veicolo != NULL
 * Post-condizione: Se scaduta, il veicolo viene reso disponibile
 */
void termina_prenotazione(Prenotazione prenotazione, Veicolo veicolo) {
    time_t ora_corrente;
    time(&ora_corrente);
    
    /* Controlla se la prenotazione è terminata */
    if (ora_corrente >= prenotazione->fine) {
        /* Rende nuovamente disponibile il veicolo */
        imposta_disponibilita(veicolo, 1);
        imposta_fine_noleggio(veicolo, 0);
        
        /* Registra la prenotazione completata nello storico */
        salva_storico(prenotazione);
    }
}

/**
 * Verifica la disponibilità di un veicolo in un determinato intervallo di tempo.
 * 
 * Controlla se il veicolo è disponibile e se non ci sono altre prenotazioni
 * che si sovrappongono all'intervallo richiesto.
 * 
 * Pre-condizione: lista != NULL, veicolo != NULL, inizio < fine
 * Post-condizione: Ritorna 1 se il veicolo è disponibile nel periodo specificato, 0 altrimenti
 */
int verifica_disponibilita(ListaPrenotazioni lista, Veicolo veicolo, time_t inizio, time_t fine) {
    /* Controlla prima se il veicolo è disponibile in generale */
    if (!verifica_disponibilita(veicolo)) {
        /* Se il veicolo non è disponibile, verifica se la fine del noleggio corrente
           è prima dell'inizio del nuovo intervallo richiesto */
        if (prendi_fine_noleggio(veicolo) <= inizio) {
            /* Il veicolo sarà disponibile per il periodo richiesto */
        } else {
            /* Il veicolo non sarà disponibile per il periodo richiesto */
            return 0;
        }
    }
    
    /* Scorre la lista di prenotazioni per verificare sovrapposizioni */
    while (lista != NULL) {
        Prenotazione p = lista->prenotazione;
        Veicolo v = prendi_veicolo(p);
        
        /* Confronta il veicolo con quello della prenotazione corrente */
        if (strcmp(prendi_targa(veicolo), prendi_targa(v)) == 0) {
            /* Controlla se c'è sovrapposizione temporale */
            if ((inizio >= prendi_inizio(p) && inizio < prendi_fine(p)) || 
                (fine > prendi_inizio(p) && fine <= prendi_fine(p)) || 
                (inizio <= prendi_inizio(p) && fine >= prendi_fine(p))) {
                /* C'è sovrapposizione, il veicolo non è disponibile */
                return 0;
            }
        }
        
        lista = lista->prossimo;
    }
    
    /* Se arriviamo qui, il veicolo è disponibile nell'intervallo richiesto */
    return 1;
}
