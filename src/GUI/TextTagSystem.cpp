#include "stdafx.h"
#include "TextTagSystem.h"

/* PRIVATE FUNCTIONS ============================================================================================ */

void TextTagSystem::initFonts(const std::string font_path)
{
    if (!font.loadFromFile(font_path))
        ErrorHandler::throwErr("TEXTTAGSYSTEM::TEXTTAGSYSTEM::ERR_LOADING_FONT: " + font_path);
}

void TextTagSystem::initVariables()
{
}

void TextTagSystem::initTagTemplates()
{
    tagTemplates[DEFAULT_TAG] = new TextTag(0.f, 0.f,
                                            1, -1,
                                            5.f, 50.f,
                                            300.f,
                                            sf::Color::White,
                                            gui::calc_char_size(vm, 140),
                                            "DEFAULT_TAG", font);

    tagTemplates[DAMAGE_TAG] = new TextTag(0.f, 0.f,
                                           1, -1,
                                           5.f, 50.f,
                                           300.f,
                                           sf::Color(255, 50, 50, 255),
                                           gui::calc_char_size(vm, 140),
                                           "DAMAGE_TAG", font);

    tagTemplates[EXPERIENCE_TAG] = new TextTag(0.f, 0.f,
                                               1, -1,
                                               5.f, 50.f,
                                               300.f,
                                               sf::Color(50, 255, 50, 255),
                                               gui::calc_char_size(vm, 140),
                                               "EXPERIENCE_TAG", font);
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

TextTagSystem::TextTagSystem(const std::string font_path, sf::VideoMode &vm)
    : vm(vm)
{
    initFonts(font_path);
    initVariables();
    initTagTemplates();
}

TextTagSystem::~TextTagSystem()
{
    for (auto tag : tags)
        delete tag;

    for (auto &it : tagTemplates)
        delete it.second;
}

/* FUNCTIONS ====================================================================================================== */

void TextTagSystem::update(const float &dt)
{
    for (size_t i = 0; i < tags.size(); ++i)
    {
        tags[i]->update(dt);

        if (tags[i]->hasExceededLifetime())
            removeTag(i);
    }
}

void TextTagSystem::render(sf::RenderTarget &target)
{
    for (auto tag : tags)
        tag->render(target);
}

void TextTagSystem::displayTag(const TextTagType type, const float x, const float y, const std::string string)
{
    tags.push_back(new TextTag(tagTemplates[type], x, y, string));
}

void TextTagSystem::displayTag(const TextTagType type, const sf::Vector2f &position, const std::string string)
{
    tags.push_back(new TextTag(tagTemplates[type], position.x, position.y, string));
}

void TextTagSystem::removeTag(TextTag *tag)
{
    auto tag_it = std::find(tags.begin(), tags.end(), tag);

    if (tag_it != tags.end())
    {
        delete tag;
        tags.erase(tag_it);
    }
    else
        ErrorHandler::throwErr("TEXTTAGSYSTEM::REMOVETAG::ERR_TAG_NOT_FOUND_IN_VECTOR");
}

void TextTagSystem::removeTag(const size_t index)
{
    if (index >= tags.size())
        ErrorHandler::throwErr("TEXTTAGSYSTEM::REMOVETAG::INDEX_OUT_OF_BOUNDS");

    delete tags[index];
    tags.erase(tags.begin() + index);
}