#include "GOLTeamK.h"

size_t GOLTeamK::width() const
{
    return size_t(); //mGrid.width();
}

size_t GOLTeamK::height() const
{
    return size_t(); //mGrid.height();
}

size_t GOLTeamK::size() const
{
    return size_t(); //mGrid.size();
}

GOL::State GOLTeamK::state(int x, int y) const
{
    return State(); //mGrid.value(x,y);
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
    // � faire
    return mStats;
}

GOL::ImplementationInformation GOLTeamK::information() const
{
    // � faire
    return mInfo;
}

void GOLTeamK::resize(size_t width, size_t height, State defaultState)
{
    if (width == 0 || height == 0) {
        width = 0;
        height = 0;
    }
    mIteration = 0;
    //mGrid.resize(width, height, defaultState);
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
    //mGrid.setAt(x, y, state);
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
