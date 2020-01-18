#pragma once
#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

////////////////////////////////////////////////////////////
// Klasa odpowiedzialna za przechowywanie zasobów, takich 
// jak czcionki lub grafiki. Zarówno `sf::Fonts` jak 
// i `sf::Texture` posiadaj¹ metodê `loadFromFile`.
// Wczytany zasób zostaje zapisany do `mResourceMap`,
// w celu szybszego wykorzystania go w przysz³oœci.
////////////////////////////////////////////////////////////
template <typename Resource, typename Identifier>
class ResourceHolder {
public:
	////////////////////////////////////////////////////////////
	// Metoda pozwalaj¹ca za³adowaæ do pamiêci dany zasób i
	// zapisaæ go jako dane `id`.
	////////////////////////////////////////////////////////////
	void load(Identifier id, std::string filename) {
		std::unique_ptr<Resource> resource(new Resource());

		if (!resource->loadFromFile(filename)) {
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
		}

		insertResource(id, std::move(resource));
	}

	////////////////////////////////////////////////////////////
	// Metoda pozwala pobraæ znajduj¹cy siê w pamiêci zasób za 
	// pomoc¹ danego `id`.
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