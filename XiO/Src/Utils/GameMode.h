#pragma once

enum class GameMode {
	SINGLE_PLAYER	= (1 << 1),
	MULTI_PLAYER	= (1 << 2)
};

enum class Difficulty {
	EASY	= (1 << 1),
	MEDIUM	= (1 << 2), 
	HARD	= (1 << 3)
};