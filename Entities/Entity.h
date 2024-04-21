#ifndef ENTITIES_ENTITY_H_
#define ENTITIES_ENTITY_H_

#include "../Components/MovementComponent.h"
#include "../Components/AnimationComponent.h"

class Entity
{
private:
	/* INITIALIZERS */
	void initVariables();

protected:
	sf::Sprite sprite;

	MovementComponent *movementComponent;
	AnimationComponent *animationComponent;

public:
	Entity();
	virtual ~Entity();

	/* COMPONENT FUNCTIONS */
	void setTexture(sf::Texture &texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture &texture_sheet);

	/* FUNCTIONS */
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget *target = nullptr);

	virtual void setPosition(const float x, const float y);
	virtual void move(const float x, const float y, const float &dt);
};

#endif /* ENTITIES_ENTITY_H_ */
