#include "StartScreen.h"
#include "../Layers/BackgroundLayer.h"
#include "../Layers/GameUILayer.h"

StartScreen::StartScreen(GameMode gameMode) {
	this->gameMode = gameMode;
}

void StartScreen::load(Resources* resources) {
	resources->fonts.load(Fonts::Montserrat, "Data/Fonts/Montserrat.ttf");

	this->layers.push_back(new BackgroundLayer(resources));
	this->layers.push_back(new GameUILayer(resources, this->gameMode));
}