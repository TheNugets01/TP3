/*************************************************************************
                           Catalogue  -  Interface de la classe Catalogue
                             -------------------
    début                : 19/11/2021
    copyright            : (C) 2021 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilisées

#include "ListeChainee.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Catalogue>
//
// Catalogue sert à lister tous les trajets existant puis à les manipuler via les méthodes d'insertion, d'affichage ou de recherche
//
//------------------------------------------------------------------------

class Catalogue
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    void Inserer( Trajet * unTrajet);
    // Mode d'emploi :
    // Permet d'insérer un Trajet au catalogue en le triant par ordre alphabétique
    void Afficher () const ;
    // Mode d'emploi :
    // Affiche le contenu courant du catalogue
    void Rechercher (const char * depart , const char * arrivee , int mode = 0 ) const;
    // Mode d'emploi :
    // Permet de rechercher un trajet par ville de départ et d'arrivee

    void RechercherProfondeur(const char * depart, const char * arrivee) const;
    // Mode d'emploi :
    // Permet de rechercher un itinéraire de plusieurs trajets par ville de départ et d'arrivee

    const ListeChainee * const GetListeParcours();
    // Mode d'emploi :
    // Permet d'acceder a la liste de parcours



//-------------------------------------------- Constructeurs - destructeur

    Catalogue();
    // Mode d'emploi : Donne en paramètre le contenu du Catalogue 
    // Construit le catalogue

    virtual ~Catalogue();
    // Mode d'emploi :
    // Détruit le catalogue

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
    ListeChainee * listeParcours;
};

#endif // CATALOGUE_H

