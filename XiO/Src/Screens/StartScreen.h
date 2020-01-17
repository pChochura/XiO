#pragma once
#include "Screen.h"
#include "../Utils/GameMode.h"
#include "../Resources/Resources.h"

class StartScreen : public Screen {
public:
	StartScreen(GameMode);
	virtual void load(Resources*) override;

private:
	GameMode gameMode;
};