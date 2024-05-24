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

  AttributeComponent(unsigned level);
  virtual ~AttributeComponent();

  /* FUNCTIONS */

  void update();

  void updateStats(const bool reset);
  void updateLevel();

  void earnExp(const unsigned exp);

  void debugPrint();
};

#endif