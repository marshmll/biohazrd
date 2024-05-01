#ifndef GAME_H_
#define GAME_H_

#include "../States/MainMenuState.h"

class Game
{
private:
	class GraphicsSettings
	{
	public:
		/* VARIABLES */
		std::string title;
		sf::VideoMode resolution;
		bool fullscreen;
		bool verticalSync;
		unsigned frameRateLimit;
		sf::ContextSettings contextSettings;
		std::vector<sf::VideoMode> videoModes;

		GraphicsSettings()
		{
			this->title = "";
			this->resolution = sf::VideoMode::getDesktopMode();
			this->fullscreen = true;
			this->verticalSync = false;
			this->frameRateLimit = 60;
			this->contextSettings.antialiasingLevel = 0;
			this->videoModes = sf::VideoMode::getFullscreenModes();
		}

		/* FUNCTIONS */
		void saveToFile(const std::string path)
		{
			std::ofstream ofs(path);

			this->videoModes = sf::VideoMode::getFullscreenModes();

			if (ofs.is_open())
			{
				// Read from window.ini to variables
				ofs << title;
				ofs << this->resolution.width;
				ofs << " ";
				ofs << this->resolution.height;
				ofs << this->fullscreen;
				ofs << this->frameRateLimit;
				ofs << this->verticalSync;
				ofs << this->contextSettings.antialiasingLevel;
			}
			else
			{
				throw std::runtime_error(
						"GRAPHICSSETTINGS::SAVETOFILE::ERROR_COULD_NOT_SAVE_GRAPHICS_INI\n");
			}

			ofs.close();
		}

		void loadFromFile(const std::string path)
		{
			std::ifstream ifs(path);

			this->videoModes = sf::VideoMode::getFullscreenModes();

			if (ifs.is_open())
			{
				// Read from window.ini to variables
				std::getline(ifs, this->title);
				ifs >> this->resolution.width;
				ifs >> this->resolution.height;
				ifs >> this->fullscreen;
				ifs >> this->frameRateLimit;
				ifs >> this->verticalSync;
				ifs >> this->contextSettings.antialiasingLevel;
			}
			else
			{
				throw std::runtime_error(
						"GRAPHICSSETTINGS::LOADFROMFILE::ERROR_COULD_NOT_LOAD_GRAPHICS_INI\n");
			}

			ifs.close();
		}
	};

	/* VARIABLES */
	std::string currentPath;

	GraphicsSettings gfxSettings;

	sf::RenderWindow *window;
	sf::Event event;

	sf::Clock dtClock;

	float dt; // Delta Time

	std::stack<State*> states; // A stack with pointers to the game states

	std::map<std::string, sf::Keyboard::Key> acceptedKeys; // Keys the game accepts

	/* INITIALIZERS FUNCTIONS */
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStates();

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	Game();
	virtual ~Game();

	/* MAIN FUNCTIONS */
	void run();
	void update();
	void render();

	/* AUXILIARY FUNCTIONS */
	void updateDeltaTime();
	void pollSFMLEvents();
	void endApplication();

	/* ACESSORS */
	const bool isRunning() const;
};

#endif /* GAME_H_ */
