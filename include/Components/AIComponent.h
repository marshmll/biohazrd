#ifndef AICOMPONENT_H_
#define AICOMPONENT_H_

#include "AIBehaviors.h"
#include "Entity.h"

class AIComponent
{
private:
    /* VARIABLES ================================================================================================= */

    Entity &self;
    Entity *targetEntity;

    /* INITIALIZERS ============================================================================================== */

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    AIComponent(Entity &self, Entity *target_entity = nullptr);

    virtual ~AIComponent();

    /* FUNCTIONS ================================================================================================= */

    void update(const float &dt);

    /* ACCESSORS ================================================================================================= */

    /* MODIFIERS ================================================================================================= */
};

#endif /* AICOMPONENT_H_ */