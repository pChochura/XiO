#pragma once
#include <SFML/Graphics.hpp>
#include "../Resources/Resources.h"

class Drawable {
public:
	virtual void draw(Resources*) const = 0;
	virtual bool onEvent(Resources*, sf::Event*) const = 0;
};