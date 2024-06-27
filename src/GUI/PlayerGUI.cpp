#include "stdafx.h"
#include "PlayerGUI.h"

/* INITIALIZERS =================================================================================================== */

void PlayerGUI::initFont()
{
    if (!font.loadFromFile("Fonts/JetBrainsMono-Regular.ttf"))
        ErrorHandler::throwErr("PLAYERGUI::INITFONT::ERR::COULD_NOT_LOAD_FONT\n");
}

void PlayerGUI::initExpBar()
{
    expBar = new gui::ProgressBar(
        (vm.width / 2.f) - gui::p2pX(vm, 70.f) / 2.f, gui::p2pY(vm, 95.f),
        gui::p2pX(vm, 70.f), gui::p2pY(vm, 2.f),
        player->getAttributeComponent()->exp, player->getAttributeComponent()->expNext,
        sf::Color(50, 50, 50, 200), sf::Color(20, 230, 20, 200),
        font, sf::Color::White, gui::calc_char_size(vm, 140));
}

void PlayerGUI::initLevelBar()
{
    levelBar = new gui::SolidBar(
        expBar->getPosition().x, expBar->getPosition().y - gui::p2pY(vm, 3.5f),
        gui::p2pX(vm, 2.3f), gui::p2pY(vm, 3.2f),
        sf::Color(20, 20, 250, 200), sf::Color::White,
        font, gui::calc_char_size(vm, 140));
}

void PlayerGUI::initHpBar()
{
    hpBar = new gui::ProgressBar(
        expBar->getPosition().x + gui::p2pX(vm, 2.6f), expBar->getPosition().y - gui::p2pY(vm, 3.5f),
        gui::p2pX(vm, 19.5f), gui::p2pY(vm, 3.2f),
        player->getAttributeComponent()->hp, player->getAttributeComponent()->hpMax,
        sf::Color(50, 50, 50, 200), sf::Color(230, 20, 20, 200),
        font, sf::Color::White, gui::calc_char_size(vm, 140));
}

void PlayerGUI::initCooldownBar()
{
    cooldownBar = new gui::ProgressBar(
        vm.width - gui::p2pX(vm, 10.f), expBar->getPosition().y,
        gui::p2pX(vm, 6.5f), gui::p2pY(vm, 1.2f),
        player->getWeapon()->getCooldownTimerMax(), player->getWeapon()->getCooldownTimerMax(),
        sf::Color(50, 50, 50, 200), sf::Color(230, 230, 230, 200));
}

void PlayerGUI::initTabMenu()
{

}

void PlayerGUI::initCharacterTab()
{
    characterBg.setFillColor(sf::Color(50, 50, 50, 180));
    characterBg.setSize(sf::Vector2f(gui::p2pX(vm, 50.f), vm.height));

    characterInfoText.setFont(font);
    characterInfoText.setCharacterSize(gui::calc_char_size(vm, 120));
    characterInfoText.setFillColor(sf::Color::White);
    characterInfoText.setPosition(characterBg.getPosition().x + gui::p2pX(vm, 2.f),
                                  characterBg.getPosition().y + gui::p2pY(vm, 2.f));



}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

PlayerGUI::PlayerGUI(Player *player, sf::VideoMode &vm) : vm(vm)
{
    this->player = player;

    initFont();
    initExpBar();
    initLevelBar();
    initHpBar();
    initCooldownBar();

    initTabMenu();
    initCharacterTab();
}

PlayerGUI::~PlayerGUI()
{
    delete levelBar;
    delete hpBar;
    delete expBar;
    delete cooldownBar;
}

/* FUNCTIONS ===================================================================================================== */

void PlayerGUI::update(const float &dt)
{
    updateLevelBar();
    updateHpBar();
    updateExpBar();
    updateCooldownBar();

    updateCharacterTab();
}

void PlayerGUI::render(sf::RenderTarget &target)
{
    levelBar->render(target);
    hpBar->render(target);
    expBar->render(target);

    if (!player->getWeapon()->didCooldown(false))
        cooldownBar->render(target);

    // Character tab
    target.draw(characterBg);
    target.draw(characterInfoText);
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

void PlayerGUI::updateCooldownBar()
{
    if (!player->getWeapon()->didCooldown(false))
    {
        float percent = static_cast<float>(player->getWeapon()->getCurrentCooldownTimerValue()) /
                        static_cast<float>(player->getWeapon()->getCooldownTimerMax());

        cooldownBar->setProgress(percent);
    }
    else
    {
        cooldownBar->setProgress(0.f);
    }
}

void PlayerGUI::updateCharacterTab()
{
    characterInfoText.setString("TEST");
}