#ifndef IMAGE_H_
#define IMAGE_H_

#include "Surface.h"
#include <string>
#include <vector>

struct SDL_Rect;

class Image: public Surface
{
protected:
	//static SDL_Surface* _surface;
	void SetColorKey(SDL_Surface* surface, Uint8 R, Uint8 G, Uint8 B);
public:
	Image(std::vector<std::string>& fileNames, Uint8 startKey, Sint16 x, Sint16 y, Uint16 w, Uint16 h, Uint8 name);
	Image(std::string fileName, Uint8 key, Sint16 x, Sint16 y, Uint16 w, Uint16 h, Uint8 name);
	static SDL_Surface* Load(std::string& file);
	virtual ~Image();
	virtual void Draw() {}
	virtual void Render() {}
	virtual void HandleEvent(SDL_Event* event) {}
};

#endif
