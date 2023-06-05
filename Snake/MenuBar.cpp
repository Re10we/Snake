#include "MenuBar.h"

MenuBar::MenuBar()
{
	CurrentSelectionInMenu = 0;
	LastSelection = 0;
	MaxSample = 0;
}

void MenuBar::NextSelect(int8_t AddValue)
{
	LastSelection = CurrentSelectionInMenu;

	if (CurrentSelectionInMenu + AddValue < 0)
	{
		CurrentSelectionInMenu = MaxSample - 1;
	}
	else
	{
		CurrentSelectionInMenu = (CurrentSelectionInMenu + AddValue) % MaxSample;
	}
}


void MenuBar::SetMaxSample(uint8_t NewValue)
{
	MaxSample = NewValue;
}


uint8_t MenuBar::GetLastSelection() const
{
	return LastSelection;
}


uint8_t MenuBar::GetCurrentSelection() const
{
	return CurrentSelectionInMenu;
}