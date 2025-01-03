/*
 * A GUI library made by me with SFML.
 *
 * This library reunites some of the commonly
 * used Graphical User Interface resources.
 *
 *  Created on: 28 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
#include "GUI.h"

/**********************************************************************************************************
 *
 * AUXILIARY FUNCTIONS
 *
 *********************************************************************************************************/

const float gui::p2pX(const sf::VideoMode &vm, const float percent)
{
    if (percent >= 100.f)
        return static_cast<float>(vm.width);
    else if (percent <= 0.f)
        return 0.f;

    return std::floor(static_cast<float>(vm.width) * (percent / 100.f));
}

const float gui::p2pY(const sf::VideoMode &vm, const float percent)
{
    if (percent >= 100.f)
        return static_cast<float>(vm.height);
    else if (percent <= 0.f)
        return 0.f;

    return std::floor(static_cast<float>(vm.height) * (percent / 100.f));
}

const unsigned gui::calc_char_size(const sf::VideoMode &vm, unsigned constant)
{
    return (vm.width + vm.height) / constant;
}

/**********************************************************************************************************
 *
 * BUTTON
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

gui::Button::Button(
    const float x, const float y, const float width, const float height,
    sf::Font &font, std::string string, const unsigned char_size,
    sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
    sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
    sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
    const short unsigned id) : texture(nullptr)
{
    this->id = id;
    btn_state = BTN_IDLE;

    idleColor = idle_color;
    hoverColor = hover_color;
    activeColor = active_color;

    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(idle_color);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(outline_idle_color);

    textIdleColor = text_idle_color;
    textHoverColor = text_hover_color;
    textActiveColor = text_active_color;

    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(char_size);
    text.setFillColor(text_idle_color);

    text.setPosition(
        shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f,
        shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getGlobalBounds().height / 2.f - std::floor(char_size / 5.f));

    outlineIdleColor = outline_idle_color;
    outlineHoverColor = outline_hover_color;
    outlineActiveColor = outline_active_color;
}

gui::Button::Button(
    const float x, const float y, const float width, const float height,
    sf::Texture *texture, const float img_w, const float img_h,
    sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
    sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
    const short unsigned id) : texture(texture)
{
    this->id = id;
    btn_state = BTN_IDLE;

    idleColor = idle_color;
    hoverColor = hover_color;
    activeColor = active_color;

    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(idle_color);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(outline_idle_color);

    image.setSize(sf::Vector2f(img_w, img_h));
    image.setTexture(texture);
    image.setPosition(
        shape.getPosition().x + (shape.getSize().x / 2.f) - image.getSize().x / 2.f,
        shape.getPosition().y + (shape.getSize().y / 2.f) - image.getSize().y / 2.f);

    outlineIdleColor = outline_idle_color;
    outlineHoverColor = outline_hover_color;
    outlineActiveColor = outline_active_color;
}

gui::Button::~Button()
{
}

/* FUNCTIONS ==================================================================================================== */

void gui::Button::update(sf::Vector2f mouse_pos)
{
    btn_state = BTN_IDLE;

    // Hover
    if (shape.getGlobalBounds().contains(mouse_pos))
    {
        btn_state = BTN_HOVER;

        // Active
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            btn_state = BTN_ACTIVE;
        }
    }

    // Set text and fill color based on the state
    switch (btn_state)
    {
    case BTN_IDLE:
        shape.setFillColor(idleColor);
        shape.setOutlineColor(outlineIdleColor);
        text.setFillColor(textIdleColor);
        break;

    case BTN_HOVER:
        shape.setFillColor(hoverColor);
        shape.setOutlineColor(outlineHoverColor);
        text.setFillColor(textHoverColor);
        break;

    case BTN_ACTIVE:
        shape.setFillColor(activeColor);
        shape.setOutlineColor(outlineActiveColor);
        text.setFillColor(textActiveColor);
        break;
    }
}

void gui::Button::render(sf::RenderTarget &target)
{
    target.draw(shape);

    if (text.getFont())
        target.draw(text);
    else
        target.draw(image);
}

/* ACCESSORS ================================================================================================= */

const bool gui::Button::isPressed() const
{
    return btn_state == BTN_ACTIVE;
}

const short unsigned gui::Button::getId() const
{
    return id;
}

const std::string gui::Button::getString() const
{
    return text.getString();
}

/* MODIFIERS ==================================================================================================== */

void gui::Button::setId(const short unsigned id)
{
    this->id = id;
}

void gui::Button::setString(std::string string)
{
    text.setString(string);

    text.setPosition(
        shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f,
        shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getGlobalBounds().height / 2.f);
}

void gui::Button::setPosition(sf::Vector2f pos)
{
    shape.setPosition(pos);

    if (texture == nullptr)
    {
        text.setPosition(
            shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f,
            shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getGlobalBounds().height / 2.f);
    }
    else
    {
        image.setPosition(
            shape.getPosition().x + (shape.getSize().x / 2.f) - image.getSize().x / 2.f,
            shape.getPosition().y + (shape.getSize().y / 2.f) - image.getSize().y / 2.f);
    }
}

/**********************************************************************************************************
 *
 * DROPDOWNLIST
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

gui::DropDownList::DropDownList(
    const float x, const float y,
    const float width, const float height,
    sf::Font &font, const std::vector<std::string> labels,
    const unsigned char_size,
    const int max_size,
    const short unsigned default_index)
    : showList(false),
      keytime(0.f), keytimeMax(20.f)
{
    selectedElement = new gui::Button(
        x, y, width, height,
        font, labels[default_index], char_size,
        sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
        sf::Color(120, 120, 120, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
        sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50));

    for (size_t i = 0; i < labels.size(); i++)
    {
        if (max_size != -1)
        {
            if (i < max_size)
            {
                list.push_back(
                    new gui::Button(
                        x, y + ((i + 1) * height), width, height,
                        font, labels[i], char_size,
                        sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
                        sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
                        sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
                        i));
            }
        }
        else
        {
            list.push_back(
                new gui::Button(
                    x, y + ((i + 1) * height), width, height,
                    font, labels[i], char_size,
                    sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
                    sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
                    sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
                    i));
        }
    }
}

gui::DropDownList::~DropDownList()
{
    delete selectedElement;

    for (auto element : list)
        delete element;
}

/* FUNCTIONS ==================================================================================================== */

void gui::DropDownList::update(const sf::Vector2i &mouse_pos_window, const float &dt)
{
    updateKeytime(dt);

    selectedElement->update(sf::Vector2f(mouse_pos_window));

    if (selectedElement->isPressed() && hasCompletedKeytimeCicle())
        showList = !showList;

    if (showList)
    {
        for (auto &button : list)
        {
            button->update(sf::Vector2f(mouse_pos_window));

            if (button->isPressed() && hasCompletedKeytimeCicle())
            {
                selectedElement->setString(button->getString());
                selectedElement->setId(button->getId());

                showList = false;
            }
        }
    }
}

