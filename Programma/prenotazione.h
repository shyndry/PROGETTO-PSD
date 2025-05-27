/**
 * ADT per gestire le prenotazioni dei veicoli.
 *
 * Questo modulo fornisce funzionalità per la creazione, gestione e manipolazione
 * delle prenotazioni di veicoli da parte degli utenti.
 */
#ifndef PRENOTAZIONE_H
#define PRENOTAZIONE_H

#include <time.h>
#include "veicolo.h"
#include "list.h"

/**
 * Tipo di riferimento: Prenotazione.
 * Rappresenta una prenotazione effettuata da un utente per un veicolo
 * in un determinato intervallo temporale.
 */
typedef struct prenotazione *Prenotazione;


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
float calcola_costo(time_t inizio, time_t fine, float costo);

/**
 * Crea una nuova prenotazione per un veicolo.
 *
 * Pre-condizione: email != NULL && strlen(email) > 0, veicolo != NULL, giorni > 0, inzio<=fine
 * Post-condizione: email(p) = email, veicolo(p) = veicolo, inizio(p) = inizio,
 *                 fine(p) = fine, costo_totale(p) = giorni * prendi_costo_giornaliero(veicolo)
 *
 * Ritorna: Una nuova prenotazione inizializzata
 */
Prenotazione crea_prenotazione(char *email, Veicolo veicolo, time_t inzio, time_t fine);

/**
 * Termina una prenotazione esistente.
 *
 * Pre-condizione: prenotazione != NULL, veicolo != NULL
 * Post-condizione: imposta_fine_noleggio(v, fine(p)), imposta_disponibilita(v, 0)
 */
void termina_prenotazione(Prenotazione prenotazione, Veicolo veicolo);

/**
 * visualizza il costo totale di una prenotazione.
 *
 * Pre-condizione: prenotazione != NULL, fine(p) > inizio(p)
 * Post-condizione: costo = costo_totale(p)
 *
 * Ritorna: Il costo totale della prenotazione
 */
float prendi_costo(Prenotazione prenotazione);

/**
 * Stampa i dettagli di una prenotazione.
 *
 * Pre-condizione: prenotazione != NULL
 * Post-condizione: Vengono stampate su output tutte le informazioni della prenotazione
 */
void stampa_prenotazione(Prenotazione prenotazione);

/**
 * Restituisce l'email dell'utente associato alla prenotazione.
 *
 * Pre-condizione: prenotazione != NULL, email(p) != NULL
 * Post-condizione: email = email(p)
 *
 * Ritorna: Puntatore alla stringa email
 */
char *prendi_email(Prenotazione prenotazione);

/**
 * Restituisce il veicolo associato alla prenotazione.
 *
 * Pre-condizione: prenotazione != NULL
 * Post-condizione: veicolo = veicolo(p)
 *
 * Ritorna: Puntatore al veicolo associato
 */
Veicolo prendi_veicolo(Prenotazione prenotazione);

/**
 * Restituisce il timestamp di inizio della prenotazione.
 *
 * Pre-condizione: prenotazione != NULL
 * Post-condizione: inizio = inizio(p)
 *
 * Ritorna: Timestamp di inizio prenotazione
 */
time_t prendi_inizio(Prenotazione prenotazione);

/**
 * Restituisce il timestamp di fine della prenotazione.
 *
 * Pre-condizione: prenotazione != NULL
 * Post-condizione: fine = fine(p)
 *
 * Ritorna: Timestamp di fine prenotazione
 */
time_t prendi_fine(Prenotazione prenotazione);

/**
 * Restituisce  la targa del veicolo prenotato.
 * 
 * Pre-condizione: prenotazione != NULL
 * Post-condizione: Ritorna una stringa contenente la targa del 
 *                  veicolo prenotato.
 */
char *prendi_targa_veicolo(Prenotazione p);


#endif /* PRENOTAZIONE_H */