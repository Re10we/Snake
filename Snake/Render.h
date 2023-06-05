#pragma once
#include <iostream>
#include <windows.h>

class Render
{
public:

	Render();

	// Getter & Setter window height
	void SetWindowHeight(uint32_t NewValue);
	uint32_t GetWindowHeight() const;

	// Getter & Setter window width
	void SetWindowWidth(uint32_t NewValue);
	uint32_t GetWindowWidth() const;

	// Draw game area for game
	void DrawAreaForGame() const;

	// Draw menubar
	void DrawMainMenu() const;

	// Draw table result for player
	void DrawScreenResult(uint32_t CoordX, uint32_t CoordY, uint16_t Score) const;

	// Draw any element
	void DrawObject2D(uint32_t CoordX, uint32_t CoordY, std::string StrValue) const;
	void DrawObject2D(uint32_t CoordX, uint32_t CoordY, char ChValue) const;

	// Clear console
	void Cls() const;

protected:

	// Control cursor pos
	void SetCursorPosition(uint32_t CoordX, uint32_t CoordY) const;

private:

	// The number of characters of the window in width & height
	uint32_t WindowWidth;
	uint32_t WindowHeight;

};