#include "StaticSprite.h"
#include "../ImageHolder.h"

StaticSprite::StaticSprite(std::string fileName, Uint8 key, Sint16 x, Sint16 y, Uint16 w, Uint16 h, Uint8 name):
Image(fileName, key, x, y, w, h, name), _key(key)
{

}

StaticSprite::~StaticSprite()
{

}

void StaticSprite::Draw()
{
	DrawSurface(ImageHolder::GetInstance()->GetImage(_key), NULL, Location());
}
