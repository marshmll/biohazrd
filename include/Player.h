#ifndef PLAYER_H_
#define PLAYER_H_

#include "Entity.h"

class Player: public Entity
{
private:
	/* VARIABLES */
	bool isJumping;
	std::string currentJumpAnimationName;

	/* INITIALIZERS */
	void initVariables();
	void initAnimations();

public:
	Player(float x, float y, sf::Texture &texture_sheet);
	virtual ~Player();

	/* FUNCTIONS */
	void update(const float &dt);
	void render(sf::RenderTarget &target);

	void updateAnimation(const float &dt);
	void updateJump(const float &dt);
};

#endif /* PLAYER_H_ */
