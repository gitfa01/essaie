#include <stdio.h>
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

int verifUserExiste(char *login, char *mdp, USER user);
int connexion(char *login, char *mdp, USER u);
int connexionUser(char *login, char *mdp, USER U[], int nu);
void enregistrerUser(USER Us[], int nu);
int chercherTypeUser(USER U[], int nu, char *login);

int main()
{
    char login[50];
    char *mdp;
    int nu = 2;
    USER U[nu];
    strcpy(U[0].login, "Admin");
    strcpy(U[0].motDePasse, "passer");
    U[0].typeUtilisateur = 2;
    strcpy(U[1].login, "Etu");
    strcpy(U[1].motDePasse, "passer");
    U[0].typeUtilisateur = 1;
    enregistrerUser(U, nu);

    do
    {
        printf("Donnez votre login: ");
        int i = 0;
        char c;
        do
        {
            c = getchar();
            if (c != '\n' && i < 15)
            {
                login[i] = c;
                if (isspace(i))
                {
                    printf("Le login ne peut pas contenir de caractère espace. Veuillez réessayer.\n");
                }
                i++;
            }
        } while (c != '\n');
        login[i] = '\0';
        if (strlen(login) == 0)
        {
            printf("Le login ne peut pas être vide. Veuillez réessayer.\n");
        }
    } while (strlen(login) == 0);

    printf("Donnez votre mot de passe: ");
    mdp = getpass("");
    if (connexionUser(login, mdp, U, nu))
    {
        printf("Authentification réussi!\n");
    }
    else
    {
        printf("Login ou mot de passe incorect!\n");
    }
    printf("%s \n", mdp);
    if (chercherTypeUser(U,nu,login)==1)
    {
        printf("Etudiant\n");
    }
    else {
        printf("Administrateur\n");
    }
    
    return 0;
}
int chercherTypeUser(USER U[], int nu, char *login)
{
    int c,d;
    for (int i = 0; i < nu; i++)
    {
        if (strcmp(U[i].login,login))
        {
            c=i;
            break;
        }
    }
    d=U[c].typeUtilisateur;
    return d;
}

void enregistrerUser(USER Us[], int nu)
{
    FILE *file = fopen("user.txt", "w");
    if (file == NULL)
    {
        printf("Impossible d'ouvrir un fichier user.txt\n");
    }

    for (int i = 0; i < nu; i++)
    {
        fprintf(file, "%s %s\n", Us[i].login, Us[i].motDePasse);
    }

    fclose(file);
}
int connexion(char *login, char *mdp, USER u)
{
    return verifUserExiste(login, mdp, u);
}

int verifUserExiste(char *login, char *mdp, USER user)
{
    FILE *f;
    f = fopen("user.txt", "rb");
    while (fscanf(f, "%s %s\n", user.login, user.motDePasse) != EOF)
    {
        if (strcmp(user.login, login) == 0 && strcmp(user.motDePasse, mdp) == 0)
        {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int connexionUser(char *login, char *mdp, USER U[], int nu)
{
    int c;
    for (int i = 0; i < nu; i++)
    {
        c = connexion(login, mdp, U[i]);
        if (c == 1)
        {
            return 1;
        }
    }
    if (c != 1)
    {
        return 0;
    }
}