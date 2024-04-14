#ifndef STATE_H_
#define STATE_H_

#include <iostream>
#include <ctime>
#include <cstdlib>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class State
{
private:
	std::vector<sf::Texture> textures;

public:
	State();
	virtual ~State();

	virtual void update() = 0;
	virtual void render() = 0;
};

#endif /* STATE_H_ */