void gui::DropDownList::render(sf::RenderTarget &target)
{
    if (showList)
    {
        for (auto &it : list)
        {
            it->render(target);
        }
    }

    selectedElement->render(target);
}

void gui::DropDownList::updateKeytime(const float &dt)
{
    if (keytime < keytimeMax)
    {
        keytime += 100.f * dt;
    }
}

const short unsigned gui::DropDownList::getSelectedElementId() const
{
    return selectedElement->getId();
}

/* ACCESSORS ==================================================================================================== */

const bool gui::DropDownList::hasCompletedKeytimeCicle()
{
    if (keytime >= keytimeMax)
    {
        keytime = 0.f;
        return true;
    }

    return false;
}

/**********************************************************************************************************
 *
 * INCREMENT/DECREMENT INPUT
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================= */

gui::IncrementInput::IncrementInput(
    const float x, const float y, const float width, const float height,
    const float step, const sf::Color bg_color,
    sf::Color buttons_idle_color, sf::Color buttons_hover_color, sf::Color buttons_active_color,
    sf::Font &font, sf::Color text_color, const unsigned char_size, const float initial_value)
    : mousetime(0.f), mousetimeMax(1.f)
{
    // Variables
    value = initial_value;
    this->step = step;
    float btn_size = height;

    // Background
    inputBg.setPosition(x, y);
    inputBg.setSize(sf::Vector2f(width, height));
    inputBg.setFillColor(bg_color);

    // Text
    inputText.setFont(font);
    inputText.setCharacterSize(char_size);

    std::stringstream ss;
    ss << std::setprecision(4) << value;
    inputText.setString(ss.str());

    inputText.setFillColor(text_color);
    inputText.setPosition(inputBg.getPosition().x + inputBg.getSize().x / 2.f - inputText.getGlobalBounds().width / 2.f,
                          inputBg.getPosition().y + inputBg.getSize().y / 2.f - inputText.getGlobalBounds().height / 2.f);

    // Buttons
    if (!incrementBtnIcon.loadFromFile("Assets/Images/Icons/plus_icon.png"))
        ErrorHandler::throwErr("GUI::INCREMENTINPUT::INCREMENTINPUT::ERR_COULD_NOT_LOAD_INCREMENT_ICON\n");

    if (!decrementBtnIcon.loadFromFile("Assets/Images/Icons/minus_icon.png"))
        ErrorHandler::throwErr("GUI::INCREMENTINPUT::INCREMENTINPUT::ERR_COULD_NOT_LOAD_DECREMENT_ICON\n");

    incrementBtn = new gui::Button(
        inputBg.getPosition().x + inputBg.getSize().x - btn_size, y, btn_size, btn_size,
        &incrementBtnIcon, btn_size / 2.f, btn_size / 2.f,
        sf::Color(70, 70, 70, 0), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200));

    decrementBtn = new gui::Button(
        x, y, btn_size, btn_size,
        &decrementBtnIcon, btn_size / 2.f, btn_size / 2.f,
        sf::Color(70, 70, 70, 0), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200));
}

gui::IncrementInput::~IncrementInput()
{
    delete incrementBtn;
    delete decrementBtn;
}

/* FUNCTIONS =================================================================================================== */

void gui::IncrementInput::update(const float &dt, sf::Vector2f mouse_pos)
{
    // Update mousetime
    updateMousetime(dt);

    // Update text
    std::stringstream ss;
    ss << std::setprecision(4) << value;
    inputText.setString(ss.str());
    inputText.setPosition(inputBg.getPosition().x + inputBg.getSize().x / 2.f - inputText.getGlobalBounds().width / 2.f,
                          inputBg.getPosition().y + inputBg.getSize().y / 2.f - inputText.getGlobalBounds().height / 2.f);

    // Update buttons
    incrementBtn->update(mouse_pos);
    decrementBtn->update(mouse_pos);

    // Update input
    updateInput();
}

void gui::IncrementInput::render(sf::RenderTarget &target)
{
    target.draw(inputBg);
    target.draw(inputText);

    incrementBtn->render(target);
    decrementBtn->render(target);
}

void gui::IncrementInput::updateInput()
{
    if (incrementBtn->isPressed() && hasCompletedMousetimeCycle(sf::Mouse::Left))
        value += step;

    else if (decrementBtn->isPressed() && hasCompletedMousetimeCycle(sf::Mouse::Left))
        value -= step;
}

void gui::IncrementInput::updateMousetime(const float &dt)
{
    if (mousetime < mousetimeMax)
        mousetime += 10.f * dt;
}

/* ACCESSORS =================================================================================================== */

const float gui::IncrementInput::getValue() const
{
    return value;
}

const bool gui::IncrementInput::hasCompletedMousetimeCycle(sf::Mouse::Button mouse_btn)
{
    if (sf::Mouse::isButtonPressed(mouse_btn))
    {
        if (mousetime >= mousetimeMax)
        {
            mousetime = 0.f;
            return true;
        }
    }

    return false;
}

void gui::IncrementInput::setPosition(const float x, const float y)
{
    inputBg.setPosition(x, y);

    inputText.setPosition(inputBg.getPosition().x + inputBg.getSize().x / 2.f - inputText.getGlobalBounds().width / 2.f,
                          inputBg.getPosition().y + inputBg.getSize().y / 2.f - inputText.getGlobalBounds().height / 2.f);

    incrementBtn->setPosition(sf::Vector2f(inputBg.getPosition().x + inputBg.getSize().x - inputBg.getSize().y, y));
    decrementBtn->setPosition(sf::Vector2f(x, y));
}

/* MODIFIERS =================================================================================================== */

void gui::IncrementInput::setValue(const float new_value)
{
    value = new_value;
}

/**********************************************************************************************************
 *
 * TEXT INPUT
 *
 *********************************************************************************************************/

/* INITIALIZERS ============================================================================================== */

void gui::TextInput::initTimer()
{
    keyTimer.restart();
    keyTimerMax = sf::Int32(120);
}

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

gui::TextInput::TextInput(const float x, const float y, const float width, const float height,
                          const sf::Color &bg_color, const sf::Color &text_color,
                          const unsigned short char_size,
                          const sf::Font &font, const std::string initial_value,
                          const bool active)
{
    initTimer();

    inputString = initial_value;

    bg.setSize(sf::Vector2f(width, height));
    bg.setPosition(x, y);
    bg.setFillColor(bg_color);
    bg.setOutlineColor(sf::Color(150, 150, 150, 255));
    bg.setOutlineThickness(0.f);

    inputText.setFont(font);
    inputText.setCharacterSize(char_size);
    inputText.setString(initial_value);
    inputText.setFillColor(text_color);
    inputText.setPosition(
        bg.getPosition().x + bg.getSize().x / 10.f,
        bg.getPosition().y + bg.getSize().y / 10.f);

    cursor.setSize(sf::Vector2f(2.f, 25.f));
    cursor.setPosition(inputText.getPosition().x + inputText.getGlobalBounds().width + 2.f, inputText.getPosition().y);
    cursor.setFillColor(sf::Color(180, 180, 180, 240));

    this->active = active;
}

