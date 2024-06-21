#include "stdafx.h"
#include "EnemyEditorMode.h"

/* INITIALIZERS ================================================================================================ */

void EnemyEditorMode::initVariables()
{
    this->textureRect = sf::IntRect(0, 0, 0, 0);
    this->enemyType = 0;
    this->enemyAmount = 5;
    this->enemyTimeToSpawn = 60;
    this->enemyMaxDistance = 500;
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

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

EnemyEditorMode::EnemyEditorMode(StateData *data, EditorStateData *editor_data)
    : EditorMode(data, editor_data, "Enemy Editor Mode")
{
    this->initVariables();
    this->initGUI();
}

EnemyEditorMode::~EnemyEditorMode()
{
}

/* FUNCTIONS ================================================================================================== */

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
    // Spawner adding
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorData->mousePosWindow)))
        {
            this->editorData->tileMap->addSpawner(
                this->editorData->mousePosGrid->x, this->editorData->mousePosGrid->y, 0,
                sf::IntRect(0, 576, (int)this->data->gridSize, (int)this->data->gridSize),
                this->enemyType, this->enemyAmount, this->enemyTimeToSpawn, this->enemyMaxDistance);
        }
    }
    // Spawner removing
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->hasCompletedKeytimeCicle())
    {
        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(*this->editorData->mousePosWindow)))
        {
            if (this->editorData->tileMap->compareType(this->editorData->mousePosGrid->x,
                                                       this->editorData->mousePosGrid->y, 0,
                                                       TileType::SPAWNER))
            {
                this->editorData->tileMap->removeTile(this->editorData->mousePosGrid->x,
                                                      this->editorData->mousePosGrid->y, 0);
            }
        }
    }

    // Enemy type inc/dec
    if (sf::Keyboard::isKeyPressed(this->editorData->keybinds->at("ENEMY_TYPE_INC")) && this->hasCompletedKeytimeCicle())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (this->enemyType > 0)
                this->enemyType--;
        }
        else
            this->enemyType++;
    }

    // Enemy amount inc/dec
    else if (sf::Keyboard::isKeyPressed(this->editorData->keybinds->at("ENEMY_AMOUNT_INC")) && this->hasCompletedKeytimeCicle())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (this->enemyAmount > 5)
                this->enemyAmount--;
        }
        else
            this->enemyAmount++;
    }

    // Enemy time to spawn inc/dec
    else if (sf::Keyboard::isKeyPressed(this->editorData->keybinds->at("ENEMY_TIME_TO_SPAWN_INC")) && this->hasCompletedKeytimeCicle())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (this->enemyTimeToSpawn > 30)
                this->enemyTimeToSpawn--;
        }
        else
            this->enemyTimeToSpawn++;
    }

    // Enemy max distance inc/dec
    else if (sf::Keyboard::isKeyPressed(this->editorData->keybinds->at("ENEMY_MAX_DISTANCE_INC")) && this->hasCompletedKeytimeCicle())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (this->enemyMaxDistance > 50)
                this->enemyMaxDistance--;
        }
        else
            this->enemyMaxDistance++;
    }
}

void EnemyEditorMode::updateGUI(const float &dt)
{
    this->selectorRect.setPosition(
        this->editorData->mousePosGrid->x * this->data->gridSize,
        this->editorData->mousePosGrid->y * this->data->gridSize);

    this->cursorText.setPosition(sf::Vector2f(this->editorData->mousePosView->x + 40.f, this->editorData->mousePosView->y));

    std::stringstream cursor_ss;
    cursor_ss << this->editorData->mousePosWindow->x << " " << this->editorData->mousePosWindow->y << "\n"
              << this->editorData->mousePosGrid->x << " " << this->editorData->mousePosGrid->y << "\n"
              << "stacked tiles: " << this->editorData->tileMap->getAmountOfStackedTiles(this->editorData->mousePosGrid->x, this->editorData->mousePosGrid->y, 0) << "\n"
              << "enemy type: " << this->enemyType << "\n"
              << "enemy amount: " << this->enemyAmount << "\n"
              << "time to spawn: " << this->enemyTimeToSpawn << "\n"
              << "enemy max distance: " << this->enemyMaxDistance << "\n";

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

    // Render cursor in the editor camera
    target.setView(*this->editorData->editorCamera);
    target.draw(this->cursorText);

    // Render mode indicator text in the window view
    target.setView(this->data->window->getDefaultView());
    target.draw(this->modeIndicatorText);
}

/* ACCESSORS ================================================================================================= */

const bool EnemyEditorMode::hasCompletedKeytimeCicle()
{
    if (*this->editorData->keytime >= *this->editorData->keytimeMax)
    {
        *this->editorData->keytime = 0.f;
        return true;
    }

    return false;
}

const bool EnemyEditorMode::hasCompletedMousetimeCicle(const sf::Mouse::Button mouse_btn)
{
    if (*this->editorData->keytime >= *this->editorData->keytimeMax)
    {
        if (sf::Mouse::isButtonPressed(mouse_btn))
            *this->editorData->keytime = 0.f;

        return true;
    }

    return false;
}
