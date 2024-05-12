#ifndef GUI_H_
#define GUI_H_

enum button_states
{
	BTN_IDLE = 0,
	BTN_HOVER,
	BTN_ACTIVE
};

namespace gui
{

/**********************************************************************************************************
 *
 * BUTTON
 *
 *********************************************************************************************************/
class Button
{
private:
	short unsigned id;
	short unsigned btn_state;

	sf::RectangleShape shape;

	// Text Button
	sf::Text text;
	sf::Font *font;

	// Image button
	sf::RectangleShape image;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	sf::Color outlineIdleColor;
	sf::Color outlineHoverColor;
	sf::Color outlineActiveColor;

public:
	/* CONSTRUCTOR AND DESTRUCTOR */

	// Text button
	Button(float x, float y, float width, float height,
			sf::Font *font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent,
			sf::Color outline_hover_color = sf::Color::Transparent,
			sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);

	// Image button
	Button(float x, float y, float width, float height,
			sf::Texture *texture, float img_w, float img_h,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
			sf::Color outline_idle_color = sf::Color::Transparent,
			sf::Color outline_hover_color = sf::Color::Transparent,
			sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);

	virtual ~Button();

	/* FUNCTIONS */
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget &target);

	// Setters
	void setId(const short unsigned id);
	void setText(std::string text);

	/* ACCESSORS */
	const bool isPressed() const;
	const short unsigned getId() const;
	const std::string getText() const;
};

/**********************************************************************************************************
 *
 * DROPDOWNLIST
 *
 *********************************************************************************************************/
class DropDownList
{
private:
	/* VARIABLES */
	sf::Font &font;
	gui::Button *selectedElement;
	std::vector<gui::Button*> list;

	bool showList;

	float keytime;
	float keytimeMax;

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	DropDownList(float x, float y, float width, float height,
			sf::Font &font, std::string elements_name[], unsigned numOfElements, short unsigned default_index = 0);
	~DropDownList();

	/* FUNCTIONS */
	void update(const sf::Vector2i &mousePosWindow, const float &dt);
	void render(sf::RenderTarget &target);

	void updateKeytime(const float &dt);

	/* ACESSORS */
	const short unsigned getSelectedElementId() const;
	const bool hasCompletedKeytimeCicle();
};

/**********************************************************************************************************
 *
 * PAUSEMENU
 *
 *********************************************************************************************************/
class PauseMenu
{
private:
	/* VARIABLES */
	sf::Font &font;
	sf::Text pmenuText;

	sf::RectangleShape background;
	sf::RectangleShape container;
	std::map<std::string, gui::Button*> buttons;

	/* INITIALIZERS */
	void initButtons();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	PauseMenu(sf::RenderWindow &window, sf::Font &font);
	virtual ~PauseMenu();

	/* FUNCTIONS */
	void update(const sf::Vector2i &mousePosWindow);
	void render(sf::RenderTarget &target);

	void addButton(std::string key, float y, const std::string text);

	const bool isButtonPressed(const std::string key);

	/* ACCESSORS */
	std::map<std::string, gui::Button*>& getButtons();

};

/**********************************************************************************************************
 *
 * TEXTURE SELECTOR
 *
 *********************************************************************************************************/
class TextureSelector
{
private:
	/* VARIABLES */
	float gridSize;
	bool active;
	bool hidden;

	float mousetime;
	const float mousetimeMax;

	sf::Texture hideBtnIcon;
	gui::Button *hideBtn;

	sf::RectangleShape bounds;
	sf::Sprite sheet;

	sf::RectangleShape selector;
	sf::Vector2u mousePosGrid;

	sf::IntRect textureRect;

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	TextureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture *texture_sheet);
	~TextureSelector();

	/* FUNCTIONS */
	void update(const float &dt, const sf::Vector2i mousePosWindow);
	void render(sf::RenderTarget &target);

	void updateMousetime(const float &dt);

	/* ACCESSORS */
	const bool& isActive() const;
	const bool hasCompletedMousetimeCicle();
	const sf::IntRect& getTextureRect() const;
};
}

#endif /* GUI_H_ */
