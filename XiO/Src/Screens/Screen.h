#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "../Layers/Layer.h"
#include "../Drawables/Drawable.h"
#include "../Resources/Resources.h"

class Screen : public Drawable {
public:
	virtual void load(Resources*) = 0;
	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

	void setOnChangeScreenListener(std::function<void(Screen*)> onChangeScreenListener);

protected:
	std::vector<Layer*> layers;
	std::function<void(Screen*)> onChangeScreenListener;
};