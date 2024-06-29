#ifndef STATE_H_
#define STATE_H_

#include "Logger.h"
#include "IniParser.h"
#include "GraphicsSettings.h"
#include "Player.h"
#include "GUI.h"

class State; // Needed to typedef StateData.

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
    Logger *logger;
    stack<State *> *states;
    GraphicsSettings *gfxSettings;
    RenderWindow *window;
    map<string, Keyboard::Key> *acceptedKeys;
    float gridSize;
} StateData;

class State
{
private:
protected:
    /* VARIABLES ================================================================================================= */

    StateData *data;
    stack<State *> *states;

    GraphicsSettings *gfxSettings;
    RenderWindow *window;
    VideoMode &vm;

    map<string, Keyboard::Key> *acceptedKeys;
    map<string, Keyboard::Key> keybinds;

    float gridSize;

    string currentPath;

    bool isPaused;
    bool quitState;

    Clock keyTimer;
    Int32 keyTimerMax;

    Clock mouseTimer;
    Int32 mouseTimerMax;

    Vector2i mousePosScreen;
    Vector2i mousePosWindow;
    Vector2f mousePosView;
    Vector2i mousePosGrid;

    /* ASSETS ==================================================================================================== */

    map<string, Texture> textures;

    /* INITIALIZERS ============================================================================================== */

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

    /* PURE VIRTUAL FUNCTIONS ==================================================================================== */

    virtual void update(const float &dt) = 0;
    virtual void render(RenderTarget &target) = 0;
    virtual void updateInput(const float &dt) = 0;

    /* DEFINED VIRTUAL FUNCTIONS ================================================================================= */

    /**
     * @brief Update mouse postiions relative to:
     * @note -> Screen
     * @note -> Window
     * @note -> View
     *
     * @return void
     */
    virtual void updateMousePositions(View *view = nullptr);

    /**
     * @brief Sets quit current state to true.
     * The quit states triggers the state to exit
     * in Engine.cpp [Engine::update()]
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

    /* ACCESSORS ================================================================================================= */

    /**
     * @brief Returns this->quitTheState value.
     * The quit boolean value determines if the state
     * needs to quit or not.
     *
     * @return bool
     */

    const bool &hasAskedToQuit() const;

    /**
     * @brief Checks if the elapsed time by the timer is greater
     * or equal to the timer max. If so, checks if the key is pressed.
     * If the key is not pressed, return false. Otherwise, resets the
     * timer and returns true.
     * @param is_key_pressed The return value of an Keyboard::isKeyPressed
     * call.
     *
     * @return const bool
     */
    const bool hasElapsedKeyTimeMax(const bool is_key_pressed);

    /**
     * @brief Checks if the elapsed time by the timer is greater
     * or equal to the timer max. If so, checks if the mouse button is
     * pressed. If the mouse button is not pressed, return false. Otherwise,
     * resets the timer and returns true.
     * @param is_mouse_pressed The return value of an Mouse::isButtonPressed
     * call.
     *
     * @return const bool
     */
    const bool hasElapsedMouseTimeMax(const bool is_mouse_pressed);
};

#endif /* STATE_H_ */
