#pragma once
#include <SFML/Graphics.hpp>
#include "Layer.h"

////////////////////////////////////////////////////////////
// Warstwa odpowiedzialna za t³o.
////////////////////////////////////////////////////////////
class BackgroundLayer : public Layer {
public:
	BackgroundLayer(Resources*);

	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

private:
	sf::Vector2f size;
};