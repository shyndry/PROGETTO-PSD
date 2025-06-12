#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veicolo.h"
#include "list.h"
#include "prenotazione.h"
#include <time.h>
#include "utils.h"
#include "gestione_file.h"


/**
 * Funzione: controllo_disponibilita_veicolo
 * ---
 * Verifica se un veicolo è disponibile in un determinato intervallo di tempo,
 * controllando che non sia già prenotato in periodi che si sovrappongono.
 * 
 * Parametri:
 * v: veicolo da verificare
 * prenotazioni: lista delle prenotazioni esistenti
 * inizio: timestamp di inizio periodo desiderato
 * fine: timestamp di fine periodo desiderato
 * 
 * Pre-condizione:
 * - prenotazioni != NULL
 * - veicolo != NULL
 * - inizio < fine
 * 
 * Post-condizione:
 * - Restituisce 1 se il veicolo è disponibile nell'intervallo specificato
 * - Restituisce 0 se il veicolo è già prenotato in periodi che si sovrappongono
 * 
 * Ritorna:
 * 1 se disponibile, 0 altrimenti
 */
int controllo_disponibilita_veicolo(Veicolo v, lista prenotazioni, time_t inizio, time_t fine){
    time_t inPren;
    time_t finPren;
    
    while(!lista_vuota(prenotazioni)){
        inPren=prendi_inizio(ottieni_primo_elemento(prenotazioni));
        finPren=prendi_fine(ottieni_primo_elemento(prenotazioni));
        /*controlla se la targa del veicolo corrisponde a quella della prenotaizone*/
        if(strcmp(prendi_targa(v),prendi_targa_veicolo(ottieni_primo_elemento(prenotazioni)))==0){
            /*se la targa corrisponde controlla se è prenotato nel periodo di tempo desiderato*/
            if(inPren>inizio && inPren<fine){
                return 0;
            }else if(finPren>inizio && finPren<fine){
                return 0;
            }
            if(inPren<=inizio && finPren>=inizio){
                return 0;
            }else if(inPren<=fine && finPren>=fine){
                return 0;
            }
    }
    prenotazioni=ottieni_coda_lista(prenotazioni);
    }
    return 1;
}

/**
 * Funzione: stampa_disponibilita
 * ---
 * Stampa a schermo tutti i veicoli disponibili in un determinato intervallo di tempo,
 * includendo sia i veicoli attualmente disponibili che quelli prenotabili nel periodo specificato.
 * 
 * Parametri:
 * veicoli: lista dei veicoli da controllare
 * prenotazioni: lista delle prenotazioni esistenti
 * inizio: timestamp di inizio periodo desiderato
 * fine: timestamp di fine periodo desiderato
 * 
 * Pre-condizione:
 * - veicoli != NULL
 * - prenotazioni != NULL
 * - inizio < fine
 * 
 * Post-condizione:
 * - Stampa a schermo i veicoli disponibili
 * - Restituisce il numero di veicoli disponibili trovati
 * 
 * Ritorna:
 * Il numero di veicoli disponibili stampati
 */
void stampa_disponibilita(lista veicoli, lista prenotazioni, time_t inizio, time_t fine) {
    Veicolo v;
    while(!lista_vuota(veicoli)){
        v=ottieni_primo_elemento(veicoli);
        /*se il veicolo non è prenotato lo stampa direttemente altrienti controlla
          se è disponibile nell' intervallo di tempo desiderato*/
        if(verifica_disponibilita(v)){
            stampa_veicolo(v);
        }else if( controllo_disponibilita_veicolo(v, prenotazioni, inizio, fine)){
            stampa_veicolo(v); 
        }
        veicoli=ottieni_coda_lista(veicoli);
    }
}

/**
 * Funzione: prenota_veicolo
 * ---
 * Gestisce il processo completo di prenotazione di un veicolo, includendo:
 * - Inserimento delle date
 * - Verifica disponibilità
 * - Selezione veicolo
 * - Conferma finale
 * 
 * Parametri:
 * email: email dell'utente che effettua la prenotazione
 * veicoli: lista dei veicoli disponibili
 * prenotazioni: lista delle prenotazioni esistenti
 * 
 * Pre-condizione:
 * - email != NULL
 * - veicoli != NULL
 * 
 * Post-condizione:
 * - Se la prenotazione ha successo, restituisce la lista aggiornata con la nuova prenotazione
 * - Se la prenotazione fallisce, restituisce la lista invariata
 * - Gestisce interamente il dialogo con l'utente tramite stdin/stdout
 * 
 * Ritorna:
 * La lista delle prenotazioni (aggiornata o invariata)
 */

