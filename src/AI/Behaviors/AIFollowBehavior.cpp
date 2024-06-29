#include "stdafx.h"
#include "AIFollowBehavior.h"

AIFollowBehavior::AIFollowBehavior(Entity &self, Entity &target_entity)
    : AIBehavior(self), targetEntity(target_entity)
{
}

AIFollowBehavior::~AIFollowBehavior()
{
}

void AIFollowBehavior::update(const float &dt)
{
    Vector2f vec(targetEntity.getCenteredPosition().x - self.getCenteredPosition().x,
                 targetEntity.getCenteredPosition().y - self.getCenteredPosition().y);

    float vec_len = sqrt(pow(vec.x, 2) + pow(vec.y, 2));

    vec /= vec_len;

    self.move(vec.x, vec.y, dt);
}
