#include "Board.h"

Board::Board(int size) : size(size) {
	this->map = new Value * [size];
	for (int i = 0; i < size; i++) {
		this->map[i] = new Value[size];
	}
}

Board::~Board() {
	for (int i = 0; i < size; i++) {
		delete[] this->map[i];
	}
	delete[] this->map;
}

Value Board::getAt(int x, int y) {
	return this->map[x][y];
}

void Board::setAt(int x, int y, Value value) {
	this->map[x][y] = value;
}

int Board::getSize() {
	return this->size;
}
