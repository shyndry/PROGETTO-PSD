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
float calcola_costo(time_t inizio, time_t fine, float costo);

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
Prenotazione crea_prenotazione(char *email, Veicolo veicolo, time_t inzio, time_t fine);

/**
 * Termina una prenotazione esistente.
 *
 * Pre-condizione: prenotazione != NULL, veicolo != NULL
 * Post-condizione: imposta_fine_noleggio(v, fine(p)), imposta_disponibilita(v, 0)
 */
void termina_prenotazione(Prenotazione prenotazione, Veicolo veicolo);

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
float prendi_costo(Prenotazione prenotazione);

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
void stampa_prenotazione(Prenotazione prenotazione);

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
char *prendi_email(Prenotazione prenotazione);

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

Veicolo prendi_veicolo(Prenotazione prenotazione);

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
time_t prendi_inizio(Prenotazione prenotazione);

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
time_t prendi_fine(Prenotazione prenotazione);


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
char *prendi_targa_veicolo(Prenotazione p);


#endif /* PRENOTAZIONE_H */