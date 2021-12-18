/*************************************************************************
                           TrajetCompose  -  implemente un TrajetCompose
                             -------------------
    début                : 19/11/2021
    copyright            : (C) 2021 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

// -- Réalisation de la classe <TrajetCompose> (fichier TrajetCompose.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel

#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

string TrajetCompose::Afficher( int mode ) const
{
  #ifdef MAP
      cout << "Appel a l'Afficheur() <TrajetCompose>" << endl;
  #endif

  cout << "Trajet Composee de : " << endl;
  listeTrajets->Afficher( 1 );
  cout << endl;
  return "void";
} //----- Fin de Afficher

//----------------------------------------------------------------Getteur

char * TrajetCompose::GetVilleDepart() const
{
  #ifdef GETSET
    cout << "Appel a GetVilleDepart de <TrajetCompose>" << endl;
  #endif

  return listeTrajets->GetDebut()->GetTrajet()->GetVilleDepart();
} //----- Fin de GetVilleDepart

char * TrajetCompose::GetVilleArrivee() const
{
  #ifdef GETSET
    cout << "Appel a GetVilleArrivee de <TrajetCompose>" << endl;
  #endif

  return listeTrajets->GetFin()->GetTrajet()->GetVilleArrivee();
} //----- Fin de GetVilleArrive

//-------------------------------------------- Constructeurs - destructeur
TrajetCompose::TrajetCompose (ListeChainee * trajets)
{
  #ifdef MAP
      cout << "Appel au constructeur de <TrajetCompose>" << endl;
  #endif
  listeTrajets = trajets;
} //----- Fin de TrajetCompose


TrajetCompose::~TrajetCompose ( )
{
  #ifdef MAP
      cout << "Appel au destructeur de <TrajetCompose>" << endl;
  #endif
  
  delete listeTrajets;
} //----- Fin de ~TrajetCompose


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées