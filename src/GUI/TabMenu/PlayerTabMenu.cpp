#include "stdafx.h"
#include "PlayerTabMenu.h"

/* INITIALIZERS ===================================================================================================== */

void PlayerTabMenu::initVariables()
{
    keyTimerMax = sf::Int32(500);
    keyTimer.restart();
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

PlayerTabMenu::PlayerTabMenu(sf::VideoMode &vm, sf::Font &font, Player &player)
    : vm(vm), font(font), player(player)
{
    initVariables();

    tabs[CHARACTER_TAB] = new CharacterTab(gui::p2pX(vm, 40.f), vm.height,
                                      vm, font, player);
}

PlayerTabMenu::~PlayerTabMenu()
{
    for (auto &it : tabs)
        delete it.second;
}

/* FUNCTIONS ===================================================================================================== */

void PlayerTabMenu::update(const float &dt)
{
    for (auto &it : tabs)
        it.second->update(dt);
}

void PlayerTabMenu::render(sf::RenderTarget &target)
{
    for (auto &it : tabs)
        it.second->render(target);
}

const bool PlayerTabMenu::hasElapsedKeyTimeMax()
{
    if (keyTimer.getElapsedTime().asMilliseconds() >= keyTimerMax)
    {
        keyTimer.restart();
        return true;
    }

    return false;
}

/* ACCESSORS ===================================================================================================== */

const bool PlayerTabMenu::hasTabsOpen()
{
    for (auto &it : tabs)
    {
        if (it.second->isOpen())
            return true;
    }

    return false;
}

/* MODIFIERS ===================================================================================================== */

void PlayerTabMenu::toggleTab(TabType tab_type)
{
    tabs[tab_type]->hideToggle();
}
