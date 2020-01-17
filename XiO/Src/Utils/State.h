#pragma once

enum class State {
	NONE	= 0,
	X		= (1 << 1),
	O		= (1 << 2),
};

inline State operator!(State a) {
	if (a == State::NONE) {
		return State::NONE;
	}
	return a == State::X ? State::O : State::X;
}

inline State operator&(State a, State b) {
	if (a == State::NONE || b == State::NONE) {
		return State::NONE;
	}
	return a == b ? a : State::NONE;
}

inline State operator|(State a, State b) {
	return a != State::NONE ? a : (b != State::NONE ? b : State::NONE);
}