#include "MenuUILayer.h"
#include "../Utils/GameMode.h"

MenuUILayer::MenuUILayer(Resources* resources) {
	resources->textures.load(Textures::ID::Logo, "Data/Textures/logo.png");
	resources->fonts.load(Fonts::ID::Montserrat, "Data/Fonts/Montserrat.ttf");

	this->buttons.push_back(
		(new Button(sf::Vector2f(300.0f, 60.0f)))
			->withBackgroundColor(sf::Color(140, 0, 179))
			->withPadding(sf::Vector2f(50.0f, 35.0f))
			->withText("Singleplayer")
			->withTextSize(20)
			->withTextColor(sf::Color::White)
			->withTextFont(resources->fonts.get(Fonts::ID::Montserrat))
			->withPosition(sf::Vector2f(resources->window->getSize().x / 2.0f - 150.0f, 375.0f))
			->withOnClickListener([&](const Button* b) {
				this->onClickListener(GameMode::SINGLE_PLAYER);
			})
			->build()
	);
	this->buttons.push_back(
		(new Button(sf::Vector2f(300.0f, 60.0f)))
			->withBackgroundColor(sf::Color(25, 139, 179))
			->withPadding(sf::Vector2f(50.0f, 35.0f))
			->withText("Multiplayer")
			->withTextSize(20)
			->withTextColor(sf::Color::White)
			->withTextFont(resources->fonts.get(Fonts::ID::Montserrat))
			->withPosition(sf::Vector2f(resources->window->getSize().x / 2.0f - 150.0f, 450.0f))
			->withOnClickListener([&](const Button* b) {
				this->onClickListener(GameMode::MULTI_PLAYER);
			})
			->build()
	);
}

void MenuUILayer::draw(Resources* resources) const {
	sf::Sprite logo(resources->textures.get(Textures::ID::Logo));
	logo.setPosition((resources->window->getSize().x - logo.getLocalBounds().width) / 2.0f, 100.0f);
	logo.setColor(sf::Color(216, 226, 54, 255));
	resources->window->draw(logo);

	for (auto& button : this->buttons) {
		button->draw(resources);
	}
}

bool MenuUILayer::onEvent(Resources* resources, sf::Event* event) const {
	for (auto button = this->buttons.rbegin(); button < this->buttons.rend(); button++) {
		if ((*button)->onEvent(resources, event)) {
			return true;
		}
	}
	return false;
}

void MenuUILayer::setOnClickListener(std::function<void(GameMode)> onClickListener) {
	this->onClickListener = onClickListener;
}