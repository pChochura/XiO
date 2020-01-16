#include "Button.h"

Button::Button(sf::Vector2f size) : textSize(0) {
	this->size = size;
}

void Button::draw(Resources*) const {
	sf::Color maskColor = isHovering(context) ? sf::Color(200, 200, 200) : sf::Color::White;

	sf::RoundedRectangleShape rect(this->size, 5, 50);
	rect.setFillColor(this->backgroundColor * maskColor);
	rect.setPosition(this->pos);
	context->window->draw(rect);

	sf::Text text(this->text, this->textFont, (unsigned int)this->textSize);
	text.setFillColor(this->textColor);
	text.setPosition(this->pos.x + this->size.x / 2.0f - text.getLocalBounds().width / 2.0f, this->pos.y + this->size.y / 2.0f - text.getLocalBounds().height);
	context->window->draw(text);
}

bool Button::onEvent(Resources*, sf::Event*) const {
	return false;
}

bool Button::isHovering(Resources* resources) const {
	sf::Vector2i pos = sf::Mouse::getPosition(*resources->window);
	if (pos.x >= this->position.x && pos.x <= this->position.x + this->size.x &&
		pos.y >= this->position.y && pos.y <= this->position.y + this->size.y) {
		return true;
	}
	return false;
}

void Button::calculateSize() {
	sf::Text text(this->text, this->textFont, (unsigned int)this->textSize);
	if (this->text.length() != 0) {
		if (this->size.x == ButtonSize::WrapContent) {
			this->size.x = text.getLocalBounds().width + this->padding.x;
		}
		if (this->size.y == ButtonSize::WrapContent) {
			this->size.y = text.getLocalBounds().height + this->padding.y;
		}
	}
}

Button* Button::withPadding(sf::Vector2f padding) {
	this->padding = padding;
	return this;
}

Button* Button::withText(std::string text) {
	this->text = text;
	return this;
}

Button* Button::withTextSize(float textSize) {
	this->textSize = textSize;
	return this;
}

Button* Button::withTextColor(sf::Color textColor) {
	this->textColor = textColor;
	return this;
}

Button* Button::withTextFont(sf::Font textFont) {
	this->textFont = textFont;
	return this;
}

Button* Button::withBackgroundColor(sf::Color backgroundColor) {
	this->backgroundColor = backgroundColor;
	return this;
}

Button* Button::withPosition(sf::Vector2f position) {
	this->position = position;
	return this;
}

Button* Button::build() {
	if (this->size.x == ButtonSize::WrapContent || this->size.y == ButtonSize::WrapContent) {
		this->calculateSize();
	}
	return this;
}
