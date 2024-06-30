#include "stdafx.h"
#include "AIFollowBehavior.h"

/* INITIALIZERS ================================================================================================== */

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

AIFollowBehavior::AIFollowBehavior(Entity &self, Entity &target_entity)
    : AIBehavior(self), targetEntity(target_entity)
{
}

AIFollowBehavior::~AIFollowBehavior()
{
}

/* FUNCTIONS ===================================================================================================== */

void AIFollowBehavior::update(const float &dt)
{
    sf::Vector2f move_vec;

    move_vec.x = targetEntity.getPosition().x - self.getPosition().x;
    move_vec.y = targetEntity.getPosition().y - self.getPosition().y;

    float vec_len = sqrt(pow(move_vec.x, 2) + pow(move_vec.y, 2));

    move_vec /= vec_len;

    self.move(move_vec.x, move_vec.y, dt);
}

/* ACCESSORS ===================================================================================================== */

/* MODIFIERS ===================================================================================================== */
