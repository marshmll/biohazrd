#ifndef EDITORMODE_H_
#define EDITORMODE_H_

#include "State.h"
#include "TileMap.h"
#include "GUI.h"

typedef struct EditorStateData
{
    map<string, Keyboard::Key> *keybinds;
    TileMap *tileMap;
    View *editorCamera;
    Font *font;
    Clock *keyTimer;
    Int32 *keyTimerMax;
    Clock *mouseTimer;
    Int32 *mouseTimerMax;
    Vector2i *mousePosScreen;
    Vector2i *mousePosWindow;
    Vector2f *mousePosView;
    Vector2i *mousePosGrid;
} EditorStateData;

class EditorMode
{
protected:
    /* VARIABLES ================================================================================================= */

    StateData *data;

    EditorStateData *editorData;

    Text modeIndicatorText;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    EditorMode(StateData *data, EditorStateData *editor_data, string mode_name);

    virtual ~EditorMode();

    /* FUNCTIONS ================================================================================================= */

    /**
     * @brief Updates the EditorMode.
     * @note -> Checks for updates in the user input.
     * @note -> Update buttons.
     *
     * @return void
     */
    virtual void update(const float &dt) = 0;

    /**
     * @brief Renders the editor mode.
     * @note -> Draw background
     * @note -> Render buttons.
     *
     * @return void
     */
    virtual void render(RenderTarget &target) = 0;

    /**
     * @brief Updates the user input.
     *
     * @return void
     */
    virtual void updateInput(const float &dt) = 0;

    /**
     * @brief Updates the GUI elements.
     *
     * @return void
     */
    virtual void updateGUI(const float &dt) = 0;

    /**
     * @brief Renders the GUI elements into a target
     *
     * @return void
     */
    virtual void renderGUI(RenderTarget &target) = 0;

    const bool hasElapsedKeyTimeMax();

    const bool hasElapsedMouseTimeMax();
};

#endif /* EDITORMODE_H_ */
