/**
 * ADT per gestire l'autenticazione e la registrazione degli utenti.
 * 
 * Questo modulo fornisce funzionalità per la registrazione di nuovi utenti,
 * l'accesso di utenti esistenti e la gestione delle credenziali.
 */
#ifndef AUTH_H
#define AUTH_H

#include <stdio.h>
#include"utils.h"
/*
 * Funzione: trova_email
 * ---------------------
 * Verifica se una determinata email è già presente nel file degli utenti.
 *
 * Parametri:
 *   email: puntatore a una stringa che conterrà l'email da cercare
 *   fp: puntatore a FILE aperto in lettura, contenente gli utenti registrati
 *
 * Pre-condizione:
 *   email != NULL, fp != NULL e aperto in modalità lettura
 *
 * Post-condizione:
 *   Restituisce 0 se l’email è presente nel file, 1 altrimenti
 *
 * Ritorna:
 *   Intero (0 o 1) che indica se l'email è già registrata o meno
 */

void registrati(char *email);

/*
 * Funzione: accedi
 * ----------------
 * Gestisce l'autenticazione di un utente esistente, chiedendo email e password.
 *
 * Parametri:
 *   email: puntatore a una stringa dove sarà salvata l’email dell’utente autenticato
 *
 * Pre-condizione:
 *   email != NULL
 *
 * Post-condizione:
 *   Se l’autenticazione ha successo, email conterrà l’email dell’utente
 *
 * Ritorna:
 *   Nessun valore restituito (void); stampa a video l'esito dell'accesso
 */
void accedi(char *email);

/*
 * Funzione: registrati
 * --------------------
 * Registra un nuovo utente richiedendo email e password, dopo aver verificato che l’email non sia già esistente.
 *
 * Parametri:
 *   email: puntatore a una stringa dove sarà salvata l’email del nuovo utente
 *
 * Pre-condizione:
 *   email != NULL
 *
 * Post-condizione:
 *   Se la registrazione ha successo, l’email viene memorizzata nel file e in 'email'
 *
 * Ritorna:
 *   Nessun valore restituito (void); stampa a video l’esito della registrazione
 */
int trova_email(char *email, FILE *fp);

/*
 * Funzione: accedi_o_registrati
 * -----------------------------
 * Consente all’utente di scegliere se accedere a un account esistente o registrare un nuovo account.
 *
 * Parametri:
 *   Nessuno
 *
 * Pre-condizione:
 *   Nessuna
 *
 * Post-condizione:
 *   Restituisce un puntatore alla stringa contenente l’email dell’utente autenticato
 *
 * Ritorna:
 *   Puntatore a char (stringa) contenente l’email dell’utente loggato o registrato
 */
char *accedi_o_registrati();

#endif /* AUTH_H */
