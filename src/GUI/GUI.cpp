/*
 * A GUI library made by me with SFML.
 *
 * This library reunites some of the commonly
 * used Graphical User Interface resources.
 *
 *  Created on: 28 de abr. de 2024
 *      Author: renan
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

/* CONSTRUCTOR AND DESTRUCTOR */

gui::Button::Button(
    const float x, const float y, const float width, const float height,
    sf::Font *font, std::string text, const unsigned char_size,
    sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
    sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
    sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
    const short unsigned id)
{
    this->id = id;
    this->btn_state = BTN_IDLE;

    this->idleColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(idle_color);
    this->shape.setOutlineThickness(1.f);
    this->shape.setOutlineColor(outline_idle_color);

    this->font = font;

    this->textIdleColor = text_idle_color;
    this->textHoverColor = text_hover_color;
    this->textActiveColor = text_active_color;

    this->text.setFont(*font);
    this->text.setString(text);
    this->text.setCharacterSize(char_size);
    this->text.setFillColor(text_idle_color);

    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f);

    this->outlineIdleColor = outline_idle_color;
    this->outlineHoverColor = outline_hover_color;
    this->outlineActiveColor = outline_active_color;
}

gui::Button::Button(
    const float x, const float y, const float width, const float height,
    sf::Texture *texture, const float img_w, const float img_h,
    sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
    sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
    const short unsigned id)
{
    this->id = id;
    this->btn_state = BTN_IDLE;

    this->idleColor = idle_color;
    this->hoverColor = hover_color;
    this->activeColor = active_color;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(idle_color);
    this->shape.setOutlineThickness(1.f);
    this->shape.setOutlineColor(outline_idle_color);

    this->font = nullptr;

    this->image.setSize(sf::Vector2f(img_w, img_h));
    this->image.setTexture(texture);
    this->image.setPosition(
        this->shape.getPosition().x + (this->shape.getSize().x / 2.f) - this->image.getSize().x / 2.f,
        this->shape.getPosition().y + (this->shape.getSize().y / 2.f) - this->image.getSize().y / 2.f);

    this->outlineIdleColor = outline_idle_color;
    this->outlineHoverColor = outline_hover_color;
    this->outlineActiveColor = outline_active_color;
}

gui::Button::~Button()
{
}

/* FUNCTIONS */

void gui::Button::update(sf::Vector2f mousePos)
{
    this->btn_state = BTN_IDLE;

    // Hover
    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        this->btn_state = BTN_HOVER;

        // Active
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->btn_state = BTN_ACTIVE;
        }
    }

    // Set text and fill color based on the state
    switch (this->btn_state)
    {
    case BTN_IDLE:
        this->shape.setFillColor(this->idleColor);
        this->shape.setOutlineColor(this->outlineIdleColor);
        this->text.setFillColor(this->textIdleColor);
        break;

    case BTN_HOVER:
        this->shape.setFillColor(this->hoverColor);
        this->shape.setOutlineColor(this->outlineHoverColor);
        this->text.setFillColor(this->textHoverColor);
        break;

    case BTN_ACTIVE:
        this->shape.setFillColor(this->activeColor);
        this->shape.setOutlineColor(this->outlineActiveColor);
        this->text.setFillColor(this->textActiveColor);
        break;
    }
}

void gui::Button::render(sf::RenderTarget &target)
{
    target.draw(this->shape);

    if (font)
        target.draw(this->text);
    else
        target.draw(this->image);
}

/* ACCESSORS */

const bool gui::Button::isPressed() const
{
    return this->btn_state == BTN_ACTIVE;
}

const short unsigned gui::Button::getId() const
{
    return this->id;
}

const std::string gui::Button::getText() const
{
    return this->text.getString();
}

/* MODIFIERS */

void gui::Button::setId(const short unsigned id)
{
    this->id = id;
}

void gui::Button::setText(std::string text)
{
    this->text.setString(text);

    this->text.setPosition(
        this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f);
}

/**********************************************************************************************************
 *
 * DROPDOWNLIST
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR */

gui::DropDownList::DropDownList(
    const float x, const float y,
    const float width, const float height,
    sf::Font &font, const std::string elements_name[],
    const unsigned numOfElements, const unsigned char_size,
    const short unsigned default_index) : font(font), showList(false),
                                          keytime(0.f), keytimeMax(20.f)
{
    this->selectedElement = new gui::Button(
        x, y, width, height,
        &this->font, elements_name[default_index], char_size,
        sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
        sf::Color(120, 120, 120, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
        sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50));

    for (unsigned i = 0; i < numOfElements; i++)
    {
        this->list.push_back(
            new gui::Button(
                x, y + ((i + 1) * height), width, height,
                &this->font, elements_name[i], char_size,
                sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
                sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
                sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
                i));
    }
}

