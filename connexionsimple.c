#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include </home/fatoumata/Bureau/LangageC/projet/menu.c>

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
    USER user;
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

int verifUserExiste(char *login, char *mdp, USER user, int *a);
int connexion(char *login, char *mdp, USER u);
int connexionUser(char *login, char *mdp, USER U[], int nu, int *a);
void enregistrerUser(USER Us[], int nu);
int chercherTypeUser(USER U[], int nu, char *login);
int reponse();
void enregistrerEtu(ETUDIANT E[], int ne);

int main()
{
    char login[50];
    char *mdp;
    int idi;
    int nu = 4;
    USER U[nu];
    U[0].id = 1;
    strcpy(U[0].login, "Admin");
    strcpy(U[0].motDePasse, "passer");
    U[0].typeUtilisateur = 2;
    U[1].id = 2;
    strcpy(U[1].login, "Etu1");
    strcpy(U[1].motDePasse, "passer");
    U[1].typeUtilisateur = 1;
    U[2].id = 3;
    strcpy(U[2].login, "Etu2");
    strcpy(U[2].motDePasse, "passer");
    U[2].typeUtilisateur = 1;
    U[3].id = 4;
    strcpy(U[3].login, "Etu3");
    strcpy(U[3].motDePasse, "passer");
    U[3].typeUtilisateur = 1;
    enregistrerUser(U, nu);
    int ne = 3;
    ETUDIANT E[ne];
    E[0].id = 2;
    strcpy(E[0].nom, "Sy");
    strcpy(E[0].prenom, "Mbaye");
    strcpy(E[0].code, "SM123");
    strcpy(E[0].user.login, "Etu1");
    E[0].nbPresences = 14;
    E[0].minutesretardtotal = 15;
    E[0].estBloque = 1;
    E[0].nbAbsences = 3;

    E[1].id = 3;
    strcpy(E[1].nom, "Sane");
    strcpy(E[1].prenom, "Jules");
    strcpy(E[1].code, "JS456");
    strcpy(E[1].user.login, "Etu2");
    E[1].nbPresences = 15;
    E[1].minutesretardtotal = 20;
    E[1].estBloque = 1;
    E[1].nbAbsences = 2;

    E[2].id = 4;
    strcpy(E[2].nom, "Diagne");
    strcpy(E[2].prenom, "Marie");
    strcpy(E[2].code, "MD789");
    strcpy(E[2].user.login, "Etu3");
    E[2].nbPresences = 10;
    E[2].minutesretardtotal = 5;
    E[2].estBloque = 1;
    E[2].nbAbsences = 7;
    enregistrerEtu(E,ne);
    do
    {
        do
        {
            printf("Donnez votre login: ");
            int i = 0;
            char c;
            do
            {
                c = getchar();
                if (!isspace(c) && c != '\n' && i < 15)
                {
                    login[i] = c;
                    i++;
                }
            } while (c != '\n');
            login[i] = '\0';
            if (strlen(login) == 0 && reponse() != 1)
            {
                printf("Le login ne peut pas être vide. Veuillez réessayer.\n");
            }
        } while (strlen(login) == 0);

        printf("Donnez votre mot de passe: ");
        mdp = getpass("");
        if (connexionUser(login, mdp, U, nu, &idi))
        {
            printf("Authentification réussi!\n");
            printf("id : %d\n",idi);
            break;
        }
        else
        {
            printf("Login ou mot de passe incorect!\n");
        }
        //printf("%s \n", mdp);
    } while (reponse());

    if (chercherTypeUser(U, nu, login) == 1)
    {
        menuEtudiant(idi);
    }
    else if (chercherTypeUser(U, nu, login) == 2)
    {
        //printf("Administrateur\n");
        menuAdmin(idi);
    }
    else
    {
        printf("Vos données saisies étaient incorrectes. Vérifiez que vous avez le bon login et le bon moit de passe.\n");
    }

    return 0;
}

int chercherTypeUser(USER U[], int nu, char *login)
{
    int c, d, j = 0;
    for (int i = 0; i < nu; i++)
    {
        if (strcmp(U[i].login, login) == 0)
        {
            c = i;
            break;
        }
        j++;
    }
    if (j < nu)
    {
        d = U[c].typeUtilisateur;
        //printf("%d\n", d);
        return d;
    }
    else
    {
        return 0;
    }
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
        fprintf(file, "%d %s %s %d\n",Us[i].id, Us[i].login, Us[i].motDePasse,Us[i].typeUtilisateur);
    }

    fclose(file);
}
int connexion(char *login, char *mdp, USER u)
{
    int b;
    return verifUserExiste(login, mdp, u,&b);
}

int verifUserExiste(char *login, char *mdp, USER user, int *a)
{
    FILE *f;
    f = fopen("user.txt", "rb");
    while (fscanf(f, "%d %s %s %d\n",&user.id, user.login, user.motDePasse, &user.typeUtilisateur) != EOF)
    {
        *a = user.id;
        if (strcmp(user.login, login) == 0 && strcmp(user.motDePasse, mdp) == 0)
        {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int connexionUser(char *login, char *mdp, USER U[], int nu, int *a)
{
    int c,d;
    for (int i = 0; i < nu; i++)
    {
        c = verifUserExiste(login, mdp, U[i],&d);
        if (c == 1)
        {
            *a = d;
            return d;
        }
    }
    if (c != 1)
    {
        return 0;
    }
}
int reponse()
{
    int r;
    printf("Voudrez-vous recommencer ? Si oui tapez 1 si non tapez 0\n");
    do
    {
        scanf("%d", &r);
        if (r != 0 && r != 1)
        {
            printf("Veuillez choisir une réponse valable. Si oui tapez 1 si non tapez 0\n");
        }

    } while (r != 0 && r != 1);

    if (r == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void enregistrerEtu(ETUDIANT E[], int ne)
{
    FILE *file = fopen("etudiant.txt", "w");
    if (file == NULL)
    {
        printf("Impossible d'ouvrir un fichier etudiant.txt\n");
    }

    for (int i = 0; i < ne; i++)
    {
        fprintf(file, "%d %s %s %s %s %d %d %d %d\n", E[i].id, E[i].nom, E[i].prenom, E[i].code, E[i].user.login, E[i].nbPresences, E[i].minutesretardtotal, E[i].estBloque, E[i].nbAbsences);
    }

    fclose(file);
}