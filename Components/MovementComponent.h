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

enum movement_states
{
	IDLE_DOWN = 0,
	IDLE_UP,
	IDLE_RIGHT,
	IDLE_LEFT,
	MV_DOWN,
	MV_UP,
	MV_RIGHT,
	MV_LEFT,
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

	short unsigned currentState;

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
	const short unsigned getCurrentState() const;

};

#endif /* COMPONENTS_MOVEMENTCOMPONENT_H_ */
