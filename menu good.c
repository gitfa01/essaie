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

#define taillemax 15

int marquerPresence(int idEtudiant);
int verifAdminExiste(int id, char *mdp);
int marquerPresenceAdmin(int codeEtudiant);
void marquerlespresences(int idAdmin);
void masquerMotDePasse(char *mot_de_passe);

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
                printf("| 1 : Générer un fichier de la liste des présences                    |\n");
                printf("| 2 : Générer un fichier de la liste des abscences                    |\n");
                printf("| 3 : Générer un fichier de la liste des retards par date             |\n");
                printf("| 4 : Générer un fichier de la liste des retards par date             |\n");
                printf("| 5 : Générer un fichier de la liste des etudiants à renvoyer par date|\n");
                printf("| 6 : Retour au menu principal                                        |\n");
                printf("+---------------------------------------------------------------------+\n");
                do
                {
                    printf("| Veuillez choisir une option : ");
                    scanf("%d", &op2);
                    if (op2 < 1 || op2 > 6)
                    {
                        printf("Option invalide! Veuillez choisir une option comprise entre 1 et 6");
                    }

                } while (op2 < 1 || op2 > 6);

                /* code */
            } while (op2 != 6);
        }

        else if (option == 3)
        {
            /* char mdp[15];
            int nu, i = 0;
            USER U[nu];
            FILE *f;
            f = fopen("user.txt", "r");
            while (fscanf(f, "%d %s %s %d\n", &U[i].id, U[i].login, U[i].motDePasse, &U[i].typeUtilisateur) != EOF)
            {*/
            marquerlespresences(idAdmin);
            /*i++;
        }
        fclose(f);*/
        }

        else if (option == 4)
        {
            int op4;
            do
            {
                printf("+------------------------------------------------------+\n");
                printf("| 1 : Envoyer un message à étudiant                    |\n");
                printf("| 2 : Envoyer un message à tous les étudiants          |\n");
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

                /* code */
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
        printf("| 2 : NOMBRE DE MINUTES D’ABSENCE                      |\n");
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
        }

        if (option == 2)
        {
            // nbrdeminutedabscence
        }

        if (option == 3)
        {
            // messages
        }
        if (option = 4)
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
    while (fscanf(f, "%d %s %s %d %s %s %d %d %d %d\n", &e.id, e.nom, e.prenom, &e.code, e.classe.nom, e.user.login, &e.nbPresences, &e.minutesretardtotal, &e.estBloque, &e.nbAbsences) != EOF)
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
    /*ETUDIANT e={0};
    FILE *fileEtudiant = fopen("etudiant.txt", "r");
    if (fileEtudiant == NULL) {
        printf("Erreur lors de l'ouverture du fichier Etudiant.txt.");
    }

    char ligne[500], nom[50], prenom[50], classe[50];
    int id, code;

    while (fgets(ligne, sizeof(ligne), fileEtudiant)) {
        sscanf(ligne, "%d %s %s %d %s", &id, nom, prenom, &code, classe);
        if (id==idEtudiant) {
            e.id = id;
            strcpy(e.nom, nom);
            strcpy(e.prenom, prenom);
            strcpy(e.classe.nom, classe);
            e.code = code;
            break;
        }
        fclose(fileEtudiant);
    }*/
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
        if (tempsActuel->tm_hour > 8)
        {
            int min = tempsActuel->tm_hour * 60 + tempsActuel->tm_min;
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

        int code1;
        char fich[30], date[15], line[500];
        char heure[30], nom1[30], prenom1[30];
        int id1;
        strcpy(fich, "presence_");
        sprintf(date, "%2d_%2d_%d", tempsActuel->tm_mday, tempsActuel->tm_mon + 1, tempsActuel->tm_year + 1900);
        strcat(fich, date);
        strcat(fich, ".txt");
        sprintf(heure, "%2d : %2d", tempsActuel->tm_hour, tempsActuel->tm_min);
        printf("date  : %s heure : %s fichier : %s\n", date, heure, fich);

        FILE *fichPresence = fopen(fich, "a");
        FILE *fichPresence2 = fopen(fich, "ra");

        while (fgets(line, 500, fichPresence2) != NULL)
        {
            // printf("look");
            sscanf(line, "%d %s %s %d", &id1, nom1, prenom1, &code1);
            if (idEtudiant==id1)
            {
                fclose(fichPresence2);
                fclose(fichPresence);
                return -1;
            }
        }

        fprintf(fichPresence, "%d %s %s %d %s %s\n", e.id, e.nom, e.prenom, e.code, e.classe.nom, heure);

        fclose(fichPresence);
        fclose(fichPresence2);
        return 1;
    }
    else
    {
        printf("Présence non confirmée.\n");
    }
    return 0;
}
ETUDIANT *verifiEtucode(int code)
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

    while (fscanf(f, "%d %s %s %d %s %s %d %d %d %d", &e->id, e->nom, e->prenom, &e->code, e->classe.nom, e->user.login, &e->nbPresences, &e->minutesretardtotal, &e->estBloque, &e->nbAbsences) != EOF)
    {
        if (code == e->code)
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

void marquerlespresences(int idAdmin)
{
    char mdpAdmin[taillemax];
    ETUDIANT *e;
    int verif;
    /*if (!verifAdminExiste(idAdmin, mdpAdmin))
     {
         printf("Identifiants administrateur invalides.\n");
         return 0;
     }*/
    int input1, input2, codeEtudiant;
    char input[5] = "";
    fflush(stdin);
    printf("Entrez le code de l'étudiant (tapez 'q' pour sortir) : ");
    scanf("%s", input);
    /*exit = (char)codeEtudiant;
    input1 = 'q' + '0';
    input2 = 'Q' + '0';*/
    while ((strcasecmp(input, "q") != 0) && (isdigit((unsigned char)*input)))
    {
        codeEtudiant = atoi(input);
        e = verifiEtucode(codeEtudiant);
        if (e == NULL)
        {
            printf("Cet étudiant n'existe pas.\n");
            marquerlespresences(idAdmin);
        }
        else
        {
            e = verifiEtucode(codeEtudiant);
            int etuTrouve = 0;
            verifiEtuExiste(e->id, &verif);
            if (verif == 1)
            {
                marquerPresenceAdmin(codeEtudiant);
                etuTrouve = 1;
            }
            if (!etuTrouve)
            {
                printf("Aucun étudiant trouvé avec ce code.\n");
            }
            marquerlespresences(idAdmin);
        }
    }
    if (strcasecmp(input, "q") == 0)
    {
        strcpy(mdpAdmin, "");
        fflush(stdout);
        masquerMotDePasse(mdpAdmin);
        printf("Vérification... \n");
        // verifAdminExiste(idAdmin, mdpAdmin);
        if (verifAdminExiste(idAdmin, mdpAdmin))
        {
            printf("Retour au menu principal.\n");
            menuAdmin(idAdmin);
        }
        else
        {
            printf("Veuillez reprendre la saisie.\n");
            marquerlespresences(idAdmin);
        }
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

int marquerPresenceAdmin(int codeEtudiant)
{
    ETUDIANT e = {0};
    FILE *fileEtudiant = fopen("etudiant.txt", "r");
    if (fileEtudiant == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier etudiant.txt.");
    }

    int i = 0, id, code;
    char ligne[500], nom[50], prenom[50], classe[50];
    while (fgets(ligne, sizeof(ligne), fileEtudiant))
    {
        sscanf(ligne, "%d %s %s %d %s", &id, nom, prenom, &code, classe);
        if (code == codeEtudiant)
        {
            // e = verifiEtucode(codeEtudiant);
            e.id = id;
            strcpy(e.nom, nom);
            strcpy(e.prenom, prenom);
            strcpy(e.classe.nom, classe);
            e.code = code;
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

    time_t temps = time(NULL);
    struct tm *tempsActuel = localtime(&temps);

    printf("Présence de l'étudiant %s %s confirmée le %02d/%02d/%d à %02d:%02d\n",
           e.nom, e.prenom,
           tempsActuel->tm_mday, tempsActuel->tm_mon + 1, tempsActuel->tm_year + 1900,
           tempsActuel->tm_hour, tempsActuel->tm_min);
    // e.presence->datep.jour = tempsActuel->tm_mday;
    // e.presence->datep.mois = tempsActuel->tm_mon + 1;
    // e.presence->datep.annee = tempsActuel->tm_year + 1900;

    if (tempsActuel->tm_hour > 8)
    {
        int minutes = tempsActuel->tm_hour * 60 + tempsActuel->tm_min - (8 * 60);
        printf("L'étudiant a un retard de %d minutes !\n", minutes);
        e.minutesretardtotal += minutes;
    }
    else
    {
        printf("Présence de l'étudiant enregistrée à l'heure.\n");
    }

    int code1;
    char fich[30], date[15], line[500];
    char heure[30], nom1[30], prenom1[30];
    int id1;
    strcpy(fich, "presence_");
    sprintf(date, "%2d_%2d_%d", tempsActuel->tm_mday, tempsActuel->tm_mon + 1, tempsActuel->tm_year + 1900);
    strcat(fich, date);
    strcat(fich, ".txt");
    sprintf(heure, "%2d : %2d", tempsActuel->tm_hour, tempsActuel->tm_min);
    printf("date  : %s heure : %s fichier : %s\n", date, heure, fich);

    FILE *fichPresence = fopen(fich, "a");
    FILE *fichPresence2 = fopen(fich, "ra");

    while (fgets(line, 500, fichPresence2) != NULL)
    {
        // printf("look");
        sscanf(line, "%d %s %s %d", &id1, nom1, prenom1, &code1);
        if (codeEtudiant == code1)
        {
            fclose(fichPresence2);
            fclose(fichPresence);
            return -1;
        }
    }

    fprintf(fichPresence, "%d %s %s %d %s %s\n", e.id, e.nom, e.prenom, e.code, e.classe.nom, heure);

    fclose(fichPresence);
    fclose(fichPresence2);
    return 1;
}