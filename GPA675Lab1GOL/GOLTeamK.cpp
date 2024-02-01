#include "GOLTeamK.h"

GOLTeamK::GOLTeamK()
{
    setInformation();
    setStats();
}

GOLTeamK::GOLTeamK(size_t width, size_t height, State defaultState)
    :grid{width , height, defaultState}
    ,mAliveColor{}
    ,mDeadColor{}
    ,mStats{}
    ,mBorderManagement{}
    ,mIteration{}
    ,mInfo{}
{
    setInformation();
    setStats();
}

GOLTeamK::~GOLTeamK()
{
}

void GOLTeamK::setInformation()
{
    mInfo.title = "Game of life Team K";
    mInfo.authors = { {"Curiel - Garfias","Jacob","jacob.curiel-garfias.1@ens.etsmtl.ca"},};
    mInfo.answers = {};
    mInfo.optionnalComments = {};
}

void GOLTeamK::setStats()
{
    mStats.borderManagement = mBorderManagement;
    mStats.height = grid.getHeight();
    mStats.width = grid.getWidth();
    mStats.totalCells = grid.getSize();
    mStats.iteration = mIteration;
    mStats.rule = mRule;



    /*********faire un decompte de la grille**********/
    mStats.totalAliveAbs;
    mStats.totalDeadAbs;
    
    /********mettre en pourcentage par rapport le total de cellule**************/
    mStats.totalAliveRel;
    mStats.totalDeadRel;

    /*******************/
    mStats.tendencyAbs;
    mStats.tendencyRel;
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

        return true;
    }
    else
    {
        return false;
    }
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

   for (size_t row{}; row < grid.getHeight(); row++) {

        for (size_t column{}; column < grid.getWidth(); column++) {

            setState(column, row, state); 
        }
   }
    mIteration = 0;
}

void GOLTeamK::fillAlternately(State firstCell)
{
    State oppositeState = getOppositeState(firstCell);

    for (size_t row{}; row < grid.getHeight(); row++) {
        
        for (size_t column{}; column < grid.getWidth(); column++) {

            State cellstate = ((row + column) % 2 == 0) ? firstCell : oppositeState;    //l'opperateur ? resume cette ligne a --> Si VRAI alors cellstate vaut firstcell, sinon elle vaut oppositeState
            setState(column, row, cellstate);          
        }
    }
    mIteration = 0;
}

void GOLTeamK::randomize(double percentAlive)
{
    std::mt19937 gen(std::random_device{}());               //generateur aleatoire
    std::bernoulli_distribution prob(percentAlive);         //creation d'une instance qui recoit en parametre la probabilite qu'elle retourne True

    for (size_t row{}; row < grid.getHeight(); row++) {

        for (size_t column{}; column < grid.getWidth(); column++) {

            State cellstate = prob(gen) ? State::alive : State::dead;

            setState(row, column, cellstate);
        }
    }
    mIteration = 0;
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
    size_t x{}; //index pour parcourir le buffer
    DataType myGrid{ grid.data() }; //myGrid est de type Celltype*
    //* cur{};
    // uint8_t end {(static_cast<uint8_t> (*myGrid))+buffer_size};

    

    while (x < buffer_size) {

        Color cellColor = (*myGrid == State::alive) ? mAliveColor : mDeadColor;

        *(buffer+x) = (0xff << 24) | (cellColor.red << 16) | (cellColor.green << 8) | cellColor.blue;

        ++x;
        ++myGrid;
    }
    




    //size_t x{};
    //DataType myGrid = grid.data();

    //for (size_t row{}; row < grid.getHeight(); ++row) {

    //    for (size_t column{}; column < grid.getWidth(); ++column) {

    //        Color cellColor = (myGrid[row][column] == State::alive) ? mAliveColor : mDeadColor;
    //        buffer[x] = (0xff << 24) | (cellColor.red << 16) | (cellColor.green << 8) | cellColor.blue;
    //        x++;
    //    }
    //}
}

GOL::State GOLTeamK::getOppositeState(State state)
{
    if (state == State::alive) {

        return State::dead;
    }
    else {

        return State::alive;
    }
}

