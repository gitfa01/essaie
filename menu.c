#include <stdio.h>
#include <stdlib.h>
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
    char code[5];
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

#define taillemax 8

int marquerPresence(int idEtudiant);
int verifAdminExiste(int id, char *mdp);
int marquerPresenceAdmin(char *codeEtudiant);
int marquerlespresences(int idAdmin);
void masquerMotDePasse(char *mot_de_passe);
ETUDIANT verifiEtuExiste(int idEtu, int *r);
ETUDIANT *verifiEtucode(char *code);
void genererFichierdatePresence(Date datepresence);
int FichierDate(char *date);
int convertirDate(char *date, int *j, int *m, int *a);
int bissextile(int annee);
int valide_date(int a, int m, int j);
void date_suivante(int a, int m, int j, int *annee, int *mois, int *jour);
int genererFichierPresence(Date datefin);

int menuAdmin(int idAdmin)
{
    int option;
    do
    {
        printf(" __________BIENVENUE DANS L'ESPACE ADMIN_____________ \n");
        printf("+------------------------------------------------------+\n");
        printf("| 1 : Gestion des étudiants                            |\n");
        printf("| 2 : Génération de fichier                            |\n");
        printf("| 3 : Marquer les présences                            |\n");
        printf("| 4 : Envoyer un message                               |\n");
        printf("| 5 : Déconnexion                                      |\n");
        printf("+------------------------------------------------------+\n");

        do
        {
            printf("| Veuillez choisir une option : ");
            scanf("%d", &option);
            if (option < 1 || option > 5)
            {
                printf("Option invalide! Veuillez choisir une option comprise entre 1 et 5");
            }

        } while (option < 1 || option > 5);

        if (option == 1)
        {
            int op1;
            do
            {
                printf("+------------------------------------------------------+\n");
                printf("| 1 : Ajouter un étudiant                              |\n");
                printf("| 2 : Modifier un étudiant                             |\n");
                printf("| 3 : Supprimer un étudiant                            |\n");
                printf("| 4 : Afficher la liste des étudiants                  |\n");
                printf("| 5 : Retour au menu principal                         |\n");
                printf("+------------------------------------------------------+\n");
                do
                {
                    printf("| Veuillez choisir une option : ");
                    scanf("%d", &op1);
                    if (op1 < 1 || op1 > 5)
                    {
                        printf("Option invalide! Veuillez choisir une option comprise entre 1 et 5");
                    }

                } while (op1 < 1 || op1 > 5);

                /* code */
            } while (op1 != 5);
        }

        else if (option == 2)
        {
            int op2;
            do
            {
                printf("+---------------------------------------------------------------------+\n");
                printf("| 1 : Générer fichier de la liste des présences de toutes les dates   |\n");
                printf("| 2 : Générer un fichier de la liste des présences d'une date         |\n");
                printf("| 3 : Retour au menu principal                                        |\n");
                printf("+---------------------------------------------------------------------+\n");
                do
                {
                    printf("| Veuillez choisir une option : ");
                    scanf("%d", &op2);
                    if (op2 < 1 || op2 > 3)
                    {
                        printf("Option invalide! Veuillez choisir une option comprise entre 1 et 3");
                    }

                } while (op2 < 1 || op2 > 3);

                if (op2 == 1)
                {
                    Date datefin;
                    datefin.jour = 11;
                    datefin.mois = 3;
                    datefin.annee = 2024;
                    date_suivante(datefin.annee, datefin.mois, datefin.jour, &datefin.annee, &datefin.mois, &datefin.jour);
                    printf("%02d-%02d-%d\n", datefin.jour, datefin.mois, datefin.annee);
                    genererFichierPresence(datefin);
                }
                else if (op2 == 2)
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
                    continue;
                }

            } while (op2 != 3);
        }

        else if (option == 3)
        {
            marquerlespresences(idAdmin);
        }

        else if (option == 4)
        {
            int op4;
            do
            {
                printf("+------------------------------------------------------+\n");
                printf("| 1 : Envoyer un message à tous les étudiants          |\n");
                printf("| 2 : Envoyer un message à une classe                  |\n");
                printf("| 3 : Envoyer un message aux étudiants choisis         |\n");
                printf("| 4 : Retour au menu principal                         |\n");
                printf("+------------------------------------------------------+\n");
                do
                {
                    printf("| Veuillez choisir une option : ");
                    scanf("%d", &op4);
                    if (op4 < 1 || op4 > 4)
                    {
                        printf("Option invalide! Veuillez choisir une option comprise entre 1 et 4");
                    }

                } while (op4 < 1 || op4 > 4);

            } while (op4 != 4);
        }
        else if (option == 5)
        {
            return 1;
        }

    } while (option != 5);
}

