#ifndef ENTITIES_PLAYER_H_
#define ENTITIES_PLAYER_H_

#include "Entity.h"

class Player: public Entity
{
private:
	/* VARIABLES */

	/* INITIALIZERS */
	void initVariables();
	void initAnimations();

public:
	Player(float x, float y, sf::Texture &texture_sheet);
	virtual ~Player();

	/* FUNCTIONS */
	virtual void update(const float &dt);
};

#endif /* ENTITIES_PLAYER_H_ */
