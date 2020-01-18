#pragma once

////////////////////////////////////////////////////////////
// Typ wyliczeniowy przechowuj�cy warto�� dotycz�ca pola
// na planszy. Przyjmuje warto�ci jako wielokrotno�ci 
// liczby 2 w celu �atwiejszej operacji na bitach.
////////////////////////////////////////////////////////////
enum class State {
	NONE	= 0,
	X		= (1 << 1),
	O		= (1 << 2),
	TIE		= (1 << 3)
};

////////////////////////////////////////////////////////////
// Je�eli warto�� jest r�wna `State::X`, to zostanie
// zwr�ca warto�� `State::O`. Natomiast dla `State::O`
// zwr�cona zostanie warto�� `State::X`. W innych wypadkach
// `State::NONE`
////////////////////////////////////////////////////////////
inline State operator!(State a) {
	if (a == State::X || a == State::O) {
		return a == State::X ? State::O : State::X;
	}
	return State::NONE;
}

////////////////////////////////////////////////////////////
// Zwraca to, co zosta�o przekazane jedynie, gdy obie 
// warto�ci s� sobie r�wne. W przeciwnym przypadku zwracane
// jest `State::NONE`
// Dla przyk�adu:
//		`State::NONE & State::X = State::NONE;`
//		`State::O | State::X = State::O;`
// Gdy obie warto�ci s� r�ne od `State::NONE`, zwraca jest
// ta po lewej stronie.
////////////////////////////////////////////////////////////
inline State operator&(State a, State b) {
	if (a == State::NONE || b == State::NONE) {
		return State::NONE;
	}
	return a == b ? a : State::NONE;
}

////////////////////////////////////////////////////////////
// Zwraca wyra�enie, kt�re jest r�ne od `State::NONE`.
// Dla przyk�adu:
//		`State::NONE | State::X = State::X;`
//		`State::O | State::X = State::O;`
// Gdy obie warto�ci s� r�ne od State::NONE, zwraca jest
// ta po lewej stronie.
////////////////////////////////////////////////////////////
inline State operator|(State a, State b) {
	return a != State::NONE ? a : (b != State::NONE ? b : State::NONE);
}