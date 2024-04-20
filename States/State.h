#ifndef STATE_H_
#define STATE_H_

#include "../Entities/Player.h"

class State
{
private:

protected:
	/* VARIABLES */
	std::stack<State*> *states;

	sf::RenderWindow *window;

	std::map<std::string, sf::Keyboard::Key> *acceptedKeys;

	std::map<std::string, sf::Keyboard::Key> keybinds;

	std::string currentPath;

	bool quitState;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	/* ASSETS */
	std::map<std::string, sf::Texture> textures;

	/* FUNCTIONS */
	virtual void initKeybinds() = 0;

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	State(sf::RenderWindow *window, std::map<std::string, sf::Keyboard::Key> *acceptedKeys, std::stack<State*> *states);
	virtual ~State();

	/* PURE VIRTUAL FUNCTIONS */
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget *target = nullptr) = 0;

	virtual void updateInput(const float &dt) = 0;

	/* DEFINED VIRTUAL FUNCTIONS */
	virtual void updateMousePositions();
	virtual void quit();

	/* ACESSORS */
	const bool& hasAskedToQuit() const;
};

#endif /* STATE_H_ */
