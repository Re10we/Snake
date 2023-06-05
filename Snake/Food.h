#pragma once
#include <iostream>

class Food
{
public:

	Food();

	//Getter & setter for coordinate by object
	std::pair<uint32_t, uint32_t> GetCoordinateObject() const;
	void SetCoordinateObject(uint32_t NewCoordX, uint32_t NewCoordY);

	//Getter & setter for prize of food
	void SetPrizeOfFood(uint32_t Value);
	uint32_t GetPrizeOfFood() const;

private:

	uint32_t Prize;
	uint32_t CoordX;
	uint32_t CoordY;

};