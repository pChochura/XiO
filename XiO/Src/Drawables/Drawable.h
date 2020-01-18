#pragma once
#include <SFML/Graphics.hpp>
#include "../Resources/Resources.h"

class Drawable {
public:
	////////////////////////////////////////////////////////////
	// Funckja, która jest wywo³ywana co ka¿d¹ klatkê.
	// Wewn¹trz powinny znajdowaæ siê jedynie instrukcje 
	// rysuj¹ce na ekranie.
	////////////////////////////////////////////////////////////
	virtual void draw(Resources*) const = 0;

	////////////////////////////////////////////////////////////
	// Funkcja, która jest wywo³ywana przy ka¿dym wydarzeniu,
	// takim jak ruch myszki czy klikniêcie.
	// Je¿eli zostanie zwróca wartoœæ `true`, to warstwy 
	// znajduj¹ce siê poni¿ej nie otrzymaj¹ danego wydarzenia.
	////////////////////////////////////////////////////////////
	virtual bool onEvent(Resources*, sf::Event*) const = 0;
};