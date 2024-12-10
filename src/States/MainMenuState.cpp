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
    if (!font.loadFromFile("Fonts/VCR_OSD_MONO_1.001.ttf"))
    {
        data->logger->log("MainMenuState::initFonts", ERROR, "Could not load font VCR_OSD_MONO_1.001.ttf.");
        ErrorHandler::throwErr("ERROR::MAINMENUSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n");
    }

    if (!titleFont.loadFromFile("Fonts/chinese_rocks_rg.otf"))
    {
        data->logger->log("MainMenuState::initFonts", ERROR, "Could not load font chinese_rocks_rg.otf.");
        ErrorHandler::throwErr("ERROR::MAINMENUSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n");
    }

    data->logger->log("MainMenuState::initFonts", DEBUG, "Successfully loaded fonts.");
}

void MainMenuState::initKeybinds()
{
}

void MainMenuState::initGUI()
{
    // Title
    title.setFont(titleFont);
    title.setCharacterSize(gui::calc_char_size(vm, 20));
    title.setString("ECHOES OF VENGEANCE");
    title.setFillColor(sf::Color::White);
    title.setPosition((vm.width / 2.f) - title.getGlobalBounds().width / 2.f, 60.f);

    // Background
    background = new Video("Assets/Videos/bg/", 0.f, 0.f, vm.width, vm.height, 15);

    data->logger->log("MainMenuState::initGUI", DEBUG, "Successfully loaded background video.");

    // Buttons
    buttons["WORLD_SELECTION_STATE"] = new gui::Button(
        (vm.width / 2.f) - gui::p2pX(vm, 19.5f) / 2.f, gui::p2pY(vm, 40.f),
        gui::p2pX(vm, 19.5f), gui::p2pY(vm, 6.2f),
        font, "Play", gui::calc_char_size(vm, 65),
        sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    buttons["EDITOR_STATE"] = new gui::Button(
        (vm.width / 2.f) - gui::p2pX(vm, 19.5f) / 2.f, gui::p2pY(vm, 49.f),
        gui::p2pX(vm, 19.5f), gui::p2pY(vm, 6.2f),
        font, "Editor", gui::calc_char_size(vm, 65),
        sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    buttons["SETTINGS_STATE"] = new gui::Button(
        (vm.width / 2.f) - gui::p2pX(vm, 19.5f) / 2.f, gui::p2pY(vm, 58.f),
        gui::p2pX(vm, 19.5f), gui::p2pY(vm, 6.2f),
        font, "Settings", gui::calc_char_size(vm, 65),
        sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    buttons["EXIT_STATE"] = new gui::Button(
        (vm.width / 2.f) - gui::p2pX(vm, 19.5f) / 2.f, gui::p2pY(vm, 90.f),
        gui::p2pX(vm, 19.5f), gui::p2pY(vm, 6.2f),
        font, "Exit", gui::calc_char_size(vm, 65),
        sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));
}

void MainMenuState::initSounds()
{
    data->soundSys->loadBuffers("Global");

    data->soundSys->createGlobalSound("MAIN_THEME", "MAIN_THEME", 60.f, true);
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

    delete background;
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
    background->play();

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
    background->render(target);
    target.draw(title);

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
