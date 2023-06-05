#include "Render.h"

Render::Render()
{
	WindowWidth = 0;
	WindowHeight = 0;
}

// x is the column, y is the row. The origin (0,0) is top-left.
void Render::SetCursorPosition(uint32_t CoordX, uint32_t CoordY) const
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();

	COORD Coord = { (SHORT)CoordX, (SHORT)CoordY };
	SetConsoleCursorPosition(hOut, Coord);
}

void Render::SetWindowHeight(uint32_t NewValue)
{
	WindowHeight = NewValue;
}

uint32_t Render::GetWindowHeight() const
{
	return WindowHeight;
}

void Render::SetWindowWidth(uint32_t NewValue)
{
	WindowWidth = NewValue;
}

uint32_t Render::GetWindowWidth() const
{
	return WindowWidth;
}

void Render::DrawAreaForGame() const
{
	Cls();

	std::string CustomLine;
	std::string MainLine;

	// Remember top & bottom border
	for (uint32_t index = 0; index < WindowWidth - 2; index++)
	{
		CustomLine.push_back(static_cast<char>(205));
	}

	// Draw top border
	std::cout << static_cast<char>(201) << CustomLine << static_cast<char>(187);

	for (uint32_t IndexY = 0; IndexY < WindowHeight - 3; IndexY++)
	{
		MainLine.clear();

		for (uint32_t IndexX = 0; IndexX < WindowWidth; IndexX++)
		{
			if (IndexX == 0 || IndexX == WindowWidth - 1)
			{
				// Remember characters for main line
				MainLine.push_back(static_cast<char>(186));
			}
			else
			{
				// Remember characters for main line
				MainLine.push_back(' ');
			}
		}

		// Draw result main line
		std::cout << MainLine << '\n';
	}

	// Draw bottom border
	std::cout << static_cast<char>(200) << CustomLine << static_cast<char>(188);
}

void Render::DrawMainMenu() const
{
	Cls();

	SetCursorPosition((GetWindowWidth() / 2) - 5, (GetWindowHeight() / 2) - 5);
	std::cout << "[ ]" << "Start game";

	SetCursorPosition((GetWindowWidth() / 2) - 5, (GetWindowHeight() / 2) - 4);
	std::cout << "[ ]" << "Exit";
}

void Render::DrawScreenResult(uint32_t CoordX, uint32_t CoordY,uint16_t Score) const
{
	SetCursorPosition(CoordX, CoordY);
	std::cout << "Score: "<< Score;

	SetCursorPosition(0, 0);
}

void Render::DrawObject2D(uint32_t CoordX, uint32_t CoordY, std::string StrValue) const
{
	SetCursorPosition(CoordX, CoordY);
	std::cout << StrValue;
}

void Render::DrawObject2D(uint32_t CoordX, uint32_t CoordY, char ChValue) const
{
	SetCursorPosition(CoordX, CoordY);
	std::cout << ChValue;
}

void Render::Cls() const
{
	system("cls");
}
