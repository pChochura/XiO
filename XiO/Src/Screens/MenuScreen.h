#pragma once
#include "Screen.h"
#include "../Resources/Resources.h"

////////////////////////////////////////////////////////////
// Klasa odpowiedzialna za wy�wietlanie ekranu menu.
////////////////////////////////////////////////////////////
class MenuScreen : public Screen {
public:
	virtual void load(Resources*) override;
};