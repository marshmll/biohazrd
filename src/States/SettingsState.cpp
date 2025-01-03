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
    if (!font.loadFromFile("Fonts/VCR_OSD_MONO_1.001.ttf"))
    {
        data->logger->log("SettingsState::initFonts", ERROR, "Could not load fonts.");
        ErrorHandler::throwErr("ERROR::SETTINGSSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n");
    }

    if (!titleFont.loadFromFile("Fonts/chinese_rocks_rg.otf"))
    {
        data->logger->log("MainMenuState::initFonts", ERROR, "Could not load font chinese_rocks_rg.otf.");
        ErrorHandler::throwErr("ERROR::SETTINGSSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n");
    }

    data->logger->log("SettingsState::initFonts", DEBUG, "Successfully loaded fonts.");
}

void SettingsState::initKeybinds()
{
}

void SettingsState::initGUI()
{
    // Title
    title.setFont(titleFont);
    title.setCharacterSize(gui::calc_char_size(vm, 20));
    title.setString("ECHOES OF VENGEANCE");
    title.setFillColor(sf::Color::White);
    title.setPosition((vm.width / 2.f) - title.getGlobalBounds().width / 2.f, 60.f);

    // Background
    background = data->preloadedVideos->at("BACKGROUND");

    data->logger->log("SettingsState::initGUI", DEBUG, "Successfully loaded background video.");

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

    // Create the drop down lists.
    dropDownLists["RESOLUTIONS"] = new gui::DropDownList(
        gui::p2pX(vm, 25.f), gui::p2pY(vm, 41.f),
        gui::p2pX(vm, 16.f), gui::p2pY(vm, 3.f),
        font, mode_labels,
        gui::calc_char_size(vm, 135),
        10, selected_index);

    dropDownLists["FULLSCREEN"] = new gui::DropDownList(
        gui::p2pX(vm, 25.f), gui::p2pY(vm, 50.f),
        gui::p2pX(vm, 16.f), gui::p2pY(vm, 3.f),
        font, {"ON", "OFF"},
        gui::calc_char_size(vm, 135),
        10, data->gfxSettings->fullscreen ? 0 : 1);

    dropDownLists["VSYNC"] = new gui::DropDownList(
        gui::p2pX(vm, 25.f), gui::p2pY(vm, 59.f),
        gui::p2pX(vm, 16.f), gui::p2pY(vm, 3.f),
        font, {"ON", "OFF"},
        gui::calc_char_size(vm, 135),
        10, 1);

    // dropDownLists["ANTIALIASING"] = new gui::DropDownList(
    //     gui::p2pX(vm, 25.f), gui::p2pY(vm, 40.f),
    //     gui::p2pX(vm, 16.f), gui::p2pY(vm, 3.f),
    //     font, mode_labels,
    //     gui::calc_char_size(vm, 135),
    //     10);

    // Create options text
    optionsText.setFont(font);
    optionsText.setPosition(gui::p2pX(vm, 6.2f), gui::p2pY(vm, 40.f));
    optionsText.setCharacterSize(gui::calc_char_size(vm, 70));
    optionsText.setFillColor(sf::Color(255, 255, 255, 200));
    optionsText.setString("Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n");
}

void SettingsState::resetGUI()
{
    data->logger->log("SettingsState::resetGUI", DEBUG, "Resetting GUI. initGUI will be called.");

    for (auto &[key, button] : buttons)
        delete button;
    buttons.clear();

    for (auto &[key, ddl] : dropDownLists)
        delete ddl;
    dropDownLists.clear();

    initGUI();
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

SettingsState::SettingsState(StateData *data, MainMenuState *main_menu_state)
    : State(data), mainMenuState(main_menu_state)
{
    initVariables();
    initFonts();
    initKeybinds();
    initGUI();
}

SettingsState::~SettingsState()
{
    // Delete buttons
    for (auto &[key, button] : buttons)
        delete button;

    // Delete ddls
    for (auto &[key, ddl] : dropDownLists)
        delete ddl;
}

/* FUNCTIONS ===================================================================================================== */

void SettingsState::update(const float &dt)
{
    updateInput(dt);
    updateGUI(dt);
}

void SettingsState::render(sf::RenderTarget &target)
{
    background->render(target);
    target.draw(title);
    renderGUI(target);
    target.draw(optionsText);
}

void SettingsState::updateInput(const float &dt)
{
    updateMousePositions();
}

void SettingsState::updateGUI(const float &dt)
{
    background->play();

    // Updates all buttons based on mouse position view.
    for (auto &[key, button] : buttons)
    {
        button->update(sf::Vector2f(mousePosWindow));
        if (button->isPressed())
            data->soundSys->play("CLICK_BUTTON");
    }

    // Updates all ddls based on mouse position view and dt.
    for (auto &[key, ddl] : dropDownLists)
        ddl->update(mousePosWindow, dt);

    // Checks for returning
    if (buttons["BACK"]->isPressed())
    {
        data->logger->log("SettingsState::updateGUI", DEBUG, "Quitting state.");
        quit();
    }

    // Apply settings
    else if (buttons["APPLY"]->isPressed())
    {
        data->logger->log("SettingsState::updateGUI", DEBUG, "Applying new graphics settings.");

        gfxSettings->resolution = videoModes[dropDownLists["RESOLUTIONS"]->getSelectedElementId()];

        gfxSettings->fullscreen = dropDownLists.at("FULLSCREEN")->getSelectedElementId() == 0 ? true : false;

        if (gfxSettings->fullscreen)
        {
            window->create(gfxSettings->resolution, gfxSettings->title, sf::Style::Fullscreen);
        }
        else
        {
            window->create(gfxSettings->resolution, gfxSettings->title, sf::Style::Titlebar | sf::Style::Close);
        }

        window->setIcon(gfxSettings->icon.getSize().x, gfxSettings->icon.getSize().y, gfxSettings->icon.getPixelsPtr());

        resetGUI();

        mainMenuState->resetGUI();
    }
}

void SettingsState::renderGUI(sf::RenderTarget &target)
{
    // Render buttons
    for (auto &[key, button] : buttons)
        button->render(target);

    // Render ddls
    for (auto &[key, ddl] : dropDownLists)
        ddl->render(target);
}
