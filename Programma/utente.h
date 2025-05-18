#ifndef AUTH_H
#define AUTH_H

#include <stdio.h>

/* Richiede all'utente di inserire una nuova email e password, dopo aver verificato che non sia già presente.
 Se l'email è presente, chiede se accedere o uscire.*/
void registrati(char *email);

/* Chiede all'utente una email e password.
 Se l'email non esiste, propone di registrarsi o uscire.
 Se esiste, controlla la password con massimo 4 tentativi.*/
void accedi(char *email);

/* Controlla se una email esiste già nel file degli utenti.
 Restituisce 0 se trovata, 1 altrimenti.*/
int trova_email(char *email, FILE *fp);

/* Permette all'utente di scegliere se accedere o registrarsi.
Restituisce un puntatore alla stringa email autenticata.*/
char *accedi_o_registrati();

#endif
