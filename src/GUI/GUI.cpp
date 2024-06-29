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

const float gui::p2pX(const VideoMode &vm, const float percent)
{
    if (percent >= 100.f)
        return static_cast<float>(vm.width);
    else if (percent <= 0.f)
        return 0.f;

    return floor(static_cast<float>(vm.width) * (percent / 100.f));
}

const float gui::p2pY(const VideoMode &vm, const float percent)
{
    if (percent >= 100.f)
        return static_cast<float>(vm.height);
    else if (percent <= 0.f)
        return 0.f;

    return floor(static_cast<float>(vm.height) * (percent / 100.f));
}

const unsigned gui::calc_char_size(const VideoMode &vm, unsigned constant)
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
    Font &font, string string, const unsigned char_size,
    Color text_idle_color, Color text_hover_color, Color text_active_color,
    Color idle_color, Color hover_color, Color active_color,
    Color outline_idle_color, Color outline_hover_color, Color outline_active_color,
    const short unsigned id)
{
    this->id = id;
    btn_state = BTN_IDLE;

    idleColor = idle_color;
    hoverColor = hover_color;
    activeColor = active_color;

    shape.setPosition(Vector2f(x, y));
    shape.setSize(Vector2f(width, height));
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
        shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getGlobalBounds().height / 2.f - floor(char_size / 5.f));

    outlineIdleColor = outline_idle_color;
    outlineHoverColor = outline_hover_color;
    outlineActiveColor = outline_active_color;
}

