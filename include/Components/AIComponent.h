#ifndef AICOMPONENT_H_
#define AICOMPONENT_H_

#include "Entity.h"

class AIComponent
{
private:
    /* VARIABLES ================================================================================================= */

    Entity &self;
    Entity *targetEntity;

    AIFollowBehavior *follow;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    AIComponent(Entity &self, Entity *target_entity = nullptr);

    virtual ~AIComponent();

    /* FUNCTIONS ================================================================================================= */

    void addFollowBehavior();

    /* ACCESSORS ================================================================================================= */

    /* MODIFIERS ================================================================================================= */
};

#endif /* AICOMPONENT_H_ */