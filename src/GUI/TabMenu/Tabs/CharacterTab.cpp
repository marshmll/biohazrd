#include "stdafx.h"
#include "CharacterTab.h"

/* INITIALIZERS ================================================================================================== */

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

CharacterTab::CharacterTab(const float width, const float height,
                           const sf::Color bg_color, const sf::Color text_color,
                           sf::VideoMode &vm, sf::Font &font, Player &player)

    : Tab(width, height, bg_color, text_color, vm, font), player(player)
{
}

CharacterTab::~CharacterTab()
{
}

/* FUNCTIONS ====================================================================================================== */

void CharacterTab::update(const float &dt)
{
    if (!hidden)
    {
    }
}

void CharacterTab::render(sf::RenderTarget &target)
{
    if (!hidden)
    {
        target.draw(bg);
    }
}
