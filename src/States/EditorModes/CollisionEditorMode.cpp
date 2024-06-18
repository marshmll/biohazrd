#include "stdafx.h"
#include "CollisionEditorMode.h"

/* INITIALIZERS =============================================================================== */

void CollisionEditorMode::initVariables()
{
}

void CollisionEditorMode::initGUI()
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

/* CONSTRUCTOR AND DESTRUCTOR ================================================================== */

CollisionEditorMode::CollisionEditorMode(StateData *data, EditorStateData *editor_data)
    : EditorMode(data, editor_data, "Collision Editor Mode")
{
    this->initVariables();
    this->initGUI();
}

CollisionEditorMode::~CollisionEditorMode()
{
}

/* FUNCTIONS ===================================================================================== */

void CollisionEditorMode::update(const float &dt)
{
    this->updateInput(dt);
    this->updateGUI(dt);
}

void CollisionEditorMode::render(sf::RenderTarget &target)
{
    this->renderGUI(target);
}

void CollisionEditorMode::updateInput(const float &dt)
{
}

void CollisionEditorMode::updateGUI(const float &dt)
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

void CollisionEditorMode::renderGUI(sf::RenderTarget &target)
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

    // Render cursor in the editor camera
    target.setView(*this->editorData->editorCamera);
    target.draw(this->cursorText);

    // Render mode indicator text in the window view
    target.setView(this->data->window->getDefaultView());
    target.draw(this->modeIndicatorText);
}

/* ACCESSORS ===================================================================================== */

const bool CollisionEditorMode::hasCompletedKeytimeCicle()
{
    if (*this->editorData->keytime >= *this->editorData->keytimeMax)
    {
        *this->editorData->keytime = 0.f;
        return true;
    }

    return false;
}

const bool CollisionEditorMode::hasCompletedMousetimeCicle(const sf::Mouse::Button mouse_btn)
{
    if (*this->editorData->keytime >= *this->editorData->keytimeMax)
    {
        if (sf::Mouse::isButtonPressed(mouse_btn))
            *this->editorData->keytime = 0.f;

        return true;
    }

    return false;
}
