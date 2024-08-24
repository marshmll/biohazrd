#ifndef INVENTORYGUI_H_
#define INVENTORYGUI_H_

#include "Inventory.h"
#include "GUI.h"

class InventoryGUI
{
private:
    Inventory &inventory;
    sf::VideoMode &vm;

    // Hotbar
    sf::RectangleShape hotbarBg;
    sf::RectangleShape hotbarFrame;
    sf::RectangleShape hotbarSelector;

    void initHotbar();

public:
    
    InventoryGUI(Inventory &inventory, sf::VideoMode &vm);

    virtual ~InventoryGUI();

    void update(const float &dt, sf::Vector2f &mouse_pos);

    void render(sf::RenderTarget &target);
};

#endif /* INVENTORYGUI_H_ */