int menuEtudiant(int idEtudiant)
{
    int option;
    do
    {
        // printf("id : %d\n", idEtudiant);
        printf(" ___________BIENVENUE DANS L'ESPACE ETUDIANT__________ \n");
        printf("+------------------------------------------------------+\n");
        printf("| 1 : MARQUER MA PRÉSENCE                              |\n");
        printf("| 2 : NOMBRE DE MINUTES DE RETARD                      |\n");
        printf("| 3 : MES MESSAGES (0)                                 |\n");
        printf("| 4 : Deconnexion                                      |\n");
        printf("+------------------------------------------------------+\n");
        printf("Veuillez choisir une option : ");
        do
        {
            scanf("%d", &option);
            if (option < 1 || option > 4)
            {
                printf("Option invalide! Veuillez choisir une option comprise entre 1 et 4");
            }

        } while (option < 1 || option > 4);

        if (option == 1)
        {
            marquerPresence(idEtudiant);
            menuEtudiant(idEtudiant);
        }

        if (option == 2)
        {
            // nbrdeminutedabscence
        }

        if (option == 3)
        {
            // messages
        }
        if (option == 4)
        {
            return 1;
        }

    } while (option != 4);
}

ETUDIANT verifiEtuExiste(int idEtu, int *r)
{
    ETUDIANT e = {0};
    FILE *f;
    f = fopen("etudiant.txt", "r");
    while (fscanf(f, "%d %s %s %s %s %s %d %d %d %d\n", &e.id, e.nom, e.prenom, e.code, e.classe.nom, e.user.login, &e.nbPresences, &e.minutesretardtotal, &e.estBloque, &e.nbAbsences) != EOF)
    {
        if (idEtu == e.id)
        {
            fclose(f);
            *r = 1;
            return e;
        }
    }
    fclose(f);
    *r = 0;
    return e;
}

