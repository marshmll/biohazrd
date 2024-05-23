#ifndef ATTRIBUTECOMPONENT_H_
#define ATTRIBUTECOMPONENT_H_

class AttributeComponent
{
public:
  /* LEVELLING */

  unsigned level;
  unsigned exp;
  unsigned attributePoints;

  /* ATTRIBUTES */

  unsigned strength;
  unsigned vitality;
  unsigned dexterity;
  unsigned agillity;
  unsigned intelligence;

  /* STATS */

  /* CONSTRUCTOR AND DESTRUCTOR */

  AttributeComponent();
  virtual ~AttributeComponent();

  /* FUNCTIONS */
};

#endif