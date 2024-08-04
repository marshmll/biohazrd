#ifndef GUI_H_
#define GUI_H_

enum ButtonStates
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
        /* CONSTRUCTOR AND DESTRUCTOR ======================================================================== */

        /**
         * @brief Creates a button instance WITH TEXT.
         *
         * @param x The x position
         * @param y The y position
         * @param width The width in pixels
         * @param height The height in pixels
         * @param font A font reference
         * @param text The button text string
         * @param characher_size The size of the characters
         * @param text_idle_color The text's idle color
         * @param text_hover_color The text's hover color
         * @param text_active_color The text's active color
         * @param idle_color The button's idle color
         * @param hover_color The button's hover color
         * @param active_color The button's active color
         * @param outline_idle_color The outline's idle color (default = Transparent)
         * @param outline_hover_color The outline's hover color (default = Transparent)
         * @param outline_active_color The outline's active color (default = Transparent)
         * @param id The button's id (default = 0)
         */
        Button(const float x, const float y, const float width, const float height,
               sf::Font &font, std::string text, const unsigned character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
               sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
               sf::Color outline_idle_color = sf::Color::Transparent,
               sf::Color outline_hover_color = sf::Color::Transparent,
               sf::Color outline_active_color = sf::Color::Transparent,
               const short unsigned id = 0);

        /**
         * @brief Creates a button instance WITH IMAGE.
         *
         * @param x The x position
         * @param y The y position
         * @param width The width in pixels
         * @param height The height in pixels
         * @param texture A Texture pointer
         * @param img_w The image width
         * @param img_h The image height
         * @param idle_color The button's idle color
         * @param hover_color The button's hover color
         * @param active_color The button's active color
         * @param outline_idle_color The outline's idle color (default = Transparent)
         * @param outline_hover_color The outline's hover color (default = Transparent)
         * @param outline_active_color The outline's active color (default = Transparent)
         * @param id The button's id (default = 0)
         */
        Button(const float x, const float y, const float width, const float height,
               sf::Texture *texture, const float img_w, const float img_h,
               sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
               sf::Color outline_idle_color = sf::Color::Transparent,
               sf::Color outline_hover_color = sf::Color::Transparent,
               sf::Color outline_active_color = sf::Color::Transparent,
               const short unsigned id = 0);

        virtual ~Button();

        /* FUNCTIONS =========================================================================================== */

        /**
         * @brief Updates buttons states and colors.
         * @note -> Sets state to idle
         * @note -> Check for new state
         * @note -> Set new text and shape fill colors
         *
         * @return void
         */
        void update(sf::Vector2f mouse_pos);

        /**
         * @brief Renders the button into a target.
         * @note -> Draws the shape into the target
         * @note -> Draws the text into the center of the shape
         *
         * @return void
         */
        void render(sf::RenderTarget &target);

        /* ACCESSORS ========================================================================================== */

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
         * @return std::string
         */
        const std::string getString() const;

        /* MODIFIERS ========================================================================================== */

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
        void setString(std::string string);
    };

    /**********************************************************************************************************
     *
     * DROPDOWNLIST
     *
     *********************************************************************************************************/

    class DropDownList
    {
    private:
        /* VARIABLES ========================================================================================== */

        gui::Button *selectedElement;
        std::vector<gui::Button *> list;

        bool showList;

        float keytime;
        float keytimeMax;

    public:
        /* CONSTRUCTOR AND DESTRUCTOR ======================================================================== */

        /**
         * @brief Initializes the drop down list.
         * @param x The x coordinate
         * @param y The y coordinate
         * @param width The buttons width
         * @param height The buttons height
         * @param font A font reference
         * @param labels A vector of strings containing the buttons labels.
         * @param char_size The character size for the labels.
         * @param max_size The max amount of elements in the list. (default = none [-1])
         * @param default_index The index of the element that is selected by default (default = 0).
         */
        DropDownList(const float x, const float y,
                     const float width, const float height,
                     sf::Font &font, const std::vector<std::string> labels,
                     const unsigned char_size,
                     const int max_size = -1,
                     const short unsigned default_index = 0);

        /**
         * @brief Frees all memory allocated to the drop down list.
         */
        ~DropDownList();

        /* FUNCTIONS ========================================================================================== */

        /**
         * @brief Updates the selected element from the list and
         * updates the whole list IF show list is true.
         *
         * @return void
         */
        void update(const sf::Vector2i &mouse_pos_window, const float &dt);

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

        /* ACCESSORS ========================================================================================== */

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
     * INCREMENT/DECREMENT INPUT
     *
     *********************************************************************************************************/

    class IncrementInput
    {
    private:
        /* VARIABLES =========================================================================================== */

        float value;
        float step;

        float mousetime;
        float mousetimeMax;

        sf::RectangleShape inputBg;

        gui::Button *incrementBtn;
        sf::Texture incrementBtnIcon;

        gui::Button *decrementBtn;
        sf::Texture decrementBtnIcon;

        sf::Text inputText;

    public:
        /* CONSTRUCTOR AND DESTRUCTOR ========================================================================== */

        /**
         * @brief Creates a IncrementInput instance. A IncrementInput is numeric input
         * which allows increasing and decreasing the value by a given step.
         *
         * @param x The x position
         * @param y The y position
         * @param width The input width
         * @param height The input height
         * @param step The increment/decrement step
         * @param bg_color The background color of the input.
         * @param buttons_idle_color The idle color of the buttons.
         * @param buttons_hover_color The hover color of the buttons.
         * @param buttons_active_color The active color of the buttons.
         * @param font A font reference.
         * @param text_color The color of the text.
         * @param char_size The text's character size.
         * @param initial_value The value the input stars with.
         */
        IncrementInput(const float x, const float y, const float width, const float height,
                       const float step, const sf::Color bg_color,
                       sf::Color buttons_idle_color, sf::Color buttons_hover_color, sf::Color buttons_active_color,
                       sf::Font &font, sf::Color text_color, const unsigned char_size, const float initial_value = 0.f);

        virtual ~IncrementInput();

        /* FUNCTIONS =========================================================================================== */

        /**
         * @brief Updates the whole input, as text, user input and value.
         *
         * @return void
         */
        void update(const float &dt, sf::Vector2f mouse_pos);

        /**
         * @brief Renders the input into a target.
         *
         * @return void
         */
        void render(sf::RenderTarget &target);

        /**
         * @brief Updates the user input and the buttons.
         *
         * @return void
         */
        void updateInput();

        /**
         * @brief Updates the mouse time.
         *
         * @return void
         */
        void updateMousetime(const float &dt);

        /* ACCESSORS =========================================================================================== */

        /**
         * @brief Returns the input's value.
         *
         * @return const float
         */
        const float getValue() const;

        const bool hasCompletedMousetimeCycle(sf::Mouse::Button mouse_btn);

        /* MODIFIERS =========================================================================================== */

        /**
         * @brief Sets the input value to a new value.
         *
         * @return void
         */
        void setValue(const float new_value);
    };

    /**********************************************************************************************************
     *
     * TEXT INPUT
     *
     *********************************************************************************************************/

    class TextInput
    {
    private:
        /* VARIABLES ========================================================================================== */

        sf::RectangleShape bg;
        sf::Text inputText;

        sf::RectangleShape cursor;

        std::string inputString;

        bool hasFocus;

        sf::Clock keyTimer;
        sf::Int32 keyTimerMax;

        sf::Event previousEvent;

        bool active;

        /* INITIALIZERS ======================================================================================= */

        void initTimer();

    public:
        /* CONSTRUCTOR AND DESTRUCTOR ======================================================================== */

        /**
         * @brief Creates a TextInput instance.
         *
         * @param x The x position
         * @param y The y position
         * @param width The input width
         * @param height The input height
         * @param bg_color The color of the input's interior.
         * @param text_color The text's color.
         * @param char_size The text's character size.
         * @param font A font reference.
         * @param initial_value The value the input starts with. Default = ""
         * @param active If the input starts being active or not. Default = false
         */
        TextInput(const float x, const float y, const float width, const float height,
                  const sf::Color &bg_color, const sf::Color &text_color,
                  const unsigned short char_size,
                  const sf::Font &font, const std::string initial_value = "",
                  const bool active = false);

        virtual ~TextInput();

        /* FUNCTIONS ========================================================================================== */

        /**
         * @brief Update the input if active.
         * Watch's for key releases and text entered.
         *
         * @return void
         */
        void update(const float &dt, const sf::Vector2f mouse_pos, sf::Event &event);

        /**
         * @brief Renders the text input if active.
         *
         * @return void
         */
        void render(sf::RenderTarget &target);

        /**
         * @brief Updates the cursor position when the input changes.
         *
         * @return void.
         */
        void updateCursor(const float &dt);

        const bool hasElapsedKeyTimeMax(const bool key_pressed);

        /* ACCESSORS ========================================================================================== */

        /**
         * @brief Returns if the input is active.
         *
         @return const bool.
         */
        const bool isActive() const;

        /**
         * @brief Returns the input's text content as a string.
         *
         * @return const std::string
         */
        const std::string getString() const;

        /* MODIFIERS ========================================================================================== */

        /**
         * @brief Sets active to the given value
         *
         * @return void
         */
        void setActive(const bool active);

        /**
         * @brief Sets the input's value to the given string.
         *
         * @return void
         */
        void setString(const std::string str, const bool clear_stream = true);
    };

    /**********************************************************************************************************
     *
     * PAUSEMENU
     *
     *********************************************************************************************************/

    class PauseMenu
    {
    private:
        /* VARIABLES ========================================================================================== */

        sf::VideoMode &vm;
        sf::Font &font;
        sf::Text pmenuText;

        sf::RectangleShape background;
        sf::RectangleShape container;
        std::map<std::string, gui::Button *> buttons;

        /* INITIALIZERS ======================================================================================= */

        /**
         * @brief Initializes pause menu buttons.
         *
         * @return void
         */
        void initButtons();

    public:
        /* CONSTRUCTOR AND DESTRUCTOR ======================================================================== */

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

        /* FUNCTIONS ========================================================================================== */

        /**
         * @brief Updates the pause menu interaction.
         * @note-> Updates all buttons
         * @note -> DOES NOT executes any function for the buttons.
         *
         * @return void
         */
        void update(const sf::Vector2i &mouse_pos_window);

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

        /* ACCESSORS ========================================================================================== */

        /**
         * @brief Returns the buttons map reference.
         *
         * @return std::map<std::string, Button*>&
         */
        std::map<std::string, gui::Button *> &getButtons();
    };

    /**********************************************************************************************************
     *
     * CONFIRMATION MODAL
     *
     *********************************************************************************************************/

    class ConfirmationModal
    {
    private:
        /* VARIABLES ============================================================================================= */

        sf::RectangleShape bg;
        sf::RectangleShape container;

        sf::Text text;

        gui::Button *confirmBtn;
        gui::Button *denyBtn;

        bool active;

        bool answered;
        bool answer;

    public:
        /* CONSTRUCTOR AND DESTRUCTOR ============================================================================ */

        /**
         * @brief Creates a confirmation modal instance.
         *
         * @param msg The message to be displayed
         * @param char_size The character size.
         * @param bg_color The color of the background.
         * @param container_color The color of the container box.
         * @param font A font reference.
         * @param vm A videomode reference.
         */
        ConfirmationModal(const std::string msg, const unsigned char_size,
                          const sf::Color bg_color, const sf::Color container_color,
                          sf::Font &font, const sf::VideoMode &vm);

        virtual ~ConfirmationModal();

        /* FUNCTIONS ============================================================================================= */

        /**
         * @brief Updates the confirmation modal, if active.
         *
         * @return void
         */
        void update(const float &dt, sf::Vector2f mouse_pos);

        /**
         * @brief Renders the confirmation modal, if active.
         */
        void render(sf::RenderTarget &target);

        /**
         * @brief Displays the confirmation modal. Sets itself as
         * active and set answered to false.
         *
         * @return void
         */
        void display();

        /* ACCESSORS ============================================================================================= */

        /**
         * @brief Returns if the confirmation modal is answered.
         *
         * @return const bool
         */
        const bool isAnswered() const;

        /**
         * @brief Returns the given answer. Returns true if confirmed,
         * otherwise false.
         *
         * @return const bool
         */
        const bool getAnswer() const;

        /**
         * @brief Returns if the modal is active.
         *
         * @return const bool
         */
        const bool isActive() const;

        /* MODIFIERS ============================================================================================= */

        /**
         * @brief Sets answred to the given value.
         *
         * @return bool
         */
        void setAnswered(const bool answered);

        /**
         * @brief Sets the answer to the given value.
         *
         * @return void
         */
        void setAnswer(const bool answer);

        /**
         * @brief Sets active to the given value.
         *
         * @return void
         */
        void setActive(const bool active);
    };

    /**********************************************************************************************************
     *
     * WORLD DATA MODAL
     *
     *********************************************************************************************************/

    class WorldDataModal
    {
    private:
        /* VARIABLES ============================================================================================= */

        sf::RectangleShape bg;
        sf::RectangleShape container;

        gui::TextInput *titleInput;
        gui::TextInput *descriptionInput;

        gui::Button *confirmBtn;
        gui::Button *denyBtn;

        bool active;
        bool confirmed;

    public:
        /* CONSTRUCTOR AND DESTRUCTOR ============================================================================ */

        /**
         * @brief Creates a instance of a world data modal.
         * The world data modal is used in the creation and in the edition
         * of worlds data.
         *
         * @param bg_color The color of the background when the modal is active.
         * @param container_color The color of the modal container.
         * @param font A font reference.
         * @param vm A videomode reference.
         */
        WorldDataModal(const sf::Color bg_color, const sf::Color container_color,
                       sf::Font &font, const sf::VideoMode &vm);

        virtual ~WorldDataModal();

        /* FUNCTIONS ============================================================================================= */

        /**
         * @brief Updates the modal, if active.
         *
         * @param dt The delta time.
         * @param mouse_pos The mouse position.
         * @param event Engine event reference.
         *
         * @return void.
         */
        void update(const float &dt, sf::Vector2f mouse_pos, sf::Event &event);

        /**
         * @brief Renders the modal into a target, if active.
         *
         * @return void.
         */
        void render(sf::RenderTarget &target);

        /**
         * @brief Displays the modal. Sets active to true and
         * confirmation to false.
         *
         * @return void
         */
        void display();

        /* ACCESSORS ============================================================================================= */

        /**
         * @brief Returns the content of the title TextInput.
         *
         * @return const std::string
         */
        const std::string getTitle() const;

        /**
         * @brief Returns the content of the description TextInput.
         *
         * @return const std::string
         */
        const std::string getDescription() const;

        /**
         * @brief Returns if the modal is active.
         *
         * @return const bool
         */
        const bool isActive() const;

        /**
         * @brief Returns if the modal was submitted.
         *
         * @return const bool
         */
        const bool isConfirmed() const;

        /* MODIFIERS ============================================================================================= */

        /**
         * @brief Sets active to the given value.
         *
         * @return void
         */
        void setActive(const bool active);

        /**
         * @brief Sets the confirmation to the given value.
         *
         * @return void
         */
        void setConfirmed(const bool confirmed);
    };

    /**********************************************************************************************************
     *
     * TEXTURE SELECTOR
     *
     *********************************************************************************************************/

    class TextureSelector
    {
    private:
        /* VARIABLES ========================================================================================== */

        float gridSizeF;
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
        /* CONSTRUCTOR AND DESTRUCTOR ======================================================================== */

        /**
         * @brief Creates a texture selector.
         */
        TextureSelector(const float btn_x, const float btn_y,
                        const float btn_width, const float btn_height,
                        const float txtr_slctr_x, const float txtr_slctr_y,
                        const float txtr_slctr_width, const float txtr_slctr_height,
                        const float grid_size_f, const sf::Texture *texture_sheet);

        /**
         * @brief Frees all buttons memory.
         */
        ~TextureSelector();

        /* FUNCTIONS ========================================================================================== */

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
        void update(const float &dt, const sf::Vector2i mouse_pos_window);

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
        void render(sf::RenderTarget &target);

        /**
         * @brief Updates the mousetime.
         * The mousetime is used for key presses filtering and
         * debugging.
         *
         * @return void
         */
        void updateMousetime(const float &dt);

        /**
         * @brief Closes the texture selector by setting hidden to true.
         *
         * @return void
         */
        void close();

        /* ACCESSORS ========================================================================================== */

        /**
         * @brief Returns if the texture selector is active.
         * @note -> Active means that the mouse is inside the box.
         *
         * @return const bool&
         */
        const bool &isActive() const;

        /**
         * @brief Returns if the texture selector is visible.
         *
         * @return const bool
         */
        const bool isVisible() const;

        /**
         * @brief Returns if a mousetime cicle has completed.
         * A mousetime cicle means that a defined amount of
         * time has passed after a mouse button was pressed.
         * @note -> Restarts mousetime after verification.
         *
         * @return const bool
         */
        const bool hasCompletedMousetimeCycle();

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
     * COLLISION EDITOR
     *
     *********************************************************************************************************/

    class CollisionEditor
    {
    private:
        /* VARIABLES =========================================================================================== */

        float gridSizeF;
        float scale;

        bool active;
        bool hidden;
        bool editing;

        sf::Vector2f offsets;
        sf::Vector2f dimensions;

        float mousetime;
        const float mousetimeMax;

        sf::Texture hideBtnIcon;
        gui::Button *hideBtn;

        sf::RectangleShape bounds;
        sf::Sprite sheet;

        sf::RectangleShape selector;
        sf::Vector2u mousePosGrid;

        sf::IntRect textureRect;

        sf::VideoMode &vm;

        sf::RectangleShape editorBg;
        sf::RectangleShape editorTile;
        sf::RectangleShape editorCollBox;

        sf::Text inputLabels;
        std::map<std::string, gui::IncrementInput *> incrementInputs;

        gui::Button *resetBtn;

    public:
        /* CONSTRUCTOR AND DESTRUCTOR ========================================================================== */

        CollisionEditor(const float btn_x, const float btn_y,
                        const float btn_width, const float btn_height,
                        const float col_editor_x, const float col_editor_y,
                        const float col_editor_width, const float col_editor_height,
                        const float grid_size_f, const float scale,
                        const sf::Texture *texture_sheet,
                        sf::Font &font, sf::VideoMode &vm);

        virtual ~CollisionEditor();

        /* FUNCTIONS =========================================================================================== */

        /**
         * @return void
         *
         * @brief Updates the collision editor if not hidden.
         * @note -> Updates mousetime
         * @note -> Updates the hide button
         * @note -> Updates the active state
         * @note -> Changes the selector position
         * @note -> Sets the texture rect.
         */
        void update(const float &dt, sf::Vector2i mouse_pos_window, sf::IntRect &texture_rect);

        /**
         * @brief Renders the collision editor into a target if
         * not hidden.
         * @note -> Renders the hide button
         * @note -> Renders bounds
         * @note -> Renders sheet
         * @note -> Renders selector if active.
         *
         * @return void
         */
        void render(sf::RenderTarget &target);

        void updateInput();

        /**
         * @brief Updates the mousetime.
         * The mousetime is used for key presses filtering and
         * debugging.
         *
         * @return void
         */
        void updateMousetime(const float &dt);

        /**
         * @brief Resets the collision editor input values.
         *
         * @return void
         */
        void resetValues();

        /**
         * @brief Closes the collision editor by setting editing to false.
         *
         * @return void
         */
        void close();

        /* ACCESSORS =========================================================================================== */

        /**
         * @brief Returns the collision box dimensions.
         *
         * @return sf::Vector2f&
         */
        const sf::Vector2f &getDimensions() const;

        /**
         * @brief Returns the collision box offsets.
         *
         * @return sf::Vector2f&
         */
        const sf::Vector2f &getOffsets() const;

        /**
         * @brief Returns if the collision editor is visible.
         *
         * @return const bool
         */
        const bool isVisible() const;

        /**
         * @brief Returns if a mousetime cicle has completed.
         * A mousetime cicle means that a defined amount of
         * time has passed after a mouse button was pressed.
         * @note -> Restarts mousetime after verification.
         *
         * @return const bool
         */
        const bool hasCompletedMousetimeCycle();

        /* MODIFIERS =========================================================================================== */
    };

    /**********************************************************************************************************
     *
     * SOLID BAR
     *
     *********************************************************************************************************/

    class SolidBar
    {
    private:
        /* VARIABLES ========================================================================================== */

        sf::RectangleShape bar;
        sf::Vector2f barMaxSize;
        sf::Text barText;

    public:
        /* CONSTRUCTOR AND DESTRUCTOR ======================================================================== */

        SolidBar(const float x, const float y,
                 const float width, const float height,
                 const sf::Color bg_color, const sf::Color text_color,
                 const sf::Font &font, const unsigned char_size,
                 const std::string string = "");

        virtual ~SolidBar();

        /* FUNCTIONS ========================================================================================== */

        void update();

        /**
         * @brief Renders the solid bar into a target.
         *
         * @return void
         */
        void render(sf::RenderTarget &target);

        /* MODIFIERS ========================================================================================== */

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
        /* VARIABLES ========================================================================================== */

        float currentValue;
        float maxValue;

        sf::RectangleShape barBg;
        sf::RectangleShape barFill;
        sf::Vector2f barMaxSize;
        sf::Text barText;

    public:
        /* CONSTRUCTOR AND DESTRUCTOR ======================================================================== */

        /**
         * @brief Progress bar constructor WITH text.
         * @param x The x position
         * @param y The y position
         * @param width The progress bar width
         * @param height The progress bar height
         * @param current_value The progress bar's current value
         * @param max_value The progress bar's maximum value
         * @param bg_color The background color for the bar.
         * @param fill_color The fill color for the bar.
         * @param font A font pointer for the text.
         * @param text_color The text color.
         * @param char_size The character size for the text.
         * @param string The initial string to display (default = "")
         */
        ProgressBar(
            const float x, const float y,
            const float width, const float height,
            const float current_value, const float max_value,
            const sf::Color bg_color, const sf::Color fill_color,
            sf::Font &font, const sf::Color text_color,
            const unsigned char_size, const std::string string = "");

        /**
         * @brief Progress bar constructor WITHOUT text.
         * @param x The x position
         * @param y The y position
         * @param width The progress bar width
         * @param height The progress bar height
         * @param current_value The progress bar's current value
         * @param max_value The progress bar's maximum value
         * @param bg_color The background color for the bar.
         * @param fill_color The fill color for the bar.
         */
        ProgressBar(
            const float x, const float y,
            const float width, const float height,
            const float current_value, const float max_value,
            const sf::Color bg_color, const sf::Color fill_color);

        virtual ~ProgressBar();

        /* FUNCTIONS ========================================================================================== */

        void update();

        void render(sf::RenderTarget &target);

        /* ACCESSORS ========================================================================================== */

        const sf::Vector2f &getPosition() const;

        /* MODIFIERS ========================================================================================== */

        /**
         * @brief Sets the bar's text string and update text position.
         *
         * @return void
         */
        void setString(const std::string string);

        /**
         * @brief Sets the bar's percent. Resizes the bar fill relative
         * to the percent.
         *
         * @return void
         */
        void setProgress(const float percent);

        /**
         * @brief Sets the bar's current value.
         *
         * @return void
         */
        void setCurrentValue(const float value);

        /**
         * @brief Sets the bar's max value.
         *
         * @return void
         */
        void setMaxValue(const float value);
    };
}

#endif /* GUI_H_ */
