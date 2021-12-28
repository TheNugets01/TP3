/*************************************************************************
                           ListeChainee  -  implemente une liste chainee
                             -------------------
    début                : 19/11/2021
    copyright            : 2021 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

// -- Réalisation de la classe <ListeChainee> (fichier ListeChainee.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//------------------------------------------------------ Include personnel
#include "ListeChainee.h"
//--------------------------------------------------------------Constantes

//------------------------------------------------------------------PUBLIC

//--------------------------------------------------- Fonctions Ordinaires

string convertToString(char* a)
{
    int size =0;
    for (size = 0; a[size]!= '\0' ; ++size){}
    string s = "";

    for (int i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

//----------------------------------------------------- Méthodes publiques
void NouveauEnSuite(  Trajet * contenu , Maillon * actuelle)
{
  Maillon * nouveau = new Maillon(contenu);
  
  Maillon * MemSuivant = actuelle->GetProchain();

  nouveau -> SetProchain( MemSuivant );
  actuelle -> SetProchain( nouveau );
}



void ListeChainee::Sauvegarde( ofstream & dest, string mode )
{
  Maillon * actuelle = debut;

  if( mode == "1")//Sauvegarde du Catalogue
  {
    while( actuelle != nullptr)
    {
      dest << actuelle->GetTrajet()->Afficher(2) << endl ;
      actuelle = actuelle->GetProchain();
    }
  }
  else if( mode == "2")
  {
    string type;
    do{
      cout << "Quel type souhaitez vous sauvegarde" << endl;
      cout << "- S : les trajets simples" << endl;
      cout << "- C : les trajets composes" << endl << ">> ";
      cin >> type;
    }while( type != "S" && type != "C");

    string typeTrajet = "T"+type;

    while( actuelle != nullptr)
    {
      if( actuelle->GetTrajet()->type() == type )
      {
        dest << actuelle->GetTrajet()->Afficher(2) << endl ;
      }
      actuelle = actuelle->GetProchain();
    }
  }
  else if( mode == "3")
  {
    cout << "Indiquez votre ville de depart (ou -1 si import par ville d'arrivee)" << endl;
    string choixDepart;
    cin >> choixDepart;
    string choixArrivee;
    if(choixDepart != "-1")
    {
      cout << "Indiquez votre ville d'arrive (ou -1 si uniquement par depart)" << endl;
    }
    else
    {
      cout << "Indiquez votre ville d'arrivee : " << endl;
    }
    cin >> choixArrivee;

    while(actuelle != nullptr)
    {
      if( (choixDepart == convertToString( actuelle->GetTrajet()->GetVilleDepart() ) && (choixArrivee == convertToString( actuelle->GetTrajet()->GetVilleArrivee() ) || choixArrivee=="-1")) 
            || (choixArrivee== convertToString( actuelle->GetTrajet()->GetVilleArrivee() ) && choixDepart=="-1"))
      {
        dest << actuelle->GetTrajet()->Afficher(2) << endl ;
      }
      
      actuelle = actuelle->GetProchain();
    }
  }
  else if( mode == "4")
  {
    cout << "Debut de l'intervalle de selection" << endl;
    int n;
    cin >> n;

    cout << "Fin de l'intervalle de selection" << endl;
    int m;
    cin >> m;

    int LigneLu = 1;
    while( LigneLu != n )
    {
      actuelle = actuelle->GetProchain();
      ++LigneLu;
    }

    for(int i = 0 ; i <= m-n ; ++i)
    {
      dest << actuelle->GetTrajet()->Afficher(2) << endl ;
      actuelle = actuelle->GetProchain();
    }
  }
}


Maillon * ListeChainee::GetDebut() const
{
  return debut;
} //----- Fin de GetDebut

Maillon * ListeChainee::GetFin() const
{
  return fin;
} //----- Fin de GetFin

int ListeChainee::GetNbMaillon() const
{
  return nbMaillon;
}

void ListeChainee::AjouterTri( Trajet * contenu )
{
  #ifdef MAP
      cout << "Appel a la fonction AjouterTri de <ListeChainee>" << endl;
  #endif

  if ( debut == nullptr )
  //Si la chaine est vide
  {
    debut = new Maillon(contenu);
    fin = debut;
    ++nbMaillon;
  }
  else
  {
    Maillon * actuelle = debut;

    if( actuelle == debut && strcmp( contenu->GetVilleDepart() , actuelle->GetTrajet()->GetVilleDepart() ) <= 0 )
    //Si on est debut il y a potentiellement un ajout en debut
    {
      if( strcmp( contenu->GetVilleDepart() , actuelle->GetTrajet()->GetVilleDepart() ) == 0 
          && strcmp( contenu->GetVilleArrivee() , actuelle->GetTrajet()->GetVilleArrivee()  ) > 0 )
      // Cas ou l'ajout ne se fait pas avant
      {
        if(actuelle->GetProchain() != nullptr )
        {
          NouveauEnSuite( contenu , actuelle );
          ++nbMaillon;
        }
        else
        {
          AjouterFin( contenu );
        }
      }
      else
      {
        AjouterDeb(contenu);
      }
    }
    else
    {
      bool ajout = false;

      while(!ajout)
      {
        if( actuelle->GetProchain() != nullptr )
        {
          if( strcmp ( contenu->GetVilleDepart() , actuelle->GetProchain()->GetTrajet()->GetVilleDepart() ) < 0 
              //Si on est avant dans le tri alphabetique par rapport au départ ^^^^^^^
              || ( strcmp( contenu->GetVilleDepart() , actuelle->GetProchain()->GetTrajet()->GetVilleDepart() ) == 0 
              && strcmp( contenu->GetVilleArrivee() , actuelle->GetProchain()->GetTrajet()->GetVilleArrivee() ) < 0 ) )
              //Si on a les mêms départ et qu'on est avant dans le tri alphabetique par rapport a l'arrivée ^^^^^^^
          {
            NouveauEnSuite( contenu , actuelle );
            ajout = true;
            ++nbMaillon;
          }
          else
          {
            actuelle = actuelle->GetProchain();
          }
        }
        else
        {
          AjouterFin( contenu );
          ajout = true;
        }
      }
    }
  }
}//---- Fin de Ajouter Tri

void ListeChainee::AjouterDeb( Trajet * contenu )
{
  #ifdef MAP
      cout << "Appel a la fonction AjouterDeb de <ListeChainee>" << endl;
  #endif

  ++nbMaillon;

  if(debut == nullptr) // Si liste vide on place le nouveau maillon en debut et fin
  {
    debut = new Maillon(contenu);
    fin = debut;
  }
  else // Sinon on le place en debut de liste
  {
    Maillon * nouveau = new Maillon(contenu);
    nouveau -> SetProchain( debut );
    debut = nouveau;
  }
} //----- Fin de AjouterDeb


void ListeChainee::AjouterFin( Trajet * contenu )
{
  #ifdef MAP
      cout << "Appel a la fonction AjouterFin de <ListeChainee>" << endl;
  #endif
  
  ++nbMaillon;

  if(debut == nullptr) // Si liste vide on place le nouveau maillon en debut et fin
  {
    debut = new Maillon(contenu);
    fin = debut;
  }
  else // Sinon on le place en fin de liste
  {
    Maillon * nouveau = new Maillon(contenu);
    fin->SetProchain(nouveau);
    fin = nouveau;
  }
} //----- Fin de AjouterFin

string ListeChainee::Afficher ( int mode ) const
{
  #ifdef MAP
      cout << "Appel a la fonction Afficher() de <ListeChainee>" << endl;
  #endif

  string Affichage ="";

  if ( mode == 0)
  {
    Maillon * courant = debut;
    while( courant->GetProchain() != nullptr )
    {
      courant -> GetTrajet()->Afficher();
      courant = courant->GetProchain();
    }
    courant->GetTrajet()->Afficher();
  }
  else if (mode == 1 )
  {
    Maillon * courant = debut;
    while( courant != nullptr )
    {
      courant -> GetTrajet()->Afficher(mode);
      courant = courant->GetProchain();
    }
  }
  else if (mode == 2 )
  {
    Maillon * courant = debut;
    while( courant != nullptr )
    {
      Affichage = Affichage + (courant -> GetTrajet()->Afficher(mode+1));
      courant = courant->GetProchain();
    }

    return Affichage;
  }

  return Affichage = "Cout";
} //----- Fin de Afficher

//---------------------------- Constructeurs - destructeur
ListeChainee::ListeChainee ( )
{
  #ifdef MAP
      cout << "Appel au constructeur de <ListeChainee>" << endl;
  #endif

  debut = nullptr;
  fin = debut;
  nbMaillon = 0;

} //----- Fin de ListeChainee


ListeChainee::~ListeChainee ( )
{
  #ifdef MAP
      cout << "Appel au destructeur de <ListeChainee>" << endl;
  #endif

  delete debut; // Detruit le premier maillon de la liste (les autres seront detruit en cascade par ~Maillon)
} //----- Fin de ~ListeChainee


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées

