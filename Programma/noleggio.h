#ifndef NOLEGGIO_H
#define NOLEGGIO_H

#include "list.h"
#include "veicolo.h"
#include "prenotazione.h"
#include "utils.h"
#include <time.h>


/**
 * Verifica la disponibilità di un veicolo in un determinato intervallo di tempo.
 * 
 * 
 * Pre-condizione: prenotazioni != NULL, veicolo != NULL, inizio < fine
 * Post-condizione: Ritorna 1 se il veicolo è disponibile nel periodo specificato, 0 altrimenti
 */
int controllo_disponibilita_veicolo(Veicolo v, lista prenotazioni, time_t inizio, time_t fine);

/**
 * stampa i veicoli disponibili in uno specifico intervallo di tempo .
 * 
 * 
 * Pre-condizione: veicoli != NULL, prenotazioni != NULL, inizio < fine
 * output: stampa tutti i veicoli disponibili nell' intervallo di tempo passato come 
 *         argomento
 */
void stampa_disponibilita(lista veicoli, lista prenotazioni, time_t inizio, time_t fine);

/**
 * se la prenotazione va a buon fine restituisce la lista delle prenotazioni 
 * con aggiunta la nuova prenotazione
 * 
 * pre-condizioni: email != NULL, veicoli != NULL
 * post_condizioni: se l' intervallo di tempo o la targa non sono validi restituisce 
 *                  la lista non aggiornata, se tutti i campi sono inseriti correttamente 
 *                  restituisce la lista delle prenotazioni con aggiunta la nuova prentazione
 * 
 */
lista prenota_veicolo(char *email, lista veicoli, lista prenotazioni);

/**
 * stampa tutte le prenotazioni effettuate dall' utente che sono ancora in corso
 * 
 * pre-condizioni: email != NULL
 * output: stampa le prenotazioni dell' utente a schermo, se l' utente non 
 *         ha effettuato prenotazioni viene stampato a schermo un messaggio 
 *         di avvertenza.
 */
void stampa_prenotazioni_utente(char *email, lista p);
#endif // NOLEGGIO_H