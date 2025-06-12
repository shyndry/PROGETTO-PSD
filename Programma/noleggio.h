#ifndef NOLEGGIO_H
#define NOLEGGIO_H

#include "list.h"
#include "veicolo.h"
#include "prenotazione.h"
#include "utils.h"
#include <time.h>


/**
 * Funzione: controllo_disponibilita_veicolo
 * ---
 * Verifica se un veicolo è disponibile in un determinato intervallo di tempo,
 * controllando che non sia già prenotato in periodi che si sovrappongono.
 * 
 * Parametri:
 * v: veicolo da verificare
 * prenotazioni: lista delle prenotazioni esistenti
 * inizio: timestamp di inizio periodo desiderato
 * fine: timestamp di fine periodo desiderato
 * 
 * Pre-condizione:
 * - prenotazioni != NULL
 * - veicolo != NULL
 * - inizio < fine
 * 
 * Post-condizione:
 * - Restituisce 1 se il veicolo è disponibile nell'intervallo specificato
 * - Restituisce 0 se il veicolo è già prenotato in periodi che si sovrappongono
 * 
 * Ritorna:
 * 1 se disponibile, 0 altrimenti
 */
int controllo_disponibilita_veicolo(Veicolo v, lista prenotazioni, time_t inizio, time_t fine);

/**
 * Funzione: stampa_disponibilita
 * ---
 * Stampa a schermo tutti i veicoli disponibili in un determinato intervallo di tempo,
 * includendo sia i veicoli attualmente disponibili che quelli prenotabili nel periodo specificato.
 * 
 * Parametri:
 * veicoli: lista dei veicoli da controllare
 * prenotazioni: lista delle prenotazioni esistenti
 * inizio: timestamp di inizio periodo desiderato
 * fine: timestamp di fine periodo desiderato
 * 
 * Pre-condizione:
 * - veicoli != NULL
 * - prenotazioni != NULL
 * - inizio < fine
 * 
 * Post-condizione:
 * - Stampa a schermo i veicoli disponibili
 * - Restituisce il numero di veicoli disponibili trovati
 * 
 * Ritorna:
 * Il numero di veicoli disponibili stampati
 */
void stampa_disponibilita(lista veicoli, lista prenotazioni, time_t inizio, time_t fine);

/**
 * Funzione: prenota_veicolo
 * ---
 * Gestisce il processo completo di prenotazione di un veicolo, includendo:
 * - Inserimento delle date
 * - Verifica disponibilità
 * - Selezione veicolo
 * - Conferma finale
 * 
 * Parametri:
 * email: email dell'utente che effettua la prenotazione
 * veicoli: lista dei veicoli disponibili
 * prenotazioni: lista delle prenotazioni esistenti
 * 
 * Pre-condizione:
 * - email != NULL
 * - veicoli != NULL
 * 
 * Post-condizione:
 * - Se la prenotazione ha successo, restituisce la lista aggiornata con la nuova prenotazione
 * - Se la prenotazione fallisce, restituisce la lista invariata
 * - Gestisce interamente il dialogo con l'utente tramite stdin/stdout
 * 
 * Ritorna:
 * La lista delle prenotazioni (aggiornata o invariata)
 */
lista prenota_veicolo(char *email, lista veicoli, lista prenotazioni);

/**
 * Funzione: stampa_prenotazioni_utente
 * ---
 * Stampa tutte le prenotazioni attive associate a un particolare utente.
 * 
 * Parametri:
 * email: email dell'utente di cui visualizzare le prenotazioni
 * p: lista delle prenotazioni da controllare
 * 
 * Pre-condizione:
 * - email != NULL
 * 
 * Post-condizione:
 * - Stampa a schermo tutte le prenotazioni associate all'email
 * - Se non ci sono prenotazioni, stampa un messaggio informativo
 * 
 * Ritorna:
 * Nessun valore di ritorno
 */
void stampa_prenotazioni_utente(char *email, lista p);
#endif // NOLEGGIO_H