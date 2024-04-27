#ifndef GUI_PAUSEMENU_H_
#define GUI_PAUSEMENU_H_

#include "../Resource Files/Button.h"

class PauseMenu
{
private:
	/* VARIABLES */
	sf::Font &font;
	sf::Text pmenuText;

	sf::RectangleShape background;
	sf::RectangleShape container;
	std::map<std::string, Button*> buttons;

	/* INITIALIZERS */
	void initButtons();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	PauseMenu(sf::RenderWindow &window, sf::Font &font);
	virtual ~PauseMenu();

	/* FUNCTIONS */
	void update(const sf::Vector2f &mousePos);
	void render(sf::RenderTarget &target);

	void addButton(std::string key, float y, const std::string text);

	const bool isButtonPressed(const std::string key);

	/* ACCESSORS */
	std::map<std::string, Button*>& getButtons();

};

#endif /* GUI_PAUSEMENU_H_ */
