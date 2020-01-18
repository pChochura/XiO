#include "MenuScreen.h"
#include "../Screens/StartScreen.h"
#include "../Layers/BackgroundLayer.h"
#include "../Layers/MenuUILayer.h"
#include "../Layers/DifficultyLayer.h"

void MenuScreen::load(Resources* resources) {
	resources->fonts.load(Fonts::ID::Montserrat, "Data/Fonts/Montserrat.ttf");

	MenuUILayer* menuUILayer = new MenuUILayer(resources);
	menuUILayer->setOnClickListener([&, resources](GameMode gameMode) {
		if (gameMode == GameMode::SINGLE_PLAYER) {
			DifficultyLayer* difficultyLayer = new DifficultyLayer(resources);
			difficultyLayer->setOnClickListener([&, gameMode](Difficulty difficulty) {
				this->onChangeScreenListener(new StartScreen(gameMode, difficulty));
			});
			this->layers.push_back(difficultyLayer);
		} else {
			this->onChangeScreenListener(new StartScreen(gameMode, Difficulty::EASY));
		}
	});

	this->layers.push_back(new BackgroundLayer(resources));
	this->layers.push_back(menuUILayer);
}