#ifndef AIFOLLOW_H_
#define AIFOLLOW_H_

#include "AIBehavior.h"

class Entity;

class AIFollow : public AIBehavior
{
private:
    /* VARIABLES ================================================================================================= */

    Entity &player;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    AIFollow(Entity &self, Entity &player);

    virtual ~AIFollow();

    /* FUNCTIONS ================================================================================================= */

    void update(const float &dt);

    /* ACCESSORS ================================================================================================= */

    /* MODIFIERS ================================================================================================= */
};

#endif /* AIFOLLOW_H_ */