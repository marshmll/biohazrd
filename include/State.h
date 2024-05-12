#ifndef STATE_H_
#define STATE_H_

#include "Player.h"
#include "GUI.h"
#include "GraphicsSettings.h"

class State;
class Player;
class GraphicsSettings;

/* This struct packs all important data from a state. */
typedef struct
{
	std::stack<State*> *states;
	GraphicsSettings *gfxSettings;
	sf::RenderWindow *window;
	std::map<std::string, sf::Keyboard::Key> *acceptedKeys;
	float gridSize;
}
StateData;

class State
{
private:

protected:
	/* VARIABLES */
	StateData *data;
	std::stack<State*> *states;

	GraphicsSettings *gfxSettings;
	sf::RenderWindow *window;

	std::map<std::string, sf::Keyboard::Key> *acceptedKeys;
	std::map<std::string, sf::Keyboard::Key> keybinds;

	float gridSize;

	std::string currentPath;

	bool quitState;
	bool isPaused;

	float keytime;
	float keytimeMax;

	float mousetime;
	float mousetimeMax;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	/* ASSETS */
	std::map<std::string, sf::Texture> textures;

	/* FUNCTIONS */
	virtual void initKeybinds() = 0;

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	State(StateData *data);
	virtual ~State();

	/* PURE VIRTUAL FUNCTIONS */
	virtual void update(const float &dt) = 0;
	virtual void render(sf::RenderTarget &target) = 0;

	virtual void updateInput(const float &dt) = 0;

	/* DEFINED VIRTUAL FUNCTIONS */
	virtual void updateMousePositions(sf::View *view = nullptr);
	virtual void updateKeytime(const float &dt);
	virtual void updateMousetime(const float &dt);
	virtual void quit();
	virtual void pauseToggle();
	virtual void pause();
	virtual void resume();

	/* ACESSORS */
	const bool& hasAskedToQuit() const;
	const bool hasCompletedKeytimeCicle();
	const bool hasCompletedMousetimeCicle(sf::Mouse::Button mouseBtn);
};

#endif /* STATE_H_ */
