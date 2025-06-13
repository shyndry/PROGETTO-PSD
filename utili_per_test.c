#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"
#include "veicolo.h"

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

time_t stringa_a_time_t(const char *data_str) {
	struct tm tm_data = {0};
	int giorno, mese, anno;

	// Parsing della stringa con sscanf
	if (sscanf(data_str, "%d/%d/%d", &giorno, &mese, &anno) != 3) {
		printf("Formato data non valido: %s\n", data_str);
		return (time_t)-1;
	}

	// Popolamento della struct tm
	tm_data.tm_mday = giorno;
	tm_data.tm_mon = mese - 1;     // tm_mon va da 0 (gennaio) a 11 (dicembre)
	tm_data.tm_year = anno - 1900; // tm_year C( l'anno dal 1900

	// Conversione in time_t
	return mktime(&tm_data);
}

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

void azzera_disponibilita(lista veicoli) {
	while(!lista_vuota(veicoli)) {
		imposta_disponibilita(ottieni_primo_elemento(veicoli), 1);
		veicoli=ottieni_coda_lista(veicoli);
	}
}

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

int conta_righe_file(FILE *fp) {
	char riga[256];
	int righe=0;

	while (fgets(riga, sizeof(riga), fp)) {
		righe++;
	}
	rewind(fp);
	return righe;
}

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

int confronta_file(char *nome_file1, char *nome_file2) {
	FILE *f1=fopen(nome_file1, "r");
	if(f1==NULL) {
		printf("errore nell' apertura del file 1\n");
		return 0;
	}
	FILE *f2=fopen(nome_file2, "r");
	if(f2==NULL) {
		printf("errore nell' apertura del file 2\n");
		return 0;
	}
	int n_righe1, n_righe2;

	n_righe1=conta_righe_file(f1);
	n_righe2=conta_righe_file(f2);
	if(n_righe1 != n_righe2) {
		fclose(f1);
		fclose(f2);
		return 0;
	}

	char riga1[256], riga2[256];

	while(fgets(riga1, sizeof(riga1), f1)) {
		fgets(riga2, sizeof(riga2), f2);
		if(strcmp(riga1, riga2)) {
			fclose(f1);
			fclose(f2);
			return 0;
		}
	}
	fclose(f1);
	fclose(f2);
	return 1;
}