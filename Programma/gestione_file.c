#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veicolo.h"
#include "list.h"
#include "prenotazione.h"
#include <time.h>
#include "utils.h"
#include "gestione_file.h"
#include "storico_utente.h"

/**
 * Trova e restituisce un veicolo in base alla targa.
 * 
 * 
 * Pre-condizioni:`targa` è una stringa valida e terminata da '\0',
 *                 `veicoli` è una lista valida di elementi 
 *                  di tipo `Veicolo`
 * 
 * Post-condizioni: Ritorna il veicolo corrispondente alla targa se trovato,
 *                  Ritorna NULL se nessun veicolo con quella 
 *                  targa è presente nella lista
*/
Veicolo trova_veicolo(char *targa, lista veicoli){
    Veicolo v;
    while(!lista_vuota(veicoli)){
        v=ottieni_primo_elemento(veicoli);
        if(strcmp(targa, prendi_targa(v))==0){
            return v;
        }
        veicoli=ottieni_coda_lista(veicoli);
    }
    return NULL;
}


/**
 * Carica una lista di veicoli da un file.
 * 
 * Legge i dati dei veicoli da un file di testo con formato:
 * targa;modello;costo_giornaliero;luogo
 * 
 * Pre-condizione: nome_file != NULL, il file deve esistere e avere il formato corretto
 * Post-condizione: Ritorna una lista di veicoli caricati dal file
 */
lista carica_veicolo_file(char *nome_file) {
    FILE *fp = fopen(nome_file, "r");
    if (fp==NULL){
        printf("errore nell' apertura file dei veicli \n");
        return ;
    }

    lista l=nuova_lista();
    char targa[8], modello[31], prezzo[8], luogo[10];
    char c;
    float costo;
    Veicolo v;
    /*legge tutto il file*/
    while((c=fgetc(fp))!=EOF){
        /*legge ogni riga del file separando i vari campi*/
        prendi_stringa_file(targa, c,fp);
        c=fgetc(fp);/*salta il ;*/
        prendi_stringa_file(modello, c, fp);
        c=fgetc(fp);
        prendi_stringa_file(prezzo, c,fp);
        c=fgetc(fp);
        costo=atof(prezzo);
        prendi_stringa_file(luogo, c, fp);
        /*crea il veicolo e lo aggiunge alla lista*/
        v=crea_veicolo(targa, modello, costo, luogo);
        l=aggiungi_a_lista(v, l);
    }
    fclose(fp);
    return l;
}

/**
 * Carica una lista di prenotazioni da un file.
 * 
 * Legge i dati delle prenotazioni da un file di testo con formato:
 * targa mail gg/mm/aaaa gg/mm/aaaa
 * 
 * Pre-condizione: nome_file != NULL, il file deve esistere e avere il formato corretto, tutte le auto prenotati
 *                 devono essere presenti in veicoli, 
 * Post-condizione: Ritorna una lista di prenotazioni caricati dal file
 */
lista carica_prenotazione_file(lista veicoli, char *nome_file) {
    FILE *fp = fopen(nome_file, "r");
    if (fp==NULL){
        printf("errore nell' apertura file prenotazioni \n");
        return ;
    }
    lista temp;
    lista pren=nuova_lista();
    char email[51], targa[9];
    char c;
    int giorno, mese, anno;
    time_t inizio, fine;
    Veicolo v;
    Prenotazione p;
    time_t now = time(NULL);/*prende la data odierna */
    
    while(fscanf(fp, "%s ", targa)==1){
        temp=veicoli;
        /*trova il veicolo corrispondete alla targa nel file prenotaioni*/
        while(strcmp(targa, prendi_targa(ottieni_primo_elemento(temp)))){
            temp=ottieni_coda_lista(temp);
        }
        /*legge da file tutti i campi necessari e crea la prenotazione*/
        v=ottieni_primo_elemento(temp);
        fscanf(fp, "%s ", email);
        fscanf(fp, "%d/%d/%d ", &giorno, &mese, &anno);
        inizio=converti_data(giorno, mese, anno);
        fscanf(fp, "%d/%d/%d\n", &giorno, &mese, &anno);
        fine=converti_data(giorno, mese, anno);
        p=crea_prenotazione(email, v, inizio, fine);
        
        /*se la prenotazione non è piu valida la elimina e la aggiunge allo storico*/
        if(now>prendi_fine(p)){
            aggiorna_storico_utente(email,p);
            free(p);
        }else{
            imposta_disponibilita(v, 0); /*se il veicolo è nella lisat prenotazioni lo imposta la dispobilita a zero*/
            pren=aggiungi_a_lista(p, pren);
        }
    }
    fclose(fp);
    return pren;
}

/**
 * copia una lista di prenorazioni in un file azzerando il contenuto precednete del file
 * 
 * scrive i dati delle prenotazioni da un file di testo con formato:
 * targa mail gg/mm/aaaa gg/mm/aaaa
 * 
 * Pre-condizione: nome_file != NULL 
 */
void aggiorna_file_prenotazioni(lista prenotazioni, char *nome_file){
    FILE *fp = fopen(nome_file, "w");
    if (fp==NULL){
        printf("errore nell' apertura file prenotazioni \n");
        return ;
    }
    char data[11];
    Prenotazione p;
    while(!lista_vuota(prenotazioni)){
        /*copia tutti i campi di ogni prenotazione nel file e libera la memeoria*/
        p=ottieni_primo_elemento(prenotazioni);
        fprintf(fp, "%s %s ", prendi_targa_veicolo(p),prendi_email(p));
        data_in_stringa(prendi_inizio(p), data, sizeof(data));
        fprintf(fp, "%s ", data);
        data_in_stringa(prendi_fine(p), data, sizeof(data));
        fprintf(fp, "%s\n", data);
        free(p);/*libera la memoria */
        prenotazioni=ottieni_coda_lista(prenotazioni);
    }
}