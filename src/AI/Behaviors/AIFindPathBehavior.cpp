#include "stdafx.h"
#include "AIFindPathBehavior.h"

void AIFindPathBehavior::clearNodes()
{
    for (auto node : nodes)
        delete node;

    nodes.clear();
}

AIFindPathBehavior::AIFindPathBehavior(Entity &self, Entity &target_entity, TileMap &tilemap,
                                       const float max_distance)

    : AIBehavior(self), targetEntity(target_entity),
      tileMap(tilemap), maxDistance(max_distance)
{
}

AIFindPathBehavior::~AIFindPathBehavior()
{
    clearNodes();
}

void AIFindPathBehavior::update(const float &dt)
{
    float distance = self.getRangeDistanceFrom(targetEntity);

    std::cout << distance << "\n";
}

void AIFindPathBehavior::updateNodes()
{
    if (nodes.front()->pos != self.getCenteredPosition() &&
        nodes.back()->pos != targetEntity.getCenteredPosition())
    {
        clearNodes();

        nodes.push_back(new Node(nullptr, self.getCenteredPosition(), 0, 0, true));
    }
}
