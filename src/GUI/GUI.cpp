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

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

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

/* FUNCTIONS ==================================================================================================== */

void gui::Button::update(sf::Vector2f mouse_pos)
{
    this->btn_state = BTN_IDLE;

    // Hover
    if (this->shape.getGlobalBounds().contains(mouse_pos))
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

/* ACCESSORS ================================================================================================= */

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

/* MODIFIERS ==================================================================================================== */

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

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

gui::DropDownList::DropDownList(
    const float x, const float y,
    const float width, const float height,
    sf::Font &font, const std::string elements_name[],
    const unsigned num_of_elements, const unsigned char_size,
    const short unsigned default_index) : font(font), showList(false),
                                          keytime(0.f), keytimeMax(20.f)
{
    this->selectedElement = new gui::Button(
        x, y, width, height,
        &this->font, elements_name[default_index], char_size,
        sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
        sf::Color(120, 120, 120, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
        sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50));

    for (unsigned i = 0; i < num_of_elements; i++)
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

/* FUNCTIONS ==================================================================================================== */

void gui::DropDownList::update(const sf::Vector2i &mouse_pos_window, const float &dt)
{
    this->updateKeytime(dt);

    this->selectedElement->update(sf::Vector2f(mouse_pos_window));

    if (this->selectedElement->isPressed() && this->hasCompletedKeytimeCicle())
        this->showList = !this->showList;

    if (this->showList)
    {
        for (auto &button : this->list)
        {
            button->update(sf::Vector2f(mouse_pos_window));

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

/* ACCESSORS ==================================================================================================== */

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
 * INCREMENT/DECREMENT INPUT
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================= */

gui::IncrementInput::IncrementInput(
    const float x, const float y, const float width, const float height,
    const float step, const sf::Color bg_color,
    sf::Color buttons_idle_color, sf::Color buttons_hover_color, sf::Color buttons_active_color,
    sf::Font *font, sf::Color text_color, const unsigned char_size, const float initial_value)
    : mousetime(0.f), mousetimeMax(1.f)
{
    // Variables
    this->value = initial_value;
    this->step = step;
    float btn_size = height;

    // Background
    this->inputBg.setPosition(x, y);
    this->inputBg.setSize(sf::Vector2f(width, height));
    this->inputBg.setFillColor(bg_color);

    // Text
    this->inputText.setFont(*font);
    this->inputText.setCharacterSize(char_size);

    std::stringstream ss;
    ss << std::setprecision(4) << this->value;
    this->inputText.setString(ss.str());

    this->inputText.setFillColor(text_color);
    this->inputText.setPosition(this->inputBg.getPosition().x + this->inputBg.getSize().x / 2.f - this->inputText.getGlobalBounds().width / 2.f,
                                this->inputBg.getPosition().y + this->inputBg.getSize().y / 2.f - this->inputText.getGlobalBounds().height / 2.f);

    // Buttons
    if (!this->incrementBtnIcon.loadFromFile("Assets/Images/Icons/plus_icon.png"))
        ErrorHandler::throwErr("GUI::INCREMENTINPUT::INCREMENTINPUT::ERR_COULD_NOT_LOAD_INCREMENT_ICON\n");

    if (!this->decrementBtnIcon.loadFromFile("Assets/Images/Icons/minus_icon.png"))
        ErrorHandler::throwErr("GUI::INCREMENTINPUT::INCREMENTINPUT::ERR_COULD_NOT_LOAD_DECREMENT_ICON\n");

    this->incrementBtn = new gui::Button(
        this->inputBg.getPosition().x + this->inputBg.getSize().x - btn_size, y, btn_size, btn_size,
        &this->incrementBtnIcon, btn_size / 2.f, btn_size / 2.f,
        sf::Color(70, 70, 70, 0), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200));

    this->decrementBtn = new gui::Button(
        x, y, btn_size, btn_size,
        &this->decrementBtnIcon, btn_size / 2.f, btn_size / 2.f,
        sf::Color(70, 70, 70, 0), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200));
}

gui::IncrementInput::~IncrementInput()
{
    delete this->incrementBtn;
    delete this->decrementBtn;
}

/* FUNCTIONS =================================================================================================== */

void gui::IncrementInput::update(const float &dt, sf::Vector2f mouse_pos)
{
    // Update mousetime
    this->updateMousetime(dt);

    // Update text
    std::stringstream ss;
    ss << std::setprecision(4) << this->value;
    this->inputText.setString(ss.str());
    this->inputText.setPosition(this->inputBg.getPosition().x + this->inputBg.getSize().x / 2.f - this->inputText.getGlobalBounds().width / 2.f,
                                this->inputBg.getPosition().y + this->inputBg.getSize().y / 2.f - this->inputText.getGlobalBounds().height / 2.f);

    // Update buttons
    this->incrementBtn->update(mouse_pos);
    this->decrementBtn->update(mouse_pos);

    // Update input
    this->updateInput();
}

void gui::IncrementInput::render(sf::RenderTarget &target)
{
    target.draw(this->inputBg);
    target.draw(this->inputText);

    this->incrementBtn->render(target);
    this->decrementBtn->render(target);
}

void gui::IncrementInput::updateInput()
{
    if (this->incrementBtn->isPressed() && this->hasCompletedMousetimeCycle(sf::Mouse::Left))
        this->value += this->step;

    else if (this->decrementBtn->isPressed() && this->hasCompletedMousetimeCycle(sf::Mouse::Left))
        this->value -= this->step;
}

void gui::IncrementInput::updateMousetime(const float &dt)
{
    if (this->mousetime < this->mousetimeMax)
        this->mousetime += 10.f * dt;
}

/* ACCESSORS =================================================================================================== */

const float gui::IncrementInput::getValue() const
{
    return this->value;
}

const bool gui::IncrementInput::hasCompletedMousetimeCycle(sf::Mouse::Button mouse_btn)
{
    if (sf::Mouse::isButtonPressed(mouse_btn))
    {
        if (this->mousetime >= this->mousetimeMax)
        {
            this->mousetime = 0.f;
            return true;
        }
    }

    return false;
}

/* MODIFIERS =================================================================================================== */

void gui::IncrementInput::setValue(const float new_value)
{
    this->value = new_value;
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

/* FUNCTIONS ==================================================================================================== */

void gui::PauseMenu::update(const sf::Vector2i &mouse_pos_window)
{
    for (auto &it : this->buttons)
        it.second->update(sf::Vector2f(mouse_pos_window));
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

/* ACCESSORS ==================================================================================================== */

std::map<std::string, gui::Button *> &gui::PauseMenu::getButtons()
{
    return this->buttons;
}

/**********************************************************************************************************
 *
 * TEXTURE SELECTOR
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

gui::TextureSelector::TextureSelector(
    const float btn_x, const float btn_y,
    const float btn_width, const float btn_height,
    const float txtr_slctr_x, const float txtr_slctr_y,
    const float txtr_slctr_width, const float txtr_slctr_height,
    const float grid_size_f, const sf::Texture *texture_sheet) : mousetime(0.f), mousetimeMax(10.f)
{
    this->gridSizeF = grid_size_f;
    this->active = false;
    this->hidden = true;
    float offset = grid_size_f;

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
    this->selector.setSize(sf::Vector2f(grid_size_f, grid_size_f));
    this->selector.setFillColor(sf::Color::Transparent);
    this->selector.setOutlineThickness(1.f);
    this->selector.setOutlineColor(sf::Color::Green);

    // Mouse texture selector
    this->textureRect.width = static_cast<int>(grid_size_f);
    this->textureRect.height = static_cast<int>(grid_size_f);

    if (!this->hideBtnIcon.loadFromFile("Assets/Images/Icons/texture_selector_icon.png"))
        ErrorHandler::throwErr("GUI::TEXTURESELECTOR::TEXTURESELECTOR::ERR_COULD_NOT_LOAD_TEXTURE_SELECTOR_ICON");

    this->hideBtn = new gui::Button(
        btn_x, btn_y, btn_width, btn_height,
        &this->hideBtnIcon, btn_width, btn_height,
        sf::Color(70, 70, 70, 0), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200));
}

gui::TextureSelector::~TextureSelector()
{
    delete this->hideBtn;
}

/* FUNCTIONS ==================================================================================================== */

void gui::TextureSelector::update(const float &dt, const sf::Vector2i mouse_pos_window)
{
    this->updateMousetime(dt);

    this->hideBtn->update(sf::Vector2f(mouse_pos_window));

    if (this->hideBtn->isPressed() && this->hasCompletedMousetimeCicle())
        this->hidden = !this->hidden;

    if (!this->hidden)
    {
        this->active = this->bounds.getGlobalBounds().contains(sf::Vector2f(mouse_pos_window));

        if (this->active)
        {
            this->mousePosGrid.x = (mouse_pos_window.x - this->bounds.getPosition().x) / (unsigned)this->gridSizeF;
            this->mousePosGrid.y = (mouse_pos_window.y - this->bounds.getPosition().y) / (unsigned)this->gridSizeF;

            this->selector.setPosition(
                this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSizeF,
                this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSizeF);

            this->textureRect.left = this->mousePosGrid.x * this->gridSizeF;
            this->textureRect.top = this->mousePosGrid.y * this->gridSizeF;
        }
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

void gui::TextureSelector::updateMousetime(const float &dt)
{
    if (this->mousetime < this->mousetimeMax)
    {
        this->mousetime += 100.f * dt;
    }
}
void gui::TextureSelector::close()
{
    this->hidden = true;
}

/* ACCESSORS ================================================================================================= */

const bool &gui::TextureSelector::isActive() const
{
    return this->active;
}

const bool gui::TextureSelector::isVisible() const
{
    return this->hidden;
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
 * COLLISION EDITOR
 *
 *********************************************************************************************************/

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================= */

gui::CollisionEditor::CollisionEditor(
    const float btn_x, const float btn_y,
    const float btn_width, const float btn_height,
    const float col_editor_x, const float col_editor_y,
    const float col_editor_width, const float col_editor_height,
    const float grid_size_f, const sf::Texture *texture_sheet,
    sf::Font *font, sf::VideoMode &vm)
    : mousetime(0.f), mousetimeMax(10.f), vm(vm)
{
    this->gridSizeF = grid_size_f;
    this->active = false;
    this->hidden = true;
    this->editing = false;

    this->offsets = sf::Vector2f(0.f, 0.f);
    this->dimensions = sf::Vector2f(grid_size_f, grid_size_f);

    // Texture rectangle
    this->textureRect.width = static_cast<int>(grid_size_f);
    this->textureRect.height = static_cast<int>(grid_size_f);

    if (!this->hideBtnIcon.loadFromFile("Assets/Images/Icons/collision_editor_icon.png"))
        ErrorHandler::throwErr("GUI::COLLISIONEDITOR::COLLISIONEDITOR::ERR_COULD_NOT_LOAD_COLLISION_EDITOR_ICON\n");

    this->hideBtn = new gui::Button(
        btn_x, btn_y, btn_width, btn_height,
        &this->hideBtnIcon, btn_width, btn_height,
        sf::Color(70, 70, 70, 0), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200));

    // Editing
    this->editorBg.setSize(sf::Vector2f(this->gridSizeF * 3.f, this->gridSizeF * 3.f));
    this->editorBg.setFillColor(sf::Color(100, 100, 100, 100));
    this->editorBg.setOutlineThickness(1.f);
    this->editorBg.setOutlineColor(sf::Color(100, 100, 100, 150));
    this->editorBg.setPosition(col_editor_x, col_editor_y);

    this->editorTile.setTexture(texture_sheet);
    this->editorTile.setTextureRect(this->textureRect);
    this->editorTile.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
    this->editorTile.setPosition(this->editorBg.getPosition().x + this->editorBg.getSize().x / 2.f - this->editorTile.getSize().x / 2.f,
                                 this->editorBg.getPosition().y + this->editorBg.getSize().y / 2.f - this->editorTile.getSize().y / 2.f);

    this->editorCollBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
    this->editorCollBox.setFillColor(sf::Color(255, 100, 100, 100));
    this->editorCollBox.setOutlineThickness(1.f);
    this->editorCollBox.setOutlineColor(sf::Color(255, 100, 100, 150));
    this->editorCollBox.setPosition(this->editorTile.getPosition());

    this->incrementInputs["WIDTH"] = new gui::IncrementInput(
        this->editorBg.getPosition().x + this->editorBg.getSize().x,
        this->editorBg.getPosition().y,
        200.f, 30.f, 1.f, sf::Color(100, 100, 100, 100),
        sf::Color(70, 70, 70, 200), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200),
        font, sf::Color(255, 255, 255, 255), gui::calc_char_size(this->vm, 140), grid_size_f);

    this->incrementInputs["HEIGHT"] = new gui::IncrementInput(
        this->editorBg.getPosition().x + this->editorBg.getSize().x,
        this->editorBg.getPosition().y + 50.f,
        200.f, 30.f, 1.f, sf::Color(100, 100, 100, 100),
        sf::Color(70, 70, 70, 200), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200),
        font, sf::Color(255, 255, 255, 255), gui::calc_char_size(this->vm, 140), grid_size_f);

    this->incrementInputs["OFFSET_X"] = new gui::IncrementInput(
        this->editorBg.getPosition().x + this->editorBg.getSize().x,
        this->editorBg.getPosition().y + 100.f,
        200.f, 30.f, 1.f, sf::Color(100, 100, 100, 100),
        sf::Color(70, 70, 70, 200), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200),
        font, sf::Color(255, 255, 255, 255), gui::calc_char_size(this->vm, 140), 0.f);

    this->incrementInputs["OFFSET_Y"] = new gui::IncrementInput(
        this->editorBg.getPosition().x + this->editorBg.getSize().x,
        this->editorBg.getPosition().y + 150.f,
        200.f, 30.f, 1.f, sf::Color(100, 100, 100, 100),
        sf::Color(70, 70, 70, 200), sf::Color(255, 255, 255, 100), sf::Color(255, 255, 255, 200),
        font, sf::Color(255, 255, 255, 255), gui::calc_char_size(this->vm, 140), 0.f);
}

gui::CollisionEditor::~CollisionEditor()
{
    delete this->hideBtn;

    for (auto &it : this->incrementInputs)
        delete it.second;
}

/* FUNCTIONS =================================================================================================== */

void gui::CollisionEditor::update(const float &dt, sf::Vector2i mouse_pos_window, sf::IntRect &texture_rect)
{
    this->updateMousetime(dt);

    this->hideBtn->update(sf::Vector2f(mouse_pos_window));

    if (this->hideBtn->isPressed() && this->hasCompletedMousetimeCicle())
        this->editing = !this->editing;

    this->textureRect = texture_rect;

    this->editorTile.setTextureRect(this->textureRect);

    if (this->editing)
    {
        for (auto &it : this->incrementInputs)
            it.second->update(dt, static_cast<sf::Vector2f>(mouse_pos_window));

        this->offsets.x = this->incrementInputs.at("OFFSET_X")->getValue();
        this->offsets.y = this->incrementInputs.at("OFFSET_Y")->getValue();

        this->dimensions.x = this->incrementInputs.at("WIDTH")->getValue();
        this->dimensions.y = this->incrementInputs.at("HEIGHT")->getValue();

        this->editorCollBox.setSize(this->dimensions);
        this->editorCollBox.setPosition(this->editorTile.getPosition().x + this->offsets.x,
                                        this->editorTile.getPosition().y + this->offsets.y);
    }
}

void gui::CollisionEditor::render(sf::RenderTarget &target)
{
    if (this->editing)
    {
        target.draw(this->editorBg);
        target.draw(this->editorTile);
        target.draw(this->editorCollBox);

        for (auto &it : this->incrementInputs)
            it.second->render(target);
    }

    this->hideBtn->render(target);
}

void gui::CollisionEditor::updateMousetime(const float &dt)
{
    if (this->mousetime < this->mousetimeMax)
    {
        this->mousetime += 100.f * dt;
    }
}

void gui::CollisionEditor::close()
{
    this->editing = false;
}

/* ACCESSORS =================================================================================================== */

const sf::Vector2f &gui::CollisionEditor::getDimensions() const
{
    return this->dimensions;
}

const sf::Vector2f &gui::CollisionEditor::getOffsets() const
{
    return this->offsets;
}

const bool gui::CollisionEditor::isVisible() const
{
    return this->editing;
}

const bool gui::CollisionEditor::hasCompletedMousetimeCicle()
{
    if (this->mousetime >= this->mousetimeMax)
    {
        this->mousetime = 0.f;
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

/* FUNCTIONS ==================================================================================================== */

void gui::SolidBar::update()
{
}

void gui::SolidBar::render(sf::RenderTarget &target)
{
    target.draw(this->bar);
    target.draw(this->barText);
}

/* MODIFIERS ==================================================================================================== */

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

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

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

/* FUNCTIONS ==================================================================================================== */

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

/* MODIFIERS ==================================================================================================== */

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