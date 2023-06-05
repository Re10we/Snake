#include "Food.h"

Food::Food()
{
	Prize = 10;
	CoordX = 0;
	CoordY = 0;
}

std::pair<uint32_t, uint32_t> Food::GetCoordinateObject() const
{
	return std::pair<uint32_t, uint32_t>(CoordX, CoordY);
}

void Food::SetCoordinateObject(uint32_t NewCoordX, uint32_t NewCoordY)
{
	this->CoordX = NewCoordX;
	this->CoordY = NewCoordY;
}

void Food::SetPrizeOfFood(uint32_t Value)
{
	if (Value > 0)
	{
		Prize = Value;
	}
}

uint32_t Food::GetPrizeOfFood() const
{
	return Prize;
}
