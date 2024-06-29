#ifndef AIFOLLOWBEHAVIOR_H_
#define AIFOLLOWBEHAVIOR_H_

#include "AIBehavior.h"
#include "Entity.h"

class AIFollowBehavior : public AIBehavior
{
private:
    Entity &targetEntity;

public:
    AIFollowBehavior(Entity &self, Entity &target_entity);

    virtual ~AIFollowBehavior();

    void update(const float &dt);
};

#endif /* AIFOLLOWBEHAVIOR_H_ */