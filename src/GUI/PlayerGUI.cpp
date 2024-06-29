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
        player.getAttributeComponent()->exp, player.getAttributeComponent()->expNext,
        Color(50, 50, 50, 200), Color(20, 230, 20, 200),
        font, Color::White, gui::calc_char_size(vm, 140));
}

void PlayerGUI::initLevelBar()
{
    levelBar = new gui::SolidBar(
        expBar->getPosition().x, expBar->getPosition().y - gui::p2pY(vm, 3.5f),
        gui::p2pX(vm, 2.3f), gui::p2pY(vm, 3.2f),
        Color(20, 20, 250, 200), Color::White,
        font, gui::calc_char_size(vm, 140));
}

void PlayerGUI::initHpBar()
{
    hpBar = new gui::ProgressBar(
        expBar->getPosition().x + gui::p2pX(vm, 2.6f), expBar->getPosition().y - gui::p2pY(vm, 3.5f),
        gui::p2pX(vm, 19.5f), gui::p2pY(vm, 3.2f),
        player.getAttributeComponent()->hp, player.getAttributeComponent()->hpMax,
        Color(50, 50, 50, 200), Color(230, 20, 20, 200),
        font, Color::White, gui::calc_char_size(vm, 140));
}

void PlayerGUI::initCooldownBar()
{
    cooldownBar = new gui::ProgressBar(
        vm.width - gui::p2pX(vm, 10.f), expBar->getPosition().y,
        gui::p2pX(vm, 6.5f), gui::p2pY(vm, 1.2f),
        player.getWeapon()->getCooldownTimerMax(), player.getWeapon()->getCooldownTimerMax(),
        Color(50, 50, 50, 200), Color(230, 230, 230, 200));
}

void PlayerGUI::initPlayerMenu()
{
    playerMenu = new PlayerTabMenu(vm, font, player);
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

PlayerGUI::PlayerGUI(Player &player, VideoMode &vm)
    : player(player), vm(vm)
{
    initFont();
    initExpBar();
    initLevelBar();
    initHpBar();
    initCooldownBar();
    initPlayerMenu();
}

PlayerGUI::~PlayerGUI()
{
    delete levelBar;
    delete hpBar;
    delete expBar;
    delete cooldownBar;
    delete playerMenu;
}

/* FUNCTIONS ===================================================================================================== */

void PlayerGUI::update(const float &dt)
{
    updateLevelBar();
    updateHpBar();
    updateExpBar();
    updateCooldownBar();
    updatePlayerMenu(dt);
}

void PlayerGUI::render(RenderTarget &target)
{
    renderLevelBar(target);
    renderHpBar(target);
    renderExpBar(target);
    renderCooldownBar(target);
    renderPlayerMenu(target);
}

void PlayerGUI::updateLevelBar()
{
    levelBar->setString(to_string(player.getAttributeComponent()->level));
}

void PlayerGUI::updateHpBar()
{
    stringstream hpBarText;
    hpBarText << player.getAttributeComponent()->hp << " | " << player.getAttributeComponent()->hpMax;

    hpBar->setString(hpBarText.str());

    float percent = static_cast<float>(player.getAttributeComponent()->hp) /
                    static_cast<float>(player.getAttributeComponent()->hpMax);

    hpBar->setProgress(percent);
}

void PlayerGUI::updateExpBar()
{
    stringstream expBarText;
    expBarText << player.getAttributeComponent()->exp << " | " << player.getAttributeComponent()->expNext;

    expBar->setString(expBarText.str());
    expBar->setMaxValue(player.getAttributeComponent()->expNext);

    float percent = static_cast<float>(player.getAttributeComponent()->exp) /
                    static_cast<float>(player.getAttributeComponent()->expNext);

    expBar->setProgress(percent);
}

void PlayerGUI::updateCooldownBar()
{
    if (!player.getWeapon()->didCooldown(false))
    {
        float percent = static_cast<float>(player.getWeapon()->getCurrentCooldownTimerValue()) /
                        static_cast<float>(player.getWeapon()->getCooldownTimerMax());

        cooldownBar->setProgress(percent);
    }
    else
    {
        cooldownBar->setProgress(0.f);
    }
}

void PlayerGUI::updatePlayerMenu(const float &dt)
{
    playerMenu->update(dt);
}

void PlayerGUI::renderLevelBar(RenderTarget &target)
{
    levelBar->render(target);
}

void PlayerGUI::renderHpBar(RenderTarget &target)
{
    hpBar->render(target);
}

void PlayerGUI::renderExpBar(RenderTarget &target)
{
    expBar->render(target);
}

void PlayerGUI::renderCooldownBar(RenderTarget &target)
{
    if (!player.getWeapon()->didCooldown(false))
        cooldownBar->render(target);
}

void PlayerGUI::renderPlayerMenu(RenderTarget &target)
{
    playerMenu->render(target);
}

void PlayerGUI::toggleTab(TabType tab_type)
{
    playerMenu->toggleTab(tab_type);
}

/* ACCESSORS ===================================================================================================== */

const bool PlayerGUI::hasTabsOpen() const
{
    return playerMenu->hasTabsOpen();
}
