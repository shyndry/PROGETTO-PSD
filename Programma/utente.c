#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void registrati(char *);

int trova_email(char *email, FILE *fp){
    char c;
    char buffer[51];
    int j=0;
    rewind (fp);
    printf("inserisci la tua email\n");
    fgets(email, 51, stdin);
    email[strcspn(email, "\n")] = '\0';
    while(1){
        while((c=fgetc(fp)) != ';' && c != EOF )/*legge l' email e controlla 
        se corrisponde a quella passata per argomento */
        {
            buffer[j++]=c;
        }
        buffer[j]='\0';
        if(strcmp(email,buffer)==0){
            return 0;
        }
        memset(buffer, 0, sizeof(buffer));
        while ((c = fgetc(fp)) != EOF && c != '\n') /*legge la restante parte dopo il putno e vigola */
        {
        }
        if (c == EOF)//esce dal ciclo in caso l' email non dovesse essere presente nel file*/
        {
            return 1;  
        }
        j=0;
    }
}

void accedi(char *email){
    int j=0, flag=1;
    FILE *fp=fopen("utenti.txt","r");
    if(fp==NULL){
        printf("errore nell' esecuzione del programma\n");
        exit(0);
    }
    char c;
    if(fp==NULL){
        printf("errore nell' esecuzione del programma\n");
        exit(0);
    }
    char password[21], buffer[121];
    while(flag)/*controlla se la mail e presente e se non viene trovata 
    fornise una scelta all' utente su cosa fare*/
    {
        flag=trova_email(email, fp);
        if(flag){
            printf("mail errata o accunt non esistente:\n  
                riprovare (1)\n  crea account(2)\n  esci dal programma(3)\n");
            scanf("%d", &j);
            getchar();
            memset(email, 0, 51);
            if(j==2){
                fclose(fp);
                registrati(email);
                return ;
            }else if(j==3){
                exit(0);
            }
        }
    }
    flag=1;
    j=0;
    while((c=fgetc(fp)) !=EOF && c != '\n')/*dopo che la mail è stata trovata 
    preleva dal file la password associata*/
    {
        buffer[j++]=c;
    }
    buffer[j]='\0';
    printf("%s\n", buffer);
    j=0;
    while(flag)/*permette all' utente di inserire la password e la controlla 
    con un massimo di 4 tentativi*/
    {
        printf("inserisci la password:  \n");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password,"\n")]= '\0';
        flag=strcmp(password, buffer);
        if(flag){
            j++;
            if(j==4){
                exit(0);    
            }
            printf("password errata si prega di riprovare (%d tentativi rimasti)\n", 4-j);
            memset(password, 0, sizeof(password));
        }
    }
    fclose(fp);
} 

void registrati(char *email){
    int flag=0, j;
    FILE *fp=fopen("utenti.txt", "r+");
    if(fp==NULL){
        printf("errore nell' esecuzione del programma\n");
        exit(0);
    }
    char c, password[21];
    while(flag==0)/*controlla se la mail inserita è gia presnete e in caso dà all' utente 
    la possibilita di scegliere se riprovare accedere o uscire dal programma*/
    {
        flag=trova_email(email, fp);
        if(flag==0){
            printf("account gia esistente:\n  riprovare(1)\n  accedi(2)\n  esci(3)\n");
            scanf("%d", &j);
            getchar();
            memset(email, 0, 51);
            if(j==2){
                accedi(email);
                return;
            }else if(j==3){
                exit(0);
            }
        }
    }
    /*se la mail non è presente fa inserire all' utente la paswword 
    e isnerisce sia l' email che password nel file utenti */
    printf("inserisci la password (massimo 20 caratteri):\n");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';
    while(fgetc(fp) != EOF){}
    fprintf(fp, "%s;%s\n", email, password); 
    fclose(fp);
}

char *accedi_o_registrati(){
    int i=0;
    char *email=malloc(sizeof(char)*51);
    if(email==NULL){
        printf("errore nell' esecuzione del programma\n");
        exit(0);
    }
    while(1){
        printf("registrarti (digita 1) o accedi (digita 2):\n");
        scanf("%d", &i);
        getchar();
        if(i== 1){
            registrati(email);
            return email;
        }else if(i==2){
            accedi(email);
            return email;
        }
        printf("errore di inserimento riporva\n");
    }
}
