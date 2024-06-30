#ifndef AIFOLLOW_H_
#define AIFOLLOW_H_

#include "AIBehavior.h"
#include "Entity.h"

class AIFollowBehavior : public AIBehavior
{
private:
    /* VARIABLES ================================================================================================= */

    Entity &targetEntity;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    AIFollowBehavior(Entity &self, Entity &target_entity);

    virtual ~AIFollowBehavior();

    /* FUNCTIONS ================================================================================================= */

    void update(const float &dt);

    /* ACCESSORS ================================================================================================= */

    /* MODIFIERS ================================================================================================= */
};

#endif /* AIFOLLOW_H_ */