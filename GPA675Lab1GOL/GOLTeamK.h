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
	size_t width() const override;																	//done
	size_t height() const override;																	//done
	size_t size() const override;																	//done
	State state(int x, int y) const override;														//done
	std::string rule() const override;																//done
	BorderManagement borderManagement() const override;												//done
	Color color(State state) const override;														//done
	Statistics statistics() const override;															//done
	ImplementationInformation information() const override;											//done

	void resize(size_t width, size_t height, State defaultState) override;							//done
	bool setRule(std::string const& rule) override;													//done
	void setBorderManagement(BorderManagement borderManagement) override;							//done
	void setState(int x, int y, State state) override;												//done
	void fill(State state) override;																//done
	void fillAlternately(State firstCell) override;													//done
	void randomize(double percentAlive) override;													//done
	bool setFromPattern(std::string const& pattern, int centerX, int centerY) override;				//done
	bool setFromPattern(std::string const& pattern) override;										//done
	void setSolidColor(State state, Color const& color) override;									//done		fonction pour definir la couleur
	void processOneStep() override;																	//done 
	void updateImage(uint32_t* buffer, size_t buffer_size) const override;							//done
	
	int getAliveAround(int column, int row, bool onBorder, State* pastGrid);						//fonction qui compte le nombre de cellules vivantes autour d'une position dans la grille
	void copyGrid();																				//fonction qui copy l'etat actuel de la grille dans mPastGrid
	State getOppositeState(State state);															//fonction qui retourne un etat oppose
	void setInformation();																			//fonction pour les informations du projet


	bool onBorder(size_t row, size_t column);														//fonction qui verifie si nous sommes sur une bordure
	bool ignoreBorder();																			//fonction qui verifie les bordures non modifiables
	void fillBorder(size_t row, size_t column, State state);										//fonction qui remplie cases de bordure respectant le BorderManagement


	void tendencyCal();
	void resetStats();
	void setStats(State state);
	void relStats();


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

