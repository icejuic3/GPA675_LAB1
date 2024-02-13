#include "GOLTeamK.h"

GOLTeamK::GOLTeamK()

{
    setInformation();
    //setStats();
}

GOLTeamK::GOLTeamK(size_t width, size_t height, State defaultState)
    :mGrid{ width , height, defaultState }
    , mPastGrid{ width, height, defaultState }
    , mAliveColor{}
    , mDeadColor{}
    , mStats{}
    , mBorderManagement{}
    , mIteration{ 0 }
    , mInfo{}
    , mBornRule{}
    , mSurviveRule{}
    , mRule{}
    ,mNewStats{}
{
    setInformation();
}

GOLTeamK::~GOLTeamK()
{
}

void GOLTeamK::setInformation()
{
    mInfo.title = "Game of life Team K";
    mInfo.authors = { {"Curiel - Garfias","Jacob","jacob.curiel-garfias.1@ens.etsmtl.ca"}, };
    mInfo.answers = {};
    mInfo.optionnalComments = {};
}

void GOLTeamK::setStats(State state)
{
    if (state == State::alive) {

        (*mStats.totalAliveAbs)++;
    }
    else if (state == State::dead) {

        (*mStats.totalDeadAbs)++;
    }
}

void GOLTeamK::relStats()
{
    mStats.totalAliveRel = static_cast<float>(*mStats.totalAliveAbs) / (*mStats.totalCells);
    mStats.totalDeadRel = static_cast<float>(*mStats.totalDeadAbs) / (*mStats.totalCells);
}

void GOLTeamK::tendencyCal()
{
    mStats.tendencyAbs = (static_cast<int>(*mNewStats.totalAliveAbs) - static_cast<int>(*mStats.totalAliveAbs)) - (static_cast<int>(*mNewStats.totalDeadAbs) - static_cast<int>(*mStats.totalDeadAbs));
    mStats.tendencyRel = static_cast<float>(*mStats.tendencyAbs) / (*mStats.totalCells);
}

void GOLTeamK::resetStats()
{
    mStats.tendencyAbs = 0;
    mStats.tendencyRel = 0;
    mStats.totalAliveAbs = 0;
    mStats.totalDeadAbs = 0;
    mStats.totalAliveRel = 0;
    mStats.totalDeadRel = 0;

    mNewStats.tendencyAbs = 0;
    mNewStats.tendencyRel = 0;
    mNewStats.totalAliveAbs = 0;
    mNewStats.totalDeadAbs = 0;
    mNewStats.totalAliveRel = 0;
    mNewStats.totalDeadRel = 0;
}

bool GOLTeamK::onBorder(size_t row, size_t column)
{
    if (row == 0 || row == mGrid.getHeight() - 1 || column == 0 || column == mGrid.getWidth() - 1) {

        return true;
    }
    return false;
}

bool GOLTeamK::ignoreBorder()
{
    //les Bordures non modifiables 

    if (mBorderManagement == BorderManagement::immutableAsIs
        || mBorderManagement == BorderManagement::foreverDead
        || mBorderManagement == BorderManagement::foreverAlive) {

        return true;
    }
    return false;
}

void GOLTeamK::fillBorder(size_t row, size_t column, State state)
{
    if (mBorderManagement == BorderManagement::foreverDead) {           //si foreverDead, alors cellule morte
        setState(column, row, State::dead);
    }
    else if (mBorderManagement == BorderManagement::foreverAlive) {     //si foreverAlive, alors cellule vivante
        setState(column, row, State::alive);
    }
    else if (mBorderManagement == BorderManagement::immutableAsIs) {
        setState(column, row, state);
    }
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
    return mGrid.value(x, y);       //ne valide pas ses entrees
    //return grid.at(x, y);           //valide ses entrees
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
    resetStats();
    if (width == 0 || height == 0) {
        width = 0;
        height = 0;
    }

    mGrid.resize(width, height, defaultState);
    mPastGrid.resize(width, height, defaultState);  

    mStats.iteration = mIteration = 0;
    mStats.height = mGrid.getHeight();
    mStats.width = mGrid.getWidth();
    mStats.totalCells = mGrid.getSize();

    //ajustement des couleurs de bordures
    for (size_t i{}; i < mGrid.getSize(); i++) {

        size_t column = i % mGrid.getWidth();
        size_t row = i / mGrid.getWidth();

        if (onBorder(row, column) && ignoreBorder()) {

            fillBorder(row, column, mGrid.value(column, row));
        }
        else {
            setStats(defaultState);
        }
    }
    relStats();
}

