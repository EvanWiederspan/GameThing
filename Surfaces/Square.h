#ifndef SQUARE_H_
#define SQUARE_H_

#include "../Image.h"
#include <string>
#include "../SDL/SDL_events.h"
#include <vector>

#include "Grid.h"

class Square: public Image
{
private:
	static std::vector<std::string> selections; // the filepaths to the images used by the square class
	Uint8 _row, _column;
	Uint8 _state; // 0000axyz a = flag; x = mine; y = clicked; z = pushed, upper four bits tell the number of surrounding mines
	Uint8 _sides; // used to tell whether the square is on the outer edge
	Grid* _owner; // pointer to the grid that owns the square
public:
	static const Uint8 kTopLeft = 0x01;
	static const Uint8 kTopMiddle = 0x02;
	static const Uint8 kTopRight = 0x04;
	static const Uint8 kMiddleRight = 0x08;
	static const Uint8 kBottomRight = 0x10;
	static const Uint8 kBottomMiddle = 0x20;
	static const Uint8 kBottomLeft = 0x40;
	static const Uint8 kMiddleLeft = 0x80;
	static const Uint8 kAll = 0xFF;
	static const Uint8 SQUARE_WIDTH = 30;
	static const Uint8 SQUARE_HEIGHT = 30;
	Square(Sint16 row, Sint16 column, Grid* owner);
	~Square();
	bool IsSurrounded(Uint8 side);
	void SetSurrounded(Uint8 side);
	void SetMine();
	void SetFlag();
	bool Flag();
	bool Mine();
	bool Clicked(); // true if Click() has been called
	bool Pushed();
	void Push(); // called when the mouse is held down over a square, but not let up yet
	void UnPush(); // called when the mouse Push()es the square but moves off of the square without letting go
	void Click(); // called when a square is actually clicked
	Square& GetSquare(Uint8 side); // should pass in one of the static constants above
	virtual void Draw();
	virtual void Render();
	virtual void HandleEvent(SDL_Event* event);
};

#endif
