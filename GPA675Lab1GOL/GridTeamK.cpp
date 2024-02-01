#include "GridTeamK.h"

GridTeamK::GridTeamK() 
	:mWidth{ 0 }						
	,mHeight{ 0 }						
	,mSize{ 0 }
	,mGrid{ nullptr }		
{
}

GridTeamK::GridTeamK(size_t width, size_t height, CellType initValue)
	:mWidth{ width }						//column
	,mHeight{ height }						//row
	,mSize{ width * height }
	,mGrid{ new CellType  [mSize]}		//initialisation du pointeur de ligne
{

	for (DataType cur{mGrid}; cur < mGrid + mSize; ++cur) {

		*cur = initValue;
	}


	//for (size_t row{}; row < height; row++) {

	//	mGrid[row] = new CellType [width];	//initialisation du pointeur de colonne

	//	for (size_t column{}; column < width; column++) {

	//		mGrid[row][column] = initValue;
	//	}
	//}
}

GridTeamK::~GridTeamK()
{
	gridDelete();
}

void GridTeamK::gridDelete()
{
	delete[] mGrid;
	mGrid = nullptr;
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
	gridDelete();

	mWidth = width;
	mHeight = height;
	mSize = width * height;
	mGrid = new CellType [mSize];			//initialise mGrid avec la nouvelle taille


	for (DataType cur{ mGrid }; cur < mGrid + mSize; ++cur) {

		*cur = initValue;
	}


	//for (size_t row{}; row < height; row++) {

	//	mGrid[row] = new CellType[width];

	//	for (size_t column{}; column < width; column++) {

	//		mGrid[row][column] = initValue;
	//	}
	//}
}

CellType GridTeamK::value(int column, int row) const
{

	return mGrid[row * mWidth + (column)];

	//return mGrid[row][column];
}

void GridTeamK::setValue(int column, int row, CellType value)
{
	mGrid[row * mWidth + (column)] = value;


	//mGrid[row][column] = value;
}

optional<CellType> GridTeamK::at(int column, int row) const
{
	if (row >= 0 && row < mHeight && column >= 0 && column < mWidth) {
		return mGrid[row * mWidth + (column)];
	}
	return nullopt;
}

void GridTeamK::setAt(int column, int row, CellType value)
{
	if (row >= 0 && row < mHeight && column >= 0 && column < mWidth) {
		mGrid[row * mWidth + (column)] = value;
	}
}

DataType const& GridTeamK::data() const
{
	return mGrid; //a changer
}

DataType& GridTeamK::data()
{
	return mGrid; //a changer
}

