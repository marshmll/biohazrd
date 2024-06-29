#include "stdafx.h"
#include "CharacterTab.h"

/* INITIALIZERS ================================================================================================== */

void CharacterTab::initText()
{
    text.setFont(font);
    text.setString(player.formatStringToCharTab());
    text.setCharacterSize(gui::calc_char_size(vm, 130));
    text.setPosition(bg.getPosition().x + gui::p2pX(vm, 3.f), bg.getPosition().y + gui::p2pY(vm, 3.f));
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

CharacterTab::CharacterTab(const float width, const float height,
                           VideoMode &vm, Font &font, Player &player)

    : Tab(width, height, Color(5, 5, 5, 240), Color::White, vm, font), player(player)
{
    initText();
}

CharacterTab::~CharacterTab()
{
}

/* FUNCTIONS ====================================================================================================== */

void CharacterTab::update(const float &dt)
{
    if (!hidden)
    {
        text.setString(player.formatStringToCharTab());
    }
}

void CharacterTab::render(RenderTarget &target)
{
    if (!hidden)
    {
        target.draw(bg);
        target.draw(text);
    }
}
