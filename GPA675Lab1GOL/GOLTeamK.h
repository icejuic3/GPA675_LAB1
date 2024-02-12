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
	bool setFromPattern(std::string const& pattern, int centerX, int centerY) override;				//a faire
	bool setFromPattern(std::string const& pattern) override;										//a faire
	void setSolidColor(State state, Color const& color) override;									//done		fonction pour definir la couleur
	void processOneStep() override;																	//done ---> faire warping et mirror
	void updateImage(uint32_t* buffer, size_t buffer_size) const override;							//done
	//void browseHandling(GridTeamK& grid, void(*task)(State &));
	int getAliveAround(int column, int row, bool onBorder, State* pastGrid);
	void copyGrid();


	State getOppositeState(State state);															//fonction qui retourne un etat oppose
	void setInformation();																			//fonction pour les informations du projet


	bool onBorder(size_t row, size_t column);														//fonction qui verifie si nous sommes sur une bordure
	bool ignoreBorder();																			//fonction qui verifie les bordures non modifiables
	void fillBorder(size_t row, size_t column, State state);


	void tendencyCal();
	void resetStats();
	void setStats(State state);
	void relStats();


private:

	GridTeamK mGrid;
	GridTeamK mPastGrid;
	std::string mRule;
	bool mBornRule[9];
	bool mSurviveRule[9];
	BorderManagement mBorderManagement;

	Color mAliveColor;	// une struct contenant trois channel de couleur (uint8_t) pour les cellules vivantes
	Color mDeadColor;	// une struct contenant trois channel de couleur (uint8_t) pour les cellules mortes

	Statistics mStats;
	Statistics mNewStats;
	ImplementationInformation mInfo;
	IterationType mIteration;

};

