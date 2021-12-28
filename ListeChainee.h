/*************************************************************************
                           ListeChainee  -  Interface de la classe ListeChainee
                             -------------------
    début                : 19/11/2021
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//----Interface de la classe <ListeChainee> (fichier ListeChainee.h) -----
#if ! defined ( LISTECHAINNEE_H )
#define LISTECHAINNEE_H

//--------------------------------------------------- Interfaces utilisées
#include <fstream>
using namespace std;

#include "Maillon.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <ListeChainee>
//  Implemente la liste chainee avec pointeur de debut et de fin
//  Utile pour creer des trajets compose et le catalogue
//------------------------------------------------------------------------

class ListeChainee
{
public:
//--------------------------- Méthodes publiques
    void Sauvegarde( ofstream & dest, string mode );
    // Mode d'emploi :
    // Permet de Sauvegarder l'intégralité ou une partie de la liste en fonction de différents critéres 
    void AjouterTri( Trajet * contenu);
    // Mode d'emploi :
    // Ajout d'un trajet dans la liste par ordre alphabétique de la ville de départ

    void AjouterDeb( Trajet * contenu);
    // Mode d'emploi :
    // Ajout d'un Trajet en debut de liste

    void AjouterFin( Trajet * contenu);
    // Mode d'emploi :
    // Ajout d'un Trajet en fin de liste

    string Afficher ( int mode = 0 ) const;
    // Mode d'emploi :
    // Affiche le contenu de la liste :
    // Par défaut mode = 0 : On affiche les trajets de manière classique
    // mode = 1 : On affiche les trajets simple au sein de trajets composees

//----------------------------------------------------------------Getteur

    Maillon * GetDebut() const;
    // Mode d'emploi :
    // Renvoie le premier maillon de la liste

    Maillon * GetFin() const;
    // Mode d'emploi :
    // Renvoie le dernier maillon de la liste

    int GetNbMaillon() const;
    // Mode d'emploi :
    // Renvoie le nombre de maillons de la liste

//---- Constructeurs - destructeur
    ListeChainee ( );
    // Mode d'emploi :
    // Construit la liste chainee
    virtual ~ListeChainee ( );
    // Mode d'emploi :
    // Detruit la liste chainee

protected:
//------------ Méthodes protégées

//--- Attributs protégés
  Maillon * debut;
  Maillon * fin;
  int nbMaillon;

};

//------------------------ Autres définitions dépendantes de <ListeChainee>

#endif // LISTECHAINEE_H

