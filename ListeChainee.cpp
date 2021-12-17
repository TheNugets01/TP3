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

//----------------------------------------------------- Méthodes publiques
void NouveauEnSuite(  Trajet * contenu , Maillon * actuelle)
{
  Maillon * nouveau = new Maillon(contenu);
  
  Maillon * MemSuivant = actuelle->GetProchain();

  nouveau -> SetProchain( MemSuivant );
  actuelle -> SetProchain( nouveau );
}



void ListeChainee::Sauvegarde( ofstream & dest, int mode )
{
  Maillon * actuelle = debut;
  if(mode == 1)
  {
    while( actuelle != nullptr)
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

void ListeChainee::Afficher ( int mode ) const
{
  #ifdef MAP
      cout << "Appel a la fonction Afficher() de <ListeChainee>" << endl;
  #endif
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

