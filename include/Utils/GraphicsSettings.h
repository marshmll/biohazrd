#ifndef GRAPHICSSETTINGS_H_
#define GRAPHICSSETTINGS_H_

#include "IniParser.h"

class GraphicsSettings
{
public:
    /* VARIABLES ================================================================================================= */

    string title;
    VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned frameRateLimit;
    ContextSettings contextSettings;
    vector<VideoMode> videoModes;

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
    void saveToFile(const string path);

    /**
     * @brief Loads the graphics settings from a graphics.ini
     * file.
     *
     * @return void
     */
    void loadFromFile(const string path);
};
#endif /* GRAPHICSSETTINGS_H_ */