int marquerPresence(int idEtudiant)
{
    int v;
    char confirmation;
    time_t temps;
    struct tm *tempsActuel;

    printf("Confirmez-vous votre présence ? (o/n): ");
    scanf(" %c", &confirmation);
    ETUDIANT e = verifiEtuExiste(idEtudiant, &v);
    time(&temps);
    tempsActuel = localtime(&temps);

    if (confirmation == 'o' || confirmation == 'O')
    {
        int id1;
        char fich[30], date[15], line[200], heure[30], nom1[50], prenom1[50], code1[5];

        strcpy(fich, "copy_presence_");
        sprintf(date, "%02d_%02d_%d", tempsActuel->tm_mday, tempsActuel->tm_mon + 1, tempsActuel->tm_year + 1900);
        strcat(fich, date);
        strcat(fich, ".txt");
        sprintf(heure, "%02d : %02d", tempsActuel->tm_hour, tempsActuel->tm_min);

        /*FILE *fichPresence = fopen(fich, "r");
        while (fgets(line, 200, fichPresence) != NULL)
        {
            sscanf(line, "%d %s %s %s", &id1, nom1, prenom1, code1);
            if (idEtudiant == id1)
            {
                printf("La présence a été déjà enregistrée\n");
                fclose(fichPresence);
                return 0;
            }
        }
        fclose(fichPresence);
        // printf("date  : %s heure : %s fichier : %s\n", date, heure, fich);
        if (tempsActuel->tm_hour >= 8)
        {
            int min = (tempsActuel->tm_hour - 8) * 60 + tempsActuel->tm_min;
            printf("Vous avez un retard !\n");
            e.minutesretardtotal = e.minutesretardtotal + min;
        }
        else
        {
            printf("Présence enregistrée à l'heure.\n");
        }*/

        FILE *fichPresence = fopen(fich, "a");
        FILE *fichPresence2 = fopen(fich, "ra");

        while (fgets(line, 200, fichPresence2) != NULL)
        {
            sscanf(line, "%d %s %s %s", &id1, nom1, prenom1, code1);
            if (idEtudiant == id1)
            {
                printf("La présence a été déjà enregistrée\n");
                fclose(fichPresence2);
                fclose(fichPresence);
                return -1;
            }
        }
        fprintf(fichPresence, "%d %s %s %s %s %s\n", e.id, e.nom, e.prenom, e.code, e.classe.nom, heure);
        fclose(fichPresence);
        fclose(fichPresence2);
        char date1[11], date2[11], date3[11];
        int c = 0;
        FILE *fichDate = fopen("date.txt", "a");
        FILE *fichDate2 = fopen("date.txt", "ra");
        sprintf(date2, "%02d-%02d-%d", tempsActuel->tm_mday, tempsActuel->tm_mon + 1, tempsActuel->tm_year + 1900);
        sprintf(date3, "%02d/%02d/%d", tempsActuel->tm_mday, tempsActuel->tm_mon + 1, tempsActuel->tm_year + 1900);
        while (fgets(line, 20, fichDate2) != NULL)
        {
            sscanf(line, "%s", date1);
            if (strcmp(date2, date1) == 0 || strcmp(date3, date1) == 0)
            {
                fclose(fichDate2);
                fclose(fichDate);
                c++;
                break;
            }
        }
        if (c == 0)
        {
            fprintf(fichDate, "%s\n %s\n", date2, date3);
            fclose(fichDate);
            fclose(fichDate2);
        }
        printf("date  : %s heure : %s fichier : %s\n", date, heure, fich);
        if (tempsActuel->tm_hour >= 8)
        {
            int min = (tempsActuel->tm_hour - 8) * 60 + tempsActuel->tm_min;
            printf("Vous avez un retard !\n");
            e.minutesretardtotal = e.minutesretardtotal + min;
        }
        else
        {
            printf("Présence enregistrée à l'heure.\n");
        }

        printf("Présence confirmée le %02d/%02d/%d à %02d:%02d\n",
               tempsActuel->tm_mday, tempsActuel->tm_mon + 1, tempsActuel->tm_year + 1900,
               tempsActuel->tm_hour, tempsActuel->tm_min);
        return 1;
    }
    else
    {
        printf("Présence non confirmée.\n");
        return 0;
    }
}

ETUDIANT *verifiEtucode(char *code)
{
    ETUDIANT *e = malloc(sizeof(ETUDIANT));
    if (!e)
    {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }

    FILE *f = fopen("etudiant.txt", "r");
    if (!f)
    {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier etudiant.txt.\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(f, "%d %s %s %s %s %s %d %d %d %d", &e->id, e->nom, e->prenom, e->code, e->classe.nom, e->user.login, &e->nbPresences, &e->minutesretardtotal, &e->estBloque, &e->nbAbsences) != EOF)
    {
        if (strcmp(code, e->code) == 0)
        {
            fclose(f);
            return e;
        }
    }
    fclose(f);
    free(e);
    return NULL;
}
int verifAdminExiste(int id, char *mdp)
{
    USER user = {0};
    FILE *f;
    f = fopen("user.txt", "r");

    while (fscanf(f, "%d %s %s", &user.id, user.login, user.motDePasse) != EOF)
    {
        if (user.id == id)
        {
            if (strcmp(user.motDePasse, mdp) == 0)
            {
                printf("Mot de passe correcte \n");
                fclose(f);
                return 1;
            }
            else
            {
                printf("Mot de passe incorrecte \n");
                fclose(f);
                return 0;
            }
        }
    }

    printf("ID Admin non trouvé \n");
    fclose(f);
    return 0;
}

