#include "stdafx.h"
#include "TabMenu.h"

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

TabMenu::TabMenu(sf::VideoMode &vm, sf::Font &font)
    : vm(vm), font(font)
{
}

TabMenu::~TabMenu()
{
    for (auto tab : tabs)
        delete tab;
}

/* FUNCTIONS ===================================================================================================== */

void TabMenu::update(const float &dt)
{
    for (auto tab : tabs)
        tab->update(dt);
}

void TabMenu::render(sf::RenderTarget &target)
{
    for (auto tab : tabs)
        tab->render(target);
}

void TabMenu::addTab(Tab *tab)
{
    tabs.push_back(tab);
}

/* ACCESSORS ===================================================================================================== */

/* MODIFIERS ===================================================================================================== */
