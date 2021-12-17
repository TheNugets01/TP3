#include "Catalogue.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include <iostream>
#include <cstring>

using namespace std;

#define TAILLEBUFFER 100
#define VIDEBUFFERCLAVIER() char ch; while( (ch = getchar() != '\n') && ch != EOF );

char * Saisi(); //Extension de la portée sinon double definition
void Menu(Catalogue * catalogue);
void AfficheMenu();

int main()
{
    cout << "----- Bienvenue dans notre Agence de Voyage -----" << endl << endl;
    Catalogue * notreCatalogue = new Catalogue();
    Menu(notreCatalogue);
    
    delete notreCatalogue;

    return 0;
}

char * Saisi( )
// Algorithme : Permet de saisir une chaine de caractère au clavier et de la ranger dans une zone alloué dynamiquement
{
    char unMot[TAILLEBUFFER];
    cin >> unMot;

    char * leMot = new char[strlen(unMot)+1];
    strcpy( leMot , unMot );
    
    if(strcmp(leMot,"-1") != 0)
    {
        VIDEBUFFERCLAVIER();
    }
    
    return leMot;
} //----- Fin de Saisi

void Menu(Catalogue * catalogue)
// Algorithme : Permet d'afficher le menu et de gerer les interactions avec l'utilisateur
//
{   
    char lecture;
    AfficheMenu();
    cin >> lecture;
    while (lecture != 'q')
    {
        if (lecture== '1')
        {
            VIDEBUFFERCLAVIER();
            bool estTC = false;
            ListeChainee * tc;

            // On recolte les informations du premier trajet

            cout << "Veuillez indiquez votre Ville de depart" << endl << ">> ";
            char * depart = Saisi();
            cout << "Quel est la prochaine destination ?" << endl << ">> ";
            char * arrive = Saisi();
            cout << "Par quel moyen de transport ?" << endl << ">> ";
            char * transport = Saisi();
            Trajet * t1 = new TrajetSimple(depart,arrive,transport);

            cout << "Quel est la prochaine destination ? (Si Fini tapez -1)" << endl << ">> ";
            depart = new char[ strlen(arrive) + 1 ];
            strcpy(depart,arrive);
            arrive = Saisi();

            // Si il y en a d'autres c'est donc un TC -> on rentre dans le while

            while(strcmp(arrive,"-1")!=0)
            {
                if(!estTC) // Si premiere fois qu'on rentre dans le while on initialise la liste et on insere le premier trajet
                {
                    tc = new ListeChainee();
                    tc->AjouterFin(t1);
                    estTC = true;
                }
                cout << "Par quel moyen de transport ?" << endl << ">> ";
                transport = Saisi();
                tc->AjouterFin( new TrajetSimple(depart,arrive,transport) );

                // on demande le prochain trajet à la fin du while pour savoir si on continue ou pas

                cout << "Quel est la prochaine destination ? (Si Fini tapez -1)" << endl << ">> ";
                depart = new char[ strlen(arrive) + 1 ];
                strcpy(depart,arrive);
                arrive = Saisi();
            }

            if(!estTC) // Si il n'y avait qu'un trajet on insere le premier trajet dans le catalogue
            {
                catalogue->Inserer(t1);
            }
            else // Sinon on insere le trajet composee de la liste creer dans le while
            {
                catalogue->Inserer(new TrajetCompose(tc));
            }

            delete[] arrive; // A la fin on delete nos pointeurs de depart et d'arrive que l'on a initialise mais pas utilise
            delete[] depart;
            // pas de delete sur le moyen de transport car on les a mis dans un trajet
        }
        else if (lecture== '2')
        {
            if( catalogue->GetListeParcours()->GetDebut() != nullptr)
            {
                VIDEBUFFERCLAVIER();
                catalogue -> Afficher();
                cout << endl;
                cout << "Pour retourner au menu entrez un charactere" << endl << ">> ";
                char c;
                cin >> c;
            }
            else
            {
                cout << "Votre Catalogue est vide" << endl;
            }
        }
        else if (lecture== '3')
        {
            if( catalogue->GetListeParcours()->GetDebut() != nullptr)
            {
                VIDEBUFFERCLAVIER();

                cout << "D'ou voulez vous partir ?" << endl << ">> ";
                const char * unDepart = Saisi();
                cout << "Pour arriver ou ?" << endl << ">> ";
                const char * uneArrivee = Saisi();

                catalogue -> Rechercher( unDepart , uneArrivee );
                cout << endl;
                cout << "Pour retourner au menu entrez un charactere" << endl << ">> ";
                char c;
                cin >> c;
            }
            else
            {
                cout << "Votre Catalogue est vide" << endl;
            }
        }
        else if(lecture =='4')
        {
            catalogue -> Import();
        }
        else
        {
            cout << "Je n'ai pas compris veuillez recommencer !" << endl;
        }

        VIDEBUFFERCLAVIER();
        AfficheMenu();
        cin >> lecture;
    }
} //----- Fin de Menu

void AfficheMenu()
{
    cout << endl << "Veuillez choisir une Action :" << endl;
    cout << "- 1 : Ajouter un trajet au catalogue" << endl;
    cout << "- 2 : Afficher le catalogue" << endl;
    cout << "- 3 : Rechercher dans le cataloge " << endl;
    cout << "- 4 : Importer une sauvegarde dans le Catalogue " << endl;
    cout << "- q : Quitter" << endl << ">> ";
}