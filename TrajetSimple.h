/*************************************************************************
                           TrajetSimple  -  interface de la classe TrajetSimple
                             -------------------
    début                : 19/11/2021
    copyright            : (C) 2021 par Hugo Blaess & Octave Duvivier
    e-mail               : hugo.blaess@insa-lyon.fr & octave.duvivier@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h) ----------------
#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H

//--------------------------------------------------- Interfaces utilisées

#include "Trajet.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
class TrajetSimple : public Trajet
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    string Afficher( int mode = 0) const;
    // Mode d'emploi :
    // Affiche le contenu de la liste :
    // Par défaut mode = 0 : On affiche les trajets de manière classique
    // mode = 1 : On affiche les trajets simple au sein de trajets composees

//----------------------------------------------------------------Getteur

    char * GetVilleDepart() const;
    // Mode d'emploi :
    // Renvoie la ville de depart du trajetSimple
    char * GetVilleArrivee() const;
    // Mode d'emploi :
    // Renvoie la ville d'arrivee du trajetCompose

//-------------------------------------------- Constructeurs - destructeur
    
    TrajetSimple (char * unDepart, char * uneArrivee, char * unTransport);
    // Mode d'emploi :
    // Construit le trajet simple a partir de sa ville de depart, d'arrivee et son moyen de transport
    virtual ~TrajetSimple ( );
    // Mode d'emploi :
    // Detruit le trajet simple

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
char * villeArrivee;
char * villeDepart;
char * moyenTransport;
};

#endif // TRAJETSIMPLE_H

