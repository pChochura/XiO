#pragma once
#include "Layer.h"
#include "../Board.h"

class GameUILayer : public Layer {
public:
	GameUILayer(Resources*);

	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

private:
	Board* board;
};