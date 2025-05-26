/**
 * ADT per la gestione dei veicoli nel sistema di noleggio.
 * 
 * Questo modulo implementa le funzionalità necessarie per creare e gestire
 * i veicoli disponibili per il noleggio, inclusa la gestione della loro
 * disponibilità e la visualizzazione delle loro informazioni.
 */
#ifndef VEICOLO_H
#define VEICOLO_H
#define NULLITEM 0

#include <time.h>


/**
 * Tipo di riferimento: Veicolo.
 * Rappresenta un singolo veicolo nel sistema di noleggio.
 */
typedef struct veicolo *Veicolo;

/**
 * Crea un nuovo veicolo con i parametri specificati.
 * 
 * Pre-condizione: targa != NULL && strlen(targa) > 0,
 *                modello != NULL && strlen(modello) > 0,
 *                costo_giornaliero > 0
 * Post-condizione: Ritorna un nuovo veicolo inizializzato con i dati forniti
 * 
 * Ritorna: Un nuovo veicolo con targa, modello e costo specificati
 */
Veicolo crea_veicolo(char *targa, char *modello, float costo_giornaliero);

/**
 * Stampa le informazioni di un veicolo.
 * 
 * Pre-condizione: veicolo != NULL
 * Post-condizione: Vengono visualizzate a video le informazioni del veicolo
 */
void stampa_veicolo(Veicolo veicolo);

/**
 * Restituisce la targa di un veicolo.
 * 
 * Pre-condizione: veicolo != NULL
 * Post-condizione: targa = targa(veicolo)
 * 
 * Ritorna: Puntatore alla stringa contenente la targa del veicolo
 */
char *prendi_targa(Veicolo veicolo);

/**
 * Restituisce il costo giornaliero di un veicolo.
 * 
 * Pre-condizione: veicolo != NULL
 * Post-condizione: costo = costo_giornaliero(veicolo)
 * 
 * Ritorna: Il costo giornaliero del veicolo
 */
float prendi_costo_giornaliero(Veicolo veicolo);

/**
 * Verifica se un veicolo è disponibile per il noleggio.
 * 
 * Pre-condizione: veicolo != NULL
 * Post-condizione: disponibile = disponibile(veicolo)
 * 
 * Ritorna: 1 se il veicolo è disponibile, 0 altrimenti
 */
int verifica_disponibilita(Veicolo veicolo);

/**
 * Imposta lo stato di disponibilità di un veicolo.
 * 
 * Pre-condizione: veicolo != NULL, stato è 0 o 1
 * Post-condizione: disponibile(veicolo) = stato
 */
void imposta_disponibilita(Veicolo veicolo, int stato);
 
#endif /* VEICOLO_H */