gui::Button::Button(
    const float x, const float y, const float width, const float height,
    Texture *texture, const float img_w, const float img_h,
    Color idle_color, Color hover_color, Color active_color,
    Color outline_idle_color, Color outline_hover_color, Color outline_active_color,
    const short unsigned id)
{
    this->id = id;
    btn_state = BTN_IDLE;

    idleColor = idle_color;
    hoverColor = hover_color;
    activeColor = active_color;

    shape.setPosition(Vector2f(x, y));
    shape.setSize(Vector2f(width, height));
    shape.setFillColor(idle_color);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(outline_idle_color);

    image.setSize(Vector2f(img_w, img_h));
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

void gui::Button::update(Vector2f mouse_pos)
{
    btn_state = BTN_IDLE;

    // Hover
    if (shape.getGlobalBounds().contains(mouse_pos))
    {
        btn_state = BTN_HOVER;

        // Active
        if (Mouse::isButtonPressed(Mouse::Left))
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

void gui::Button::render(RenderTarget &target)
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

const string gui::Button::getString() const
{
    return text.getString();
}

/* MODIFIERS ==================================================================================================== */

void gui::Button::setId(const short unsigned id)
{
    this->id = id;
}

void gui::Button::setString(string string)
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
    Font &font, const vector<string> labels,
    const unsigned char_size,
    const int max_size,
    const short unsigned default_index)
    : showList(false),
      keytime(0.f), keytimeMax(20.f)
{
    selectedElement = new gui::Button(
        x, y, width, height,
        font, labels[default_index], char_size,
        Color(255, 255, 255, 150), Color(255, 255, 255, 200), Color(20, 20, 20, 50),
        Color(120, 120, 120, 200), Color(150, 150, 150, 200), Color(20, 20, 20, 200),
        Color(255, 255, 255, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50));

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
                        Color(255, 255, 255, 150), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
                        Color(70, 70, 70, 200), Color(150, 150, 150, 200), Color(20, 20, 20, 200),
                        Color(255, 255, 255, 0), Color(255, 255, 255, 0), Color(20, 20, 20, 0),
                        i));
            }
        }
        else
        {
            list.push_back(
                new gui::Button(
                    x, y + ((i + 1) * height), width, height,
                    font, labels[i], char_size,
                    Color(255, 255, 255, 150), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
                    Color(70, 70, 70, 200), Color(150, 150, 150, 200), Color(20, 20, 20, 200),
                    Color(255, 255, 255, 0), Color(255, 255, 255, 0), Color(20, 20, 20, 0),
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

void gui::DropDownList::update(const Vector2i &mouse_pos_window, const float &dt)
{
    updateKeytime(dt);

    selectedElement->update(Vector2f(mouse_pos_window));

    if (selectedElement->isPressed() && hasCompletedKeytimeCicle())
        showList = !showList;

    if (showList)
    {
        for (auto &button : list)
        {
            button->update(Vector2f(mouse_pos_window));

            if (button->isPressed() && hasCompletedKeytimeCicle())
            {
                selectedElement->setString(button->getString());
                selectedElement->setId(button->getId());

                showList = false;
            }
        }
    }
}

void gui::DropDownList::render(RenderTarget &target)
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
    const float step, const Color bg_color,
    Color buttons_idle_color, Color buttons_hover_color, Color buttons_active_color,
    Font &font, Color text_color, const unsigned char_size, const float initial_value)
    : mousetime(0.f), mousetimeMax(1.f)
{
    // Variables
    value = initial_value;
    this->step = step;
    float btn_size = height;

    // Background
    inputBg.setPosition(x, y);
    inputBg.setSize(Vector2f(width, height));
    inputBg.setFillColor(bg_color);

    // Text
    inputText.setFont(font);
    inputText.setCharacterSize(char_size);

    stringstream ss;
    ss << setprecision(4) << value;
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
        Color(70, 70, 70, 0), Color(255, 255, 255, 100), Color(255, 255, 255, 200));

    decrementBtn = new gui::Button(
        x, y, btn_size, btn_size,
        &decrementBtnIcon, btn_size / 2.f, btn_size / 2.f,
        Color(70, 70, 70, 0), Color(255, 255, 255, 100), Color(255, 255, 255, 200));
}

gui::IncrementInput::~IncrementInput()
{
    delete incrementBtn;
    delete decrementBtn;
}

/* FUNCTIONS =================================================================================================== */

void gui::IncrementInput::update(const float &dt, Vector2f mouse_pos)
{
    // Update mousetime
    updateMousetime(dt);

    // Update text
    stringstream ss;
    ss << setprecision(4) << value;
    inputText.setString(ss.str());
    inputText.setPosition(inputBg.getPosition().x + inputBg.getSize().x / 2.f - inputText.getGlobalBounds().width / 2.f,
                          inputBg.getPosition().y + inputBg.getSize().y / 2.f - inputText.getGlobalBounds().height / 2.f);

    // Update buttons
    incrementBtn->update(mouse_pos);
    decrementBtn->update(mouse_pos);

    // Update input
    updateInput();
}

void gui::IncrementInput::render(RenderTarget &target)
{
    target.draw(inputBg);
    target.draw(inputText);

    incrementBtn->render(target);
    decrementBtn->render(target);
}

void gui::IncrementInput::updateInput()
{
    if (incrementBtn->isPressed() && hasCompletedMousetimeCycle(Mouse::Left))
        value += step;

    else if (decrementBtn->isPressed() && hasCompletedMousetimeCycle(Mouse::Left))
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

const bool gui::IncrementInput::hasCompletedMousetimeCycle(Mouse::Button mouse_btn)
{
    if (Mouse::isButtonPressed(mouse_btn))
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
 * PAUSEMENU
 *
 *********************************************************************************************************/

/* INITIALIZERS ============================================================================================== */

void gui::PauseMenu::initButtons()
{
}

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

gui::PauseMenu::PauseMenu(VideoMode &vm, Font &font) : vm(vm), font(font)
{
    // Background
    background.setSize(Vector2f(vm.width, vm.height));
    background.setFillColor(Color(20, 20, 20, 100));

    // Container
    container.setSize(Vector2f(
        background.getSize().x / 4.f,
        background.getSize().y - gui::p2pY(vm, 7.5f)));

    container.setFillColor(Color(20, 20, 20, 200));

    container.setPosition(Vector2f(
        background.getSize().x / 2 - container.getSize().x / 2,
        background.getSize().y / 2 - container.getSize().y / 2));

    // Pause menu text
    pmenuText.setFont(font);
    pmenuText.setFillColor(Color(255, 255, 255, 200));
    pmenuText.setCharacterSize(gui::calc_char_size(vm, 60));
    pmenuText.setString("PAUSED");

    pmenuText.setPosition(Vector2f(
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

void gui::PauseMenu::update(const Vector2i &mouse_pos_window)
{
    for (auto &it : buttons)
        it.second->update(Vector2f(mouse_pos_window));
}

void gui::PauseMenu::render(RenderTarget &target)
{
    target.draw(background);
    target.draw(container);
    target.draw(pmenuText);

    for (auto &it : buttons)
        it.second->render(target);
}

void gui::PauseMenu::addButton(const string key, const float y, const string text)
{
    float width = gui::p2pX(vm, 9.f);
    float height = gui::p2pY(vm, 6.2f);

    float x = container.getPosition().x + container.getSize().x / 2 - width / 2;

    buttons[key] = new Button(
        x, y, width, height,
        font, text, gui::calc_char_size(vm, 90),
        Color(200, 200, 200, 200), Color(250, 250, 250, 250), Color(20, 20, 20, 50),
        Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0));
}

const bool gui::PauseMenu::isButtonPressed(const string key)
{
    return buttons[key]->isPressed();
}

/* ACCESSORS ==================================================================================================== */

map<string, gui::Button *> &gui::PauseMenu::getButtons()
{
    return buttons;
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
    const float grid_size_f, const Texture *texture_sheet) : mousetime(0.f), mousetimeMax(10.f)
{
    gridSizeF = grid_size_f;
    active = false;
    hidden = true;
    float offset = grid_size_f;

    // Outer box
    bounds.setSize(Vector2f(txtr_slctr_width, txtr_slctr_height));
    bounds.setPosition(txtr_slctr_x, txtr_slctr_y);
    bounds.setFillColor(Color(50, 50, 50, 100));

    bounds.setOutlineThickness(2.f);
    bounds.setOutlineColor(Color(255, 255, 255, 200));

    // Texture sheet
    sheet.setTexture(*texture_sheet);
    sheet.setPosition(txtr_slctr_x, txtr_slctr_y);

    // If the sheet is larger than the outer box
    if (sheet.getGlobalBounds().width > bounds.getGlobalBounds().width)
    {
        sheet.setTextureRect(
            IntRect(0, 0, bounds.getGlobalBounds().width, sheet.getGlobalBounds().height));
    }

    // If the sheet is taller than the outer box
    if (sheet.getGlobalBounds().height > bounds.getGlobalBounds().height)
    {
        sheet.setTextureRect(
            IntRect(0, 0, sheet.getGlobalBounds().width, bounds.getGlobalBounds().height));
    }

    // Selector Box
    selector.setPosition(txtr_slctr_x, txtr_slctr_y);
    selector.setSize(Vector2f(grid_size_f, grid_size_f));
    selector.setFillColor(Color::Transparent);
    selector.setOutlineThickness(1.f);
    selector.setOutlineColor(Color::Green);

    // Mouse texture selector
    textureRect.width = static_cast<int>(grid_size_f);
    textureRect.height = static_cast<int>(grid_size_f);

    if (!hideBtnIcon.loadFromFile("Assets/Images/Icons/texture_selector_icon.png"))
        ErrorHandler::throwErr("GUI::TEXTURESELECTOR::TEXTURESELECTOR::ERR_COULD_NOT_LOAD_TEXTURE_SELECTOR_ICON");

    hideBtn = new gui::Button(
        btn_x, btn_y, btn_width, btn_height,
        &hideBtnIcon, btn_width, btn_height,
        Color(70, 70, 70, 0), Color(255, 255, 255, 100), Color(255, 255, 255, 200));
}

gui::TextureSelector::~TextureSelector()
{
    delete hideBtn;
}

/* FUNCTIONS ==================================================================================================== */

void gui::TextureSelector::update(const float &dt, const Vector2i mouse_pos_window)
{
    updateMousetime(dt);

    hideBtn->update(Vector2f(mouse_pos_window));

    if (hideBtn->isPressed() && hasCompletedMousetimeCycle())
        hidden = !hidden;

    if (!hidden)
    {
        active = bounds.getGlobalBounds().contains(Vector2f(mouse_pos_window));

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

void gui::TextureSelector::render(RenderTarget &target)
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

const IntRect &gui::TextureSelector::getTextureRect() const
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
    const Texture *texture_sheet,
    Font &font, VideoMode &vm)
    : mousetime(0.f), mousetimeMax(10.f), vm(vm)
{
    gridSizeF = grid_size_f;
    this->scale = scale;

    active = false;
    hidden = true;
    editing = false;

    offsets = Vector2f(0.f, 0.f);
    dimensions = Vector2f(grid_size_f, grid_size_f);

    // Texture rectangle
    textureRect.width = static_cast<int>(grid_size_f);
    textureRect.height = static_cast<int>(grid_size_f);

    if (!hideBtnIcon.loadFromFile("Assets/Images/Icons/collision_editor_icon.png"))
        ErrorHandler::throwErr("GUI::COLLISIONEDITOR::COLLISIONEDITOR::ERR_COULD_NOT_LOAD_COLLISION_EDITOR_ICON\n");

    hideBtn = new gui::Button(
        btn_x, btn_y, btn_width, btn_height,
        &hideBtnIcon, btn_width, btn_height,
        Color(70, 70, 70, 0), Color(255, 255, 255, 100), Color(255, 255, 255, 200));

    // Background
    editorBg.setSize(Vector2f(gridSizeF * scale * 2.f, gridSizeF * scale * 2.f));
    editorBg.setFillColor(Color(100, 100, 100, 100));
    editorBg.setOutlineThickness(1.f);
    editorBg.setOutlineColor(Color(100, 100, 100, 150));
    editorBg.setPosition(col_editor_x, col_editor_y);

    // Tile
    editorTile.setTexture(texture_sheet);
    editorTile.setTextureRect(textureRect);
    editorTile.setSize(Vector2f(gridSizeF * scale, gridSizeF * scale));
    editorTile.setPosition(editorBg.getPosition().x + editorBg.getSize().x / 2.f - editorTile.getSize().x / 2.f,
                           editorBg.getPosition().y + editorBg.getSize().y / 2.f - editorTile.getSize().y / 2.f);
    // Collision box
    editorCollBox.setSize(Vector2f(gridSizeF * scale, gridSizeF * scale));
    editorCollBox.setFillColor(Color(255, 100, 100, 100));
    editorCollBox.setOutlineThickness(1.f);
    editorCollBox.setOutlineColor(Color(255, 100, 100, 150));
    editorCollBox.setPosition(editorTile.getPosition());

    // Input labels
    inputLabels.setFont(font);
    inputLabels.setCharacterSize(gui::calc_char_size(vm, 140));
    inputLabels.setFillColor(Color(255, 255, 255, 150));
    inputLabels.setString("Width\n\n\nHeight\n\n\nOffset X\n\n\nOffset Y");
    inputLabels.setPosition(Vector2f(
        editorBg.getPosition().x + editorBg.getSize().x + gui::p2pX(vm, 2.f),
        editorBg.getPosition().y - gui::calc_char_size(vm, 140)));

    // Inputs
    incrementInputs["WIDTH"] = new gui::IncrementInput(
        editorBg.getPosition().x + editorBg.getSize().x + gui::p2pX(vm, 2.f),
        editorBg.getPosition().y,
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 3.75f), 1.f, Color(100, 100, 100, 100),
        Color(70, 70, 70, 200), Color(255, 255, 255, 100), Color(255, 255, 255, 200),
        font, Color(255, 255, 255, 255), gui::calc_char_size(vm, 140), grid_size_f);

    incrementInputs["HEIGHT"] = new gui::IncrementInput(
        editorBg.getPosition().x + editorBg.getSize().x + gui::p2pX(vm, 2.f),
        editorBg.getPosition().y + gui::p2pY(vm, 6.3f),
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 3.75f), 1.f, Color(100, 100, 100, 100),
        Color(70, 70, 70, 200), Color(255, 255, 255, 100), Color(255, 255, 255, 200),
        font, Color(255, 255, 255, 255), gui::calc_char_size(vm, 140), grid_size_f);

    incrementInputs["OFFSET_X"] = new gui::IncrementInput(
        editorBg.getPosition().x + editorBg.getSize().x + gui::p2pX(vm, 2.f),
        editorBg.getPosition().y + gui::p2pY(vm, 12.7f),
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 3.75f), 1.f, Color(100, 100, 100, 100),
        Color(70, 70, 70, 200), Color(255, 255, 255, 100), Color(255, 255, 255, 200),
        font, Color(255, 255, 255, 255), gui::calc_char_size(vm, 140), 0.f);

    incrementInputs["OFFSET_Y"] = new gui::IncrementInput(
        editorBg.getPosition().x + editorBg.getSize().x + gui::p2pX(vm, 2.f),
        editorBg.getPosition().y + gui::p2pY(vm, 19.1f),
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 3.75f), 1.f, Color(100, 100, 100, 100),
        Color(70, 70, 70, 200), Color(255, 255, 255, 100), Color(255, 255, 255, 200),
        font, Color(255, 255, 255, 255), gui::calc_char_size(vm, 140), 0.f);

    // Reset button
    resetBtn = new Button(
        editorBg.getPosition().x + editorBg.getSize().x + gui::p2pX(vm, 2.f),
        editorBg.getPosition().y + gui::p2pY(vm, 25.5f),
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 3.75f), font, "Reset", gui::calc_char_size(vm, 130),
        Color(255, 255, 255, 150), Color(255, 255, 255, 200), Color(255, 255, 255, 255),
        Color(70, 70, 70, 200), Color(255, 255, 255, 100), Color(255, 255, 255, 200));
}

gui::CollisionEditor::~CollisionEditor()
{
    delete hideBtn;

    for (auto &it : incrementInputs)
        delete it.second;

    delete resetBtn;
}

/* FUNCTIONS =================================================================================================== */

void gui::CollisionEditor::update(const float &dt, Vector2i mouse_pos_window, IntRect &texture_rect)
{
    updateMousetime(dt);

    hideBtn->update(Vector2f(mouse_pos_window));
    resetBtn->update(Vector2f(mouse_pos_window));

    updateInput();

    if (hideBtn->isPressed() && hasCompletedMousetimeCycle())
        editing = !editing;

    textureRect = texture_rect;

    editorTile.setTextureRect(textureRect);

    if (editing)
    {
        for (auto &it : incrementInputs)
            it.second->update(dt, static_cast<Vector2f>(mouse_pos_window));

        offsets.x = incrementInputs.at("OFFSET_X")->getValue();
        offsets.y = incrementInputs.at("OFFSET_Y")->getValue();

        dimensions.x = incrementInputs.at("WIDTH")->getValue();
        dimensions.y = incrementInputs.at("HEIGHT")->getValue();

        editorCollBox.setSize(Vector2f(dimensions.x * scale, dimensions.y * scale));
        editorCollBox.setPosition(editorTile.getPosition().x + offsets.x * scale,
                                  editorTile.getPosition().y + offsets.y * scale);
    }
}

void gui::CollisionEditor::render(RenderTarget &target)
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

const Vector2f &gui::CollisionEditor::getDimensions() const
{
    return dimensions;
}

const Vector2f &gui::CollisionEditor::getOffsets() const
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
    const Color bg_color, const Color text_color,
    const Font &font, const unsigned char_size,
    const string string)
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
        bar.getPosition().x + bar.getSize().x / 2.f - roundf(barText.getGlobalBounds().width / 2.f),
        bar.getPosition().y + bar.getSize().y / 2.f - floor(barText.getGlobalBounds().height / 2.f + 2.f));
}

