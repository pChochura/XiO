#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Layer.h"
#include "../Utils/State.h"
#include "../Drawables/Button.h"

////////////////////////////////////////////////////////////
// Warstwa wyœwietlana po zakoñczeniu rozgrywki. Pokazuje
// wygranego, oraz pozwala kontynuowaæ grê b¹dŸ j¹ 
// zakoñczyæ.
////////////////////////////////////////////////////////////
class CompleteLayer : public Layer {
public:
	CompleteLayer(Resources*, State = State::NONE);

	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

	////////////////////////////////////////////////////////////
	// Pozwala ustawiæ funkcjê, która zostanie wywo³ana po
	// klikniêciu jednego z przycisków z warstwy.
	// Je¿eli zostanie wciœniêty przycisk `Try again`, to 
	// zostanie zwróca wartoœæ `false`, w przeciwnym przypadku
	// `true`.
	////////////////////////////////////////////////////////////
	void setOnClickListener(std::function<void(bool)>);

	////////////////////////////////////////////////////////////
	// Pozwala ustawiæ wygranego, ¿eby wyœwietlana by³a
	// odpowiednia wiadomoœæ.
	////////////////////////////////////////////////////////////
	void setState(State);

private:
	State state;
	sf::Vector2f size;
	sf::Vector2f pos;

	std::vector<Button*> buttons;

	std::function<void(bool)> onClickListener;
};