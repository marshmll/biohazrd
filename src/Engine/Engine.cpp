#include "stdafx.h"
#include "Engine.h"

/* INITIALIZERS FUNCTIONS ======================================================================================== */

void Engine::initVariables()
{
    currentPath = std::filesystem::current_path().string();

    window = nullptr;

    dt = 0.f;

    gridSize = 64.f; // Tile size.
}

void Engine::initGraphicsSettings()
{
    gfxSettings.loadFromFile("Config/graphics.ini");
}

void Engine::initWindow()
{
    // Create the window
    if (gfxSettings.fullscreen) // If in fullscreen mode
    {
        window = new sf::RenderWindow(gfxSettings.resolution, gfxSettings.title,
                                      sf::Style::Fullscreen, gfxSettings.contextSettings);
    }
    else // If in window mode
    {
        window = new sf::RenderWindow(gfxSettings.resolution, gfxSettings.title,
                                      sf::Style::Titlebar | sf::Style::Close, gfxSettings.contextSettings);
    }

    window->setFramerateLimit(gfxSettings.frameRateLimit);
    window->setVerticalSyncEnabled(gfxSettings.verticalSync);
}

void Engine::initKeys()
{
    std::ifstream ifs("Config/accepted_keys.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value)
            acceptedKeys[key] = sf::Keyboard::Key(key_value);
    }
    else
        ErrorHandler::throwErr("GAME::INITKEYS::ERROR_COULD_NOT_LOAD_ACCEPTED_KEYS_INI\n");

    ifs.close();
}

void Engine::initStateData()
{
    data.states = &states;
    data.gfxSettings = &gfxSettings;
    data.window = window;
    data.acceptedKeys = &acceptedKeys;
    data.gridSize = gridSize;
}

void Engine::initStates()
{
    states.push(new MainMenuState(&data));
}

/* CONSTRUCTOR AND DESTRUCTOR =================================================================================== */

Engine::Engine()
{
    initVariables();
    initGraphicsSettings();
    initWindow();
    initKeys();
    initStateData();
    initStates();
}

Engine::~Engine()
{
    delete window;

    while (!states.empty())
    {
        delete states.top();
        states.pop();
    }
}

/* MAIN FUNCTIONS ================================================================================================= */

void Engine::run()
{
    while (isRunning())
    {
        // If windows has focus
        if (window->hasFocus())
        {
            update();
            render();
        }
    }
}

void Engine::update()
{
    updateDeltaTime();
    pollSFMLEvents();

    // If there are still states available
    if (!states.empty())
    {
        // Update the top state in the states stack
        states.top()->update(dt);

        // If the state wants to end
        if (states.top()->hasAskedToQuit())
        {
            // Delete the state and pop it from the stack.
            delete states.top();
            states.pop();
        }
    }
    // If there are no states
    else
    {
        // Quit application.
        endApplication();
    }
}

void Engine::render()
{
    // Clear window
    window->clear();

    // If there are states in the stack
    if (!states.empty())
    {
        // If the window has focus
        if (window->hasFocus())
        {
            // Render them into the window.
            states.top()->render(*window);
        }
    }

    // Display window
    window->display();
}

/* AUXILIARY FUNCTIONS =========================================================================================== */

void Engine::updateDeltaTime()
{
    dt = dtClock.restart().asSeconds();
}

void Engine::pollSFMLEvents()
{
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            endApplication();
            break;

        default:
            break;
        }
    }
}

void Engine::endApplication()
{
    window->close();
}

/* ACCESSORS ===================================================================================================== */

const bool Engine::isRunning() const
{
    return window->isOpen();
}