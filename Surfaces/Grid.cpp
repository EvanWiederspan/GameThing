#include "Grid.h"
#include "Square.h"
#include "../App.h"

Grid::Grid(Sint16 x, Sint16 y, Uint8 rows, Uint8 columns, Uint16 numMines): Geometry(GRID, -1, -1, 0, 0), _selectedRow(rows), _selectedColumn(columns), _done(false), xStart(x), yStart(y), rowNum(rows), columnNum(columns)
{
	for (Uint8 row = 0; row < rowNum; row++)
	{
		for (Uint8 column = 0; column < columnNum; column++)
		{
			squares.push_back(Square(row, column, this));
		}
	}
	while (numMines != 0)
	{
		Square& currSquare = GetSquare((rand() % rowNum), (rand() % columnNum));
		if (currSquare.Mine() == false)
		{
			currSquare.SetMine();
			numMines--;
		}
	}
}

Grid::~Grid()
{
	squares.clear();
}

void Grid::Draw()
{
	for (Uint32 square = 0; square < (columnNum * rowNum); square++)
	{
		squares[square].Draw();
	}
}

void Grid::HandleEvent(SDL_Event* event)
{
	if (_done)
		return;

	if (event->type == SDL_MOUSEMOTION)
	{
		if (_selectedRow >= rowNum and _selectedColumn >= columnNum)
			return;

		GetSquare(_selectedRow, _selectedColumn).UnPush();

		Uint16 mouseX = event->button.x;
		Uint16 mouseY = event->button.y;

		if (mouseX < xStart)
			return;
		if (mouseX > (xStart + (columnNum * Square::SQUARE_WIDTH))) // if they didnt click within the grid, dont bother checking
			return;
		if (mouseY < yStart)
			return;
		if (mouseY > (yStart + (rowNum * Square::SQUARE_HEIGHT)))
			return;

		_selectedColumn = (mouseX - xStart) / Square::SQUARE_WIDTH;
		_selectedRow = (mouseY - yStart) / Square::SQUARE_HEIGHT;

		GetSquare(_selectedRow, _selectedColumn).Push();
	}
	if (App::GetInstance()->Mouse()->Clicked())
	{
		Uint16 mouseX = event->button.x;
		Uint16 mouseY = event->button.y;

		if ((mouseX < xStart) or (mouseX > (xStart + (columnNum * Square::SQUARE_WIDTH))) or (mouseY < yStart) or (mouseY > (yStart + (rowNum * Square::SQUARE_HEIGHT))))
		{
			_selectedRow = rowNum;
			_selectedColumn = columnNum;
			return;
		}

		_selectedColumn = (mouseX - xStart) / Square::SQUARE_WIDTH;
		_selectedRow = (mouseY - yStart) / Square::SQUARE_HEIGHT;

		GetSquare(_selectedRow, _selectedColumn).Push();
	}
	if (App::GetInstance()->Mouse()->Clicked() == false)
	{
		if ((_selectedRow == rowNum) or (_selectedColumn == columnNum))
			return;
		GetSquare(_selectedRow, _selectedColumn).Click();
		_selectedRow = rowNum;
		_selectedColumn = columnNum;
	}

}

Square& Grid::GetSquare(Uint8 row, Uint8 column)
{
	return squares[(row * columnNum) + column];
}

Square& Grid::SquareAtCursor(Uint16 mouseX, Uint16 mouseY)
{
	return GetSquare((mouseX + xStart) / Square::SQUARE_WIDTH, (mouseY + yStart) / Square::SQUARE_HEIGHT);
}

void Grid::End()
{
	if (_done)
		return;

	for (Uint32 square = 0; square < (rowNum * columnNum); square++)
	{
		if(squares[square].Mine())
			squares[square].Click();
	}
	_done = true;

}