gui::TextInput::~TextInput()
{
}

/* FUNCTIONS ==================================================================================================== */

void gui::TextInput::update(const float &dt, const sf::Vector2f mouse_pos, sf::Event &event)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (bg.getGlobalBounds().contains(mouse_pos))
        {
            active = true;
            bg.setOutlineThickness(2.f);
        }
        else
        {
            active = false;
            bg.setOutlineThickness(0.f);
        }
    }

    if (active)
    {
        updateCursor(dt);

        if (event.type == sf::Event::KeyReleased && previousEvent.type == sf::Event::TextEntered)
        {
            if (event.key.code == sf::Keyboard::BackSpace)
            {
                if (inputString.size() > 0)
                {
                    inputString.pop_back();
                }
            }
            else if (previousEvent.text.unicode < 0x80)
            {
                char c = static_cast<char>(previousEvent.text.unicode);
                inputString.push_back(c);
            }
        }

        previousEvent = event;
        inputText.setString(inputString);
    }
    else
    {
        bg.setOutlineThickness(0.f);
    }
}

void gui::TextInput::render(sf::RenderTarget &target)
{
    target.draw(bg);
    target.draw(inputText);

    if (active)
        target.draw(cursor);
}

void gui::TextInput::updateCursor(const float &dt)
{
    cursor.setPosition(inputText.getPosition().x + inputText.getGlobalBounds().width, inputText.getPosition().y);
}

const bool gui::TextInput::hasElapsedKeyTimeMax(const bool key_pressed)
{
    if (keyTimer.getElapsedTime().asMilliseconds() >= keyTimerMax)
    {
        if (key_pressed)
            keyTimer.restart();

        return key_pressed;
    }

    return false;
}

/* ACCESSORS ==================================================================================================== */

const bool gui::TextInput::isActive() const
{
    return active;
}

const std::string gui::TextInput::getString() const
{
    return inputString;
}

/* MODIFIERS ==================================================================================================== */

void gui::TextInput::setActive(const bool active)
{
    this->active = active;
}

void gui::TextInput::setString(const std::string str, const bool clear)
{
    if (clear)
        inputString.clear();

    inputString = str;
}

/**********************************************************************************************************
 *
 * WINDOW BASE FRAME
 *
 *********************************************************************************************************/

/* INITIALIZERS ================================================================================================== */

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

gui::WindowBaseFrame::WindowBaseFrame(
    const float x, const float y, const float width, const float height, const float titlebar_height,
    const sf::Color bg_color, const sf::Color titlebar_color,
    sf::Font &font, const std::string title, const unsigned char_size,
    const sf::Color title_text_color,
    const sf::Color btn_idle_color, const sf::Color btn_hover_color, const sf::Color btn_active_color,
    const sf::Color outline_color, const float outline_thickness, const bool visible)
{
    bg.setPosition(x, y + titlebar_height);
    bg.setSize(sf::Vector2f(width, height));
    bg.setFillColor(bg_color);
    bg.setOutlineColor(outline_color);
    bg.setOutlineThickness(outline_thickness);

    titleBar.setPosition(x, y);
    titleBar.setSize(sf::Vector2f(width, titlebar_height));
    titleBar.setFillColor(titlebar_color);

    titleText.setFont(font);
    titleText.setString(title);
    titleText.setFillColor(title_text_color);
    titleText.setCharacterSize(char_size);
    titleText.setPosition(titleBar.getPosition().x + titleBar.getSize().x / 2.f - titleText.getGlobalBounds().width / 2.f,
                          titleBar.getPosition().y + titleBar.getSize().y / 2.f - titleText.getGlobalBounds().height / 2.f);

    if (!closeIcon.loadFromFile("Assets/Images/Icons/x_icon.png"))
        ErrorHandler::printErr("GUI::WINDOWBASEFRAME::WINDOWBASEFRAME::ERR_COULD_NOT_LOAD_ICON");

    closeBtn = new gui::Button(titleBar.getPosition().x + titleBar.getSize().x - titleBar.getSize().y,
                               titleBar.getPosition().y,
                               titleBar.getSize().y, titleBar.getSize().y,
                               &closeIcon, titleBar.getSize().y / 1.5f, titleBar.getSize().y / 1.5f,
                               btn_idle_color, btn_hover_color, btn_active_color);

    this->visible = visible;

    movementLock = false;
}

gui::WindowBaseFrame::~WindowBaseFrame()
{
    delete closeBtn;
}

/* FUNCTIONS ===================================================================================================== */

