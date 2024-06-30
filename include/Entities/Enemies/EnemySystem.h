#ifndef ENEMYSYSTEM_H_
#define ENEMYSYSTEM_H_

#include "EnemySpawnerTile.h"
#include "GreenSlime.h"

enum EnemyType
{
    GREEN_SLIME = 0
};

class EnemySystem
{
private:
    /* VARIABLES =============================================================================================== */

    std::vector<Enemy *> &activeEnemies;
    std::map<std::string, sf::Texture> &textures;
    Entity &player;

public:
    /* CONSTRUCTOR AND DESTRUCTOR =============================================================================== */

    EnemySystem(std::vector<Enemy *> &active_enemies, std::map<std::string, sf::Texture> &textures, Entity &player);

    virtual ~EnemySystem();

    /* FUNCTIONS ================================================================================================ */

    void update(const float &dt);

    void render(sf::RenderTarget &target);

    /**
     * @brief Creates an enemy of a given type on x and y coordinates.
     *
     * @return void
     */
    void createEnemy(const EnemyType type, const float x, const float y, EnemySpawnerTile& enemy_spawner_tile);

    /**
     * @brief Creates an enemy of a given type on a position.
     *
     * @return void
     */
    void createEnemy(const EnemyType type, const sf::Vector2f position, EnemySpawnerTile& enemy_spawner_tile);

    /**
     * @brief Deletes an enemy by its index.
     * @attention Deletes the data AND erases the pointer from the vector.
     *
     * @return void
     */
    void deleteEnemy(const size_t index);

    /**
     * @brief Deletes an enemy by its pointer.
     * @attention Deletes the data AND erases the pointer from the vector.
     *
     * @return void
     */
    void deleteEnemy(Enemy *enemy);

    /* ACCESSORS ================================================================================================ */

    /* MODIFIERS ================================================================================================ */
};

#endif /* ENEMYSYSTEM_H_ */