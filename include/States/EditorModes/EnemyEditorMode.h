#ifndef ENEMYEDITORMODE_H_
#define ENEMYEDITORMODE_H_

#include "EditorMode.h"
#include "EnemySpawnerTile.h"

class EnemyEditorMode : public EditorMode
{
private:
    /* VARIABLES ================================================================================================= */

    sf::Text cursorText;
    sf::RectangleShape sidebar;
    sf::RectangleShape selectorRect;

    sf::IntRect textureRect;

    short enemyType;
    short enemyAmount;
    short enemyTimeToSpawn;
    short enemyMaxDistance;
    short enemySpawnAreaSize;

    /* INITIALIZERS ============================================================================================== */

    void initVariables();

    void initGUI();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    EnemyEditorMode(StateData *data, EditorStateData *editor_data);

    virtual ~EnemyEditorMode();

    /* FUNCTIONS ================================================================================================= */

    /**
     * @brief Updates the EditorMode.
     * @note -> Checks for updates in the user input.
     * @note -> Update buttons.
     *
     * @return void
     */
    void update(const float &dt, const sf::Event &event);

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
    void updateGUI(const float &dt, const sf::Event &event);

    /**
     * @brief Renders the GUI elements into a target.
     *
     * @return void
     */
    void renderGUI(sf::RenderTarget &target);
};
#endif /* ENEMYEDITORMODE_H_ */
