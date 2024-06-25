/*
 * SettingsState.cpp
 *
 *  Created on: 28 de abr. de 2024
 *      Author: renan
 */

#include "stdafx.h"
#include "SettingsState.h"

/* INITIALIZERS ================================================================================================== */

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
    std::vector<std::string> mode_labels;

    // Get the video modes strings
    for (auto &mode : videoModes)
    {
        std::stringstream ss;
        ss << mode.width << "x" << mode.height;

        if (std::find(mode_labels.begin(), mode_labels.end(), ss.str()) == mode_labels.end())
            mode_labels.push_back(ss.str());
    }

    // Find the index of the current mode label in mode labels
    short unsigned selected_index = 0;
    std::stringstream current_mode_label;

    current_mode_label << vm.width << "x" << vm.height;

    auto it = std::find(mode_labels.begin(), mode_labels.end(), current_mode_label.str());
    if (it != mode_labels.end())
    {
        auto index = std::distance(mode_labels.begin(), it);

        selected_index = static_cast<short unsigned>(index);
    }

    // Create the drop down list.
    dropDownLists["RESOLUTIONS"] = new gui::DropDownList(
        gui::p2pX(vm, 25.f), gui::p2pY(vm, 40.f),
        gui::p2pX(vm, 16.f), gui::p2pY(vm, 3.f),
        font, mode_labels,
        gui::calc_char_size(vm, 135),
        10, selected_index);

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

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

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

/* FUNCTIONS ===================================================================================================== */

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
