#include "stdafx.h"
#include "DefaultEditorMode.h"

/* INITIALIZERS */

void DefaultEditorMode::initVariables()
{
    this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->data->gridSize), static_cast<int>(this->data->gridSize));

    this->collision = false;
    this->type = TileTypes::DEFAULT;

    this->layer = 0;
}

void DefaultEditorMode::initGUI()
{
    // Cursor text
    this->cursorText.setFont(*this->editorData->font);
    this->cursorText.setCharacterSize(12);

    // Sidebar
    this->sidebar.setSize(sf::Vector2f(this->data->gridSize, this->data->gfxSettings->resolution.height));
    this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
    this->sidebar.setOutlineThickness(1.f);
    this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));

    // World selector
    this->selectorRect.setSize(sf::Vector2f(this->data->gridSize, this->data->gridSize));
    this->selectorRect.setFillColor(sf::Color(255, 255, 255, 200));
    this->selectorRect.setOutlineColor(sf::Color::Red);
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setTexture(this->tileMap->getTileTextureSheet());
    this->selectorRect.setTextureRect(this->textureRect);

    // Texture selector
    this->textureSelector = new gui::TextureSelector(
        this->sidebar.getSize().x / 2 - 50.f / 2, gui::p2pY(this->data->gfxSettings->resolution, 5.f),
        50.f, 50.f,
        this->sidebar.getSize().x + gui::p2pY(this->data->gfxSettings->resolution, 2.5f), gui::p2pY(this->data->gfxSettings->resolution, 2.5f),
        960.f, 640.f,
        this->data->gridSize, this->tileMap->getTileTextureSheet());
}

/* CONSTRUCTOR AND DESTRUCTOR */

DefaultEditorMode::DefaultEditorMode(StateData *data, EditorStateData *editor_data, TileMap *tile_map)
    : EditorMode(data, editor_data)
{
    this->tileMap = tile_map;

    this->initVariables();
    this->initGUI();
}

DefaultEditorMode::~DefaultEditorMode()
{
    delete textureSelector;
}

/* FUNCTIONS */

void DefaultEditorMode::update(const float &dt)
{
    this->updateInput(dt);
    this->updateGUI(dt);
}

void DefaultEditorMode::render(sf::RenderTarget &target)
{
    this->renderGUI(target);
}

void DefaultEditorMode::updateInput(const float &dt)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorData->mousePosWindow)))
        {
            if (!this->textureSelector->isActive())
            {
                this->tileMap->addTile(this->editorData->mousePosGrid->x, this->editorData->mousePosGrid->y,
                                       0, this->textureRect,
                                       this->collision, this->type);
            }
            else
            {
                this->textureRect = this->textureSelector->getTextureRect();
            }
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->hasCompletedKeytimeCicle())
    {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorData->mousePosWindow)))
        {
            if (!this->textureSelector->isActive())
                this->tileMap->removeTile(this->editorData->mousePosGrid->x, this->editorData->mousePosGrid->y, 0);
        }
    }

    // Toggle collision
    if (sf::Keyboard::isKeyPressed(this->editorData->keybinds->at("TOGGLE_COLLISION")) && this->hasCompletedKeytimeCicle())
    {
        this->collision = !this->collision;
    }
    // Type increase
    else if (sf::Keyboard::isKeyPressed(this->editorData->keybinds->at("INCREASE_TYPE")) && this->hasCompletedKeytimeCicle())
    {
        this->type++;
    }
    // Type decrease
    else if (sf::Keyboard::isKeyPressed(this->editorData->keybinds->at("DECREASE_TYPE")) && this->hasCompletedKeytimeCicle())
    {
        if (this->type > 0)
            this->type--;
    }
}

void DefaultEditorMode::updateGUI(const float &dt)
{
    this->textureSelector->update(dt, *this->editorData->mousePosWindow);

    if (!this->textureSelector->isActive())
    {
        this->selectorRect.setPosition(
            this->editorData->mousePosGrid->x * this->data->gridSize,
            this->editorData->mousePosGrid->y * this->data->gridSize);

        this->selectorRect.setTextureRect(this->textureRect);
    }

    this->cursorText.setPosition(sf::Vector2f(this->editorData->mousePosView->x + 40.f, this->editorData->mousePosView->y));

    std::stringstream ss;
    ss << this->editorData->mousePosWindow->x << " " << this->editorData->mousePosWindow->y << "\n"
       << this->editorData->mousePosGrid->x << " " << this->editorData->mousePosGrid->y << "\n"
       << this->textureRect.left << " " << this->textureRect.top << "\n"
       << "collision: " << (this->collision ? "true" : "false") << "\n"
       << "type selected: " << this->getTypeName() << "\n"
       << "stacked tiles: " << this->tileMap->getAmountOfStackedTiles(this->editorData->mousePosGrid->x, this->editorData->mousePosGrid->y, this->layer);
    this->cursorText.setString(ss.str());
}

void DefaultEditorMode::renderGUI(sf::RenderTarget &target)
{
    if (!this->textureSelector->isActive() && !this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorData->mousePosWindow)))
    {
        // Render selector rect in the editor camera
        target.setView(*this->editorData->editorCamera);
        target.draw(this->selectorRect);
    }

    // Render texture selector and sidebar in the window view
    target.setView(this->data->window->getDefaultView());
    this->textureSelector->render(target);
    target.draw(this->sidebar);

    // Render cursor text in the editor camera
    target.setView(*this->editorData->editorCamera);
    target.draw(this->cursorText);
}

const bool DefaultEditorMode::hasCompletedKeytimeCicle()
{
    if (*this->editorData->keytime >= *this->editorData->keytimeMax)
    {
        *this->editorData->keytime = 0.f;
        return true;
    }

    return false;
}

const bool DefaultEditorMode::hasCompletedMousetimeCicle(const sf::Mouse::Button mouseBtn)
{
    if (*this->editorData->keytime >= *this->editorData->keytimeMax)
    {
        if (sf::Mouse::isButtonPressed(mouseBtn))
            *this->editorData->keytime = 0.f;

        return true;
    }

    return false;
}

const std::string DefaultEditorMode::getTypeName() const
{
    switch (this->type)
    {
    case TileTypes::DEFAULT:
        return "DEFAULT";
        break;
    case TileTypes::DOODAD:
        return "DOODAD";
        break;
    case TileTypes::HARMFUL:
        return "HARMFUL";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}