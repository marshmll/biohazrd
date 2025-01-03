#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "State.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "TextTagSystem.h"
#include "Video.h"

class GameState : public State
{
private:
    /* VARIABLES ================================================================================================= */

    Video *loader;
    bool isGameLoaded;

    sf::View playerCamera;
    sf::Vector2i playerCameraPosGrid;

    sf::RenderTexture renderBuffer;
    sf::Sprite renderSprite;

    bool showDebugStats;
    sf::Text debugText;

    sf::Shader coreShader;
    sf::Vector3f ambientLight;

    gui::PauseMenu *pauseMenu;

    Player *player;
    PlayerGUI *playerGUI;

    sf::Font font;

    std::vector<Enemy *> activeEnemies;
    EnemySystem *enemySystem;

    TextTagSystem *textTagSystem;

    TileMap *tileMap;

    /* INITIALIZERS ============================================================================================== */

    /**
     * @brief Initializes general game variables.
     *
     * @return void.
     */
    void initVariables();

    /**
     * @brief Initializes the buffered render.
     * The buffered render utilizes a render texture and a
     * sprite for render optimizing.
     *
     * @return void
     */
    void initBufferedRender();

    /**
     * @brief Initializes player camera, setting size and center.
     *
     * @return void
     */
    void initPlayerCamera();

    /**
     * @brief Binds the accepted keys to its respective functionality.
     * It might differ from state to state, each state can have
     * its own binding to a key.
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
     * @brief Initializes the loading screen video.
     * 
     * @return void
     */
    void initLoadingScreen();

    /**
     * @brief Initializes text.
     *
     * @return void
     */
    void initText();

    /**
     * @brief nitializes textures used in the game.
     *
     * @return void
     */
    void initTextures();

    /**
     * @brief Initializes the game shaders.
     *
     * @return void
     */
    void initShaders();

    /**
     * @brief Initializes pause menu.
     *
     * @return void
     */
    void initPauseMenu();

    /**
     * @brief Initializes player(s).
     *
     * @return void
     */
    void initPlayers();

    /**
     * @brief Initializes the player gui.
     *
     * @return void
     */
    void initPlayerGUI();

    /**
     * @brief Initializes a tilemap for the gamestate.
     *
     * @return void
     */
    void initTileMap(const std::string map_path);

    /**
     * @brief Initializes the enemy system.
     *
     * @return void
     */
    void initEnemySystem();

    /**
     * @brief Initializes the enemy system.
     *
     * @return void
     */
    void initTextTagSystem();

    void initializerThread(const std::string &map_path);

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    /**
     * @brief Calls the parent constructor State(window, acceptedKeys)
     * @note -> Initializes the keybinds for the state.
     * @note -> Initializes fonts
     * @note -> Initializes textures
     * @note -> Initializes pause menu
     * @note -> Initializes player(s)
     */
    GameState(StateData *data, const std::string map_path);

    /**
     * @brief Frees all allocated memory
     */
    virtual ~GameState();

    /* FUNCTIONS ================================================================================================= */

    /**
     * @brief Updates the GameState.
     * @note-> Checks for updates in the state input.
     * @note-> Checks for updates in the player input, if NOT paused.
     * @note-> Checks for updates in the player input, if NOT paused.
     * @note-> Updates player, if NOT paused.
     * @note-> Updates pause menu if PAUSED.
     * @note-> Uptades pause menu buttons if PAUSED.
     *
     * @return void
     */
    void update(const float &dt);

    /**
     * @brief Renders GameState into a render texture buffer.
     * @note -> Display the buffered texture into the target.
     *
     * @return void
     */
    void render(sf::RenderTarget &target);

    /**
     * @brief Renders everything into a RenderTexture buffer.
     * @note-> Clear the buffer.
     * @note-> Render into the buffer
     * @note-> Display the buffer
     * @note-> Set renderSprite texture to buffer.
     *
     * @return void
     */
    void renderToBuffer();

    /**
     * @brief Updates inputs related to the state.
     *
     * @return void
     */
    void updateInput(const float &dt);

    /**
     * @brief Updates all game players.
     *
     * @return void
     */
    void updatePlayers(const float &dt);

    /**
     * @brief Updates the player input.
     *
     * @note Checks for keybinds and executes its respective
     * action.
     *
     * @return void
     */
    void updatePlayerInput(const float &dt);

    /**
     * @brief Updates the player's GUI.
     *
     * @return void
     */
    void updatePlayerGUI(const float &dt, sf::Vector2f mouse_pos);

    /**
     * @brief Updates all game enemies.
     *
     * @return void
     */
    void updateEnemiesAndCombat(const float &dt);

    /**
     * @brief Updates the combat between player and an enemy.
     * @param dt The game delta time
     * @param enemy A pointer to an enemy
     * @param index The enemy's index in the activeEnemies vector.
     *
     * @return void
     */
    void updateCombat(const float &dt, Enemy *enemy);

    /**
     * @brief Updates tilemap and collisions.
     *
     * @return void
     */
    void updateTileMap(const float &dt);

    void updateShaders();

    void updateDebugStats(const float &dt);

    /**
     * @brief Updates button interactions from the pause menu.
     * Executes its functionality.
     *
     * @return void
     */
    void updatePauseMenuButtons();

    /**
     * @brief Updates the player camera, keeps player on
     * the center of the screen.
     *
     * @return void
     */
    void updatePlayerCamera(const float &dt);

    void debugStatsToggle();
};

#endif /* GAMESTATE_H_ */
