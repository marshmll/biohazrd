#ifndef MAINMENUSTATE_H_
#define MAINMENUSTATE_H_

#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "WorldSelectionState.h"

class MainMenuState : public State
{
private:
    /* VARIABLES ================================================================================================= */

    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button *> buttons;

    /* INITIALIZERS ============================================================================================== */

    /**
     * @brief Initializes MainMenuState variables
     *
     * @return void
     */
    void initVariables();

    /**
     * @brief Loads font from file.
     *
     * @return void
     */
    void initFonts();

    /**
     * @brief Binds the accepted keys to its respective functionality.
     * It might differ from state to state, each state can have
     * its own function binding to a key.
     *
     * @return void
     */
    void initKeybinds();

    /**
     * @brief Initializes all the GUI of the MainMenuState.
     *
     * @return void
     */
    void initGUI();

    void initSounds();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    /**
     * @brief Calls the parent constructor for State.
     * @note -> Initializes variables
     * @note -> Initializes background
     * @note -> Initializes fonts
     * @note -> Initializes keybinds
     * @note -> Initializes buttons
     */
    MainMenuState(StateData *data);

    /**
     * @brief Frees all the memory allocated for the buttons.
     */
    virtual ~MainMenuState();

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
     * @brief Updates the input.
     * @note -> Updates mouse positions.
     *
     * @return void
     */
    void updateInput(const float &dt);

    void updateSounds();

    /**
     * @brief Updates the GUI.
     * @note Iterates over all buttons and update their states based on
     * mouse click and position.
     * @note Executes a functionality for each button.
     *
     * @return void
     */
    void updateGUI();

    /**
     * @brief Renders the GUI into a target.
     * @note Iterates over all buttons and renders them into a target.
     *
     * @return void
     */
    void renderGUI(sf::RenderTarget &target);

    /**
     * @brief Resets the entire GUI.
     * @note -> Deletes all the elements and erase pointers
     * to gui elements
     * @note -> Resets background.
     * @note -> Re-initializes GUI.
     */
    void resetGUI();
};

#endif /* MAINMENUSTATE_H_ */
