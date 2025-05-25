#include <stdio.h>
#include <time.h>  
#include <ctype.h>
#include <string.h>
#include "utils.h"

/**
 * Converte una data composta da giorno, mese e anno in un tipo time_t.
 *
 *
 * Pre-condizione: data valida (giorno, mese, anno corretti)
 * Post-condizione: ritorna il valore time_t corrispondente alla data
 */
time_t converti_data(int giorno, int mese, int anno){
    struct tm data = {0};

    // Assegna i valori alla struct tm
    data.tm_mday = giorno;
    data.tm_mon = mese - 1;         // mese va da 0 a 11
    data.tm_year = anno - 1900;     // anno rispetto al 1900
    data.tm_hour = 0;
    data.tm_min = 0;
    data.tm_sec = 0;

    // Converte in time_t
    time_t tempo = mktime(&data);
    
    return tempo;
    }

/**
 * Richiede all'utente di inserire una data da tastiera e la converte in time_t.
 *
 * restituisce una data inserita dall' utente in time_t
 */    
time_t inserisci_data(){
    int giorno, mese, anno;
    time_t data;
    printf("-giorno: ");
    scanf("%d", &giorno);
    printf("-mese: ");
    scanf("%d", &mese);
    printf("-anno: ");
    scanf("%d", &anno);
    return data=converti_data(giorno, mese, anno);
}

/**
 * Stampa una data in formato gg/mm/aaaa leggibile da time_t.
 *
 *
 * Output: stampa su stdout (es. 22/05/2025)
 */
void stampa_data(time_t t){
        struct tm *data = localtime(&t);

    printf("%02d/%02d/%04d\n", data->tm_mday, data->tm_mon + 1, data->tm_year + 1900);   
}


/**
 * converte un time_t in una stringa del tipo 
 * gg/mm/aaaa
 * 
 * Pre-condizione: buffer != NULL, size= dimesione buffer, size>=11
 * side-effect: buffer contiene la data in formato stringao
 * 
 */
void data_in_stringa(time_t tempo, char *buffer, size_t size) {
    struct tm *info = localtime(&tempo);
    strftime(buffer, size, "%d/%m/%Y", info);
}

/**
 * coverte tutte le lettere di una stringa in lettere maiuscole
 * 
 * Pre-condizione: buffer deve terminare con \0
 * side-effect: tutte le lettere di buffer duventano maiuscole 
 */
void stringa_maiuscola(char *buffer){
    for(int i=0; i<strlen(buffer); i++){
        buffer[i]=toupper(buffer[i]);
    }
}

/**
 * coverte tutte le lettere di una stringa in lettere minuscile
 * 
 * Pre-condizione: buffer deve terminare con \0
 * side-effect: tutte le lettere di buffer duventano minuscole 
 */
void stringa_minuscola(char *buffer){
    for(int i=0; i<strlen(buffer); i++){
        buffer[i]=tolower(buffer[i]);
    }
}

/**
 * Legge una stringa da un file fino al carattere ';', '\n' o EOF.
 *
 *
 * Pre-condizione: buffer ha spazio sufficiente, fp != NULL, c contiene 
 *                 la prima lettera della stringa da leggere.
 * Post-condizione: buffer contiene la stringa letta
 */
void prendi_stringa_file(char *buffer, char c, FILE *fp) {
    int i = 0;
    /*legge dal file finche non incotra un ; o un /n*/
    while (c != ';' && c != '\n' && c != EOF) {
        buffer[i++] = c;
        c = fgetc(fp);/*legge la lettera successiva*/
    }
    buffer[i] = '\0';/*aggiunge il terminaotre alla stringa*/
}