gui::DropDownList::~DropDownList()
{
    delete this->selectedElement;

    for (auto &it : this->list)
    {
        delete it;
    }
}

/* FUNCTIONS */

void gui::DropDownList::update(const sf::Vector2i &mousePosWindow, const float &dt)
{
    this->updateKeytime(dt);

    this->selectedElement->update(sf::Vector2f(mousePosWindow));

    if (this->selectedElement->isPressed() && this->hasCompletedKeytimeCicle())
        this->showList = !this->showList;

    if (this->showList)
    {
        for (auto &button : this->list)
        {
            button->update(sf::Vector2f(mousePosWindow));

            if (button->isPressed() && this->hasCompletedKeytimeCicle())
            {
                this->selectedElement->setText(button->getText());
                this->selectedElement->setId(button->getId());

                this->showList = false;
            }
        }
    }
}

void gui::DropDownList::render(sf::RenderTarget &target)
{
    if (this->showList)
    {
        for (auto &it : this->list)
        {
            it->render(target);
        }
    }

    this->selectedElement->render(target);
}

void gui::DropDownList::updateKeytime(const float &dt)
{
    if (this->keytime < this->keytimeMax)
    {
        this->keytime += 100.f * dt;
    }
}

const short unsigned gui::DropDownList::getSelectedElementId() const
{
    return this->selectedElement->getId();
}

/* ACESSORS */
const bool gui::DropDownList::hasCompletedKeytimeCicle()
{
    if (this->keytime >= this->keytimeMax)
    {
        this->keytime = 0.f;
        return true;
    }

    return false;
}

/**********************************************************************************************************
 *
 * PAUSEMENU
 *
 *********************************************************************************************************/

/* INITIALIZERS */

void gui::PauseMenu::initButtons()
{
}

/* CONSTRUCTOR AND DESTRUCTOR */

gui::PauseMenu::PauseMenu(sf::VideoMode &vm, sf::Font &font) : vm(vm), font(font)
{
    // Background
    this->background.setSize(sf::Vector2f(this->vm.width, this->vm.height));
    this->background.setFillColor(sf::Color(20, 20, 20, 100));

    // Container
    this->container.setSize(sf::Vector2f(
        this->background.getSize().x / 4.f,
        this->background.getSize().y - gui::p2pY(this->vm, 7.5f)));

    this->container.setFillColor(sf::Color(20, 20, 20, 200));

    this->container.setPosition(sf::Vector2f(
        this->background.getSize().x / 2 - this->container.getSize().x / 2,
        this->background.getSize().y / 2 - this->container.getSize().y / 2));

    // Pause menu text
    this->pmenuText.setFont(this->font);
    this->pmenuText.setFillColor(sf::Color(255, 255, 255, 200));
    this->pmenuText.setCharacterSize(gui::calc_char_size(this->vm, 60));
    this->pmenuText.setString("PAUSED");

    this->pmenuText.setPosition(sf::Vector2f(
        this->container.getPosition().x + this->container.getSize().x / 2 - this->pmenuText.getGlobalBounds().width / 2,
        this->container.getPosition().y + gui::p2pY(this->vm, 7.5f) - this->pmenuText.getGlobalBounds().height / 2));

    this->initButtons();
}

gui::PauseMenu::~PauseMenu()
{
    for (auto &it : this->buttons)
    {
        delete it.second;
    }
}

/* FUNCTIONS */

void gui::PauseMenu::update(const sf::Vector2i &mousePosWindow)
{
    for (auto &it : this->buttons)
        it.second->update(sf::Vector2f(mousePosWindow));
}

void gui::PauseMenu::render(sf::RenderTarget &target)
{
    target.draw(this->background);
    target.draw(this->container);
    target.draw(this->pmenuText);

    for (auto &it : this->buttons)
        it.second->render(target);
}

