#pragma once
#include <SFML/Graphics.hpp>
#include "../Resources/Resources.h"

class Drawable {
public:
	////////////////////////////////////////////////////////////
	// Funckja, kt�ra jest wywo�ywana co ka�d� klatk�.
	// Wewn�trz powinny znajdowa� si� jedynie instrukcje 
	// rysuj�ce na ekranie.
	////////////////////////////////////////////////////////////
	virtual void draw(Resources*) const = 0;

	////////////////////////////////////////////////////////////
	// Funkcja, kt�ra jest wywo�ywana przy ka�dym wydarzeniu,
	// takim jak ruch myszki czy klikni�cie.
	// Je�eli zostanie zwr�ca warto�� `true`, to warstwy 
	// znajduj�ce si� poni�ej nie otrzymaj� danego wydarzenia.
	////////////////////////////////////////////////////////////
	virtual bool onEvent(Resources*, sf::Event*) const = 0;
};