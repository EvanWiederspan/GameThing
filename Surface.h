#ifndef SURFACE_H_
#define SURFACE_H_

#include "SDL/SDL.h"
#include <stdlib.h>
#include <string>

class Screen;

class Surface
{
protected:
	SDL_Rect _area;
	Sint16 _lastX, _lastY;
	bool _changed; // will be set to true whenever x, y or animation is changed
	Uint8 _name; // helps identify what the object is
public:
	Surface(Uint8 name, Sint16 x, Sint16 y, Uint16 w, Uint16 h);
	virtual ~Surface();
	void ChangeX(Sint16 Xvalue);
	void ChangeY(Sint16 Yvalue);
	bool HasChanged();
	void SetChanged(bool changed);
	void DrawSurface(SDL_Surface* surface, SDL_Rect* srcrect, SDL_Rect* destrect);
	void DrawSurface(Uint8 key, SDL_Rect* srcrect, SDL_Rect* destrect);
	void DrawAtCursor(SDL_Surface* surface, SDL_Rect* srcrect);
	void DrawAtCursor(Uint8 key, SDL_Rect* srcrect);
	void Register(std::string surface, Uint8 key);
	Sint16 GetX();
	Sint16 GetLastX();
	Sint16 GetY();
	Sint16 GetLastY();
	Uint16 GetW();
	Uint16 GetH();
	SDL_Rect* Location(); // returns a SDL_Rect containing the values for _x, _y, _w and _h
	Uint8 GetName();
	virtual void Render() = 0; // abstract function that will perform the logic for the object and choose which surface to choose (if there are multiple)
	virtual void Draw() = 0; // draws surface to the screen at _x and _y with the width of _w and the height of _h
	virtual void HandleEvent(SDL_Event* event) = 0; // handles events (i.e. keypresses and mouse movements)
};

#endif
