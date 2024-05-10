#ifndef ENTITIES_ENTITY_H_
#define ENTITIES_ENTITY_H_

#include "../Components/HitboxComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/AnimationComponent.h"

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
	virtual void render(sf::RenderTarget &target);
	virtual void move(const float x, const float y, const float &dt);

	/* ACCESSORS */
	virtual const sf::Vector2f& getPosition();
	virtual const sf::Vector2f getCenteredPosition();

	/* MODIFIERS */
	virtual void setPosition(const float x, const float y);

};

#endif /* ENTITIES_ENTITY_H_ */
