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
typedef struct nodo_veicolo *ListaVeicoli;


/**
 * Tipo di riferimento: Veicolo.
 * Rappresenta un singolo veicolo nel sistema di noleggio.
 */
typedef struct veicolo *Veicolo;

/**
 * Tipo di riferimento: ListaVeicoli.
 * Rappresenta una lista concatenata di veicoli.
 */
typedef struct nodo_veicolo {
    Veicolo veicolo;
    struct nodo_veicolo *prossimo;
} *ListaVeicoli;

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

/**
 * Restituisce il timestamp di fine noleggio di un veicolo.
 * 
 * Pre-condizione: veicolo != NULL
 * Post-condizione: fine = fine_noleggio(veicolo)
 * 
 * Ritorna: Timestamp di fine noleggio, 0 se il veicolo non è attualmente noleggiato
 */
time_t prendi_fine_noleggio(Veicolo veicolo);

/**
 * Imposta il timestamp di fine noleggio di un veicolo.
 * 
 * Pre-condizione: veicolo != NULL
 * Post-condizione: fine_noleggio(veicolo) = fine
 */
void imposta_fine_noleggio(Veicolo veicolo, time_t fine);

/**
 * Carica una lista di veicoli da un file.
 * 
 * Pre-condizione: nome_file != NULL, il file deve esistere e avere il formato corretto
 * Post-condizione: Ritorna una lista di veicoli caricati dal file
 * 
 * Ritorna: Una lista di veicoli caricati dal file
 */
ListaVeicoli carica_veicoli_da_file(const char *nome_file);

/**
 * Aggiorna lo stato di disponibilità dei veicoli nella lista.
 * 
 * Verifica se i veicoli noleggiati hanno superato la data di fine noleggio
 * e, in tal caso, li segna come disponibili.
 * 
 * Pre-condizione: lista != NULL
 * Post-condizione: Ogni veicolo nella lista viene aggiornato in base alla data corrente
 */
void aggiorna_disponibilita(ListaVeicoli lista);

#endif /* VEICOLO_H */