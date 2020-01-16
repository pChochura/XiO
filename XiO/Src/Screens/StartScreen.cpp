#include "StartScreen.h"
#include "../Layers/BackgroundLayer.h"
#include "../Layers/GameUILayer.h"

void StartScreen::load(Resources* resources) {
	resources->fonts.load(Fonts::Montserrat, "Data/Fonts/Montserrat.ttf");

	this->layers.push_back(new BackgroundLayer(resources));
	this->layers.push_back(new GameUILayer(resources));
}