void gui::WindowBaseFrame::update(const float &dt, const sf::Vector2f &mouse_pos)
{
    if (isVisible())
    {
        closeBtn->update(mouse_pos);

        if (closeBtn->isPressed())
        {
            movementLock = false;
            setVisibility(false);
            return;
        }

        if (titleBar.getGlobalBounds().contains(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && !movementLock)
        {
            movementLock = true;
            mouse_offset = mouse_pos - titleBar.getPosition();
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            movementLock = false;
        }

        if (movementLock)
        {
            updateMouseDrag(mouse_pos);
        }
    }
}

void gui::WindowBaseFrame::render(sf::RenderTarget &target)
{
    if (isVisible())
    {
        target.draw(bg);
        target.draw(titleBar);
        target.draw(titleText);
        closeBtn->render(target);
    }
}

void gui::WindowBaseFrame::updateMouseDrag(const sf::Vector2f &mouse_pos)
{
    sf::Vector2f new_position(mouse_pos.x - mouse_offset.x, mouse_pos.y - mouse_offset.y);

    setPosition(new_position);
}

const bool gui::WindowBaseFrame::isVisible() const
{
    return visible;
}

const sf::FloatRect gui::WindowBaseFrame::getGlobalBounds() const
{
    return sf::FloatRect(titleBar.getPosition().x, titleBar.getPosition().y,
                         titleBar.getSize().x, titleBar.getSize().y + bg.getSize().y);
}

const sf::RectangleShape &gui::WindowBaseFrame::getTitleBar()
{
    return titleBar;
}

const sf::RectangleShape &gui::WindowBaseFrame::getBackground()
{
    return bg;
}

const bool gui::WindowBaseFrame::isDragging() const
{
    return movementLock;
}

void gui::WindowBaseFrame::setPosition(const sf::Vector2f &pos)
{
    titleBar.setPosition(pos);
    titleText.setPosition(titleBar.getPosition().x + titleBar.getSize().x / 2.f - titleText.getGlobalBounds().width / 2.f,
                          titleBar.getPosition().y + titleBar.getSize().y / 2.f - titleText.getGlobalBounds().height / 2.f);

    bg.setPosition(titleBar.getPosition().x, titleBar.getPosition().y + titleBar.getSize().y);

    closeBtn->setPosition(sf::Vector2f(titleBar.getPosition().x + titleBar.getSize().x - titleBar.getSize().y,
                                       titleBar.getPosition().y));
}

void gui::WindowBaseFrame::setVisibility(const bool visibility)
{
    visible = visibility;
}

/* ACCESSORS ===================================================================================================== */

/* MODIFIERS ===================================================================================================== */

/**********************************************************************************************************
 *
 * PAUSEMENU
 *
 *********************************************************************************************************/

/* INITIALIZERS ============================================================================================== */

void gui::PauseMenu::initButtons()
{
}

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

gui::PauseMenu::PauseMenu(sf::VideoMode &vm, sf::Font &font) : vm(vm), font(font)
{
    // Background
    background.setSize(sf::Vector2f(vm.width, vm.height));
    background.setFillColor(sf::Color(20, 20, 20, 100));

    // Container
    container.setSize(sf::Vector2f(
        background.getSize().x / 4.f,
        background.getSize().y - gui::p2pY(vm, 7.5f)));

    container.setFillColor(sf::Color(20, 20, 20, 200));

    container.setPosition(sf::Vector2f(
        background.getSize().x / 2 - container.getSize().x / 2,
        background.getSize().y / 2 - container.getSize().y / 2));

    // Pause menu text
    pmenuText.setFont(font);
    pmenuText.setFillColor(sf::Color(255, 255, 255, 200));
    pmenuText.setCharacterSize(gui::calc_char_size(vm, 60));
    pmenuText.setString("PAUSED");

    pmenuText.setPosition(sf::Vector2f(
        container.getPosition().x + container.getSize().x / 2 - pmenuText.getGlobalBounds().width / 2,
        container.getPosition().y + gui::p2pY(vm, 7.5f) - pmenuText.getGlobalBounds().height / 2));

    initButtons();
}

gui::PauseMenu::~PauseMenu()
{
    for (auto &it : buttons)
    {
        delete it.second;
    }
}

/* FUNCTIONS ==================================================================================================== */

void gui::PauseMenu::update(const sf::Vector2i &mouse_pos_window)
{
    for (auto &it : buttons)
        it.second->update(sf::Vector2f(mouse_pos_window));
}

void gui::PauseMenu::render(sf::RenderTarget &target)
{
    target.draw(background);
    target.draw(container);
    target.draw(pmenuText);

    for (auto &it : buttons)
        it.second->render(target);
}

void gui::PauseMenu::addButton(const std::string key, const float y, const std::string text)
{
    float width = gui::p2pX(vm, 9.f);
    float height = gui::p2pY(vm, 6.2f);

    float x = container.getPosition().x + container.getSize().x / 2 - width / 2;

    buttons[key] = new Button(
        x, y, width, height,
        font, text, gui::calc_char_size(vm, 90),
        sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

const bool gui::PauseMenu::isButtonPressed(const std::string key)
{
    return buttons[key]->isPressed();
}

/* ACCESSORS ==================================================================================================== */

std::map<std::string, gui::Button *> &gui::PauseMenu::getButtons()
{
    return buttons;
}

/**********************************************************************************************************
 *
 * CONFIRMATION MODAL
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

gui::ConfirmationModal::ConfirmationModal(const std::string msg, const unsigned char_size,
                                          const sf::Color bg_color, const sf::Color container_color,
                                          sf::Font &font, const sf::VideoMode &vm)
{
    bg.setSize(sf::Vector2f(vm.width, vm.height));
    bg.setPosition(0.f, 0.f);
    bg.setFillColor(bg_color);

    container.setSize(sf::Vector2f(.5f * vm.width, .5f * vm.height));
    container.setPosition(vm.width / 2.f - container.getSize().x / 2.f,
                          vm.height / 2.f - container.getSize().y / 2.f);
    container.setFillColor(container_color);

    text.setFont(font);
    text.setCharacterSize(char_size);
    text.setString(msg);
    text.setPosition(container.getPosition().x + container.getSize().x / 2.f - text.getGlobalBounds().width / 2.f,
                     container.getPosition().y + gui::p2pY(vm, 2.f));

    confirmBtn = new gui::Button(
        container.getPosition().x + gui::p2pX(vm, 1.f), container.getPosition().y + container.getSize().y - gui::p2pY(vm, 6.f),
        container.getSize().x / 2.f - gui::p2pX(vm, 1.f), gui::p2pY(vm, 5.f),
        font, "Yes", gui::calc_char_size(vm, 120),
        sf::Color(255, 255, 255, 250), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(150, 70, 70, 250), sf::Color(200, 150, 150, 250), sf::Color(50, 20, 20, 50));

    denyBtn = new gui::Button(
        container.getPosition().x + container.getSize().x / 2.f, container.getPosition().y + container.getSize().y - gui::p2pY(vm, 6.f),
        container.getSize().x / 2.f - gui::p2pX(vm, 1.f), gui::p2pY(vm, 5.f),
        font, "No", gui::calc_char_size(vm, 120),
        sf::Color(255, 255, 255, 250), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 250), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50));

    answered = true;
    answer = false;
    active = false;
}

gui::ConfirmationModal::~ConfirmationModal()
{
    delete confirmBtn;
    delete denyBtn;
}

/* FUNCTIONS ===================================================================================================== */

void gui::ConfirmationModal::update(const float &dt, sf::Vector2f mouse_pos)
{
    if (active)
    {
        confirmBtn->update(mouse_pos);
        denyBtn->update(mouse_pos);

        if (confirmBtn->isPressed() && !answered)
        {
            setAnswered(true);
            setAnswer(true);
        }
        else if (denyBtn->isPressed() && !answered)
        {
            setAnswered(true);
            setAnswer(false);
        }
    }
}

void gui::ConfirmationModal::render(sf::RenderTarget &target)
{
    if (active)
    {
        target.draw(bg);
        target.draw(container);

        target.draw(text);

        confirmBtn->render(target);
        denyBtn->render(target);
    }
}

void gui::ConfirmationModal::display()
{
    setAnswered(false);
    setActive(true);
}

/* ACCESSORS ===================================================================================================== */

const bool gui::ConfirmationModal::isAnswered() const
{
    return answered;
}

const bool gui::ConfirmationModal::getAnswer() const
{
    return answer;
}

const bool gui::ConfirmationModal::isActive() const
{
    return active;
}

/* MODIFIERS ===================================================================================================== */

void gui::ConfirmationModal::setAnswered(const bool answered)
{
    this->answered = answered;
}

void gui::ConfirmationModal::setAnswer(const bool answer)
{
    this->answer = answer;
}

void gui::ConfirmationModal::setActive(const bool active)
{
    this->active = active;
}

/**********************************************************************************************************
 *
 * WORLD DATA MODAL
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

gui::WorldDataModal::WorldDataModal(const sf::Color bg_color, const sf::Color container_color,
                                    sf::Font &font, const sf::VideoMode &vm)
{
    bg.setSize(sf::Vector2f(vm.width, vm.height));
    bg.setPosition(0.f, 0.f);
    bg.setFillColor(bg_color);

    container.setSize(sf::Vector2f(.5f * vm.width, .5f * vm.height));
    container.setPosition(vm.width / 2.f - container.getSize().x / 2.f,
                          vm.height / 2.f - container.getSize().y / 2.f);
    container.setFillColor(container_color);

    titleInput = new gui::TextInput(container.getPosition().x + container.getSize().x / 2.f - (container.getSize().x * .8f) / 2.f,
                                    container.getPosition().y + gui::p2pY(vm, 5.f),
                                    container.getSize().x * .8f, gui::p2pY(vm, 4.f),
                                    sf::Color(20, 20, 20, 250), sf::Color::White,
                                    gui::calc_char_size(vm, 120), font, "New World", false);

    descriptionInput = new gui::TextInput(container.getPosition().x + container.getSize().x / 2.f - (container.getSize().x * .8f) / 2.f,
                                          container.getPosition().y + gui::p2pY(vm, 10.f),
                                          container.getSize().x * .8f, gui::p2pY(vm, 8.f),
                                          sf::Color(20, 20, 20, 250), sf::Color::White,
                                          gui::calc_char_size(vm, 120), font, "My new world", false);

    confirmBtn = new gui::Button(
        container.getPosition().x + gui::p2pX(vm, 1.f), container.getPosition().y + container.getSize().y - gui::p2pY(vm, 6.f),
        container.getSize().x / 2.f - gui::p2pX(vm, 1.f), gui::p2pY(vm, 5.f),
        font, "Create", gui::calc_char_size(vm, 120),
        sf::Color(255, 255, 255, 250), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 150, 70, 250), sf::Color(150, 200, 150, 250), sf::Color(20, 50, 20, 50));

    denyBtn = new gui::Button(
        container.getPosition().x + container.getSize().x / 2.f, container.getPosition().y + container.getSize().y - gui::p2pY(vm, 6.f),
        container.getSize().x / 2.f - gui::p2pX(vm, 1.f), gui::p2pY(vm, 5.f),
        font, "Cancel", gui::calc_char_size(vm, 120),
        sf::Color(255, 255, 255, 250), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(150, 70, 70, 250), sf::Color(200, 150, 150, 250), sf::Color(50, 20, 20, 50));

    active = false;
    confirmed = true;
}

gui::WorldDataModal::~WorldDataModal()
{
    delete titleInput;
    delete descriptionInput;
    delete confirmBtn;
    delete denyBtn;
}

/* FUNCTIONS ===================================================================================================== */

void gui::WorldDataModal::update(const float &dt, sf::Vector2f mouse_pos, sf::Event &event)
{
    if (active)
    {
        titleInput->update(dt, mouse_pos, event);
        descriptionInput->update(dt, mouse_pos, event);

        confirmBtn->update(mouse_pos);
        denyBtn->update(mouse_pos);

        if (confirmBtn->isPressed())
        {
            setConfirmed(true);
        }
        else if (denyBtn->isPressed())
        {
            setConfirmed(false);
            setActive(false);
        }
    }
}

void gui::WorldDataModal::render(sf::RenderTarget &target)
{
    if (active)
    {
        target.draw(bg);
        target.draw(container);

        titleInput->render(target);
        descriptionInput->render(target);

        confirmBtn->render(target);
        denyBtn->render(target);

        if (confirmed)
            active = false;
    }
}

void gui::WorldDataModal::display()
{
    setActive(true);
    setConfirmed(false);
}

/* ACCESSORS ===================================================================================================== */

const std::string gui::WorldDataModal::getTitle() const
{
    return titleInput->getString();
}

const std::string gui::WorldDataModal::getDescription() const
{
    return descriptionInput->getString();
}

const bool gui::WorldDataModal::isActive() const
{
    return active;
}

const bool gui::WorldDataModal::isConfirmed() const
{
    return confirmed;
}

/* MODIFIERS ===================================================================================================== */

void gui::WorldDataModal::setActive(const bool active)
{
    this->active = active;
}

void gui::WorldDataModal::setConfirmed(const bool confirmed)
{
    this->confirmed = confirmed;
}

/**********************************************************************************************************
 *
 * TEXTURE SELECTOR
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

gui::TextureSelector::TextureSelector(
    const float btn_x, const float btn_y,
    const float btn_width, const float btn_height,
    const float txtr_slctr_x, const float txtr_slctr_y,
    const float txtr_slctr_width, const float txtr_slctr_height,
    const float grid_size_f, const sf::Texture *texture_sheet,
    sf::Font &font, const sf::VideoMode &vm) : mousetime(0.f), mousetimeMax(10.f)
{
    gridSizeF = grid_size_f;
    active = false;
    float offset = grid_size_f;

    // Window frame
    frame = new gui::WindowBaseFrame(
        txtr_slctr_x, txtr_slctr_y, txtr_slctr_width, txtr_slctr_height, 30.f,
        sf::Color(20, 20, 20, 100), sf::Color(50, 50, 50, 250), font, "Texture Selector",
        gui::calc_char_size(vm, 130), sf::Color::White,
        sf::Color(200, 50, 50, 255), sf::Color(255, 50, 50, 255), sf::Color(100, 50, 50, 255),
        sf::Color(200, 200, 200, 200), -2.f, false);

    sheetOffsetX = 0.f;
    sheetOffsetY = 0.f;

    // Texture sheet
    sheet.setTexture(*texture_sheet);
    sheet.setPosition(frame->getBackground().getPosition().x, frame->getBackground().getPosition().y);

    // If the sheet is larger than the outer box
    if (sheet.getGlobalBounds().width > frame->getBackground().getGlobalBounds().width)
    {
        sheet.setTextureRect(
            sf::IntRect(sheetOffsetX, sheetOffsetY, frame->getBackground().getGlobalBounds().width, sheet.getGlobalBounds().height));
    }

    // If the sheet is taller than the outer box
    if (sheet.getGlobalBounds().height > frame->getBackground().getGlobalBounds().height)
    {
        sheet.setTextureRect(
            sf::IntRect(sheetOffsetX, sheetOffsetY, sheet.getGlobalBounds().width, frame->getBackground().getGlobalBounds().height));
    }

    // Selector Box
    selector.setPosition(txtr_slctr_x, txtr_slctr_y);
    selector.setSize(sf::Vector2f(grid_size_f, grid_size_f));
    selector.setFillColor(sf::Color::Transparent);
    selector.setOutlineThickness(1.f);
    selector.setOutlineColor(sf::Color::Green);

    // Mouse texture selector
    textureRect.width = static_cast<int>(grid_size_f);
    textureRect.height = static_cast<int>(grid_size_f);

    if (!toggleBtnIcon.loadFromFile("Assets/Images/Icons/texture_selector_icon.png"))
        ErrorHandler::throwErr("GUI::TEXTURESELECTOR::TEXTURESELECTOR::ERR_COULD_NOT_LOAD_TEXTURE_SELECTOR_ICON");

    toggleBtn = new gui::Button(
        btn_x, btn_y, btn_width, btn_height,
        &toggleBtnIcon, btn_width, btn_height,
        sf::Color(70, 70, 70, 0), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200));
}

gui::TextureSelector::~TextureSelector()
{
    delete toggleBtn;
    delete frame;
}

/* FUNCTIONS ==================================================================================================== */

void gui::TextureSelector::update(const float &dt, const sf::Vector2i mouse_pos_window)
{
    updateMousetime(dt);

    toggleBtn->update(sf::Vector2f(mouse_pos_window));
    frame->update(dt, sf::Vector2f(mouse_pos_window));

    if (toggleBtn->isPressed() && hasCompletedMousetimeCycle())
        frame->setVisibility(!frame->isVisible());

    if (frame->isVisible())
    {
        updateMouseDrag(sf::Vector2f(mouse_pos_window));
        updateTextureSheetView();
        active = frame->getGlobalBounds().contains(sf::Vector2f(mouse_pos_window));

        if (active && !frame->getTitleBar().getGlobalBounds().contains(sf::Vector2f(mouse_pos_window)))
        {
            mousePosGrid.x = (mouse_pos_window.x - frame->getBackground().getPosition().x) / (unsigned)gridSizeF;
            mousePosGrid.y = (mouse_pos_window.y - frame->getBackground().getPosition().y) / (unsigned)gridSizeF;

            selector.setPosition(
                frame->getBackground().getPosition().x + mousePosGrid.x * gridSizeF,
                frame->getBackground().getPosition().y + mousePosGrid.y * gridSizeF);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                textureRect.left = (mousePosGrid.x * gridSizeF) + sheetOffsetX;
                textureRect.top = (mousePosGrid.y * gridSizeF) + sheetOffsetY;
            }
        }
    }
    else
    {
        active = false;
    }
}

void gui::TextureSelector::render(sf::RenderTarget &target)
{
    if (frame->isVisible())
    {
        frame->render(target);
        target.draw(sheet);

        if (active)
            target.draw(selector);
    }

    toggleBtn->render(target);
}

void gui::TextureSelector::updateMousetime(const float &dt)
{
    if (mousetime < mousetimeMax)
    {
        mousetime += 100.f * dt;
    }
}

void gui::TextureSelector::updateMouseDrag(const sf::Vector2f mouse_pos)
{
    sheet.setPosition(frame->getBackground().getPosition().x, frame->getBackground().getPosition().y);
}

void gui::TextureSelector::updateTextureSheetView()
{
    if (hasCompletedMousetimeCycle())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
        {
            if (sheetOffsetY > 0.f)
            {
                sheetOffsetY -= gridSizeF;
                sheet.setTextureRect(
                    sf::IntRect(sheetOffsetX, sheetOffsetY, frame->getBackground().getGlobalBounds().width, sheet.getGlobalBounds().height));
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
        {
            if (sheetOffsetY < sheet.getTexture()->getSize().y - sheet.getTextureRect().height)
            {
                sheetOffsetY += gridSizeF;
                sheet.setTextureRect(
                    sf::IntRect(sheetOffsetX, sheetOffsetY, frame->getBackground().getGlobalBounds().width, sheet.getGlobalBounds().height));
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
        {
            if (sheetOffsetX < sheet.getTexture()->getSize().x - sheet.getTextureRect().width)
            {
                sheetOffsetX += gridSizeF;
                sheet.setTextureRect(
                    sf::IntRect(sheetOffsetX, sheetOffsetY, frame->getBackground().getGlobalBounds().width, sheet.getGlobalBounds().height));
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
        {
            if (sheetOffsetX > 0.f)
            {
                sheetOffsetX -= gridSizeF;
                sheet.setTextureRect(
                    sf::IntRect(sheetOffsetX, sheetOffsetY, frame->getBackground().getGlobalBounds().width, sheet.getGlobalBounds().height));
            }
        }
    }
}

void gui::TextureSelector::close()
{
    frame->setVisibility(false);
}

/* ACCESSORS ================================================================================================= */

const bool &gui::TextureSelector::isActive() const
{
    return active;
}

const bool gui::TextureSelector::isVisible() const
{
    return frame->isVisible();
}

const bool gui::TextureSelector::hasCompletedMousetimeCycle()
{
    if (mousetime >= mousetimeMax)
    {
        mousetime = 0.f;
        return true;
    }

    return false;
}

const sf::IntRect &gui::TextureSelector::getTextureRect() const
{
    return textureRect;
}

/**********************************************************************************************************
 *
 * COLLISION EDITOR
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================= */

gui::CollisionEditor::CollisionEditor(
    const float btn_x, const float btn_y,
    const float btn_width, const float btn_height,
    const float col_editor_x, const float col_editor_y,
    const float col_editor_width, const float col_editor_height,
    const float grid_size_f, const float scale,
    const sf::Texture *texture_sheet,
    sf::Font &font, sf::VideoMode &vm)
    : mousetime(0.f), mousetimeMax(10.f), vm(vm)
{
    gridSizeF = grid_size_f;
    this->scale = scale;

    active = false;
    hidden = true;

    offsets = sf::Vector2f(0.f, 0.f);
    dimensions = sf::Vector2f(grid_size_f, grid_size_f);

    // Texture rectangle
    textureRect.width = static_cast<int>(grid_size_f);
    textureRect.height = static_cast<int>(grid_size_f);

    if (!toggleBtnIcon.loadFromFile("Assets/Images/Icons/collision_editor_icon.png"))
        ErrorHandler::throwErr("GUI::COLLISIONEDITOR::COLLISIONEDITOR::ERR_COULD_NOT_LOAD_COLLISION_EDITOR_ICON\n");

    toggleBtn = new gui::Button(
        btn_x, btn_y, btn_width, btn_height,
        &toggleBtnIcon, btn_width, btn_height,
        sf::Color(70, 70, 70, 0), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200));

    // Background
    frame = new gui::WindowBaseFrame(
        col_editor_x, col_editor_y,
        gridSizeF * scale * 2.f, gridSizeF * scale * 2.f, 30.f,
        sf::Color(100, 100, 100, 100), sf::Color(20, 20, 20, 200),
        font, "Collision Editor", gui::calc_char_size(vm, 125), sf::Color::White,
        sf::Color(200, 50, 50, 255), sf::Color(255, 50, 50, 255), sf::Color(100, 50, 50, 255),
        sf::Color(200, 200, 200, 200), -2.f, false);

    // Tile
    editorTile.setTexture(texture_sheet);
    editorTile.setTextureRect(textureRect);
    editorTile.setSize(sf::Vector2f(gridSizeF * scale, gridSizeF * scale));
    editorTile.setPosition(frame->getBackground().getPosition().x + frame->getBackground().getSize().x / 2.f - editorTile.getSize().x / 2.f,
                           frame->getBackground().getPosition().y + frame->getBackground().getSize().y / 2.f - editorTile.getSize().y / 2.f);
    // Collision box
    editorCollBox.setSize(sf::Vector2f(gridSizeF * scale, gridSizeF * scale));
    editorCollBox.setFillColor(sf::Color(255, 100, 100, 100));
    editorCollBox.setOutlineThickness(1.f);
    editorCollBox.setOutlineColor(sf::Color(255, 100, 100, 150));
    editorCollBox.setPosition(editorTile.getPosition());

    // Input labels
    inputLabels.setFont(font);
    inputLabels.setCharacterSize(gui::calc_char_size(vm, 140));
    inputLabels.setFillColor(sf::Color(255, 255, 255, 150));
    inputLabels.setString("Width\n\n\nHeight\n\n\nOffset X\n\n\nOffset Y");
    inputLabels.setPosition(sf::Vector2f(
        frame->getBackground().getPosition().x + frame->getBackground().getSize().x + gui::p2pX(vm, 2.f),
        frame->getBackground().getPosition().y - gui::calc_char_size(vm, 140)));

    // Inputs
    incrementInputs["WIDTH"] = new gui::IncrementInput(
        frame->getBackground().getPosition().x + frame->getBackground().getSize().x + gui::p2pX(vm, 2.f),
        frame->getBackground().getPosition().y,
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 3.75f), 1.f, sf::Color(100, 100, 100, 100),
        sf::Color(70, 70, 70, 200), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200),
        font, sf::Color(255, 255, 255, 255), gui::calc_char_size(vm, 140), grid_size_f);

    incrementInputs["HEIGHT"] = new gui::IncrementInput(
        frame->getBackground().getPosition().x + frame->getBackground().getSize().x + gui::p2pX(vm, 2.f),
        frame->getBackground().getPosition().y + gui::p2pY(vm, 6.3f),
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 3.75f), 1.f, sf::Color(100, 100, 100, 100),
        sf::Color(70, 70, 70, 200), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200),
        font, sf::Color(255, 255, 255, 255), gui::calc_char_size(vm, 140), grid_size_f);

    incrementInputs["OFFSET_X"] = new gui::IncrementInput(
        frame->getBackground().getPosition().x + frame->getBackground().getSize().x + gui::p2pX(vm, 2.f),
        frame->getBackground().getPosition().y + gui::p2pY(vm, 12.7f),
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 3.75f), 1.f, sf::Color(100, 100, 100, 100),
        sf::Color(70, 70, 70, 200), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200),
        font, sf::Color(255, 255, 255, 255), gui::calc_char_size(vm, 140), 0.f);

    incrementInputs["OFFSET_Y"] = new gui::IncrementInput(
        frame->getBackground().getPosition().x + frame->getBackground().getSize().x + gui::p2pX(vm, 2.f),
        frame->getBackground().getPosition().y + gui::p2pY(vm, 19.1f),
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 3.75f), 1.f, sf::Color(100, 100, 100, 100),
        sf::Color(70, 70, 70, 200), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200),
        font, sf::Color(255, 255, 255, 255), gui::calc_char_size(vm, 140), 0.f);

    // Reset button
    resetBtn = new Button(
        frame->getBackground().getPosition().x + frame->getBackground().getSize().x + gui::p2pX(vm, 2.f),
        frame->getBackground().getPosition().y + gui::p2pY(vm, 25.5f),
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 3.75f), font, "Reset", gui::calc_char_size(vm, 130),
        sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255),
        sf::Color(70, 70, 70, 200), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200));
}

