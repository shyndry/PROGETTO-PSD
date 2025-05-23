#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prenotazione.h"
#include "veicolo.h"
#include "list.h"
#include "utils.h"
#include <time.h>
#include "utenti.h"





void crea_utente_storico(char *email){
    FILE *fp=fopen("storico_utenti.txt", "a");
    fprintf(fp, "\n#%s\n\n", email);
    fclose(fp);
}

//ritrona il numero di righe contate fino alla mail desiderata
int cerca_mail(char *email, FILE *fp){
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
    /*se non tova la mail la funzione crea nel file lo spazio 
    per la mail e la fun zione si richima in modo riorsivo*/
    fclose(fp); 
    crea_utente_storico(email); 
    fp=fopen("storico_utenti.txt", "r+");
    return cerca_mail(email, fp);
}


/*ritorna le righe del file fino alla fine dello sotrico 
della mail passata per argomento*/
int conta_righe(char *email, FILE *fp){
    int count=0;
    count=cerca_mail(email, fp);
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

//stampa a schermo lo sotrico dell' utente passato come argomento
void stampa_storico(char *email){
    printf("il tuo storico è :\n");
    FILE *fp=fopen("storico_utenti.txt", "r");
    cerca_mail(email, fp);
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

void aggiorna_storico_utente(char *email ,Prenotazione p){
    int cont=0;
    FILE *fp=fopen("storico_utenti.txt", "r+");
    FILE *temp=fopen("file_temp.txt", "w+");
    char riga[251];
    char data[11];
    
    cont=conta_righe(email, fp);//legge il file fino alla fine dello storico dell' utente desidersto
    
    // aggiunge la nuova prenazione nello sotrico dell' utente 
    fprintf(temp, "%s ",  prendi_targa_veicolo(p));
    data_in_stringa(prendi_inizio_noleggio(p), data, sizeof(data));
    fprintf(temp, "%s ", data);
    data_in_stringa(prendi_fine_noleggio(p), data, sizeof(data));
    fprintf(temp, "%s %f\n\n", data, prendi_costo(p));
    

    while (fgets(riga, sizeof(riga), fp))/*stampa nel file temporaneo la nuova prenotazione 
    e  la paete restante del file storico_utenti */
    {
        riga[strcspn(riga, "\n")] = '\0';
        fprintf(temp, "%s\n",  riga);
    }    
    
    rewind(fp);
    rewind(temp);
    //aggiorna il file utnente storico 
    for(int i=0; i<cont; i++){
        fgets(riga, sizeof(riga), fp);
    }
    while(fgets(riga, sizeof(riga), temp)){
        fprintf(fp, "%s",  riga);
    }
    fclose(fp);
    fclose(temp);
}