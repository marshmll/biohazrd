/*
 * SettingsState.cpp
 *
 *  Created on: 28 de abr. de 2024
 *      Author: renan
 */

#include "stdafx.h"
#include "SettingsState.h"

/* INITIALIZERS */

void SettingsState::initVariables()
{
    videoModes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initFonts()
{
    if (!font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
        ErrorHandler::throwErr("ERROR::SETTINGSSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n");
}

void SettingsState::initKeybinds()
{
    std::ifstream ifs("Config/mainmenustate_keybinds.ini");

    if (ifs.is_open())
    {
        std::string action = "";
        std::string key = "";

        while (ifs >> action >> key)
            keybinds[action] = acceptedKeys->at(key);
    }
    else
        ErrorHandler::throwErr("ERROR::SETTINGSSTATE::INITKEYBINDS_COULD_NOT_LOAD_KEYBINDS\n");

    ifs.close();
}

void SettingsState::initGUI()
{
    const sf::VideoMode &vm = data->gfxSettings->resolution;

    // Background
    background.setSize(sf::Vector2f(vm.width, vm.height));

    if (!backgroundTexture.loadFromFile("Assets/Images/Backgrounds/main_menu_bg.png"))
        ErrorHandler::throwErr("ERROR::SETTINGSSTATE::INITBACKGROUND::ERROR_COULD_NOT_LOAD_MAINMENU_BG\n");

    background.setTexture(&backgroundTexture);

    // Buttons
    buttons["BACK"] = new gui::Button(
        gui::p2pX(vm, 84.3f), gui::p2pY(vm, 82.5f),
        gui::p2pX(vm, 11.7f), gui::p2pY(vm, 6.2f),
        font, "Back", gui::calc_char_size(vm, 65),
        sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    buttons["APPLY"] = new gui::Button(
        gui::p2pX(vm, 68.7f), gui::p2pY(vm, 82.5f),
        gui::p2pX(vm, 11.7f), gui::p2pY(vm, 6.2f),
        font, "Apply", gui::calc_char_size(vm, 65),
        sf::Color(200, 200, 200, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

    // Drop down lists
    std::vector<std::string> modes_str;

    // Get the video modes strings
    for (auto &mode : videoModes)
        modes_str.push_back(std::to_string(mode.width) + "x" + std::to_string(mode.height));

    // Find the index of the current videomode in videomodes
    unsigned i;
    auto it = std::find(videoModes.begin(), videoModes.end(), vm);
    if (it != videoModes.end())
    {
        auto index = std::distance(videoModes.begin(), it);

        i = static_cast<unsigned>(index);
    }

    // Create the drop down list.
    dropDownLists["RESOLUTIONS"] = new gui::DropDownList(
        gui::p2pX(vm, 25.f), gui::p2pY(vm, 40.f),
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 6.2f),
        font, modes_str.data(), modes_str.size(),
        gui::calc_char_size(vm, 120), i);

    // Create options text
    optionsText.setFont(font);
    optionsText.setPosition(gui::p2pX(vm, 6.2f), gui::p2pY(vm, 40.f));
    optionsText.setCharacterSize(gui::calc_char_size(vm, 70));
    optionsText.setFillColor(sf::Color(255, 255, 255, 200));
    optionsText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n");
}

void SettingsState::resetGUI()
{
    for (auto &it : buttons)
        delete it.second;
    buttons.clear();

    for (auto &it : dropDownLists)
        delete it.second;
    dropDownLists.clear();

    initGUI();
}

/* CONSTRUCTOR AND DESTRUCTOR */

SettingsState::SettingsState(StateData *data, MainMenuState *main_menu_state) : State(data)
{
    mainMenuState = main_menu_state;

    initVariables();

    initFonts();

    initKeybinds();

    initGUI();
}

SettingsState::~SettingsState()
{
    // Delete buttons
    for (auto &it : buttons)
        delete it.second;

    // Delete ddls
    for (auto &it : dropDownLists)
        delete it.second;
}

/* FUNCTIONS */

void SettingsState::update(const float &dt)
{
    updateInput(dt);
    updateGUI(dt);
}

void SettingsState::render(sf::RenderTarget &target)
{
    target.draw(background);
    renderGUI(target);
    target.draw(optionsText);

    //////////////////////////// REMOVE LATER: DEBUGGING STUFF ////////////////////////////////
    // sf::Text mouseText;
    // mouseText.setPosition(sf::Vector2f(mousePosView.x, mousePosView.y - 20));
    // mouseText.setFont(font);
    // mouseText.setCharacterSize(12);

    // std::stringstream ss;
    // ss << mousePosView.x << " " << mousePosView.y;
    // mouseText.setString(ss.str());

    // target.draw(mouseText);
    ///////////////////////////////////////////////////////////////////////////////////////////
}

void SettingsState::updateInput(const float &dt)
{
    updateMousePositions();
}

void SettingsState::updateGUI(const float &dt)
{
    // Updates all buttons based on mouse position view.
    for (auto &it : buttons)
        it.second->update(sf::Vector2f(mousePosWindow));

    // Updates all ddls based on mouse position view and dt.
    for (auto &it : dropDownLists)
        it.second->update(mousePosWindow, dt);

    // Checks for returning
    if (buttons["BACK"]->isPressed())
        quit();

    // Apply settings
    else if (buttons["APPLY"]->isPressed())
    {
        gfxSettings->resolution = videoModes[dropDownLists["RESOLUTIONS"]->getSelectedElementId()];

        window->create(gfxSettings->resolution, "BIOHAZRD", sf::Style::Titlebar | sf::Style::Close);

        resetGUI();

        mainMenuState->resetGUI();
    }
}

void SettingsState::renderGUI(sf::RenderTarget &target)
{
    // Render buttons
    for (auto &it : buttons)
        it.second->render(target);

    // Render ddls
    for (auto &it : dropDownLists)
        it.second->render(target);
}
