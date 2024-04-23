#ifndef COMPONENTS_HITBOXCOMPONENT_H_
#define COMPONENTS_HITBOXCOMPONENT_H_

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

class HitboxComponent
{
private:
	/* VARIABLES */
	sf::Sprite &sprite;
	sf::RectangleShape hitbox;

	float offsetX;
	float offsetY;

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	HitboxComponent(sf::Sprite &sprite,
			float offset_x, float offset_y,
			float width, float height);
	virtual ~HitboxComponent();

	/* FUNCTIONS */
	void update();
	void render(sf::RenderTarget &target);

	/* ACCESSORS */
	const bool hasIntersected(sf::FloatRect &frect) const;
};

#endif /* COMPONENTS_HITBOXCOMPONENT_H_ */
