#ifndef EDITORMODE_H_
#define EDITORMODE_H_

#include "State.h"
#include "TileMap.h"
#include "GUI.h"

class State;
class Tile;
class TileMap;

typedef struct
{
    std::map<std::string, sf::Keyboard::Key> *keybinds;
    sf::View *editorCamera;
    sf::Font *font;
    float *keytime;
    float *keytimeMax;
    float *mousetime;
    float *mousetimeMax;
    sf::Vector2i *mousePosScreen;
    sf::Vector2i *mousePosWindow;
    sf::Vector2f *mousePosView;
    sf::Vector2i *mousePosGrid;     
}
EditorStateData;

class EditorMode
{
private:

protected:
    /* VARIABLES */

    StateData *data;
    EditorStateData *editorData;
    TileMap *tileMap;

public:
    /* CONSTRUCTOR AND DESTRUCTOR */

    EditorMode(StateData *data, EditorStateData *editor_data);

    virtual ~EditorMode();

     /* FUNCTIONS */

    /**
     * @brief Updates the EditorMode.
     * @note -> Checks for updates in the user input.
     * @note -> Update buttons.
     *
     * @return void
     */
    virtual void update(const float &dt) = 0;

    /**
     * @brief Renders the editor mode.
     * @note -> Draw background
     * @note -> Render buttons.
     *
     * @return void
     */
    virtual void render(sf::RenderTarget &target) = 0;

    /**
     * @brief Updates the user input.
     *
     * @return void
     */
    virtual void updateInput(const float &dt) = 0;

    /**
     * @brief Updates the GUI elements.
     *
     * @return void
     */
    virtual void updateGUI(const float &dt) = 0;

    /**
     * @brief Renders the GUI elements into a target
     *
     * @return void
     */
    virtual void renderGUI(sf::RenderTarget &target) = 0;
};

#endif /* EDITORMODE_H_ */
