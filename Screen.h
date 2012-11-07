#ifndef SCREEN_H_
#define SCREEN_H_

#include "Surface.h"
#include "Surfaces.h"
#include "ButtonManager.h"
#include <vector>
#include <string>

class Screen
{
protected:
	SDL_Surface* background;
	ButtonManager buttonMan;
	bool _running;
public:
	std::vector<Surface*> surfaces; // a vector containing all of the surfaces in this screen
	Screen(std::string bgnd); // takes in the path to the background image
	virtual void Load() = 0;
	virtual void Destroy();
	virtual ~Screen();
	void DrawPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B); // draws a pixel on the screen at the given location
	void Add(Surface* item); // calls push_back to add a Surface* to the surfaces vector
	void DrawAll(); // draws all surfaces
	void Clear(); // blit the original onto the screen
	bool IsRunning();
	void SetRunning(bool running);
	virtual void Draw(); // run through every surfaces in surfaces and call its draw() function
	virtual void Render();
	virtual void Events(SDL_Event* event);
	SDL_Surface* Background();
	// drawing shape functions
	void DrawRect(SDL_Rect* rect, Uint32 color);
	void DrawRect(Sint16 x, Sint16 y, Uint16 w, Uint16 h, Uint8 R, Uint8 G, Uint8 B);
	void DrawRect(Sint16 x, Sint16 y, Uint16 w, Uint16 h, Uint32 color);
	void PlaceSurface(SDL_Surface* surface, SDL_Rect* srcrect, SDL_Rect* destrect);
	void ButtonCheck(SDL_Event* event);
};

#endif
