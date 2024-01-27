#include "GOLTeamK.h"

GOLTeamK::GOLTeamK()
{
}

GOLTeamK::GOLTeamK(size_t width, size_t height, State defaultState)
{

    mInfo.title = "Game of life";
    mInfo.authors = { {"Curiel - Garfias","Jacob","jacob.curiel-garfias.1@ens.etsmtl.ca"}, };




}

size_t GOLTeamK::width() const
{
    return grid.getWidth();
}

size_t GOLTeamK::height() const
{
    return grid.getHeight();
}

size_t GOLTeamK::size() const
{
    return grid.getSize();
}

GOL::State GOLTeamK::state(int x, int y) const
{
    return grid.value(x, y);    //ne valide pas ses entrees
    //return grid.at(x, y); //valide ses entrees
}

std::string GOLTeamK::rule() const
{
    return mRule;
}

GOL::BorderManagement GOLTeamK::borderManagement() const
{
    return mBorderManagement;
}

GOL::Color GOLTeamK::color(State state) const
{
    if (state == State::alive) {
        return mAliveColor;
    }
    else if (state == State::dead) {
        return mDeadColor;
    }
}

GOL::Statistics GOLTeamK::statistics() const
{
    // à faire
    return mStats;
}

GOL::ImplementationInformation GOLTeamK::information() const
{
    return mInfo;
}

void GOLTeamK::resize(size_t width, size_t height, State defaultState)
{
    if (width == 0 || height == 0) {
        width = 0;
        height = 0;
    }
    mIteration = 0;

    grid.resize(width, height, defaultState);
}

bool GOLTeamK::setRule(std::string const& rule)
{
    std::regex pattern{ "^B[0-8]{0,9}/S[0-8]{0,9}$", std::regex_constants::icase };
    if (std::regex_match(rule, pattern)) {
        mRule = rule;
        mIteration = 0;
    }
    return false;
}

void GOLTeamK::setBorderManagement(BorderManagement borderManagement)
{
    mBorderManagement = borderManagement;
    mIteration = 0;
}

void GOLTeamK::setState(int x, int y, State state)
{
    grid.setValue(x, y, state); //ne valide pas ses entrees
    //grid.setAt(x, y, state);  //valide ses entrees
}

void GOLTeamK::fill(State state)
{
    ////version non efficace et marche pas, va falloir faire des pointeurs
    //for (size_t i{}; i < mGrid.width(); i++) {
    //    for (size_t j{}; j < mGrid.height(); j++) {
    //        mGrid[i][j] = state;
    //    }
    //}
    //mIteration = 0;
}

void GOLTeamK::fillAlternately(State firstCell)
{
}

void GOLTeamK::randomize(double percentAlive)
{
}

bool GOLTeamK::setFromPattern(std::string const& pattern, int centerX, int centerY)
{
    return false;
}

bool GOLTeamK::setFromPattern(std::string const& pattern)
{
    return false;
}

void GOLTeamK::setSolidColor(State state, Color const& color)
{
    if (state == State::alive) {
        mAliveColor = color;
    }
    else if(state == State::dead) {
        mDeadColor = color;
    }
}

void GOLTeamK::processOneStep()
{
}

void GOLTeamK::updateImage(uint32_t* buffer, size_t buffer_size) const
{
    size_t x{};
    
   /* while (CUR < buffer_size) {
        *(buffer + x) = *(CUR) ? : mAliveColor : mDeadColor;
        ++x;
        ++CUR;
    
    }*/
}