int marquerlespresences(int idAdmin)
{
    char mdpAdmin[taillemax];
    ETUDIANT *e;
    int verif;
    /*if (!verifAdminExiste(idAdmin, mdpAdmin))
     {
         printf("Identifiants administrateur invalides.\n");
         return 0;
     }*/
    // int codeEtudiant;
    char input[5] = "";
    fflush(stdin);
    printf("Entrez le code de l'étudiant (tapez 'q' pour sortir) : ");
    scanf("%s", input);
    if ((strcasecmp(input, "q") != 0) && (isdigit((unsigned char)*input)))
    {
        // codeEtudiant = atoi(input);
        e = verifiEtucode(input);
        if (e == NULL)
        {
            printf("Cet étudiant n'existe pas.\n");
            marquerlespresences(idAdmin);
        }
        else
        {
            e = verifiEtucode(input);
            int etuTrouve = 0;
            verifiEtuExiste(e->id, &verif);
            if (verif == 1)
            {
                marquerPresenceAdmin(input);
                etuTrouve = 1;
            }
            if (!etuTrouve)
            {
                printf("Aucun étudiant trouvé avec ce code.\n");
            }
            marquerlespresences(idAdmin);
        }
    }
    else if (strcasecmp(input, "q") == 0)
    {
        strcpy(mdpAdmin, "");
        fflush(stdout);
        masquerMotDePasse(mdpAdmin);
        printf("Vérification... \n");
        if (verifAdminExiste(idAdmin, mdpAdmin))
        {
            printf("Retour au menu principal.\n");
            return 0;
        }
        else
        {
            printf("Veuillez reprendre la saisie.\n");
            marquerlespresences(idAdmin);
        }
    }
    else
    {
        printf("Entrée invalide. Veuillez réessayer.\n");
        marquerlespresences(idAdmin);
    }
}

void masquerMotDePasse(char *mot_de_passe)
{
    int i = 0;
    char c;

    initscr();
    cbreak();
    refresh();
    strcpy(mot_de_passe, "");
    printw("Entrez votre mot de passe : ");
    noecho();

    while ((c = getch()) != '\n' && i < taillemax - 1)
    {
        mot_de_passe[i++] = c;
        printw("*");
    }
    mot_de_passe[i] = '\0';
    clear();
    echo();
    endwin();
}

