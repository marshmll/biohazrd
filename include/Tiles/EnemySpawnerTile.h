#ifndef ENEMYSPAWNERTILE_H_
#define ENEMYSPAWNERTILE_H_

#include "Tile.h"

class EnemySpawnerTile : public Tile
{
private:
    /* VARIABLES ================================================================================================= */

    sf::Clock spawnTimer;

    short enemyType;
    short enemyAmount;
    short enemyCounter;
    short enemyTimeToSpawn; // As seconds
    short enemyMaxDistance;
    short enemySpawnAreaSize;

    bool spawned;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    EnemySpawnerTile(
        const unsigned grid_x, const unsigned grid_y, const float grid_size_f,
        const sf::Texture &texture, const sf::IntRect texture_rect,
        const short enemy_type, const short enemy_amount,
        const short enemy_time_to_spawn, const short enemy_max_distance,
        const short enemy_spawn_area_size);

    virtual ~EnemySpawnerTile();

    /* FUNCTIONS ================================================================================================= */

    void update();

    /**
     * @brief Renders the tile into a target.
     * @note If a shader pointer is passed in, it will be used for rendering.
     *
     * @param target A render target reference.
     * @param shader A shader pointer. (optional)
     * @param light_pos The lighting position (needed if using shaders)
     *
     * @return void
     */
    void render(sf::RenderTarget &target, sf::Shader *shader = nullptr, const sf::Vector2f light_pos = sf::Vector2f());

    const bool canSpawn(const sf::Vector2f &player_pos);

    const bool hasElapsedSpawnTime();

    const bool isPlayerInsideSpawnArea(const sf::Vector2f &player_pos);

    const bool hasSpawnedAllEnemies() const;

    void increaseEnemyCounter();

    void decreaseEnemyCounter();

    /* ACCESSORS ================================================================================================= */

    const short &getEnemyCounter() const;

    /**
     * @brief Returns the tile properties as a std::string.
     * @note Returns:
     * @note -> Type
     * @note -> Texture rectangle left
     * @note -> Texture rectangle top
     * @note -> Enemy type
     * @note -> Enemy amount
     * @note -> Enemy time to spawn
     * @note -> Enemy max distance
     *
     * @return const std::string
     */
    const std::string getPropertiesAsString() const;

    /* MODIFIERS ================================================================================================= */
};

#endif /* ENEMYSPAWNERTILE_H_ */
