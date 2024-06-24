#include "stdafx.h"
#include "DefaultEditorMode.h"

/* INITIALIZERS ================================================================================================== */

void DefaultEditorMode::initVariables()
{
    textureRect = sf::IntRect(0, 0, static_cast<int>(data->gridSize), static_cast<int>(data->gridSize));

    collision = false;

    collBoxWidth = data->gridSize;
    collBoxHeight = data->gridSize;
    collBoxOffsetX = 0.f;
    collBoxOffsetY = 0.f;

    type = TileType::DEFAULT;

    layer = 0;

}

void DefaultEditorMode::initGUI()
{
    // Cursor text
    cursorText.setFont(*editorData->font);
    cursorText.setCharacterSize(12);

    // Sidebar
    sidebar.setSize(sf::Vector2f(data->gridSize, data->gfxSettings->resolution.height));
    sidebar.setFillColor(sf::Color(50, 50, 50, 100));
    sidebar.setOutlineThickness(1.f);
    sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));

    // Tile world selector
    selectorRect.setSize(sf::Vector2f(data->gridSize, data->gridSize));
    selectorRect.setFillColor(sf::Color(255, 255, 255, 200));
    selectorRect.setOutlineColor(sf::Color::Yellow);
    selectorRect.setOutlineThickness(1.f);
    selectorRect.setTexture(editorData->tileMap->getTileTextureSheet());
    selectorRect.setTextureRect(textureRect);

    // Tile collision box world selector
    collisionRect.setSize(sf::Vector2f(collBoxWidth, collBoxHeight));
    collisionRect.setFillColor(sf::Color(255, 100, 100, 100));
    collisionRect.setOutlineThickness(1.f);
    collisionRect.setOutlineColor(sf::Color::Red);

    // Texture selector
    textureSelector = new gui::TextureSelector(
        sidebar.getSize().x / 2.f - 50.f / 2.f, gui::p2pY(data->gfxSettings->resolution, 1.f),
        50.f, 50.f,
        sidebar.getSize().x + gui::p2pY(data->gfxSettings->resolution, 2.5f),
        gui::p2pY(data->gfxSettings->resolution, 2.5f),
        960.f, 640.f,
        data->gridSize, editorData->tileMap->getTileTextureSheet());

    // Collision editor
    collisionEditor = new gui::CollisionEditor(
        sidebar.getSize().x / 2.f - 50.f / 2.f, 50.f + gui::p2pY(data->gfxSettings->resolution, 2.f),
        50.f, 50.f,
        sidebar.getSize().x + gui::p2pY(data->gfxSettings->resolution, 2.5f),
        gui::p2pY(data->gfxSettings->resolution, 5.f),
        640.f, 640.f,
        data->gridSize, 2.f, editorData->tileMap->getTileTextureSheet(),
        *editorData->font, data->gfxSettings->resolution);
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

DefaultEditorMode::DefaultEditorMode(StateData *data, EditorStateData *editor_data)
    : EditorMode(data, editor_data, "Default Editor Mode")
{
    initVariables();
    initGUI();
}

DefaultEditorMode::~DefaultEditorMode()
{
    delete textureSelector;
    delete collisionEditor;
}

/* FUNCTIONS ======================================================================================================= */

void DefaultEditorMode::update(const float &dt)
{
    updateInput(dt);
    updateGUI(dt);
}

void DefaultEditorMode::render(sf::RenderTarget &target)
{
    renderGUI(target);
}

void DefaultEditorMode::updateInput(const float &dt)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!sidebar.getGlobalBounds().contains(sf::Vector2f(*editorData->mousePosWindow)))
        {
            if (!textureSelector->isActive())
                textureSelector->close();

            else
                textureRect = textureSelector->getTextureRect();

            if (collisionEditor->isVisible())
            {
                // Update collision box offsets and dimensions.
                collBoxWidth = collisionEditor->getDimensions().x;
                collBoxHeight = collisionEditor->getDimensions().y;

                collBoxOffsetX = collisionEditor->getOffsets().x;
                collBoxOffsetY = collisionEditor->getOffsets().y;
            }

            if (!textureSelector->isActive() && !collisionEditor->isVisible())
            {
                editorData->tileMap->addTile(editorData->mousePosGrid->x, editorData->mousePosGrid->y,
                                             0, textureRect,
                                             collision,
                                             collBoxWidth, collBoxHeight,
                                             collBoxOffsetX, collBoxOffsetY,
                                             static_cast<TileType>(type));
            }
        }
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && hasCompletedKeytimeCicle())
    {
        if (!sidebar.getGlobalBounds().contains(sf::Vector2f(*editorData->mousePosWindow)))
        {
            if (!textureSelector->isActive())
            {
                textureSelector->close();

                editorData->tileMap->removeTile(editorData->mousePosGrid->x, editorData->mousePosGrid->y, 0);
            }
        }
    }

    // Toggle collision
    if (sf::Keyboard::isKeyPressed(editorData->keybinds->at("TOGGLE_COLLISION")) && hasCompletedKeytimeCicle())
    {
        collision = !collision;
    }
    // Type increase
    else if (sf::Keyboard::isKeyPressed(editorData->keybinds->at("INCREASE_TYPE")) && hasCompletedKeytimeCicle())
    {
        if (static_cast<TileType>(type + 1) != TileType::SPAWNER)
            type++;
    }
    // Type decrease
    else if (sf::Keyboard::isKeyPressed(editorData->keybinds->at("DECREASE_TYPE")) && hasCompletedKeytimeCicle())
    {
        if (static_cast<TileType>(type - 1) != TileType::SPAWNER && type > 0)
            type--;
    }
}

