#include "MenuScreen.h"
#include "../Screens/StartScreen.h"
#include "../Layers/BackgroundLayer.h"
#include "../Layers/MenuUILayer.h"

void MenuScreen::load(Resources* resources) {
	resources->fonts.load(Fonts::Montserrat, "Data/Fonts/Montserrat.ttf");

	MenuUILayer* menuUILayer = new MenuUILayer(resources);
	menuUILayer->setOnClickListener([&, resources](GameMode gameMode) {
		this->onChangeScreenListener(new StartScreen);
	});

	this->layers.push_back(new BackgroundLayer(resources));
	this->layers.push_back(menuUILayer);
}