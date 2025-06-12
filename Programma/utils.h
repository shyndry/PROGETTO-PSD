#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <ctype.h>
#include <string.h>

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
time_t converti_data(int giorno, int mese, int anno);

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
time_t inserisci_data();

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
void stampa_data(time_t t);

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
void data_in_stringa(time_t tempo, char *buffer, size_t size);

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
void stringa_maiuscola(char *buffer);

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
void stringa_minuscola(char *buffer);

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

void prendi_stringa_file(char *buffer, char c, FILE *fp);
#endif // UTILS_H