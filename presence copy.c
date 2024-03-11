#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
typedef struct
{
    int heure;
    int minute;
} Heure;

typedef struct
{
    int jour;
    int mois;
    int annee;
} Date;

typedef struct
{
    int estPresent;
    Heure hmarque;
    Date datep;
} PRESENCE;

typedef struct
{
    int retardQuota;
    int minutesRetard;
    Date date;
} RETARD;

typedef struct
{
    int estJustifiee;
    Date date;
} ABSCENCE;

typedef struct
{
    int identifiantMessage;
    char expediteur[50];
    char sujet[100];
    char corps[1000];
    char destinataires[100][50];
    int nbDestinataires;
} MESSAGE;

typedef struct
{
    int id;
    char login[50];
    char motDePasse[50];
    int typeUtilisateur;
} USER;

typedef struct
{
    int numClasse;
    char nom[50];
    char filiere[50];
    int annee;
    // ETUDIANT etudiants[100];
    int nbEtudiants;
} CLASSE;

typedef struct
{
    int id;
    char nom[50];
    char prenom[50];
    int code;
    USER user;
    PRESENCE presence[31];
    PRESENCE abscence[31];
    int nbPresences;
    RETARD retard[31];
    CLASSE classe;
    int minutesretardtotal;
    MESSAGE messages[100];
    int nbMessages;
    int estBloque;
    int nbAbsences;
} ETUDIANT;

typedef struct
{
    int id;
    USER user;
} ADMIN;

typedef struct
{
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;
    int tm_wday;
    int tm_yday;
    int tm_isdst;
} tm;

int genererFichierdatePresence();
int genererFichierPresences();
int main()
{
}
int genererFichierdatePresence(Date datepresence)
{
    int code1, id1;
    char fich[30], date[15], line[500], nom1[50], prenom1[50], classe1[20];
    strcpy(fich, "presence_");
    sprintf(date, "%2d_%2d_%d", datepresence.jour, datepresence.mois, datepresence.annee);
    strcat(fich, date);
    strcat(fich, ".txt");

    FILE *fichPresence = fopen(fich, "a");
    FILE *fichPresence2 = fopen(fich, "ra");
    if (fichPresence2 == NULL)
    {
        printf("\nLe fichier %s %s est introuvable.", fich, date);
        return -1;
    }
    fprintf(fichPresence "+----------------------------------------------------------------------------------+\n");
    fprintf(fichPresence "    ****************Liste présence du %s*********************** \n", date);
    fprintf(fichPresence "+----------------------------------------------------------------------------------+\n");

    while (fgets(line, 500, fichPresence2) != NULL)
    {
        if (strcmp(classe1, "Dev Web Mobile"))
        {
            sscanf(line, "%d %s %s %d", &id1, nom1, prenom1, &code1);
            int id = id1, code = code1;
            char nom[50], prenom[50], classe[50];
            strcpy(nom, nom1);
            strcpy(prenom, prenom1);
            strcpy(classe, classe1);
            fprintf(fichPresence "  ______________________%s__________________________________\n", classe);
            fprintf(fichPresence "| ID :\t|     NOM      \t|          PRÉNOM       \t|    CODE  \t|      CLASSE      |\n");
            fprintf(fichPresence "+----------------------------------------------------------------------------------|\n");
            fprintf(fichPresence "|%d   \t|%s            \t|%s                     \t|%d        \t|Dev Web/Mobile    |\n", id, nom, prenom, code);
            fprintf(fichPresence "+----------------------------------------------------------------------------------+\n");
        }
        else if (strcmp(classe1, "dev Data"))
        {
            sscanf(line, "%d %s %s %d", &id1, nom1, prenom1, &code1);
            int id = id1, code = code1;
            char nom[50], prenom[50], classe[50];
            strcpy(nom, nom1);
            strcpy(prenom, prenom1);
            strcpy(classe, classe1);
            fprintf(fichPresence "  ______________________%s__________________________________\n", classe);
            fprintf(fichPresence "| ID :\t|     NOM      \t|          PRÉNOM       \t|    CODE  \t|      CLASSE      |\n");
            fprintf(fichPresence "+----------------------------------------------------------------------------------|\n");
            fprintf(fichPresence "|%d   \t|%s            \t|%s                     \t|%d        \t|Dev Data          |\n", id, nom, prenom, code);
            fprintf(fichPresence "+----------------------------------------------------------------------------------+\n");
        }
        else if (strcmp(classe1, "Réf Dig"))
        {
            sscanf(line, "%d %s %s %d", &id1, nom1, prenom1, &code1);
            int id = id1, code = code1;
            char nom[50], prenom[50], classe[50];
            strcpy(nom, nom1);
            strcpy(prenom, prenom1);
            strcpy(classe, classe1);
            fprintf(fichPresence "  ______________________%s__________________________________\n", classe);
            fprintf(fichPresence "| ID  \t|     NOM      \t|          PRÉNOM       \t|    CODE  \t|      CLASSE      |\n");
            fprintf(fichPresence "+----------------------------------------------------------------------------------|\n");
            fprintf(fichPresence "|%d   \t|%s            \t|%s                     \t|%d        \t|Réf Dig           |\n", id, nom, prenom, code);
            fprintf(fichPresence "+----------------------------------------------------------------------------------+\n");
        }
    }
}

int genererFichierPresence()
{
    printf("+---------------------------------------------------------+\n");
    printf("|                   LISTE DES PRESENCES                   |\n");
    printf("+---------------------------------------------------------+\n\n");
    FILE fichallPresence = fopen("ToutesLesPresences.txt", "a+");
    if (fichallPresence == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier etudiant.txt.\n");
        exit(EXIT_FAILURE);
    }
    int code1, id1;
    char fich[30], date[15], line[500], nom1[50], prenom1[50], classe1[20];
    strcpy(fich, "presence_");
    sprintf(date, "%2d_%2d_%d", tempsActuel->tm_mday, tempsActuel->tm_mon + 1, tempsActuel->tm_year + 1900);
    strcat(fich, date);
    strcat(fich, ".txt");
}
