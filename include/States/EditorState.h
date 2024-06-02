#ifndef EDITORSTATE_H_
#define EDITORSTATE_H_

#include "State.h"
#include "TileMap.h"

class State;
class TileMap;

class EditorState : public State
{
private:
	/* VARIABLES */

	sf::View editorCamera;
	sf::Vector2i editorCameraPosGrid;

	sf::Font font;
	sf::Text cursorText;

	gui::PauseMenu *pauseMenu;
	std::map<std::string, gui::Button *> buttons;

	TileMap *tileMap;

	sf::RectangleShape sidebar;
	sf::RectangleShape selectorRect;
	gui::TextureSelector *textureSelector;

	sf::IntRect textureRect;

	bool collision;
	short type;
	float cameraSpeed;
	unsigned layer;

	/* INITIALIZERS */

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
	 * @brief Initializes the texts for the state.
	 *
	 * @return void
	 */
	void initText();

	/**
	 * @brief Initializes pause menu.
	 *
	 * @return void
	 */
	void initPauseMenu();

	/**
	 * @brief Initializes all the buttons of the EditorState.
	 *
	 * @return void
	 */
	void initButtons();

	/**
	 * @brief Initializes the tilemap for the editor.
	 *
	 * @return void
	 */
	void initTileMap();

	/**
	 * @brief Initializes the GUI elements.
	 * @note -> initializes selector rect.
	 *
	 * @return void
	 */
	void initGUI();

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
	 * @brief Updates the input specific for the editor
	 *
	 * @return void
	 */
	void updateEditorInput(const float &dt);

	/**
	 * @brief Updates the editor camera.
	 * @note Moves the camera.
	 * @note Update editorCameraPosGrid.
	 * 
	 * @return void
	 */
	void updateEditorCamera(const float &dt);

	/**
	 * @brief Iterates over all buttons and update their states based on
	 * mouse click and position.
	 *
	 * @return void
	 */
	void updateButtons();

	/**
	 * @brief Updates pause menu buttons
	 *
	 * @return void
	 */
	void updatePauseMenuButtons();

	/**
	 * @brief Updates the GUI elements.
	 *
	 * @return void
	 */
	void updateGUI(const float &dt);

	/**
	 * @brief Iterates over all buttons and renders them into a target.
	 *
	 * @return void
	 */
	void renderButtons(sf::RenderTarget &target);

	/**
	 * @brief Renders the GUI elements into a target
	 *
	 * @return void
	 */

	void renderGUI(sf::RenderTarget &target);

	/**
	 * @brief Returns the tile type's name.
	 * 
	 * @return const std::string
	 */
	const std::string getTypeName() const;
};

#endif /* EDITORSTATE_H_ */
