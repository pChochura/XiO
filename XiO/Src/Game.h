#pragma once
#include <string>
#include "Resources/Resources.h"
#include "Screens/Screen.h"

class Game {
public:
	Game(std::string title, int width = 1080, int height = 720);

	void show();

	void changeScreen(Screen*);

private:
	Resources* resources;
	Screen* screen;
};