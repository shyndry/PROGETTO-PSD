#ifndef STORICO_H
#define STORICO_H

#include <stdio.h>
#include "prenotazione.h"

void crea_utente_storico(char *email);
int trova_mail(char *email, FILE *fp);
int conta_righe(char *email, FILE *fp);
void stampa_storico(char *email);
void aggiorna_storico_utente(char *email, Prenotazione p);

#endif // STORICO_H