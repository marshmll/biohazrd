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
  void updateStats(const bool reset);

  /**
   * @brief Updates the level while the exp is bigger than or
   * equal to the next exp.
   *
   * @return void
   */
  void updateLevel();

  /**
   * @brief Increases a the exp by a given amount.
   *
   * @return void
   */
  void earnExp(const unsigned exp);

  /**
   * @brief Print data for debuggin purposes.
   *
   * @return void
   */
  void debugPrint();
};

#endif