int marquerPresenceAdmin(char *codeEtudiant)
{
    ETUDIANT *e = malloc(sizeof(ETUDIANT));
    if (!e)
    {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }
    FILE *fileEtudiant = fopen("etudiant.txt", "r");
    if (fileEtudiant == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier etudiant.txt.");
    }

    int i = 0, id;
    char ligne[150], nom[50], prenom[50], code[5], classe[50];
    while (fgets(ligne, sizeof(ligne), fileEtudiant))
    {
        sscanf(ligne, "%d %s %s %s %s", &id, nom, prenom, code, classe);
        if (strcmp(code, codeEtudiant) == 0)
        {
            e = verifiEtucode(codeEtudiant);
            i++;
            break;
        }
    }
    fclose(fileEtudiant);
    if (!i)
    {
        printf("Aucun étudiant trouvé avec ce code.\n");
        return 0;
    }
    else
    {
        e->id = id;
        strcpy(e->nom, nom);
        strcpy(e->prenom, prenom);
        strcpy(e->classe.nom, classe);
        strcpy(e->code, code);
        time_t temps = time(NULL);
        struct tm *tempsActuel = localtime(&temps);

        char fich[30], date[15], line[200];
        char heure[30], nom1[30], prenom1[30], code1[5], classe1[50];
        int id1;
        strcpy(fich, "copy_presence_");
        sprintf(date, "%02d_%02d_%d", tempsActuel->tm_mday, tempsActuel->tm_mon + 1, tempsActuel->tm_year + 1900);
        strcat(fich, date);
        strcat(fich, ".txt");
        sprintf(heure, "%02d : %02d", tempsActuel->tm_hour, tempsActuel->tm_min);
        printf("date  : %s heure : %s fichier : %s\n", date, heure, fich);

        /*FILE *fichPresence1 = fopen(fich, "r");
        while (fgets(line, 150, fichPresence1) != NULL)
        {
            sscanf(line, "%d %s %s %s %s", &id1, nom1, prenom1, code1, classe1);
            if (strcmp(codeEtudiant, code1) == 0)
            {
                printf("La présence a été déjà enregistrée\n");
                fclose(fichPresence1);
                return 0;
            }
        }
        fclose(fichPresence1);*/

        FILE *fichPresence = fopen(fich, "a");
        FILE *fichPresence2 = fopen(fich, "ra");
        if (fichPresence == NULL)
        {

            printf("Error opening file %s.\n", fich);

            return -1;
        }
        if (fichPresence2 == NULL)
        {

            printf("Error opening file %s.\n", fich);

            fclose(fichPresence);

            return -1;
        }
        while (fgets(line, 150, fichPresence2) != NULL)
        {
            sscanf(line, "%d %s %s %s %s", &id1, nom1, prenom1, code1, classe1);
            if (strcmp(codeEtudiant, code1) == 0)
            {
                printf("La présence a été déjà enregistrée\n");
                fclose(fichPresence2);
                fclose(fichPresence);
                return -1;
            }
        }

        fprintf(fichPresence, "%d %s %s %s %s %s\n", id, nom, prenom, code, classe, heure);

        char date1[11], date2[11], date3[11];
        int c = 0;
        FILE *fichDate = fopen("date.txt", "a");
        FILE *fichDate2 = fopen("date.txt", "ra");
        sprintf(date2, "%02d-%02d-%d", tempsActuel->tm_mday, tempsActuel->tm_mon + 1, tempsActuel->tm_year + 1900);
        sprintf(date3, "%02d/%02d/%d", tempsActuel->tm_mday, tempsActuel->tm_mon + 1, tempsActuel->tm_year + 1900);
        while (fgets(line, 20, fichDate2) != NULL)
        {
            sscanf(line, "%s", date1);
            if (strcmp(date2, date1) == 0 || strcmp(date3, date1) == 0)
            {
                fclose(fichDate2);
                fclose(fichDate);
                c++;
                break;
            }
        }
        if (c == 0)
        {
            fprintf(fichDate, "%s\n", date2);
            fprintf(fichDate, "%s\n", date3);
            fclose(fichDate);
            fclose(fichDate2);
        }

        printf("Présence de l'étudiant %s %s confirmée le %02d/%02d/%d à %02d:%02d\n",
               e->nom, e->prenom,
               tempsActuel->tm_mday, tempsActuel->tm_mon + 1, tempsActuel->tm_year + 1900,
               tempsActuel->tm_hour, tempsActuel->tm_min);
        // e.presence->datep.jour = tempsActuel->tm_mday;
        // e.presence->datep.mois = tempsActuel->tm_mon + 1;
        // e.presence->datep.annee = tempsActuel->tm_year + 1900;

        if (tempsActuel->tm_hour > 8)
        {
            int minutes = (tempsActuel->tm_hour - 8) * 60 + tempsActuel->tm_min;
            printf("L'étudiant a un retard de %d minutes !\n", minutes);
            e->minutesretardtotal += minutes;
        }
        else
        {
            printf("Présence de l'étudiant enregistrée à l'heure.\n");
        }
        fclose(fichPresence);
        fclose(fichPresence2);
        return 1;
    }
}

