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
#include <fstream>

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
    void Sauvegarde();
    // Mode d'emploi :
    // Permet de Sauvegarder l'intégralité ou une partie du Catalogue en fonction de différents critéres
    void Import();
    // Mode d'emploi :
    // Permet d'importer des trajet a partir d'un fichier
    void LireSimple(ifstream & src);
    // Mode d'emploi :
    // Permet de lire un trajet simple dans un fichier passé en paramètre et de l'ajouter au catalogue
    void LireCompose(ifstream & src);
    // Mode d'emploi :
    // Permet de lire un trajet Compose dans un fichier passé en paramètre et de l'ajouter au catalogue
    void LireFichier(ifstream & src, char typeTrajet);


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

    ListeChainee * GetListeParcours();
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

