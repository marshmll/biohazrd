#ifndef STATE_H_
#define STATE_H_

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

class State
{
private:
	sf::RenderWindow *window;
	std::vector<sf::Texture> textures;
	bool quit;

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	State(sf::RenderWindow *window);
	virtual ~State();

	/* PURE VIRTUAL FUNCTIONS */
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget *target = nullptr) = 0;

	virtual void updateKeybinds(const float &dt) = 0;

	virtual void endState() = 0;

	/* DEFINED VIRTUAL FUNCTIONS */
	virtual void checkForQuit();

	/* ACESSORS */
	const bool& requestedToQuit() const;
};

#endif /* STATE_H_ */
