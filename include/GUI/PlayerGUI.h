#ifndef PLAYERGUI_H_
#define PLAYERGUI_H_

#include "Player.h"
#include "GUI.h"
#include "PlayerTabMenu.h"

class PlayerGUI
{
private:
    /* VARIABLES ================================================================================================= */

    Player &player;

    sf::VideoMode &vm;

    sf::Font font;

    gui::ProgressBar *expBar;
    gui::SolidBar *levelBar;
    gui::ProgressBar *hpBar;
    gui::ProgressBar *cooldownBar;

    PlayerTabMenu *playerMenu;


    /* INITIALIZERS =============================================================================================== */

    /**
     * @brief Initializes the font.
     *
     * @return void
     */
    void initFont();

    /**
     * @brief Initializes the exp bar.
     *
     * @return void
     */
    void initExpBar();

    /**
     * @brief
     *
     * @return void
     */
    void initLevelBar();

    /**
     * @brief Initializes the hp bar.
     *
     * @return void
     */
    void initHpBar();

    /**
     * @brief Initializes the cooldown bar.
     *
     * @return void
     */
    void initCooldownBar();

    /**
     * @brief Initializes the player tab menu.
     *
     * @return void
     */

    void initPlayerMenu();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    /**
     * @brief Creates a instance for the player GUI.
     */
    PlayerGUI(Player &player, sf::VideoMode &vm);

    /**
     * @brief Player GUI class destructor.
     */
    virtual ~PlayerGUI();

    /* FUNCTIONS ================================================================================================== */

    /**
     * @brief Updates the Player's GUI
     *
     * @return void
     */
    void update(const float &dt);

    /**
     * @brief Updates the Player's GUI
     *
     * @return void
     */
    void render(sf::RenderTarget &target);

    /**
     * @brief Updates the player's level bar.
     *
     * @return void
     */
    void updateLevelBar();

    /**
     * @brief Updates the Player's Hp bar.
     *
     * @return void
     */
    void updateHpBar();

    /**
     * @brief Updates the Player's exp bar.
     *
     * @return void
     */
    void updateExpBar();

    void updateCooldownBar();

    void updatePlayerMenu(const float &dt);

    void renderLevelBar(sf::RenderTarget &target);

    void renderHpBar(sf::RenderTarget &target);

    void renderExpBar(sf::RenderTarget &target);

    void renderCooldownBar(sf::RenderTarget &target);

    void renderPlayerMenu(sf::RenderTarget &target);

    void toggleTab(TabType tab_type);

    /* ACCESSORS ================================================================================================= */

    const bool hasTabsOpen() const;
};

#endif /* PLAYERGUI_H_ */