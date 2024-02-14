#pragma once

#include "GOL.h"
#include "GridTeamK.h"
#include <regex>
#include <random>


class GOLTeamK : public GOL
{
public:
	//! \brief Constructeur par défaut.
	GOLTeamK();
	// 
	//! \brief Constructeur d'initialisation personnalisé.
	GOLTeamK(size_t width, size_t height, State defaultState = State::dead);
	// 
	//! Destructeur.
	virtual ~GOLTeamK();
	// 
	// Les 4 autres fonctions spéciales sont laissées à votre discrétion.
	// Toutefois, un simple -delete- est suffisant pour ce premier laboratoire.
	GOLTeamK(GOLTeamK const&) = delete;
	GOLTeamK(GOLTeamK&&) = delete;
	GOLTeamK& operator=(GOLTeamK const&) = delete;
	GOLTeamK& operator=(GOLTeamK&&) = delete;

	// Inherited via GOL
	size_t width() const override;																	//
	size_t height() const override;																	//
	size_t size() const override;																	//
	State state(int x, int y) const override;														//
	std::string rule() const override;																//
	BorderManagement borderManagement() const override;												//
	Color color(State state) const override;														//
	Statistics statistics() const override;															//
	ImplementationInformation information() const override;											//

	void resize(size_t width, size_t height, State defaultState) override;							//
	bool setRule(std::string const& rule) override;													//
	void setBorderManagement(BorderManagement borderManagement) override;							//
	void setState(int x, int y, State state) override;												//
	void fill(State state) override;																//fonction de remplissage
	void fillAlternately(State firstCell) override;													//
	void randomize(double percentAlive) override;													//
	bool setFromPattern(std::string const& pattern, int centerX, int centerY) override;				//
	bool setFromPattern(std::string const& pattern) override;										//
	void setSolidColor(State state, Color const& color) override;									//fonction pour definir la couleur
	void processOneStep() override;																	//
	void updateImage(uint32_t* buffer, size_t buffer_size) const override;							//
	
	int getAliveAround(int column, int row, bool onBorder, State* pastGrid);						//fonction qui compte le nombre de cellules vivantes autour d'une position dans la grille
	void copyGrid();																				//fonction qui copy l'état actuel de la grille dans mPastGrid
	State getOppositeState(State state);															//fonction qui retourne l'état opposé d'une cellule
	void setInformation();																			//fonction pour les informations du projet


	bool onBorder(size_t row, size_t column);														//fonction qui vérifie si nous sommes sur une bordure
	bool ignoreBorder();																			//fonction qui vérifie les bordures non modifiables
	void fillBorder(size_t row, size_t column, State state);										//fonction qui remplie cases de bordure respectant le BorderManagement

	void tendencyCal();																				//fonction qui met à jour la tendence
	void resetStats();																				//fonction qui met les statistiques à zéro
	void setStats(State state);																		//fonction qui incrémente les statistiques absolues
	void relStats();																				//fonction qui met à jour les statistiques relatives


private:

	GridTeamK mGrid;
	GridTeamK mPastGrid;
	std::string mRule;						//la regle de survie ou de naissance en texte
	bool mBornRule[9];						//tableau de booleen representant le nombre de voisins a evaluer pour naitre
	bool mSurviveRule[9];					//tableau de booleen representant le nombre de voisins a evaluer pour suvivre
	BorderManagement mBorderManagement;

	Color mAliveColor;	// une struct contenant trois channel de couleur (uint8_t) pour les cellules vivantes
	Color mDeadColor;	// une struct contenant trois channel de couleur (uint8_t) pour les cellules mortes

	Statistics mStats;
	Statistics mNewStats;
	ImplementationInformation mInfo;
	IterationType mIteration;

};

