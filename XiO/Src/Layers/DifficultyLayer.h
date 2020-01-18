#pragma once
#include <functional>
#include "Layer.h"
#include "../Utils/GameMode.h"
#include "../Drawables/Button.h"

////////////////////////////////////////////////////////////
// Warstwa, na której wyœwietlane s¹ poziomy trudnoœci
// po wybraniu trybu `Singleplayer`.
////////////////////////////////////////////////////////////
class DifficultyLayer : public Layer {
public:
	DifficultyLayer(Resources*);

	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

	////////////////////////////////////////////////////////////
	// Pozwala ustawiæ funckjê, która zostanie wywo³ana
	// po wybraniu poziomu trudnoœci. Poziom ten zostanie
	// przekazany jako parametr.
	////////////////////////////////////////////////////////////
	void setOnClickListener(std::function<void(Difficulty)>);

private:
	sf::Vector2f size;
	sf::Vector2f pos;
	std::vector<Button*> buttons;

	std::function<void(Difficulty)> onClickListener;
};