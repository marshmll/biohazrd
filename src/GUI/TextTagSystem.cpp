#include "stdafx.h"
#include "TextTagSystem.h"

/* PRIVATE FUNCTIONS ============================================================================================ */

void TextTagSystem::initFonts(const string font_path)
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
                                            Color::White,
                                            gui::calc_char_size(vm, 140),
                                            "DEFAULT_TAG", font);

    tagTemplates[NEGATIVE_TAG] = new TextTag(0.f, 0.f,
                                             0, -1,
                                             0.f, 70.f,
                                             300.f,
                                             Color::Red,
                                             gui::calc_char_size(vm, 135),
                                             "NEGATIVE_TAG", font, false);

    tagTemplates[POSITIVE_TAG] = new TextTag(0.f, 0.f,
                                             0, -1,
                                             0.f, 70.f,
                                             300.f,
                                             Color::Green,
                                             gui::calc_char_size(vm, 135),
                                             "POSITIVE_TAG", font, false);

    tagTemplates[DAMAGE_TAG] = new TextTag(0.f, 0.f,
                                           1, -1,
                                           5.f, 50.f,
                                           300.f,
                                           Color(255, 50, 50, 255),
                                           gui::calc_char_size(vm, 140),
                                           "DAMAGE_TAG", font);

    tagTemplates[EXPERIENCE_TAG] = new TextTag(0.f, 0.f,
                                               1, -1,
                                               5.f, 50.f,
                                               300.f,
                                               Color(50, 255, 50, 255),
                                               gui::calc_char_size(vm, 140),
                                               "EXPERIENCE_TAG", font);
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

TextTagSystem::TextTagSystem(const string font_path, VideoMode &vm)
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
    TextTag *tag;

    for (size_t i = 0; i < tags.size(); ++i)
    {
        tag = tags[i];

        tag->update(dt);

        if (tag->isExpired())
            deleteTag(i);
    }
}

void TextTagSystem::render(RenderTarget &target)
{
    for (auto tag : tags)
        tag->render(target);
}

void TextTagSystem::deleteTag(TextTag *tag)
{
    auto tag_it = find(tags.begin(), tags.end(), tag);

    if (tag_it == tags.end())
        ErrorHandler::throwErr("TEXTTAGSYSTEM::REMOVETAG::ERR_TAG_NOT_FOUND_IN_VECTOR");

    delete tag;
    tags.erase(tag_it);
}

void TextTagSystem::deleteTag(const size_t index)
{
    if (index >= tags.size())
        ErrorHandler::throwErr("TEXTTAGSYSTEM::REMOVETAG::INDEX_OUT_OF_BOUNDS");

    delete tags[index];
    tags.erase(tags.begin() + index);
}