#include "ImageHolder.h"

ImageHolder* ImageHolder::_instance = NULL;

ImageHolder::ImageHolder(): surfaces()
{

}

ImageHolder::~ImageHolder()
{
	for (Uint16 i = 0; i < NUM_IMAGES; i++)
	{
		SDL_FreeSurface(surfaces[i]);
	}
}

ImageHolder* ImageHolder::GetInstance()
{
	if (_instance == NULL)
		_instance = new ImageHolder();
	return _instance;
}

void ImageHolder::Register(SDL_Surface* surface, Uint8 key)
{
	if (key > NUM_IMAGES)
		return;

	if (surfaces[key] != NULL) // if a surface already exists at this location, delete the old one and replace it with the new one
		SDL_FreeSurface(surfaces[key]);

	surfaces[key] = surface;
}

SDL_Surface* ImageHolder::GetImage(Uint8 key)
{
	if (key < NUM_IMAGES)
		return surfaces[key];
	else
		return NULL;
}

bool ImageHolder::Registered(Uint8 key)
{
	return (surfaces[key] != NULL);
}
