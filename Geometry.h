#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "Surface.h"

class Geometry: public Surface
{
public:
	Geometry(Sint16 x, Sint16 y, Uint16 w, Uint16 h, Uint8 name);
	virtual ~Geometry() {}
	virtual void Render() {}
	virtual void Draw() {}
	virtual void HandleEvent(SDL_Event* event) {}
};

#endif
