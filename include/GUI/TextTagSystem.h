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

        sf::Text text;

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
                const sf::Color color,
                const unsigned char_size,
                const std::string string, sf::Font &font,
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

        TextTag(TextTag *tag, const float x, const float y, const std::string string)
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
            if (!hasExceededLifetime())
            {
                if (fadeFx)
                {
                    float opacity_percent = currentLifetime / initialLifetime;

                    sf::Uint8 alpha = static_cast<sf::Uint8>(255 * opacity_percent);

                    text.setFillColor(sf::Color(text.getFillColor().r,
                                                text.getFillColor().g,
                                                text.getFillColor().b,
                                                alpha));
                }

                text.move((speedX * dirX) * dt, (speedY * dirY) * dt);
            }

            updateLifetime(dt);
        }

        void render(sf::RenderTarget &target)
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

        inline const bool hasExceededLifetime() const { return currentLifetime <= 0.f; }

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

        void setString(const std::string string)
        {
            text.setString(string);
        }

        void setPosition(const float x, const float y)
        {
            text.setPosition(x, y);
        }
    };

    /* VARIABLES =================================================================================================== */

    sf::Font font;

    sf::VideoMode &vm;

    std::map<TextTagType, TextTag *> tagTemplates;

    std::vector<TextTag *> tags;

    /* PRIVATE FUNCTIONS ========================================================================================== */

    void initFonts(const std::string font_path);

    void initVariables();

    void initTagTemplates();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================== */

    TextTagSystem(const std::string font_path, sf::VideoMode &vm);

    virtual ~TextTagSystem();

    /* FUNCTIONS =================================================================================================== */

    void update(const float &dt);

    void render(sf::RenderTarget &target);

    void displayTag(const TextTagType type, const float x, const float y, const std::string string);

    void displayTag(const TextTagType type, const sf::Vector2f &position, const std::string string);

    void removeTag(TextTag *tag);

    void removeTag(const size_t index);

    /* ACCESSORS =================================================================================================== */

    /* MODIFIERS =================================================================================================== */
};

#endif /* TEXTTAGSYSTEM_H_ */
