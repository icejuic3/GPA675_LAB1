#include "GridTeamK.h"

GridTeamK::GridTeamK() 
	:mWidth{0}
	,mHeight{0}
	,mSize{ mWidth* mHeight }
	,mGrid{ new CellType* [mSize] }
{
}

GridTeamK::GridTeamK(size_t width, size_t height, CellType initValue)
	:mWidth{ width }
	,mHeight{ height }
	,mSize{ width * height }
	,mGrid{ new CellType * [height] }
{
	for (size_t i{}; i < width; i++) {

		mGrid[i] = new CellType [width];

		for (size_t j{}; j < height; j++) {

			mGrid[i][j] = initValue;
		}
	}
}

GridTeamK::~GridTeamK()
{
	for (size_t i{}; i < mHeight; i++) {

		delete[] mGrid[i];
	}
	delete[] mGrid;
	mGrid = nullptr;
}

size_t GridTeamK::width() const
{
	return mWidth;
}

size_t GridTeamK::height() const
{
	return mHeight;
}

size_t GridTeamK::size() const
{
	return mSize;
}

void GridTeamK::resize(size_t width, size_t height, CellType initValue)
{
	mWidth = width;
	mHeight = height;
	mSize = width * height;
	mGrid = new CellType * [height];			//initialise mGrid avec la nouvelle taille

	for (size_t i{}; i < height; i++) {

		mGrid[i] = new CellType[width];

		for (size_t j{}; j < width; j++) {

			mGrid[i][j] = initValue;
		}
	}
}

CellType GridTeamK::value(int column, int row) const
{
	return mGrid[row][column];
}

void GridTeamK::setValue(int column, int row, CellType value)
{
	mGrid[row][column] = value;
}

optional<CellType> GridTeamK::at(int column, int row) const
{
	if (row >= 0 && row < mHeight && column >= 0 && column < mWidth) {
		return mGrid[row][column];
	}
	return nullopt;
}

void GridTeamK::setAt(int column, int row, CellType value)
{
	if (row >= 0 && row < mHeight && column >= 0 && column < mWidth) {
		mGrid[row][column] = value;
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

