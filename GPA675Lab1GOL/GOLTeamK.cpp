#include "GOLTeamK.h"

GOLTeamK::GOLTeamK()
{
    setInformation();
    setStats();
}

GOLTeamK::GOLTeamK(size_t width, size_t height, State defaultState)
    :mGrid{width , height, defaultState}
    ,mPastGrid{width, height, defaultState}
    ,mAliveColor{}
    ,mDeadColor{}
    ,mStats{}
    ,mBorderManagement{}
    ,mIteration{0}
    ,mInfo{}
    ,mBornRule{}
    ,mSurviveRule{}
    ,mRule{}
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
    mStats.height = mGrid.getHeight();
    mStats.width = mGrid.getWidth();
    mStats.totalCells = mGrid.getSize();
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
    return mGrid.getWidth();
}

size_t GOLTeamK::height() const
{
    return mGrid.getHeight();
}

size_t GOLTeamK::size() const
{
    return mGrid.getSize();
}

GOL::State GOLTeamK::state(int x, int y) const
{
    return mGrid.value(x, y);    //ne valide pas ses entrees
    //return grid.at(x, y); //valide ses entrees
}

std::string GOLTeamK::rule() const
{
    /*std::string rule( "B" );
    for (uint8_t i{ 0 }; i < 10; i++) {
        if (mBornRule[i]) {
            char num = '0' + i;
            rule += num;
        }
    }
    rule + "/S";
    for (uint8_t i{ 0 }; i < 10; i++) {
        if (mSurviveRule[i]) {
            char num = '0' + i;
            rule += num;
        }
    }*/
    
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

    mGrid.resize(width, height, defaultState);
    


}