gui::CollisionEditor::~CollisionEditor()
{
    delete frame;
    delete toggleBtn;

    for (auto &it : incrementInputs)
        delete it.second;

    delete resetBtn;
}

/* FUNCTIONS =================================================================================================== */

void gui::CollisionEditor::update(const float &dt, const sf::Vector2i &mouse_pos_window, sf::IntRect &texture_rect)
{
    updateMousetime(dt);

    frame->update(dt, sf::Vector2f(mouse_pos_window));

    toggleBtn->update(sf::Vector2f(mouse_pos_window));
    resetBtn->update(sf::Vector2f(mouse_pos_window));

    updateInput();

    if (toggleBtn->isPressed() && hasCompletedMousetimeCycle())
        frame->setVisibility(!frame->isVisible());

    textureRect = texture_rect;

    editorTile.setTextureRect(textureRect);

    if (frame->isVisible())
    {
        for (auto &it : incrementInputs)
            it.second->update(dt, static_cast<sf::Vector2f>(mouse_pos_window));

        offsets.x = incrementInputs.at("OFFSET_X")->getValue();
        offsets.y = incrementInputs.at("OFFSET_Y")->getValue();

        dimensions.x = incrementInputs.at("WIDTH")->getValue();
        dimensions.y = incrementInputs.at("HEIGHT")->getValue();

        editorCollBox.setSize(sf::Vector2f(dimensions.x * scale, dimensions.y * scale));
        editorCollBox.setPosition(editorTile.getPosition().x + offsets.x * scale,
                                  editorTile.getPosition().y + offsets.y * scale);

        if (frame->isDragging())
        {
            updateDrag(mouse_pos_window);
        }
    }
}

