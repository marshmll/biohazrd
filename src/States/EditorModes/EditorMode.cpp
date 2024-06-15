#include "stdafx.h"
#include "EditorMode.h"

/* CONSTRUCTOR AND DESTRUCTOR */

EditorMode::EditorMode(StateData *data, EditorStateData *editor_data)
    : data(data), editorData(editor_data)
{
}

EditorMode::~EditorMode()
{
}
