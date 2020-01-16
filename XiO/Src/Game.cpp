#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Screens/MenuScreen.h"
#include "Resources/Resources.h"

Game::Game(std::string title, int width, int height) : screen(new MenuScreen) {
	this->resources = new Resources(
		new sf::RenderWindow(sf::VideoMode(width, height), 
			title, 
			sf::Style::Close, 
			sf::ContextSettings(0, 0, 8)
		)
	);
	changeScreen(this->screen);
}

void Game::show() {
	while (this->resources->window->isOpen()) {
		sf::Event event;
		while (this->resources->window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->resources->window->close();
			} else {
				this->screen->onEvent(this->resources, &event);
			}
		}

		this->resources->window->clear();

		this->screen->draw(resources);

		this->resources->window->display();
	}
}

void Game::changeScreen(Screen* screen) {
	this->screen = screen;
	this->screen->load(this->resources);
	this->screen->setOnChangeScreenListener([&](Screen* s) {
		changeScreen(s);
	});
}