void gui::CollisionEditor::render(sf::RenderTarget &target)
{
    if (frame->isVisible())
    {
        frame->render(target);
        target.draw(editorTile);
        target.draw(editorCollBox);

        target.draw(inputLabels);

        for (auto &it : incrementInputs)
            it.second->render(target);

        resetBtn->render(target);
    }

    toggleBtn->render(target);
}

void gui::CollisionEditor::updateInput()
{
    if (resetBtn->isPressed() && hasCompletedMousetimeCycle())
        resetValues();
}

void gui::CollisionEditor::updateDrag(const sf::Vector2i &mouse_pos_window)
{
    editorTile.setPosition(frame->getBackground().getPosition().x + frame->getBackground().getSize().x / 2.f - editorTile.getSize().x / 2.f,
                           frame->getBackground().getPosition().y + frame->getBackground().getSize().y / 2.f - editorTile.getSize().y / 2.f);

    editorCollBox.setPosition(editorTile.getPosition());

    inputLabels.setPosition(sf::Vector2f(
        frame->getBackground().getPosition().x + frame->getBackground().getSize().x + gui::p2pX(vm, 2.f),
        frame->getBackground().getPosition().y - gui::calc_char_size(vm, 140)));

    incrementInputs.at("WIDTH")->setPosition(
        frame->getBackground().getPosition().x + frame->getBackground().getSize().x + gui::p2pX(vm, 2.f),
        frame->getBackground().getPosition().y);

    incrementInputs.at("HEIGHT")->setPosition(
        frame->getBackground().getPosition().x + frame->getBackground().getSize().x + gui::p2pX(vm, 2.f),
        frame->getBackground().getPosition().y + gui::p2pY(vm, 6.3f));

    incrementInputs.at("OFFSET_X")->setPosition(frame->getBackground().getPosition().x + frame->getBackground().getSize().x + gui::p2pX(vm, 2.f), frame->getBackground().getPosition().y + gui::p2pY(vm, 12.7f));

    incrementInputs.at("OFFSET_Y")->setPosition(frame->getBackground().getPosition().x + frame->getBackground().getSize().x + gui::p2pX(vm, 2.f), frame->getBackground().getPosition().y + gui::p2pY(vm, 19.1f));

    resetBtn->setPosition(sf::Vector2f(frame->getBackground().getPosition().x + frame->getBackground().getSize().x + gui::p2pX(vm, 2.f),
                                       frame->getBackground().getPosition().y + gui::p2pY(vm, 25.5f)));
}

