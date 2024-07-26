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
    const short unsigned id)
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
    const short unsigned id)
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
                          const sf::Font &font, const std::string initial_value)
{
    initTimer();

    inputString = initial_value;

    bg.setSize(sf::Vector2f(width, height));
    bg.setPosition(x, y);
    bg.setFillColor(bg_color);

    inputText.setFont(font);
    inputText.setCharacterSize(char_size);
    inputText.setString(initial_value);
    inputText.setFillColor(text_color);
    inputText.setPosition(
        bg.getPosition().x + bg.getSize().x / 10.f,
        bg.getPosition().y + bg.getSize().y / 2.f - inputText.getGlobalBounds().height / 2.f - char_size / 8.f);
}

gui::TextInput::~TextInput()
{
}

/* FUNCTIONS ==================================================================================================== */

void gui::TextInput::update()
{
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
        inputString.push_back('A');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::B)))
        inputString.push_back('B');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::C)))
        inputString.push_back('C');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
        inputString.push_back('D');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::E)))
        inputString.push_back('E');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::F)))
        inputString.push_back('F');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::G)))
        inputString.push_back('G');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::H)))
        inputString.push_back('H');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::I)))
        inputString.push_back('I');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::J)))
        inputString.push_back('J');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::K)))
        inputString.push_back('K');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::L)))
        inputString.push_back('L');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::M)))
        inputString.push_back('M');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::N)))
        inputString.push_back('N');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::O)))
        inputString.push_back('O');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::P)))
        inputString.push_back('P');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)))
        inputString.push_back('Q');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::R)))
        inputString.push_back('R');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
        inputString.push_back('S');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::T)))
        inputString.push_back('T');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::U)))
        inputString.push_back('U');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::V)))
        inputString.push_back('V');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
        inputString.push_back('W');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::X)))
        inputString.push_back('X');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)))
        inputString.push_back('Y');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)))
        inputString.push_back('Z');

    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)))
        inputString.push_back('0');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)))
        inputString.push_back('1');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)))
        inputString.push_back('2');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)))
        inputString.push_back('3');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)))
        inputString.push_back('4');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)))
        inputString.push_back('5');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)))
        inputString.push_back('6');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)))
        inputString.push_back('7');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)))
        inputString.push_back('8');
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)))
        inputString.push_back('9');

    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && inputString.size() > 0))
        inputString.pop_back();

    inputText.setString(inputString);
}

