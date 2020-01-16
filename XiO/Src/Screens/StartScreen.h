#pragma once
#include "Screen.h"
#include "../Resources/Resources.h"

class StartScreen : public Screen {
public:
	virtual void load(Resources*) override;
};