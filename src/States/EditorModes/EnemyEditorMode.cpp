#include "stdafx.h"
#include "EnemyEditorMode.h"

/* INITIALIZERS ================================================================================================ */

void EnemyEditorMode::initVariables()
{
    textureRect = sf::IntRect(0, 0, 0, 0);
    enemyType = 0;
    enemyAmount = 5;
    enemyTimeToSpawn = 30;
    enemyMaxDistance = 50;
    enemySpawnAreaSize = 20;
}

void EnemyEditorMode::initGUI()
{
    // Cursor text
    cursorText.setFont(*editorData->font);
    cursorText.setCharacterSize(12);

    // Sidebar
    sidebar.setSize(sf::Vector2f(data->gridSize, data->gfxSettings->resolution.height));
    sidebar.setFillColor(sf::Color(50, 50, 50, 100));
    sidebar.setOutlineThickness(1.f);
    sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));

    // World selector
    selectorRect.setSize(sf::Vector2f(data->gridSize, data->gridSize));
    selectorRect.setFillColor(sf::Color::Transparent);
    selectorRect.setOutlineColor(sf::Color::Red);
    selectorRect.setOutlineThickness(1.f);
}

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

EnemyEditorMode::EnemyEditorMode(StateData *data, EditorStateData *editor_data)
    : EditorMode(data, editor_data, "Enemy Editor Mode")
{
    initVariables();
    initGUI();
}

EnemyEditorMode::~EnemyEditorMode()
{
}

/* FUNCTIONS ================================================================================================== */

void EnemyEditorMode::update(const float &dt)
{
    updateInput(dt);
    updateGUI(dt);
}

void EnemyEditorMode::render(sf::RenderTarget &target)
{
    renderGUI(target);
}

void EnemyEditorMode::updateInput(const float &dt)
{
    // Spawner adding
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!sidebar.getGlobalBounds().contains(sf::Vector2f(*editorData->mousePosWindow)))
        {
            editorData->tileMap->addSpawner(
                editorData->mousePosGrid->x, editorData->mousePosGrid->y, 0,
                sf::IntRect(0, 576, (int)data->gridSize, (int)data->gridSize),
                enemyType, enemyAmount, enemyTimeToSpawn,
                enemyMaxDistance, enemySpawnAreaSize);
        }
    }
    // Spawner removing
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && hasElapsedMouseTimeMax())
    {
        if (!sidebar.getGlobalBounds().contains(sf::Vector2f(*editorData->mousePosWindow)))
        {
            if (editorData->tileMap->compareType(editorData->mousePosGrid->x,
                                                 editorData->mousePosGrid->y, 0,
                                                 TileType::SPAWNER))
            {
                editorData->tileMap->removeTile(editorData->mousePosGrid->x,
                                                editorData->mousePosGrid->y, 0);
            }
        }
    }

    // Enemy type inc/dec
    if (sf::Keyboard::isKeyPressed(editorData->keybinds->at("ENEMY_TYPE_INC")) && hasElapsedKeyTimeMax())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (enemyType > 0)
                enemyType--;
        }
        else
            enemyType++;
    }

    // Enemy amount inc/dec
    else if (sf::Keyboard::isKeyPressed(editorData->keybinds->at("ENEMY_AMOUNT_INC")) && hasElapsedKeyTimeMax())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (enemyAmount > 5)
                enemyAmount--;
        }
        else
            enemyAmount++;
    }

    // Enemy time to spawn inc/dec
    else if (sf::Keyboard::isKeyPressed(editorData->keybinds->at("ENEMY_TIME_TO_SPAWN_INC")) && hasElapsedKeyTimeMax())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (enemyTimeToSpawn > 5)
                enemyTimeToSpawn--;
        }
        else
            enemyTimeToSpawn++;
    }

    // Enemy max distance inc/dec
    else if (sf::Keyboard::isKeyPressed(editorData->keybinds->at("ENEMY_MAX_DISTANCE_INC")) && hasElapsedKeyTimeMax())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (enemyMaxDistance > 10)
                enemyMaxDistance--;
        }
        else
            enemyMaxDistance++;
    }

    // Enemy spawn area size.
    else if (sf::Keyboard::isKeyPressed(editorData->keybinds->at("ENEMY_SPAWN_AREA_SIZE_INC")) && hasElapsedKeyTimeMax())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        {
            if (enemySpawnAreaSize > 5)
                enemySpawnAreaSize--;
        }
        else
            enemySpawnAreaSize++;
    }
}

void EnemyEditorMode::updateGUI(const float &dt)
{
    selectorRect.setPosition(
        editorData->mousePosGrid->x * data->gridSize,
        editorData->mousePosGrid->y * data->gridSize);

    cursorText.setPosition(sf::Vector2f(editorData->mousePosView->x + 40.f, editorData->mousePosView->y));

    std::stringstream cursor_ss;
    cursor_ss << editorData->mousePosWindow->x << " " << editorData->mousePosWindow->y << "\n"
              << editorData->mousePosGrid->x << " " << editorData->mousePosGrid->y << "\n"
              << "stacked tiles: " << editorData->tileMap->getAmountOfStackedTiles(editorData->mousePosGrid->x, editorData->mousePosGrid->y, 0) << "\n"
              << "enemy type: " << enemyType << "\n"
              << "enemy amount: " << enemyAmount << "\n"
              << "time to spawn: " << enemyTimeToSpawn << "\n"
              << "enemy max distance: " << enemyMaxDistance << "\n"
              << "enemy spawn area diam.: " << enemySpawnAreaSize << "\n";

    cursorText.setString(cursor_ss.str());
}

void EnemyEditorMode::renderGUI(sf::RenderTarget &target)
{
    if (editorData->mousePosGrid->x >= 0 && editorData->mousePosGrid->y >= 0)
    {
        // Render selector rect in the editor camera
        target.setView(*editorData->editorCamera);
        target.draw(selectorRect);
    }

    // Render sidebar in the window view
    target.setView(data->window->getDefaultView());
    target.draw(sidebar);

    // Render cursor in the editor camera
    target.setView(*editorData->editorCamera);
    target.draw(cursorText);

    // Render mode indicator text in the window view
    target.setView(data->window->getDefaultView());
    target.draw(modeIndicatorText);
}