void gui::PauseMenu::addButton(const std::string key, const float y, const std::string text)
{
    float width = gui::p2pX(this->vm, 19.5f);
    float height = gui::p2pY(this->vm, 6.2f);

    float x = this->container.getPosition().x + this->container.getSize().x / 2 - width / 2;

    this->buttons[key] = new Button(
        x, y, width, height,
        &this->font, text, gui::calc_char_size(this->vm, 70),
        sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

const bool gui::PauseMenu::isButtonPressed(const std::string key)
{
    return this->buttons[key]->isPressed();
}

/* ACCESSORS */

std::map<std::string, gui::Button *> &gui::PauseMenu::getButtons()
{
    return this->buttons;
}

/**********************************************************************************************************
 *
 * TEXTURE SELECTOR
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR */

gui::TextureSelector::TextureSelector(
    const float btn_x, const float btn_y,
    const float btn_width, const float btn_height,
    const float txtr_slctr_x, const float txtr_slctr_y,
    const float txtr_slctr_width, const float txtr_slctr_height,
    const float gridSize, const sf::Texture *texture_sheet) : mousetime(0.f), mousetimeMax(10.f)
{
    this->gridSize = gridSize;
    this->active = false;
    this->hidden = true;
    float offset = gridSize;

    // Outer box
    this->bounds.setSize(sf::Vector2f(txtr_slctr_width, txtr_slctr_height));
    this->bounds.setPosition(txtr_slctr_x, txtr_slctr_y);
    this->bounds.setFillColor(sf::Color(50, 50, 50, 100));

    this->bounds.setOutlineThickness(2.f);
    this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

    // Texture sheet
    this->sheet.setTexture(*texture_sheet);
    this->sheet.setPosition(txtr_slctr_x, txtr_slctr_y);

    // If the sheet is larger than the outer box
    if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
    {
        this->sheet.setTextureRect(
            sf::IntRect(0, 0, this->bounds.getGlobalBounds().width, this->sheet.getGlobalBounds().height));
    }

    // If the sheet is taller than the outer box
    if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
    {
        this->sheet.setTextureRect(
            sf::IntRect(0, 0, this->sheet.getGlobalBounds().width, this->bounds.getGlobalBounds().height));
    }

    // Selector Box
    this->selector.setPosition(txtr_slctr_x, txtr_slctr_y);
    this->selector.setSize(sf::Vector2f(gridSize, gridSize));
    this->selector.setFillColor(sf::Color::Transparent);
    this->selector.setOutlineThickness(1.f);
    this->selector.setOutlineColor(sf::Color::Green);

    // Mouse texture selector
    this->textureRect.width = static_cast<int>(gridSize);
    this->textureRect.height = static_cast<int>(gridSize);

    if (!this->hideBtnIcon.loadFromFile("Assets/Images/Icons/texture_selector_icon.png"))
        ErrorHandler::throwErr("GUI::TEXTURESELECTOR::TEXTURESELECTOR::ERR_COULD_NOT_LOAD_TEXTURE_SELECTOR_ICON");

    this->hideBtn = new gui::Button(
        btn_x, btn_x, btn_width, btn_height,
        &this->hideBtnIcon, btn_width, btn_height,
        sf::Color(70, 70, 70, 0), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200));
}

gui::TextureSelector::~TextureSelector()
{
    delete this->hideBtn;
}

/* FUNCTIONS */

void gui::TextureSelector::update(const float &dt, const sf::Vector2i mousePosWindow)
{
    this->updateMousetime(dt);

    this->hideBtn->update(sf::Vector2f(mousePosWindow));

    if (this->hideBtn->isPressed() && this->hasCompletedMousetimeCicle())
        this->hidden = !this->hidden;

    if (!this->hidden)
    {
        this->active = this->bounds.getGlobalBounds().contains(sf::Vector2f(mousePosWindow));

        if (this->active)
        {
            this->mousePosGrid.x = (mousePosWindow.x - this->bounds.getPosition().x) / (unsigned)this->gridSize;
            this->mousePosGrid.y = (mousePosWindow.y - this->bounds.getPosition().y) / (unsigned)this->gridSize;

            this->selector.setPosition(
                this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
                this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize);

            this->textureRect.left = this->mousePosGrid.x * gridSize;
            this->textureRect.top = this->mousePosGrid.y * gridSize;
        }
    }
}

void gui::TextureSelector::updateMousetime(const float &dt)
{
    if (this->mousetime < this->mousetimeMax)
    {
        this->mousetime += 100.f * dt;
    }
}

void gui::TextureSelector::render(sf::RenderTarget &target)
{
    if (!this->hidden)
    {
        target.draw(this->bounds);
        target.draw(this->sheet);

        if (this->active)
            target.draw(this->selector);
    }

    this->hideBtn->render(target);
}

/* ACCESSORS */

const bool &gui::TextureSelector::isActive() const
{
    return this->active;
}

const bool gui::TextureSelector::hasCompletedMousetimeCicle()
{
    if (this->mousetime >= this->mousetimeMax)
    {
        this->mousetime = 0.f;
        return true;
    }

    return false;
}

const sf::IntRect &gui::TextureSelector::getTextureRect() const
{
    return this->textureRect;
}

/**********************************************************************************************************
 *
 * SOLID BAR
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR */

gui::SolidBar::SolidBar(
    const float x, const float y,
    const float width, const float height,
    const sf::Color bg_color, const sf::Color text_color,
    const sf::Font &font, const unsigned char_size,
    const std::string string)
{
    this->barMaxSize.x = width;
    this->barMaxSize.y = height;

    this->bar.setSize(this->barMaxSize);
    this->bar.setPosition(x, y);
    this->bar.setFillColor(bg_color);

    this->barText.setFont(font);
    this->barText.setCharacterSize(char_size);
    this->barText.setFillColor(text_color);
    this->barText.setString(string);

    // Center bar text in the bar.
    this->barText.setPosition(
        this->bar.getPosition().x + this->bar.getSize().x / 2.f - std::roundf(this->barText.getGlobalBounds().width / 2.f),
        this->bar.getPosition().y + this->bar.getSize().y / 2.f - std::floor(this->barText.getGlobalBounds().height / 2.f + 2.f));
}

gui::SolidBar::~SolidBar()
{
}

/* FUNCTIONS */

void gui::SolidBar::update()
{
}

void gui::SolidBar::render(sf::RenderTarget &target)
{
    target.draw(this->bar);
    target.draw(this->barText);
}

/* MODIFIERS */

void gui::SolidBar::setString(const std::string string)
{
    this->barText.setString(string);

    // Center bar text in the bar.
    this->barText.setPosition(
        this->bar.getPosition().x + this->bar.getSize().x / 2.f - std::roundf(this->barText.getGlobalBounds().width / 2.f),
        this->bar.getPosition().y + this->bar.getSize().y / 2.f - std::floor(this->barText.getGlobalBounds().height / 2.f + 2.f));
}

/**********************************************************************************************************
 *
 * PROGRESS BAR
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR */

gui::ProgressBar::ProgressBar(
    const float x, const float y,
    const float width, const float height,
    const float current_value, const float max_value,
    const sf::Color bg_color, const sf::Color fill_color,
    sf::Font *font, const sf::Color text_color,
    const unsigned char_size, const std::string string)
{
    this->barMaxSize.x = width;
    this->barMaxSize.y = height;

    this->font = font;

    this->currentValue = current_value;
    this->maxValue = max_value;

    this->barBg.setSize(this->barMaxSize);
    this->barBg.setPosition(x, y);
    this->barBg.setFillColor(bg_color);

    this->barFill.setSize(this->barMaxSize);
    this->barFill.setPosition(x, y);
    this->barFill.setFillColor(fill_color);

    this->barText.setFont(*font);
    this->barText.setCharacterSize(char_size);
    this->barText.setFillColor(text_color);
    this->barText.setString(string);

    // Center bar text in the bar.
    this->barText.setPosition(
        this->barBg.getPosition().x + this->barBg.getSize().x / 10.f,
        this->barBg.getPosition().y + this->barBg.getSize().y / 2.f - std::floor(this->barText.getGlobalBounds().height / 2.f + 2.f));
}

gui::ProgressBar::ProgressBar(
    const float x, const float y,
    const float width, const float height,
    const float current_value, const float max_value,
    const sf::Color bg_color, const sf::Color fill_color)
{
    this->barMaxSize.x = width;
    this->barMaxSize.y = height;

    this->font = nullptr;

    this->currentValue = current_value;
    this->maxValue = max_value;

    this->barBg.setSize(this->barMaxSize);
    this->barBg.setPosition(x, y);
    this->barBg.setFillColor(bg_color);

    this->barFill.setSize(this->barMaxSize);
    this->barFill.setPosition(x, y);
    this->barFill.setFillColor(fill_color);
}

gui::ProgressBar::~ProgressBar()
{
}

/* FUNCTIONS */

void gui::ProgressBar::update()
{
}

void gui::ProgressBar::render(sf::RenderTarget &target)
{
    target.draw(this->barBg);
    target.draw(this->barFill);

    if (this->font)
        target.draw(this->barText);
}

/* MODIFIERS */

void gui::ProgressBar::setString(const std::string string)
{
    if (this->font)
    {
        this->barText.setString(string);

        // Center bar text in the bar.
        this->barText.setPosition(
            this->barBg.getPosition().x + this->barBg.getSize().x / 10.f,
            this->barBg.getPosition().y + this->barBg.getSize().y / 2.f - std::floor(this->barText.getGlobalBounds().height / 2.f + 2.f));
    }
}

void gui::ProgressBar::setProgress(const float percent)
{
    this->setCurrentValue(this->maxValue * percent);

    this->barFill.setSize(sf::Vector2f(
        static_cast<float>(std::floor(this->barMaxSize.x * percent)),
        this->barMaxSize.y));
}

void gui::ProgressBar::setCurrentValue(const float value)
{
    if (value < 0.f)
        this->currentValue = 0.f;
    else if (value > this->maxValue)
        this->currentValue = this->maxValue;
    else
        this->currentValue = value;
}

void gui::ProgressBar::setMaxValue(const float value)
{
    this->maxValue = value;
}
