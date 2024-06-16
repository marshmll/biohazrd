#ifndef DEFAULTEDITORMODE_H_
#define DEFAULTEDITORMODE_H_

#include "State.h"
#include "EditorMode.h"

class State;
class EditorMode;
class Tile;
class TileMap;

class DefaultEditorMode : public EditorMode
{
private:
    TileMap *tileMap;

    sf::Text cursorText;

    sf::RectangleShape sidebar;

    sf::RectangleShape selectorRect;

    sf::IntRect textureRect;
    gui::TextureSelector *textureSelector;

    bool collision;
    short type;
    unsigned layer;

    /* INITIALIZERS */

    void initVariables();

    void initGUI();   

public:
    /* CONSTRUCTOR AND DESTRUCTOR */

    DefaultEditorMode(StateData *data, EditorStateData *editor_data, TileMap *tile_map);

    virtual ~DefaultEditorMode();

    /* FUNCTIONS */

    void update(const float &dt);

    void render(sf::RenderTarget &target);

    void updateInput(const float &dt);

    void updateGUI(const float &dt);

    void renderGUI(sf::RenderTarget &target);

    /* ACCESSORS */

    const bool hasCompletedKeytimeCicle();
    
    const bool hasCompletedMousetimeCicle(const sf::Mouse::Button mouseBtn);

    const std::string getTypeName() const;
};

#endif /* DEFAULTEDITORMODE_H_ */
