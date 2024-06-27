#ifndef EDITORMODE_H_
#define EDITORMODE_H_

#include "State.h"
#include "TileMap.h"
#include "GUI.h"

typedef struct EditorStateData
{
    std::map<std::string, sf::Keyboard::Key> *keybinds;
    TileMap *tileMap;
    sf::View *editorCamera;
    sf::Font *font;
    sf::Clock *keyTimer;
    sf::Int32 *keyTimerMax;
    sf::Clock *mouseTimer;
    sf::Int32 *mouseTimerMax;
    sf::Vector2i *mousePosScreen;
    sf::Vector2i *mousePosWindow;
    sf::Vector2f *mousePosView;
    sf::Vector2i *mousePosGrid;
} EditorStateData;

class EditorMode
{
protected:
    /* VARIABLES ================================================================================================= */

    StateData *data;

    EditorStateData *editorData;

    sf::Text modeIndicatorText;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    EditorMode(StateData *data, EditorStateData *editor_data, std::string mode_name);

    virtual ~EditorMode();

    /* FUNCTIONS ================================================================================================= */

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

    const bool hasElapsedKeyTimeMax();
    
    const bool hasElapsedMouseTimeMax();
};

#endif /* EDITORMODE_H_ */
