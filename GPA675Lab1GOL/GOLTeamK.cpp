#include "GOLTeamK.h"

size_t GOLTeamK::width() const
{
    return size_t();
}

size_t GOLTeamK::height() const
{
    return size_t();
}

size_t GOLTeamK::size() const
{
    return size_t();
}

State GOLTeamK::state(int x, int y) const
{
    return State();
}

std::string GOLTeamK::rule() const
{
    return std::string();
}

BorderManagement GOLTeamK::borderManagement() const
{
    return BorderManagement();
}

Color GOLTeamK::color(State state) const
{
    return Color();
}

Statistics GOLTeamK::statistics() const
{
    return Statistics();
}

ImplementationInformation GOLTeamK::information() const
{
    return ImplementationInformation();
}

void GOLTeamK::resize(size_t width, size_t height, State defaultState)
{
}

bool GOLTeamK::setRule(std::string const& rule)
{
    return false;
}

void GOLTeamK::setBorderManagement(BorderManagement borderManagement)
{
}

void GOLTeamK::setState(int x, int y, State state)
{
}

void GOLTeamK::fill(State state)
{
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
}

void GOLTeamK::processOneStep()
{
}

void GOLTeamK::updateImage(uint32_t* buffer, size_t buffer_size) const
{
}
