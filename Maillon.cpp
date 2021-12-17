/*************************************************************************
                           Maillon  -  implémente le Maillon d'une liste chainée
                             -------------------
    début                : 19/11/2021
    copyright            : (C) 2021 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

// -- Réalisation de la classe <Maillon> (fichier Maillon.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Maillon.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
const Trajet * Maillon::GetTrajet() const
{
  return trajet;
} //----- Fin de GetTrajet

Maillon * Maillon::GetProchain() const
{
  return prochain;
} //----- Fin de GetProchain

void Maillon::SetTrajet( Trajet * unTrajet )
{
  trajet = unTrajet;
} //----- Fin de SetTrajet

void Maillon::SetProchain( Maillon * unProchain )
{
  prochain = unProchain;
} //----- Fin de SetProchain

//-------------------------------------------- Constructeurs - destructeur
Maillon::Maillon ( Trajet * contenu ) : trajet(contenu) , prochain(nullptr)
{
  #ifdef MAP
      cout << "Appel au constructeur de <Maillon>" << endl;
  #endif
} //----- Fin de Maillon


Maillon::~Maillon ( )
{
  #ifdef MAP
      cout << "Appel au destructeur de <Maillon>" << endl;
  #endif

  if ( prochain != nullptr )
  {
    delete prochain;
  }
  
  delete trajet;
  
} //----- Fin de ~Maillon


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
