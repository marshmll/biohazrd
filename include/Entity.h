#ifndef ENTITY_H_
#define ENTITY_H_

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	/* INITIALIZERS */
	void initVariables();

protected:
	/* ENTITY SPRITE */
	sf::Sprite sprite;

	/* ENTITY FUNCTIONAL COMPONENTS */
	HitboxComponent *hitboxComponent;
	MovementComponent *movementComponent;
	AnimationComponent *animationComponent;

public:
	Entity();
	virtual ~Entity();

	/* COMPONENT FUNCTIONS */
	void setTexture(sf::Texture &texture);

	void createHitboxComponent(
			const float offset_x, const float offset_y,
			const float width, const float height);

	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);

	void createAnimationComponent(sf::Texture &texture_sheet);

	/* FUNCTIONS */
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget &target) = 0;
	virtual void move(const float x, const float y, const float &dt);

	/* ACCESSORS */
	virtual const sf::Vector2f& getPosition();
	virtual const sf::Vector2f getCenteredPosition();
	virtual const sf::Vector2f getSize();

	virtual const bool hasCollided(sf::FloatRect &frect);

	/* MODIFIERS */
	virtual void setPosition(const sf::Vector2f& position);

};

#endif /* ENTITY_H_ */
