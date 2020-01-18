#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Layer.h"
#include "../Utils/State.h"
#include "../Drawables/Button.h"

////////////////////////////////////////////////////////////
// Warstwa wy�wietlana po zako�czeniu rozgrywki. Pokazuje
// wygranego, oraz pozwala kontynuowa� gr� b�d� j� 
// zako�czy�.
////////////////////////////////////////////////////////////
class CompleteLayer : public Layer {
public:
	CompleteLayer(Resources*, State = State::NONE);

	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

	////////////////////////////////////////////////////////////
	// Pozwala ustawi� funkcj�, kt�ra zostanie wywo�ana po
	// klikni�ciu jednego z przycisk�w z warstwy.
	// Je�eli zostanie wci�ni�ty przycisk `Try again`, to 
	// zostanie zwr�ca warto�� `false`, w przeciwnym przypadku
	// `true`.
	////////////////////////////////////////////////////////////
	void setOnClickListener(std::function<void(bool)>);

	////////////////////////////////////////////////////////////
	// Pozwala ustawi� wygranego, �eby wy�wietlana by�a
	// odpowiednia wiadomo��.
	////////////////////////////////////////////////////////////
	void setState(State);

private:
	State state;
	sf::Vector2f size;
	sf::Vector2f pos;

	std::vector<Button*> buttons;

	std::function<void(bool)> onClickListener;
};