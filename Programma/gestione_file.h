#ifndef GESTIONE_FILE_H
#define GESTIONE_FILE_H

#include "list.h"
#include "veicolo.h"
#include "prenotazione.h"
#include "utils.h"
#include "storico_utente.h"

/**
 * Funzione: trova_veicolo
 * ---
 * Cerca un veicolo nella lista in base alla targa fornita.
 * 
 * Parametri:
 * targa: stringa contenente la targa da cercare (terminata con '\0')
 * veicoli: lista di veicoli in cui cercare
 * 
 * Pre-condizione:
 * - targa deve essere una stringa valida e terminata da '\0'
 * - veicoli deve essere una lista valida di elementi di tipo Veicolo
 * 
 * Post-condizione:
 * - Se trovato, restituisce il puntatore al veicolo con la targa specificata
 * - Se non trovato, restituisce NULL
 * - La lista originale rimane invariata
 * 
 * Ritorna:
 * Puntatore al veicolo trovato o NULL se non trovato
 */
Veicolo trova_veicolo(char *targa, lista veicoli);

/**
 * Funzione: carica_veicolo_file
 * ---
 * Carica una lista di veicoli da un file di testo con formato specifico.
 * 
 * Formato file:
 * targa;modello;costo_giornaliero;luogo
 * 
 * Parametri:
 * nome_file: percorso del file da cui leggere i dati dei veicoli
 * 
 * Pre-condizione:
 * - nome_file != NULL
 * - Il file deve esistere ed essere leggibile
 * - Il file deve seguire il formato specificato
 * 
 * Post-condizione:
 * - Restituisce una lista contenente tutti i veicoli letti dal file
 * - In caso di errore, restituisce NULL e stampa un messaggio di errore
 * - Il file viene chiuso correttamente
 * 
 * Ritorna:
 * Lista di veicoli caricati dal file o NULL in caso di errore
 */
lista carica_veicolo_file(char *nome_file);

/**
 * Funzione: carica_prenotazione_file
 * ---
 * Carica una lista di prenotazioni da file, verificandone la validità temporale
 * e spostando quelle scadute nello storico.
 * 
 * Formato file:
 * targa mail gg/mm/aaaa gg/mm/aaaa
 * 
 * Parametri:
 * veicoli: lista dei veicoli disponibili (per verifica corrispondenza)
 * nome_file: percorso del file delle prenotazioni attive
 * nome_file_storico: percorso del file dello storico prenotazioni
 * 
 * Pre-condizione:
 * - nome_file != NULL e nome_file_storico != NULL
 * - I file devono esistere ed essere leggibili
 * - Tutti i veicoli prenotati devono essere presenti nella lista veicoli
 * - Il file deve seguire il formato specificato
 * 
 * Post-condizione:
 * - Restituisce una lista contenente solo le prenotazioni ancora valide
 * - Le prenotazioni scadute vengono aggiunte allo storico
 * - I veicoli con prenotazioni attive vengono marcati come non disponibili
 * - In caso di errore, restituisce NULL e stampa un messaggio di errore
 * - I file vengono chiusi correttamente
 * 
 * Ritorna:
 * Lista di prenotazioni valide o NULL in caso di errore
 */

lista carica_prenotazione_file(lista veicoli,char *nome_file, char *nome_file_storico);

/**
 * Funzione: aggiorna_file_prenotazioni
 * ---
 * Salva l'intera lista di prenotazioni su file, sovrascrivendo il contenuto precedente.
 * 
 * Formato file:
 * targa mail gg/mm/aaaa gg/mm/aaaa
 * 
 * Parametri:
 * prenotazioni: lista delle prenotazioni da salvare
 * nome_file: percorso del file in cui salvare le prenotazioni
 * 
 * Pre-condizione:
 * - nome_file != NULL
 * - Il file deve essere scrivibile
 * 
 * Post-condizione:
 * - Tutte le prenotazioni vengono scritte nel file specificato
 * - La memoria delle prenotazioni viene liberata
 * - In caso di errore, stampa un messaggio di errore
 * - Il file viene chiuso correttamente
 * 
 * Ritorna:
 * Nessun valore di ritorno
 */
void aggiorna_file_prenotazioni(lista prenotazioni, char *nome_file);

#endif
