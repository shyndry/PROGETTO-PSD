#include <stdio.h>
#include <time.h>  
#include <ctype.h>
#include <string.h>
#include "utils.h"

/*
 * Funzione: converti_data
 * -----------------------
 * Converte una data fornita come giorno, mese e anno in un valore di tipo time_t.
 *
 * Parametri:
 *   giorno: intero che rappresenta il giorno
 *   mese: intero che rappresenta il mese (1-12)
 *   anno: intero che rappresenta l’anno (es. 2025)
 *
 * Pre-condizione:
 *   La data deve essere valida (giorno, mese e anno coerenti)
 *
 * Post-condizione:
 *   Restituisce un valore di tipo time_t corrispondente alla data
 *
 * Ritorna:
 *   time_t che rappresenta la data convertita
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

/*
 * Funzione: inserisci_data
 * ------------------------
 * Chiede all’utente di inserire una data da tastiera e la converte in time_t.
 *
 * Parametri:
 *   Nessuno (input interattivo da stdin)
 *
 * Pre-condizione:
 *   Nessuna
 *
 * Post-condizione:
 *   Restituisce la data inserita dall’utente in formato time_t
 *
 * Ritorna:
 *   time_t corrispondente alla data inserita
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

/*
 * Funzione: stampa_data
 * ---------------------
 * Stampa una data in formato leggibile (gg/mm/aaaa) partendo da una variabile time_t.
 *
 * Parametri:
 *   t: variabile di tipo time_t che rappresenta una data
 *
 * Pre-condizione:
 *   Nessuna
 *
 * Post-condizione:
 *   Stampa la data su stdout nel formato gg/mm/aaaa
 *
 * Ritorna:
 *   Nessun valore restituito (void)
 */

void stampa_data(time_t t){
        struct tm *data = localtime(&t);

    printf("%02d/%02d/%04d\n", data->tm_mday, data->tm_mon + 1, data->tm_year + 1900);   
}


/*
 * Funzione: data_in_stringa
 * -------------------------
 * Converte una variabile di tipo time_t in una stringa formattata "gg/mm/aaaa".
 *
 * Parametri:
 *   tempo: valore di tipo time_t da convertire
 *   buffer: puntatore a un buffer di caratteri dove salvare la stringa risultante
 *   size: dimensione del buffer, deve essere almeno 11
 *
 * Pre-condizione:
 *   buffer != NULL, size >= 11
 *
 * Side-effect:
 *   Scrive nel buffer la data in formato "gg/mm/aaaa"
 *
 * Ritorna:
 *   Nessun valore restituito (void)
 */

void data_in_stringa(time_t tempo, char *buffer, size_t size) {
    struct tm *info = localtime(&tempo);
    strftime(buffer, size, "%d/%m/%Y", info);
}

/*
 * Funzione: stringa_maiuscola
 * ---------------------------
 * Converte tutte le lettere di una stringa in maiuscolo.
 *
 * Parametri:
 *   buffer: puntatore a una stringa terminata da '\0'
 *
 * Pre-condizione:
 *   La stringa deve essere correttamente terminata da '\0'
 *
 * Side-effect:
 *   Modifica la stringa convertendo ogni lettera in maiuscola
 *
 * Ritorna:
 *   Nessun valore restituito (void)
 */

void stringa_maiuscola(char *buffer){
    for(int i=0; i<strlen(buffer); i++){
        buffer[i]=toupper(buffer[i]);
    }
}

 
/*
 * Funzione: stringa_minuscola
 * ---------------------------
 * Converte tutte le lettere di una stringa in minuscolo.
 *
 * Parametri:
 *   buffer: puntatore a una stringa terminata da '\0'
 *
 * Pre-condizione:
 *   La stringa deve essere correttamente terminata da '\0'
 *
 * Side-effect:
 *   Modifica la stringa convertendo ogni lettera in minuscola
 *
 * Ritorna:
 *   Nessun valore restituito (void)
 */

void stringa_minuscola(char *buffer){
    for(int i=0; i<strlen(buffer); i++){
        buffer[i]=tolower(buffer[i]);
    }
}

/*
 * Funzione: prendi_stringa_file
 * -----------------------------
 * Legge una stringa da un file fino al carattere ';', '\n' o EOF.
 *
 * Parametri:
 *   buffer: puntatore a una stringa dove salvare il testo letto
 *   c: carattere iniziale già letto dal file (prima lettera della stringa)
 *   fp: puntatore al file da cui leggere
 *
 * Pre-condizione:
 *   buffer ha spazio sufficiente, fp != NULL, c è il primo carattere utile
 *
 * Post-condizione:
 *   La stringa letta viene salvata in buffer (terminata da '\0')
 *
 * Ritorna:
 *   Nessun valore restituito (void)
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
