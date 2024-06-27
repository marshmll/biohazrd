#include "stdafx.h"
#include "AIComponent.h"

/* INITIALIZERS ============================================================================================== */

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

AIComponent::AIComponent(Entity &self, Entity *target_entity)
    : self(self), targetEntity(target_entity)
{
}

AIComponent::~AIComponent()
{
}

/* FUNCTIONS ================================================================================================= */

void AIComponent::update(const float &dt)
{
}

/* ACCESSORS ================================================================================================= */

/* MODIFIERS ================================================================================================= */
