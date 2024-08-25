#include "stdafx.h"
#include "PlayerGUI.h"

/* INITIALIZERS =================================================================================================== */

void PlayerGUI::initFont()
{
    if (!font.loadFromFile("Fonts/VCR_OSD_MONO_1.001.ttf"))
        ErrorHandler::throwErr("PLAYERGUI::INITFONT::ERR::COULD_NOT_LOAD_FONT\n");
}

void PlayerGUI::initInventoryGUI()
{
    inventory = new InventoryGUI(*player.getInventory(), vm);
}

void PlayerGUI::initExpBar()
{
    expBar = new gui::ProgressBar(
        (vm.width / 2.f) - gui::p2pY(vm, 8.f) * 9.f / 2.f, gui::p2pY(vm, 87.f),
        gui::p2pY(vm, 8.f) * 9.f, gui::p2pY(vm, 2.f),
        player.getAttributeComponent()->exp, player.getAttributeComponent()->expNext,
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
        player.getAttributeComponent()->hp, player.getAttributeComponent()->hpMax,
        sf::Color(50, 50, 50, 200), sf::Color(230, 20, 20, 200),
        font, sf::Color::White, gui::calc_char_size(vm, 140));
}

void PlayerGUI::initCooldownBar()
{
    cooldownBar = new gui::ProgressBar(
        vm.width - gui::p2pX(vm, 10.f), expBar->getPosition().y,
        gui::p2pX(vm, 6.5f), gui::p2pY(vm, 1.2f),
        player.getWeapon()->getCooldownTimerMax(), player.getWeapon()->getCooldownTimerMax(),
        sf::Color(50, 50, 50, 200), sf::Color(230, 230, 230, 200));
}

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

PlayerGUI::PlayerGUI(Player &player, sf::VideoMode &vm)
    : player(player), vm(vm)
{
    initFont();
    initInventoryGUI();
    initExpBar();
    initLevelBar();
    initHpBar();
    initCooldownBar();
}

PlayerGUI::~PlayerGUI()
{
    delete inventory;
    delete levelBar;
    delete hpBar;
    delete expBar;
    delete cooldownBar;
}

/* FUNCTIONS ===================================================================================================== */

void PlayerGUI::update(const float &dt, sf::Vector2f &mouse_pos)
{
    updateInventory(dt, mouse_pos);

    updateLevelBar();
    updateHpBar();
    updateExpBar();
    updateCooldownBar();
}

void PlayerGUI::render(sf::RenderTarget &target)
{
    renderInventory(target);

    renderLevelBar(target);
    renderHpBar(target);
    renderExpBar(target);
    renderCooldownBar(target);
}

void PlayerGUI::updateInventory(const float &dt, sf::Vector2f &mouse_pos)
{
    inventory->update(dt, mouse_pos);
}

void PlayerGUI::updateLevelBar()
{
    levelBar->setString(std::to_string(player.getAttributeComponent()->level));
}

void PlayerGUI::updateHpBar()
{
    std::stringstream hpBarText;
    hpBarText << player.getAttributeComponent()->hp << " | " << player.getAttributeComponent()->hpMax;

    hpBar->setString(hpBarText.str());

    float percent = static_cast<float>(player.getAttributeComponent()->hp) /
                    static_cast<float>(player.getAttributeComponent()->hpMax);

    hpBar->setProgress(percent);
}

void PlayerGUI::updateExpBar()
{
    std::stringstream expBarText;
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

void PlayerGUI::renderInventory(sf::RenderTarget &target)
{
    inventory->render(target);
}

void PlayerGUI::renderLevelBar(sf::RenderTarget &target)
{
    levelBar->render(target);
}

void PlayerGUI::renderHpBar(sf::RenderTarget &target)
{
    hpBar->render(target);
}

void PlayerGUI::renderExpBar(sf::RenderTarget &target)
{
    expBar->render(target);
}

void PlayerGUI::renderCooldownBar(sf::RenderTarget &target)
{
    if (!player.getWeapon()->didCooldown(false))
        cooldownBar->render(target);
}

/* ACCESSORS ===================================================================================================== */
