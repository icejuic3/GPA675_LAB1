#pragma once
#include "GOLTeamK.h"

// D�finition des types														//
using CellType = GOLTeamK::State;											// Correspond au type fondamental de chaque cellule de la grille. 
using DataType = CellType**;												// Correspond � la grille, au conteneur de cellules. Nous n'utilisons pas de vecteur puisque la memoire doit etre gerer manuellement
using namespace std;


class GridTeamK																	// Classe facilitant la gestion d'un tableau dynamique 2d.
{																				// 
public:																			// 
	
	// D�finition des constructeurs / destructeur								//
	GridTeamK();																// 
	GridTeamK(size_t width, size_t height, CellType initValue = CellType{});	// 
	GridTeamK(GridTeamK const&) = delete;										// 
	GridTeamK(GridTeamK&&) = delete;											// 
	GridTeamK& operator=(GridTeamK const&) = delete;							// 
	GridTeamK& operator=(GridTeamK&&) = delete;									// 
	~GridTeamK();														    	// 

	//fonction qui detruit le tableau
	void gridDelete();
	
	// Accesseurs et mutateurs de la grille										// 
	size_t width() const;														// Accesseur retournant la largeur de la grille.
	size_t height() const;														// Accesseur retournant la hauteur de la grille.
	size_t size() const;														// Accesseur retournant le nombre de cellule de la grille.
	 
	void resize(size_t width, size_t height, CellType initValue = CellType{});	// Mutateur modifiant la taille de la grille et initialise le contenu par la valeur sp�cifi�e.
	
	// Accesseurs et mutateurs des cellules										//
	CellType value(int column, int row) const;									// Accesseur retournant la valeur d'une cellule � une certaine coordonn�e. Pour une raison de performance, cette fonction NE VALIDE PAS ses entr�es. Autrement dit, c'est la responsabilit� du programmeur utilisateur de faire ses validations, au risque de 'crasher' le programme.
	void setValue(int column, int row, CellType value);							// Mutateur modifiant la valeur d'une cellule � une certaine coordonn�e. Pour une raison de performance, cette fonction NE VALIDE PAS ses entr�es. Autrement dit, c'est la responsabilit� du programmeur utilisateur de faire ses validations, au risque de 'crasher' le programme.
	// 
	optional<CellType> at(int column, int row) const;							// Accesseur retournant la valeur d'une cellule � une certaine coordonn�e. Cette fonction VALIDE ses entr�es et retourne un optional nul si la coordonn�e est invalide. 
	void setAt(int column, int row, CellType value);							// Mutateur modifiant la valeur d'une cellule � une certaine coordonn�e. Cette fonction VALIDE ses entr�es et ne fait rien si la coordonn�e est invalide. 
	
	// Accesseurs du "buffer" de la grille.										//
	DataType const& data() const;												// Accesseur en lecture seule sur le "buffer" de la grille.
	DataType& data();															// Accesseur en lecture/�criture sur le "buffer" de la grille.
	
private:																		// 
	DataType mGrid;																//pointeur de pointeur
	size_t mWidth;											    				// Il y a des attributs essentiels au fonctionnement de cette classe.
	size_t mHeight;
	size_t mSize;
};