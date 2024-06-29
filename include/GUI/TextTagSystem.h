#ifndef TEXTTAGSYSTEM_H_
#define TEXTTAGSYSTEM_H_

#include "GUI.h"

enum TextTagType
{
    DEFAULT_TAG = 0,
    NEGATIVE_TAG,
    POSITIVE_TAG,
    DAMAGE_TAG,
    EXPERIENCE_TAG,
    ENVIROMENTAL_TAG,
};

class TextTagSystem
{
private:
    /* Text Tag private class. */
    class TextTag
    {
    public:
        /* VARIABLES ============================================================= */

        Text text;

        short dirX;
        short dirY;

        float speedX;
        float speedY;

        float initialLifetime;
        float currentLifetime;

        bool fadeFx;

        /* CONSTRUCTOR AND DESTRUCTOR ============================================ */

        TextTag(const float x, const float y,
                const short dir_x, const short dir_y,
                const float speed_x, const float speed_y,
                const float lifetime,
                const Color color,
                const unsigned char_size,
                const string string, Font &font,
                const bool use_fade_fx = USE_FADE_FX)
        {
            dirX = dir_x;
            dirY = dir_y;

            speedX = speed_x;
            speedY = speed_y;

            initialLifetime = lifetime;
            currentLifetime = lifetime;

            text.setFont(font);
            text.setCharacterSize(char_size);
            text.setFillColor(color);
            text.setString(string);
            text.setPosition(x, y);

            fadeFx = use_fade_fx;
        }

        TextTag(TextTag *tag, const float x, const float y, const string string)
        {
            dirX = tag->dirX;
            dirY = tag->dirY;

            speedX = tag->speedX;
            speedY = tag->speedY;

            initialLifetime = tag->initialLifetime;
            currentLifetime = tag->currentLifetime;

            text = tag->text;
            text.setString(string);
            text.setPosition(x, y);

            fadeFx = tag->fadeFx;
        }

        ~TextTag() {}

        /* FUNCTIONS ============================================================= */

        void update(const float &dt)
        {
            if (!isExpired())
            {
                if (fadeFx)
                {
                    float opacity_percent = currentLifetime / initialLifetime;

                    Uint8 alpha = static_cast<Uint8>(255 * opacity_percent);

                    text.setFillColor(Color(text.getFillColor().r,
                                                text.getFillColor().g,
                                                text.getFillColor().b,
                                                alpha));
                }

                text.move((speedX * dirX) * dt, (speedY * dirY) * dt);
            }

            updateLifetime(dt);
        }

        void render(RenderTarget &target)
        {
            target.draw(text);
        }

        void updateLifetime(const float &dt)
        {
            if (currentLifetime > 0.f)
                currentLifetime -= 100.f * dt;
            else
                currentLifetime = 0.f;
        }

        /* ACCESSORS ============================================================= */

        inline const bool isExpired() const { return currentLifetime <= 0.f; }

        /* MODIFIERS ============================================================= */

        void setDirection(const short dir_x, const short dir_y)
        {
            dirX = dir_x;
            dirY = dir_y;
        }

        void setSpeed(const float speed_x, const float speed_y)
        {
            speedX = speed_x;
            speedY = speed_y;
        }

        void setLifetime(const float new_lifetime)
        {
            initialLifetime = new_lifetime;
            currentLifetime = new_lifetime;
        }

        void setString(const string string)
        {
            text.setString(string);
        }

        void setPosition(const float x, const float y)
        {
            text.setPosition(x, y);
        }
    };

    /* VARIABLES =================================================================================================== */

    Font font;

    VideoMode &vm;

    map<TextTagType, TextTag *> tagTemplates;

    vector<TextTag *> tags;

    /* PRIVATE FUNCTIONS ========================================================================================== */

    void initFonts(const string font_path);

    void initVariables();

    void initTagTemplates();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================== */

    TextTagSystem(const string font_path, VideoMode &vm);

    virtual ~TextTagSystem();

    /* FUNCTIONS =================================================================================================== */

    /**
     * @brief Iterates through all active tags and update them.
     * Deletes any expired tag.
     *
     * @return void
     */
    void update(const float &dt);

    /**
     * @brief Renders all active tags into a target.
     *
     * @return void
     */
    void render(RenderTarget &target);

    /**
     * @brief Creates a new tag into the system. The tag will be
     * shown and updated until it ends the lifetime.
     * @param type The tag type (TextTagType enum)
     * @param x The x position.
     * @param y The y position.
     * @param content The content of the tag.
     * @param prefix A prefix to the tag. Default none.
     * @param postfix a postfix to the tag. Default none.
     *
     * @return void.
     */
    template <typename T>
    void displayTag(const TextTagType type, const float x, const float y, const T content,
                    const string prefix = "", const string postfix = "")
    {
        stringstream ss;
        ss << prefix << content << postfix;

        tags.push_back(new TextTag(tagTemplates[type], x, y, ss.str()));
    }

    /**
     * @brief Creates a new tag into the system. The tag will be
     * shown and updated until it ends the lifetime.
     * @param type The tag type (TextTagType enum)
     * @param position A Vector2f of the position.
     * @param content The content of the tag.
     * @param prefix A prefix to the tag. Default none.
     * @param postfix a postfix to the tag. Default none.
     *
     * @return void.
     */
    template <typename T>
    void displayTag(const TextTagType type, const Vector2f &position, const T content,
                    const string prefix = "", const string postfix = "")
    {
        stringstream ss;
        ss << prefix << content << postfix;

        tags.push_back(new TextTag(tagTemplates[type], position.x, position.y, ss.str()));
    }

    /**
     * @brief Deletes a tag by its pointer.
     * @attention Deletes the data AND the pointer from the vector.
     * 
     * @return void
     */
    void deleteTag(TextTag *tag);

    /**
     * @brief Deletes a tag by its index.
     * @attention Deletes the data AND the pointer from the vector.
     *
     * @return void
     */
    void deleteTag(const size_t index);

    /* ACCESSORS =================================================================================================== */

    /* MODIFIERS =================================================================================================== */
};

#endif /* TEXTTAGSYSTEM_H_ */