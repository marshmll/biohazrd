#ifndef COMPONENTS_MOVEMENTCOMPONENT_H_
#define COMPONENTS_MOVEMENTCOMPONENT_H_

#include <iostream>
#include <ctime>
#include <cmath>
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

enum states
{
	IDLE = 0,
	MOVING
};

enum directions
{
	DOWN = 0,
	UP,
	RIGHT,
	LEFT
};

class MovementComponent
{
private:
	/* VARIABLES */
	sf::Sprite &sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

	short unsigned state;
	short unsigned direction;

	/* INITIALIZERS */

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	/* FUNCTIONS */
	void update(const float &dt);
	void move(const float dir_x, const float dir_y, const float &dt);

	/* ACESSORS */
	const sf::Vector2f& getVelocity() const;
	const float& getMaxVelocity() const;
	const short unsigned& getCurrentState() const;
	const std::string getDirection() const;

};

#endif /* COMPONENTS_MOVEMENTCOMPONENT_H_ */
