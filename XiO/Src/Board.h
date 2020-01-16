#pragma once

enum class Value {
	NONE, X, O
};

class Board {
public:
	Board(int);
	~Board();

	Value getAt(int, int);
	void setAt(int, int, Value);

	int getSize();

private:
	int size;
	Value** map;
};