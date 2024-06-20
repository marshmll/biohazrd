#ifndef ENEMYSPAWNERTILE_H_
#define ENEMYSPAWNERTILE_H_

#include "Tile.h"

class Tile;

class EnemySpawnerTile : public Tile
{
private:
    /* VARIABLES =============================================================================================== */

    int enemyType;
    int enemyAmount;
    int enemyTimeToSpawn;
    int enemyMaxDistance;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================*/

    EnemySpawnerTile(
        const unsigned grid_x, const unsigned grid_y, const float grid_size_f,
        const sf::Texture &texture, const sf::IntRect texture_rect,
        const int enemy_type, const int enemy_amount,
        const int enemy_time_to_spawn, const int enemy_max_distance);

    virtual ~EnemySpawnerTile();

    /* FUNCTIONS ================================================================================================= */

    void update();

    void render(sf::RenderTarget &target, sf::Shader *shader = nullptr, const sf::Vector2f light_pos = sf::Vector2f());

    /* ACCESSORS ================================================================================================== */

    const std::string getPropertiesAsString() const;
};

#endif /* ENEMYSPAWNERTILE_H_ */