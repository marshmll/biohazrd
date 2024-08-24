#include "stdafx.h"
#include "InventoryGUI.h"

void InventoryGUI::initHotbar()
{
    hotbarBg.setSize(sf::Vector2f(gui::p2pY(vm, 8.f) * 9.f, gui::p2pY(vm, 8.f)));
    hotbarBg.setPosition(vm.width / 2.f - hotbarBg.getSize().x / 2.f, 10.f);
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
}

InventoryGUI::InventoryGUI(Inventory &inventory, sf::VideoMode &vm) : inventory(inventory), vm(vm)
{
    initHotbar();
}

InventoryGUI::~InventoryGUI()
{
}

void InventoryGUI::update(const float &dt, sf::Vector2f &mouse_pos)
{
}

void InventoryGUI::render(sf::RenderTarget &target)
{
    target.draw(hotbarBg);

    for (int i = 0; i < 9; ++i)
    {
        hotbarFrame.setPosition(hotbarBg.getPosition().x + (hotbarBg.getSize().y * i), hotbarBg.getPosition().y);
        target.draw(hotbarFrame);
    }

    target.draw(hotbarSelector);
}
