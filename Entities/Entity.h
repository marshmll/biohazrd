#ifndef ENTITIES_ENTITY_H_
#define ENTITIES_ENTITY_H_

#include "../Components/MovementComponent.h"

class Entity
{
private:
	/* INITIALIZERS */
	void initVariables();

protected:
	sf::Sprite sprite;

	MovementComponent *movementComponent;

public:
	Entity();
	virtual ~Entity();

	/* COMPONENT FUNCTIONS */
	void setTexture(sf::Texture &texture);
	void createMovementComponent(const float maxVelocity);

	/* FUNCTIONS */
	virtual void update(const float &dt);
	virtual void render(sf::RenderTarget *target = nullptr);

	virtual void setPosition(const float x, const float y);
	virtual void move(const float x, const float y, const float &dt);
};

#endif /* ENTITIES_ENTITY_H_ */
