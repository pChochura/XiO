#pragma once
#include <functional>
#include "Layer.h"
#include "../Utils/GameMode.h"
#include "../Drawables/Button.h"

////////////////////////////////////////////////////////////
// Warstwa, na kt�rej wy�wietlane s� poziomy trudno�ci
// po wybraniu trybu `Singleplayer`.
////////////////////////////////////////////////////////////
class DifficultyLayer : public Layer {
public:
	DifficultyLayer(Resources*);

	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

	////////////////////////////////////////////////////////////
	// Pozwala ustawi� funckj�, kt�ra zostanie wywo�ana
	// po wybraniu poziomu trudno�ci. Poziom ten zostanie
	// przekazany jako parametr.
	////////////////////////////////////////////////////////////
	void setOnClickListener(std::function<void(Difficulty)>);

private:
	sf::Vector2f size;
	sf::Vector2f pos;
	std::vector<Button*> buttons;

	std::function<void(Difficulty)> onClickListener;
};