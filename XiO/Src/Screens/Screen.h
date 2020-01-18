#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "../Layers/Layer.h"
#include "../Drawables/Drawable.h"
#include "../Resources/Resources.h"

////////////////////////////////////////////////////////////
// Klasa opisuj¹ca obecnie wyœwietlany obraz na ekranie.
// Sk³ada siê z warstw.
////////////////////////////////////////////////////////////
class Screen : public Drawable {
public:
	////////////////////////////////////////////////////////////
	// Powinna byæ wywo³ywana na pocz¹tku w celu za³adowania
	// wymaganych zasobów.
	////////////////////////////////////////////////////////////
	virtual void load(Resources*) = 0;

	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

	////////////////////////////////////////////////////////////
	// Pozwala ustawiæ funkcjê, która zostanie wywo³ana gdy
	// wymagane bêdzie zmienie obecnie wyœwietlanego obrazu.
	// Parametrem jest kolejna instancja `Screen`, która 
	// nastêpnie bêdzie wyœwietlana.
	////////////////////////////////////////////////////////////
	void setOnChangeScreenListener(std::function<void(Screen*)>);

protected:
	std::vector<Layer*> layers;
	std::function<void(Screen*)> onChangeScreenListener;
};