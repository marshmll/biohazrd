#include "stdafx.h"
#include "Engine.h"

/* INITIALIZERS FUNCTIONS */

void Engine::initVariables()
{
    this->currentPath = std::filesystem::current_path().string();

    this->window = nullptr;

    this->dt = 0.f;

    this->gridSize = 64.f; // Tile size.
}

void Engine::initGraphicsSettings()
{
    this->gfxSettings.loadFromFile("Config/graphics.ini");
}

void Engine::initWindow()
{
    // Create the window
    if (this->gfxSettings.fullscreen) // If in fullscreen mode
    {
        this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title,
                                            sf::Style::Fullscreen, this->gfxSettings.contextSettings);
    }
    else // If in window mode
    {
        this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title,
                                            sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);
    }

    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Engine::initKeys()
{
    std::ifstream ifs("Config/accepted_keys.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        int key_value = 0;

        while (ifs >> key >> key_value)
            this->acceptedKeys[key] = sf::Keyboard::Key(key_value);
    }
    else
        ErrorHandler::throwErr("GAME::INITKEYS::ERROR_COULD_NOT_LOAD_ACCEPTED_KEYS_INI\n");

    ifs.close();
}

void Engine::initStateData()
{
    this->data.states = &this->states;
    this->data.gfxSettings = &this->gfxSettings;
    this->data.window = this->window;
    this->data.acceptedKeys = &this->acceptedKeys;
    this->data.gridSize = this->gridSize;
}

void Engine::initStates()
{
    this->states.push(new MainMenuState(&this->data));
}

/* CONSTRUCTOR AND DESTRUCTOR */

Engine::Engine()
{
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();
}

Engine::~Engine()
{
    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

/* MAIN FUNCTIONS */

void Engine::run()
{
    while (this->isRunning())
    {
        // If windows has focus
        if (this->window->hasFocus())
        {
            this->update();
            this->render();
        }
    }
}

void Engine::update()
{
    this->updateDeltaTime();
    this->pollSFMLEvents();

    // If there are still states available
    if (!this->states.empty())
    {
        // Update the top state in the states stack
        this->states.top()->update(this->dt);

        // If the state wants to end
        if (this->states.top()->hasAskedToQuit())
        {
            // Delete the state and pop it from the stack.
            delete this->states.top();
            this->states.pop();
        }
    }
    // If there are no states
    else
    {
        // Quit application.
        this->endApplication();
    }
}

void Engine::render()
{
    // Clear window
    this->window->clear();

    // If there are states in the stack
    if (!this->states.empty())
    {
        // If the window has focus
        if (this->window->hasFocus())
        {
            // Render them into the window.
            this->states.top()->render(*this->window);
        }
    }

    // Display window
    this->window->display();
}

/* AUXILIARY FUNCTIONS */

void Engine::updateDeltaTime()
{
    this->dt = this->dtClock.restart().asSeconds();
}

void Engine::pollSFMLEvents()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->endApplication();
            break;

        default:
            break;
        }
    }
}

void Engine::endApplication()
{
    this->window->close();
}

/* ACESSORS */

const bool Engine::isRunning() const
{
    return this->window->isOpen();
}