#ifndef TAB_H_
#define TAB_H_

#include "GUI.h"

class Tab
{
private:
protected:
    /* VARIABLES ================================================================================================= */

    sf::VideoMode &vm;
    sf::Font &font;

    sf::RectangleShape bg;

    bool hidden;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    Tab(const float width, const float height,
        const sf::Color bg_color, const sf::Color text_color,
        sf::VideoMode &vm, sf::Font &font);

    virtual ~Tab();

    /* FUNCTIONS ================================================================================================= */

    virtual void update(const float &dt) = 0;

    virtual void render(sf::RenderTarget &target) = 0;

    /* ACCESSORS ================================================================================================= */

    const bool &isHidden() const;

    /* MODIFIERS ================================================================================================= */

    void hideToggle();

    void show();

    void hide();
};

#endif /* TAB_H_ */