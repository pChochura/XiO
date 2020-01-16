#pragma once
#include "Layer.h"
#include "../Utils/GameMode.h"
#include "../Drawables/Button.h"

class MenuUILayer : public Layer {
public:
	MenuUILayer(Resources*);

	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

	void setOnClickListener(std::function<void(GameMode)>);

private:
	std::vector<Button*> buttons;
	std::function<void(GameMode)> onClickListener;
};