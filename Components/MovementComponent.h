#ifndef COMPONENTS_MOVEMENTCOMPONENT_H_
#define COMPONENTS_MOVEMENTCOMPONENT_H_

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <stack>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class MovementComponent
{
private:
	sf::Sprite &sprite;

	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f deceleration;

	float maxVelocity;

	/* INITIALIZERS */

public:
	MovementComponent(sf::Sprite &sprite, float maxVelocity);
	virtual ~MovementComponent();

	/* FUNCTIONS */
	void update(const float &dt);
	void move(const float dir_x, const float dir_y, const float &dt);

	/* ACESSORS */
	const sf::Vector2f& getVelocity() const;
};

#endif /* COMPONENTS_MOVEMENTCOMPONENT_H_ */
