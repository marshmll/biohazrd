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
    if (!font.loadFromFile("Fonts/VCR_OSD_MONO_1.001.ttf"))
    {
        data->logger->log("WorldSelectionState::initFonts", ERROR, "Could not load fonts.");
        ErrorHandler::throwErr("ERROR::WORLDSELECTIONSTATE::INITFONTS::COULD_NOT_LOAD_FONT\n");
    }
}

void WorldSelectionState::initGUI()
{
    // Background
    background = data->preloadedVideos->at("BACKGROUND");

    data->logger->log("MainMenuState::initGUI", DEBUG, "Successfully loaded background video.");

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

    deleteConfirmationModal = new gui::ConfirmationModal(
        "Do you want to delete the world forever?", gui::calc_char_size(vm, 90),
        sf::Color(20, 20, 20, 100), sf::Color(50, 50, 50, 220), font, vm);

    worldDataModal = new gui::WorldDataModal(sf::Color(20, 20, 20, 100), sf::Color(50, 50, 50, 220), font, vm);
}

void WorldSelectionState::initWorldDescriptors()
{
    std::vector<std::string> map_filepaths;

    std::filesystem::path fpath("Maps/");
    std::filesystem::directory_iterator start(fpath);
    std::filesystem::directory_iterator end;
    std::transform(start, end, std::back_inserter(map_filepaths),
                   [](const std::filesystem::directory_entry &entry)
                   { return entry.path().string(); });

    int counter = 0;
    for (auto &fpath : map_filepaths)
    {
        if (fpath.size() > 7) // .biomap
        {
            if (fpath.substr(fpath.size() - 7, 7) == ".biomap")
            {
                std::string title;
                std::string description;
                std::time_t creation_time;

                std::ifstream ifs(fpath);

                if (!ifs.is_open())
                {
                    data->logger->log("WorldSelectionState::initWorldDescriptors", ERROR,
                                      "An error ocurred while trying to open file: " + fpath);

                    ErrorHandler::throwErr(
                        "WORDLSELECTIONSTATE::INITWORLDDESCRIPTORS::ERR_COULD_NOT_OPEN_FILE: " + fpath);
                }

                std::getline(ifs, title);
                std::getline(ifs, description);
                ifs >> creation_time;

                ifs.close();

                worldDescriptors.push_back(
                    new WorldDescriptorBox(fpath, title, description, creation_time,
                                           font, vm, gui::p2pY(vm, 20.f + (counter * 15.f)),
                                           iconTexture));

                ++counter;
            }
        }
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
    initWorldDescriptors();
}

WorldSelectionState::~WorldSelectionState()
{
    for (auto &[key, button] : buttons)
        delete button;

    for (auto &descriptor : worldDescriptors)
        delete descriptor;

    delete deleteConfirmationModal;
    delete worldDataModal;
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
    background->play();
    deleteConfirmationModal->update(dt, mousePosView);
    worldDataModal->update(dt, mousePosView, *data->event);

    if (deleteConfirmationModal->isActive())
    {
        if (deleteConfirmationModal->isAnswered())
        {
            if (deleteConfirmationModal->getAnswer() == true)
            {
                std::cout << "WorldSelectionState::UpdateGUI > Deleting " << selectedDescriptor->filename << "\n";

                remove(selectedDescriptor->filename.c_str());
                delete selectedDescriptor;

                worldDescriptors.erase(std::find(worldDescriptors.begin(), worldDescriptors.end(), selectedDescriptor));
                selectedDescriptor = nullptr;

                updateWorldDescriptors();
            }
            data->soundSys->play("CLICK_BUTTON");

            deleteConfirmationModal->setActive(false);
        }

        return;
    }

    if (worldDataModal->isActive())
    {
        if (worldDataModal->isConfirmed())
        {
            const std::string map_title = worldDataModal->getTitle();
            const std::string map_description = worldDataModal->getDescription();

            data->soundSys->play("CLICK_BUTTON");

            data->soundSys->stop("MAIN_THEME");

            data->logger->log("WorldSelectionState::updateGUI", DEBUG, "Creating new world: " + map_title);
            data->states->pop();
            data->states->push(new EditorState(data, map_title, map_description));

            worldDataModal->setActive(false);
        }
        return;
    }

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

        data->logger->log("WorldSelectionState::updateGUI", DEBUG, "Pushing a new GameState from the map: " + selectedDescriptor->filename);
        data->states->push(new GameState(data, selectedDescriptor->filename));
    }
    else if (hasElapsedMouseTimeMax(buttons.at("DELETE")->isPressed()) && selectedDescriptor != nullptr)
    {
        deleteConfirmationModal->display();
    }
    else if (hasElapsedMouseTimeMax(buttons.at("EDIT")->isPressed()) && selectedDescriptor != nullptr)
    {
        data->logger->log("WorldSelectionState::updateGUI", DEBUG, "Popping self from stack.");
        data->states->pop();
        data->soundSys->stop("MAIN_THEME");

        data->logger->log("WorldSelectionState::updateGUI", DEBUG, "Pushing a new EditorState from the map: " + selectedDescriptor->filename);
        data->states->push(new EditorState(data, selectedDescriptor->filename));
    }
    else if (hasElapsedMouseTimeMax(buttons.at("CREATE")->isPressed()))
    {
        worldDataModal->display();
    }
}

void WorldSelectionState::updateWorldDescriptors()
{
    int counter = 0;

    for (auto &descriptor : worldDescriptors)
    {
        descriptor->setYPosition(vm, gui::p2pY(vm, 20.f + (counter * 15.f)));

        ++counter;
    }
}

void WorldSelectionState::renderGUI(sf::RenderTarget &target)
{
    background->render(target);

    target.draw(headerBg);
    target.draw(headerText);

    target.draw(menuBg);

    for (auto &[key, button] : buttons)
        button->render(target);

    for (auto &descriptor : worldDescriptors)
        descriptor->render(target);

    deleteConfirmationModal->render(target);

    worldDataModal->render(target);
}
