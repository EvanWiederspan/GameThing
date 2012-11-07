#include "App.h"
#include "SDL/SDL_main.h"
#include "Screens.h"
#include "header.h"
#include <vector>
#include <ctime>

App* App::_instance = NULL;

App::App()
{
	running = true;
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
	srand(time(0));
}

App::~App()
{
	delete(event);
	delete(gameScreen);
	delete(screen);
	screens.clear();
	SDL_Quit();
}

void App::SetupScreens()
{
	gameScreen = new GameScreen("images/gameBackground.bmp"); // takes in the file path to the background image

	screens.push_back(gameScreen);
	StartScreen(GAME);
}

void App::StartScreen(Uint8 startScreen)
{
	screens[startScreen]->Load();
	screens[startScreen]->SetRunning(true);
	display = screens[startScreen];
}

int App::Execute()
{
	if (Init() == false)
		return -1;
	event = new SDL_Event();
	mouse = Controller();
	//display->Clear();
	//display->DrawAll();
	while(running)
	{
		display->Clear();
		while (SDL_PollEvent(event))
		{
			if (event->type == SDL_QUIT)
				running = false;
			mouse.Update(event);
			display->Events(event);
			display->ButtonCheck(event);
		}
		display->Render();
		display->Draw();
		UpdateScreen();
		SDL_Delay(5);
	}
	return 1;
}

bool App::Init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;
	SDL_WM_SetCaption("MineSweeper", NULL);
	SetupScreens();
	return true;
}

void App::UpdateScreen()
{
	SDL_UpdateRect(screen,0,0,0,0);
}

void App::ChangeScreen(Uint8 newScreen, bool pause)
{
	Screen* _newScreen = screens[newScreen];
	if (!pause)
		display->Destroy();
	if (!(_newScreen->IsRunning()))
	{
		_newScreen->Load();
		_newScreen->SetRunning(true);
	}
	display = _newScreen;
	display->Clear();
	//display->DrawAll();
}

App* App::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new App();
	}
	return _instance;
}

Controller* App::Mouse()
{
	return &mouse;
}
