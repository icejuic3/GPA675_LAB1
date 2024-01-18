#pragma once
#include "GOLTeamK.h"

class GridTeamK																		// Classe facilitant la gestion d'un tableau dynamique 2d.
{																				// 
public:																			// 
	// Définition des types														//
	using CellType = GOLTeamK::State;												// Correspond au type fondamental de chaque cellule de la grille. 
	using DataType = ...;														// Correspond à la grille, au conteneur de cellules. À vous de déterminer la structure de données à utiliser.
	
	// Définition des cosntructeurs / destructeur								//
	GridTeamK();																		// 
	GridTeamK(size_t width, size_t height, CellType initValue = CellType{});			// 
	GridTeamK(GridTeamK const&) = delete;													// 
	GridTeamK(GridTeamK&&) = delete;														// 
	GridTeamK& operator=(GridTeamK const&) = delete;										// 
	GridTeamK& operator=(GridTeamK&&) = delete;											// 
	~GridTeamK();																	// 
	
	// Accesseurs et mutateurs de la grille										// 
	size_t width() const;														// Accesseur retournant la largeur de la grille.
	size_t height() const;														// Accesseur retournant la hauteur de la grille.
	size_t size() const;														// Accesseur retournant le nombre de cellule de la grille.
	 
	void resize(size_t width, size_t height, CellType initValue = CellType{});	// Mutateur modifiant la taille de la grille et initialise le contenu par la valeur spécifiée.
	
	// Accesseurs et mutateurs des cellules										//
	CellType value(int column, int row) const;									// Accesseur retournant la valeur d'une cellule à une certaine coordonnée. Pour une raison de performance, cette fonction NE VALIDE PAS ses entrées. Autrement dit, c'est la responsabilité du programmeur utilisateur de faire ses validations, au risque de 'crasher' le programme.
	void setValue(int column, int row, CellType value);							// Mutateur modifiant la valeur d'une cellule à une certaine coordonnée. Pour une raison de performance, cette fonction NE VALIDE PAS ses entrées. Autrement dit, c'est la responsabilité du programmeur utilisateur de faire ses validations, au risque de 'crasher' le programme.
	// 
	std::optional<CellType> at(int column, int row) const;						// Accesseur retournant la valeur d'une cellule à une certaine coordonnée. Cette fonction VALIDE ses entrées et retourne un optional nul si la coordonnée est invalide. 
	void setAt(int column, int row, CellType value);							// Mutateur modifiant la valeur d'une cellule à une certaine coordonnée. Cette fonction VALIDE ses entrées et ne fait rien si la coordonnée est invalide. 
	
	// Accesseurs du "buffer" de la grille.										//
	DataType const& data() const;												// Accesseur en lecture seule sur le "buffer" de la grille.
	DataType& data();															// Accesseur en lecture/écriture sur le "buffer" de la grille.
	
private:																		// 
	size_t mWidth;															// Il y a des attributs essentiels au fonctionnement de cette classe.
	size_t mHeight;
	size_t mSize;
	CellType * mGrid;
};