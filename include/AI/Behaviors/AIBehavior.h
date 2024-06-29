#ifndef AIBEHAVIOR_H_
#define AIBEHAVIOR_H_

class Entity;

class AIBehavior
{
protected:
    Entity &self;

public:
    AIBehavior(Entity &self);

    virtual ~AIBehavior();

    virtual void update(const float &dt) = 0;
};

#endif /* AIBEHAVIOR_H_ */