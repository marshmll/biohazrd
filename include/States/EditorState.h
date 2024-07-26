#ifndef EDITORSTATE_H_
#define EDITORSTATE_H_

#include "EditorModes.h"

enum EditorModes
{
    DEFAULT_MODE = 0,
    ENEMY_MODE
};

class EditorState : public State
{
private:
    /* VARIABLES ================================================================================================= */

    EditorStateData editorStateData;

    TileMap *tileMap;

    sf::View editorCamera;
    sf::Vector2i editorCameraPosGrid;
    float cameraSpeed;

    sf::Font font;

    gui::PauseMenu *pauseMenu;

    std::map<std::string, gui::Button *> buttons;

    std::map<EditorModes, EditorMode *> modes;

    EditorModes activeEditorMode;

    /* INITIALIZERS ============================================================================================== */

    /**
     * @brief Initializes MainMenuState variables
     *
     * @return void
     */
    void initVariables();

    /**
     * @brief Initializes the editor camera (view).
     *
     * @return void
     */
    void initEditorCamera();

    /**
     * @brief Binds the accepted keys to its respective functionality.
     * It might differ from state to state, each state can have
     * its own function binding to a key.
     *
     * @return void
     */
    void initKeybinds();

    /**
     * @brief Loads font from file.
     *
     * @return void
     */
    void initFonts();

    /**
     * @brief Initializes pause menu.
     *
     * @return void
     */
    void initPauseMenu();

    /**
     * @brief Initializes the tilemap for the editor.
     *
     * @return void
     */
    void initTileMap();

    /**
     * @brief Initializes the tilemap for the editor.
     *
     * @attention LOADS TILEMAP
     *
     * @return void
     */
    void initTileMap(const std::string map_file_path);

    /**
     * @brief Initializes the GUI elements.
     *
     * @return void
     */
    void initGUI();

    /**
     * @brief Initializes the Editor State Data.
     *
     * @return void
     */
    void initEditorStateData();

    /**
     * @brief Initializes the editor modes.
     *
     * @return void
     */
    void initModes();

public:
    /* CONSTRUCTOR AND DESTRUCTOR */

    /**
     * @brief Calls the parent constructor for State.
     * @note -> Initializes variables
     * @note -> Initializes fonts
     * @note -> Initializes keybinds
     * @note -> Initializes buttons
     */
    EditorState(StateData *data);

    /**
     * @brief Calls the parent constructor for State.
     * @attention LOADS TILEMAP
     * @note -> Initializes variables
     * @note -> Initializes fonts
     * @note -> Initializes keybinds
     * @note -> Initializes buttons
     */
    EditorState(StateData *data, const std::string map_file_path);

    /**
     * @brief Frees all the memory allocated for the buttons.
     */
    virtual ~EditorState();

    /* FUNCTIONS */

    /**
     * @brief Updates the MainMenuState.
     * @note -> Checks for updates in the user input.
     * @note -> Update buttons.
     *
     * @return void
     */
    void update(const float &dt);

    /**
     * @brief Renders the main menu.
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
     * @note -> Iterates over all buttons and update their states based on
     * mouse click and position.
     *
     * @return void
     */
    void updateGUI(const float &dt);

    /**
     * @brief Updates the editor camera.
     * @note Moves the camera.
     * @note Update editorCameraPosGrid.
     *
     * @return void
     */
    void updateEditorCamera(const float &dt);

    /**
     * @brief Updates pause menu interactions.
     * @note -> Checks for executing functions for buttons presses.
     *
     * @return void
     */
    void updatePauseMenuInteraction();

    /**
     * @brief Updates the active editor mode.
     *
     * @return void
     */
    void updateModes(const float &dt);

    /**
     * @brief Renders the GUI elements into a target
     *
     * @return void
     */
    void renderGUI(sf::RenderTarget &target);

    /**
     * @brief Renders the active editor mode.
     *
     * @return void
     */
    void renderModes(sf::RenderTarget &target);
};

#endif /* EDITORSTATE_H_ */
