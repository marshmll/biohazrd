#include "stdafx.h"
#include "EditorMode.h"

/* CONSTRUCTOR AND DESTRUCTOR */

EditorMode::EditorMode(StateData *data, EditorStateData *editor_data, std::string mode_name)
    : data(data), editorData(editor_data)
{
    this->modeIndicatorText.setFont(*editor_data->font);
    this->modeIndicatorText.setCharacterSize(gui::calc_char_size(data->gfxSettings->resolution, 140));
    this->modeIndicatorText.setFillColor(sf::Color(255, 255, 255, 150));
    this->modeIndicatorText.setString(mode_name);
    this->modeIndicatorText.setPosition((float)data->gfxSettings->resolution.width - std::floor(this->modeIndicatorText.getGlobalBounds().width) - 10.f, 15.f);
}

EditorMode::~EditorMode()
{
}