bool GOLTeamK::setRule(std::string const& rule)
{
    const std::regex pattern{ "^B([0-8]{0,9})/S([0-8]{0,9})$", std::regex_constants::icase };
    std::smatch matches;
    if (std::regex_match(rule,matches, pattern)) {
        mRule = rule;

        for (int i{}; i < 9; ++i) {
            mBornRule[i] = false;
            mSurviveRule[i] = false;
        }

        std::ssub_match bornNumbers = matches[1];
        std::string bornString = bornNumbers.str();
        for (char digit : bornString) {
            int num = digit - '0';
            mBornRule[num] = true;
        }

        std::ssub_match surviveNumbers = matches[2];
        std::string surviveString = surviveNumbers.str();
        for (char digit : surviveString) {
            int num = digit - '0';
            mSurviveRule[num] = true;
        }
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
    mGrid.setValue(x, y, state); //ne valide pas ses entrees
    //grid.setAt(x, y, state);  //valide ses entrees
}

void GOLTeamK::fill(State state)
{

    for (size_t row{}; row < mGrid.getHeight(); row++) {

        for (size_t column{}; column < mGrid.getWidth(); column++) {
            if (row == 0 || row == mGrid.getHeight()-1 || column == 0 || column == mGrid.getWidth()-1){
                if (mBorderManagement == BorderManagement::foreverDead) {
                    setState(column, row, State::dead);
                }
                else if (mBorderManagement == BorderManagement::foreverAlive) {
                    setState(column, row, State::alive);
                }
            }
            else {
                setState(column, row, state);
            }
        }
    }
    mIteration = 0;
}

void GOLTeamK::fillAlternately(State firstCell)
{
    State oppositeState = getOppositeState(firstCell);

    for (size_t row{}; row < mGrid.getHeight(); row++) {
        
        for (size_t column{}; column < mGrid.getWidth(); column++) {
            if (row == 0 || row == mGrid.getHeight() - 1 || column == 0 || column == mGrid.getWidth() - 1) {
                if (mBorderManagement == BorderManagement::foreverDead) {
                    setState(column, row, State::dead);
                }
                else if (mBorderManagement == BorderManagement::foreverAlive) {
                    setState(column, row, State::alive);
                }
            }
            else {
                State cellstate = ((row + column) % 2 == 0) ? firstCell : oppositeState;    //l'opperateur ? resume cette ligne a --> Si VRAI alors cellstate vaut firstcell, sinon elle vaut oppositeState
                setState(column, row, cellstate);
            }
        }
    }
    mIteration = 0;
}

void GOLTeamK::randomize(double percentAlive)
{
    std::mt19937 gen(std::random_device{}());               //generateur aleatoire
    std::bernoulli_distribution prob(percentAlive);         //creation d'une instance qui recoit en parametre la probabilite qu'elle retourne True

    for (size_t row{}; row < mGrid.getHeight(); row++) {

        for (size_t column{}; column < mGrid.getWidth(); column++) {
            if (row == 0 || row == mGrid.getHeight() - 1 || column == 0 || column == mGrid.getWidth() - 1) {
                if (mBorderManagement == BorderManagement::foreverDead) {
                    setState(column, row, State::dead);
                }
                else if (mBorderManagement == BorderManagement::foreverAlive) {
                    setState(column, row, State::alive);
                }  
            }
            else {
                State cellstate = prob(gen) ? State::alive : State::dead;

                setState(column, row, cellstate);
            }
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
    const size_t width = mGrid.getWidth();
    const size_t height = mGrid.getHeight();
    const size_t size = mGrid.getSize();
    const bool ignoreBorder = mBorderManagement == BorderManagement::immutableAsIs || mBorderManagement == BorderManagement::foreverDead || mBorderManagement == BorderManagement::foreverAlive;

    State* pastGrid{ mGrid.data() };

    for (size_t i{};i<size;++i){
        int column = i % width;
        int row = i / width;
        bool onBorder = row == 0 || row == height - 1 || column == 0 || column == width - 1;

        if (ignoreBorder && onBorder) {
            setState(column,row,*pastGrid);
        }
        else {
            int alive = getAliveAround(onBorder, pastGrid);

            if (mGrid.value(column, row) == State::alive) {
                if (!mSurviveRule[alive]) {
                    setState(column, row, State::dead);
                }
            }
            else {
                if (mBornRule[alive]) {
                    setState(column, row, State::alive);
                }
            }
        }
        ++pastGrid;
    }

    ++mIteration;

 /*   const bool ignoreBorder = mBorderManagement == BorderManagement::immutableAsIs || mBorderManagement == BorderManagement::foreverDead || mBorderManagement == BorderManagement::foreverAlive;
    int iter{};
    int end{};

    if (ignoreBorder) {
        iter = width + 1;
        end = size - width - 1;
    }
    else { 
        iter = 0; 
        end = size;
    }

    while (iter < end) {
        int column = iter / width;
        int row = iter % width;

        int alive = getAliveAround(row, column, ignoreBorder);
        
        if (mGrid.value(column, row) == State::alive) {
            if (!mSurviveRule[alive]) {
                futureGrid.setAt(column, row, State::dead);
            }
        }
        else {
            if (mBornRule[alive]) {
                futureGrid.setAt(column, row, State::alive);
            }
        }

        if (ignoreBorder && iter % width == width - 1) {
            iter += 3;
        }
        else {
            ++iter;
        }
    }*/
}

void GOLTeamK::updateImage(uint32_t* buffer, size_t buffer_size) const
{
    size_t x{}; //index pour parcourir le buffer
    DataType myGrid{ mGrid.data() }; //myGrid est de type Celltype*
    //* cur{};
    // uint8_t end {(static_cast<uint8_t> (*myGrid))+buffer_size};



    while (x < buffer_size) {

        Color cellColor = (*myGrid == State::alive) ? mAliveColor : mDeadColor;

        *(buffer + x) = (0xff << 24) | (cellColor.red << 16) | (cellColor.green << 8) | cellColor.blue;

        ++x;
        ++myGrid;
    }
}


int GOLTeamK::getAliveAround(bool onBorder, State* pastGrid)
{
    int aliveCells{};
    int width = mGrid.getWidth();
    int height = mGrid.getHeight();

    State* topLeft = pastGrid-width - 1;
    State* top = pastGrid - width;
    State* topRight = pastGrid - width + 1;
    State* left = pastGrid - 1;
    State* right = pastGrid + 1;
    State* bottomLeft = pastGrid + width - 1;
    State* bottom = pastGrid + width;
    State* bottomRight = pastGrid + width + 1;
    

    if (mBorderManagement == BorderManagement::mirror && onBorder) {

    }
    else if (mBorderManagement == BorderManagement::warping && onBorder) {

    }
    else {
        if (*topLeft == State::alive) {
            ++aliveCells;
        }
        if (*top == State::alive) {
            ++aliveCells;
        }
        if (*topRight == State::alive) {
            ++aliveCells;
        }
        if (*left == State::alive) {
            ++aliveCells;
        }
        if (*right == State::alive) {
            ++aliveCells;
        }
        if (*bottomLeft == State::alive) {
            ++aliveCells;
        }
        if (*bottom == State::alive) {
            ++aliveCells;
        }
        if (*bottomRight == State::alive) {
            ++aliveCells;
        }

        return aliveCells;
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

//void GOLTeamK::browseHandling(GridTeamK& grid, void(*task)(State &))
//{
//    if (mBorderManagement == BorderManagement::immutableAsIs || mBorderManagement == BorderManagement::foreverDead || mBorderManagement == BorderManagement::foreverAlive) {
//        for (size_t row{}; row < grid.getHeight(); row++) {
//
//            for (size_t column{}; column < grid.getWidth(); column++) {
//
//                setState(column, row,State &);
//            }
//        }
//    }
//
//    if (mBorderManagement == BorderManagement::mirror) {
//
//    }
//
//    if (mBorderManagement == BorderManagement::warping) {
//
//    }
//}

GOL::State GOLTeamK::getOppositeState(State state)
{
    if (state == State::alive) {

        return State::dead;
    }
    else {

        return State::alive;
    }
}

