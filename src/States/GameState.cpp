/*
 * GameState class that extends State class.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
#include "GameState.h"

/* INITIALIZERS ================================================================================================= */

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
    std::ifstream ifs("Config/gamestate_keybinds.ini");

    if (ifs.is_open())
    {
        std::string action = "";
        std::string key = "";

        while (ifs >> action >> key)
            keybinds[action] = acceptedKeys->at(key);
    }
    else
        ErrorHandler::throwErr("GAMESTATE::INITKEYBINDS::ERROR_COULD_NOT_LOAD_KEYBINDS\n");

    ifs.close();
}

void GameState::initFonts()
{
    if (!font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
        ErrorHandler::throwErr("ERROR::GAMESTATE::INITFONTS::COULD_NOT_LOAD_FONT\n");
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
        ErrorHandler::throwErr("ERROR::GAMESTATE::INITTEXTURES::COULD_NOT_LOAD_TEXTURE_PLAYER_SPRITESHEET\n");

    if (!textures["SLIME_SPRITESHEET"].loadFromFile("Assets/Images/Sprites/Slime/slime.png"))
        ErrorHandler::throwErr("ERROR::GAMESTATE::INITTEXTURES::COULD_NOT_LOAD_TEXTURE_SLIME_SPRITESHEEET\n");
}

void GameState::initShaders()
{
    if (!coreShader.loadFromFile("Shaders/vertex_shader.vert", "Shaders/fragment_shader.frag"))
        ErrorHandler::throwErr("GAMESTATE::INITSHADERS::ERR_COULD_NOT_LOAD_SHADERS\n");
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
    playerGUI = new PlayerGUI(player, vm);
}

void GameState::initEnemySystem()
{
    enemySystem = new EnemySystem(activeEnemies, textures);
}

void GameState::initTextTagSystem()
{
    textTagSystem = new TextTagSystem("Fonts/VCR_OSD_MONO_1.001.ttf", vm);
}

void GameState::initTileMap()
{
    tileMap = new TileMap("Maps/test.biomap");
}

/* CONSTRUCTOR AND DESTRUCTOR ================================================================================== */

GameState::GameState(StateData *data) : State(data)
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
    initEnemySystem();
    initTextTagSystem();
    initTileMap();

    textTagSystem->addTag(TextTagType::DEFAULT_TAG, 200.f, 500.f, "Hello, world!");
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

/* FUNCTIONS ==================================================================================================== */

void GameState::update(const float &dt)
{
    updateMousePositions(&playerCamera);
    updateKeytime(dt);
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

    tileMap->render(
        renderBuffer, playerCameraPosGrid,
        vm, DO_NOT_SHOW_COL_BOX, USE_DEFERRED_RENDER,
        &coreShader, player->getCenteredPosition());

    for (auto &enemy : activeEnemies)
        enemy->render(renderBuffer, DO_NOT_SHOW_HITBOX, &coreShader, player->getCenteredPosition());

    player->render(renderBuffer, DO_NOT_SHOW_HITBOX, &coreShader, player->getCenteredPosition());

    tileMap->deferredRender(
        renderBuffer,
        &coreShader, player->getCenteredPosition());

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
    if (sf::Keyboard::isKeyPressed(keybinds["PAUSE"]) && hasCompletedKeytimeCicle())
        pauseToggle();
}

void GameState::updatePlayers(const float &dt)
{
    player->update(dt, mousePosView);
}

void GameState::updatePlayerInput(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && hasCompletedKeytimeCicle())
        player->earnExp(100);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && hasCompletedKeytimeCicle())
        player->loseExp(100);

    if (sf::Keyboard::isKeyPressed(keybinds["MOVE_UP"]))
    {
        player->move(0.f, -1.f, dt);
    }
    else if (sf::Keyboard::isKeyPressed(keybinds["MOVE_DOWN"]))
    {
        player->move(0.f, 1.f, dt);
    }
    else if (sf::Keyboard::isKeyPressed(keybinds["MOVE_LEFT"]))
    {
        player->move(-1.f, 0.f, dt);
    }
    else if (sf::Keyboard::isKeyPressed(keybinds["MOVE_RIGHT"]))
    {
        player->move(1.f, 0.f, dt);
    }
}

void GameState::updatePlayerGUI(const float &dt)
{
    playerGUI->update(dt);
}

void GameState::updateEnemiesAndCombat(const float &dt)
{
    short unsigned index = 0;
    for (auto enemy : activeEnemies)
    {
        enemy->update(dt);

        tileMap->updateWorldBoundsCollision(dt, enemy);
        tileMap->updateTileCollision(dt, enemy);

        updateCombat(dt, enemy, index);

        // Very safe code LOL (TODO: change later)
        if (enemy->isDead())
        {
            // Earn exp
            player->earnExp(enemy->getExpDrop());

            textTagSystem->addTag(TextTagType::EXPERIENCE_TAG,
                                  player->getPosition().x,
                                  player->getPosition().y,
                                  "+" + std::to_string(enemy->getExpDrop()) + "exp");

            // Delete entity
            activeEnemies.erase(activeEnemies.begin() + index);
            --index;
        }

        ++index;
    }
}

void GameState::updateCombat(const float &dt, Enemy *enemy, const short unsigned index)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (enemy->getGlobalBounds().contains(mousePosView) &&
            player->getRangeDistanceFrom(*enemy) <= player->getWeapon()->getRange() &&
            player->getWeapon()->didCooldown())
        {
            enemy->loseHp(player->getWeapon()->getDamageMin());

            textTagSystem->addTag(TextTagType::DAMAGE_TAG,
                                  enemy->getPosition().x,
                                  enemy->getPosition().y,
                                  "-" + std::to_string(player->getWeapon()->getDamageMin()) + "hp");
        }
    }
}

void GameState::updateTileMap(const float &dt)
{
    tileMap->updateTiles(dt, player, enemySystem);

    tileMap->updateWorldBoundsCollision(dt, player);
    tileMap->updateTileCollision(dt, player);
}

void GameState::updatePauseMenuButtons()
{
    if (pauseMenu->isButtonPressed("QUIT"))
        quit();
    else if (pauseMenu->isButtonPressed("RESUME"))
        pauseToggle();
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
