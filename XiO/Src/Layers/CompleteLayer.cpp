#include <SFML/Graphics.hpp>
#include "CompleteLayer.h"
#include "../Drawables/Button.h"
#include "../Drawables/RoundedRectangleShape.h"

CompleteLayer::CompleteLayer(Resources* resources, State state) : state(state) {
	resources->fonts.load(Fonts::ID::Montserrat, "Data/Fonts/Montserrat.ttf");

	this->size = sf::Vector2f(resources->window->getSize().y * 0.65f, resources->window->getSize().y * 0.45f);
	this->pos = sf::Vector2f((resources->window->getSize().x - this->size.x) / 2.0f, (resources->window->getSize().y - this->size.y) / 2.0f);

	this->buttons.push_back(
		(new Button(sf::Vector2f(200.0f, 60.0f)))
		->withBackgroundColor(sf::Color(245, 84, 11))
		->withText("Try Again")
		->withTextFont(resources->fonts.get(Fonts::ID::Montserrat))
		->withPadding(sf::Vector2f(50.0f, 30.0f))
		->withPosition(sf::Vector2f(resources->window->getSize().x / 2.0f - 100.0f, resources->window->getSize().y / 2.0f))
		->withTextColor(sf::Color::White)
		->withTextSize(20)
		->withOnClickListener([&](const Button* button) {
			this->onClickListener(false);
		})
		->build()
	);
	this->buttons.push_back(
		(new Button(sf::Vector2f(200.0f, 60.0f)))
		->withBackgroundColor(sf::Color(98, 146, 182))
		->withText("Exit")
		->withTextFont(resources->fonts.get(Fonts::ID::Montserrat))
		->withPadding(sf::Vector2f(50.0f, 30.0f))
		->withPosition(sf::Vector2f(resources->window->getSize().x / 2.0f - 100.0f, resources->window->getSize().y / 2.0f + 75.0f))
		->withTextColor(sf::Color::White)
		->withTextSize(20)
		->withOnClickListener([&](const Button* button) {
			this->onClickListener(true);
		})
		->build()
	);
}

void CompleteLayer::draw(Resources* resources) const {
	sf::RoundedRectangleShape dialog(this->size, 30.0f, 50);
	dialog.setFillColor(sf::Color(51, 51, 51));
	dialog.setPosition(this->pos);
	resources->window->draw(dialog);

	std::string temp;
	switch (this->state) {
	case State::TIE:
		temp = "It's a tie.";
		break;
	case State::X:
		temp = "Player with 'X' won.";
		break;
	case State::O:
		temp = "Player with 'O' won.";
		break;
	}
	sf::Text text(temp, resources->fonts.get(Fonts::ID::Montserrat), 30);
	text.setFillColor(sf::Color::White);
	text.setPosition((resources->window->getSize().x - text.getLocalBounds().width) / 2.0f, this->pos.y + 50.0f);
	resources->window->draw(text);

	for (auto& button : this->buttons) {
		button->draw(resources);
	}
}

bool CompleteLayer::onEvent(Resources* resources, sf::Event* event) const {
	for (auto button = this->buttons.rbegin(); button < this->buttons.rend(); button++) {
		if ((*button)->onEvent(resources, event)) {
			return true;
		}
	}
	return true;
}

void CompleteLayer::setOnClickListener(std::function<void(bool)> onClickListener) {
	this->onClickListener = onClickListener;
}

void CompleteLayer::setState(State state) {
	this->state = state;
}
