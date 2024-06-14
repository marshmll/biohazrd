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
     * AUXILIARY FUNCTIONS
     *
     *********************************************************************************************************/

    /**
     * @brief Converts a window width percent to a pixel
     * coordinate dynamically.
     *
     * @param vm sf::VideoMode&
     * @param percent percent relative to window width
     *
     * @return const float;
     */
    const float p2pX(const sf::VideoMode &vm, const float percent);

    /**
     * @brief Converts a window height percent to a pixel
     * coordinate dynamically.
     *
     * @param vm sf::VideoMode&
     * @param percent percent relative to window height
     *
     * @return const float;
     */
    const float p2pY(const sf::VideoMode &vm, const float percent);

    /**
     * @brief Calculates the adequate character size based
     * on the window resolution
     *
     * @param vm sf::VideoMode&
     * @param constant A constant parameter for calculating the
     * char size (default = 60)
     *
     * @note The bigger the constant, the smaller the char size.
     *
     * @return const unsigned
     */
    const unsigned calc_char_size(const sf::VideoMode &vm, unsigned constant = 60);

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

        /**
         * @brief Creates a button instance WITH TEXT.
         * @note -> Sets initial state to idle
         * @note -> Sets button shape colors
         * @note -> Sets position, size and fil color
         * @note -> Sets font and text color
         * @note -> Sets text string, character size and text color
         * @note -> Sets text position centered in button.
         */
        Button(const float x, const float y, const float width, const float height,
               sf::Font *font, std::string text, const unsigned character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
               sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
               sf::Color outline_idle_color = sf::Color::Transparent,
               sf::Color outline_hover_color = sf::Color::Transparent,
               sf::Color outline_active_color = sf::Color::Transparent,
               const short unsigned id = 0);

        /**
         * @brief Creates a button instance WITH IMAGE.
         * @note -> Sets initial state to idle
         * @note -> Sets button shape colors
         * @note -> Sets position, size and fil color
         * @note -> Sets font to nullptr
         * @note -> Sets image size, texture and position
         * @note -> Sets image position centered in button.
         */
        Button(const float x, const float y, const float width, const float height,
               sf::Texture *texture, const float img_w, const float img_h,
               sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
               sf::Color outline_idle_color = sf::Color::Transparent,
               sf::Color outline_hover_color = sf::Color::Transparent,
               sf::Color outline_active_color = sf::Color::Transparent,
               const short unsigned id = 0);

        virtual ~Button();

        /* FUNCTIONS */

        /**
         * @brief Updates buttons states and colors.
         * @note -> Sets state to idle
         * @note -> Check for new state
         * @note -> Set new text and shape fill colors
         *
         * @return void
         */
        void update(sf::Vector2f mousePos);

        /**
         * @brief Renders the button into a target.
         * @note -> Draws the shape into the target
         * @note -> Draws the text into the center of the shape
         *
         * @return void
         */
        void render(sf::RenderTarget &target);

        /* ACCESSORS */

        /**
         * @brief Returns if the button is pressed.
         * An active status implies in a pressed button.
         *
         * @return const bool
         */
        const bool isPressed() const;

        /**
         * @brief Return a button's ID.
         *
         * @return short unsigned
         */
        const short unsigned getId() const;

        /**
         * @brief Returns a button's text string.
         *
         * @return std::string&
         */
        const std::string getText() const;

        /* MODIFIERS */

        /**
         * @brief Sets a new id for a button.
         *
         * @return void
         */
        void setId(const short unsigned id);

        /**
         * @brief Sets a new text string for a button and recenter it.
         *
         * @return void
         */
        void setText(std::string text);
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
        std::vector<gui::Button *> list;

        bool showList;

        float keytime;
        float keytimeMax;

    public:
        /* CONSTRUCTOR AND DESTRUCTOR */

        /**
         * @brief Initializes the drop down list.
         */
        DropDownList(const float x, const float y,
                     const float width, const float height,
                     sf::Font &font, const std::string elements_name[],
                     const unsigned numOfElements, const unsigned char_size,
                     const short unsigned default_index = 0);

        /**
         * @brief Frees all memory allocated to the drop down list.
         */
        ~DropDownList();

        /* FUNCTIONS */

        /**
         * @brief Updates the selected element from the list and
         * updates the whole list IF show list is true.
         *
         * @return void
         */
        void update(const sf::Vector2i &mousePosWindow, const float &dt);

        /**
         * @brief Renders the selected element from the list and
         * renders the whole list IF show list is true.
         *
         * @return void
         */
        void render(sf::RenderTarget &target);

        /**
         * @brief Updates the keytime.
         * The keytime is used for key presses filtering and
         * debugging.
         *
         * @return void
         */
        void updateKeytime(const float &dt);

        /* ACESSORS */

        /**
         * @brief Returns the selected element's id.
         *
         * @return const short unsigned
         */
        const short unsigned getSelectedElementId() const;

        /**
         * @brief Returns if a keytime cicle has completed.
         * A keytime cicle means that a defined amount of
         * time has passed after a key was pressed.
         * @note -> Restarts keytime after verification.
         *
         * @return const bool
         */
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
        sf::VideoMode &vm;
        sf::Font &font;
        sf::Text pmenuText;

        sf::RectangleShape background;
        sf::RectangleShape container;
        std::map<std::string, gui::Button *> buttons;

        /* INITIALIZERS */

        /**
         * @brief Initializes pause menu buttons.
         *
         * @return void
         */
        void initButtons();

    public:
        /* CONSTRUCTOR AND DESTRUCTOR */

        /**
         * @brief Creates the pause menu.
         * @note -> Sets background
         * @note -> Sets container
         * @note -> Sets the text
         * @note -> Initialize buttons.
         */
        PauseMenu(sf::VideoMode &vm, sf::Font &font);

        /**
         * @brief Free allocated memory from the pause menu
         * and destructs is.
         */
        virtual ~PauseMenu();

        /* FUNCTIONS */

        /**
         * @brief Updates the pause menu.
         * @note-> Updates all buttons
         *
         * @return void
         */
        void update(const sf::Vector2i &mousePosWindow);

        /**
         * @brief Renders the pause menu into a render target.
         * @note -> Renders background
         * @note -> Renders container
         * @note -> Renders text
         * @note -> Renders buttons
         *
         * @return void
         */
        void render(sf::RenderTarget &target);

        /**
         * @brief Adds a button to the pause menu
         * @param key
         * @param y
         * @param text.
         *
         * @return void
         */
        void addButton(const std::string key, const float y, const std::string text);

        /**
         * @brief Returns if a button is pressed based on its key.
         *
         * @return const bool&
         */
        const bool isButtonPressed(const std::string key);

        /* ACCESSORS */

        /**
         * @brief Returns the buttons map reference.
         *
         * @return std::map<std::string, Button*>&
         */
        std::map<std::string, gui::Button *> &getButtons();
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

        /**
         * @brief Creates a texture selector.
         */
        TextureSelector(const float btn_x, const float btn_y,
                        const float btn_width, const float btn_height,
                        const float txtr_slctr_x, const float txtr_slctr_y,
                        const float txtr_slctr_width, const float txtr_slctr_height,
                        const float gridSize, const sf::Texture *texture_sheet);

        /**
         * @brief Frees all buttons memory.
         */
        ~TextureSelector();

        /* FUNCTIONS */

        /**
         * @return void
         *
         * @brief Updates the texture selector if not hidden.
         * @note -> Updates mousetime
         * @note -> Updates the hide button
         * @note -> Updates the active state
         * @note -> Changes the selector position
         * @note -> Sets the texture rect.
         */
        void update(const float &dt, const sf::Vector2i mousePosWindow);

        /**
         * @brief Updates the mousetime.
         * The mousetime is used for key presses filtering and
         * debugging.
         *
         * @return void
         */
        void render(sf::RenderTarget &target);

        /**
         * @brief Renders the texture selector into a target if
         * not hidden.
         * @note -> Renders the hide button
         * @note -> Renders bounds
         * @note -> Renders sheet
         * @note -> Renders selector if active.
         *
         * @return void
         */
        void updateMousetime(const float &dt);

        /* ACCESSORS */

        /**
         * @brief Returns if the texture selector is active.
         *
         * @return const bool&
         */
        const bool &isActive() const;

        /**
         * @brief Returns if a mousetime cicle has completed.
         * A mousetime cicle means that a defined amount of
         * time has passed after a mouse button was pressed.
         * @note -> Restarts mousetime after verification.
         *
         * @return const bool
         */
        const bool hasCompletedMousetimeCicle();

        /**
         * @brief Returns the texture selector's texture rect.
         * The texture rect is the texture that is under
         * the mouse posiitons.
         *
         * @return const sf::IntRect&
         */
        const sf::IntRect &getTextureRect() const;
    };

    /**********************************************************************************************************
     *
     * SOLID BAR
     *
     *********************************************************************************************************/

    class SolidBar
    {
    private:
        /* VARIABLES */
        sf::RectangleShape bar;
        sf::Vector2f barMaxSize;
        sf::Font *font;
        sf::Text barText;

    public:
        /* CONSTRUCTOR AND DESTRUCTOR */

        SolidBar(const float x, const float y,
                 const float width, const float height,
                 const sf::Color bg_color, const sf::Color text_color,
                 const sf::Font &font, const unsigned char_size,
                 const std::string string = "");

        virtual ~SolidBar();

        /* FUNCTIONS */

        void update();

        void render(sf::RenderTarget &target);

        /* MODIFIERS */

        /**
         * @brief Sets the bar's text string and update text position.
         *
         * @return void
         */
        void setString(const std::string string);
    };

    /**********************************************************************************************************
     *
     * PROGRESS BAR
     *
     *********************************************************************************************************/

    class ProgressBar
    {
    private:
        /* VARIABLES */

        float currentValue;
        float maxValue;

        sf::RectangleShape barBg;
        sf::RectangleShape barFill;
        sf::Vector2f barMaxSize;
        sf::Font *font;
        sf::Text barText;

    public:
        /* CONSTRUCTOR AND DESTRUCTOR */

        ProgressBar(
            const float x, const float y,
            const float width, const float height,
            const float current_value, const float max_value,
            const sf::Color bg_color, const sf::Color fill_color,
            sf::Font *font, const sf::Color text_color,
            const unsigned char_size, const std::string string = "");

        ProgressBar(
            const float x, const float y,
            const float width, const float height,
            const float current_value, const float max_value,
            const sf::Color bg_color, const sf::Color fill_color);

        virtual ~ProgressBar();

        /* FUNCTIONS */

        void update();

        void render(sf::RenderTarget &target);

        /* MODIFIERS */

        /**
         * @brief Sets the bar's text string and update text position.
         *
         * @return void
         */
        void setString(const std::string string);

        /**
         * @brief Sets the bar's current value and resizes it relative to the
         * percentage of the max value.
         *
         * @return void
         */
        void setValue(const float value);
    };
}

#endif /* GUI_H_ */
