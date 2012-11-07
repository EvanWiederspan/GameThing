#include "Screen.h"
#include "App.h"

Screen::Screen(std::string bgnd): buttonMan()
{
	background = SDL_LoadBMP(bgnd.c_str());
	_running = false;
}

Screen::~Screen()
{
	if (background) SDL_FreeSurface(background);
	Destroy();
}

void Screen::DrawPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
	Uint32 pixel = SDL_MapRGB(background->format, R, G, B);
	 int bpp = background->format->BytesPerPixel;
	 // Here p is the address to the pixel we want to set
	 Uint8 *p = (Uint8 *)background->pixels + y * background->pitch + x * bpp;

	 switch(bpp)
	 {
	 case 1:
		   *p = pixel;
		   break;
	 case 2:
		   *(Uint16 *)p = pixel;
		   break;
	 case 3:
		   if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		   {
				p[0] = (pixel >> 16) & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = pixel & 0xff;
		   }
		   else
		   {
				p[0] = pixel & 0xff;
				p[1] = (pixel >> 8) & 0xff;
				p[2] = (pixel >> 16) & 0xff;
		   }
	   break;
     case 4:
		   *(Uint32 *)p = pixel;
		   break;
	 }
}

void Screen::Add(Surface* item)
{
	surfaces.push_back(item);
	if ((item->GetName() & 0x80))
		buttonMan.Add(dynamic_cast<Button*>(item));
}

void Screen::Destroy()
{
	if (IsRunning() and ((bool)surfaces.empty() == false))
	{
		for (Uint32 i = 0; i < (Uint32)surfaces.size(); i++)
		{
			delete(surfaces[i]);
		}
		surfaces.clear();
		buttonMan.Clear();
	}
	SetRunning(false);
}

void Screen::Clear()
{
	SDL_BlitSurface(background, NULL, App::GetInstance()->screen, NULL);
}

bool Screen::IsRunning()
{
	return _running;
}

void Screen::SetRunning(bool running)
{
	_running = running;
}

void Screen::Draw()
{
	for (Uint16 i = 0; i < (Uint16) surfaces.size(); i++)
	{
		/*
		Surface* currSurface = surfaces[i];
		if (currSurface->HasChanged()) // if the surface has changed
		{
			SDL_Rect clearArea = {currSurface->GetLastX(), currSurface->GetLastY(), currSurface->GetW(), currSurface->GetH()}; // the area that needs to be drawn over to cover the old object
			SDL_BlitSurface(background, &clearArea, App::GetInstance()->screen, &clearArea); // cover the old object
			currSurface->Draw(); // and draw the new one
			//currSurface->SetChanged(false); // so the object wont keep drawing itself (this should be set back to true somewhere in Render() or HandleEvent())
		}
		*/
		surfaces[i]->Draw();
	}
}

void Screen::DrawAll()
{
	for (Uint16 i = 0; i < (Uint16) surfaces.size(); i++)
	{
		surfaces[i]->Draw();
	}
}
void Screen::Render()
{
	for (Uint16 i = 0; i < (Uint16) surfaces.size(); i++)
	{
		Surface* currSurface = surfaces[i];
		currSurface->Render();
	}
}

void Screen::Events(SDL_Event* event)
{
	for (Uint16 i = 0; i < (Uint16) surfaces.size(); i++)
	{
		surfaces[i]->HandleEvent(event);
	}
}

SDL_Surface* Screen::Background()
{
	return background;
}

void Screen::DrawRect(SDL_Rect* rect, Uint32 color)
{
	SDL_FillRect(App::GetInstance()->screen, rect, color);
}

void Screen::DrawRect(Sint16 x, Sint16 y, Uint16 w, Uint16 h, Uint8 R, Uint8 G, Uint8 B)
{
	Uint32 color = SDL_MapRGB(background->format, R, G, B);
	SDL_Rect rect = {x,y,w,h};
	SDL_FillRect(App::GetInstance()->screen, &rect, color);

}

void Screen::DrawRect(Sint16 x, Sint16 y, Uint16 w, Uint16 h, Uint32 color)
{
	SDL_Rect rect = {x,y,w,h};
	SDL_FillRect(App::GetInstance()->screen, &rect, color);
}

void Screen::PlaceSurface(SDL_Surface* surface, SDL_Rect* srcrect, SDL_Rect* destrect)
{
	SDL_BlitSurface(surface, srcrect, App::GetInstance()->screen, destrect);
}

void Screen::ButtonCheck(SDL_Event* event)
{
	buttonMan.CheckButtons(event);
}
