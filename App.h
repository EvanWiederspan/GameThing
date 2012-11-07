#ifndef APP_H
#define APP_H

#include "SDL/SDL.h"
#include "Screen.h"
#include "header.h"
#include "Controller.h"
#include <vector>
#include <cstdlib>

class App
{
private:
	bool running; // true when the app is running, should only be set to false when you want the app to exit
	SDL_Event* event;
	Controller mouse;
	void SetupScreens(); // sets up all screens
	void StartScreen(Uint8 startScreen); // sets the specified screen to be the starting screen
	static App* _instance;
	App();
public:
	static App* GetInstance();
	Screen* display; // pointer to the current screen thats running
	Screen* gameScreen; // all of the different screens
	std::vector<Screen*> screens; // a vector of all the screens. They should be added in numerical order of their titles in header.h
	static const int SCREEN_HEIGHT = 600;
	static const int SCREEN_WIDTH = 600;
	SDL_Surface* screen; // the surface shown on screen
	~App();
	Controller* Mouse();
	int Execute();
	bool Init();
	void UpdateScreen();
	void ChangeScreen(Uint8 newScreen, bool pause);
};


#endif
