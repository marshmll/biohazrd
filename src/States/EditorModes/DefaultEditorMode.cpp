#include "stdafx.h"
#include "DefaultEditorMode.h"

/* INITIALIZERS ================================================================================================== */

void DefaultEditorMode::initVariables()
{
    this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->data->gridSize), static_cast<int>(this->data->gridSize));

    this->collision = false;

    this->collBoxWidth = this->data->gridSize;
    this->collBoxHeight = this->data->gridSize;
    this->collBoxOffsetX = 0.f;
    this->collBoxOffsetY = 0.f;

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
    this->selectorRect.setTexture(this->editorData->tileMap->getTileTextureSheet());
    this->selectorRect.setTextureRect(this->textureRect);

    // Texture selector
    this->textureSelector = new gui::TextureSelector(
        this->sidebar.getSize().x / 2.f - 50.f / 2.f, gui::p2pY(this->data->gfxSettings->resolution, 1.f),
        50.f, 50.f,
        this->sidebar.getSize().x + gui::p2pY(this->data->gfxSettings->resolution, 2.5f),
        gui::p2pY(this->data->gfxSettings->resolution, 2.5f),
        960.f, 640.f,
        this->data->gridSize, this->editorData->tileMap->getTileTextureSheet());

    // Collision editor
    this->collisionEditor = new gui::CollisionEditor(
        this->sidebar.getSize().x / 2.f - 50.f / 2.f, 50.f + gui::p2pY(this->data->gfxSettings->resolution, 2.f),
        50.f, 50.f,
        this->sidebar.getSize().x + gui::p2pY(this->data->gfxSettings->resolution, 2.5f),
        gui::p2pY(this->data->gfxSettings->resolution, 5.f),
        640.f, 640.f,
        this->data->gridSize, this->editorData->tileMap->getTileTextureSheet(),
        this->editorData->font, this->data->gfxSettings->resolution);
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

DefaultEditorMode::DefaultEditorMode(StateData *data, EditorStateData *editor_data)
    : EditorMode(data, editor_data, "Default Editor Mode")
{
    this->initVariables();
    this->initGUI();
}

DefaultEditorMode::~DefaultEditorMode()
{
    delete textureSelector;
    delete collisionEditor;
}

/* FUNCTIONS ======================================================================================================= */

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
                this->textureSelector->close();

            else
                this->textureRect = this->textureSelector->getTextureRect();

            if (this->collisionEditor->isVisible())
            {
                // Update collision box offsets and dimensions.
                this->collBoxWidth = this->collisionEditor->getDimensions().x;
                this->collBoxHeight = this->collisionEditor->getDimensions().y;

                this->collBoxOffsetX = this->collisionEditor->getOffsets().x;
                this->collBoxOffsetY = this->collisionEditor->getOffsets().y;
            }

            if (!this->textureSelector->isActive() && !this->collisionEditor->isVisible())
            {
                this->editorData->tileMap->addTile(this->editorData->mousePosGrid->x, this->editorData->mousePosGrid->y,
                                                   0, this->textureRect,
                                                   this->collision,
                                                   this->collBoxWidth, this->collBoxHeight,
                                                   this->collBoxOffsetX, this->collBoxOffsetY,
                                                   this->type);
            }
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->hasCompletedKeytimeCicle())
    {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorData->mousePosWindow)))
        {
            if (!this->textureSelector->isActive())
            {
                this->textureSelector->close();

                this->editorData->tileMap->removeTile(this->editorData->mousePosGrid->x, this->editorData->mousePosGrid->y, 0);
            }
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
    this->collisionEditor->update(dt, *this->editorData->mousePosWindow, this->textureRect);

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
       << "stacked tiles: " << this->editorData->tileMap->getAmountOfStackedTiles(this->editorData->mousePosGrid->x, this->editorData->mousePosGrid->y, this->layer);
    this->cursorText.setString(ss.str());
}

void DefaultEditorMode::renderGUI(sf::RenderTarget &target)
{
    if (!this->textureSelector->isActive() && !this->collisionEditor->isVisible() &&
        !this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorData->mousePosWindow)))
    {
        if (this->editorData->mousePosGrid->x >= 0 && this->editorData->mousePosGrid->y >= 0)
        {
            // Render selector rect in the editor camera
            target.setView(*this->editorData->editorCamera);
            target.draw(this->selectorRect);
        }
    }

    // Render texture selector, collision editor and sidebar in the window view
    target.setView(this->data->window->getDefaultView());
    target.draw(this->sidebar);
    this->textureSelector->render(target);
    this->collisionEditor->render(target);

    // Render cursor in the editor camera
    target.setView(*this->editorData->editorCamera);
    target.draw(this->cursorText);

    // Render mode indicator text in the window view
    target.setView(this->data->window->getDefaultView());
    target.draw(this->modeIndicatorText);
}

/* ACCESSORS ===================================================================================================== */

const bool DefaultEditorMode::hasCompletedKeytimeCicle()
{
    if (*this->editorData->keytime >= *this->editorData->keytimeMax)
    {
        *this->editorData->keytime = 0.f;
        return true;
    }

    return false;
}

const bool DefaultEditorMode::hasCompletedMousetimeCicle(const sf::Mouse::Button mouse_btn)
{
    if (*this->editorData->keytime >= *this->editorData->keytimeMax)
    {
        if (sf::Mouse::isButtonPressed(mouse_btn))
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
    case TileTypes::SPAWNER:
        return "SPAWNER";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}