#include "App.h"

int main(int argc, char* args[])
{
	App* app = App::GetInstance();
	return app->Execute();
}
