#ifndef AIFINDPATHBEHAVIOR_H_
#define AIFINDPATHBEHAVIOR_H_

#include "AIBehavior.h"
#include "TileMap.h"
#include "Entity.h"

class AIFindPathBehavior : public AIBehavior
{
private:
    class Node
    {
    public:
        Node *parentNode;

        sf::Vector2f pos; // Node coords

        float gCost; // Distance from start node
        float hCost; // Distance from end node
        float fCost; // Sum of both.

        bool closed;
        bool transposable;

        Node(Node *parent_node, const sf::Vector2f &pos,
             const float g_cost, const float h_cost,
             const bool closed = false, const bool transposable = true)
        {
            this->parentNode = parent_node;

            this->pos = pos;

            this->gCost = g_cost,
            this->hCost = h_cost,
            this->fCost = g_cost + h_cost;

            this->closed = closed;
            this->transposable = transposable;
        }

        ~Node() {}
    };

    Entity &targetEntity;
    TileMap &tileMap;

    float maxDistance;

    std::vector<Node *> nodes;

    void clearNodes();

public:
    AIFindPathBehavior(Entity &self, Entity &target_entity, TileMap &tilemap,
                       const float max_distance);

    virtual ~AIFindPathBehavior();

    void update(const float &dt);

    void updateNodes();
};

#endif /* AIFINDPATHBEHAVIOR_H_ */