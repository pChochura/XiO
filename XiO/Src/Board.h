#pragma once
#include <functional>
#include "Utils/State.h"
#include "Utils/GameMode.h"

class Board {
public:
	Board(int, GameMode, Difficulty = Difficulty::MEDIUM);
	~Board();

	State getAt(int, int);
	void setAt(int, int, State);

	int getSize();
	GameMode getGameMode();
	State getCurrentPlayer();

	void makeMove();

	void setOnCompleteListener(std::function<void(State)>);

private:
	void checkComplete();

	void makeEasyMove();
	void makeMediumMove();
	void makeHardMove();

	int countHorizontally(int, State, int&);
	int countVertically(int, State, int&);
	int countDiagonally(State, int&);

private:
	int size;
	GameMode gameMode;
	Difficulty difficulty;
	State* map;
	State currentPlayer;

	std::function<void(State)> onCompleteListener;
};