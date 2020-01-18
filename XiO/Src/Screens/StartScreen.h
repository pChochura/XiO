#pragma once
#include "Screen.h"
#include "../Utils/GameMode.h"
#include "../Layers/GameUILayer.h"
#include "../Resources/Resources.h"
#include "../Layers/CompleteLayer.h"

////////////////////////////////////////////////////////////
// Klasa odpowiedzialna za wy�wietlanie obrazu po 
// rozpocz�ciu rozgrywki.
////////////////////////////////////////////////////////////
class StartScreen : public Screen {
public:
	StartScreen(GameMode, Difficulty);
	virtual void load(Resources*) override;

private:
	GameMode gameMode;
	Difficulty difficulty;
	GameUILayer* gameUILayer;
	CompleteLayer* completeLayer;
};