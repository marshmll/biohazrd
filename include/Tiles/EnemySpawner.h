#ifndef ENEMYSPAWNER_H_
#define ENEMYSPAWNER_H_

#include "Tile.h"

class Tile;

class EnemySpawner : public Tile
{
private:
    /* VARIABLES */
    int enemyType;
    int enemyAmount;
    int enemyTimeToSpawn;
    int enemyMaxDistance;

public:
    EnemySpawner(
        const int enemy_type, const int enemy_amount, const int enemy_time_to_spawn, const int enemy_max_distance,
        const unsigned grid_x, const unsigned grid_y, const float grid_size_f,
        const sf::Texture &texture, const sf::IntRect texture_rect);

    virtual ~EnemySpawner();

    void update();
    void render(sf::RenderTarget &target, sf::Shader *shader = nullptr, const sf::Vector2f light_pos = sf::Vector2f());
};

#endif /* ENEMYSPAWNER_H_ */