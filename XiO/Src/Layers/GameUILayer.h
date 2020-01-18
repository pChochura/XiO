#pragma once
#include "Layer.h"
#include "../Board.h"
#include "../Utils/GameMode.h"

////////////////////////////////////////////////////////////
// Warstwa wy�wietlaj�ca plansz�.
////////////////////////////////////////////////////////////
class GameUILayer : public Layer {
public:
	GameUILayer(Resources*, GameMode, Difficulty);

	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

	////////////////////////////////////////////////////////////
	// Pozwala ustawi� funkcj�, kt�ra zostanie wywo�ana, gdy
	// gra zostanie zako�czona. Parametr przyjmuje warto��
	// w zale�no�ci od wyniku.
	////////////////////////////////////////////////////////////
	void setOnCompleteListener(std::function<void(State)>);

	////////////////////////////////////////////////////////////
	// Pozwala ustawi� plansz� jako pust�.
	////////////////////////////////////////////////////////////
	void resetBoard();

private:
	Board* board;
	std::function<void(State)> onCompleteListener;
};