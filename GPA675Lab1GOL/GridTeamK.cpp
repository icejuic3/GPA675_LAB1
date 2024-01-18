#include "GridTeamK.h"

GridTeamK::GridTeamK() 
	:mWidth{0}
	,mHeight{0}
	, mSize{ mWidth* mHeight }
	, mGrid{ new CellType[mSize] }
{
}

GridTeamK::GridTeamK(size_t width, size_t height, CellType initValue)
	:mWidth{ width }
	, mHeight{ height }
	, mSize{ width * height }
	, mGrid{ new CellType[mSize]}
{
	for (CellType * i; i < mSize; ++i) {
		*i = initValue;
	}
}


GridTeamK::~GridTeamK()
{
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
