#pragma once
#include "Layer.h"
#include "../Board.h"
#include "../Utils/GameMode.h"

////////////////////////////////////////////////////////////
// Warstwa wyœwietlaj¹ca planszê.
////////////////////////////////////////////////////////////
class GameUILayer : public Layer {
public:
	GameUILayer(Resources*, GameMode, Difficulty);

	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

	////////////////////////////////////////////////////////////
	// Pozwala ustawiæ funkcjê, która zostanie wywo³ana, gdy
	// gra zostanie zakoñczona. Parametr przyjmuje wartoœæ
	// w zale¿noœci od wyniku.
	////////////////////////////////////////////////////////////
	void setOnCompleteListener(std::function<void(State)>);

	////////////////////////////////////////////////////////////
	// Pozwala ustawiæ planszê jako pust¹.
	////////////////////////////////////////////////////////////
	void resetBoard();

private:
	Board* board;
	std::function<void(State)> onCompleteListener;
};