#ifndef TAB_H_
#define TAB_H_

#include "GUI.h"

class Tab
{
private:
protected:
    /* VARIABLES ================================================================================================= */

    VideoMode &vm;
    Font &font;

    RectangleShape bg;

    bool hidden;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    Tab(const float width, const float height,
        const Color bg_color, const Color text_color,
        VideoMode &vm, Font &font);

    virtual ~Tab();

    /* FUNCTIONS ================================================================================================= */

    virtual void update(const float &dt) = 0;

    virtual void render(RenderTarget &target) = 0;

    /* ACCESSORS ================================================================================================= */

    const bool &isHidden() const;

    const bool isOpen() const;

    /* MODIFIERS ================================================================================================= */

    void hideToggle();

    void show();

    void hide();
};

#endif /* TAB_H_ */