/*
 * MainMenuState class that extends State class.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
#include "EditorState.h"

/* INITIALIZERS ================================================================================================== */

void EditorState::initVariables()
{
    cameraSpeed = 500.f;
    activeEditorMode = EditorModes::DEFAULT_MODE;
}

void EditorState::initEditorCamera()
{
    editorCamera.setSize(Vector2f(vm.width, vm.height));

    editorCamera.setCenter(vm.width / 2.f, vm.height / 2.f);
}

void EditorState::initKeybinds()
{
    IniParser parser("Config/keybinds.ini");

    for (auto it : parser.getAllKeyValuePairs("EditorState"))
        keybinds[it.first] = acceptedKeys->at(it.second);

    data->logger->log("EditorState::initKeybinds", INFO,
                      "Initialized " + to_string(keybinds.size()) + " keybinds.");
}

void EditorState::initFonts()
{
    if (!font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
    {
        data->logger->log("EditorState::initFonts", ERROR, "Could not load fonts.");
        ErrorHandler::throwErr("ERROR::EDITORSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n");
    }

    data->logger->log("EditorState::initFonts", DEBUG, "Successfully loaded fonts");
}

void EditorState::initPauseMenu()
{
    pauseMenu = new gui::PauseMenu(vm, font);
    pauseMenu->addButton("LOAD", gui::p2pY(vm, 59.5f), "Load Map");
    pauseMenu->addButton("SAVE", gui::p2pY(vm, 67.5f), "Save Map");
    pauseMenu->addButton("RESUME", gui::p2pY(vm, 75.5f), "Resume");
    pauseMenu->addButton("QUIT", gui::p2pY(vm, 83.5f), "Quit");
}

void EditorState::initTileMap()
{
    tileMap = new TileMap(data->gridSize, 100, 100, "Assets/Images/Tiles/tilesheet.png");
}

void EditorState::initGUI()
{
}

void EditorState::initEditorStateData()
{
    editorStateData.keybinds = &keybinds;
    editorStateData.tileMap = tileMap;
    editorStateData.editorCamera = &editorCamera;
    editorStateData.font = &font;
    editorStateData.keyTimer = &keyTimer;
    editorStateData.keyTimerMax = &keyTimerMax;
    editorStateData.mouseTimer = &mouseTimer;
    editorStateData.mouseTimerMax = &mouseTimerMax;
    editorStateData.mousePosScreen = &mousePosScreen;
    editorStateData.mousePosWindow = &mousePosWindow;
    editorStateData.mousePosView = &mousePosView;
    editorStateData.mousePosGrid = &mousePosGrid;
}

void EditorState::initModes()
{
    modes[EditorModes::DEFAULT_MODE] = new DefaultEditorMode(data, &editorStateData);
    modes[EditorModes::ENEMY_MODE] = new EnemyEditorMode(data, &editorStateData);
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

EditorState::EditorState(StateData *data) : State(data)
{
    initVariables();
    initEditorCamera();
    initFonts();
    initKeybinds();
    initPauseMenu();
    initTileMap();
    initGUI();
    initEditorStateData();
    initModes();
}

EditorState::~EditorState()
{
    for (auto &it : buttons)
        delete it.second;

    delete pauseMenu;

    delete tileMap;

    for (auto &it : modes)
        delete it.second;
}

/* FUNCTIONS ===================================================================================================== */

void EditorState::update(const float &dt)
{
    updateMousePositions(&editorCamera);
    updateInput(dt);

    if (!isPaused)
    {
        updateGUI(dt);
        updateEditorCamera(dt);
        updateModes(dt);
    }
    else
    {
        pauseMenu->update(mousePosWindow);
    }
}

void EditorState::render(RenderTarget &target)
{
    // Render tilemap in the editor camera
    target.setView(editorCamera);
    tileMap->render(target, editorCameraPosGrid, vm, SHOW_COL_BOX);

    if (!isPaused)
    {
        // Render GUI in the window view
        target.setView(window->getDefaultView());
        renderGUI(target);
        renderModes(target);
    }
    else
    {
        // Render pause menu in the window view
        target.setView(window->getDefaultView());
        pauseMenu->render(target);
        updatePauseMenuInteraction();
    }
}

void EditorState::updateInput(const float &dt)
{

    // Pause menu toggle
    if (hasElapsedKeyTimeMax(Keyboard::isKeyPressed(keybinds["PAUSE"])))
        pauseToggle();

    // Default editor mode
    if (hasElapsedKeyTimeMax(Keyboard::isKeyPressed(keybinds.at("DEFAULT_EDITOR_MODE"))))
        activeEditorMode = EditorModes::DEFAULT_MODE;

    // Enemy editor mode
    else if (hasElapsedKeyTimeMax(Keyboard::isKeyPressed(keybinds.at("ENEMY_EDITOR_MODE"))))
        activeEditorMode = EditorModes::ENEMY_MODE;
}

void EditorState::updateGUI(const float &dt)
{
    // Buttons
    for (auto &it : buttons)
        it.second->update(Vector2f(mousePosWindow));
}

void EditorState::updateEditorCamera(const float &dt)
{
    if (Keyboard::isKeyPressed(keybinds["MOVE_CAMERA_UP"]))
        editorCamera.move(0.f, floor(-cameraSpeed * dt));

    else if (Keyboard::isKeyPressed(keybinds["MOVE_CAMERA_DOWN"]))
        editorCamera.move(0.f, floor(cameraSpeed * dt));

    else if (Keyboard::isKeyPressed(keybinds["MOVE_CAMERA_LEFT"]))
        editorCamera.move(floor(-cameraSpeed * dt), 0.f);

    else if (Keyboard::isKeyPressed(keybinds["MOVE_CAMERA_RIGHT"]))
        editorCamera.move(floor(cameraSpeed * dt), 0.f);

    editorCameraPosGrid.x = static_cast<int>(editorCamera.getCenter().x) / static_cast<int>(data->gridSize);
    editorCameraPosGrid.y = static_cast<int>(editorCamera.getCenter().y) / static_cast<int>(data->gridSize);
}

void EditorState::updatePauseMenuInteraction()
{
    if (hasElapsedMouseTimeMax(pauseMenu->isButtonPressed("LOAD")))
    {
        tileMap->loadFromFile("Maps/test.biomap");
        data->logger->log("EditorState::updatePauseMenuInteraction", DEBUG, "Loaded map to Maps/test.biomap");
    }

    else if (hasElapsedMouseTimeMax(pauseMenu->isButtonPressed("SAVE")))
    {
        tileMap->saveToFile("Maps/test.biomap");
        data->logger->log("EditorState::updatePauseMenuInteraction", DEBUG, "Saved map to Maps/test.biomap");
    }

    else if (hasElapsedMouseTimeMax(pauseMenu->isButtonPressed("RESUME")))
    {
        data->logger->log("EditorState::updatePauseMenuInteraction", DEBUG, "Resuming state.");
        resume();
    }

    else if (hasElapsedMouseTimeMax(pauseMenu->isButtonPressed("QUIT")))
    {
        data->logger->log("EditorState::updatePauseMenuInteraction", DEBUG, "Quitting state.");
        quit();
    }
}

void EditorState::updateModes(const float &dt)
{
    modes[activeEditorMode]->update(dt);
}

void EditorState::renderGUI(RenderTarget &target)
{
}

void EditorState::renderModes(RenderTarget &target)
{
    modes[activeEditorMode]->render(target);
}
