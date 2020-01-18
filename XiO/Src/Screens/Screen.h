#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "../Layers/Layer.h"
#include "../Drawables/Drawable.h"
#include "../Resources/Resources.h"

////////////////////////////////////////////////////////////
// Klasa opisuj�ca obecnie wy�wietlany obraz na ekranie.
// Sk�ada si� z warstw.
////////////////////////////////////////////////////////////
class Screen : public Drawable {
public:
	////////////////////////////////////////////////////////////
	// Powinna by� wywo�ywana na pocz�tku w celu za�adowania
	// wymaganych zasob�w.
	////////////////////////////////////////////////////////////
	virtual void load(Resources*) = 0;

	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

	////////////////////////////////////////////////////////////
	// Pozwala ustawi� funkcj�, kt�ra zostanie wywo�ana gdy
	// wymagane b�dzie zmienie obecnie wy�wietlanego obrazu.
	// Parametrem jest kolejna instancja `Screen`, kt�ra 
	// nast�pnie b�dzie wy�wietlana.
	////////////////////////////////////////////////////////////
	void setOnChangeScreenListener(std::function<void(Screen*)>);

protected:
	std::vector<Layer*> layers;
	std::function<void(Screen*)> onChangeScreenListener;
};