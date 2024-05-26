#include "stdafx.h"
#include "AttributeComponent.h"

/* CONSTRUCTOR AND DESTRUCTOR */

AttributeComponent::AttributeComponent(const int level)
{
  this->level = level;
  this->exp = 0;
  this->expNext = static_cast<int>((50 / 14) * (std::pow(this->level, 2) / 6 * std::pow(this->level, 2) + (this->level * 17) - 12));
  this->attributePoints = 1;

  this->vitality = 1;
  this->strength = 1;
  this->dexterity = 1;
  this->agillity = 1;
  this->intelligence = 1;

  this->updateLevel();
  this->updateStats(true);
}

AttributeComponent::~AttributeComponent()
{
}

/* FUNCTIONS */

void AttributeComponent::update()
{
  this->updateLevel();
}

void AttributeComponent::updateStats(const bool reset)
{
  this->hpMax = this->vitality * 5 + this->vitality + this->strength / 2 + this->intelligence / 5;
  this->damageMax = this->strength * 2 + this->strength / 2 + this->intelligence / 5;
  this->damageMin = this->strength * 2 + this->strength / 4 + this->intelligence / 5;
  this->accuracy = this->dexterity * 5 + this->dexterity / 3 + this->intelligence / 5;
  this->defense = this->agillity * 2 + this->agillity / 3 + this->intelligence / 5;
  this->luck = this->intelligence * 2 + this->intelligence / 5;

  if (reset)
  {
    this->hp = this->hpMax;
  }
}

void AttributeComponent::updateLevel()
{
  while (this->exp >= this->expNext)
  {
    ++this->level;
    this->exp -= this->expNext;
    this->expNext = static_cast<int>((50 / 14) * (std::pow(this->level, 2) / 6 * std::pow(this->level, 2) + (this->level * 17) - 12));
    ++this->attributePoints;
  }
}

void AttributeComponent::debugPrint()
{
  system("clear");

  std::cout << "Level: " << this->level << "\n"
            << "Exp: " << this->exp << "\n"
            << "Exp next: " << this->expNext << "\n"
            << "Attribute points: " << this->attributePoints << "\n";
}

/* MODIFIERS */

void AttributeComponent::earnHp(const int hpAmount)
{
  this->hp += hpAmount;

  if (this->hp >= this->hpMax)
    this->hp = this->hpMax;
}

void AttributeComponent::loseHp(const int hpAmount)
{
  this->hp -= hpAmount;

  if (this->hp <= 0)
    this->hp = 0;
}

void AttributeComponent::earnExp(const int expAmount)
{
  this->exp += expAmount;

  this->updateLevel();
}

void AttributeComponent::loseExp(const int expAmount)
{
  this->exp -= expAmount;

  if (this->exp <= 0)
    this->exp = 0;
}