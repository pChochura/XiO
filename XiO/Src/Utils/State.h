#pragma once

////////////////////////////////////////////////////////////
// Typ wyliczeniowy przechowuj¹cy wartoœæ dotycz¹ca pola
// na planszy. Przyjmuje wartoœci jako wielokrotnoœci 
// liczby 2 w celu ³atwiejszej operacji na bitach.
////////////////////////////////////////////////////////////
enum class State {
	NONE	= 0,
	X		= (1 << 1),
	O		= (1 << 2),
	TIE		= (1 << 3)
};

////////////////////////////////////////////////////////////
// Je¿eli wartoœæ jest równa `State::X`, to zostanie
// zwróca wartoœæ `State::O`. Natomiast dla `State::O`
// zwrócona zostanie wartoœæ `State::X`. W innych wypadkach
// `State::NONE`
////////////////////////////////////////////////////////////
inline State operator!(State a) {
	if (a == State::X || a == State::O) {
		return a == State::X ? State::O : State::X;
	}
	return State::NONE;
}

////////////////////////////////////////////////////////////
// Zwraca to, co zosta³o przekazane jedynie, gdy obie 
// wartoœci s¹ sobie równe. W przeciwnym przypadku zwracane
// jest `State::NONE`
// Dla przyk³adu:
//		`State::NONE & State::X = State::NONE;`
//		`State::O | State::X = State::O;`
// Gdy obie wartoœci s¹ ró¿ne od `State::NONE`, zwraca jest
// ta po lewej stronie.
////////////////////////////////////////////////////////////
inline State operator&(State a, State b) {
	if (a == State::NONE || b == State::NONE) {
		return State::NONE;
	}
	return a == b ? a : State::NONE;
}

////////////////////////////////////////////////////////////
// Zwraca wyra¿enie, które jest ró¿ne od `State::NONE`.
// Dla przyk³adu:
//		`State::NONE | State::X = State::X;`
//		`State::O | State::X = State::O;`
// Gdy obie wartoœci s¹ ró¿ne od State::NONE, zwraca jest
// ta po lewej stronie.
////////////////////////////////////////////////////////////
inline State operator|(State a, State b) {
	return a != State::NONE ? a : (b != State::NONE ? b : State::NONE);
}