void gui::TextInput::render(sf::RenderTarget &target)
{
    target.draw(bg);
    target.draw(inputText);
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

const std::string gui::TextInput::getString() const
{
    return inputString;
}

/* MODIFIERS ==================================================================================================== */

void gui::TextInput::setString(const std::string str, const bool clear)
{
    if (clear)
        inputString.clear();

    inputString = str;
}

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
            answer = true;
            answered = true;
        }
        else if (denyBtn->isPressed() && !answered)
        {
            answer = false;
            answered = true;
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
 * TEXTURE SELECTOR
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

gui::TextureSelector::TextureSelector(
    const float btn_x, const float btn_y,
    const float btn_width, const float btn_height,
    const float txtr_slctr_x, const float txtr_slctr_y,
    const float txtr_slctr_width, const float txtr_slctr_height,
    const float grid_size_f, const sf::Texture *texture_sheet) : mousetime(0.f), mousetimeMax(10.f)
{
    gridSizeF = grid_size_f;
    active = false;
    hidden = true;
    float offset = grid_size_f;

    // Outer box
    bounds.setSize(sf::Vector2f(txtr_slctr_width, txtr_slctr_height));
    bounds.setPosition(txtr_slctr_x, txtr_slctr_y);
    bounds.setFillColor(sf::Color(50, 50, 50, 100));

    bounds.setOutlineThickness(2.f);
    bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

    // Texture sheet
    sheet.setTexture(*texture_sheet);
    sheet.setPosition(txtr_slctr_x, txtr_slctr_y);

    // If the sheet is larger than the outer box
    if (sheet.getGlobalBounds().width > bounds.getGlobalBounds().width)
    {
        sheet.setTextureRect(
            sf::IntRect(0, 0, bounds.getGlobalBounds().width, sheet.getGlobalBounds().height));
    }

    // If the sheet is taller than the outer box
    if (sheet.getGlobalBounds().height > bounds.getGlobalBounds().height)
    {
        sheet.setTextureRect(
            sf::IntRect(0, 0, sheet.getGlobalBounds().width, bounds.getGlobalBounds().height));
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

    if (!hideBtnIcon.loadFromFile("Assets/Images/Icons/texture_selector_icon.png"))
        ErrorHandler::throwErr("GUI::TEXTURESELECTOR::TEXTURESELECTOR::ERR_COULD_NOT_LOAD_TEXTURE_SELECTOR_ICON");

    hideBtn = new gui::Button(
        btn_x, btn_y, btn_width, btn_height,
        &hideBtnIcon, btn_width, btn_height,
        sf::Color(70, 70, 70, 0), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200));
}

gui::TextureSelector::~TextureSelector()
{
    delete hideBtn;
}

/* FUNCTIONS ==================================================================================================== */

void gui::TextureSelector::update(const float &dt, const sf::Vector2i mouse_pos_window)
{
    updateMousetime(dt);

    hideBtn->update(sf::Vector2f(mouse_pos_window));

    if (hideBtn->isPressed() && hasCompletedMousetimeCycle())
        hidden = !hidden;

    if (!hidden)
    {
        active = bounds.getGlobalBounds().contains(sf::Vector2f(mouse_pos_window));

        if (active)
        {
            mousePosGrid.x = (mouse_pos_window.x - bounds.getPosition().x) / (unsigned)gridSizeF;
            mousePosGrid.y = (mouse_pos_window.y - bounds.getPosition().y) / (unsigned)gridSizeF;

            selector.setPosition(
                bounds.getPosition().x + mousePosGrid.x * gridSizeF,
                bounds.getPosition().y + mousePosGrid.y * gridSizeF);

            textureRect.left = mousePosGrid.x * gridSizeF;
            textureRect.top = mousePosGrid.y * gridSizeF;
        }
    }
}

void gui::TextureSelector::render(sf::RenderTarget &target)
{
    if (!hidden)
    {
        target.draw(bounds);
        target.draw(sheet);

        if (active)
            target.draw(selector);
    }

    hideBtn->render(target);
}

void gui::TextureSelector::updateMousetime(const float &dt)
{
    if (mousetime < mousetimeMax)
    {
        mousetime += 100.f * dt;
    }
}
void gui::TextureSelector::close()
{
    hidden = true;
}

/* ACCESSORS ================================================================================================= */

const bool &gui::TextureSelector::isActive() const
{
    return active;
}

const bool gui::TextureSelector::isVisible() const
{
    return hidden;
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
    editing = false;

    offsets = sf::Vector2f(0.f, 0.f);
    dimensions = sf::Vector2f(grid_size_f, grid_size_f);

    // Texture rectangle
    textureRect.width = static_cast<int>(grid_size_f);
    textureRect.height = static_cast<int>(grid_size_f);

    if (!hideBtnIcon.loadFromFile("Assets/Images/Icons/collision_editor_icon.png"))
        ErrorHandler::throwErr("GUI::COLLISIONEDITOR::COLLISIONEDITOR::ERR_COULD_NOT_LOAD_COLLISION_EDITOR_ICON\n");

    hideBtn = new gui::Button(
        btn_x, btn_y, btn_width, btn_height,
        &hideBtnIcon, btn_width, btn_height,
        sf::Color(70, 70, 70, 0), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200));

    // Background
    editorBg.setSize(sf::Vector2f(gridSizeF * scale * 2.f, gridSizeF * scale * 2.f));
    editorBg.setFillColor(sf::Color(100, 100, 100, 100));
    editorBg.setOutlineThickness(1.f);
    editorBg.setOutlineColor(sf::Color(100, 100, 100, 150));
    editorBg.setPosition(col_editor_x, col_editor_y);

    // Tile
    editorTile.setTexture(texture_sheet);
    editorTile.setTextureRect(textureRect);
    editorTile.setSize(sf::Vector2f(gridSizeF * scale, gridSizeF * scale));
    editorTile.setPosition(editorBg.getPosition().x + editorBg.getSize().x / 2.f - editorTile.getSize().x / 2.f,
                           editorBg.getPosition().y + editorBg.getSize().y / 2.f - editorTile.getSize().y / 2.f);
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
        editorBg.getPosition().x + editorBg.getSize().x + gui::p2pX(vm, 2.f),
        editorBg.getPosition().y - gui::calc_char_size(vm, 140)));

    // Inputs
    incrementInputs["WIDTH"] = new gui::IncrementInput(
        editorBg.getPosition().x + editorBg.getSize().x + gui::p2pX(vm, 2.f),
        editorBg.getPosition().y,
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 3.75f), 1.f, sf::Color(100, 100, 100, 100),
        sf::Color(70, 70, 70, 200), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200),
        font, sf::Color(255, 255, 255, 255), gui::calc_char_size(vm, 140), grid_size_f);

    incrementInputs["HEIGHT"] = new gui::IncrementInput(
        editorBg.getPosition().x + editorBg.getSize().x + gui::p2pX(vm, 2.f),
        editorBg.getPosition().y + gui::p2pY(vm, 6.3f),
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 3.75f), 1.f, sf::Color(100, 100, 100, 100),
        sf::Color(70, 70, 70, 200), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200),
        font, sf::Color(255, 255, 255, 255), gui::calc_char_size(vm, 140), grid_size_f);

    incrementInputs["OFFSET_X"] = new gui::IncrementInput(
        editorBg.getPosition().x + editorBg.getSize().x + gui::p2pX(vm, 2.f),
        editorBg.getPosition().y + gui::p2pY(vm, 12.7f),
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 3.75f), 1.f, sf::Color(100, 100, 100, 100),
        sf::Color(70, 70, 70, 200), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200),
        font, sf::Color(255, 255, 255, 255), gui::calc_char_size(vm, 140), 0.f);

    incrementInputs["OFFSET_Y"] = new gui::IncrementInput(
        editorBg.getPosition().x + editorBg.getSize().x + gui::p2pX(vm, 2.f),
        editorBg.getPosition().y + gui::p2pY(vm, 19.1f),
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 3.75f), 1.f, sf::Color(100, 100, 100, 100),
        sf::Color(70, 70, 70, 200), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200),
        font, sf::Color(255, 255, 255, 255), gui::calc_char_size(vm, 140), 0.f);

    // Reset button
    resetBtn = new Button(
        editorBg.getPosition().x + editorBg.getSize().x + gui::p2pX(vm, 2.f),
        editorBg.getPosition().y + gui::p2pY(vm, 25.5f),
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 3.75f), font, "Reset", gui::calc_char_size(vm, 130),
        sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255),
        sf::Color(70, 70, 70, 200), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200));
}

