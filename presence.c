#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include </home/fatoumata/Bureau/LangageC/projet/fonctionDate.c>
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
typedef struct
{
    int jour;
    char sep;
    int mois;
    char finsep;
    int annee;
} saisieDate;

// int verifDate(char *date);
void genererFichierdatePresence(Date datepresence);
int FichierDate(char datepresence[]);
int convertirDate(char *date, int *j, int *m, int *a);
int genererFichierPresence(Date datefin);
int main()
{
    char date[11];
    int j, m, a;
    do
    {
        printf("Entrer une date sous format  JJ/MM/AAAA ou JJ-MM-AAAA : \n");
        scanf("%10s", date);
    } while (!convertirDate(date, &j, &m, &a));

    printf("Jour: %d, Mois: %d, Annee: %d\n", j, m, a);
    Date datepresence;
    datepresence.jour = j;
    datepresence.mois = m;
    datepresence.annee = a;
    genererFichierdatePresence(datepresence);
    return 0;
    //} while (!convertirDate(date, &j, &m, &a) || !FichierDate(date));

    Date dp;
    dp.jour = j;
    dp.mois = m;
    dp.annee = a;
    genererFichierdatePresence(dp);
    Date datefin;
    datefin.jour = 11;
    datefin.mois = 3;
    datefin.annee = 2024;
    genererFichierPresence(datefin);
    return 0;
}

int FichierDate(char datepresence[])
{
    FILE *fileDate = fopen("date.txt", "r");
    if (fileDate == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier de date.txt");
        return 0;
    }
    int i = 0;
    char line[20], date1[10];
    while (fgets(line, 20, fileDate))
    {
        sscanf(line, "%s", date1);
        if (strcmp(date1, datepresence) == 0)
        {
            i++;
            fclose(fileDate);
            return 1;
        }
    }
    fclose(fileDate);
    return 0;
}

int convertirDate(char *date, int *j, int *m, int *a)
{
    int jour, mois, annee;
    if (sscanf(date, "%d/%d/%d", &jour, &mois, &annee) == 3 ||
        sscanf(date, "%d-%d-%d", &jour, &mois, &annee) == 3)
    {
        if (valide_date(annee, mois, jour))
        {
            *j = jour;
            *m = mois;
            *a = annee;
            return 1;
        }
    }
    else
    {
        printf("La date est invalide.\n");
        return 0;
    }
}

/*int verifDate(char *date)
{
    9 - 3 - 2024 9 / 3 / 2024
    {
        if (!((date[i] >= '0' && date[i] <= '9') || (date[i] == '/')||(date[i]=='-')) && date[i] != '\0') {
            printf("La date ne respecte pas le format jj/mm//aaaa\n");
            return 84;
            }
        else if (date[i] == '/' || date[i] == '-')
        {
            //
        }
        else if ((date[i] >= '0' && date[i] <= '9'))
        {
            //
        }


    }
}*/
void genererFichierdatePresence(Date datepresence)
{
    int id1;
    char fich[30], fich2[30], date[15], line[100], nom1[50], prenom1[50], code1[5], classe1[20], heure[30];
    strcpy(fich2, "copy_");
    strcpy(fich, "presence_");
    sprintf(date, "%02d_%02d_%d", datepresence.jour, datepresence.mois, datepresence.annee);
    strcat(fich, date);
    strcat(fich, ".txt");
    strcat(fich2, fich);

    FILE *fichPresence = fopen(fich, "w");
    FILE *fichPresence2 = fopen(fich2, "r");

    if (fichPresence == NULL)
    {
        printf("\nLe fichier %s %s est introuvable.\n", fich, date);
        exit(1);
    }

    char date1[15];
    sprintf(date1, "%02d %02d %d", datepresence.jour, datepresence.mois, datepresence.annee);
    fprintf(fichPresence, "+----------------------------------------------------------------------------------+\n");
    fprintf(fichPresence, "    **************** Liste présence du %s *********************** \n", date1);
    fprintf(fichPresence, "+----------------------------------------------------------------------------------+\n");
    fprintf(fichPresence, "| ID :\t|     NOM      \t|          PRÉNOM       \t|    CODE  \t|      CLASSE      |\n");
    fprintf(fichPresence, "+----------------------------------------------------------------------------------+\n");

    while (fgets(line, 100, fichPresence2) != NULL)
    {
        sscanf(line, "%d %s %s %s %s", &id1, nom1, prenom1, code1, classe1);

        int id = id1;
        char code[5], nom[50], prenom[50], classe[50];

        strcpy(nom, nom1);
        strcpy(prenom, prenom1);
        strcpy(code, code1);
        strcpy(classe, classe1);
        fprintf(fichPresence, "|%d         \t%s          \t%s                     \t%s          \t%s        \n", id, nom, prenom, code, classe);
        fprintf(fichPresence, "+----------------------------------------------------------------------------------+\n");
    }

    fclose(fichPresence2);
    fclose(fichPresence);
}

int genererFichierPresence(Date datefin)
{

    FILE *fichallPresence = fopen("ToutesLesPresences.txt", "w");
    if (fichallPresence == NULL)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier etudiant.txt.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fichallPresence, "+---------------------------------------------------------------------+\n");
    fprintf(fichallPresence, "|                       LISTE DES PRESENCES                           |\n");
    fprintf(fichallPresence, "+---------------------------------------------------------------------+\n\n");
    Date date;
    date.jour = 9;
    date.mois = 3;
    date.annee = 2024;
    while (date.jour != datefin.jour && date.mois != datefin.mois && date.annee != datefin.annee)
    {
        genererFichierdatePresence(date);
        date_suivante(&date.jour, &date.mois, &date.annee);
        printf("%02d %02d %d", date.jour, date.mois, date.annee);
    }
    fclose(fichallPresence);
}
