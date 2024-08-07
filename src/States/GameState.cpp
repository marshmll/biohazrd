/*
 * GameState class that extends State class.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
#include "GameState.h"

/* INITIALIZERS ================================================================================================== */

void GameState::initBufferedRender()
{
    renderBuffer.create(vm.width, vm.height);

    renderSprite.setTexture(renderBuffer.getTexture());

    renderSprite.setTextureRect(sf::IntRect(0, 0, vm.width, vm.height));
}

void GameState::initView()
{
    playerCamera.setSize(sf::Vector2f(vm.width, vm.height));

    playerCamera.setCenter(vm.width / 2.f, vm.height / 2.f);
}

void GameState::initKeybinds()
{
    IniParser parser("Config/keybinds.ini");

    for (auto &[action, key] : parser.getAllKeyValuePairs("GameState"))
        keybinds[action] = acceptedKeys->at(key);

    data->logger->log("GameState::initKeybinds", INFO,
                      "Initialized " + std::to_string(keybinds.size()) + " keybinds.");
}

void GameState::initFonts()
{
    if (!font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
    {
        data->logger->log("GameState::initFonts", ERROR, "Could not load fonts.");
        ErrorHandler::throwErr("ERROR::GAMESTATE::INITFONTS::COULD_NOT_LOAD_FONT\n");
    }

    data->logger->log("GameState::initFonts", DEBUG, "Successfully loaded fonts.");
}

void GameState::initText()
{
    debugText.setFont(font);
    debugText.setCharacterSize(gui::calc_char_size(vm, 150));
    debugText.setPosition(vm.width - gui::p2pX(vm, 10.f), gui::p2pY(vm, 5.f));
}

void GameState::initTextures()
{
    if (!textures["PLAYER_SPRITESHEET"].loadFromFile("Assets/Images/Sprites/Player/char_a_p1_0bas_humn_v01.png"))
    {
        data->logger->log("GameState::initTextures", ERROR, "Could not player spritesheet.");
        ErrorHandler::throwErr("ERROR::GAMESTATE::INITTEXTURES::COULD_NOT_LOAD_TEXTURE_PLAYER_SPRITESHEET\n");
    }

    if (!textures["SLIME_SPRITESHEET"].loadFromFile("Assets/Images/Sprites/Slime/slime.png"))
    {
        data->logger->log("GameState::initTextures", ERROR, "Could not slime spritesheet.");
        ErrorHandler::throwErr("ERROR::GAMESTATE::INITTEXTURES::COULD_NOT_LOAD_TEXTURE_SLIME_SPRITESHEEET\n");
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
    coreShader.setUniform("useVignette", true);

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
    player = new Player(200.f, 200.f, textures["PLAYER_SPRITESHEET"]);
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
    initBufferedRender();
    initView();
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
        /* DEBUG! */
        std::stringstream ss;
        ss << "dt: " << dt << "ms";
        debugText.setString(ss.str());
        /*********/

        updatePlayerCamera(dt);
        updatePlayerInput(dt);
        updatePlayers(dt);
        updatePlayerGUI(dt);
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

    /* DEBUG! */
    target.draw(debugText);
    /**********/
}

void GameState::renderToBuffer()
{
    // Clear render buffer
    renderBuffer.clear();

    renderBuffer.setView(playerCamera);

    tileMap->render(renderBuffer, playerCameraPosGrid, vm, DO_NOT_SHOW_COL_BOX, USE_DEFERRED_RENDER,
                    &coreShader, player->getCenteredPosition());

    for (auto &enemy : activeEnemies)
        enemy->render(renderBuffer, DO_NOT_SHOW_HITBOX, &coreShader, player->getCenteredPosition());

    player->render(renderBuffer, DO_NOT_SHOW_HITBOX, &coreShader, player->getCenteredPosition());

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

    // Display render buffer
    renderBuffer.display();

    renderSprite.setTexture(renderBuffer.getTexture());
}

void GameState::updateInput(const float &dt)
{
    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(keybinds.at("PAUSE"))))
        pauseToggle();
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

    if (hasElapsedKeyTimeMax(sf::Keyboard::isKeyPressed(keybinds.at("TOGGLE_CHAR_TAB"))))
    {
        playerGUI->toggleTab(CHARACTER_TAB);
    }
}

void GameState::updatePlayerGUI(const float &dt)
{
    playerGUI->update(dt);
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

    tileMap->updateAmbientLight(ambientLight);
}

void GameState::updateShaders()
{
    coreShader.setUniform("ambient", ambientLight);
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
    // Disable player camera movement on the mouse if any tab is open.
    if (playerGUI->hasTabsOpen())
    {
        playerCamera.setCenter(
            player->getCenteredPosition().x,
            player->getCenteredPosition().y);
    }
    else
    {
        playerCamera.setCenter(
            std::floor(player->getCenteredPosition().x + ((mousePosWindow.x) - static_cast<float>(vm.width / 2)) / 20.f),
            std::floor(player->getCenteredPosition().y + ((mousePosWindow.y) - static_cast<float>(vm.height / 2)) / 20.f));
    }

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