gui::CollisionEditor::~CollisionEditor()
{
    delete hideBtn;

    for (auto &it : incrementInputs)
        delete it.second;

    delete resetBtn;
}

/* FUNCTIONS =================================================================================================== */

void gui::CollisionEditor::update(const float &dt, sf::Vector2i mouse_pos_window, sf::IntRect &texture_rect)
{
    updateMousetime(dt);

    hideBtn->update(sf::Vector2f(mouse_pos_window));
    resetBtn->update(sf::Vector2f(mouse_pos_window));

    updateInput();

    if (hideBtn->isPressed() && hasCompletedMousetimeCycle())
        editing = !editing;

    textureRect = texture_rect;

    editorTile.setTextureRect(textureRect);

    if (editing)
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
    }
}

void gui::CollisionEditor::render(sf::RenderTarget &target)
{
    if (editing)
    {
        target.draw(editorBg);
        target.draw(editorTile);
        target.draw(editorCollBox);

        target.draw(inputLabels);

        for (auto &it : incrementInputs)
            it.second->render(target);

        resetBtn->render(target);
    }

    hideBtn->render(target);
}

void gui::CollisionEditor::updateInput()
{
    if (resetBtn->isPressed() && hasCompletedMousetimeCycle())
        resetValues();
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
    editing = false;
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
    return editing;
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
