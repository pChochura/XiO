#include <time.h>
#include <SFML/Graphics.hpp>
#include "GameUILayer.h"
#include "../Board.h"
#include "../Utils/State.h"
#include "../Utils/GameMode.h"

GameUILayer::GameUILayer(Resources* resources, GameMode gameMode) {
	resources->textures.load(Textures::O, "Data/Textures/O.png");
	resources->textures.load(Textures::X, "Data/Textures/X.png");

	resources->textures.get(Textures::O).setSmooth(true);
	resources->textures.get(Textures::X).setSmooth(true);

	this->board = new Board(3, gameMode);
	this->board->setOnCompleteListener([&](State state) {
		onCompleteListener()
	});
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
			case State::X:
				icon.setTexture(resources->textures.get(Textures::X));
				break;
			case State::O:
				icon.setTexture(resources->textures.get(Textures::O));
				break;
			default:
				continue;
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
			int unitX = (int) ((pos.x - x + boardSize / 2.0f) / unitSize);
			int unitY = (int) ((pos.y - y) / unitSize);
			this->board->setAt(unitX, unitY, this->board->getCurrentPlayer());
			if (this->board->getGameMode() == GameMode::SINGLE_PLAYER) {
				this->board->makeMove();
			}
			return true;
		}
	}
	return false;
}

void GameUILayer::setOnCompleteListener(std::function<void()> onCompleteListener) {
	this->onCompleteListener = onCompleteListener;
}