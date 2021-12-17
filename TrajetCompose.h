/*************************************************************************
                           TrajetCompose  -  interface de la classe TrajetCompose
                             -------------------
    début                : 19/11/2021
    copyright            : (C) 2021 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h) ----------------
#if ! defined ( TRAJETCOMPOSE_H )
#define TRAJETCOMPOSE_H

//--------------------------------------------------- Interfaces utilisées

#include "ListeChainee.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <TrajetCompose>
//
// TrajetCompose est une liste de trajet simple
//
//------------------------------------------------------------------------

class TrajetCompose : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    string Afficher( int mode = 0 ) const;
    // Mode d'emploi :
    // Affiche le contenu du trajetCompose

//----------------------------------------------------------------Getteur

    char * GetVilleDepart() const;
    // Mode d'emploi :
    // Renvoie la ville de depart du trajetcompose
    char * GetVilleArrivee() const;
    // Mode d'emploi :
    // Renvoie la ville d'arrivee du trajetcompose

//-------------------------------------------- Constructeurs - destructeur

    TrajetCompose (ListeChainee * trajets);
    // Mode d'emploi :
    // Construit le trajetcompose a partir de la liste de trajet en parametre

    virtual ~TrajetCompose ( );
    // Mode d'emploi :
    // Detruit le trajetcompose

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    ListeChainee * listeTrajets;
};

#endif // TrajetCompose_H

