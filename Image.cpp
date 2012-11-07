#include "Image.h"
#include "ImageHolder.h"

Image::Image(std::vector<std::string>& fileNames, Uint8 startKey, Sint16 x, Sint16 y, Uint16 w, Uint16 h, Uint8 name): Surface(name, x, y, w, h)
{
	if (ImageHolder::GetInstance()->Registered(startKey))
		return;

	for (Uint8 i = 0; i < (Uint8)fileNames.size(); i++)
	{
		//SDL_Surface* clipped = Load(fileNames[i]);
		Register(fileNames[i], (startKey + i));
	}
}

Image::Image(std::string fileName, Uint8 key, Sint16 x, Sint16 y, Uint16 w, Uint16 h, Uint8 name): Surface(name, x, y, w, h)
{
	if (ImageHolder::GetInstance()->Registered(key))
		return;

	//SDL_Surface* image = Load(fileName);
	Register(fileName, key);
}

Image::~Image()
{

}

SDL_Surface* Image::Load(std::string& file)
{
	SDL_Surface* load = SDL_LoadBMP(file.c_str());
	if (load) // if it was successful
	{
		SDL_Surface* opt = SDL_DisplayFormat(load);
		SDL_FreeSurface(load);
		return opt;
	}
	else
	{
		std::string file = "images/fail.bmp";
		SDL_Surface* fail = SDL_LoadBMP(file.c_str());
		SDL_Surface* failOpt = SDL_DisplayFormat(load);
		SDL_FreeSurface(fail);
		return failOpt;
	}
}

void Image::SetColorKey(SDL_Surface* surface, Uint8 R, Uint8 G, Uint8 B)
{
	Uint32 key = SDL_MapRGB(surface->format, R, G, B);
	SDL_SetColorKey(surface, SDL_SRCCOLORKEY, key);
}
