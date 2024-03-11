void menuAdmin()
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

        if (option == 2)
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

        if (option == 3)
        {
            //marquerpresence();
        }

        if (option == 4)
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
        /*if (option==5)
        {
            return 1;
        }*/
        
    } while (option != 5);
}

void menuEtudiant()
{
    int option;
    do
    {
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
            int marquerpresence() {

            }
        }

        if (option == 2)
        {
            // nbrdeminutedabscence
        }

        if (option == 3)
        {
            // messages
        }
        /*if (option=4)
        {
            return 1;
        }*/
        
    } while (option != 4);
}