#ifndef ENEMYEDITORMODE_H_
#define ENEMYEDITORMODE_H_

#include "EditorMode.h"
#include "EnemySpawnerTile.h"

class EditorMode;
class Tile;
class TileMap;
class EnemySpawnerTile;

class EnemyEditorMode : public EditorMode
{
private:
    /* VARIABLES ================================================================================= */
    
    sf::Text cursorText;
    sf::RectangleShape sidebar;
    sf::RectangleShape selectorRect;
    
    sf::IntRect textureRect;

    short type;
    short amount;
    short timeToSpawn;
    int maxDistance;

    /* INITIALIZERS ============================================================================== */

    void initVariables();

    void initGUI();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================ */

    EnemyEditorMode(StateData *data, EditorStateData *editor_data);

    virtual ~EnemyEditorMode();

    /* FUNCTIONS ================================================================================== */

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

    /* ACCESSORS ===================================================================================== */

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
};
#endif /* ENEMYEDITORMODE_H_ */