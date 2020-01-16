#include "BackgroundLayer.h"
#include "../Resources/Resources.h"

BackgroundLayer::BackgroundLayer(Resources* resources) {
	resources->textures.load(Textures::Background, "Data/Textures/background.png");

	float max = (float)std::max(resources->window->getSize().x, resources->window->getSize().y);
	float ratio = 16.0f / 9.0f;
	this->size = { max * ratio, max };
}

void BackgroundLayer::draw(Resources* resources) const {
	sf::Sprite background(resources->textures.get(Textures::Background));
	background.setScale(this->size.x / background.getLocalBounds().width, this->size.y / background.getLocalBounds().height);
	resources->window->draw(background);
}

bool BackgroundLayer::onEvent(Resources* resources, sf::Event* event) const {
	return false;
}
