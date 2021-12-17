/*************************************************************************
                           TrajetSimple  -  implemente un TrajetSimple
                             -------------------
    début                : 19/11/2021
    copyright            : (C) 2021 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

// -- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp) --

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <iostream>
#include <cstring>
using namespace std;

//------------------------------------------------------ Include personnel

#include "TrajetSimple.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
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

string TrajetSimple::Afficher( int mode ) const
{
  if( mode == 0 )
  {
    cout << "Trajet Simple de : " << endl << " - " << villeDepart << " à " << villeArrivee << " en " << moyenTransport << endl << endl;
  }
  else if ( mode == 1 )
  {
    cout << " - " << villeDepart << " à " << villeArrivee << " en " << moyenTransport << endl;
  }
  else if ( mode == 2 )
  {
    string leDepart = convertToString(villeDepart);
    string lArrivee = convertToString(villeArrivee);
    string leMoyenTransport = convertToString(moyenTransport);

    string Ligne = "S;"+leDepart+','+leMoyenTransport+','+lArrivee;
    return Ligne;
  }

  return "void"; 
} //----- Fin de Afficher

//----------------------------------------------------------------Getteur

char * TrajetSimple::GetVilleDepart() const
{
  return villeDepart;
} //----- Fin de GetVilleDepart
char * TrajetSimple::GetVilleArrivee() const
// Algorithme : Permet d'accéder a la ville d'arrive du trajet
//
{
  return villeArrivee;
} //----- Fin de GetVilleArrivee

//-------------------------------------------- Constructeurs - destructeur
TrajetSimple::TrajetSimple (char * unDepart, char * uneArrivee, char * unTransport)
{
#ifdef MAP
    cout << "Appel au constructeur de <TrajetSimple>" << endl;
#endif
  villeDepart = unDepart;
  villeArrivee = uneArrivee;
  moyenTransport = unTransport;
} //----- Fin de TrajetSimple


TrajetSimple::~TrajetSimple ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <TrajetSimple>" << endl;
#endif
  delete[] villeDepart;
  delete[] villeArrivee;
  delete[] moyenTransport;
} //----- Fin de ~TrajetSimple


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
