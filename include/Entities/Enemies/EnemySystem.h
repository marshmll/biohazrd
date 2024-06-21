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

public:
    /* CONSTRUCTOR AND DESTRUCTOR =============================================================================== */

    EnemySystem(std::vector<Enemy *> &active_enemies, std::map<std::string, sf::Texture> &textures);

    virtual ~EnemySystem();

    /* FUNCTIONS ================================================================================================ */

    void update(const float &dt);

    void render(sf::RenderTarget &target);

    void createEnemy(const EnemyType type, const float x, const float y);

    /* ACCESSORS ================================================================================================ */

    /* MODIFIERS ================================================================================================ */
};

#endif /* ENEMYSYSTEM_H_ */