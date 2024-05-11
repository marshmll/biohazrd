#ifndef COMPONENTS_HITBOXCOMPONENT_H_
#define COMPONENTS_HITBOXCOMPONENT_H_

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
	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getSize() const;
	const bool intersects(sf::FloatRect &frect) const;

	/* MODIFIERS */
	void setPosition(const sf::Vector2f &position);
};

#endif /* COMPONENTS_HITBOXCOMPONENT_H_ */
