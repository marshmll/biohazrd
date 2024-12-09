/*
 * GameState class that extends State class.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
#include "GameState.h"

/* INITIALIZERS ================================================================================================== */

void GameState::initVariables()
{
    showDebugStats = false;
}

void GameState::initBufferedRender()
{
    renderBuffer.create(vm.width, vm.height);

    renderSprite.setTexture(renderBuffer.getTexture());

    renderSprite.setTextureRect(sf::IntRect(0, 0, vm.width, vm.height));
}

void GameState::initPlayerCamera()
{
    playerCamera.setSize(sf::Vector2f(vm.width, vm.height));

    playerCamera.setCenter(vm.width / 2.f, vm.height / 2.f);
}

void GameState::initKeybinds()
{
    IniParser parser;

    parser.loadFromFile("Config/keybinds.ini");

    for (auto &[action, key] : parser.getAllPropertiesFrom("GameState"))
        keybinds[action] = acceptedKeys->at(key);

    data->logger->log("GameState::initKeybinds", INFO,
                      "Initialized " + std::to_string(keybinds.size()) + " keybinds.");
}

void GameState::initFonts()
{
    if (!font.loadFromFile("Fonts/VCR_OSD_MONO_1.001.ttf"))
    {
        data->logger->log("GameState::initFonts", ERROR, "Could not load fonts.");
        ErrorHandler::throwErr("ERROR::GAMESTATE::INITFONTS::COULD_NOT_LOAD_FONT\n");
    }

    data->logger->log("GameState::initFonts", DEBUG, "Successfully loaded fonts.");
}

void GameState::initText()
{
    debugText.setFont(font);
    debugText.setCharacterSize(gui::calc_char_size(vm, 135));
    debugText.setPosition(gui::p2pX(vm, 1.f), gui::p2pY(vm, 1.f));
}

void GameState::initTextures()
{
    IniParser parser;

    parser.loadFromFile("Config/textures.ini");

    for (auto &[key, path] : parser.getAllProperties())
    {
        if (!textures[key].loadFromFile(path))
        {
            data->logger->log("GameState::initTextures", ERROR, "Could not load texture: " + key);
            ErrorHandler::throwErr("ERROR::GAMESTATE::INITTEXTURES::COULD_NOT_LOAD_TEXTURE");
        }
    }

    data->logger->log("GameState::initTextures", DEBUG, "Successfully loaded textures.");
}

void GameState::initShaders()
{
    ambientLight = sf::Vector3f(.2f, .2f, .2f);

    if (!coreShader.loadFromFile("Shaders/vertex_shader.vert", "Shaders/fragment_shader.frag"))
    {
        data->logger->log("GameState::initShaders", ERROR, "Could not load shaders.");
        ErrorHandler::throwErr("GAMESTATE::INITSHADERS::ERR_COULD_NOT_LOAD_SHADERS\n");
    }

    coreShader.setUniform("ambient", ambientLight);
    coreShader.setUniform("useVignette", false);

    data->logger->log("GameState::initShaders", DEBUG, "Successfully loaded shaders.");
}

void GameState::initPauseMenu()
{
    pauseMenu = new gui::PauseMenu(vm, font);

    pauseMenu->addButton("RESUME", gui::p2pY(vm, 75.5f), "Resume");
    pauseMenu->addButton("QUIT", gui::p2pY(vm, 83.5f), "Quit");
}

void GameState::initPlayers()
{
    player = new Player(200.f, 200.f, textures);
}

void GameState::initPlayerGUI()
{
    playerGUI = new PlayerGUI(*player, vm);
}

void GameState::initTileMap(const std::string map_path)
{
    tileMap = new TileMap(map_path);
}

void GameState::initEnemySystem()
{
    enemySystem = new EnemySystem(activeEnemies, textures, *player, *tileMap);
}

