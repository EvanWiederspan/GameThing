#ifndef GAMESCREEN_H_
#define GAMESCREEN_H_

#include "../Screen.h"
#include <string>
#include "../Surfaces.h"
#include "../header.h"

class GameScreen: public Screen
{
public:
	GameScreen(std::string bgnd): Screen(bgnd) {}
	~GameScreen() {}
	void Load();
};

#endif
