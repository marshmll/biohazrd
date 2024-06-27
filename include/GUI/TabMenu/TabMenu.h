#ifndef TABMENU_H_
#define TABMENU_H_

#include "Tabs.h"

class TabMenu
{
private:
    /* VARIABLES ================================================================================================= */

    sf::VideoMode &vm;
    sf::Font &font;

    std::vector<Tab *> tabs;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    TabMenu(sf::VideoMode &vm, sf::Font &font);

    virtual ~TabMenu();

    /* FUNCTIONS ================================================================================================= */

    void update(const float &dt);

    void render(sf::RenderTarget &target);

    void addTab(Tab *tab);

    /* ACCESSORS ================================================================================================= */

    /* MODIFIERS ================================================================================================= */
};

#endif /* TABMENU_H_ */