#include <SFML/Graphics.hpp>
#include "GameUILayer.h"
#include "../Board.h"

GameUILayer::GameUILayer(Resources* resources) {
	resources->textures.load(Textures::O, "Data/Textures/O.png");
	resources->textures.load(Textures::X, "Data/Textures/X.png");

	resources->textures.get(Textures::O).setSmooth(true);
	resources->textures.get(Textures::X).setSmooth(true);

	this->board = new Board(10);
}

void GameUILayer::draw(Resources* resources) const {
	float boardSize = resources->window->getSize().y * 0.75f;
	float unitSize = boardSize / this->board->getSize();
	float x = resources->window->getSize().x / 2.0f;
	float y = resources->window->getSize().y * 0.125f;

	sf::RectangleShape line;
	line.setFillColor(sf::Color(151, 151, 151));
	line.setSize(sf::Vector2f(2.0f, boardSize));
	for (int i = 1; i < this->board->getSize(); i++) {
		line.setPosition(sf::Vector2f(x - boardSize / 2.0f + i * unitSize, y));
		resources->window->draw(line);
	}
	line.setSize(sf::Vector2f(boardSize, 2.0f));
	for (int i = 1; i < this->board->getSize(); i++) {
		line.setPosition(sf::Vector2f(x - boardSize / 2.0f, y + i * unitSize));
		resources->window->draw(line);
	}

	sf::Sprite icon;
	for (int i = 0; i < this->board->getSize(); i++) {
		for (int j = 0; j < this->board->getSize(); j++) {
			switch (this->board->getAt(i, j)) {
			case Value::X:
				icon.setTexture(resources->textures.get(Textures::X));
				break;
			case Value::O:
				icon.setTexture(resources->textures.get(Textures::O));
				break;
			}
			icon.setScale(unitSize / icon.getLocalBounds().width, unitSize / icon.getLocalBounds().height);
			icon.setPosition(i * unitSize + x - boardSize / 2.0f, j * unitSize + y);
			resources->window->draw(icon);
		}
	}
}

bool GameUILayer::onEvent(Resources* resources, sf::Event* event) const {
	if (event->type == sf::Event::MouseButtonPressed && event->mouseButton.button == sf::Mouse::Left) {
		float boardSize = resources->window->getSize().y * 0.75f;
		float unitSize = boardSize / this->board->getSize();
		float x = resources->window->getSize().x / 2.0f;
		float y = resources->window->getSize().y * 0.125f;
		sf::Vector2i pos = sf::Mouse::getPosition(*resources->window);
		if (pos.x >= x - boardSize / 2.0f && pos.x <= x + boardSize / 2.0f &&
			pos.y >= y && pos.y <= y + boardSize) {
			int unitX = (pos.x - x + boardSize / 2.0f) / unitSize;
			int unitY = (pos.y - y) / unitSize;
			this->board->setAt(unitX, unitY, Value::X);
			return true;
		}
	}
	return false;
}
