#ifndef GRID_H_
#define GRID_H_

#include "../Geometry.h"
#include "../header.h"
#include <vector>
//#include "Square.h"
class Square;

class Grid: public Geometry
{
	Uint8 _selectedRow;
	Uint8 _selectedColumn;
	bool _done;
public:
	const Sint16 xStart;
	const Sint16 yStart;
	const Uint8 rowNum;
	const Uint8 columnNum;
	std::vector<Square> squares;
	Grid(Sint16 x, Sint16 y, Uint8 rows, Uint8 columns, Uint16 numMines);
	~Grid();
	void Draw();
	void Render() {}
	void HandleEvent(SDL_Event* event);
	Square& SquareAtCursor(Uint16 mouseX, Uint16 mouseY);
	Square& GetSquare(Uint8 row, Uint8 column);
	void End(); //called when a mine is clicked
};

#endif
