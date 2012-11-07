#include "Surface.h"
#include "header.h"
#include "Screen.h"
#include "App.h"
#include "ImageHolder.h"

Surface::Surface(Uint8 name, Sint16 x, Sint16 y, Uint16 w, Uint16 h): _area({x,y,w,h}), _lastX(x), _lastY(y), _changed(true), _name(name)
{
	/*
	_area.x = x;
	_area.y = y;
	_area.w = w;
	_area.h = h;
	*/
	//_area = {x,y,w,h};
}

Surface::~Surface()
{

}

SDL_Rect* Surface::Location()
{
	return &_area;
}

void Surface::DrawSurface(SDL_Surface* surface, SDL_Rect* srcrect, SDL_Rect* destrect)
{
	App::GetInstance()->display->PlaceSurface(surface, srcrect, destrect);
}

void Surface::DrawSurface(Uint8 key, SDL_Rect* srcrect, SDL_Rect* destrect)
{
	App::GetInstance()->display->PlaceSurface(ImageHolder::GetInstance()->GetImage(key), srcrect, destrect);
}

void Surface::DrawAtCursor(SDL_Surface* surface, SDL_Rect* srcrect)
{
	DrawSurface(surface, srcrect, App::GetInstance()->Mouse()->CursorLocation());
}

void Surface::DrawAtCursor(Uint8 key, SDL_Rect* srcrect)
{
	App::GetInstance()->display->PlaceSurface(ImageHolder::GetInstance()->GetImage(key), srcrect, App::GetInstance()->Mouse()->CursorLocation());
}

void Surface::Register(std::string surface, Uint8 key)
{
	ImageHolder::GetInstance()->Register(Image::Load(surface), key);
}

void Surface::ChangeX(Sint16 Xvalue)
{
	_area.x = Xvalue;
	_changed = true;
}

void Surface::ChangeY(Sint16 Yvalue)
{
	_area.y = Yvalue;
	_changed = true;
}

void Surface::SetChanged(bool changed)
{
	_changed = changed;
}

bool Surface::HasChanged() { return _changed; }

Sint16 Surface::GetX() { return _area.x; }

Sint16 Surface::GetLastX() { return _lastX; }

Sint16 Surface::GetLastY() { return _lastY; }

Sint16 Surface::GetY() { return _area.y; }

Uint16 Surface::GetW() { return _area.w; }

Uint16 Surface::GetH() { return _area.h; }

Uint8 Surface::GetName() { return _name; }