bool GOLTeamK::setRule(std::string const& rule)
{
    const std::regex pattern{ "^B([0-8]{0,9})/S([0-8]{0,9})$", std::regex_constants::icase };
    std::smatch matches;

    if (std::regex_match(rule, matches, pattern)) {
        mStats.rule = mRule = rule;

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
        mStats.iteration = mIteration = 0;
        return true;
    }
    else
    {
        return false;
    }
}

bool GOLTeamK::setFromPattern(std::string const& pattern, int centerX, int centerY)
{
    

    //fontion pour implementer le pattern
    const std::regex mPattern{ "^\\[([0-9]+)x([0-9]+)\\]([01]+)$" ,std::regex_constants::icase };
    std::smatch matches;

    if (std::regex_match(pattern, matches, mPattern)) {

        int width = std::stoi(matches[1]);
        int height = std::stoi(matches[2]);
        int size = width * height;
        std::string cellStates = matches[3];
        
        
        for (int index = 0; index < size; ++index) {
    
            // Convertir l'index linéaire en coordonnées x, y
            int x = index % width;
            int y = index / width;

            // Calculer la position réelle de la cellule dans la grille
            int realX = centerX - width / 2 + x;
            int realY = centerY - height / 2 + y;

            if (realX >= 0 && realX < mGrid.getWidth() && realY >= 0 && realY < mGrid.getHeight()) {

                // Obtenir l'état de la cellule (vivant ou mort)
                if (cellStates[index] == '1' && mGrid.value(realX,realY) == State::dead) {

                    setState(realX, realY, State::alive);
                    (*mStats.totalDeadAbs)--;
                }
                else if(cellStates[index] == '0' && mGrid.value(realX, realY) == State::alive) {
                    setState(realX, realY, State::dead);
                    (*mStats.totalAliveAbs)--;
                }
            }   
        }
        relStats();
        mStats.iteration = mIteration = 0;
        return true;
    }
    else
        return false;
}

bool GOLTeamK::setFromPattern(std::string const& pattern)
{
    int centerX = mGrid.getWidth() / 2;
    int centerY = mGrid.getHeight() / 2;

    return setFromPattern(pattern,centerX,centerY);
}

void GOLTeamK::setBorderManagement(BorderManagement borderManagement)
{
    mStats.borderManagement = mBorderManagement = borderManagement;

    if (ignoreBorder()) {   //verifie si le remplissage de bordure est necessaire
        resetStats();

        for (size_t i{}; i < mGrid.getSize(); ++i) {

            size_t column = i % mGrid.getWidth();
            size_t row = i / mGrid.getWidth();

            if (onBorder(row, column)) {

                fillBorder(row, column, mGrid.value(column, row));
            }
            else {
                setStats(mGrid.value(column, row));
            }
        }
    }
    relStats();
    mStats.iteration = mIteration = 0;  
}

void GOLTeamK::setState(int x, int y, State state)
{
    mGrid.setValue(x, y, state); //ne valide pas ses entrees
    //grid.setAt(x, y, state);  //valide ses entrees

    setStats(state);
}

void GOLTeamK::fill(State state)
{
    resetStats();                                           //les stats sont remis à zéro

    for (size_t i{}; i < mGrid.getSize(); ++i) {

        size_t column = i % mGrid.getWidth();
        size_t row = i / mGrid.getWidth();

        if (onBorder(row, column) && ignoreBorder()) {

            fillBorder(row, column, state);
        }
        else {
            setState(column, row, state);
        }
    }
    relStats();
    mStats.iteration = mIteration = 0;
}

void GOLTeamK::fillAlternately(State firstCell)
{
    resetStats();
    State oppositeState = getOppositeState(firstCell);

    for (size_t i{}; i < mGrid.getSize(); ++i) {

        size_t column = i % mGrid.getWidth();
        size_t row = i / mGrid.getWidth();
        State cellstate = ((row + column) % 2 == 0) ? firstCell : oppositeState;    //l'opperateur ? resume cette ligne a --> Si VRAI alors cellstate vaut firstcell, sinon elle vaut oppositeState

        if (onBorder(row, column) && ignoreBorder()) {

            fillBorder(row, column, cellstate);
        }
        else {
            setState(column, row, cellstate);
        }
    }
    relStats();
    mStats.iteration = mIteration = 0;
}

