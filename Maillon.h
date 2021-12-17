/*************************************************************************
                           Maillon  -  interface de la classe Maillon
                             -------------------
    début                : 19/11/2021
    copyright            : (C) 2021 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Maillon> (fichier Maillon.h) ----------------
#if ! defined ( MAILLON_H )
#define MAILLON_H

//--------------------------------------------------- Interfaces utilisées

#include "Trajet.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
// Rôle de la classe <Maillon>
//
// Maillon est un element de la liste chainee

class Maillon
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
//-----------------------------------------------Getteur
    const Trajet * GetTrajet() const;
    // Mode d'emploi :
    // Renvoie le trajet contenu par le maillon
    Maillon * GetProchain() const;
    // Mode d'emploi :
    // Renvoie le maillon suivant
//-----------------------------------------------Setteur
    void SetTrajet( Trajet * unTrajet );
    // Mode d'emploi :
    // Modifie le trajet contenu par le maillon
    void SetProchain( Maillon * unProchain);
    // Mode d'emploi :
    // Modifie le pointeur vers le maillon suivant
//-------------------------------------------- Constructeurs - destructeur
    Maillon ( Trajet * contenu);
    // Mode d'emploi :
    // Construit un maillon à partir du trajet qu'il doit contenir
    virtual ~Maillon ( );
    // Mode d'emploi :
    // Détruit le maillon

protected:
//----------------------------------------------------- Méthodes protégées
//----------------------------------------------------- Attributs protégés
    const Trajet * trajet;
    Maillon * prochain;

};

#endif // MAILLON_H

