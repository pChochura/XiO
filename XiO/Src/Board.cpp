#include <time.h>
#include <vector>
#include "Board.h"
#include "Utils/State.h"
#include "Utils/GameMode.h"
#include "Utils/Utils.h"

Board::Board(int size, GameMode gameMode, Difficulty difficulty) :
	size(size), gameMode(gameMode), difficulty(difficulty), currentPlayer(State::X), complete(false) {
	for (int i = 0; i < size * size; i++) {
		this->map.push_back(State::NONE);
	}
	srand((int) time(NULL));

	if (gameMode == GameMode::SINGLE_PLAYER) {
		makeMove();
	}
}

State Board::getAt(int x, int y) {
	return this->map[x * this->size + y];
}

void Board::setAt(int x, int y, State value) {
	this->map[x * this->size + y] = value;
	this->currentPlayer = !this->currentPlayer;
	State state = checkComplete(this->map);
	if (state != State::NONE) {
		this->complete = true;
		this->onCompleteListener(state);
	}
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

bool Board::isComplete() {
	return this->complete;
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
	State state = checkComplete(this->map);
	if (state != State::NONE) {
		this->complete = true;
		this->onCompleteListener(state);
	}
}

void Board::setOnCompleteListener(std::function<void(State)> onCompleteListener) {
	this->onCompleteListener = onCompleteListener;
}

void Board::reset() {
	for (int i = 0; i < this->size * this->size; i++) {
		this->map[i] = State::NONE;
	}
	this->currentPlayer = State::X;
	this->complete = false;
	if (gameMode == GameMode::SINGLE_PLAYER) {
		makeMove();
	}
}

State Board::checkComplete(std::vector<State> map) {
	int index = 0;
	State state = getCurrentPlayer();
	if (countDiagonally(map, true, state = getCurrentPlayer(), index) == this->size ||
		countDiagonally(map, true, state = !getCurrentPlayer(), index) == this->size ||
		countDiagonally(map, false, state = getCurrentPlayer(), index) == this->size ||
		countDiagonally(map, false, state = !getCurrentPlayer(), index) == this->size) {
		return state;
	}
	for (int i = 0; i < this->size; i++) {
		if (countHorizontally(map, i, state = getCurrentPlayer(), index) == this->size ||
			countVertically(map, i, state = getCurrentPlayer(), index) == this->size ||
			countHorizontally(map, i, state = !getCurrentPlayer(), index) == this->size ||
			countVertically(map, i, state = !getCurrentPlayer(), index) == this->size) {
			return state;
		}
	}
	for (int i = 0; i < this->size * this->size; i++) {
		if (map[i] == State::NONE) {
			return State::NONE;
		}
	}
	return State::TIE;
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
	State state = getCurrentPlayer();
	if (countDiagonally(this->map, true, state = getCurrentPlayer(), index) == this->size - 1 ||
		countDiagonally(this->map, true, state = !getCurrentPlayer(), index) == this->size - 1 ||
		countDiagonally(this->map, false, state = getCurrentPlayer(), index) == this->size - 1 ||
		countDiagonally(this->map, false, state = !getCurrentPlayer(), index) == this->size - 1) {
		this->map[index] = getCurrentPlayer();
		this->currentPlayer = !this->currentPlayer;
		return;
	}
	for (int i = 0; i < this->size; i++) {
		if (countVertically(this->map, i, state = getCurrentPlayer(), index) == this->size - 1 ||
			countHorizontally(this->map, i, state = getCurrentPlayer(), index) == this->size - 1 ||
			countVertically(this->map, i, state = !getCurrentPlayer(), index) == this->size - 1 ||
			countHorizontally(this->map, i, state = !getCurrentPlayer(), index) == this->size - 1) {
			this->map[index] = getCurrentPlayer();
			this->currentPlayer = !this->currentPlayer;
			return;
		}
	}
	makeEasyMove();
}

void Board::makeHardMove() {
	int index = 0, minEval = -100;
	for (int i = 0; i < this->size * this->size; i++) {
		if (this->map[i] == State::NONE) {
			this->map[i] = getCurrentPlayer();
			int eval = minimax(this->map, false, INT_MIN, INT_MAX);
			this->map[i] = State::NONE;
			if (eval > minEval) {
				minEval = eval;
				index = i;
			}
		}
	}

	this->map[index] = getCurrentPlayer();
	this->currentPlayer = !this->currentPlayer;
}

int getByState(std::vector<State> map, int size, State state) {
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (map[i] == state) {
			count++;
		}
	}
	return count;
}

int Board::minimax(std::vector<State> map, bool maximize, int alpha, int beta) {
	int eval = -100;
	State state = checkComplete(map);
	if (state != State::NONE) {
		eval = state == State::X ? 10 : (state == State::O ? -10 : 0);
	}
	if (eval != -100) {
		return eval;
	}

	std::vector<int> emptySlots;
	for (int i = 0; i < this->size * this->size; i++) {
		if (map[i] == State::NONE) {
			emptySlots.push_back(i);
		}
	}

	if (maximize) {
		int bestEval = -100;
		for (auto& position : emptySlots) {
			map[position] = State::X;
			int eval = minimax(map, false, alpha, beta);
			map[position] = State::NONE;
			bestEval = max(bestEval, eval);
			alpha = max(alpha, eval);
			if (beta <= alpha) {
				break;
			}
		}
		return bestEval;
	} else {
		int bestEval = 100;
		for (auto& position : emptySlots) {
			map[position] = State::O;
			int eval = minimax(map, true, alpha, beta);
			map[position] = State::NONE;
			bestEval = min(bestEval, eval);
			beta = min(beta, eval);
			if (beta <= alpha) {
				break;
			}
		}
		return bestEval;
	}
}

int Board::countHorizontally(std::vector<State> map, int y, State state, int& index) {
	int count = 0;
	for (int i = 0; i < this->size; i++) {
		if (map[i * this->size + y] == state) {
			count++;
		} else if (map[i * this->size + y] == State::NONE) {
			index = i * this->size + y;
		} else {
			count = INT_MAX;
			return count;
		}
	}
	return count;
}

int Board::countVertically(std::vector<State> map, int x, State state, int& index) {
	int count = 0;
	for (int i = 0; i < this->size; i++) {
		if (map[x * this->size + i] == state) {
			count++;
		} else if (map[x * this->size + i] == State::NONE) {
			index = x * this->size + i;
		} else {
			count = INT_MAX;
			return count;
		}
	}
	return count;
}

int Board::countDiagonally(std::vector<State> map, bool left, State state, int& index) {
	int count = 0;
	for (int i = 0; i < this->size; i++) {
		if (map[i * this->size + (left ? i : (this->size - i - 1))] == state) {
			count++;
		} else if (map[i * this->size + (left ? i : (this->size - i - 1))] == State::NONE) {
			index = i * this->size + (left ? i : (this->size - i - 1));
		} else {
			count = INT_MAX;
			return count;
		}
	}
	return count;
}