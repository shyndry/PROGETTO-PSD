/**
 * Implementazione dell'ADT Utente per gestire l'autenticazione degli utenti.
 * 
 * Questo file implementa le funzionalità definite in utente.h per la
 * registrazione di nuovi utenti e l'accesso di utenti esistenti al sistema.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Verifica se un'email è già registrata nel sistema.
 * 
 * Cerca l'email specificata nel file degli utenti e restituisce un valore
 * che indica se l'email è stata trovata o meno.
 * 
 * Pre-condizione: email != NULL, fp != NULL e aperto in modalità lettura
 * Post-condizione: Restituisce 0 se l'email è stata trovata, 1 altrimenti
 */
int trova_email(char *email, FILE *fp) {
    char c;
    char buffer[51];
    int j = 0;
    
    rewind(fp);
    printf("Inserisci la tua email:\n");
    fgets(email, 51, stdin);
    
    /* Rimuove il carattere newline dalla stringa */
    email[strcspn(email, "\n")] = '\0';
    
    while(1) {
        /* Legge l'email dal file fino al separatore ';' */
        while((c = fgetc(fp)) != ';' && c != EOF) {
            buffer[j++] = c;
        }
        buffer[j] = '\0';
        
        /* Verifica se l'email corrisponde a quella cercata */
        if(strcmp(email, buffer) == 0) {
            return 0; /* Email trovata */
        }
        
        /* Pulisce il buffer per la prossima lettura */
        memset(buffer, 0, sizeof(buffer));
        
        /* Legge il resto della riga (password) fino a newline */
        while((c = fgetc(fp)) != EOF && c != '\n') {
            /* Salta il resto della riga */
        }
        
        /* Se siamo arrivati alla fine del file, l'email non è presente */
        if(c == EOF) {
            return 1;
        }
        
        j = 0;
    }
}

/**
 * Gestisce l'accesso di un utente esistente.
 * 
 * Chiede all'utente di inserire email e password. Se l'email non esiste,
 * propone all'utente di registrarsi o uscire. Se l'email esiste, verifica
 * la password con un massimo di 4 tentativi.
 * 
 * Pre-condizione: email != NULL
 * Post-condizione: Se l'accesso ha successo, email conterrà l'indirizzo dell'utente
 */
void accedi(char *email) {
    int j = 0, flag = 1;
    FILE *fp = fopen("utenti.txt", "r");
    
    if(fp == NULL) {
        printf("Errore nell'apertura del file utenti.txt\n");
        exit(EXIT_FAILURE);
    }
    
    char password[21], buffer[121];
    
    /* Verifica se l'email esiste nel file utenti */
    while(flag) {
        flag = trova_email(email, fp);
        
        if(flag) {
            printf("Email non trovata o account non esistente:\n");
            printf("  1. Riprovare\n");
            printf("  2. Crea un nuovo account\n");
            printf("  3. Esci dal programma\n");
            printf("Scelta: ");
            
            scanf("%d", &j);
            getchar(); /* Consuma il newline */
            
            memset(email, 0, 51);
            
            if(j == 2) {
                fclose(fp);
                registrati(email);
                return;
            } else if(j == 3) {
                exit(EXIT_SUCCESS);
            }
        }
    }
    
    /* Email trovata, ora legge la password associata */
    flag = 1;
    j = 0;
    
    /* Legge la password dal file */
    while((flag = (fgetc(fp) != EOF)) && flag != '\n') {
        buffer[j++] = flag;
    }
    buffer[j] = '\0';
    
    j = 0;
    flag = 1;
    
    /* Verifica la password con massimo 4 tentativi */
    while(flag) {
        printf("Inserisci la password:\n");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';
        
        flag = strcmp(password, buffer);
        
        if(flag) {
            j++;
            if(j == 4) {
                printf("Numero massimo di tentativi raggiunto. Uscita dal programma.\n");
                exit(EXIT_FAILURE);
            }
            
            printf("Password errata. Si prega di riprovare (%d tentativi rimasti)\n", 4-j);
            memset(password, 0, sizeof(password));
        }
    }
    
    printf("Accesso effettuato con successo!\n");
    fclose(fp);
}

/**
 * Gestisce la registrazione di un nuovo utente.
 * 
 * Richiede all'utente di inserire una nuova email e password, verificando
 * che l'email non sia già presente nel sistema.
 * 
 * Pre-condizione: email != NULL
 * Post-condizione: Se la registrazione ha successo, email conterrà l'indirizzo registrato
 */
void registrati(char *email) {
    int flag = 0, j;
    FILE *fp = fopen("utenti.txt", "r+");
    
    if(fp == NULL) {
        /* Se il file non esiste, lo crea */
        fp = fopen("utenti.txt", "w+");
        if(fp == NULL) {
            printf("Errore nella creazione del file utenti.txt\n");
            exit(EXIT_FAILURE);
        }
    }
    
    char password[21];
    
    /* Verifica se l'email esiste già */
    while(flag == 0) {
        flag = trova_email(email, fp);
        
        if(flag == 0) {
            printf("Account già esistente:\n");
            printf("  1. Riprovare con un'altra email\n");
            printf("  2. Accedi con questo account\n");
            printf("  3. Esci dal programma\n");
            printf("Scelta: ");
            
            scanf("%d", &j);
            getchar(); /* Consuma il newline */
            
            memset(email, 0, 51);
            
            if(j == 2) {
                accedi(email);
                return;
            } else if(j == 3) {
                exit(EXIT_SUCCESS);
            }
        }
    }
    
    /* Email non trovata, procede con la registrazione */
    printf("Inserisci la password (massimo 20 caratteri):\n");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';
    
    /* Posiziona il cursore alla fine del file */
    fseek(fp, 0, SEEK_END);
    
    /* Scrive le credenziali nel file */
    fprintf(fp, "%s;%s\n", email, password);
    printf("Registrazione completata con successo!\n");
    
    fclose(fp);
}

/**
 * Gestisce il processo di autenticazione.
 * 
 * Permette all'utente di scegliere se accedere con un account esistente
 * o registrarne uno nuovo.
 * 
 * Pre-condizione: Nessuna
 * Post-condizione: Restituisce un puntatore alla stringa email dell'utente autenticato
 */
char *accedi_o_registrati() {
    int i = 0;
    char *email = malloc(sizeof(char) * 51);
    
    if(email == NULL) {
        printf("Errore di allocazione memoria\n");
        exit(EXIT_FAILURE);
    }
    
    while(1) {
        printf("\n===== SISTEMA DI AUTENTICAZIONE =====\n");
        printf("1. Registrati (nuovo utente)\n");
        printf("2. Accedi (utente esistente)\n");
        printf("Scelta: ");
        
        scanf("%d", &i);
        getchar(); /* Consuma il newline */
        
        if(i == 1) {
            registrati(email);
            return email;
        } else if(i == 2) {
            accedi(email);
            return email;
        }
        
        printf("Scelta non valida. Riprova.\n");
    }
}
