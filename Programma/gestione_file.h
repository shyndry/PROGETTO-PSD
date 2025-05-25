#ifndef GESTIONE_FILE_H
#define GESTIONE_FILE_H

#include "list.h"
#include "veicolo.h"
#include "prenotazione.h"
#include "utils.h"
#include "storico_utente.h"

/**
 * Cerca un veicolo nella lista tramite la targa.
 * 
 * @param targa La targa del veicolo da cercare.
 * @param veicoli La lista dei veicoli.
 * @return Il veicolo trovato oppure NULL se non esiste.
 */
Veicolo trova_veicolo(char *targa, lista veicoli);

/**
 * Carica una lista di veicoli da un file.
 * 
 * Pre-condizione: nome_file != NULL, il file deve esistere e avere il formato corretto
 * Post-condizione: Ritorna una lista di veicoli caricati dal file
 * 
 * Ritorna: Una lista di veicoli caricati dal file
 */
lista carica_veicolo_file(char *nome_file);

/**
 * Carica una lista di veicoli da un file.
 * 
 * Legge i dati delle prenotazioni da un file di testo con formato:
 * targa mail gg/mm/aaaa gg/mm/aaaa
 * 
 * Pre-condizione: nome_file != NULL, il file deve esistere e avere il formato corretto, tutte le auto prenotati
 *                 devono essere presenti in veicoli, 
 * Post-condizione: Ritorna una lista di prenotazioni caricati dal file
 * 
 * Ritorna: Una lista di prenotazioni caricate dal file
 */
lista carica_prenotazione_file(lista veicoli,char *nome_file);

/**
 * copia una lista di prenorazioni in un file
 * 
 * scrive i dati delle prenotazioni da un file di testo con formato:
 * targa mail gg/mm/aaaa gg/mm/aaaa
 * 
 * Pre-condizione: nome_file != NULL 
 */
void aggiorna_file_prenotazioni(lista prenotazioni, char *nome_file);

#endif
