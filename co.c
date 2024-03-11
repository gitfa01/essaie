#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
    int id;
    char nom[50];
    char prenom[50];
    char code[50];
    PRESENCE presence[31];
    PRESENCE abscence[31];
    int nbPresences;
    RETARD retard[31];
    int minutesretardtotal;
    MESSAGE messages[100];
    int nbMessages;
    int estBloque;
    int nbAbsences;
} ETUDIANT;

typedef struct
{
    int numClasse;
    char nom[50];
    char filiere[50];
    int annee;
    ETUDIANT etudiants[100];
    int nbEtudiants;
} CLASSE;

typedef struct
{
    int id;
    USER user;
} ADMIN;

int verifUserExiste(char *login, char *mdp);
int connexion(char *login, char *mdp, USER *u);
int connexionUser(char *login, char *mdp, USER U[], int nu);

int main()
{
    char login[50];
    char *mdp;
    int nu = 2;
    USER U[nu];
    strcpy(U[0].login, "Admin");
    strcpy(U[0].motDePasse, "passer");
    strcpy(U[1].login, "Etu");
    strcpy(U[1].motDePasse, "passer");

    printf("Donnez votre login: ");
    scanf("%s", login);

    printf("Donnez votre mot de passe: ");
    mdp = getpass("");
    if (connexionUser(login, mdp, U, nu))
    {
        printf("Authentification réussie!\n");
    }
    else
    {
        printf("Login ou mot de passe incorrect!\n");
    }

    return 0;
}

void enregistrerUser(USER Us[], int nu) {
    FILE *file = fopen("user.txt", "w");
    if (file == NULL) {
        printf("Impossible d'ouvrir un fichier user.txt\n");
        return;
    }

    for (int i = 0; i < nu; i++) {
        fprintf(file, "%s %s\n", Us[i].login, Us[i].motDePasse);
    }

    fclose(file);
}

int verifUserExiste(char *login, char *mdp) {
    FILE *f;
    char file_login[50];
    char file_mdp[50];
    f = fopen("user.txt", "r");
    if (f == NULL) {
        printf("Impossible d'ouvrir un fichier user.txt\n");
        return 0;
    }

    while (fscanf(f, "%s %s\n", file_login, file_mdp) != EOF) {
        if (strcmp(file_login, login) == 0 && strcmp(file_mdp, mdp) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int connexion(char *login, char *mdp, USER *u)
{
    return verifUserExiste(login, mdp);
}

int connexionUser(char *login, char *mdp, USER U[], int nu)
{
    for (int i = 0; i < nu; i++)
    {
        if (connexion(login, mdp, &U[i]))
        {
            return 1;
        }
    }
    return 0;
}
