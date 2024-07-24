/*
 * MainMenuState class that extends State class.
 *
 *  Created on: 14 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
#include "MainMenuState.h"

/* INITIALIZERS ================================================================================================== */

void MainMenuState::initVariables()
{
}

void MainMenuState::initFonts()
{
    if (!font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
    {
        data->logger->log("MainMenuState::initFonts", ERROR, "Could not load fonts.");
        ErrorHandler::throwErr("ERROR::MAINMENUSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n");
    }

    data->logger->log("MainMenuState::initFonts", DEBUG, "Successfully loaded fonts.");
}

void MainMenuState::initKeybinds()
{
}

void MainMenuState::initGUI()
{
    // Background
    background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));

    if (!backgroundTexture.loadFromFile("Assets/Images/Backgrounds/main_menu_bg.png"))
    {
        data->logger->log("MainMenuState::initGUI", ERROR, "Could not load background image.");
        ErrorHandler::throwErr("ERROR::MAINMENUSTATE::INITBACKGROUND::ERROR_COULD_NOT_LOAD_MAINMENU_BG\n");
    }

    data->logger->log("MainMenuState::initGUI", DEBUG, "Successfully loaded background image.");

    background.setTexture(&backgroundTexture);

    // Buttons
    buttons["WORLD_SELECTION_STATE"] = new gui::Button(
        gui::p2pX(vm, 8.6f), gui::p2pY(vm, 40.f),
        gui::p2pX(vm, 19.5f), gui::p2pY(vm, 6.2f),
        font, "Play", gui::calc_char_size(vm, 65),
        sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    buttons["EDITOR_STATE"] = new gui::Button(
        gui::p2pX(vm, 8.6f), gui::p2pY(vm, 49.f),
        gui::p2pX(vm, 19.5f), gui::p2pY(vm, 6.2f),
        font, "Editor", gui::calc_char_size(vm, 65),
        sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    buttons["SETTINGS_STATE"] = new gui::Button(
        gui::p2pX(vm, 8.6f), gui::p2pY(vm, 58.f),
        gui::p2pX(vm, 19.5f), gui::p2pY(vm, 6.2f),
        font, "Settings", gui::calc_char_size(vm, 65),
        sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    buttons["EXIT_STATE"] = new gui::Button(
        gui::p2pX(vm, 8.6f), gui::p2pY(vm, 82.f),
        gui::p2pX(vm, 19.5f), gui::p2pY(vm, 6.2f),
        font, "Exit", gui::calc_char_size(vm, 65),
        sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void MainMenuState::initSounds()
{
    data->soundSys->loadBuffers("Global");

    data->soundSys->createGlobalSound("MAIN_THEME", "MAIN_THEME", 80.f, true);
    data->soundSys->createGlobalSound("CLICK_BUTTON", "CLICK_BUTTON", 20.f, false);

    data->soundSys->play("MAIN_THEME");
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

MainMenuState::MainMenuState(StateData *data) : State(data)
{
    initVariables();
    initFonts();
    initKeybinds();
    initGUI();
    initSounds();
}

MainMenuState::~MainMenuState()
{
    for (auto &[key, button] : buttons)
        delete button;
}

/* FUNCTIONS ===================================================================================================== */

void MainMenuState::update(const float &dt)
{
    updateInput(dt);
    updateSounds();
    updateGUI();
}

void MainMenuState::render(sf::RenderTarget &target)
{
    target.draw(background);
    renderGUI(target);
}

void MainMenuState::updateInput(const float &dt)
{
    updateMousePositions();
}

void MainMenuState::updateSounds()
{
    if (!data->soundSys->isPlaying("MAIN_THEME"))
        data->soundSys->play("MAIN_THEME");
}

void MainMenuState::updateGUI()
{
    // Updates all buttons based on mouse position view.
    for (auto &it : buttons)
        it.second->update(mousePosView);

    // World Selection
    if (buttons["WORLD_SELECTION_STATE"]->isPressed())
    {
        data->logger->log("MainMenuState::updateGUI", DEBUG, "Pushing a new WorldSelectionState.");

        data->soundSys->play("CLICK_BUTTON");

        states->push(new WorldSelectionState(data));
    }

    // Editor state
    else if (buttons["EDITOR_STATE"]->isPressed())
    {
        data->logger->log("MainMenuState::updateGUI", DEBUG, "Pushing a new EditorState.");

        data->soundSys->play("CLICK_BUTTON");

        data->soundSys->stop("MAIN_THEME");

        states->push(new EditorState(data));
    }

    // Settings
    else if (buttons["SETTINGS_STATE"]->isPressed())
    {
        data->logger->log("MainMenuState::updateGUI", DEBUG, "Pushing a new SettingsState.");

        data->soundSys->play("CLICK_BUTTON");

        states->push(new SettingsState(data, this));
    }

    // Exit
    else if (buttons["EXIT_STATE"]->isPressed())
    {
        data->logger->log("MainMenuState::updateGUI", DEBUG, "Quitting state.");
        data->soundSys->play("CLICK_BUTTON");

        quit();
    }
}

void MainMenuState::renderGUI(sf::RenderTarget &target)
{
    for (auto &[key, button] : buttons)
        button->render(target);
}

void MainMenuState::resetGUI()
{
    data->logger->log("MainMenuState::resetGUI", DEBUG, "Resetting GUI, initGUI will be called.");

    for (auto &[key, button] : buttons)
        delete button;

    buttons.clear();

    initGUI();
}