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
	BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE
};

class Button
{
private:
	short unsigned btn_state;

	sf::RectangleShape shape;

	sf::Text text;
	sf::Font *font;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

public:
	Button(float x, float y, float width, float height,
			sf::Font *font, std::string text,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	virtual ~Button();

	/* FUNCTIONS */
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget *target = nullptr);

	/* ACCESSORS */
	const bool isPressed() const;
};

#endif /* RESOURCE_FILES_BUTTON_H_ */
