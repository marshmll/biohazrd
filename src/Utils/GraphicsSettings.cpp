/*
 * GraphicsSettings.cpp
 *
 *  Created on: 1 de mai. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
#include "GraphicsSettings.h"

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

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

/* FUNCTIONS ===================================================================================================== */

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
    IniParser parser;

    parser.loadFromFile(path);

    title = parser.getProperty("Graphics", "Title");
    resolution.width = parser.getInt("Graphics", "ResolutionWidth");
    resolution.height = parser.getInt("Graphics", "ResolutionHeight");
    fullscreen = parser.getBool("Graphics", "Fullscreen");
    frameRateLimit = parser.getInt("Graphics", "FramerateLimit");
    verticalSync = parser.getBool("Graphics", "VSync");
    contextSettings.antialiasingLevel = parser.getInt("Graphics", "AntialiasingLevel");
}
