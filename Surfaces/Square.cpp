#include "Square.h"
#include "../header.h"
#include "../Image.h"
#include "../ImageHolder.h"
#include "../App.h"

#define EMPTY     0
#define ONE       1
#define TWO       2
#define THREE     3
#define FOUR      4
#define FIVE      5
#define SIX       6
#define SEVEN     7
#define EIGHT     8
#define UNCLICKED 9
#define CLICKED   10
#define MINE      11

#ifndef UNCLICKED_FLAG
	#define UNCLICKED_FLAG 13 // normally defined in FlagButton.cpp
#endif

//SDL_Rect Square::selections[4] = {{0, 0, SQUARE_WIDTH, SQUARE_HEIGHT}, {20, 0, SQUARE_WIDTH, SQUARE_HEIGHT}, {0, 20, SQUARE_WIDTH, SQUARE_HEIGHT}, {20, 20, SQUARE_WIDTH, SQUARE_HEIGHT}};
std::string rects[12] = {"images/Empty.bmp", "images/One.bmp", "images/Two.bmp", "images/Three.bmp", "images/Four.bmp", "images/Five.bmp", "images/Six.bmp", "images/Seven.bmp", "images/Eight.bmp", "images/Clicked.bmp", "images/Square.bmp", "images/Mine.bmp"};
std::vector<std::string> Square::selections(rects, rects + sizeof(rects) / sizeof(std::string));

Square::Square(Sint16 row, Sint16 column, Grid* owner): Image(selections, EMPTY, ((column * SQUARE_WIDTH) + owner->xStart), ((row * SQUARE_WIDTH) + owner->yStart), SQUARE_WIDTH, SQUARE_HEIGHT, SQUARE), _row(row), _column(column), _state(0), _sides(0), _owner(owner)
{
	if (column == 0)
		SetSurrounded(kTopLeft | kMiddleLeft | kBottomLeft);
	else if (column == (_owner->rowNum - 1))
		SetSurrounded(kTopRight | kMiddleRight | kBottomRight);

	if (row == 0)
		SetSurrounded(kTopLeft | kTopMiddle | kTopRight);
	else if (row == (_owner->columnNum - 1))
		SetSurrounded(kBottomLeft | kBottomMiddle | kBottomRight);
}

Square::~Square()
{

}

void Square::Draw()
{
	if (Clicked())
	{
		if (Flag())
		{
			DrawSurface(ImageHolder::GetInstance()->GetImage(UNCLICKED_FLAG), NULL, Location());
		}
		else if (Mine())
		{
			DrawSurface(ImageHolder::GetInstance()->GetImage(MINE), NULL, Location());
		}
		else
		{
			DrawSurface(ImageHolder::GetInstance()->GetImage(EMPTY), NULL, Location());
			Uint8 mineCount = _state >> 4;
			if (mineCount != 0)
				DrawSurface(ImageHolder::GetInstance()->GetImage(mineCount + EMPTY), NULL, Location());
		}
	}
	else if (Pushed())
		DrawSurface(ImageHolder::GetInstance()->GetImage(UNCLICKED), NULL, Location());
	else
		DrawSurface(ImageHolder::GetInstance()->GetImage(CLICKED), NULL, Location());
	_changed = false;
}

void Square::Render()
{

}

void Square::HandleEvent(SDL_Event* event)
{

}

void Square::SetFlag()
{
	_state = _state | 0x08;
}

bool Square::Flag()
{
	return _state & 0x08;
}

bool Square::Clicked()
{
	_changed = true;
	return _state & 0x02;
}

bool Square::Pushed()
{
	return _state & 0x01;
}

void Square::Push()
{
	if (Clicked())
		return;
	_changed = true;
	_state = _state | 0x01;
}

void Square::UnPush()
{
	if (Clicked())
		return;
	_changed = true;
	_state = _state & 0xFE;
}

void Square::SetMine()
{
	_state = _state | 0x04;
}

bool Square::Mine()
{
	return _state & 0x04;
}

void Square::Click()
{
	if (Clicked())
		return;
	_changed = true;
	_state = _state | 0x02;
	if (App::GetInstance()->Mouse()->InState(FLAG))
	{
		SetFlag();
	}
	else if (Mine())
		_owner->End();
	else
	{
		Uint8 mineCount = 0;
		for (int side = kTopLeft; side != 0; side = side << 1)
		{
			if (IsSurrounded(side))
				continue;
			if (GetSquare(side).Mine())
				mineCount++;
		}
		_state = _state | (mineCount << 4);
		if (mineCount == 0)
		{
			for (Uint8 side = kTopLeft; side != 0; side = side << 1)
			{
				if (IsSurrounded(side) == false)
					GetSquare(side).Click(); // yay, recursion!
			}
		}
	}
}

Square& Square::GetSquare(Uint8 side)
{
	Sint16 row = _row;
	Sint16 column = _column;
	switch(side)
	{
	case kTopLeft:
		row--;
		column--;
		break;
	case kTopMiddle:
		row--;
		break;
	case kTopRight:
		row--;
		column++;
		break;
	case kMiddleRight:
		column++;
		break;
	case kBottomRight:
		row++;
		column++;
		break;
	case kBottomMiddle:
		row++;
		break;
	case kBottomLeft:
		row++;
		column--;
		break;
	case kMiddleLeft:
		column--;
		break;
	default:
		break;
	}

	return _owner->GetSquare(row, column);

}

bool Square::IsSurrounded(Uint8 side)
{
	if (side == kAll)
		return (_sides & kAll) == kAll;
	else
		return _sides & side;
}

void Square::SetSurrounded(Uint8 side)
{
	_sides = _sides | side;
}
