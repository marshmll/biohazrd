/*
 * MainMenuState class that extends State class.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
#include "EditorState.h"

/* INITIALIZERS */
void EditorState::initVariables()
{
    this->cameraSpeed = 500.f;
    this->activeEditorMode = EditorModes::DEFAULT_MODE;
}

void EditorState::initEditorCamera()
{
    this->editorCamera.setSize(sf::Vector2f(this->vm.width, this->vm.height));

    this->editorCamera.setCenter(this->vm.width / 2.f, this->vm.height / 2.f);
}

void EditorState::initKeybinds()
{
    std::ifstream ifs("Config/editorstate_keybinds.ini");

    if (ifs.is_open())
    {
        std::string action = "";
        std::string key = "";

        while (ifs >> action >> key)
            this->keybinds[action] = this->acceptedKeys->at(key);
    }
    else
        ErrorHandler::throwErr("MAINMENUSTATE::INITKEYBINDS::ERROR_COULD_NOT_LOAD_KEYBINDS\n");

    ifs.close();
}

void EditorState::initFonts()
{
    if (!this->font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
        ErrorHandler::throwErr("ERROR::EDITORSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n");
}

void EditorState::initPauseMenu()
{
    this->pauseMenu = new gui::PauseMenu(this->vm, this->font);
    this->pauseMenu->addButton("QUIT", gui::p2pY(this->vm, 83.7f), "Exit");
    this->pauseMenu->addButton("SAVE", gui::p2pY(this->vm, 62.5f), "Save");
    this->pauseMenu->addButton("LOAD", gui::p2pY(this->vm, 50.f), "Load");
}

void EditorState::initTileMap()
{
    this->tileMap = new TileMap(this->data->gridSize, 100, 100, "Assets/Images/Tiles/tilesheet.png");
}

void EditorState::initGUI()
{
}

void EditorState::initEditorStateData()
{
    this->editorStateData.keybinds = &this->keybinds;
    this->editorStateData.tileMap = this->tileMap;
    this->editorStateData.editorCamera = &this->editorCamera;
    this->editorStateData.font = &this->font;
    this->editorStateData.keytime = &this->keytime;
    this->editorStateData.keytimeMax = &this->keytimeMax;
    this->editorStateData.mousetime = &this->mousetime;
    this->editorStateData.mousetimeMax = &this->mousetimeMax;
    this->editorStateData.mousePosScreen = &this->mousePosScreen;
    this->editorStateData.mousePosWindow = &this->mousePosWindow;
    this->editorStateData.mousePosView = &this->mousePosView;
    this->editorStateData.mousePosGrid = &this->mousePosGrid;
}

void EditorState::initModes()
{
    this->modes[EditorModes::DEFAULT_MODE] = new DefaultEditorMode(this->data, &this->editorStateData);
    this->modes[EditorModes::ENEMY_MODE] = new EnemyEditorMode(this->data, &this->editorStateData);
}

/* CONSTRUCTOR AND DESTRUCTOR */
EditorState::EditorState(StateData *data) : State(data)
{
    this->initVariables();
    this->initEditorCamera();
    this->initFonts();
    this->initKeybinds();
    this->initPauseMenu();
    this->initTileMap();
    this->initGUI();
    this->initEditorStateData();
    this->initModes();
}

EditorState::~EditorState()
{
    for (auto &it : this->buttons)
        delete it.second;

    delete this->pauseMenu;

    delete this->tileMap;

    for (auto &it : this->modes)
        delete it.second;
}

/* FUNCTIONS */
void EditorState::update(const float &dt)
{
    this->updateMousePositions(&this->editorCamera);
    this->updateInput(dt);
    this->updateKeytime(dt);
    this->updateMousetime(dt);

    if (!this->isPaused)
    {
        this->updateGUI(dt);
        this->updateEditorCamera(dt);
        this->updateModes(dt);
    }
    else
    {
        this->pauseMenu->update(this->mousePosWindow);
    }
}

void EditorState::render(sf::RenderTarget &target)
{
    // Render tilemap in the editor camera
    target.setView(this->editorCamera);
    this->tileMap->render(target, this->editorCameraPosGrid, this->vm, SHOW_COL_BOX);

    if (!this->isPaused)
    {
        // Render GUI in the window view
        target.setView(this->window->getDefaultView());
        this->renderGUI(target);
        this->renderModes(target);
    }
    else
    {
        // Render pause menu in the window view
        target.setView(this->window->getDefaultView());
        this->pauseMenu->render(target);
        this->updatePauseMenuInteraction();
    }
}

void EditorState::updateInput(const float &dt)
{
    // Pause menu toggle
    if (sf::Keyboard::isKeyPressed(this->keybinds["PAUSE"]) && this->hasCompletedKeytimeCicle())
        this->pauseToggle();

    // Change between modes
    if (sf::Keyboard::isKeyPressed(this->keybinds.at("DEFAULT_EDITOR_MODE")) && this->hasCompletedKeytimeCicle())
        this->activeEditorMode = EditorModes::DEFAULT_MODE;

    else if (sf::Keyboard::isKeyPressed(this->keybinds.at("ENEMY_EDITOR_MODE")) && this->hasCompletedKeytimeCicle())
        this->activeEditorMode = EditorModes::ENEMY_MODE;
}

void EditorState::updateGUI(const float &dt)
{
    // Buttons
    for (auto &it : this->buttons)
        it.second->update(sf::Vector2f(this->mousePosWindow));
}

void EditorState::updateEditorCamera(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_CAMERA_UP"]))
        this->editorCamera.move(0.f, std::floor(-this->cameraSpeed * dt));

    else if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_CAMERA_DOWN"]))
        this->editorCamera.move(0.f, std::floor(this->cameraSpeed * dt));

    else if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_CAMERA_LEFT"]))
        this->editorCamera.move(std::floor(-this->cameraSpeed * dt), 0.f);

    else if (sf::Keyboard::isKeyPressed(this->keybinds["MOVE_CAMERA_RIGHT"]))
        this->editorCamera.move(std::floor(this->cameraSpeed * dt), 0.f);

    this->editorCameraPosGrid.x = static_cast<int>(this->editorCamera.getCenter().x) / static_cast<int>(this->data->gridSize);
    this->editorCameraPosGrid.y = static_cast<int>(this->editorCamera.getCenter().y) / static_cast<int>(this->data->gridSize);
}

void EditorState::updatePauseMenuInteraction()
{
    if (this->pauseMenu->isButtonPressed("QUIT"))
        this->quit();

    else if (this->pauseMenu->isButtonPressed("SAVE"))
        this->tileMap->saveToFile("Maps/test.biomap");

    else if (this->pauseMenu->isButtonPressed("LOAD"))
        this->tileMap->loadFromFile("Maps/test.biomap");
}

void EditorState::updateModes(const float &dt)
{
    this->modes[this->activeEditorMode]->update(dt);
}

void EditorState::renderGUI(sf::RenderTarget &target)
{
}

void EditorState::renderModes(sf::RenderTarget &target)
{
    this->modes[this->activeEditorMode]->render(target);
}
