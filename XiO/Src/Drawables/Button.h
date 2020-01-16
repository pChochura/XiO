#pragma once
#include <functional>
#include "Drawable.h"
#include "../Resources/Resources.h"

enum ButtonSize {
	WrapContent = INT_MIN
};

class Button : public Drawable {
public:
	Button(sf::Vector2f size = { ButtonSize::WrapContent, ButtonSize::WrapContent });

	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

	Button* withOnClickListener(std::function<void(const Button*)> onClickListener);

	Button* withPadding(sf::Vector2f padding);

	Button* withText(std::string text);
	Button* withTextSize(float textSize);
	Button* withTextColor(sf::Color textColor);
	Button* withTextFont(sf::Font textFont);

	Button* withBackgroundColor(sf::Color backgroundColor);

	Button* withPosition(sf::Vector2f position);

	Button* build();

private:
	bool isHovering(Resources*) const;
	void calculateSize();

private:
	sf::Vector2f size;

	sf::Vector2f position;
	sf::Vector2f padding;

	float textSize;
	std::string text;
	sf::Color textColor;
	sf::Font textFont;

	sf::Color backgroundColor;

	std::function<void(const Button*)> onClickListener;
};