#ifndef MAPMANAGER_H_
#define MAPMANAGER_H_

#include "TileMap.h"
#include "GUI.h"

class MapManager
{
private:
    sf::VideoMode &vm;
    sf::Font &font;

    TileMap *loadedMap;

    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, gui::Button *> buttons;
    gui::TextInput *mapNameInput;

    std::vector<std::string> availableMaps;

public:
    MapManager(sf::VideoMode &vm, sf::Font &font);

    virtual ~MapManager();

    void update(const sf::Vector2f &mouse_pos);

    void render(sf::RenderTarget &target);
};

#endif /* MAPMANAGER_H_ */