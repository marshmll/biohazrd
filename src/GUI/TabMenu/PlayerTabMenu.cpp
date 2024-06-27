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

    charTab = new CharacterTab(gui::p2pX(vm, 40.f), vm.height,
                               sf::Color(20, 20, 20, 200), sf::Color::White,
                               vm, font, player);
}

PlayerTabMenu::~PlayerTabMenu()
{
    delete charTab;
}

/* FUNCTIONS ===================================================================================================== */

void PlayerTabMenu::update(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && hasElapsedKeyTimeMax())
        charTab->hideToggle();

    charTab->update(dt);
}

void PlayerTabMenu::render(sf::RenderTarget &target)
{
    charTab->render(target);
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

/* MODIFIERS ===================================================================================================== */
