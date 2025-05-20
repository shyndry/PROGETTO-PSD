/**
 * ADT per gestire l'autenticazione e la registrazione degli utenti.
 * 
 * Questo modulo fornisce funzionalità per la registrazione di nuovi utenti,
 * l'accesso di utenti esistenti e la gestione delle credenziali.
 */
#ifndef AUTH_H
#define AUTH_H

#include <stdio.h>

/**
 * Gestisce la registrazione di un nuovo utente.
 * 
 * Richiede all'utente di inserire una nuova email e password, verificando
 * che l'email non sia già presente nel sistema. Se l'email è già registrata,
 * chiede all'utente se desidera accedere con le credenziali esistenti o uscire.
 * 
 * Pre-condizione: email != NULL
 * Post-condizione: Se la registrazione ha successo, email conterrà l'indirizzo registrato
 *                 e il nuovo utente sarà salvato nel file utenti.txt
 */
void registrati(char *email);

/**
 * Gestisce l'accesso di un utente esistente.
 * 
 * Chiede all'utente di inserire email e password. Se l'email non esiste nel sistema,
 * propone all'utente di registrarsi o uscire. Se l'email esiste, verifica la password
 * concedendo un massimo di 4 tentativi prima di terminare il programma.
 * 
 * Pre-condizione: email != NULL
 * Post-condizione: Se l'accesso ha successo, email conterrà l'indirizzo dell'utente autenticato
 */
void accedi(char *email);

/**
 * Verifica se un'email è già registrata nel sistema.
 * 
 * Cerca l'email specificata nel file degli utenti e restituisce un valore
 * che indica se l'email è stata trovata o meno.
 * 
 * Pre-condizione: email != NULL, fp != NULL e aperto in modalità lettura
 * Post-condizione: Restituisce 0 se l'email è stata trovata, 1 altrimenti
 * 
 * Ritorna: 0 se l'email è presente, 1 se non è presente
 */
int trova_email(char *email, FILE *fp);

/**
 * Gestisce il processo di autenticazione.
 * 
 * Permette all'utente di scegliere se accedere con un account esistente
 * o registrarne uno nuovo. Restituisce l'email dell'utente autenticato.
 * 
 * Pre-condizione: Nessuna
 * Post-condizione: Restituisce un puntatore alla stringa contenente l'email dell'utente autenticato
 * 
 * Ritorna: Puntatore alla stringa email dell'utente autenticato
 */
char *accedi_o_registrati();

#endif /* AUTH_H */
