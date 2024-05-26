#ifndef STATE_H_
#define STATE_H_

#include "Player.h"
#include "GUI.h"
#include "GraphicsSettings.h"

class State;
class Player;
class GraphicsSettings;

/**
 * @brief This struct packs all important data from a state.
 * @note Saves:
 * @note Pointer to States stack
 * @note Pointer to graphics settings
 * @note Pointer to the render window
 * @note Pointer to the accepted keys map
 * @note Grid Size F.
 */
typedef struct
{
	std::stack<State *> *states;
	GraphicsSettings *gfxSettings;
	sf::RenderWindow *window;
	std::map<std::string, sf::Keyboard::Key> *acceptedKeys;
	float gridSize;
} StateData;

class State
{
private:
protected:
	/* VARIABLES */

	StateData *data;
	std::stack<State *> *states;

	GraphicsSettings *gfxSettings;
	sf::RenderWindow *window;

	std::map<std::string, sf::Keyboard::Key> *acceptedKeys;
	std::map<std::string, sf::Keyboard::Key> keybinds;

	float gridSize;

	std::string currentPath;

	bool quitState;
	bool isPaused;

	float keytime;
	float keytimeMax;

	float mousetime;
	float mousetimeMax;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;

	/* ASSETS */

	std::map<std::string, sf::Texture> textures;

	/* FUNCTIONS */

	virtual void initKeybinds() = 0;

public:
	/* CONSTRUCTOR AND DESTRUCTOR */

	/**
	 * @brief Constructs a State instance.
	 * @note -> Sets a pointer to the states stack.
	 * @note -> Sets this->window to window pointer
	 * @note -> Sets the accepted keys
	 * @note -> Sets current directory path.
	 * @note -> Sets this->quitState to false
	 * @note -> Sets is paused to false
	 * @note -> Sets keytime and keytimeMax
	 * @note -> Sets mousetime and mousetimeMax
	 */
	State(StateData *data);

	virtual ~State();

	/* AUXILIARY FUNCTIONS */

	/**
	 * @brief Converts a screen width percentage to a pixel
	 * coordinate dynamically.
	 *
	 * @param percent Percentage relative to screen width
	 *
	 * @return const float;
	 */
	const float p2pX(const float percent);

	/**
	 * @brief Converts a screen height percentage to a pixel
	 * coordinate dynamically.
	 *
	 * @param percent Percentage relative to screen height
	 *
	 * @return const float;
	 */
	const float p2pY(const float percent);

	/* PURE VIRTUAL FUNCTIONS */

	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget &target) = 0;
	virtual void updateInput(const float &dt) = 0;

	/* DEFINED VIRTUAL FUNCTIONS */

	/**
	 * @brief Update mouse postiions relative to:
	 * @note -> Screen
	 * @note -> Window
	 * @note -> View
	 *
	 * @return void
	 */
	virtual void updateMousePositions(sf::View *view = nullptr);

	/**
	 * @brief Updates the keytime.
	 * The keytime is used for debounce key presses
	 * at a single press.
	 *
	 * @return void
	 */
	virtual void updateKeytime(const float &dt);

	/**
	 * @brief Updates the mousetime.
	 * The mousetime is used for debounce mouse clicks
	 * at a single click.
	 *
	 * @return void
	 */
	virtual void updateMousetime(const float &dt);

	/**
	 * @brief Sets quit current state to true.
	 * The quit states triggers the state to exit
	 * in Game.cpp [Game::update()]
	 *
	 * @return void
	 */
	virtual void quit();

	/**
	 * @brief Pauses/unpauses the state.
	 * Pauses if unpaused, unpauses if paused.
	 *
	 * @return void
	 */
	virtual void pauseToggle();

	/**
	 * @brief Pauses the state.
	 * @note -> Sets isPaused to true.
	 *
	 * @return void
	 */
	virtual void pause();

	/**
	 * @brief Resumes the state.
	 * @note -> Sets isPaused to false.
	 *
	 * @return void
	 */
	virtual void resume();

	/* ACCESSORS */

	/**
	 * @brief Returns this->quitTheState value.
	 * The quit boolean value determines if the state
	 * needs to quit or not.
	 *
	 * @return bool
	 */

	const bool &hasAskedToQuit() const;

	/**
	 * @brief Returns if a keytime cicle has completed.
	 * A keytime cicle means that a defined amount of
	 * time has passed after a key was pressed.
	 * @note-> Restarts keytime after verification.
	 *
	 * @return const bool
	 */
	const bool hasCompletedKeytimeCicle();

	/**
	 * @brief Returns if a mousetime cicle has completed.
	 * A mousetime cicle means that a defined amount of
	 * time has passed after a mouse button was pressed.
	 * @note -> Restarts mousetime after verification.
	 *
	 * @return const bool
	 */
	const bool hasCompletedMousetimeCicle(sf::Mouse::Button mouseBtn);
};

#endif /* STATE_H_ */
