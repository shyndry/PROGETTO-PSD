#ifndef UTIL_H
#define UTIL_H

#include <time.h>
#include <stdio.h>

/*  
* Funzione: stringa_a_time_t  
* ---  
* Converte una stringa rappresentante una data nel formato "GG/MM/AAAA" in un valore time_t.  
*  
* Parametri:  
* data_str: stringa contenente la data da convertire  
*  
* Pre-condizione:  
* data_str deve essere una stringa non NULL nel formato "GG/MM/AAAA" con valori validi per giorno, mese e anno  
*  
* Post-condizione:  
* Se il parsing ha successo, restituisce il valore time_t corrispondente alla data  
* Se il parsing fallisce, restituisce (time_t)-1 e stampa un messaggio di errore  
*  
* Ritorna:  
* Il valore time_t corrispondente alla data o (time_t)-1 in caso di errore  
*/  
time_t stringa_a_time_t(const char *data_str);

/*  
* Funzione: azzera_disponibilita  
* ---  
* Imposta a 1 il campo disponibilità di tutti i veicoli in una lista.  
*  
* Parametri:  
* veicoli: lista di veicoli da modificare  
*  
* Pre-condizione:  
* veicoli deve essere una lista valida (può essere vuota)  
*  
* Post-condizione:  
* Tutti i veicoli nella lista avranno disponibilità impostata a 1  
* La lista rimane invariata nella sua struttura  
*  
* Ritorna:  
* Nessun valore di ritorno  
*/  
void azzera_disponibilita(lista veicoli);

/*  
* Funzione: conta_righe_file  
* ---  
* Conta il numero di righe presenti in un file.  
*  
* Parametri:  
* fp: puntatore al file già aperto  
*  
* Pre-condizione:  
* fp deve essere un puntatore a file valido e già aperto in lettura  
*  
* Post-condizione:  
* Il puntatore del file viene riportato all'inizio (rewind)  
*  
* Ritorna:  
* Il numero di righe nel file  
*/
int conta_righe_file(FILE *fp);

/*  
* Funzione: confronta_file  
* ---  
* Confronta il contenuto di due file testo riga per riga.  
*  
* Parametri:  
* nome_file1: percorso del primo file da confrontare  
* nome_file2: percorso del secondo file da confrontare  
*  
* Pre-condizione:  
* Entrambi i file devono esistere e essere leggibili  
*  
* Post-condizione:  
* I file vengono chiusi dopo il confronto  
*  
* Ritorna:  
* 1 se i file sono identici, 0 altrimenti  
* In caso di errori di apertura dei file, restituisce 0 e stampa un messaggio di errore  
*/ 
int confronta_file(char *nome_file1, char *nome_file2);

#endif // UTIL_H