/*
 * GraphicsSettings.cpp
 *
 *  Created on: 1 de mai. de 2024
 *      Author: renan
 */

#include "stdafx.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
    title = "BIOHAZRD";
    resolution = sf::VideoMode::getDesktopMode();
    fullscreen = true;
    verticalSync = false;
    frameRateLimit = 60;
    contextSettings.antialiasingLevel = 0;
    videoModes = sf::VideoMode::getFullscreenModes();
}

GraphicsSettings::~GraphicsSettings()
{
}

/* FUNCTIONS */

void GraphicsSettings::saveToFile(const std::string path)
{
    std::ofstream ofs(path);

    videoModes = sf::VideoMode::getFullscreenModes();

    if (ofs.is_open())
    {
        // Write data into file.
        ofs << title << "\n"
            << resolution.width << " "
            << resolution.height << "\n"
            << fullscreen << "\n"
            << frameRateLimit << "\n"
            << verticalSync << "\n"
            << contextSettings.antialiasingLevel;
    }
    else
        ErrorHandler::throwErr("GRAPHICSSETTINGS::SAVETOFILE::ERROR_COULD_NOT_SAVE_GRAPHICS_INI\n");

    ofs.close();
}

void GraphicsSettings::loadFromFile(const std::string path)
{
    std::ifstream ifs(path);

    videoModes = sf::VideoMode::getFullscreenModes();

    if (ifs.is_open())
    {
        // Read from window.ini to variables
        ifs >>
            title >>
            resolution.width >>
            resolution.height >>
            fullscreen >>
            frameRateLimit >>
            verticalSync >>
            contextSettings.antialiasingLevel;
    }
    else
        ErrorHandler::throwErr("GRAPHICSSETTINGS::LOADFROMFILE::ERROR_COULD_NOT_LOAD_GRAPHICS_INI\n");

    ifs.close();
}
