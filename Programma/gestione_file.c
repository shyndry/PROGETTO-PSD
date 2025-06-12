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
 * Funzione: trova_veicolo
 * ---
 * Cerca un veicolo nella lista in base alla targa fornita.
 * 
 * Parametri:
 * targa: stringa contenente la targa da cercare (terminata con '\0')
 * veicoli: lista di veicoli in cui cercare
 * 
 * Pre-condizione:
 * - targa deve essere una stringa valida e terminata da '\0'
 * - veicoli deve essere una lista valida di elementi di tipo Veicolo
 * 
 * Post-condizione:
 * - Se trovato, restituisce il puntatore al veicolo con la targa specificata
 * - Se non trovato, restituisce NULL
 * - La lista originale rimane invariata
 * 
 * Ritorna:
 * Puntatore al veicolo trovato o NULL se non trovato
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
 * Funzione: carica_veicolo_file
 * ---
 * Carica una lista di veicoli da un file di testo con formato specifico.
 * 
 * Formato file:
 * targa;modello;costo_giornaliero;luogo
 * 
 * Parametri:
 * nome_file: percorso del file da cui leggere i dati dei veicoli
 * 
 * Pre-condizione:
 * - nome_file != NULL
 * - Il file deve esistere ed essere leggibile
 * - Il file deve seguire il formato specificato
 * 
 * Post-condizione:
 * - Restituisce una lista contenente tutti i veicoli letti dal file
 * - In caso di errore, restituisce NULL e stampa un messaggio di errore
 * - Il file viene chiuso correttamente
 * 
 * Ritorna:
 * Lista di veicoli caricati dal file o NULL in caso di errore
 */

lista carica_veicolo_file(char *nome_file) {
    FILE *fp = fopen(nome_file, "r");
    if (fp==NULL){
        printf("errore nell' apertura del file dei veicoli \n");
        return NULL;
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
 * Funzione: carica_prenotazione_file
 * ---
 * Carica una lista di prenotazioni da file, verificandone la validità temporale
 * e spostando quelle scadute nello storico.
 * 
 * Formato file:
 * targa mail gg/mm/aaaa gg/mm/aaaa
 * 
 * Parametri:
 * veicoli: lista dei veicoli disponibili (per verifica corrispondenza)
 * nome_file: percorso del file delle prenotazioni attive
 * nome_file_storico: percorso del file dello storico prenotazioni
 * 
 * Pre-condizione:
 * - nome_file != NULL e nome_file_storico != NULL
 * - I file devono esistere ed essere leggibili
 * - Tutti i veicoli prenotati devono essere presenti nella lista veicoli
 * - Il file deve seguire il formato specificato
 * 
 * Post-condizione:
 * - Restituisce una lista contenente solo le prenotazioni ancora valide
 * - Le prenotazioni scadute vengono aggiunte allo storico
 * - I veicoli con prenotazioni attive vengono marcati come non disponibili
 * - In caso di errore, restituisce NULL e stampa un messaggio di errore
 * - I file vengono chiusi correttamente
 * 
 * Ritorna:
 * Lista di prenotazioni valide o NULL in caso di errore
 */

lista carica_prenotazione_file(lista veicoli, char *nome_file, char *nome_file_storico) {
    FILE *fp = fopen(nome_file, "r");
    if (fp==NULL){
        printf("errore nell' apertura file prenotazioni \n");
        return NULL;
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
            aggiorna_storico_utente(email,p, nome_file_storico);
            free(p);
        }else{
            imposta_disponibilita(v, 0); /*se il veicolo è nella lista prenotazioni imposta la disponibilita a zero*/
            pren=aggiungi_a_lista(p, pren);
        }
    }
    fclose(fp);
    return pren;
}

/**
 * Funzione: aggiorna_file_prenotazioni
 * ---
 * Salva l'intera lista di prenotazioni su file, sovrascrivendo il contenuto precedente.
 * 
 * Formato file:
 * targa mail gg/mm/aaaa gg/mm/aaaa
 * 
 * Parametri:
 * prenotazioni: lista delle prenotazioni da salvare
 * nome_file: percorso del file in cui salvare le prenotazioni
 * 
 * Pre-condizione:
 * - nome_file != NULL
 * - Il file deve essere scrivibile
 * 
 * Post-condizione:
 * - Tutte le prenotazioni vengono scritte nel file specificato
 * - La memoria delle prenotazioni viene liberata
 * - In caso di errore, stampa un messaggio di errore
 * - Il file viene chiuso correttamente
 * 
 * Ritorna:
 * Nessun valore di ritorno
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