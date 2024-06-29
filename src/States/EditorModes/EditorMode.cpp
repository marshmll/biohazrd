#include "stdafx.h"
#include "EditorMode.h"

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

EditorMode::EditorMode(StateData *data, EditorStateData *editor_data, string mode_name)
    : data(data), editorData(editor_data)
{
    modeIndicatorText.setFont(*editor_data->font);
    modeIndicatorText.setCharacterSize(gui::calc_char_size(data->gfxSettings->resolution, 140));
    modeIndicatorText.setFillColor(sf::Color(255, 255, 255, 150));
    modeIndicatorText.setString(mode_name);
    modeIndicatorText.setPosition((float)data->gfxSettings->resolution.width - floor(modeIndicatorText.getGlobalBounds().width) - 10.f, 15.f);
}

EditorMode::~EditorMode()
{
}

/* FUNCTIONS ===================================================================================================== */

const bool EditorMode::hasElapsedKeyTimeMax()
{
    if (editorData->keyTimer->getElapsedTime().asMilliseconds() >= *editorData->keyTimerMax)
    {
        editorData->keyTimer->restart();

        return true;
    }

    return false;
}

const bool EditorMode::hasElapsedMouseTimeMax()
{
    if (editorData->mouseTimer->getElapsedTime().asMilliseconds() >= *editorData->mouseTimerMax)
    {
        editorData->mouseTimer->restart();

        return true;
    }

    return false;
}
