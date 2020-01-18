#pragma once
#include <functional>
#include "Drawable.h"
#include "../Resources/Resources.h"

enum ButtonSize {
	WrapContent = INT_MIN
};

////////////////////////////////////////////////////////////
// Klasa pozwalaj�ca tworzy� przyciski i rysowa� je na 
// ekranie. Mo�liwa personalizacja to: kolor t�a, czcionki,
// rozmiar czcionki oraz sam tekst.
////////////////////////////////////////////////////////////
class Button : public Drawable {
public:
	Button(sf::Vector2f size = { ButtonSize::WrapContent, ButtonSize::WrapContent });

	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

	////////////////////////////////////////////////////////////
	// Pozwala doda� funkcj�, kt�ra zostanie wywo�ana po 
	// klikni�ciu przycisku.
	// Zwraca instancj� tego obiektu, �eby mo�na by�o wywo�ywa�
	// metody �a�cuchowo.
	////////////////////////////////////////////////////////////
	Button* withOnClickListener(std::function<void(const Button*)> onClickListener);

	////////////////////////////////////////////////////////////
	// Pozwala doda� odst�p tekstu od kraw�dzi, je�eli rozmiar
	// zosta� ustawiony na `ButtonSize::WrapContent`.
	// Zwraca instancj� tego obiektu, �eby mo�na by�o wywo�ywa�
	// metody �a�cuchowo.
	////////////////////////////////////////////////////////////
	Button* withPadding(sf::Vector2f padding);

	////////////////////////////////////////////////////////////
	// Pozwala ustawi� tekst przycisku.
	// Zwraca instancj� tego obiektu, �eby mo�na by�o wywo�ywa�
	// metody �a�cuchowo.
	////////////////////////////////////////////////////////////
	Button* withText(std::string text);

	////////////////////////////////////////////////////////////
	// Pozwala ustawi� rozmiar czcionki.
	// Zwraca instancj� tego obiektu, �eby mo�na by�o wywo�ywa�
	// metody �a�cuchowo.
	////////////////////////////////////////////////////////////
	Button* withTextSize(float textSize);

	////////////////////////////////////////////////////////////
	// Pozwala ustawi� kolor tekstu.
	// Zwraca instancj� tego obiektu, �eby mo�na by�o wywo�ywa�
	// metody �a�cuchowo.
	////////////////////////////////////////////////////////////
	Button* withTextColor(sf::Color textColor);

	////////////////////////////////////////////////////////////
	// Pozwala ustawi� czcionk�.
	// Zwraca instancj� tego obiektu, �eby mo�na by�o wywo�ywa�
	// metody �a�cuchowo.
	////////////////////////////////////////////////////////////
	Button* withTextFont(sf::Font textFont);

	////////////////////////////////////////////////////////////
	// Pozwala ustawi� kolor t�a przycisku.
	// Zwraca instancj� tego obiektu, �eby mo�na by�o wywo�ywa�
	// metody �a�cuchowo.
	////////////////////////////////////////////////////////////
	Button* withBackgroundColor(sf::Color backgroundColor);

	////////////////////////////////////////////////////////////
	// Pozwala ustawi� pozycj� przycisku na ekranie.
	// Zwraca instancj� tego obiektu, �eby mo�na by�o wywo�ywa�
	// metody �a�cuchowo.
	////////////////////////////////////////////////////////////
	Button* withPosition(sf::Vector2f position);

	////////////////////////////////////////////////////////////
	// Po ustawieniu wszystkich warto�ci nale�y wykona� t�
	// metod�, �eby rozmiar przycisku zosta� poprawnie 
	// obliczony.
	// Zwraca instancj� tego obiektu, �eby mo�na by�o wywo�ywa�
	// metody �a�cuchowo.
	////////////////////////////////////////////////////////////
	Button* build();

private:
	////////////////////////////////////////////////////////////
	// Zwraca `true` je�li myszka znajduje si� nad przyciskiem.
	////////////////////////////////////////////////////////////
	bool isHovering(Resources*) const;

	////////////////////////////////////////////////////////////
	// Oblicza rozmiar przycisku na podstawie `padding`.
	////////////////////////////////////////////////////////////
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