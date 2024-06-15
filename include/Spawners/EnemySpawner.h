#ifndef ENEMYSPAWNER_H_
#define ENEMYSPAWNER_H_

class EnemySpawner
{
private:
    /* VARIABLES */

    sf::RectangleShape shape;
    sf::Vector2i gridPosition;
    float gridSize;
    int type;
    int amount;
    int spawnTimer;
    int maxDistance;

public:
    EnemySpawner(const sf::Vector2i grid_position, const float grid_size, const int type,
                 const int amount, const int spawn_timer, const int max_distance);

    virtual ~EnemySpawner();

    void update(const float &dt);
    void render(sf::RenderTarget &target);
};

#endif /* ENEMYSPAWNER_H_ */