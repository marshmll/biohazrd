#include "stdafx.h"
#include "AIComponent.h"

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

AIComponent::AIComponent(Entity &self, Entity *target_entity)
    : self(self), targetEntity(target_entity)
{
    follow = nullptr;
}

AIComponent::~AIComponent()
{
    delete follow;
}

/* FUNCTIONS ===================================================================================================== */

void AIComponent::addFollowBehavior()
{
    if (targetEntity)
        follow = new AIFollowBehavior(self, *targetEntity);
    else
        ErrorHandler::throwErr("AICOMPONENT::ADDFOLLOWBEHAVIOR::ERR_NULL_ENTITY");
}
