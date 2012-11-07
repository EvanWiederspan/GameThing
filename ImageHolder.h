#ifndef IMAGEHOLDER_H_
#define IMAGEHOLDER_H_

#include "SDL/SDL.h"
#include "header.h"

class ImageHolder
{
private:
	static ImageHolder* _instance;
	SDL_Surface* surfaces[NUM_IMAGES];
	ImageHolder();
public:
	~ImageHolder();
	static ImageHolder* GetInstance();
	void Register(SDL_Surface* surface, Uint8 key);
	bool Registered(Uint8 key); // returns truw if there is already an image at that place
	SDL_Surface* GetImage(Uint8 key);
};

#endif
