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
	for (size_t i{}; i < height; i++) {

		mGrid[i] = new CellType [width];

		for (size_t j{}; j < width; j++) {

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
	//resize?
}

CellType GridTeamK::value(int column, int row) const
{
	return CellType();
}

void GridTeamK::setValue(int column, int row, CellType value)
{
}

void GridTeamK::setAt(int column, int row, CellType value)
{
}

DataType const& GridTeamK::data() const
{
	// TODO: insert return statement here
}

DataType& GridTeamK::data()
{
	// TODO: insert return statement here
}
