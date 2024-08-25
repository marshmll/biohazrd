#include "stdafx.h"
#include "InventoryGUI.h"

void InventoryGUI::initHotbar()
{
    hotbarBg.setSize(sf::Vector2f(gui::p2pY(vm, 8.f) * 9.f, gui::p2pY(vm, 8.f)));
    hotbarBg.setPosition(vm.width / 2.f - hotbarBg.getSize().x / 2.f, gui::p2pY(vm, 90.f));
    hotbarBg.setFillColor(sf::Color(50, 50, 20, 100));

    hotbarFrame.setSize(sf::Vector2f(hotbarBg.getSize().y, hotbarBg.getSize().y));
    hotbarFrame.setFillColor(sf::Color::Transparent);
    hotbarFrame.setOutlineThickness(-2.f);
    hotbarFrame.setOutlineColor(sf::Color(200, 200, 200, 255));
    hotbarFrame.setPosition(hotbarBg.getPosition());

    hotbarSelector.setSize(sf::Vector2f(hotbarBg.getSize().y, hotbarBg.getSize().y));
    hotbarSelector.setPosition(hotbarBg.getPosition());
    hotbarSelector.setFillColor(sf::Color::Transparent);
    hotbarSelector.setOutlineThickness(2.f);
    hotbarSelector.setOutlineColor(sf::Color::White);

    hotbarSize = 9;

    for (unsigned short i = 0; i < hotbarSize; ++i)
    {
        sf::RectangleShape slot;

        slot.setSize(sf::Vector2f(hotbarBg.getSize().y, hotbarBg.getSize().y));
        slot.setPosition(hotbarBg.getPosition().x + (hotbarBg.getSize().y * i), hotbarBg.getPosition().y);
        slot.setFillColor(sf::Color::Transparent);

        hotbarSlots.push_back(slot);
    }

    hotbarItems = std::make_unique<Item *[]>(hotbarSize);

    for (unsigned short i = 0; i < hotbarSize; ++i)
    {
        hotbarItems[i] = nullptr;
    }
}

InventoryGUI::InventoryGUI(Inventory &inventory, sf::VideoMode &vm) : inventory(inventory), vm(vm)
{
    initHotbar();

    hotbarItems[0] = inventory.at(0);
}

InventoryGUI::~InventoryGUI()
{
}

void InventoryGUI::update(const float &dt, sf::Vector2f &mouse_pos)
{
    for (unsigned short i = 0; i < hotbarSize; ++i)
    {
        if (hotbarItems[i] != nullptr)
        {
            hotbarSlots[i].setTexture(hotbarItems[i]->getTexture());
            hotbarSlots[i].setTextureRect(hotbarItems[i]->getIconIntRect());
            hotbarSlots[i].setFillColor(sf::Color::White);
        }
        else
        {
            hotbarSlots[i].setTexture(nullptr);
            hotbarSlots[i].setFillColor(sf::Color::Transparent);
        }
    }
}

void InventoryGUI::render(sf::RenderTarget &target)
{
    target.draw(hotbarBg);

    for (auto &slot : hotbarSlots)
        target.draw(slot);

    for (unsigned short i = 0; i < hotbarSize; ++i)
    {
        hotbarFrame.setPosition(hotbarBg.getPosition().x + (hotbarBg.getSize().y * i), hotbarBg.getPosition().y);
        target.draw(hotbarFrame);
    }

    target.draw(hotbarSelector);
}
