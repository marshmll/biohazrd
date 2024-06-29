#include "stdafx.h"
#include "AIFollow.h"

/* INITIALIZERS ================================================================================================== */

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

AIFollow::AIFollow(Entity &self, Entity &player)
    : AIBehavior(self), player(player)
{
}

AIFollow::~AIFollow()
{
}

/* FUNCTIONS ===================================================================================================== */

void AIFollow::update(const float &dt)
{
    Vector2f move_vec;

    move_vec.x = player.getPosition().x - self.getPosition().x;
    move_vec.y = player.getPosition().y - self.getPosition().y;

    float vec_len = sqrt(pow(move_vec.x, 2) + pow(move_vec.y, 2));

    move_vec /= vec_len;

    self.move(move_vec.x, move_vec.y, dt);
}

/* ACCESSORS ===================================================================================================== */

/* MODIFIERS ===================================================================================================== */