void GameState::initTextTagSystem()
{
    textTagSystem = new TextTagSystem("Fonts/VCR_OSD_MONO_1.001.ttf", vm);
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

GameState::GameState(StateData *data, const std::string map_path) : State(data)
{
    initVariables();
    initBufferedRender();
    initPlayerCamera();
    initKeybinds();
    initFonts();
    initText();
    initTextures();
    initShaders();
    initPauseMenu();
    initPlayers();
    initPlayerGUI();
    initTileMap(map_path);
    initEnemySystem();
    initTextTagSystem();
}

GameState::~GameState()
{
    delete pauseMenu;
    delete player;
    delete playerGUI;
    delete enemySystem;
    delete textTagSystem;
    delete tileMap;

    for (auto enemy : activeEnemies)
        delete enemy;
}

/* FUNCTIONS ===================================================================================================== */

void GameState::update(const float &dt)
{
    updateMousePositions(&playerCamera);
    updateInput(dt);

    // Not-paused update
    if (!isPaused)
    {
        updateDebugStats(dt);

        updatePlayerCamera(dt);
        updatePlayerInput(dt);
        updatePlayers(dt);
        updatePlayerGUI(dt, sf::Vector2f(mousePosWindow));
        updateEnemiesAndCombat(dt);
        updateTileMap(dt);
        updateShaders();

        textTagSystem->update(dt);
    }

    // Paused update
    else
    {
        pauseMenu->update(mousePosWindow);
        updatePauseMenuButtons();
    }
}

void GameState::render(sf::RenderTarget &target)
{
    renderToBuffer();

    target.draw(renderSprite);
}

void GameState::renderToBuffer()
{
    // Clear render buffer
    renderBuffer.clear();

    renderBuffer.setView(playerCamera);

    tileMap->render(renderBuffer, playerCameraPosGrid, vm, SHOW_COL_BOX, USE_DEFERRED_RENDER,
                    &coreShader, player->getCenteredPosition());

    for (auto &enemy : activeEnemies)
        enemy->render(renderBuffer, SHOW_HITBOX, &coreShader, player->getCenteredPosition());

    player->render(renderBuffer, SHOW_HITBOX, &coreShader, player->getCenteredPosition());

    tileMap->deferredRender(renderBuffer, &coreShader, player->getCenteredPosition());

    renderBuffer.setView(playerCamera);
    textTagSystem->render(renderBuffer);

    renderBuffer.setView(renderBuffer.getDefaultView());
    playerGUI->render(renderBuffer);

    if (isPaused)
    {
        // renderBuffer.setView(renderBuffer.getDefaultView());
        pauseMenu->render(renderBuffer);
    }

    if (showDebugStats)
    {
        // renderBuffer.setView(renderBuffer.getDefaultView());
        renderBuffer.draw(debugText);
    }

    // Display render buffer
    renderBuffer.display();

    renderSprite.setTexture(renderBuffer.getTexture());
}

void GameState::updateInput(const float &dt)
{
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(keybinds.at("PAUSE"))))
        pauseToggle();
    else if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(keybinds.at("DEBUG_STATS"))))
        debugStatsToggle();
}

void GameState::updatePlayers(const float &dt)
{
    player->update(dt, mousePosView);
}