void gui::CollisionEditor::updateMousetime(const float &dt)
{
    if (mousetime < mousetimeMax)
    {
        mousetime += 100.f * dt;
    }
}

void gui::CollisionEditor::resetValues()
{
    incrementInputs.at("WIDTH")->setValue(gridSizeF);
    incrementInputs.at("HEIGHT")->setValue(gridSizeF);
    incrementInputs.at("OFFSET_X")->setValue(0.f);
    incrementInputs.at("OFFSET_Y")->setValue(0.f);
}

void gui::CollisionEditor::close()
{
    frame->setVisibility(false);
}

/* ACCESSORS =================================================================================================== */

const sf::Vector2f &gui::CollisionEditor::getDimensions() const
{
    return dimensions;
}

const sf::Vector2f &gui::CollisionEditor::getOffsets() const
{
    return offsets;
}

const bool gui::CollisionEditor::isVisible() const
{
    return frame->isVisible();
}

const bool gui::CollisionEditor::hasCompletedMousetimeCycle()
{
    if (mousetime >= mousetimeMax)
    {
        mousetime = 0.f;
        return true;
    }

    return false;
}

/**********************************************************************************************************
 *
 * SOLID BAR
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

gui::SolidBar::SolidBar(
    const float x, const float y,
    const float width, const float height,
    const sf::Color bg_color, const sf::Color text_color,
    const sf::Font &font, const unsigned char_size,
    const std::string string)
{
    barMaxSize.x = width;
    barMaxSize.y = height;

    bar.setSize(barMaxSize);
    bar.setPosition(x, y);
    bar.setFillColor(bg_color);

    barText.setFont(font);
    barText.setCharacterSize(char_size);
    barText.setFillColor(text_color);
    barText.setString(string);

    // Center bar text in the bar.
    barText.setPosition(
        bar.getPosition().x + bar.getSize().x / 2.f - std::roundf(barText.getGlobalBounds().width / 2.f),
        bar.getPosition().y + bar.getSize().y / 2.f - std::floor(barText.getGlobalBounds().height / 2.f + 2.f));
}

gui::SolidBar::~SolidBar()
{
}

/* FUNCTIONS ==================================================================================================== */

