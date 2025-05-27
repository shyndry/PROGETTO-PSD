#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <ctype.h>
#include <string.h>

/**
 * Converte una data composta da giorno, mese e anno in un tipo time_t.
 *
 *
 * Pre-condizione: data valida (giorno, mese, anno corretti)
 * Post-condizione: ritorna il valore time_t corrispondente alla data
 */
time_t converti_data(int giorno, int mese, int anno);

/**
 * Richiede all'utente di inserire una data da tastiera e la converte in time_t.
 *
 * post-condizoni: restituisce una data inserita dall' utente in time_t
 */ 
time_t inserisci_data();

/**
 * Stampa una data in formato gg/mm/aaaa leggibile da time_t.
 *
 *
 * Output: stampa su stdout (es. 22/05/2025)
 */
void stampa_data(time_t t);

/**
 * converte un time_t in una stringa del tipo 
 * gg/mm/aaaa
 * 
 * Pre-condizione: buffer != NULL, size= dimensione buffer, size>=11
 * side-effect: buffer contiene la data in formato stringa
 * 
 */
void data_in_stringa(time_t tempo, char *buffer, size_t size);

/**
 * coverte tutte le lettere di una stringa in lettere maiuscole
 * 
 * Pre-condizione: buffer deve terminare con '\0'
 * side-effect: tutte le lettere di buffer diventano maiuscole 
 */
void stringa_maiuscola(char *buffer);

/**
 * coverte tutte le lettere di una stringa in lettere minuscole
 * 
 * Pre-condizione: buffer deve terminare con '\0'
 * side-effect: tutte le lettere di buffer diventano minuscole 
 */
void stringa_minuscola(char *buffer);

/**
 * Legge una stringa da un file fino al carattere ';', '\n' o EOF.
 *
 *
 * Pre-condizione: buffer ha spazio sufficiente, fp != NULL, c contiene 
 *                 la prima lettera della stringa da leggere.
 * Post-condizione: buffer contiene la stringa letta
 */
void prendi_stringa_file(char *buffer, char c, FILE *fp);
#endif // UTILS_H