void GameState::updatePlayerInput(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_UP")))
    {
        player->move(0.f, -1.f, dt);
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_DOWN")))
    {
        player->move(0.f, 1.f, dt);
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_LEFT")))
    {
        player->move(-1.f, 0.f, dt);
    }
    else if (sf::Keyboard::isKeyPressed(keybinds.at("MOVE_RIGHT")))
    {
        player->move(1.f, 0.f, dt);
    }
}

void GameState::updatePlayerGUI(const float &dt, sf::Vector2f mouse_pos)
{
    playerGUI->update(dt, mouse_pos);
}

void GameState::updateEnemiesAndCombat(const float &dt)
{
    Enemy *enemy;

    for (size_t i = 0; i < activeEnemies.size(); ++i)
    {
        enemy = activeEnemies[i];
        enemy->update(dt);

        tileMap->updateWorldBoundsCollision(dt, enemy);
        tileMap->updateTileCollision(dt, enemy);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            updateCombat(dt, enemy);

            if (enemy->isDead())
            {
                player->earnExp(enemy->getExpDrop());

                textTagSystem->displayTag(EXPERIENCE_TAG, player->getPosition(),
                                          enemy->getExpDrop(), "+", "exp");

                enemySystem->deleteEnemy(i);
            }
        }
    }
}

void GameState::updateCombat(const float &dt, Enemy *enemy)
{
    if (enemy->getGlobalBounds().contains(mousePosView) &&
        player->getRangeDistanceFrom(*enemy) <= player->getWeapon()->getRange() &&
        player->getWeapon()->didCooldown())
    {
        unsigned short damage = player->getWeapon()->getDamage();

        enemy->loseHp(damage);

        sf::Vector2f knock_vec(enemy->getCenteredPosition().x - player->getCenteredPosition().x,
                               enemy->getCenteredPosition().y - player->getCenteredPosition().y);

        float knock_vec_len = sqrt(pow(knock_vec.x, 2) + pow(knock_vec.y, 2));

        knock_vec /= knock_vec_len;

        enemy->knockback(knock_vec, player->getWeapon()->getKnockback());

        textTagSystem->displayTag(DAMAGE_TAG, enemy->getPosition(), damage, "-", "hp");
    }
}

void GameState::updateTileMap(const float &dt)
{
    tileMap->updateTiles(dt, player, enemySystem);

    tileMap->updateWorldBoundsCollision(dt, player);
    tileMap->updateTileCollision(dt, player);

    tileMap->updateAmbientLight(dt, ambientLight);
}

void GameState::updateShaders()
{
    coreShader.setUniform("ambient", ambientLight);
}

void GameState::updateDebugStats(const float &dt)
{
    std::stringstream ss;

    ss << "[delta]: " << dt << "ms" << "\n"
       << "[player x]: " << player->getGridPosition(gridSize).x << "\n"
       << "[player y]: " << player->getGridPosition(gridSize).y << "\n"
       << "[velocity x]: " << player->getVelocity().x << "\n"
       << "[velocity y]: " << player->getVelocity().y << "\n"
       << "[daytime]: " << tileMap->getDayTime() << "\n";

    debugText.setString(ss.str());
}

void GameState::updatePauseMenuButtons()
{
    if (pauseMenu->isButtonPressed("QUIT"))
    {
        data->logger->log("GameState::updatePauseMenuButtons", DEBUG, "Quitting state.");
        quit();
    }
    else if (pauseMenu->isButtonPressed("RESUME"))
    {
        data->logger->log("GameState::updatePauseMenuButtons", DEBUG, "Resuming state.");
        resume();
    }
}

void GameState::updatePlayerCamera(const float &dt)
{

    playerCamera.setCenter(
        std::floor(player->getCenteredPosition().x + ((mousePosWindow.x) - static_cast<float>(vm.width / 2)) / 20.f),
        std::floor(player->getCenteredPosition().y + ((mousePosWindow.y) - static_cast<float>(vm.height / 2)) / 20.f));

    // Make sure that the player camera width is smaller than the world
    if (playerCamera.getSize().x <= tileMap->getSize().x)
    {
        if (playerCamera.getCenter().x - playerCamera.getSize().x / 2.f < 0.f)
            playerCamera.setCenter(0.f + playerCamera.getSize().x / 2.f, playerCamera.getCenter().y);

        else if (playerCamera.getCenter().x + playerCamera.getSize().x / 2.f > tileMap->getSize().x)
            playerCamera.setCenter(tileMap->getSize().x - playerCamera.getSize().x / 2.f, playerCamera.getCenter().y);
    }

    // Make sure that the player camera height is smaller than the world
    if (playerCamera.getSize().x <= tileMap->getSize().x)
    {
        if (playerCamera.getCenter().y - playerCamera.getSize().y / 2.f < 0.f)
            playerCamera.setCenter(playerCamera.getCenter().x, 0.f + playerCamera.getSize().y / 2.f);

        else if (playerCamera.getCenter().y + playerCamera.getSize().y / 2.f > tileMap->getSize().y)
            playerCamera.setCenter(playerCamera.getCenter().x, tileMap->getSize().y - playerCamera.getSize().y / 2.f);
    }

    playerCameraPosGrid.x = static_cast<int>(playerCamera.getCenter().x) / static_cast<int>(data->gridSize);
    playerCameraPosGrid.y = static_cast<int>(playerCamera.getCenter().y) / static_cast<int>(data->gridSize);
}

void GameState::debugStatsToggle()
{
    showDebugStats = !showDebugStats;
}