int FichierDate(char *date)
{
    FILE *fileDate = fopen("date.txt", "r");
    if (fileDate == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier de date.txt");
        return 0;
    }
    char line[100], date1[10];
    while (fgets(line, 100, fileDate))
    {
        sscanf(line, "%s", date1);
        if (!strcmp(date1, date))
        {
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

    /*FILE* fichPresence = fopen(fich, "r");
    FILE* fichPresence2 = fopen(fich2, "a");

    if (fichPresence == NULL) {
        printf("\nLe fichier %s %s est introuvable.", fich, date);
        exit(1);
    }

    while (fgets(line, sizeof(line), fichPresence)) {
        sscanf(line, "%d %s %s %d %s %s", &id1, nom1, prenom1, &code1, classe1, heure);
        fprintf(fichPresence2, "%d %s %s %d %s \n", id1, nom1, prenom1, code1, classe1);
    }

    fclose(fichPresence2);
    fclose(fichPresence);
    */
    FILE *fichPresence = fopen(fich, "w");
    FILE *fichPresence2 = fopen(fich2, "r");

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
        fprintf(stderr, "Erreur lors de l'ouverture du fichier Touteslesprésences.txt.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fichallPresence, "+----------------------------------------------------------------------------+\n");
    fprintf(fichallPresence, "|                          LISTE DES PRESENCES                               |\n");
    fprintf(fichallPresence, "+----------------------------------------------------------------------------+\n\n");
    Date date;
    date.jour = 9;
    date.mois = 3;
    date.annee = 2024;
    while (date.jour != datefin.jour || date.mois != datefin.mois || date.annee != datefin.annee)
    {
        /* genererFichierdatePresence(date);*/
        int id1;
        char fich[30], date1[15], line[100], nom1[50], prenom1[50], code1[5], classe1[20], heure[30];
        strcpy(fich, "copy_presence_");
        sprintf(date1, "%02d_%02d_%d", date.jour, date.mois, date.annee);
        strcat(fich, date1);
        strcat(fich, ".txt");
        FILE *fichallPresence2 = fopen(fich, "r");
        printf("Date : %02d %02d %02d\t", date.jour, date.mois, date.annee);
        if (fichallPresence2 == NULL)
        {
            printf("\nPas de presence pour cette date : %s \n", date1);
            continue;
        }
        sprintf(date1, "%02d %02d %d", date.jour, date.mois, date.annee);
        fprintf(fichallPresence, "+----------------------------------------------------------------------------------+\n");
        fprintf(fichallPresence, "    **************** Liste présence du %s *********************** \n", date1);
        fprintf(fichallPresence, "+----------------------------------------------------------------------------------+\n");
        fprintf(fichallPresence, "| ID :\t|     NOM      \t|          PRÉNOM       \t|    CODE  \t|      CLASSE      |\n");
        fprintf(fichallPresence, "+----------------------------------------------------------------------------------+\n");

        while (fgets(line, 100, fichallPresence2) != NULL)
        {
            sscanf(line, "%d %s %s %s %s", &id1, nom1, prenom1, code1, classe1);
            int id = id1;
            char code[5], nom[50], prenom[50], classe[50];
            strcpy(nom, nom1);
            strcpy(prenom, prenom1);
            strcpy(code, code1);
            strcpy(classe, classe1);
            fprintf(fichallPresence, "|%d         \t%s          \t%s                     \t%s          \t%s        \n", id, nom, prenom, code, classe);
            fprintf(fichallPresence, "+----------------------------------------------------------------------------------+\n");
        }
        fclose(fichallPresence2);
        date_suivante(date.annee, date.mois, date.jour, &date.annee, &date.mois, &date.jour);
    }
    fclose(fichallPresence);
}
int bissextile(int annee)
{
    if (!(annee % 4) && ((annee % 100) || !(annee % 400)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int valide_date(int a, int m, int j)
{
    int j_m = 31;

    if (m == 2)
    {

        j_m = bissextile(a) ? 29 : 28;
    }
    else if (m == 4 || m == 6 || m == 9 || m == 11)
    {

        j_m = 30;
    }
    return j <= j_m;
}

void date_suivante(int a, int m, int j, int *annee, int *mois, int *jour)
{
    if ((m == 1) && (m == 3) && (m == 5) && (m == 7) && (m == 8) && (m == 10) && (j == 31))
    {

        j = 1;
        m++;
    }
    else if ((m == 4) && (m == 6) && (m == 9) && (m == 11) && (j == 30))
    {
        j = 1;
        m++;
    }
    else if ((m == 12) && (j == 31))
    {
        j = 1;
        m = 1;
        a++;
    }
    else if (m == 2)
    {
        if ((((a % 4) || !(a % 100) && (a % 400)) && (j == 28)) || (!(a % 4) && ((a % 100) || !(a % 400)) && (j == 29)))
        {
            j = 1;
            m++;
        }
        else
        {
            j++;
        }
    }
    else
    {
        j++;
    }
    *jour = j;
    *mois = m;
    *annee = a;
}