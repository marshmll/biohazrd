#ifndef COLLISIONEDITORMODE_H_
#define COLLISIONEDITORMODE_H_

#include "EditorMode.h"

class EditorMode;

class CollisionEditorMode : public EditorMode
{
private:
    /* VARIABLES ================================================================================= */

    sf::Text cursorText;
    sf::RectangleShape sidebar;
    sf::RectangleShape selectorRect;

    sf::IntRect textureRect;
    
    /* INITIALIZERS ============================================================================== */

    void initVariables();

    void initGUI();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================= */

    CollisionEditorMode(StateData *data, EditorStateData *editor_data);
    
    virtual ~CollisionEditorMode();

    /* FUNCTIONS ================================================================================== */

    void update(const float &dt);

    void render(sf::RenderTarget &target);

    void updateInput(const float &dt);

    void updateGUI(const float &dt);

    void renderGUI(sf::RenderTarget &target);

    /* ACCESSORS ===================================================================================== */

    const bool hasCompletedKeytimeCicle();

    const bool hasCompletedMousetimeCicle(const sf::Mouse::Button mouse_btn);
};

#endif /* COLLISIONEDITORMODE_H_ */