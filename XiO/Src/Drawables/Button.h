#pragma once
#include <functional>
#include "Drawable.h"
#include "../Resources/Resources.h"

enum ButtonSize {
	WrapContent = INT_MIN
};

////////////////////////////////////////////////////////////
// Klasa pozwalaj¹ca tworzyæ przyciski i rysowaæ je na 
// ekranie. Mo¿liwa personalizacja to: kolor t³a, czcionki,
// rozmiar czcionki oraz sam tekst.
////////////////////////////////////////////////////////////
class Button : public Drawable {
public:
	Button(sf::Vector2f size = { ButtonSize::WrapContent, ButtonSize::WrapContent });

	virtual void draw(Resources*) const override;
	virtual bool onEvent(Resources*, sf::Event*) const override;

	////////////////////////////////////////////////////////////
	// Pozwala dodaæ funkcjê, która zostanie wywo³ana po 
	// klikniêciu przycisku.
	// Zwraca instancjê tego obiektu, ¿eby mo¿na by³o wywo³ywaæ
	// metody ³añcuchowo.
	////////////////////////////////////////////////////////////
	Button* withOnClickListener(std::function<void(const Button*)> onClickListener);

	////////////////////////////////////////////////////////////
	// Pozwala dodaæ odstêp tekstu od krawêdzi, je¿eli rozmiar
	// zosta³ ustawiony na `ButtonSize::WrapContent`.
	// Zwraca instancjê tego obiektu, ¿eby mo¿na by³o wywo³ywaæ
	// metody ³añcuchowo.
	////////////////////////////////////////////////////////////
	Button* withPadding(sf::Vector2f padding);

	////////////////////////////////////////////////////////////
	// Pozwala ustawiæ tekst przycisku.
	// Zwraca instancjê tego obiektu, ¿eby mo¿na by³o wywo³ywaæ
	// metody ³añcuchowo.
	////////////////////////////////////////////////////////////
	Button* withText(std::string text);

	////////////////////////////////////////////////////////////
	// Pozwala ustawiæ rozmiar czcionki.
	// Zwraca instancjê tego obiektu, ¿eby mo¿na by³o wywo³ywaæ
	// metody ³añcuchowo.
	////////////////////////////////////////////////////////////
	Button* withTextSize(float textSize);

	////////////////////////////////////////////////////////////
	// Pozwala ustawiæ kolor tekstu.
	// Zwraca instancjê tego obiektu, ¿eby mo¿na by³o wywo³ywaæ
	// metody ³añcuchowo.
	////////////////////////////////////////////////////////////
	Button* withTextColor(sf::Color textColor);

	////////////////////////////////////////////////////////////
	// Pozwala ustawiæ czcionkê.
	// Zwraca instancjê tego obiektu, ¿eby mo¿na by³o wywo³ywaæ
	// metody ³añcuchowo.
	////////////////////////////////////////////////////////////
	Button* withTextFont(sf::Font textFont);

	////////////////////////////////////////////////////////////
	// Pozwala ustawiæ kolor t³a przycisku.
	// Zwraca instancjê tego obiektu, ¿eby mo¿na by³o wywo³ywaæ
	// metody ³añcuchowo.
	////////////////////////////////////////////////////////////
	Button* withBackgroundColor(sf::Color backgroundColor);

	////////////////////////////////////////////////////////////
	// Pozwala ustawiæ pozycjê przycisku na ekranie.
	// Zwraca instancjê tego obiektu, ¿eby mo¿na by³o wywo³ywaæ
	// metody ³añcuchowo.
	////////////////////////////////////////////////////////////
	Button* withPosition(sf::Vector2f position);

	////////////////////////////////////////////////////////////
	// Po ustawieniu wszystkich wartoœci nale¿y wykonaæ tê
	// metodê, ¿eby rozmiar przycisku zosta³ poprawnie 
	// obliczony.
	// Zwraca instancjê tego obiektu, ¿eby mo¿na by³o wywo³ywaæ
	// metody ³añcuchowo.
	////////////////////////////////////////////////////////////
	Button* build();

private:
	////////////////////////////////////////////////////////////
	// Zwraca `true` jeœli myszka znajduje siê nad przyciskiem.
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