#pragma once
#include <iostream>

class MenuBar
{
public:

	MenuBar();

	// Move to next element
	void NextSelect(int8_t AddValue);

	// Maximum number of menu items
	void SetMaxSample(uint8_t NewValue);

	//Getting Last player choice
	uint8_t GetLastSelection() const;

	//Getting Current player choice
	uint8_t GetCurrentSelection() const;

private:

	uint8_t CurrentSelectionInMenu;
	uint8_t LastSelection;
	uint8_t MaxSample;

};