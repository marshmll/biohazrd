#ifndef TABMENU_H_
#define TABMENU_H_

#include "Tabs.h"

class PlayerTabMenu
{
private:
    /* VARIABLES ================================================================================================= */

    sf::VideoMode &vm;
    sf::Font &font;
    Player &player;

    sf::Clock keyTimer;
    sf::Int32 keyTimerMax;

    /* TABS */

    CharacterTab *charTab;

    /* INITIALIZERS ============================================================================================== */

    void initVariables();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    PlayerTabMenu(sf::VideoMode &vm, sf::Font &font, Player &player);

    virtual ~PlayerTabMenu();

    /* FUNCTIONS ================================================================================================= */

    void update(const float &dt);

    void render(sf::RenderTarget &target);

    const bool hasElapsedKeyTimeMax();

    /* ACCESSORS ================================================================================================= */

    /* MODIFIERS ================================================================================================= */
};

#endif /* TABMENU_H_ */