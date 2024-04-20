#ifndef ENTITIES_PLAYER_H_
#define ENTITIES_PLAYER_H_

#include "Entity.h"

class Player: public Entity
{
private:
	/* VARIABLES */

	/* INITIALIZERS */
	void initVariables();
	void initComponents();

public:
	Player(float x, float y, sf::Texture &texture);
	virtual ~Player();

	/* FUNCTIONS */
};

#endif /* ENTITIES_PLAYER_H_ */
