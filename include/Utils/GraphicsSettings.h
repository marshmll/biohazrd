#ifndef GRAPHICSSETTINGS_H_
#define GRAPHICSSETTINGS_H_

#include "IniParser.h"

class GraphicsSettings
{
public:
    /* VARIABLES ================================================================================================= */ 

    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;

    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    /**
     * @brief Graphics Settings constructor.
     */
    GraphicsSettings();

    /**
     * @brief Graphics Settings destructor.
     */
    ~GraphicsSettings();

    /* FUNCTIONS ================================================================================================= */

    /**
     * @brief Saves the graphics settings into a graphics.ini
     * file.
     *
     * @return void
     */
    void saveToFile(const std::string path);

    /**
     * @brief Loads the graphics settings from a graphics.ini
     * file.
     *
     * @return void
     */
    void loadFromFile(const std::string path);
};
#endif /* GRAPHICSSETTINGS_H_ */
