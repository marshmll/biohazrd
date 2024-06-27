#ifndef CHARACTERTAB_H
#define CHARACTERTAB_H

#include "Tab.h"
#include "Player.h"

class CharacterTab : public Tab
{
private:
    /* VARIABLES ================================================================================================= */

    Player &player;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    CharacterTab(const float width, const float height,
                 const sf::Color bg_color, const sf::Color text_color,
                 sf::VideoMode &vm, sf::Font &font, Player &player);

    virtual ~CharacterTab();

    /* FUNCTIONS ================================================================================================= */

    void update(const float &dt);

    void render(sf::RenderTarget &target);

    /* ACCESSORS ================================================================================================= */

    /* MODIFIERS ================================================================================================= */
};

#endif /* CHARACTERTAB_H */