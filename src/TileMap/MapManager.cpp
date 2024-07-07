#include "stdafx.h"
#include "MapManager.h"

MapManager::MapManager(sf::VideoMode &vm, sf::Font &font)
    : vm(vm), font(font)
{
    background.setSize(sf::Vector2f(vm.width, vm.height));
    background.setPosition(0.f, 0.f);
    background.setFillColor(sf::Color(10, 10, 10, 180));

    container.setSize(sf::Vector2f(vm.width / 3.f, vm.height - gui::p2pY(vm, 5.f)));
    container.setPosition(vm.width / 2.f - container.getSize().x / 2,
                          gui::p2pY(vm, 2.5f));
    container.setFillColor(sf::Color(200, 200, 200, 200));

    mapNameInput = new gui::TextInput(container.getPosition().x, container.getPosition().y,
                                      200.f, 30.f,
                                      sf::Color(255, 255, 255, 255), sf::Color::Black,
                                      gui::calc_char_size(vm, 130), font, "TESTE");
}

MapManager::~MapManager()
{
    delete mapNameInput;

    for (auto &it : buttons)
        delete it.second;
}

void MapManager::update(const sf::Vector2f &mouse_pos)
{
    mapNameInput->update();

    for (auto &it : buttons)
        it.second->update(mouse_pos);
}

void MapManager::render(sf::RenderTarget &target)
{
    target.draw(background);
    target.draw(container);

    mapNameInput->render(target);

    for (auto &it : buttons)
        it.second->render(target);
}