void GOLTeamK::randomize(double percentAlive)
{
    resetStats();
    std::mt19937 gen(std::random_device{}());               //generateur aleatoire
    std::bernoulli_distribution prob(percentAlive);         //creation d'une instance qui recoit en parametre la probabilite qu'elle retourne True

    for (size_t i{}; i < mGrid.getSize(); ++i) {

        State cellstate = prob(gen) ? State::alive : State::dead;
        size_t column = i % mGrid.getWidth();
        size_t row = i / mGrid.getWidth();

        if (onBorder(row, column) && ignoreBorder()) {
            fillBorder(row, column, cellstate);
        }
        else {
            setState(column, row, cellstate);
        }
    }
    relStats();
    mStats.iteration = mIteration = 0;
}

void GOLTeamK::setSolidColor(State state, Color const& color)
{
    if (state == State::alive) {
        mAliveColor = color;
    }
    else if (state == State::dead) {
        mDeadColor = color;
    }
}

void GOLTeamK::processOneStep()
{

    const size_t width = mGrid.getWidth();
    const size_t height = mGrid.getHeight();
    const size_t size = mGrid.getSize();
    const bool ignoreBorder = mBorderManagement == BorderManagement::immutableAsIs || mBorderManagement == BorderManagement::foreverDead || mBorderManagement == BorderManagement::foreverAlive;
    copyGrid();
    resetStats();
    State* pastGrid{ mPastGrid.data() };

    /*************************************************************************************************************************/

    for (size_t i{}; i < size; ++i) {
        int column = i % width;
        int row = i / width;
        bool onBorder = row == 0 || row == height - 1 || column == 0 || column == width - 1;

        if (ignoreBorder && onBorder) {

            //setState(column, row, *pastGrid);
            fillBorder(row,column,*pastGrid);

            if (mGrid.value(column,row) == State::alive) {  //verifie la ouvelle valeur de la grille
                (*mNewStats.totalAliveAbs)++;
            }
            else {
                (*mNewStats.totalDeadAbs)++;
            }
        }
        else {

            int alive = getAliveAround(column, row, onBorder, pastGrid); //retourne le nombre de cellules vivantes sur la cellule avant modification de la grille

            if (mGrid.value(column, row) == State::alive) { //verifie la valeur presente, si la cellule est vivante

                (*mStats.totalAliveAbs)++;                

                if (!mSurviveRule[alive]) { //si le nombre vivant autour de la cellule ne respecte pas la regle de survie
                    //setState(column, row, State::dead);   //on n'utilise pas la fonction setState car elle modifie les statistiques de l'ancienne grille
                    mGrid.setValue(column, row, State::dead); 
                    (*mNewStats.totalDeadAbs)++;
                }
                else {
                    (*mNewStats.totalAliveAbs)++;
                }
            }
            else {
                (*mStats.totalDeadAbs)++;

                if (mBornRule[alive]) {
                
                    mGrid.setValue(column, row, State::alive);
                    (*mNewStats.totalAliveAbs)++;
                }   
                else {
                    (*mNewStats.totalDeadAbs)++;
                }
            }
        }
        ++pastGrid;
    }
    mStats.iteration = ++mIteration;
    tendencyCal();  //a faire avant de swap les stats

    //petit bug, j'ai remarqué qu'on retourné les stats de l'ancienne grille donc apres un onestep les stats ne faisait pas de sense
    //pour l'instant les deux prochaines lignes regles le problemes donc on peut laisser ca de meme pour l'instant
    mStats.totalAliveAbs = mNewStats.totalAliveAbs;
    mStats.totalDeadAbs = mNewStats.totalDeadAbs;

    relStats();

    

    /************************************************************************************************************************************************************************/

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


int GOLTeamK::getAliveAround(int column, int row, bool onBorder, State* pastGrid)
{
    int aliveCells = 0;
    int width = mGrid.getWidth();
    int height = mGrid.getHeight();

    //Des pointeurs de State qui pointent autour de la cellule
    State* topLeft = pastGrid - width - 1;
    State* top = pastGrid - width;
    State* topRight = pastGrid - width + 1;
    State* left = pastGrid - 1;
    State* right = pastGrid + 1;
    State* bottomLeft = pastGrid + width - 1;
    State* bottom = pastGrid + width;
    State* bottomRight = pastGrid + width + 1;


    if (mBorderManagement == BorderManagement::mirror && onBorder) {
        if (row == 0 && column == 0) {
            if (*right == State::alive) {
                aliveCells += 2;
            }
            if (*bottom == State::alive) {
                aliveCells += 2;
            }
            if (*bottomRight == State::alive) {
                aliveCells += 2;
            }
        }
        else if (row == 0 && column == height - 1) {
            if (*right == State::alive) {
                aliveCells += 2;
            }
            if (*top == State::alive) {
                aliveCells += 2;
            }
            if (*topRight == State::alive) {
                aliveCells += 2;
            }
        }
        else if (row == 0) {
            if (*top == State::alive) {
                ++aliveCells;
            }
            if (*topRight == State::alive) {
                aliveCells += 2;
            }
            if (*right == State::alive) {
                aliveCells += 2;
            }
            if (*bottom == State::alive) {
                ++aliveCells;
            }
            if (*bottomRight == State::alive) {
                aliveCells += 2;
            }

        }
        else if (row == width - 1 && column == 0) {
            if (*left == State::alive) {
                aliveCells += 2;
            }
            if (*bottom == State::alive) {
                aliveCells += 2;
            }
            if (*bottomLeft == State::alive) {
                aliveCells += 2;
            }
        }
        else if (row == width - 1 && column == height - 1) {
            if (*left == State::alive) {
                aliveCells += 2;
            }
            if (*top == State::alive) {
                aliveCells += 2;
            }
            if (*topLeft == State::alive) {
                aliveCells += 2;
            }
        }
        else if (row == width - 1) {
            if (*top == State::alive) {
                ++aliveCells;
            }
            if (*topLeft == State::alive) {
                aliveCells += 2;
            }
            if (*left == State::alive) {
                aliveCells += 2;
            }
            if (*bottom == State::alive) {
                ++aliveCells;
            }
            if (*bottomLeft == State::alive) {
                aliveCells += 2;
            }

        }
    }
    else if (mBorderManagement == BorderManagement::warping && onBorder) {
        if (row == 0 && column == 0) {
            topLeft = pastGrid + (width * height - 1);
            top = pastGrid + (height * (width - 1));
            topRight = pastGrid + (height * (width - 1) + 1);
            left = pastGrid + width - 1;
            bottomLeft = pastGrid + (2 * width - 1);
        }
        else if (row == 0 && column == height - 1) {
            topLeft = pastGrid - 1;
            left = pastGrid + width - 1;
            bottomLeft = pastGrid - (width * (height - 2) - 1);
            bottom = pastGrid - (width * (height - 1));
            bottomRight = pastGrid - (width * (height - 1) + 1);
        }
        else if (row == 0) {
            topLeft = pastGrid + (2 * width) - 1;                     //Equivalent de bottomLeft (Left->topLeft, bottomLeft->Left) 
        }
        else if (row == width - 1 && column == 0) {
            topLeft = pastGrid + (width * (height - 1) - 1);
            top = pastGrid + (width * (height - 1));
            topRight = pastGrid + (width * (height - 2) + 1);
            right = pastGrid - width + 1;
            bottomRight = pastGrid + 1;
        }
        else if (row == width - 1 && column == height - 1) {
            topRight = pastGrid - (width * (height - 2)) + 1;
            right = pastGrid - width + 1;
            bottomLeft = pastGrid - (width * height) + 1;
            bottom = pastGrid - (width * (height - 1));
            bottomRight = pastGrid - (width * (height - 1)) - 1;
        }
        else if (row == width - 1) {
            bottomRight = pastGrid - (2 * width) + 1;                 //Equivalent de topRight (Right->bottomRight, bottomRight->Right)
        }
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

        return aliveCells;  //retourne le nombre de cellules vivantes
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

void GOLTeamK::copyGrid()
{
    int size = mGrid.getSize();
    int height = mGrid.getHeight();
    int width = mGrid.getWidth();
    State* grid = mGrid.data();

    for (int i{}; i < size; ++i) {
        int row = i / width;
        int column = i % width;
        mPastGrid.setValue(row, column, *(grid + i));
    }
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