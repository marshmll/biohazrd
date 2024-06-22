#include "stdafx.h"
#include "PlayerGUI.h"

/* INITIALIZERS */

void PlayerGUI::initFont()
{
    if (!font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
        ErrorHandler::throwErr("PLAYERGUI::INITFONT::ERR::COULD_NOT_LOAD_FONT\n");
}

void PlayerGUI::initLevelBar()
{
    levelBar = new gui::SolidBar(
        gui::p2pX(vm, 1.5f), gui::p2pY(vm, 2.5f),
        gui::p2pX(vm, 2.3f), gui::p2pY(vm, 3.7f),
        sf::Color(20, 20, 250, 200), sf::Color::White,
        font, gui::calc_char_size(vm, 140));
}

void PlayerGUI::initHpBar()
{
    hpBar = new gui::ProgressBar(
        gui::p2pX(vm, 1.5f), gui::p2pY(vm, 7.5f),
        gui::p2pX(vm, 19.5f), gui::p2pY(vm, 3.7f),
        player->getAttributeComponent()->hp, player->getAttributeComponent()->hpMax,
        sf::Color(50, 50, 50, 200), sf::Color(250, 20, 20, 200),
        font, sf::Color::White, gui::calc_char_size(vm, 140));
}

void PlayerGUI::initExpBar()
{
    expBar = new gui::ProgressBar(
        gui::p2pX(vm, 1.5f), gui::p2pY(vm, 12.5f),
        gui::p2pX(vm, 15.6f), gui::p2pY(vm, 2.5f),
        player->getAttributeComponent()->exp, player->getAttributeComponent()->expNext,
        sf::Color(50, 50, 50, 200), sf::Color(20, 250, 20, 200),
        font, sf::Color::White, gui::calc_char_size(vm, 140));
}

/* CONSTRUCTOR AND DESTRUCTOR */

PlayerGUI::PlayerGUI(Player *player, sf::VideoMode &vm) : vm(vm)
{
    this->player = player;

    initFont();
    initLevelBar();
    initHpBar();
    initExpBar();
}

PlayerGUI::~PlayerGUI()
{
    delete levelBar;
    delete hpBar;
    delete expBar;
}

/* FUNCTIONS */

void PlayerGUI::update(const float &dt)
{
    updateLevelBar();
    updateHpBar();
    updateExpBar();
}

void PlayerGUI::render(sf::RenderTarget &target)
{
    levelBar->render(target);
    hpBar->render(target);
    expBar->render(target);
}

void PlayerGUI::updateLevelBar()
{
    levelBar->setString(std::to_string(player->getAttributeComponent()->level));
}

void PlayerGUI::updateHpBar()
{
    std::stringstream hpBarText;
    hpBarText << player->getAttributeComponent()->hp << " | " << player->getAttributeComponent()->hpMax;

    hpBar->setString(hpBarText.str());

    float percent = static_cast<float>(player->getAttributeComponent()->hp) /
                    static_cast<float>(player->getAttributeComponent()->hpMax);

    hpBar->setProgress(percent);
}

void PlayerGUI::updateExpBar()
{
    std::stringstream expBarText;
    expBarText << player->getAttributeComponent()->exp << " | " << player->getAttributeComponent()->expNext;

    expBar->setString(expBarText.str());
    expBar->setMaxValue(player->getAttributeComponent()->expNext);

    float percent = static_cast<float>(player->getAttributeComponent()->exp) /
                    static_cast<float>(player->getAttributeComponent()->expNext);

    expBar->setProgress(percent);
}
