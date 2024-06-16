#include "stdafx.h"
#include "EnemyEditorMode.h"

/* INITIALIZERS ================================================================================= */

void EnemyEditorMode::initVariables()
{
}

void EnemyEditorMode::initGUI()
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
    this->selectorRect.setFillColor(sf::Color::Transparent);
    this->selectorRect.setOutlineColor(sf::Color::Red);
    this->selectorRect.setOutlineThickness(1.f);
}

/* CONSTRUCTOR AND DESTRUCTOR =================================================================== */

EnemyEditorMode::EnemyEditorMode(StateData *data, EditorStateData *editor_data, TileMap *tile_map)
    : EditorMode(data, editor_data), tileMap(tile_map)
{
    this->initVariables();
    this->initGUI();
}

EnemyEditorMode::~EnemyEditorMode()
{
}

/* FUNCTIONS ===================================================================================== */

void EnemyEditorMode::update(const float &dt)
{
    this->updateInput(dt);
    this->updateGUI(dt);
}

void EnemyEditorMode::render(sf::RenderTarget &target)
{
    this->renderGUI(target);
}

void EnemyEditorMode::updateInput(const float &dt)
{
}

void EnemyEditorMode::updateGUI(const float &dt)
{
    this->selectorRect.setPosition(
        this->editorData->mousePosGrid->x * this->data->gridSize,
        this->editorData->mousePosGrid->y * this->data->gridSize);

    this->cursorText.setPosition(sf::Vector2f(this->editorData->mousePosView->x + 40.f, this->editorData->mousePosView->y));

    std::stringstream cursor_ss;
    cursor_ss << this->editorData->mousePosWindow->x << " " << this->editorData->mousePosWindow->y << "\n"
              << this->editorData->mousePosGrid->x << " " << this->editorData->mousePosGrid->y << "\n";

    this->cursorText.setString(cursor_ss.str());
}

void EnemyEditorMode::renderGUI(sf::RenderTarget &target)
{
    if (this->editorData->mousePosGrid->x >= 0 && this->editorData->mousePosGrid->y >= 0)
    {
        // Render selector rect in the editor camera
        target.setView(*this->editorData->editorCamera);
        target.draw(this->selectorRect);
    }

    // Render sidebar in the window view
    target.setView(this->data->window->getDefaultView());
    target.draw(this->sidebar);

    // Render cursor text in the editor camera
    target.setView(*this->editorData->editorCamera);
    target.draw(this->cursorText);
}

/* ACCESSORS ====================================================================================== */

const bool EnemyEditorMode::hasCompletedKeytimeCicle()
{
    if (*this->editorData->keytime >= *this->editorData->keytimeMax)
    {
        *this->editorData->keytime = 0.f;
        return true;
    }

    return false;
}

const bool EnemyEditorMode::hasCompletedMousetimeCicle(const sf::Mouse::Button mouseBtn)
{
    if (*this->editorData->keytime >= *this->editorData->keytimeMax)
    {
        if (sf::Mouse::isButtonPressed(mouseBtn))
            *this->editorData->keytime = 0.f;

        return true;
    }

    return false;
}
