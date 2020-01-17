#include <time.h>
#include <vector>
#include "Board.h"
#include "Utils/State.h"
#include "Utils/GameMode.h"

Board::Board(int size, GameMode gameMode, Difficulty difficulty) : size(size), gameMode(gameMode), difficulty(difficulty), currentPlayer(State::X) {
	this->map = new State[size * size];
	for (int i = 0; i < size * size; i++) {
		this->map[i] = State::NONE;
	}
	srand(time(NULL));
}

Board::~Board() {
	delete[] this->map;
}

State Board::getAt(int x, int y) {
	return this->map[x * this->size + y];
}

void Board::setAt(int x, int y, State value) {
	this->map[x * this->size + y] = value;
	this->currentPlayer = !this->currentPlayer;
	checkComplete();
}

int Board::getSize() {
	return this->size;
}

GameMode Board::getGameMode() {
	return this->gameMode;
}

State Board::getCurrentPlayer() {
	return this->currentPlayer;
}

void Board::makeMove() {
	switch (this->difficulty) {
	case Difficulty::EASY:
		makeEasyMove();
		break;
	case Difficulty::MEDIUM:
		makeMediumMove();
		break;
	case Difficulty::HARD:
		makeHardMove();
		break;
	}
	checkComplete();
}

void Board::setOnCompleteListener(std::function<void(State)> onCompleteListener) {
	this->onCompleteListener = onCompleteListener;
}

void Board::checkComplete() {
	State state = getAt(0, 0);
	for (int j = 1; j < this->size; j++) {
		state = state & getAt(j, j);
	}
	if (state != State::NONE) {
		this->onCompleteListener(state);
	}
	bool hasEmptySlot = false;
	for (int i = 0; i < this->size; i++) {
		State stateV = getAt(0, i);
		State stateH = getAt(i, 0);
		for (int j = 1; j < this->size; j++) {
			stateV = stateV & getAt(j, i);
			stateH = stateH & getAt(i, j);
		}
		if (stateV != State::NONE || stateH != State::NONE) {
			this->onCompleteListener(stateV | stateH);
		}
		for (int j = 0; j < this->size; j++) {
			if (getAt(i, j) == State::NONE) {
				hasEmptySlot = true;
				break;
			}
		}
	}
	if (!hasEmptySlot) {
		this->onCompleteListener(State::NONE);
	}
}

void Board::makeEasyMove() {
	std::vector<int> emptySlots;
	for (int i = 0; i < this->size * this->size; i++) {
		if (this->map[i] == State::NONE) {
			emptySlots.push_back(i);
		}
	}
	int index = rand() % emptySlots.size();
	this->map[emptySlots[index]] = getCurrentPlayer();
	this->currentPlayer = !this->currentPlayer;
}

void Board::makeMediumMove() {
	int index = 0;
	if (countDiagonally(!getCurrentPlayer(), index) == this->size - 1) {
		this->map[index] = getCurrentPlayer();
		this->currentPlayer = !this->currentPlayer;
		return;
	}
	for (int i = 0; i < this->size; i++) {
		if (countVertically(i, !getCurrentPlayer(), index) == this->size - 1 ||
			countHorizontally(i, !getCurrentPlayer(), index) == this->size - 1) {
			this->map[index] = getCurrentPlayer();
			this->currentPlayer = !this->currentPlayer;
			return;
		}
	}
	makeEasyMove();
}

void Board::makeHardMove() {}

int Board::countHorizontally(int y, State state, int& index) {
	int count = 0;
	for (int i = 0; i < this->size; i++) {
		if (getAt(i, y) == state) {
			count++;
		} else if (getAt(i, y) == State::NONE) {
			index = i * this->size + y;
		} else {
			count = this->size;
			return count;
		}
	}
	return count;
}

int Board::countVertically(int x, State state, int& index) {
	int count = 0;
	for (int i = 0; i < this->size; i++) {
		if (getAt(x, i) == state) {
			count++;
		} else if (getAt(x, i) == State::NONE) {
			index = x * this->size + i;
		} else {
			count = this->size;
			return count;
		}
	}
	return count;
}

int Board::countDiagonally(State state, int& index) {
	int count = 0;
	for (int i = 0; i < this->size; i++) {
		if (getAt(i, i) == state) {
			count++;
		} else if (getAt(i, i) == State::NONE) {
			index = i * this->size + i;
		} else {
			count = this->size;
			return count;
		}
	}
	if (count == this->size - 1) {
		return count;
	}

	count = 0;
	for (int i = 0; i < this->size; i++) {
		if (getAt(i, this->size - i + 1) == state) {
			count++;
		} else if (getAt(i, this->size - i + 1) == State::NONE) {
			index = (i + 1) * this->size - i + 1;
		} else {
			count = this->size;
			return count;
		}
	}
	return count;
}