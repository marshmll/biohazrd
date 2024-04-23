#ifndef RESOURCE_FILES_BUTTON_H_
#define RESOURCE_FILES_BUTTON_H_

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum button_states
{
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_ACTIVE
};

class Button
{
private:
	short unsigned btn_state;

	sf::RectangleShape shape;

	sf::Text text;
	sf::Font *font;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height,
			sf::Font *font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color);
	virtual ~Button();

	/* FUNCTIONS */
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget &target);

	/* ACCESSORS */
	const bool isPressed() const;
};

#endif /* RESOURCE_FILES_BUTTON_H_ */
