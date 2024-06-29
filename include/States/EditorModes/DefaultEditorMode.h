#ifndef DEFAULTEDITORMODE_H_
#define DEFAULTEDITORMODE_H_

#include "State.h"
#include "EditorMode.h"

class DefaultEditorMode : public EditorMode
{
private:
    /* VARIABLES ============================================================================================ */

    Text cursorText;
    RectangleShape sidebar;
    RectangleShape selectorRect;
    RectangleShape collisionRect;
    IntRect textureRect;

    gui::TextureSelector *textureSelector;
    gui::CollisionEditor *collisionEditor;

    bool collision;

    float collBoxWidth;
    float collBoxHeight;
    float collBoxOffsetX;
    float collBoxOffsetY;

    short type;
    unsigned layer;

    /* INITIALIZERS =========================================================================================== */

    void initVariables();

    void initGUI();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ============================================================================= */

    DefaultEditorMode(StateData *data, EditorStateData *editor_data);

    virtual ~DefaultEditorMode();

    /* FUNCTIONS =============================================================================================== */

    /**
     * @brief Updates the EditorMode.
     * @note -> Checks for updates in the user input.
     * @note -> Update buttons.
     *
     * @return void
     */
    void update(const float &dt);

    /**
     * @brief Renders the editor mode.
     * @note -> Draw background
     * @note -> Render buttons.
     *
     * @return void
     */
    void render(RenderTarget &target);

    /**
     * @brief Updates the user input.
     *
     * @return void
     */
    void updateInput(const float &dt);

    /**
     * @brief Updates the GUI elements.
     *
     * @return void
     */
    void updateGUI(const float &dt);

    /**
     * @brief Renders the GUI elements into a target.
     *
     * @return void
     */
    void renderGUI(RenderTarget &target);

    /* ACCESSORS =============================================================================================== */

    /**
     * @brief Returns the type name of a tile as a string.
     *
     * @return std::string
     */
    const string getTypeName() const;
};

#endif /* DEFAULTEDITORMODE_H_ */
