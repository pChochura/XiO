#include "StartScreen.h"
#include "MenuScreen.h"
#include "../Layers/GameUILayer.h"
#include "../Layers/CompleteLayer.h"
#include "../Layers/BackgroundLayer.h"

StartScreen::StartScreen(GameMode gameMode, Difficulty difficulty) {
	this->gameMode = gameMode;
	this->difficulty = difficulty;
}

void StartScreen::load(Resources* resources) {
	resources->fonts.load(Fonts::ID::Montserrat, "Data/Fonts/Montserrat.ttf");

	this->layers.push_back(new BackgroundLayer(resources));

	this->gameUILayer = new GameUILayer(resources, this->gameMode, this->difficulty);
	this->completeLayer = new CompleteLayer(resources);
	this->completeLayer->setOnClickListener([&](bool exit) {
		if (exit) {
			onChangeScreenListener(new MenuScreen);
		} else {
			this->gameUILayer->resetBoard();
			this->layers.pop_back();
		}
	});
	this->gameUILayer->setOnCompleteListener([&, resources](State state) {
		this->completeLayer->setState(state);
		this->layers.push_back(this->completeLayer);
	});

	this->layers.push_back(this->gameUILayer);
}