void DefaultEditorMode::updateGUI(const float &dt)
{
    textureSelector->update(dt, *editorData->mousePosWindow);
    collisionEditor->update(dt, *editorData->mousePosWindow, textureRect);

    if (!textureSelector->isActive())
    {
        selectorRect.setPosition(
            editorData->mousePosGrid->x * data->gridSize,
            editorData->mousePosGrid->y * data->gridSize);

        selectorRect.setTextureRect(textureRect);

        collisionRect.setSize(sf::Vector2f(collBoxWidth, collBoxHeight));
        collisionRect.setPosition(
            selectorRect.getPosition().x + collBoxOffsetX,
            selectorRect.getPosition().y + collBoxOffsetY);
    }

    cursorText.setPosition(sf::Vector2f(editorData->mousePosView->x + 40.f, editorData->mousePosView->y));

    std::stringstream ss;
    ss << editorData->mousePosWindow->x << " " << editorData->mousePosWindow->y << "\n"
       << editorData->mousePosGrid->x << " " << editorData->mousePosGrid->y << "\n"
       << textureRect.left << " " << textureRect.top << "\n"
       << "collision: " << (collision ? "true" : "false") << "\n"
       << "type selected: " << getTypeName() << "\n"
       << "stacked tiles: " << editorData->tileMap->getAmountOfStackedTiles(editorData->mousePosGrid->x, editorData->mousePosGrid->y, layer);
    cursorText.setString(ss.str());
}

void DefaultEditorMode::renderGUI(sf::RenderTarget &target)
{
    if (!textureSelector->isActive() && !collisionEditor->isVisible() &&
        !sidebar.getGlobalBounds().contains(sf::Vector2f(*editorData->mousePosWindow)))
    {
        if (editorData->mousePosGrid->x >= 0 && editorData->mousePosGrid->y >= 0)
        {
            // Render selector rect in the editor camera
            target.setView(*editorData->editorCamera);
            target.draw(selectorRect);

            // Render collision rect if collision == true
            if (collision)
                target.draw(collisionRect);
        }
    }

    // Render texture selector, collision editor and sidebar in the window view
    target.setView(data->window->getDefaultView());
    target.draw(sidebar);
    textureSelector->render(target);
    collisionEditor->render(target);

    // Render cursor in the editor camera
    target.setView(*editorData->editorCamera);
    target.draw(cursorText);

    // Render mode indicator text in the window view
    target.setView(data->window->getDefaultView());
    target.draw(modeIndicatorText);
}

/* ACCESSORS ===================================================================================================== */

const bool DefaultEditorMode::hasCompletedKeytimeCicle()
{
    if (*editorData->keytime >= *editorData->keytimeMax)
    {
        *editorData->keytime = 0.f;
        return true;
    }

    return false;
}

const bool DefaultEditorMode::hasCompletedMousetimeCicle(const sf::Mouse::Button mouse_btn)
{
    if (*editorData->keytime >= *editorData->keytimeMax)
    {
        if (sf::Mouse::isButtonPressed(mouse_btn))
            *editorData->keytime = 0.f;

        return true;
    }

    return false;
}

const std::string DefaultEditorMode::getTypeName() const
{
    switch (type)
    {
    case TileType::DEFAULT:
        return "DEFAULT";
        break;
    case TileType::DOODAD:
        return "DOODAD";
        break;
    case TileType::HARMFUL:
        return "HARMFUL";
        break;
    case TileType::SPAWNER:
        return "SPAWNER";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}