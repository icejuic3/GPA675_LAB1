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
	//Le pointeur est initialis� avec l'adresse de mGrid
	//et on incr�mente le pointeur tant qu'il est plus petit
	//que l'adresse du d�but+le nombre de cellule n�cessaire.

	for (DataType cur{mGrid}; cur < mGrid + mSize; ++cur) {			
		*cur = initValue;											//l'�tat est sauvegarder a l'endroit o� pointe le pointeur
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
	//nous pouvons tout  simplement suprimer notre pointeur mGrid pour lib�rer la m�moire
	delete[] mGrid;							
	mGrid = nullptr;					//nous devons mettre le pointeur a nullptr car il n'est pas utilis�
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
	gridDelete();													//appel la fonction pour lib�rer la m�moire

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
	//(row * mWidth) nous permet de trouver sur quelle rang�e nous sommes
	//ensuite nous avons juste � additionner la colonne de notre position
	return mGrid[row * mWidth + (column)];								
}

void GridTeamK::setValue(int column, int row, CellType value)
{
	mGrid[row * mWidth + (column)] = value;
}

optional<CellType> GridTeamK::at(int column, int row) const
{
	//V�rification que la rang�e et la colonne sont valide
	if (row >= 0 && row < mHeight && column >= 0 && column < mWidth) {
		return mGrid[row * mWidth + (column)];
	}
	return nullopt;
}

void GridTeamK::setAt(int column, int row, CellType value)
{
	//V�rification que la rang�e et la colonne sont valide
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