void gui::SolidBar::update()
{
}

void gui::SolidBar::render(sf::RenderTarget &target)
{
    target.draw(bar);
    target.draw(barText);
}

/* MODIFIERS ==================================================================================================== */

void gui::SolidBar::setString(const std::string string)
{
    barText.setString(string);

    // Center bar text in the bar.
    barText.setPosition(
        bar.getPosition().x + bar.getSize().x / 2.f - std::roundf(barText.getGlobalBounds().width / 2.f),
        bar.getPosition().y + bar.getSize().y / 2.f - std::floor(barText.getGlobalBounds().height / 2.f + 2.f));
}

/**********************************************************************************************************
 *
 * PROGRESS BAR
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

gui::ProgressBar::ProgressBar(
    const float x, const float y,
    const float width, const float height,
    const float current_value, const float max_value,
    const sf::Color bg_color, const sf::Color fill_color,
    sf::Font &font, const sf::Color text_color,
    const unsigned char_size, const std::string string)
{
    barMaxSize.x = width;
    barMaxSize.y = height;

    currentValue = current_value;
    maxValue = max_value;

    barBg.setSize(barMaxSize);
    barBg.setPosition(x, y);
    barBg.setFillColor(bg_color);

    barFill.setSize(barMaxSize);
    barFill.setPosition(x, y);
    barFill.setFillColor(fill_color);

    barText.setFont(font);
    barText.setCharacterSize(char_size);
    barText.setFillColor(text_color);
    barText.setString(string);

    // Center bar text in the bar.
    barText.setPosition(
        barBg.getPosition().x + barBg.getSize().x / 10.f,
        barBg.getPosition().y + barBg.getSize().y / 2.f - std::floor(barText.getGlobalBounds().height / 2.f + 2.f));
}

gui::ProgressBar::ProgressBar(
    const float x, const float y,
    const float width, const float height,
    const float current_value, const float max_value,
    const sf::Color bg_color, const sf::Color fill_color)
{
    barMaxSize.x = width;
    barMaxSize.y = height;

    currentValue = current_value;
    maxValue = max_value;

    barBg.setSize(barMaxSize);
    barBg.setPosition(x, y);
    barBg.setFillColor(bg_color);

    barFill.setSize(barMaxSize);
    barFill.setPosition(x, y);
    barFill.setFillColor(fill_color);
}

gui::ProgressBar::~ProgressBar()
{
}

/* FUNCTIONS ===================================================================================================== */

void gui::ProgressBar::update()
{
}

void gui::ProgressBar::render(sf::RenderTarget &target)
{
    target.draw(barBg);
    target.draw(barFill);

    if (barText.getFont())
        target.draw(barText);
}

const sf::Vector2f &gui::ProgressBar::getPosition() const
{
    return barBg.getPosition();
}

/* MODIFIERS ==================================================================================================== */

void gui::ProgressBar::setString(const std::string string)
{
    if (barText.getFont())
    {
        barText.setString(string);

        // Center bar text in the bar.
        barText.setPosition(
            barBg.getPosition().x + barBg.getSize().x / 10.f,
            barBg.getPosition().y + barBg.getSize().y / 2.f - std::floor(barText.getGlobalBounds().height / 2.f + 2.f));
    }
}

void gui::ProgressBar::setProgress(const float percent)
{
    setCurrentValue(maxValue * percent);

    barFill.setSize(sf::Vector2f(
        static_cast<float>(std::floor(barMaxSize.x * percent)),
        barMaxSize.y));
}

void gui::ProgressBar::setCurrentValue(const float value)
{
    if (value < 0.f)
        currentValue = 0.f;
    else if (value > maxValue)
        currentValue = maxValue;
    else
        currentValue = value;
}

void gui::ProgressBar::setMaxValue(const float value)
{
    maxValue = value;
}