lista prenota_veicolo(char *email, lista veicoli, lista prenotazioni){
    time_t inizio, fine;
    time_t now;
    Prenotazione p;
    char targa[8];
    int conferma;
    Veicolo v;
    time(&now);
    printf("\n======= INSERISCI INTERVALLO PRENOTAZIONE =======\n");
    printf(" dai 30 giorni in su verra applicato il 20%% di sconto\n");
    printf("\n inserire la data di inizo del noleggio\n");
    inizio=inserisci_data();
    /*controlla che l'inzio della prenotazione sia maggiore della data odierna*/
    if(now>=inizio){
        printf("data inizio prenotazione non valida\n");
        return prenotazioni;
    }
    printf("inserire la data di fine del noleggio\n");
    fine=inserisci_data();
    getchar();
    /*controlla che la data di fine prenotazione sia maggiore della data di inizio*/
    if(inizio>fine){
        printf("\ndata fine prenotazione non valida\n");
        return prenotazioni;
    }
    printf("\n\n======== MACCHINE DISPONIBILI ========\n\n");
    
    stampa_disponibilita(veicoli, prenotazioni, inizio, fine);/*stampa le macchine disponibili*/
    
    do{
        conferma=2;
        printf("\n\nscegli la macchina desiderata inderendo la targa: ");
        fgets(targa, sizeof(targa), stdin);
        targa[strcspn(targa, "\n")] = '\0';
        stringa_maiuscola(targa);
        v=trova_veicolo(targa, veicoli);
        /*se la targa non viene trovata da all' utente la possibilità di reinserirla o di annullare l' operazione*/
        if(v==NULL){
            targa[0]='\0';
            printf("errore, auto non trovata.\n");
            printf("si desidera riprovare ?\n-1 si\n-2 no\n");
            scanf("%d", &conferma);/*permette all' utente di effettuare la scelta*/
            getchar();
            if(conferma==2){
                return prenotazioni;  
            }
        }
    }while(conferma==1);
    p=crea_prenotazione(email, v, inizio, fine);
    stampa_prenotazione(p);
    /*chiede conferma prima di aggiungere la prenotazione alla lista prenotazioni*/
    printf("confermare prenotazione?\n-1 si\n-2 no\n");
    scanf("%d", &conferma);
    getchar();
    if(conferma == 1){
        prenotazioni=aggiungi_a_lista(p, prenotazioni);
        return prenotazioni;
    }else if(conferma == 2){
        free(p);/*se la prenotazione viene annullata viene liberato lo spazio allocato per la prenotazione*/
        return prenotazioni;
    }
}

/**
 * Funzione: stampa_prenotazioni_utente
 * ---
 * Stampa tutte le prenotazioni attive associate a un particolare utente.
 * 
 * Parametri:
 * email: email dell'utente di cui visualizzare le prenotazioni
 * p: lista delle prenotazioni da controllare
 * 
 * Pre-condizione:
 * - email != NULL
 * 
 * Post-condizione:
 * - Stampa a schermo tutte le prenotazioni associate all'email
 * - Se non ci sono prenotazioni, stampa un messaggio informativo
 * 
 * Ritorna:
 * Nessun valore di ritorno
 */
void stampa_prenotazioni_utente(char *email, lista p){
    int cont=0;
    while(!lista_vuota(p)){
        if(strcmp(email,prendi_email(ottieni_primo_elemento(p)))==0){
            stampa_prenotazione(ottieni_primo_elemento(p));
            cont++;
        }
        p=ottieni_coda_lista(p);
    }
    /*se non sono presenti prenotazioni associate ad "email" verra stampato un messaggio apposito*/
    if(cont == 0){
        printf("non sono prensti prenotazioni a nome dell' utnete al momento\n");
    }
}