gui::SolidBar::~SolidBar()
{
}

/* FUNCTIONS ==================================================================================================== */

void gui::SolidBar::update()
{
}

void gui::SolidBar::render(RenderTarget &target)
{
    target.draw(bar);
    target.draw(barText);
}

/* MODIFIERS ==================================================================================================== */

void gui::SolidBar::setString(const string string)
{
    barText.setString(string);

    // Center bar text in the bar.
    barText.setPosition(
        bar.getPosition().x + bar.getSize().x / 2.f - roundf(barText.getGlobalBounds().width / 2.f),
        bar.getPosition().y + bar.getSize().y / 2.f - floor(barText.getGlobalBounds().height / 2.f + 2.f));
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
    const Color bg_color, const Color fill_color,
    Font &font, const Color text_color,
    const unsigned char_size, const string string)
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
        barBg.getPosition().y + barBg.getSize().y / 2.f - floor(barText.getGlobalBounds().height / 2.f + 2.f));
}

gui::ProgressBar::ProgressBar(
    const float x, const float y,
    const float width, const float height,
    const float current_value, const float max_value,
    const Color bg_color, const Color fill_color)
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

void gui::ProgressBar::render(RenderTarget &target)
{
    target.draw(barBg);
    target.draw(barFill);

    if (barText.getFont())
        target.draw(barText);
}

const Vector2f &gui::ProgressBar::getPosition() const
{
    return barBg.getPosition();
}

/* MODIFIERS ==================================================================================================== */

void gui::ProgressBar::setString(const string string)
{
    if (barText.getFont())
    {
        barText.setString(string);

        // Center bar text in the bar.
        barText.setPosition(
            barBg.getPosition().x + barBg.getSize().x / 10.f,
            barBg.getPosition().y + barBg.getSize().y / 2.f - floor(barText.getGlobalBounds().height / 2.f + 2.f));
    }
}

void gui::ProgressBar::setProgress(const float percent)
{
    setCurrentValue(maxValue * percent);

    barFill.setSize(Vector2f(
        static_cast<float>(floor(barMaxSize.x * percent)),
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