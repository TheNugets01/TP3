/*************************************************************************
                           Trajet  -  interface de la classe Trajet
                             -------------------
    début                : 19/11/2021
    copyright            : (C) 2021 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( TRAJET_H )
#define TRAJET_H

//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Trajet>
//
// La classe trajet permet de mettre des trajets simple et composee dans une meme collection
//
//------------------------------------------------------------------------

class Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    virtual void Afficher( int mode = 0 ) const = 0;
    // Mode d'emploi :
    // Affiche le contenu de la liste :
    // Par défaut mode = 0 : On affiche les trajets de manière classique
    // mode = 1 : On affiche les trajets simple au sein de trajets composees

//----------------------------------------------------------------Getteur

    virtual char * GetVilleDepart() const = 0;
    // Mode d'emploi :
    // Renvoie la ville de depart d'un trajet
    virtual char * GetVilleArrivee() const = 0;
    // Mode d'emploi :
    // Renvoie la ville de d'arrivee d'un trajet


//-------------------------------------------- Constructeurs - destructeur

    Trajet ();
    // Mode d'emploi :
    // Construit le trajet
    virtual ~Trajet ( );
    // Mode d'emploi :
    // Detruit le trajet
//------------------------------------------------------------------ PRIVE

protected:

//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
};

#endif // TRAJET_H

