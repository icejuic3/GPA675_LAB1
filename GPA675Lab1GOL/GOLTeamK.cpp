#include "GOLTeamK.h"

GOLTeamK::GOLTeamK()
{
    setInformation();
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
    , mNewStats{}
{
    setInformation();
}

GOLTeamK::~GOLTeamK()
{
}

void GOLTeamK::setInformation()
{
    mInfo.title = "Game of life Team K";
    mInfo.authors = { {"Curiel - Garfias","Jacob","jacob.curiel-garfias.1@ens.etsmtl.ca"}, {"David-Way","William","william.david-way.1@ens.etsmtl.ca"}};
    mInfo.answers = {{"1. Nous avons utilisé un tableau à une dimension que nous gérons grâce à un pointeur qui se déplace dans la mémoire selon les colonnes et les rangées"
                      "Déterminées par l'utilisateur. Le tableau est et le pointeur sont créés a la création d'un objet GridTeamK, le tableau est supprimé et le pointeur mis a nullptr"
                      "lors de l'appel du destructeur. Il en est de même lors de la fonction resize, ou on détruit la grille actuelle et en crée une nouvelle selon les nouvelles dimensions." },
                     {"2. La fonction processOneStep commence par faire une copie des données de la grille actuelle dans une autre grille représentant l'état passe de celle-ci, puis parcours"
                      "la grille au complet (sauf la bordure dans les cas où celle-ci reste identique) en vérifiant l'état des cases qui entourent la case évaluée présentement dans la grille"
                      "de l'état passe, puis modifie la case évaluée dans la grille principale selon les règles de mort ou de survie. Les statistiques de la grille sont également mises à jour."},
                     {"3.Dans une boucle while qui reste vraie tant que notre index est plus petit que la taille du tampon, nous vérifions pour chaque cellule son état."
                      "Si la cellule est vivante, la couleur de mAliveColor est utilisée. Sinon, la couleur de mDeadColor est utilisée."
                      "La couleur est sauvegardée dans un objet de type Color qui contient les composantes rouge, vertes et bleues de notre couleur."
                      "Ensuite, nous mettons à jour la couleur du buffer sous un format ARGB à la position (buffer+x)."
                      "Nous incrémentons nos variables, l'index x pour la position suivante du buffer et le pointeur myGrid pour la prochaine cellule de la grille."
                      "Puisque Color est une struct contenant 3 bandes de couleurs de type uint8_t, nous devons mettre (0xff) avant nos bandes de couleur dans le buffer car elle représente l'opacité."
                      "Remarque que Buffer est de type uint32_t, contenant 32 bit au total pour le format ARGB et notre struct Color est composé seulement de 24 bit."},
                     {"4. Nous avons créer des variables membres de GOLTeamK sous la forme d'un tableau de 9 booléen représentant la règle de naissance et la règle de survie. Lors de la lecture"
                      "de la règle il suffisait à mettre les positions associées au nombre souhaité par la règle à leur valeur booléenne. Puis, lors de l'exécution, on utilise le nombre de"
                      "cellules vivantes autour de la cellule évaluée comme index des tableaux pour déterminer si la naissance ou la survive de cette dernière est vraie."},
                     {"5. Pour les trois stratégies qui n'évaluent pas les bords (immutableAsIs, foreverDead et foreverAlive), nous avons simplement fait le remplissage approprie des bords lors du"
                      "remplissage de la grille, puis ignore les cellules de bordure lors de notre processOneStep. Lorsqu'on évalue que la gestion de bordure est mirror et que la cellule évaluée."
                      "est située sur la bordure, nous comptons seulement les cases de la grille nécessaires en double. Lorsque la gestion de bordure est warping et que la cellule évaluée est sur"
                      "la bordure, on modifie les pointeurs qui pointeraient normalement à une position à l'extérieur de la grille pour qu'ils pointent à la position représentant le côté opposé."}};
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
    //nous utilisons le static_cast pour convertir le chiffre entier size_t en un chiffre de type Float
    mStats.totalAliveRel = static_cast<float>(*mStats.totalAliveAbs) / (*mStats.totalCells);
    mStats.totalDeadRel = static_cast<float>(*mStats.totalDeadAbs) / (*mStats.totalCells);
}

void GOLTeamK::tendencyCal()
{
    //nouc calculons la tendence avec en utilisant l'éqution suivante: tendency = (NewTotalAlive - OldTotalAlive ) - (NewTotalDead - OldTotalDead)
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
    //vérifie si les coordonnées se trouvent sur une bordure
    if (row == 0 || row == mGrid.getHeight() - 1 || column == 0 || column == mGrid.getWidth() - 1) {

        return true;
    }
    return false;
}

bool GOLTeamK::ignoreBorder()
{
    //Vérifie si la bordure est modifiable 
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
    else if (mBorderManagement == BorderManagement::immutableAsIs) {    //sinon la cellule garde son état tel quel
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
    return mGrid.value(x, y);       
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
    //retourne la couleur de la cellule
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
    resetStats();                                                   //nous remettons nos statistiques à zéro
    if (width == 0 || height == 0) {
        width = 0;
        height = 0;
    }

    mGrid.resize(width, height, defaultState);                      //on redimensionne notre grille
    mPastGrid.resize(width, height, defaultState);                  //ainsi que la grille de copie pour le OneStep

    mStats.iteration = mIteration = 0;                              //L'itération courante est remise à 0.
    mStats.height = mGrid.getHeight();                              //Les statistiques sont mises à jours avec les nouvelles dimensions
    mStats.width = mGrid.getWidth();
    mStats.totalCells = mGrid.getSize();

    //ajustement des couleurs de bordures
    for (size_t i{}; i < mGrid.getSize(); i++) {

        size_t column = i % mGrid.getWidth();
        size_t row = i / mGrid.getWidth();

        if (onBorder(row, column) && ignoreBorder()) {              //Si nous avons une bordure qui doit avoir un état précis

            fillBorder(row, column, mGrid.value(column, row));      //alors la modification est appliquée
        }
        else {
            setStats(defaultState);
        }
    }
    relStats();                                                     //Nous mettons à jour nos statistiques après avoir compté le nombre de cellules mortes et vivantes
}

bool GOLTeamK::setRule(std::string const& rule)
{
    const std::regex pattern{ "^B([0-8]{0,9})/S([0-8]{0,9})$", std::regex_constants::icase };   //format de la règle qui doit être respecté
    std::smatch matches;

    if (std::regex_match(rule, matches, pattern)) {                 //Vérification que la régle de l'utilisateur est valide
        mStats.rule = mRule = rule;                                 //sauvegarde la règle dans stats et mRule

        //initialisation des tableaux 
        for (int i{}; i < 9; ++i) {
            mBornRule[i] = false;
            mSurviveRule[i] = false;
        }

        // Extrait les chiffres de la partie born de la règle et les marque comme true dans mBornRule.
        std::ssub_match bornNumbers = matches[1];
        std::string bornString = bornNumbers.str();
        for (char digit : bornString) {
            int num = digit - '0';
            mBornRule[num] = true;
        }

        // Extrait les chiffres de la partie Survive de la règle et les marque comme true dans mSurviveRule.
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
        
        fill(State::dead);

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

    if (ignoreBorder()) {                                               //verifie si le remplissage de bordure est nécessaire
        resetStats();                                                   //mise à zéro des statistiques

        for (size_t i{}; i < mGrid.getSize(); ++i) {

            size_t column = i % mGrid.getWidth();
            size_t row = i / mGrid.getWidth();

            if (onBorder(row, column)) {                                //vérification de bordure

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
    setStats(state);
}

void GOLTeamK::fill(State state)
{
    resetStats();                                           //les stats sont remis à zéro

    for (size_t i{}; i < mGrid.getSize(); ++i) {            //vérifie chaque cellules de la grille

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
    State oppositeState = getOppositeState(firstCell);  //sauvegarde l'état opposé de la cellule actuelle

    for (size_t i{}; i < mGrid.getSize(); ++i) {

        size_t column = i % mGrid.getWidth();
        size_t row = i / mGrid.getWidth();
        State cellstate = ((row + column) % 2 == 0) ? firstCell : oppositeState;    //l'opperateur ? resume cette ligne à --> Si VRAI alors cellstate vaut firstcell, sinon elle vaut oppositeState

        if (onBorder(row, column) && ignoreBorder()) {                              //vérification de bordure    

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

        if (onBorder(row, column) && ignoreBorder()) {      //vérification de bordure

            fillBorder(row, column, cellstate);
        }
        else {
            setState(column, row, cellstate);
        }
    }
    relStats();                                             //mise à jour des statistiques
    mStats.iteration = mIteration = 0;                      //mise à zéro des itération
}

void GOLTeamK::setSolidColor(State state, Color const& color)
{
    //mettre les nouvelles couleurs pour les couleurs vivantes et mortes
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

    for (size_t i{}; i < size; ++i) {
        int column = i % width;
        int row = i / width;
        bool onBorder = row == 0 || row == height - 1 || column == 0 || column == width - 1;

        if (ignoreBorder && onBorder) {
            fillBorder(row,column,*pastGrid);

            if (mGrid.value(column,row) == State::alive) {                  //verifie la nouvelle valeur de la grille
                (*mNewStats.totalAliveAbs)++;
            }
            else {
                (*mNewStats.totalDeadAbs)++;
            }
        }
        else {

            int alive = getAliveAround(column, row, onBorder, pastGrid);    //retourne le nombre de cellules vivantes sur la cellule avant modification de la grille

            if (mGrid.value(column, row) == State::alive) {                 //verifie si la cellule est vivante

                (*mStats.totalAliveAbs)++;                                  //si oui on incrémente notre statistique de cellules vivantes

                //traitement des cellules en fonction des règles de survie
                if (!mSurviveRule[alive]) {                                 
                //on n'utilise pas la fonction setState car elle modifie les statistiques de l'ancienne grille
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
        ++pastGrid;                                                         //passe à la prochaine cellule de la grille avant modification
    }
    mStats.iteration = ++mIteration;
    tendencyCal();                                                          //à faire avant de modifier les stats
    mStats.totalAliveAbs = mNewStats.totalAliveAbs;
    mStats.totalDeadAbs = mNewStats.totalDeadAbs;

    relStats();
}

void GOLTeamK::updateImage(uint32_t* buffer, size_t buffer_size) const
{
    size_t x{};                                                                                             //index pour parcourir le buffer
    DataType myGrid{ mGrid.data() };                                                                        //myGrid est de type Celltype*
  
    while (x < buffer_size) {                                                                               // Parcourt le tampon de l'image

        Color cellColor = (*myGrid == State::alive) ? mAliveColor : mDeadColor;                             // Si la cellule est vivante, utilise mAliveColor; sinon, utilise mDeadColor.

        // Met à jour la couleur de la cellule dans le buffer.
        // Format ARGB : 0xff pour l'opacité (Alpha), puis les composantes Rouge, Verte, Bleue.
        *(buffer + x) = (0xff << 24) | (cellColor.red << 16) | (cellColor.green << 8) | cellColor.blue;

        // Incrémente les pointeurs pour passer à la cellule suivante
        ++x;
        ++myGrid;
    }
}

int GOLTeamK::getAliveAround(int column, int row, bool onBorder, State* pastGrid)
{

    int aliveCells = 0;                 // Compteur pour les cellules vivantes
    int width = mGrid.getWidth();       // Largeur de la grille
    int height = mGrid.getHeight();     // Hauteur de la grille

    //Des pointeurs de State qui pointent autour de la cellule
    State* topLeft = pastGrid - width - 1;
    State* top = pastGrid - width;
    State* topRight = pastGrid - width + 1;
    State* left = pastGrid - 1;
    State* right = pastGrid + 1;
    State* bottomLeft = pastGrid + width - 1;
    State* bottom = pastGrid + width;
    State* bottomRight = pastGrid + width + 1;

    //Vérifie si la grille est gérée avec une bordure mirror ou warping
    // alors le calcul des cellules vivantes est ajusté pour refléter cela.
    if (mBorderManagement == BorderManagement::mirror && onBorder) {
        if (row == 0 && column == 0) {
            if (*right == State::alive) {
                aliveCells += 2;
            }
            if (*bottom == State::alive) {
                aliveCells += 2;
            }
            if (*bottomRight == State::alive) {
                aliveCells += 4;
            }
        }
        else if (row == 0 && column == width - 1) {
            if (*left == State::alive) {
                aliveCells += 2;
            }
            if (*bottomLeft == State::alive) {
                aliveCells += 4;
            }
            if (*bottom == State::alive) {
                aliveCells += 2;
            }
        }
        else if (column == 0 && row == height - 1) {
            if (*right == State::alive) {
                aliveCells += 2;
            }
            if (*topRight == State::alive) {
                aliveCells += 4;
            }
            if (*top == State::alive) {
                aliveCells += 2;
            }
        }
        else if (row == height - 1 && column == width - 1) {
            if (*left == State::alive) {
                aliveCells += 2;
            }
            if (*top == State::alive) {
                aliveCells += 2;
            }
            if (*topLeft == State::alive) {
                aliveCells += 4;
            }
        }
        else if (row == 0) {
            if (*left == State::alive) {
                ++aliveCells;
            }
            if (*right == State::alive) {
                ++aliveCells;
            }
            if (*bottomLeft == State::alive) {
                aliveCells += 2;
            }
            if (*bottom == State::alive) {
                aliveCells += 2;
            }
            if (*bottomRight == State::alive) {
                aliveCells += 2;
            }

        }
        else if (column == 0) {
            if (*topRight == State::alive) {
                aliveCells+=2;
            }
            if (*right == State::alive) {
                aliveCells+=2;
            }
            if (*bottomRight == State::alive) {
                aliveCells+=2;
            }
            if (*top == State::alive) {
                ++aliveCells;
            }
            if (*bottom == State::alive) {
                ++aliveCells;
            }
        }
        else if (row == height - 1) {
            if (*top == State::alive) {
                aliveCells+=2;
            }
            if (*topLeft == State::alive) {
                aliveCells+=2;
            }
            if (*topRight == State::alive) {
                aliveCells+=2;
            }
            if (*left == State::alive) {
                ++aliveCells;
            }
            if (*right == State::alive) {
                ++aliveCells;
            }
        }
        else if (column == width-1) {
            if (*topLeft == State::alive) {
                aliveCells += 2;
            }
            if (*left == State::alive) {
                aliveCells += 2;
            }
            if (*bottomLeft == State::alive) {
                aliveCells += 2;
            }
            if (*top == State::alive) {
                ++aliveCells;
            }
            if (*bottom == State::alive) {
                ++aliveCells;
            }
        }
    }
    else {
        if (mBorderManagement == BorderManagement::warping && onBorder) {
            if (row == 0 && column == 0) {
                topLeft = pastGrid + width * height - 1;
                top = pastGrid + width * (height - 1);
                topRight = pastGrid + width * (height - 1) + 1;
                left = pastGrid + width - 1;
                bottomLeft = pastGrid + 2 * width - 1;
            }
            else if (row == 0 && column == width - 1) {
                topLeft = pastGrid + width * (height - 1) - 1;
                top = pastGrid + width * (height - 1);
                topRight = pastGrid + width * (height - 2) + 1;
                right = pastGrid - (width - 1);
                bottomRight = pastGrid + 1;
            }
            else if (column == 0 && row == height - 1) {
                //topLeft = oldLeft;
                topLeft = pastGrid + width - 1;        //newLeft
                bottomLeft = pastGrid - width * (height - 2) - 1;
                bottom = pastGrid - width * (height - 1);
                bottomRight = pastGrid - width * (height - 1) + 1;
            }
            else if (row == height - 1 && column == width - 1) {
                topRight = pastGrid - (width * 2) + 1;
                right = pastGrid - width + 1;
                bottomRight = pastGrid - width * height + 1;
                bottom = pastGrid - width * (height - 1);
                bottomLeft = pastGrid - width * (height - 1) - 1;
            }
            else if (row == 0) {
                topLeft = pastGrid + width * (height - 1) - 1;
                top = pastGrid + width * (height - 1);
                topRight = pastGrid + width * (height - 1) + 1;
            }
            else if (column == 0) {
                topLeft = pastGrid + (2 * width) - 1;                     //Equivalent de bottomLeft (Left->topLeft, bottomLeft->Left) 
            }
            else if (column == width - 1) {
                bottomRight = pastGrid - (2 * width) + 1;                 //Equivalent de topRight (Right->bottomRight, topRight->Right)
            }
            else if (row == height - 1) {
                bottomLeft = pastGrid - width * (height - 1) - 1;
                bottom = pastGrid - width * (height - 1);
                bottomRight = pastGrid - width * (height - 1) + 1;
            }
        }
        // on compte simplement le nombre de cellules vivantes parmi les 8 cellules voisines.
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
    }

    return aliveCells; //retourne le nombre de cellules vivantes
}

void GOLTeamK::copyGrid()
{
    int size = mGrid.getSize();
    int height = mGrid.getHeight();
    int width = mGrid.getWidth();
    State* grid = mGrid.data();                 //pointeur vers les données de la grille

    for (int i{}; i < size; ++i) {
        int column = i % width;
        int row = i / width;
        mPastGrid.setValue(column,row, *(grid + i));    // Copie l'état de la cellule vers mPastGrid à la position correspondante
    }
}

GOL::State GOLTeamK::getOppositeState(State state)
{
    if (state == State::alive) {

        return State::dead;         // Si la cellule est vivante, retourne l'état mort
    }
    else {

        return State::alive;        // Sinon, si la cellule est morte, retourne l'état vivant
    }
}