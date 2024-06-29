#ifndef TABMENU_H_
#define TABMENU_H_

#include "Tabs.h"

class PlayerTabMenu
{
private:
    /* VARIABLES ================================================================================================= */

    VideoMode &vm;
    Font &font;
    Player &player;

    Clock keyTimer;
    Int32 keyTimerMax;

    /* TABS */

    map<TabType, Tab *> tabs;

    /* INITIALIZERS ============================================================================================== */

    void initVariables();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    PlayerTabMenu(VideoMode &vm, Font &font, Player &player);

    virtual ~PlayerTabMenu();

    /* FUNCTIONS ================================================================================================= */

    void update(const float &dt);

    void render(RenderTarget &target);

    const bool hasElapsedKeyTimeMax();

    /* ACCESSORS ================================================================================================= */

    const bool hasTabsOpen();

    /* MODIFIERS ================================================================================================= */

    void toggleTab(TabType tab_type);
};

#endif /* TABMENU_H_ */