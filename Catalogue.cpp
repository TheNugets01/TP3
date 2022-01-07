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
#include <cstring>
using namespace std;

//------------------------------------------------------ Include personnel

#include "Catalogue.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes

#define TAILLEBUFFER 100
#define VIDEBUFFERCLAVIER() char ch; while( (ch = getchar() != '\n') && ch != EOF );

//----------------------------------------------------------------- PUBLIC

typedef struct
{
    char * Nom = nullptr;
    char * Parent = nullptr;
}DataVille;

//----------------------------------------------------- Fonctions Ordinaires

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

char * Ajuster(char * aAjuster)
{
    char * ajuste = new char[strlen(aAjuster)+1];
    strcpy( ajuste , aAjuster );
    return ajuste;
}//---- Fin de Ajuster

bool ExistanceFichier(const string& name){
    ifstream f(name.c_str());
    return f.good();
}//---- Fin de ExistanceFichier

//----------------------------------------------------- Méthodes publiques

ListeChainee * Catalogue::GetListeParcours()
{
    return listeParcours;
}

void Catalogue::Sauvegarde()
// Cette méthode permet d'importer des données du Catalogue dans un fichier
{
    // int mode = 0;
    string lecture;
    cout << " --- Menu de Sauvegarde --- " << endl;
    cout << "Dans quel fichier voulez vous faire votre sauvegarde" << endl;
    cin >> lecture;
    ofstream dest ( lecture );
    cout << endl;

    cout << endl << "Quel type de sauvegarde voullez vous effectuez" << endl;
    cout << "- 1 : L'integralité du Catalogue " << endl;
    cout << "- 2 : Selon le type de trajet " << endl;
    cout << "- 3 : Selon la ville de depart et/ou d'arrivee " << endl;
    cout << "- 4 : Selon l'index du trajet " << endl << ">> ";

    cin >> lecture;

    GetListeParcours()->Sauvegarde( dest , lecture);
}//----- Fin de Sauvegarde

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

void Catalogue::LireFichier(ifstream & src, char typeTrajet)
{
    char depart[TAILLEBUFFER];
    char arrive[TAILLEBUFFER];
    char moyen[TAILLEBUFFER];
    if(typeTrajet=='S')
    {
        src.getline(depart,TAILLEBUFFER,',');
        src.getline(moyen,TAILLEBUFFER,',');
        src.getline(arrive,TAILLEBUFFER,'\n');
        Inserer(new TrajetSimple(Ajuster(depart),Ajuster(arrive),Ajuster(moyen)));
    }
    else if(typeTrajet=='C')
    {
        src.getline(depart,TAILLEBUFFER,',');
        src.getline(moyen,TAILLEBUFFER,',');
        src.getline(arrive,TAILLEBUFFER,',');
        ListeChainee * tc = new ListeChainee();
        tc -> AjouterFin(new TrajetSimple(Ajuster(depart),Ajuster(arrive),Ajuster(moyen)));
        while(src.peek()!='\n' && src.peek()!=EOF)
        {
            strcpy(depart,arrive);
            src.getline(moyen,TAILLEBUFFER,',');
            src.getline(arrive,TAILLEBUFFER,',');
            tc -> AjouterFin(new TrajetSimple(Ajuster(depart),Ajuster(arrive),Ajuster(moyen)));
            if(src.eof())
                cout << "Bloqué4" << endl;
        }
        Inserer(new TrajetCompose(tc));
        if(!src.eof())
        {
            src.ignore(TAILLEBUFFER,'\n');
        }
    }
}

void Catalogue::Import()
// Cette méthode permet d'importer les donné contenu dans un fichier dans le catalogue
{
    bool succeed = false;
    bool created = false;
    string nfile;
    cout << "Quel est le nom de la sauvegarde que vous voulez importer ?" << endl;
    while(!created)
    {
        cin >> nfile;
        if(ExistanceFichier(nfile))
        {
            created = true;
        }
        else
        {
            cout << "Ce nom de fichier n'existe pas veuillez reessayer " << endl;
        }
    }
    ifstream src (nfile, ios_base::in);
    cout << "Quel type d'import voulez vous effectuer ?" << endl;
    cout << "- 1 : Sans critere de selection " << endl;
    cout << "- 2 : Selon le type de trajet " << endl;
    cout << "- 3 : Selon la ville de depart et/ou d'arrivee " << endl;
    cout << "- 4 : Selon l'index du trajet " << endl << ">> ";
    char lecture;
    cin >> lecture;
    if(lecture == '1') // import tout
    {
        char type;
        while(!src.eof())
        {
            src.get(type);
            src.ignore(TAILLEBUFFER,';');
            LireFichier(src,type);
            succeed = true;
        }
    }
    else if(lecture=='2')//import par type de trajet
    {
        bool bonChoix = false;
        cout << "Quel type de Trajet voulez vous importer ? (Tapez S ou C)" << endl;
        char choix;
        while(!bonChoix)
        {
            cin >> choix;
            if(choix == 'C' || choix == 'S')
            {
                bonChoix = true;
            }
            else
            {
                cout << "je n'ai pas compris veuillez reessayer " << endl;
            }
        }
        char type;
        while(!src.eof())
        {
            src.get(type);
            src.ignore(TAILLEBUFFER,';');
            if(type==choix)
            {
                LireFichier(src,type);
            }
            else
            {
                src.ignore(TAILLEBUFFER,'\n');
            }
        }
        succeed = true;
    }
    else if(lecture=='3')// import par Ville de depart et/ou arrive
    {
        cout << "Indiquez votre ville de depart (ou -1 si import par ville d'arrivee)" << endl;
        string choixDepart;
        cin >> choixDepart;
        string choixArrivee;
        if(choixDepart!="-1")
        {
            cout << "Indiquez votre ville d'arrive (ou -1 si uniquement par depart)" << endl;
        }
        else
        {
            cout << "Indiquez votre ville d'arrivee : " << endl;
        }
        cin >> choixArrivee;
        while(!src.eof())
        {
            string depart;
            string arrivee;
            char type;
            src.get(type);
            src.ignore(TAILLEBUFFER,',');
            getline(src,depart,',');
            getline(src,arrivee,';');
            if((choixDepart == depart && (choixArrivee == arrivee || choixArrivee=="-1")) || (choixArrivee==arrivee && choixDepart=="-1"))
            {
                LireFichier(src,type);
            }
            else
            {
                src.ignore(TAILLEBUFFER,'\n');
            }
        }
        succeed = true;
    }
    else if(lecture == '4') // import par intervalle de trajet
    {
        int n;
        int m;
        int ligneLu = 1;
        cout << "Quel est le premier trajet que vous voulez importer ?" << endl;
        cin >> n;
        cout << "Quel est le dernier trajet que vous voulez importer ?" << endl;
        cin >> m;
        char type;
        while(!src.eof())
        {
            if(ligneLu >= n && ligneLu <= m)
            {
                src.get(type);
                src.ignore(TAILLEBUFFER,';');
                LireFichier(src,type);
            }
            else
            {
                src.ignore(TAILLEBUFFER,'\n');
            }
            ++ligneLu;
        }
        succeed = true;
    }
    else
    {
        cout << "je n'ai pas compris veuillez reessayer" << endl;
    }
    if(succeed)
    {
        cout << "Bravo vos trajets ont ete importes dans le catalogue ! " << endl;
    }
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