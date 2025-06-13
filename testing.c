#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veicolo.h"
#include "list.h"
#include "prenotazione.h"
#include <time.h>
#include "utils.h"
#include "utente.h"
#include "noleggio.h"
#include "storico_utente.h"
#include "gestione_file.h"
#include "utili_per_test.h"
#define M 100

/**
 * Funzione: esegui_caso_prova_disponibilita_storico
 * ---
 * Esegue un test per verificare la corretta gestione dello storico e della disponibilità dei veicoli.
 * 
 * Parametri:
 * tc_id: identificativo del test case (utilizzato per costruire i nomi dei file)
 * veicoli: lista dei veicoli disponibili
 * 
 * Pre-condizione:
 * - tc_id != NULL
 * - veicoli è una lista correttamente inizializzata
 * - Esistono i file: <tc_id>_input.txt, <tc_id>_prenotazioni.txt, <tc_id>_oracle_disp.txt, <tc_id>_oracle_stor.txt
 * 
 * Post-condizione:
 * - Carica le prenotazioni e aggiorna lo storico
 * - Verifica la disponibilità per ogni veicolo nel periodo indicato nei file
 * - Confronta i file generati con quelli oracle
 * 
 * Ritorna:
 * 1 se i risultati coincidono con gli oracle, 0 altrimenti
 */
int esegui_caso_prova_disponibilita_storico(char *tc_id, lista veicoli){
	char input_fname[M], input_prenotazioni[M], output_disponibilita[M], output_storico[M], oracle_storico[M], oracle_disponibilita[M];

	strcpy(input_fname,tc_id);
	strcat(input_fname, "_input.txt");
	strcpy(input_prenotazioni,tc_id);
	strcat(input_prenotazioni, "_prenotazioni.txt");
	strcpy(output_disponibilita,tc_id);
	strcat(output_disponibilita, "_output_disponibilita.txt");
	strcpy(output_storico,tc_id);
	strcat(output_storico, "_output_storico.txt");
	strcpy(oracle_disponibilita,tc_id);
	strcat(oracle_disponibilita, "_oracle_disp.txt");
	strcpy(oracle_storico,tc_id);
	strcat(oracle_storico, "_oracle_stor.txt");
	
    lista prenotazioni=carica_prenotazione_file(veicoli, input_prenotazioni, output_storico);
    FILE *fp=fopen(input_fname, "r");
    FILE *f=fopen(output_disponibilita, "w");
    lista temp;
    char targa[8], data_inizio[11], data_fine[11];
    time_t inizio, fine;
    while(fscanf(fp, "%s %s",  data_inizio, data_fine ) == 2){
        inizio=stringa_a_time_t(data_inizio);
        fine=stringa_a_time_t(data_fine);
        temp= veicoli;
        while(!lista_vuota(temp)){
        fprintf(f, "%d\n", controllo_disponibilita_veicolo(ottieni_primo_elemento(temp), prenotazioni, inizio, fine));
        temp=ottieni_coda_lista(temp);
        }
    }
    int risultato_storico, risultato_disponibilita;
    fclose(fp);
    fclose(f);
    while(!lista_vuota(prenotazioni)){
        free(ottieni_primo_elemento(prenotazioni));
        prenotazioni=ottieni_coda_lista(prenotazioni);
    }
    
    risultato_storico=confronta_file(output_storico, oracle_storico);
    if(risultato_storico){
    }
    risultato_disponibilita=confronta_file(output_disponibilita, oracle_disponibilita);
    if(risultato_disponibilita){
    }
    if(risultato_storico && risultato_disponibilita){
        return 1;
    }
    return 0;
}

/**
 * Funzione: esegui_caso_prova_crea_prenotazione
 * ---
 * Esegue un test per verificare la corretta creazione di prenotazioni.
 * 
 * Parametri:
 * tc_id: identificativo del test case (utilizzato per costruire i nomi dei file)
 * veicoli: lista dei veicoli disponibili
 * 
 * Pre-condizione:
 * - tc_id != NULL
 * - veicoli è una lista valida
 * - Esiste il file: <tc_id>_input.txt
 * 
 * Post-condizione:
 * - Crea prenotazioni a partire dai dati del file
 * - Scrive le prenotazioni nel file <tc_id>_output.txt
 * - Verifica la disponibilità dei veicoli e la scrive nel file
 * - Confronta l'output con il file oracle
 * 
 * Ritorna:
 * 1 se l’output coincide con l’oracle, 0 altrimenti
 */
int esegui_caso_prova_crea_prenotazione(char *tc_id, lista veicoli){
	char input_fname[M],output_fname[M], oracle_fname[M];

	strcpy(input_fname,tc_id);
	strcat(input_fname, "_input.txt");
	strcpy(output_fname,tc_id);
	strcat(output_fname, "_output.txt");
	strcpy(oracle_fname,tc_id);
	strcat(oracle_fname, "_oracle.txt");
	
    
    FILE *fp=fopen(input_fname, "r");
    if(fp==NULL){
    }
    
    Veicolo v;
    Prenotazione p;
    lista l=nuova_lista();
    char email[51], targa[20];
    char data_inizio[20], data_fine[20];
    time_t inizio, fine;
    while(fscanf(fp, "%s %s %s %s", email, targa, data_inizio, data_fine) == 4){
        inizio=stringa_a_time_t(data_inizio);
        fine=stringa_a_time_t(data_fine);
        v=trova_veicolo(targa, veicoli);
        p=crea_prenotazione(email, v, inizio, fine);
        l=aggiungi_a_lista(p, l);
    }
    rewind(fp);
    conta_righe_file(fp);
    fclose(fp);
    

    
    aggiorna_file_prenotazioni(l, output_fname);
    
    FILE *f=fopen(output_fname, "a");
    
    lista temp=veicoli;
    while(!lista_vuota(temp)){
        fprintf(fp, "%d\n", verifica_disponibilita(ottieni_primo_elemento(temp)));
        temp=ottieni_coda_lista(temp);
    }
    fclose(f);
    
    azzera_disponibilita(veicoli);
    
    int result=confronta_file(output_fname, oracle_fname);
	return result;
}

/**
 * Funzione: esegui_caso_prova_costo
 * ---
 * Esegue un test per verificare il corretto calcolo del costo di una prenotazione.
 * 
 * Parametri:
 * tc_id: identificativo del test case (utilizzato per costruire i nomi dei file)
 * 
 * Pre-condizione:
 * - tc_id != NULL
 * - Esiste il file: <tc_id>_input.txt contenente righe nel formato:
 *       costo_giornaliero data_inizio data_fine
 * 
 * Post-condizione:
 * - Calcola il prezzo per ciascuna riga del file
 * - Scrive il risultato nel file <tc_id>_output.txt
 * - Confronta l’output con il file <tc_id>_oracle.txt
 * 
 * Ritorna:
 * 1 se l’output coincide con l’oracle, 0 altrimenti
 */

int esegui_caso_prova_costo(char *tc_id){
	char input_fname[M],output_fname[M], oracle_fname[M];

	strcpy(input_fname,tc_id);
	strcat(input_fname, "_input.txt");
	strcpy(output_fname,tc_id);
	strcat(output_fname, "_output.txt");
	strcpy(oracle_fname,tc_id);
	strcat(oracle_fname, "_oracle.txt");
    
    FILE *fp=fopen(input_fname, "r");
    FILE *f=fopen(output_fname, "w");
    float costo, prezzo_finale;
    char data_inizio[11], data_fine[11];
    time_t inizio, fine;
    while(fscanf(fp, "%f %s %s", &costo, data_inizio, data_fine)==3){
        inizio=stringa_a_time_t(data_inizio);
        fine=stringa_a_time_t(data_fine);
        prezzo_finale=calcola_costo(inizio, fine, costo);
        fprintf(f,"%.2f\n", prezzo_finale);
    }
    fclose(fp);
    fclose(f);
    int result=confronta_file(output_fname, oracle_fname);
	return result;
}



int main(int argc, char *argv[])
{
	FILE *test_suite, *result;
	char tc_id[M];
	int n=0, pass;

	if(argc<3)
	{
	printf("Nomi dei file mancanti\n");
	exit(1);
	}

	test_suite=fopen(argv[1], "r");
	result=fopen(argv[2], "w");

	if(test_suite==NULL || result==NULL)
	{
	printf("Errore nell'apertura dei file\n");
	exit(1);
	}
	
	lista v=carica_veicolo_file("veicoli_per_test.txt");

	while(fscanf(test_suite, "%s", tc_id) != EOF)
	{
	    if(n==0){
	        pass= esegui_caso_prova_costo(tc_id);
	    }
	    if(n==1){
	        pass= esegui_caso_prova_crea_prenotazione(tc_id, v);
	    }
	    if(n>=2){
	        pass= esegui_caso_prova_disponibilita_storico(tc_id, v);
	    }
	    n++;

	fprintf(result, "%s ", tc_id);
	if(pass==1)
	fprintf(result, "PASS\n");
	else
	fprintf(result, "FAIL\n");
	}

	fclose(test_suite);
	fclose(result);
}