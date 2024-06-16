#ifndef ENEMYEDITORMODE_H_
#define ENEMYEDITORMODE_H_

#include "EditorMode.h"
#include "EnemySpawner.h"

class EditorMode;
class Tile;
class TileMap;
class EnemySpawner;

class EnemyEditorMode : public EditorMode
{
private:
    /* VARIABLES ================================================================================= */

    TileMap *tileMap;
    
    sf::Text cursorText;
    sf::RectangleShape sidebar;
    sf::RectangleShape selectorRect;

    /* INITIALIZERS ============================================================================== */

    void initVariables();

    void initGUI();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================ */

    EnemyEditorMode(StateData *data, EditorStateData *editor_data, TileMap *tile_map);

    virtual ~EnemyEditorMode();

    /* FUNCTIONS ================================================================================== */

    void update(const float &dt);

    void render(sf::RenderTarget &target);

    void updateInput(const float &dt);

    void updateGUI(const float &dt);

    void renderGUI(sf::RenderTarget &target);

    /* ACCESSORS ===================================================================================== */

    const bool hasCompletedKeytimeCicle();

    const bool hasCompletedMousetimeCicle(const sf::Mouse::Button mouseBtn);
};
#endif /* ENEMYEDITORMODE_H_ */