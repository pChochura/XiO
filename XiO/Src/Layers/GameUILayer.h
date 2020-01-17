#pragma once
#include "Layer.h"
#include "../Board.h"
#include "../Utils/GameMode.h"

class GameUILayer : public Layer {
public:
	GameUILayer(Resources*, GameMode);

	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

	void setOnCompleteListener(std::function<void()>);

private:
	Board* board;
	std::function<void()> onCompleteListener;
};