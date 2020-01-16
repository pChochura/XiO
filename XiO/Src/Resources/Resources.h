#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"

namespace Textures {
	enum ID {
		Background,
		Logo,
		X,
		O
	};
}

namespace Fonts {
	enum ID {
		Montserrat
	};
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

struct Resources {
	Resources(sf::RenderWindow* window) {
		this->window = window;
	}

	sf::RenderWindow* window;
	TextureHolder textures;
	FontHolder fonts;
};