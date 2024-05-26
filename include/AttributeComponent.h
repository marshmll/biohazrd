#ifndef ATTRIBUTECOMPONENT_H_
#define ATTRIBUTECOMPONENT_H_

class AttributeComponent
{
public:
  /* LEVELLING */

  unsigned level;
  unsigned exp;
  unsigned expNext;
  unsigned attributePoints;

  /* ATTRIBUTES */

  int vitality;
  int strength;
  int dexterity;
  int agillity;
  int intelligence;

  /* STATS */

  int hp;
  int hpMax;

  int damageMin;
  int damageMax;

  int accuracy;
  int defense;

  int luck;

  /* CONSTRUCTOR AND DESTRUCTOR */

  /**
   * @brief Creates an attribute component given a level.
   */
  AttributeComponent(unsigned level);

  /**
   * @brief Attribute component class destructor
   */
  virtual ~AttributeComponent();

  /* FUNCTIONS */

  /**
   * @brief Updates the attribute component
   * @note -> Updates the level.
   *
   * @return void
   */
  void update();

  /**
   * @brief Update the stats.
   *
   * @return void
   */
  void updateStats(const bool reset = false);

  /**
   * @brief Updates the level while the exp is bigger than or
   * equal to the next exp.
   *
   * @return void
   */
  void updateLevel();

  void debugPrint();

  /* MODIFIERS */

  /**
   * @brief Increases hp by a given amount.
   * @note -> Limits hp to hpMax
   *
   * @return void
   */
  void earnHp(const unsigned hpAmount);

  /**
   * @brief Decreases hp by a given amount.
   * @note -> Limits hp to 0
   *
   * @return void
   */
  void loseHp(const unsigned hpAmount);

  /**
   * @brief Increases exp by a given amount.
   * @note -> Updates the level.
   *
   * @return void
   */
  void earnExp(const unsigned expAmount);

  /**
   * @brief Decreases exp by a given amount.
   * @note -> Limits exp to 0
   *
   * @return void
   */
  void loseExp(const unsigned expAmount);

  /**
   * @brief Print data for debuggin purposes.
   *
   * @return void
   */
};

#endif