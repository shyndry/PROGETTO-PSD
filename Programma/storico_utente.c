#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazione.h"
#include "veicolo.h"
#include "list.h"
#include "utils.h"
#include <time.h>
#include "utente.h"




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
void crea_utente_storico(char *email, char *fname){
    FILE *fp=fopen(fname, "a");
    if(fp==NULL){
        printf("errore nell' apertura dei file utenti\n");
        return;
    }
    fprintf(fp, "\n#%s\n\n", email);
    fclose(fp);
}

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
int cerca_mail(char *email, FILE *fp, char *fname){
    char c;
    int flag, j=0, cont=0;
    char buffer[51];
    while((c=fgetc(fp)) != EOF) /*legge la mail riga per riga e quando trova 
    il simbolo # copia la mail e verifica se è uguale a qualla passata per argomento*/
    {
        if(c=='#'){
            j=0;
            while((c=fgetc(fp)) != EOF && c != '\n'){
                buffer[j++]=c;
            }
            buffer[j]='\0';
        }
        if(c=='\n'){
            cont++;
        }
        if(strcmp(email,buffer)==0){
            return cont;
        }
    }
    /*se non trova la mail la funzione crea nel file lo spazio 
    per la mail e la funzione si richiama in modo ricorsivo*/
    fclose(fp); 
    crea_utente_storico(email, fname); 
    fp=fopen(fname, "r+");
    if(fp==NULL){
        printf("errore nell' apertura dei file utenti\n");
        return -1;
    }
    return cerca_mail(email, fp, fname);
}


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
int conta_righe(char *email, FILE *fp,  char *fname){
    int count=0;
    count=cerca_mail(email, fp, fname);
    char riga[251];
    while (fgets(riga, sizeof(riga), fp)) /*dopo aver contato le righe fino alla mail conta le righe restanti 
    per arrivare alla fine dello storico*/
    {
        riga[strcspn(riga, "\n")] = '\0';
        if (strlen(riga) == 0) {
            return count;
        }
        count++;
    }
}

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
void stampa_storico(char *email, char *fname){
    printf("il tuo storico è :\n");
    FILE *fp=fopen(fname, "r");
    if(fp==NULL){
        printf("errore nell' apertura dello sotorico\n");
        return ;
    }
    cerca_mail(email, fp, fname);
    char riga[256];
    while (fgets(riga, sizeof(riga), fp)) //stampa fino a quando non trova un rigo vuoto
    {
        riga[strcspn(riga, "\n")] = '\0';
        if (strlen(riga) == 0) {
            break;
        }
        printf("%s\n", riga);
    }
    fclose(fp);
}

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
void aggiorna_storico_utente(char *email ,Prenotazione p, char *fname){
    int cont=0;
    FILE *fp=fopen(fname, "r+");
    if(fp==NULL){
        printf("errore nell' apertura dello sotorico\n");
        return ;
    }
    FILE *temp=fopen("file_temp.txt", "w+");
    if(temp==NULL){
        printf("errore nel file temporaneo\n");
        return ;
    }
    char riga[251];
    char data[11];
    
    cont=conta_righe(email, fp, fname);//legge il file fino alla fine dello storico dell' utente desiderato
    
    // aggiunge la nuova prenazione nello storico dell' utente 
    fprintf(temp, "%s ",  prendi_targa_veicolo(p));
    data_in_stringa(prendi_inizio(p), data, sizeof(data));
    fprintf(temp, "%s ", data);
    data_in_stringa(prendi_fine(p), data, sizeof(data));
    fprintf(temp, "%s %f\n\n", data, prendi_costo(p));
    

    while (fgets(riga, sizeof(riga), fp))/*stampa nel file temporaneo la nuova prenotazione 
    e  la parte restante del file storico_utenti */
    {
        riga[strcspn(riga, "\n")] = '\0';
        fprintf(temp, "%s\n",  riga);
    }    
    
    rewind(fp);
    rewind(temp);
    //aggiorna il file utente storico 
    for(int i=0; i<cont; i++){
        fgets(riga, sizeof(riga), fp);
    }
    while(fgets(riga, sizeof(riga), temp)){
        fprintf(fp, "%s",  riga);
    }
    fclose(fp);
    fclose(temp);
}