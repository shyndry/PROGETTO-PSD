#ifndef STORICO_H
#define STORICO_H

#include <stdio.h>
#include "prenotazione.h"


/**
 * Funzione: crea_utente_storico
 * ---
 * Crea una nuova sezione storico per un utente nel file specificato.
 * 
 * fotmato file:
 * #email
 * targa gg/mm/aaaa gg/mm/aaaa costo
 * 
 * 
 * alla fine di ogni storico ci devono essere due righe vuote
 * 
 * Parametri:
 * email: email dell'utente da aggiungere (stringa terminata con '\0')
 * fname: percorso del file storico da modificare
 * 
 * Pre-condizione:
 * - email != NULL e correttamente terminata
 * - fname deve essere un percorso valido
 * - Il file deve essere scrivibile
 * 
 * Post-condizione:
 * - Aggiunge una nuova sezione per l'utente nel formato "#email\n\n"
 * - Il file viene chiuso correttamente
 * 
 * Side-effect:
 * Modifica il file aggiungendo una nuova sezione utente
 */
void crea_utente_storico(char *email, char *fname);

/**
 * Funzione: cerca_mail
 * ---
 * Cerca la posizione di un utente nel file storico.
 * 
 * fotmato file:
 * #email
 * targa gg/mm/aaaa gg/mm/aaaa costo
 * 
 * 
 * alla fine di ogni storico ci devono essere due righe vuote
 * 
 * Parametri:
 * email: email dell'utente da cercare
 * fp: puntatore a file già aperto in lettura
 * fname: percorso del file (per eventuale riapertura)
 * 
 * Pre-condizione:
 * - email != NULL e correttamente terminata
 * - fp != NULL e puntatore a file aperto in lettura
 * - fname != NULL e percorso valido
 * 
 * Post-condizione:
 * - Restituisce il numero di righe fino alla sezione dell'utente
 * - Se non trovato, crea la sezione e si richiama ricorsivamente
 * - Il file rimane aperto per ulteriori operazioni
 * 
 * Ritorna:
 * Numero di righe fino alla sezione utente (0-based)
 */
int trova_mail(char *email, FILE *fp, char *fname);

/**
 * Funzione: conta_righe
 * ---
 * Conta le righe fino alla fine della sezione storico di un utente.
 * 
 * fotmato file:
 * #email
 * targa gg/mm/aaaa gg/mm/aaaa costo
 * 
 * 
 * alla fine di ogni storico ci devono essere due righe vuote
 * 
 * Parametri:
 * email: email dell'utente da cercare
 * fp: puntatore a file già aperto in lettura
 * fname: percorso del file (per eventuale riapertura)
 * 
 * Pre-condizione:
 * - email != NULL e correttamente terminata
 * - fp != NULL e puntatore a file aperto in lettura
 * - fname != NULL e percorso valido
 * 
 * Post-condizione:
 * - Restituisce il numero totale di righe fino alla fine della sezione utente
 * - La sezione utente è delimitata da una riga vuota
 * 
 * Ritorna:
 * Numero totale di righe fino alla fine della sezione utente
 */
int conta_righe(char *email, FILE *fp, char *fanme);

/**
 * Funzione: stampa_storico
 * ---
 * Visualizza lo storico prenotazioni di un utente.
 *
 * fotmato file:
 * #email
 * targa gg/mm/aaaa gg/mm/aaaa costo
 * 
 * 
 * alla fine di ogni storico ci devono essere due righe vuote
 * 
 * Parametri:
 * email: email dell'utente di cui visualizzare lo storico
 * fname: percorso del file storico
 * 
 * Pre-condizione:
 * - email != NULL e correttamente terminata
 * - fname != NULL e percorso valido
 * - Il file deve esistere ed essere leggibile
 * 
 * Post-condizione:
 * - Stampa a schermo tutte le prenotazioni dell'utente
 * - Le prenotazioni sono delimitate da una riga vuota
 * - Il file viene chiuso correttamente
 * 
 * Output:
 * Stampa lo storico utente formattato a schermo
 */
void stampa_storico(char *email, char *fname);

/**
 * Funzione: aggiorna_storico_utente
 * ---
 * Aggiunge una nuova prenotazione allo storico utente.
 * 
 * fotmato file:
 * #email
 * targa gg/mm/aaaa gg/mm/aaaa costo
 * 
 * 
 * alla fine di ogni storico ci devono essere due righe vuote
 * 
 * Parametri:
 * email: email dell'utente da aggiornare
 * p: prenotazione da aggiungere allo storico
 * fname: percorso del file storico
 * 
 * Pre-condizione:
 * - email != NULL e correttamente terminata
 * - p != NULL e prenotazione valida
 * - fname != NULL e percorso valido
 * 
 * Post-condizione:
 * - Aggiunge la prenotazione alla sezione utente
 * - Mantiene l'integrità del resto del file
 * - Utilizza un file temporaneo per l'aggiornamento
 * - I file vengono chiusi correttamente
 * 
 * Side-effect:
 * Modifica il file storico aggiungendo una nuova prenotazione
 */
void aggiorna_storico_utente(char *email, Prenotazione p, char *fname);

#endif // STORICO_H