#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veicolo.h"
#include "list.h"
#include "prenotazione.h"
#include <time.h>
#include "utils.h"
#include "utente.h"
#include "noleggio.h"
#include "storico_utente.h"
#include "gestione_file.h"

int main(){
    printf("========AVVERTENZA========\n");
    printf(" a meno di una richiesta particolare le scelte verranno\n effettuate tramite i numeri interi associati alle scelte\n");
    printf("==========================\n");
    
    char *email;
    int controllo=0;
    lista prenotazioni, veicoli;
    email=accedi_o_registrati();
    if(email==NULL){
        return 0;
    }
    // carica i veicoli e le prenotazioni dai file
    veicoli=carica_veicolo_file("auto.txt");
    if(veicoli==NULL){
        return 0;
    }
    prenotazioni=carica_prenotazione_file(veicoli, "prenotazioni.txt");
    // il ciclo while permette di visualizzare il menu e di effettuare le operazioni
    while(1){
        printf("\n=========== MENU ============\n"); 
        printf("che operazione si desidera effettuare?\n");
        printf (" 1. prenota veicolo\n 2. visualizza il proprio storico\n 3. visualizza prenotazioni effettuate\n 4. esci dal programma\n");
        scanf("%d", &controllo);
        getchar();
        switch(controllo){
        case 1:
            printf("\n Hai scelto: effettua prenotazione\n");
            prenotazioni=prenota_veicolo(email, veicoli, prenotazioni);
            break;
        case 2:
            printf("\n Hai scelto: visualizza il proprio storico\n");
            stampa_storico(email);
            break;
        case 3:
            printf("\n Hai scelto: visualizza prenotazioni effettuate\n");
            stampa_prenotazioni_utente(email, prenotazioni);
            break;
        case 4:
            printf("Uscita dal programma...\n");
            aggiorna_file_prenotazioni(prenotazioni, "prenotazioni.txt");
            return 0;
            break;
        default:
            printf("\n Scelta non valida. Riprovare.\n");
        }
    }
}