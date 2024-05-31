#ifndef PLAYERGUI_H_
#define PLAYERGUI_H_

#include "Player.h"
#include "GUI.h"

class Player;
class GUI;

class PlayerGUI
{
private:
  /* VARIABLES */
  Player *player;

  sf::VideoMode &vm;

  sf::Font font;

  gui::ProgressBar *hpBar;
  gui::ProgressBar *expBar;

  gui::SolidBar *levelBar;

  /* INITIALIZERS */

  /**
   * @brief Initializes the font.
   *
   * @return void
   */
  void initFont();

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
   * @brief Initializes the exp bar.
   *
   * @return void
   */
  void initExpBar();

public:
  /* CONSTRUCTOR AND DESTRUCTOR */

  /**
   * @brief Creates a instance for the player GUI.
   */
  PlayerGUI(Player *player, sf::VideoMode &vm);

  /**
   * @brief Player GUI class destructor.
   */
  virtual ~PlayerGUI();

  /* FUNCTIONS */

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
};

#endif