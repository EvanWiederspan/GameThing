#ifndef STATICSPRITE_H_
#define STATICSPRITE_H_

#include "../Image.h"
#include <string>

class StaticSprite: public Image
{
private:
	Uint8 _key;
public:
	StaticSprite(std::string fileName, Uint8 key, Sint16 x, Sint16 y, Uint16 w, Uint16 h, Uint8 name);
	virtual ~StaticSprite();
	void Draw();
};

#endif
