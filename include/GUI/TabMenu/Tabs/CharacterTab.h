#ifndef CHARACTERTAB_H
#define CHARACTERTAB_H

#include "Tab.h"
#include "Player.h"

class CharacterTab : public Tab
{
private:
    /* VARIABLES ================================================================================================= */

    Player &player;

    Text text;

    /* INITIALIZERS ============================================================================================== */

    void initText();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    CharacterTab(const float width, const float height,
                 VideoMode &vm, Font &font, Player &player);

    virtual ~CharacterTab();

    /* FUNCTIONS ================================================================================================= */

    void update(const float &dt);

    void render(RenderTarget &target);

    /* ACCESSORS ================================================================================================= */

    /* MODIFIERS ================================================================================================= */
};

#endif /* CHARACTERTAB_H */