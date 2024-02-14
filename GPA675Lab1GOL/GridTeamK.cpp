#include "GridTeamK.h"

GridTeamK::GridTeamK() 
	:mWidth{ 0 }						
	,mHeight{ 0 }						
	,mSize{ 0 }
	,mGrid{ nullptr }		
{
}

GridTeamK::GridTeamK(size_t width, size_t height, CellType initValue)
	:mWidth{ width }												//column
	,mHeight{ height }												//row
	,mSize{ width * height }										//taille du tableau unidimensionnel
	,mGrid{ new CellType  [mSize]}									//initialisation du pointeur de ligne
{
	//Le pointeur est initialisé avec l'adresse de mGrid
	//et on incrémente le pointeur tant qu'il est plus petit
	//que l'adresse du début+le nombre de cellule nécessaire.

	for (DataType cur{mGrid}; cur < mGrid + mSize; ++cur) {			
		*cur = initValue;											//l'état est sauvegarder a l'endroit où pointe le pointeur
	}
}

GridTeamK& GridTeamK::operator=(GridTeamK const&)
{
	return *this;
}

GridTeamK::~GridTeamK()
{
	gridDelete();
}

void GridTeamK::gridDelete()
{
	//Puisque nous travaillons avec un tableau unidimensionnel
	//nous pouvons tout  simplement suprimer notre pointeur mGrid pour libérer la mémoire
	delete[] mGrid;							
	mGrid = nullptr;					//nous devons mettre le pointeur a nullptr car il n'est pas utilisé
}

size_t GridTeamK::getWidth() const
{
	return mWidth;
}

size_t GridTeamK::getHeight() const
{
	return mHeight;
}

size_t GridTeamK::getSize() const
{
	return mSize;
}

void GridTeamK::resize(size_t width, size_t height, CellType initValue)
{
	gridDelete();													//appel la fonction pour libérer la mémoire

	mWidth = width;
	mHeight = height;
	mSize = width * height;
	mGrid = new CellType [mSize];									//initialise mGrid avec la nouvelle taille

	for (DataType cur{ mGrid }; cur < mGrid + mSize; ++cur) {

		*cur = initValue;
	}
}

CellType GridTeamK::value(int column, int row) const
{
	//(row * mWidth) nous permet de trouver sur quelle rangée nous sommes
	//ensuite nous avons juste à additionner la colonne de notre position
	return mGrid[row * mWidth + (column)];								
}

void GridTeamK::setValue(int column, int row, CellType value)
{
	mGrid[row * mWidth + (column)] = value;
}

optional<CellType> GridTeamK::at(int column, int row) const
{
	//Vérification que la rangée et la colonne sont valide
	if (row >= 0 && row < mHeight && column >= 0 && column < mWidth) {
		return mGrid[row * mWidth + (column)];
	}
	return nullopt;
}

void GridTeamK::setAt(int column, int row, CellType value)
{
	//Vérification que la rangée et la colonne sont valide
	if (row >= 0 && row < mHeight && column >= 0 && column < mWidth) {
		mGrid[row * mWidth + (column)] = value;
	}
}

DataType const& GridTeamK::data() const
{
	return mGrid;
}

DataType& GridTeamK::data()
{
	return mGrid;
}

