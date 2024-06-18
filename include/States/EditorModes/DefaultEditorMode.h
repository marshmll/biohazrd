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
    /* VARIABLES ============================================================================================ */

    sf::Text cursorText;
    sf::RectangleShape sidebar;
    sf::RectangleShape selectorRect;
    sf::IntRect textureRect;

    gui::TextureSelector *textureSelector;

    bool collision;
    
    float collBoxWidth;
    float collBoxHeight;
    float collBoxOffsetX;
    float collBoxOffsetY;

    short type;
    unsigned layer;

    /* INITIALIZERS =========================================================================================== */

    void initVariables();

    void initGUI();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ============================================================================= */

    DefaultEditorMode(StateData *data, EditorStateData *editor_data);

    virtual ~DefaultEditorMode();

    /* FUNCTIONS =============================================================================================== */

    /**
     * @brief Updates the EditorMode.
     * @note -> Checks for updates in the user input.
     * @note -> Update buttons.
     *
     * @return void
     */
    void update(const float &dt);

    /**
     * @brief Renders the editor mode.
     * @note -> Draw background
     * @note -> Render buttons.
     *
     * @return void
     */
    void render(sf::RenderTarget &target);

    /**
     * @brief Updates the user input.
     *
     * @return void
     */
    void updateInput(const float &dt);

    /**
     * @brief Updates the GUI elements.
     *
     * @return void
     */
    void updateGUI(const float &dt);

    /**
     * @brief Renders the GUI elements into a target.
     *
     * @return void
     */
    void renderGUI(sf::RenderTarget &target);

    /* ACCESSORS =============================================================================================== */

    /**
     * @brief Returns if an determined amount of time has passed
     * after the last key press.
     * @note -> Resets times back to 0.f
     *
     *
     * @return const bool
     */
    const bool hasCompletedKeytimeCicle();

    /**
     * @brief Returns if an determined amount of time has passed
     * after the last mouse button press of a specified button.
     * @param mouse_btn The mouse button to be checked.
     *
     *  @note -> Resets times back to 0.f
     *
     *
     * @return const bool
     */
    const bool hasCompletedMousetimeCicle(const sf::Mouse::Button mouse_btn);

    /**
     * @brief Returns the type name of a tile as a string.
     *
     * @return std::string
     */
    const std::string getTypeName() const;
};

#endif /* DEFAULTEDITORMODE_H_ */
