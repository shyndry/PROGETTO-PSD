/**
 * Implementazione dell'ADT Veicolo per gestire i veicoli nel sistema di noleggio.
 * 
 * Questo file implementa le funzionalità definite in veicolo.h per la creazione,
 * gestione e manipolazione dei veicoli disponibili per il noleggio.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veicolo.h"
#include "list.h"

/**
 * Struttura interna di un veicolo.
 * Contiene tutte le informazioni relative a un veicolo nel sistema.
 */
struct veicolo {
    char targa[8];              /* Targa del veicolo (identificatore univoco) */
    char modello[50];           /* Modello del veicolo */
    char luogo[20];             /* luogo dove si torva il veicolo */
    float costo_giornaliero;    /* Costo giornaliero di noleggio */
    int disponibile;            /* Flag di disponibilità: 1 se disponibile, 0 se in noleggio */
};

/**
 * Crea un nuovo veicolo con i parametri specificati.
 * 
 * Questa funzione alloca e inizializza un nuovo veicolo con targa, modello e costo,
 * impostandolo come disponibile per il noleggio.
 * 
 * Pre-condizione: targa != NULL, modello != NULL, costo_giornaliero > 0
 * Post-condizione: Viene creato un nuovo veicolo con i dati specificati
 */
Veicolo crea_veicolo(char *targa, char *modello, float costo_giornaliero, char *luogo) {
    Veicolo veicolo = malloc(sizeof(struct veicolo));
    if (veicolo == NULL) {
        fprintf(stderr, "Errore di allocazione memoria per veicolo\n");
        exit(EXIT_FAILURE);
    }
    
    /* Inizializza i campi del veicolo */
    strcpy(veicolo->targa, targa);
    strcpy(veicolo->modello, modello);
    strcpy(veicolo->luogo, luogo);
    veicolo->costo_giornaliero = costo_giornaliero;

    
    /* Imposta il veicolo come disponibile */
    veicolo->disponibile = 1;
    
    return veicolo;
}

/**
 * Stampa le informazioni di un veicolo.
 * 
 * Visualizza a video i dettagli di un veicolo: targa, modello, costo giornaliero
 * e stato di disponibilità.
 * 
 * Pre-condizione: veicolo != NULL
 * Post-condizione: Le informazioni del veicolo vengono visualizzate a video
 */
void stampa_veicolo(Veicolo veicolo) {
    printf("Targa: %s | Modello: %s | Costo: %.2f€/giorno | luogo: %s\n",
           veicolo->targa, veicolo->modello, veicolo->costo_giornaliero, 
           veicolo->luogo );
}

/**
 * Restituisce la targa di un veicolo.
 * 
 * Pre-condizione: veicolo != NULL
 * Post-condizione: Ritorna un puntatore alla stringa targa
 */
char *prendi_targa(Veicolo veicolo) {
    return veicolo->targa;
}

/**
 * Restituisce il costo giornaliero di un veicolo.
 * 
 * Pre-condizione: veicolo != NULL
 * Post-condizione: Ritorna il costo giornaliero del veicolo
 */
float prendi_costo_giornaliero(Veicolo veicolo) {
    return veicolo->costo_giornaliero;
}

/**
 * Verifica se un veicolo è disponibile per il noleggio.
 * 
 * Pre-condizione: veicolo != NULL
 * Post-condizione: Ritorna 1 se disponibile, 0 se non disponibile
 */
int verifica_disponibilita(Veicolo veicolo) {
    return veicolo->disponibile;
}

/**
 * Imposta lo stato di disponibilità di un veicolo.
 * 
 * Pre-condizione: veicolo != NULL, stato è 0 o 1
 * Post-condizione: Lo stato di disponibilità del veicolo viene aggiornato
 */
void imposta_disponibilita(Veicolo veicolo, int stato) {
    veicolo->disponibile = stato;
}

/**
 * Carica una lista di veicoli da un file.
 * 
 * Legge i dati dei veicoli da un file di testo con formato:
 * targa modello costo_giornaliero
 * 
 * Pre-condizione: nome_file != NULL, il file deve esistere e avere il formato corretto
 * Post-condizione: Ritorna una lista di veicoli caricati dal file
 */
ListaVeicoli carica_veicoli_da_file(const char *nome_file) {
    FILE *fp = fopen(nome_file, "r");
    if (!fp) {
        perror("Errore nell'apertura del file veicoli");
        return NULL;
    }

    ListaVeicoli testa = NULL;
    char targa[20], modello[50];
    float costo;

    /* Legge i dati dal file e crea i veicoli */
    while (fscanf(fp, "%s %s %f", targa, modello, &costo) == 3) {
        /* Crea un nuovo veicolo con i dati letti */
        Veicolo veicolo = crea_veicolo(targa, modello, costo);
        
        /* Aggiunge il veicolo in testa alla lista */
        ListaVeicoli nuovo = malloc(sizeof(struct nodo_veicolo));
        if (nuovo == NULL) {
            fprintf(stderr, "Errore di allocazione memoria per nodo lista veicoli\n");
            exit(EXIT_FAILURE);
        }
        
        nuovo->veicolo = veicolo;
        nuovo->prossimo = testa;
        testa = nuovo;
    }

    fclose(fp);
    return testa;
}

/**
 * Aggiorna lo stato di disponibilità dei veicoli nella lista.
 * 
 * Verifica se i veicoli noleggiati hanno superato la data di fine noleggio
 * e, in tal caso, li segna come disponibili.
 * 
 * Pre-condizione: lista != NULL
 * Post-condizione: Ogni veicolo nella lista viene aggiornato in base alla data corrente
 */
void aggiorna_disponibilita(ListaVeicoli lista) {
    time_t ora_attuale;
    time(&ora_attuale);
    
    /* Scorre la lista e controlla ogni veicolo */
    while (lista) {
        /* Se il veicolo è in noleggio e la data di fine noleggio è passata */
        if (!verifica_disponibilita(lista->veicolo) && 
            ora_attuale >= prendi_fine_noleggio(lista->veicolo)) {
            /* Segna il veicolo come nuovamente disponibile */
            imposta_disponibilita(lista->veicolo, 1);
        }
        
        lista = lista->prossimo;
    }
}