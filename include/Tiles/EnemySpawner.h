#ifndef ENEMYSPAWNER_H_
#define ENEMYSPAWNER_H_

#include "Tile.h"

class Tile;

class EnemySpawner : public Tile
{
private:
    /* VARIABLES =============================================================================================== */

    int enemyType;
    int enemyAmount;
    int enemyTimeToSpawn;
    int enemyMaxDistance;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================*/

    EnemySpawner(
        const unsigned grid_x, const unsigned grid_y, const float grid_size_f,
        const sf::Texture &texture, const sf::IntRect texture_rect,
        const int enemy_type, const int enemy_amount, const int enemy_time_to_spawn, const int enemy_max_distance);

    virtual ~EnemySpawner();

    /* FUNCTIONS ================================================================================================= */

    void update();

    void render(sf::RenderTarget &target, sf::Shader *shader = nullptr, const sf::Vector2f light_pos = sf::Vector2f());

    /* ACCESSORS ================================================================================================== */

    const std::string getPropertiesAsString() const;
};

#endif /* ENEMYSPAWNER_H_ */