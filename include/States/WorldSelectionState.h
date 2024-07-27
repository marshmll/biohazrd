#ifndef WORLDSELECTIONSTATE_H_
#define WORLDSELECTIONSTATE_H_

#include "GameState.h"
#include "EditorState.h"

class WorldSelectionState : public State
{
private:
	/* PRIVATE CLASS */
	class WorldDescriptorBox
	{
	public:
		/* VARIABLES ============================================================================================= */

		std::string filename;
		bool selected;

		sf::RectangleShape bg;
		sf::RectangleShape icon;

		sf::Text titleText;
		sf::Text descriptionText;

		/* INITIALIZERS ========================================================================================== */

		/* CONSTRUCTOR AND DESTRUCTOR ============================================================================ */

		WorldDescriptorBox(const std::string filename, const std::string title,
						   const std::string description, const std::time_t creation_date,
						   sf::Font &font, const sf::VideoMode vm, const float y,
						   sf::Texture &icon_texture)
		{
			this->filename = filename;
			selected = false;

			bg.setSize(sf::Vector2f(gui::p2pX(vm, 60.f), gui::p2pY(vm, 13.f)));
			bg.setFillColor(sf::Color(20, 20, 20, 200));
			bg.setPosition(vm.width / 2.f - bg.getSize().x / 2.f, y);
			bg.setOutlineThickness(2.f);
			bg.setOutlineColor(sf::Color::Transparent);

			icon.setFillColor(sf::Color(255, 255, 255, 200));
			icon.setSize(sf::Vector2f(bg.getSize().y, bg.getSize().y));
			icon.setPosition(bg.getPosition());
			icon.setTexture(&icon_texture);

			titleText.setFont(font);
			descriptionText.setFont(font);

			titleText.setString(title);
			titleText.setCharacterSize(gui::calc_char_size(vm, 120));
			titleText.setFillColor(sf::Color::White);

			titleText.setPosition(bg.getPosition().x + icon.getSize().x + gui::p2pX(vm, 1.f),
								  bg.getPosition().y + gui::p2pY(vm, 1.f));

			struct tm tstruct;
			char time_string[80];
			tstruct = *localtime(&creation_date);
			strftime(time_string, sizeof(time_string), "%Y-%m-%d.%X", &tstruct);

			std::stringstream ss;

			ss << description << "\n"
			   << "(" << time_string << ")";

			descriptionText.setString(ss.str());
			descriptionText.setCharacterSize(gui::calc_char_size(vm, 122));
			descriptionText.setFillColor(sf::Color(200, 200, 200, 255));

			descriptionText.setPosition(bg.getPosition().x + icon.getSize().x + gui::p2pX(vm, 1.f),
										bg.getPosition().y + titleText.getGlobalBounds().height + gui::p2pY(vm, 2.f));
		}

		~WorldDescriptorBox()
		{
		}

		/* FUNCTIONS ============================================================================================= */

		void update(const float &dt, sf::Vector2f mouse_pos)
		{
			bg.setFillColor(sf::Color(20, 20, 20, 200));

			if (selected)
				bg.setOutlineColor(sf::Color::White);
			else
				bg.setOutlineColor(sf::Color::Transparent);

			if (bg.getGlobalBounds().contains(mouse_pos))
			{
				bg.setFillColor(sf::Color(50, 50, 50, 200));

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					selected = true;
			}
		}

		void render(sf::RenderTarget &target)
		{
			target.draw(bg);
			target.draw(icon);
			target.draw(titleText);
			target.draw(descriptionText);
		}

		/* ACCESSORS ============================================================================================= */

		inline const std::string &getFilename() const { return filename; }

		inline const sf::Vector2f &getSize() const { return bg.getSize(); }

		inline bool isSelected() const { return selected; }

		/* MODIFIERS ============================================================================================= */

		void deselect() { selected = false; }

		void setYPosition(const sf::VideoMode &vm, const float y)
		{
			bg.setPosition(vm.width / 2.f - bg.getSize().x / 2.f, y);
			icon.setPosition(bg.getPosition());

			titleText.setPosition(bg.getPosition().x + icon.getSize().x + gui::p2pX(vm, 1.f),
								  bg.getPosition().y + gui::p2pY(vm, 1.f));

			descriptionText.setPosition(bg.getPosition().x + icon.getSize().x + gui::p2pX(vm, 1.f),
										bg.getPosition().y + titleText.getGlobalBounds().height + gui::p2pY(vm, 2.f));
		}
	};

	/* VARIABLES ================================================================================================= */

	sf::Font font;

	sf::Texture iconTexture;

	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	sf::RectangleShape headerBg;
	sf::Text headerText;

	sf::RectangleShape menuBg;

	std::map<std::string, gui::Button *> buttons;

	std::vector<WorldDescriptorBox *> worldDescriptors;

	WorldDescriptorBox *selectedDescriptor;

	gui::ConfirmationModal *deleteConfirmationModal;

	gui::WorldDataModal *worldDataModal;

	/* INITIALIZERS ============================================================================================== */

	/**
	 * @brief Initializes variables for the state.
	 *
	 * @return void
	 */
	void initVariables();

	/**
	 * @brief Initializes keybinds for the state.
	 *
	 * @return void
	 */
	void initKeybinds();

	/**
	 * @brief Initializes fonts for the state.
	 *
	 * @return void
	 */
	void initFonts();

	/**
	 * @brief Initializes GUI elements for the state.
	 *
	 * @return void
	 */
	void initGUI();

	/**
	 * @brief Initializes the world description selection
	 * boxes for the state.
	 *
	 * @return void
	 */
	void initWorldDescriptors();

public:
	/* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

	/**
	 * @brief This State is responsible for managing map/world loading,
	 * deleting, creatng editing and saving.
	 */
	WorldSelectionState(StateData *data);

	virtual ~WorldSelectionState();

	/* FUNCTIONS ================================================================================================= */

	/**
	 * @brief Updates all elements of the state.
	 *
	 * @return void
	 */
	void update(const float &dt);

	/**
	 * @brief Renders all elements of the state.
	 *
	 * @return void
	 */
	void render(sf::RenderTarget &target);

	/**
	 * @brief Updates user input in the state.
	 *
	 * @return void
	 */
	void updateInput(const float &dt);

	/**
	 * @brief Updates the state's GUI.
	 *
	 * @return void
	 */
	void updateGUI(const float &dt);

	/**
	 * @brief Updates all World Selection Boxes of the state.
	 *
	 * @note Called just when deleting or creating a new world.
	 *
	 * @return void
	 */
	void updateWorldDescriptors();

	/**
	 * @brief Renders all GUI elements into the screen.
	 *
	 * @return void
	 */
	void renderGUI(sf::RenderTarget &target);
};

#endif
