#include "DifficultyLayer.h"
#include "../Drawables/RoundedRectangleShape.h"

DifficultyLayer::DifficultyLayer(Resources* resources) {
	resources->fonts.load(Fonts::ID::Montserrat, "Data/Fonts/Montserrat.ttf");

	this->size = sf::Vector2f(resources->window->getSize().y * 0.75f, resources->window->getSize().y * 0.3f);
	this->pos = sf::Vector2f((resources->window->getSize().x - this->size.x) / 2.0f, (resources->window->getSize().y - this->size.y) / 2.0f);

	this->buttons.push_back(
		(new Button(sf::Vector2f(120.0f, 60.0f)))
		->withBackgroundColor(sf::Color(67, 104, 185))
		->withText("EASY")
		->withTextFont(resources->fonts.get(Fonts::ID::Montserrat))
		->withPadding(sf::Vector2f(50.0f, 30.0f))
		->withPosition(sf::Vector2f(resources->window->getSize().x / 2.0f - 190.0f, resources->window->getSize().y / 2.0f))
		->withTextColor(sf::Color::White)
		->withTextSize(20)
		->withOnClickListener([&](const Button* button) {
			this->onClickListener(Difficulty::EASY);
		})
		->build()
	);
	this->buttons.push_back(
		(new Button(sf::Vector2f(120.0f, 60.0f)))
		->withBackgroundColor(sf::Color(248, 148, 5))
		->withText("MEDIUM")
		->withTextFont(resources->fonts.get(Fonts::ID::Montserrat))
		->withPadding(sf::Vector2f(50.0f, 30.0f))
		->withPosition(sf::Vector2f(resources->window->getSize().x / 2.0f - 60.0f, resources->window->getSize().y / 2.0f))
		->withTextColor(sf::Color::White)
		->withTextSize(20)
		->withOnClickListener([&](const Button* button) {
			this->onClickListener(Difficulty::MEDIUM);
		})
		->build()
	);
	this->buttons.push_back(
		(new Button(sf::Vector2f(120.0f, 60.0f)))
		->withBackgroundColor(sf::Color(156, 11, 1))
		->withText("HARD")
		->withTextFont(resources->fonts.get(Fonts::ID::Montserrat))
		->withPadding(sf::Vector2f(50.0f, 30.0f))
		->withPosition(sf::Vector2f(resources->window->getSize().x / 2.0f + 70.0f, resources->window->getSize().y / 2.0f))
		->withTextColor(sf::Color::White)
		->withTextSize(20)
		->withOnClickListener([&](const Button* button) {
			this->onClickListener(Difficulty::HARD);
		})
		->build()
	);
}

void DifficultyLayer::draw(Resources* resources) const {
	sf::RoundedRectangleShape dialog(this->size, 30.0f, 50);
	dialog.setFillColor(sf::Color(51, 51, 51));
	dialog.setPosition(this->pos);
	resources->window->draw(dialog);

	sf::Text text("Choose difficulty", resources->fonts.get(Fonts::ID::Montserrat), 30);
	text.setFillColor(sf::Color::White);
	text.setPosition((resources->window->getSize().x - text.getLocalBounds().width) / 2.0f, this->pos.y + 50.0f);
	resources->window->draw(text);

	for (auto& button : this->buttons) {
		button->draw(resources);
	}
}

bool DifficultyLayer::onEvent(Resources* resources, sf::Event* event) const {
	for (auto button = this->buttons.rbegin(); button < this->buttons.rend(); button++) {
		if ((*button)->onEvent(resources, event)) {
			return true;
		}
	}
	return true;
}

void DifficultyLayer::setOnClickListener(std::function<void(Difficulty)> onClickListener) {
	this->onClickListener = onClickListener;
}
