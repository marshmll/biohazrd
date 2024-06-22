#ifndef SETTINGSSTATE_H_
#define SETTINGSSTATE_H_

#include "State.h"
#include "MainMenuState.h"

class MainMenuState;

class SettingsState : public State
{
private:
    /* VARIABLES */

    MainMenuState *mainMenuState;

    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button *> buttons;

    std::map<std::string, gui::DropDownList *> dropDownLists;

    sf::Text optionsText;

    std::vector<sf::VideoMode> videoModes;

    /* INITIALIZERS */

    /**
     * @brief Initializes SettingsState variables
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
     * @brief Initializes all GUI elements.
     *
     * @return void
     */
    void initGUI();

    /**
     * @brief Resets the entire GUI.
     * @note -> Deletes all the elements and erase pointers
     * to gui elements
     * @note -> Resets background.
     * @note -> Re-initializes GUI.
     */
    void resetGUI();

public:
    /* CONSTRUCTOR AND DESTRUCTOR */

    /**
     * @brief Calls the parent constructor for State.
     * @note -> Initializes variables
     * @note -> Initializes background
     * @note -> Initializes fonts
     * @note -> Initializes keybinds
     * @note -> Initializes GUI
     * @note -> Initializes text
     */
    SettingsState(StateData *data, MainMenuState *main_menu_state);

    /**
     * @brief Frees all the memory allocated for the buttons.
     */
    virtual ~SettingsState();

    /* FUNCTIONS */

    /**
     * @brief Updates the Settings State.
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
     * @brief Updates the mouse input.
     * -> Updates mouse positions.
     *
     * @return void
     */
    void updateInput(const float &dt);

    /**
     * @brief Updates all GUI elements.
     *
     * @return void
     */
    void updateGUI(const float &dt);

    /**
     * @brief Renders all GUI elements.
     *
     * @return void
     */
    void renderGUI(sf::RenderTarget &target);

    /* ACCESSORS */
};

#endif /* SETTINGSSTATE_H_ */
