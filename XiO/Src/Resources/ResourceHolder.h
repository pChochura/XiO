#pragma once
#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////
// Klasa odpowiedzialna za przechowywanie zasob�w, takich 
// jak czcionki lub grafiki. Zar�wno `sf::Fonts` jak 
// i `sf::Texture` posiadaj� metod� `loadFromFile`.
// Wczytany zas�b zostaje zapisany do `mResourceMap`,
// w celu szybszego wykorzystania go w przysz�o�ci.
////////////////////////////////////////////////////////////
template <typename Resource, typename Identifier>
class ResourceHolder {
public:
	////////////////////////////////////////////////////////////
	// Metoda pozwalaj�ca za�adowa� do pami�ci dany zas�b i
	// zapisa� go jako dane `id`.
	////////////////////////////////////////////////////////////
	void load(Identifier id, std::string filename) {
		std::unique_ptr<Resource> resource(new Resource());

		if (!resource->loadFromFile(filename)) {
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
		}

		insertResource(id, std::move(resource));
	}

	////////////////////////////////////////////////////////////
	// Metoda pozwala pobra� znajduj�cy si� w pami�ci zas�b za 
	// pomoc� danego `id`.
	////////////////////////////////////////////////////////////
	Resource& get(Identifier id) const {
		return *mResourceMap.find(id)->second;
	}

protected:
	void insertResource(Identifier id, std::unique_ptr<Resource> resource) {
		mResourceMap.insert(std::make_pair(id, std::move(resource)));
	}

protected:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};