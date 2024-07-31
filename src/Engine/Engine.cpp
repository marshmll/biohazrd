#include "stdafx.h"
#include "Engine.h"

/* INITIALIZERS FUNCTIONS ======================================================================================== */

void Engine::initLogger()
{
    logger = new Logger(DEBUG_MODE);

    logger->begin();
}

void Engine::initVariables()
{
    currentPath = std::filesystem::current_path().string();

    window = nullptr;

    dt = 0.f;

    gridSize = 32.f; // Tile size.
}

void Engine::initGraphicsSettings()
{
    gfxSettings.loadFromFile("Config/graphics.ini");

    logger->log("Engine::initGraphicsSettings", DEBUG, "Successfully loaded graphics settings.");
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
    IniParser parser("Config/accepted_keys.ini");

    for (auto &[key, keycode] : parser.getAllKeyValuePairs("AcceptedKeys"))
        acceptedKeys[key] = static_cast<sf::Keyboard::Key>(std::stoi(keycode));

    logger->log("Engine::initKeys", INFO, "Initialized " + std::to_string(acceptedKeys.size()) + " keys.");
}

void Engine::initSoundSystem()
{
    soundSys = new SoundSystem("Config/sounds.ini");
}

void Engine::initStateData()
{
    data.logger = logger;
    data.soundSys = soundSys;
    data.states = &states;
    data.gfxSettings = &gfxSettings;
    data.window = window;
    data.event = &event;
    data.acceptedKeys = &acceptedKeys;
    data.gridSize = gridSize;
}

void Engine::initStates()
{
    logger->log("Engine::initStates", DEBUG, "Pushing a new MainMenuState.");
    states.push(new MainMenuState(&data));
}

/* CONSTRUCTOR AND DESTRUCTOR =================================================================================== */

Engine::Engine()
{
    initLogger();
    initVariables();
    initGraphicsSettings();
    initWindow();
    initKeys();
    initSoundSystem();
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

    logger->log("Engine::~Engine", DEBUG, "Successfully called destructor. Ending logs.");

    logger->end();

    delete logger;
    delete soundSys;
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
    logger->log("Engine::endApplication", DEBUG, "Closing the window.");
    window->close();
}

/* ACCESSORS ===================================================================================================== */

const bool Engine::isRunning() const
{
    return window->isOpen();
}