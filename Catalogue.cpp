/*************************************************************************
                           Catalogue  -  implemente un Catalogue
                             -------------------
    début                : 19/11/2021
    copyright            : (C) 2021 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

// -- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//------------------------------------------------------ Include personnel

#include "Catalogue.h"

//------------------------------------------------------------- Constantes

#define TAILLEBUFFER 100
#define VIDEBUFFERCLAVIER() char ch; while( (ch = getchar() != '\n') && ch != EOF );

//----------------------------------------------------------------- PUBLIC

typedef struct
{
    char * Nom = nullptr;
    char * Parent = nullptr;
}DataVille;

//----------------------------------------------------- Méthodes publiques

const ListeChainee * const Catalogue::GetListeParcours()
{
    return listeParcours;
}

static bool explore( const char * , const char * , DataVille * , int , Maillon * );
//Fonction d'exploration pour la recherche avancé

void Catalogue::Inserer( Trajet * aInserer)
{
    listeParcours->AjouterTri( aInserer );
} //----- Fin de Inserer

void Catalogue::Afficher () const
{
    cout << "Voici notre Catalogue de Trajets :" << endl;
    listeParcours->Afficher();
} //----- Fin de Afficher

void Catalogue::Rechercher (const char * unDepart , const char * uneArrivee , int mode ) const
    // Algorithme :
    // On parcourt la liste de trajet et on verifie si le depart et l'arrivee correspondent a ceux passe en parametre
{
    bool Find = false; // permet d'afficher la bonne phrase d'intro et qu'une seule fois
    const Trajet * temp;
    Maillon * courant = listeParcours->GetDebut();

    while( courant != nullptr )
    {
        temp = courant -> GetTrajet();
        if(strcmp(temp->GetVilleDepart() , unDepart ) == 0 && strcmp( temp->GetVilleArrivee() , uneArrivee ) == 0 )
        {
            if(Find == false && mode == 0)
            {
                cout << "Vous voulez voyager entre " << unDepart << " et " << uneArrivee <<  ", Voila nos propositions :" << endl;
                Find = true;
            }

            temp->Afficher();
        }
        courant = courant->GetProchain();
    }

    if( Find == false && mode == 0)
    // Si on à pas trouver on tente une autre méthode de recherche
    {
        RechercherProfondeur( unDepart , uneArrivee );
    }

    if(mode == 0)
    {
        delete[] unDepart; // Il faut detruite les pointeurs que l'on a creer lors de la saisie
        delete[] uneArrivee;
    }

} //----- Fin de Rechercher

void Catalogue::RechercherProfondeur(const char * unDepart , const char * uneArrivee ) const
// Algorithme : 1. On part de la ville de depart on la marque commde déjà visité
//              2. On recupere les destinations que l'ont peut atteindre
//              3. On rehitere l'operation sur toutes les villes atteignable non visité jusque trouvé l'arrivé
//
{
    #ifdef MAP
        cout << "Appel a la méthode RechercherProfondeur de <Catalogue> pour " << unDepart << endl;
    #endif

    const int NbMaillon = listeParcours->GetNbMaillon();
    DataVille * Ville = new DataVille[ NbMaillon * 2 ];
    cout << NbMaillon << endl;
    int VilleUnique = 0;
    bool RedondanceVille;
    bool Find = false;

    Maillon * debutListe = listeParcours->GetDebut();

    Maillon * actuelle = debutListe;

    while( actuelle != nullptr )
    // Parcour du catalogue
    {
        RedondanceVille = false;
        for(int i = 0 ; i < VilleUnique ; ++i)
        // Parcours des datas par ville
        {
            if( strcmp(actuelle->GetTrajet()->GetVilleDepart() , Ville[i].Nom) == 0
              ||strcmp(actuelle->GetTrajet()->GetVilleArrivee() , Ville[i].Nom) == 0 )
            // On verifie que la ville n'existe pas déjà
            {
                RedondanceVille = true;
            }

        }

        if( !RedondanceVille )
        // Si la ville n'existe pas on l'ajoute
        {   
            Ville[ VilleUnique ].Nom = new char[ strlen( actuelle->GetTrajet()->GetVilleDepart() ) + 1];
            strcpy( Ville[VilleUnique].Nom , actuelle->GetTrajet()->GetVilleDepart() );

            if (strcmp( Ville[ VilleUnique ].Nom, unDepart) == 0 )
            // Remplir la case Parent du départ pour eviter d'y passer deux fois
            {
                Ville[ VilleUnique ].Parent = new char[ strlen( "PointDeDepart" ) + 1 ];
                strcpy( Ville[ VilleUnique ].Parent , "PointDeDepart");
            }
            
            ++VilleUnique;
        }

        actuelle = actuelle->GetProchain();
    }

    Find = explore( unDepart , uneArrivee , Ville , VilleUnique , debutListe );

    //Afficher le Parcours
    const char * BufferArrivee;
    BufferArrivee = uneArrivee;

    if( Find )
    {
        cout << "Vous pouvez voyager de " << unDepart << " à " << uneArrivee << " en faisant :"<< endl ;
        while( strcmp( BufferArrivee , unDepart ) != 0 )
        {
            for(int i = 0 ; i < VilleUnique ; ++i)
            {
                if( strcmp( BufferArrivee , Ville[i].Nom ) == 0)
                {
                    Rechercher( Ville[i].Parent , Ville[i].Nom , 1);
                    BufferArrivee = Ville[i].Parent;
                }
            }
        }
    }
    else
    {
        cout << " Nous n'avons pas trouvé de trajet ou combinaison de trajets corespondant a votre recherche" << endl;
    }
    
    //Detruit les char * dans Ville

    for(int i = 0 ; i < VilleUnique ; ++i)
    //Destroy
    {
        delete[] Ville[i].Nom;

        if(Ville[i].Parent != nullptr )
        {
            delete[] Ville[i].Parent;
        }

    }

    delete[] Ville;
    
}//----- Fin de RechercherProfondeur

static bool explore( const char * unDepart, const char * uneArrivee , DataVille * Ville , int VilleUnique, Maillon * debutListe)
{
    #ifdef MAP
        cout << "Appel a la fonction ordinaire explore de <Catalogue> pour " << unDepart << endl;
    #endif

    Maillon * actuelle = debutListe;
    bool Find = false;

    while( actuelle != nullptr )
    // Parcours du Catalogue
    {
        if( strcmp( actuelle->GetTrajet()->GetVilleDepart() , unDepart ) == 0 )
        // On trouve les Enfants du depart actuelle
        {
            for( int i = 0 ; i < VilleUnique ; ++i)
            // Parcours les villes
            {
                if( strcmp( actuelle->GetTrajet()->GetVilleArrivee() , Ville[i].Nom ) == 0 && Ville[i].Parent == nullptr )
                // Retrouve l'enfant dans ville
                {
                    if ( strcmp( uneArrivee , Ville[i].Nom) == 0)
                    {
                        Ville[i].Parent = new char[ strlen( unDepart ) + 1 ];
                        strcpy( Ville[i].Parent , unDepart );
                        // debuger : cout << "/ " << "OUI!" << " /" ;
                        return Find = true;
                    }
                    else if( Ville[i].Parent == nullptr )
                    {
                        Ville[i].Parent = new char[ strlen( unDepart ) + 1 ];
                        strcpy(Ville[i].Parent , unDepart);

                        // Exploration recursive des enfants
                        Find = explore( Ville[i].Nom , uneArrivee , Ville , VilleUnique , debutListe );

                        if(Find)
                        // On stop la recherche
                        {
                            return Find;
                        }
                    }
                    
                }
            }
        }

        actuelle = actuelle->GetProchain();
    }

    return Find;
}//----- Fin de explore

void Catalogue::Import()
{
    /*string nfile;
    cout << "Quel est le nom de la sauvegarde que vous voulez importer ?" << endl;
    cin >> nfile;
    ifstream src (nfile, ios_base::in);
    cout << "Quel type d'import voulez vous effectuer ?" << endl;
    char lecture = '1';
    //cin >> lecture;
    if(lecture == '1') // import tout
    {
        string c;
        char[100] depart;
        string arrive;
        string moyen;
        char type;
        while(!src.eof())
        {
            src.get(type);
            if(type=='S')
            {
                src.get(depart,100,',');
                src.get(arrive,100,',');
                src.get(moyen,100,',');
                Ajuster(depart);
                Inserer(new TrajetSimple(depart.c_str(),arrive.c_str(),moyen.c_str()));
            }
        }
    }*/
}//----- Fin de Import

//-------------------------------------------- Constructeurs - destructeur
Catalogue::Catalogue()
{
    #ifdef MAP
        cout << "Appel au constructeur de <Catalogue>" << endl;
    #endif

    listeParcours = new ListeChainee();
} 

Catalogue::~Catalogue()
{
    #ifdef MAP
        cout << "Appel au destructeur de <Catalogue>" << endl;
    #endif

    delete listeParcours; // Son contenu est detruit en cascade par les autres destructeurs
} //----- Fin de ~Catalogue
//----- Fin de Catalogue


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées