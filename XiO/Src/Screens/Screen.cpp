#include "Screen.h"
#include "../Resources/Resources.h"

void Screen::draw(Resources* resources) const {
	for (auto& layer : this->layers) {
		layer->draw(resources);
	}
}

bool Screen::onEvent(Resources* resources, sf::Event* event) const {
	for (auto layer = this->layers.rbegin(); layer < this->layers.rend(); layer++) {
		if ((*layer)->onEvent(resources, event)) {
			return true;
		}
	}

	return false;
}

void Screen::setOnChangeScreenListener(std::function<void(Screen*)> onChangeScreenListener) {
	this->onChangeScreenListener = onChangeScreenListener;
}