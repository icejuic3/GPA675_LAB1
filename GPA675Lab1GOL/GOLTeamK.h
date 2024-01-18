#pragma once
#include "GOL.h"

class GOLTeamK: public GOL
{
	//! \brief Constructeur par défaut.
	GOLTeamK() = default;
	// 
	//! \brief Constructeur d'initialisation personnalisé.
	GOLTeamK(size_t width, size_t height, State defaultState = State::dead) {}
	// 
	//! Destructeur.
	virtual ~GOLTeamK() = default;
	// 
	// Les 4 autres fonctions spéciales sont laissées à votre discrétion.
	// Toutefois, un simple -delete- est suffisant pour ce premier laboratoire.
	// _class_(_class_ const &) = delete;
	// _class_(_class_ &&) = delete;
	// _class_& operator=(_class_ const &) = delete;
	// _class_& operator=(_class_ &&) = delete;
	
	// Inherited via GOL
	size_t width() const override;
	size_t height() const override;
	size_t size() const override;
	State state(int x, int y) const override;
	std::string rule() const override;
	BorderManagement borderManagement() const override;
	Color color(State state) const override;
	Statistics statistics() const override;
	ImplementationInformation information() const override;
	void resize(size_t width, size_t height, State defaultState) override;
	bool setRule(std::string const& rule) override;
	void setBorderManagement(BorderManagement borderManagement) override;
	void setState(int x, int y, State state) override;
	void fill(State state) override;
	void fillAlternately(State firstCell) override;
	void randomize(double percentAlive) override;
	bool setFromPattern(std::string const& pattern, int centerX, int centerY) override;
	bool setFromPattern(std::string const& pattern) override;
	void setSolidColor(State state, Color const& color) override;
	void processOneStep() override;
	void updateImage(uint32_t* buffer, size_t buffer_size) const override;
};

