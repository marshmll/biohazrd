#ifndef PLAYERGUI_H_
#define PLAYERGUI_H_

#include "Player.h"

class PlayerGUI
{
private:
  /* VARIABLES */
  Player *player;

  sf::Font font;

  sf::RectangleShape hpBarBg;
  sf::RectangleShape hpBarFill;

  /* INITIALIZERS */
  void initFont();
  void initHpBar();

public:
  /* CONSTRUCTOR AND DESTRUCTOR */

  /**
   * @brief Creates a instance for the player GUI.
   */
  PlayerGUI(Player *player);

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
   * @brief Updates the Player's Hp bar.
   *
   * @return void
   */
  void updateHpBar();

  /**
   * @brief Renders the Player's Hp bar.
   *
   * @return void
   */
  void renderHpBar(sf::RenderTarget &target);
};

#endif