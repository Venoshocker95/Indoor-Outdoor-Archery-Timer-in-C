#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define INDOOR_TIME  120
#define OUTDOOR_TIME 240

//Colore Font
#define TESTO_ROSSO  "\x1b[31m"
#define TESTO_VERDE  "\x1b[32m"
#define TESTO_GIALLO "\x1b[33m"
#define TESTO_NERO   "\x1b[30m"
#define TESTO_RESET  "\x1b[0m"

//Colore Sfondo
#define SFONDO_ROSSO  "\e[41m"
#define SFONDO_VERDE  "\e[42m"
#define SFONDO_GIALLO "\e[43m"
#define SFONDO_NERO   "\e[40m"

#define ERR_MSG "INPUT ERROR!"
#define TXT_ERR "FILE ERROR!"

//Prototypes
int chooseTimer();
void countdown();
int userDefinedTime();
void checkFile();
void writeVolee();
void writeTurn();
char readTurn();
int readVolee();

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int main()
{
    checkFile();

    // variabile per controllare AB-CD
    int turnCount = 0;
    // variabile contenente il numero totale di volée
    int voleeCount = 1;

    //readVolee();

    for(;;)
    {
        // Continua il ciclo finchè il valore di "userChoice" non equivale a 'E'
        // terminando così l'esecuzione.
        int choosenTime = chooseTimer();

        // Esegui il conto alla rovescia
        countdown(choosenTime, turnCount, voleeCount);

        // if(turnCount % 2 == 0)
        // {
        //     writeVolee(voleeCount);
        //     voleeCount++;
        // }

        // Pseudo Loop AB-CD; CD-AB...
        if(turnCount >= 3)
        {
            turnCount = 0;
        }
        else
        {
            turnCount++;
        }
        
        if(turnCount % 2 == 0)
        {
            voleeCount++;
        }
    }

    return 0;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int chooseTimer()
{
    char userChoice = '\0';

    printf(TESTO_RESET "\n\t\t\tSELEZIONARE TIMER:\n");
    printf("\nI = indoor      O = outdoor     P = personalizzato      E = esci : ");
    //userChoice = getchar();
    scanf(" %1[^\n]", &userChoice);
    userChoice = toupper(userChoice);


    if(userChoice == 'I' )
    {
        return(INDOOR_TIME);
    }  

    else if(userChoice == 'O')
    {
        return(OUTDOOR_TIME);
    }

    else if(userChoice == 'P')
    {
        int userTime = userDefinedTime();

        return(userTime);
    }

    else if(userChoice == 'E')
    {
        exit(0);
    }

    else
    {
        // Stampa messaggio d'errore, pulisci il flusso dati e richiama la funzione
        printf("\n%s\n", ERR_MSG);
        fflush(stdin);
        chooseTimer();
    }
}



int userDefinedTime()
{
    int userTime = 0;

    printf("\nInserire tempo in SECONDI: ");
    scanf("%d", &userTime);

    return userTime;
}



void countdown(int secondi, int ab_cd, int numVolee)
{
    char *turno = "\0";

    int countVolee = numVolee;

    if(ab_cd == 0 || ab_cd == 3)
    {
        turno = "AB";
    }
    else if(ab_cd == 1 || ab_cd == 2)
    {
        turno = "CD";
    }

    while(secondi >= 0)
    {
        if(secondi == 0)
        {
            printf(TESTO_ROSSO "\r%03d T: %s", secondi, turno);
            fflush(stdout);
        }
        else if(secondi <= 30 )
        {
            printf(TESTO_GIALLO "\r%03d T: %s", secondi, turno);
            fflush(stdout);
        }
        else
        {
            printf(TESTO_VERDE "\r%03d T: %s", secondi, turno);
            //ab_cd == 0 || ab_cd == 2 ? "AB" : "CD"
            fflush(stdout);
        }
        //fflush(stdout);
        Sleep(1000);
        secondi--;
    }

    // Fine tempo
        Beep(1000,1000);
        Sleep(400);
        Beep(1000,1000);
        Sleep(400);
        Beep(1000,1000);

        // Al termine di una volée stampa sul file
        writeVolee(countVolee, turno);
}



void checkFile()
{
    FILE *f;

    f = fopen("./numVolee.txt", "r");

    //NULL CHECK
    if(f == NULL)
    {
        printf("\n%s", TXT_ERR);
        fclose(f);
        exit(1);
    }
}



void writeVolee(int voleeCount, char *turno)
{
    FILE *f;

    f = fopen("./numVolee.txt", "w+");

    //stampa numero volee su file
    fprintf(f, "%02d", voleeCount);
    fprintf(f, "\n%s", turno);

    fclose(f);
}



int readVolee()
{
    int numVolee = 0;
}