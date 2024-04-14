#ifndef ENTITIES_ENTITY_H_
#define ENTITIES_ENTITY_H_

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

class Entity
{
private:

protected:
	sf::RectangleShape shape;
	float movementSpeed;

public:
	Entity();
	virtual ~Entity();

	/* FUNCTIONS */
	virtual void update(const float &dt);
	virtual void render(sf::RenderTarget *target = nullptr);

	virtual void move(const float &dt, const float x, const float y);
};

#endif /* ENTITIES_ENTITY_H_ */
