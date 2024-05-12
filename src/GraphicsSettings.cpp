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
	this->title = "BIOHAZRD";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = true;
	this->verticalSync = false;
	this->frameRateLimit = 60;
	this->contextSettings.antialiasingLevel = 0;
	this->videoModes = sf::VideoMode::getFullscreenModes();
}

GraphicsSettings::~GraphicsSettings()
{

}

/* FUNCTIONS */
void GraphicsSettings::saveToFile(const std::string path)
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

void GraphicsSettings::loadFromFile(const std::string path)
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
