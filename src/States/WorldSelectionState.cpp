#include "stdafx.h"
#include "WorldSelectionState.h"

/* INITIALIZERS ================================================================================================== */

void WorldSelectionState::initVariables()
{
    if (!iconTexture.loadFromFile("Assets/Images/Icons/world_default_icon.png"))
    {
        data->logger->log("WorldSelectionState::initVariables", ERROR, "Could not load icon texture.");
        ErrorHandler::throwErr("ERROR::WORLDSELECTIONS::INITVARIABLES::COULD_NOT_LOAD_ICON\n");
    }

    selectedDescriptor = nullptr;
}

void WorldSelectionState::initKeybinds()
{
}

void WorldSelectionState::initFonts()
{
    if (!font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
    {
        data->logger->log("WorldSelectionState::initFonts", ERROR, "Could not load fonts.");
        ErrorHandler::throwErr("ERROR::WORLDSELECTIONSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n");
    }
}

void WorldSelectionState::initGUI()
{
    // Background
    background.setSize(sf::Vector2f(vm.width, vm.height));
    background.setPosition(0.f, 0.f);

    if (!backgroundTexture.loadFromFile("Assets/Images/Backgrounds/main_menu_bg.png"))
    {
        data->logger->log("WorldSelectionState::initGUI", ERROR, "Could not load background image.");
        ErrorHandler::throwErr("ERROR::WORLDSELECTIONSTATE::INITBACKGROUND::ERROR_COULD_NOT_LOAD_MAINMENU_BG\n");
    }

    background.setTexture(&backgroundTexture);

    // Header
    headerBg.setSize(sf::Vector2f(vm.width, gui::p2pY(vm, 15.f)));
    headerBg.setPosition(0.f, 0.f);
    headerBg.setFillColor(sf::Color(20, 20, 20, 200));

    headerText.setFont(font);
    headerText.setCharacterSize(gui::calc_char_size(vm, 70));
    headerText.setString("Select World");
    headerText.setFillColor(sf::Color::White);
    headerText.setPosition(vm.width / 2.f - headerText.getGlobalBounds().width / 2.f,
                           headerBg.getSize().y / 2.f - headerText.getGlobalBounds().height / 2.f - 3.f);

    // Menu
    menuBg.setSize(sf::Vector2f(vm.width, gui::p2pY(vm, 20.f)));
    menuBg.setPosition(0.f, vm.height - menuBg.getSize().y);
    menuBg.setFillColor(sf::Color(20, 20, 20, 200));

    // Buttons
    buttons["PLAY"] = new gui::Button(
        gui::p2pX(vm, 25.f), menuBg.getPosition().y + gui::p2pY(vm, 2.f),
        gui::p2pX(vm, 24.5f), gui::p2pY(vm, 6.2f),
        font, "Play Selected World", gui::calc_char_size(vm, 112),
        sf::Color(255, 255, 255, 255), sf::Color(250, 250, 250, 255), sf::Color(20, 20, 20, 50),
        sf::Color(100, 100, 100, 250), sf::Color(120, 120, 120, 250), sf::Color(80, 80, 80, 250));

    buttons["DELETE"] = new gui::Button(
        gui::p2pX(vm, 50.f), menuBg.getPosition().y + gui::p2pY(vm, 2.f),
        gui::p2pX(vm, 24.5f), gui::p2pY(vm, 6.2f),
        font, "Delete Selected World", gui::calc_char_size(vm, 112),
        sf::Color(255, 255, 255, 255), sf::Color(250, 250, 250, 255), sf::Color(20, 20, 20, 50),
        sf::Color(100, 100, 100, 250), sf::Color(120, 120, 120, 250), sf::Color(80, 80, 80, 250));

    buttons["EDIT"] = new gui::Button(
        gui::p2pX(vm, 25.f), menuBg.getPosition().y + gui::p2pY(vm, 9.2f),
        gui::p2pX(vm, 24.5f), gui::p2pY(vm, 6.2f),
        font, "Edit Selected World", gui::calc_char_size(vm, 112),
        sf::Color(255, 255, 255, 255), sf::Color(250, 250, 250, 255), sf::Color(20, 20, 20, 50),
        sf::Color(100, 100, 100, 250), sf::Color(120, 120, 120, 250), sf::Color(80, 80, 80, 250));

    buttons["CREATE"] = new gui::Button(
        gui::p2pX(vm, 50.f), menuBg.getPosition().y + gui::p2pY(vm, 9.2f),
        gui::p2pX(vm, 24.5f), gui::p2pY(vm, 6.2f),
        font, "Create New World", gui::calc_char_size(vm, 112),
        sf::Color(255, 255, 255, 255), sf::Color(250, 250, 250, 255), sf::Color(20, 20, 20, 50),
        sf::Color(100, 100, 100, 250), sf::Color(120, 120, 120, 250), sf::Color(80, 80, 80, 250));

    buttons["CANCEL"] = new gui::Button(
        gui::p2pX(vm, 80.f), menuBg.getPosition().y + gui::p2pY(vm, 12.2f),
        gui::p2pX(vm, 10.f), gui::p2pY(vm, 3.2f),
        font, "Cancel", gui::calc_char_size(vm, 125),
        sf::Color(255, 255, 255, 255), sf::Color(250, 250, 250, 255), sf::Color(20, 20, 20, 50),
        sf::Color(100, 100, 100, 250), sf::Color(120, 120, 120, 250), sf::Color(80, 80, 80, 250));

    // Map descriptors
    IniParser parser("Maps/maps.ini");
    std::vector<std::pair<std::string, std::string>> maps = parser.getAllKeyValuePairs("Maps");

    int counter = 0;

    for (auto &[key, filename] : maps)
    {
        std::string title;
        std::string description;
        std::time_t creation_time;

        std::ifstream ifs(filename);

        if (!ifs.is_open())
        {
            data->logger->log("WorldSelectionState::initGUI", ERROR, "An error ocurred while trying to open file: " + filename);
            ErrorHandler::throwErr("WORDLSELECTIONSTATE::INITGUI::ERR_COULD_NOT_OPEN_FILE: " + filename);
        }

        std::getline(ifs, title);
        std::getline(ifs, description);
        ifs >> creation_time;

        ifs.close();

        worldDescriptors.push_back(new WorldDescriptorBox(filename, title, description, creation_time,
                                                          font, vm, gui::p2pY(vm, 20.f + (counter * 15.f)),
                                                          iconTexture));

        ++counter;
    }

    data->logger->log("WorldSelectionState::initGUI", INFO, "Loaded " + std::to_string(counter) + " map files.");
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

WorldSelectionState::WorldSelectionState(StateData *data)
    : State(data)
{
    initVariables();
    initKeybinds();
    initFonts();
    initGUI();
}

WorldSelectionState::~WorldSelectionState()
{
    for (auto &[key, button] : buttons)
        delete button;

    for (auto &descriptor : worldDescriptors)
        delete descriptor;
}

/* FUNCTIONS ===================================================================================================== */

void WorldSelectionState::update(const float &dt)
{
    updateMousePositions();
    updateInput(dt);
    updateGUI(dt);
}

void WorldSelectionState::render(sf::RenderTarget &target)
{
    renderGUI(target);
}

void WorldSelectionState::updateInput(const float &dt)
{
}

void WorldSelectionState::updateGUI(const float &dt)
{
    for (auto &[key, button] : buttons)
    {
        button->update(mousePosView);

        if (button->isPressed())
            data->soundSys->play("CLICK_BUTTON");
    }

    for (auto &descriptor : worldDescriptors)
    {
        descriptor->update(dt, mousePosView);

        if (descriptor->isSelected() && selectedDescriptor != descriptor)
        {
            data->soundSys->play("CLICK_BUTTON");

            if (selectedDescriptor != nullptr)
            {
                selectedDescriptor->deselect();
                selectedDescriptor = descriptor;
            }
            else
            {
                selectedDescriptor = descriptor;
            }
        }
    }

    if (hasElapsedMouseTimeMax(buttons.at("CANCEL")->isPressed()))
    {
        data->logger->log("WorldSelectionState::updateGUI", DEBUG, "Quitting state.");
        quit();
    }
    else if (hasElapsedMouseTimeMax(buttons.at("PLAY")->isPressed()) && selectedDescriptor != nullptr)
    {
        data->logger->log("WorldSelectionState::updateGUI", DEBUG, "Popping self from stack.");
        data->soundSys->stop("MAIN_THEME");

        data->states->pop();


        data->logger->log("WorldSelectionState::updateGUI", DEBUG, "Pushing a new GameState from the map: " + selectedDescriptor->getFilename());
        data->states->push(new GameState(data, selectedDescriptor->getFilename()));
    }
}

void WorldSelectionState::renderGUI(sf::RenderTarget &target)
{
    target.draw(background);

    target.draw(headerBg);
    target.draw(headerText);

    target.draw(menuBg);

    for (auto &[key, button] : buttons)
        button->render(target);

    for (auto &descriptor : worldDescriptors)
        descriptor->render(target);
}
