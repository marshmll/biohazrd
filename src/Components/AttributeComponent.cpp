#include "stdafx.h"
#include "AttributeComponent.h"

/* CONSTRUCTOR AND DESTRUCTOR */

const int AttributeComponent::calc_next_exp()
{
    return static_cast<int>(std::pow(this->level, 4) + std::pow(this->level + 6, 3));
}

AttributeComponent::AttributeComponent(const int level)
{
    this->level = level;
    this->exp = 0;
    this->expNext = this->calc_next_exp();
    this->attributePoints = 1;

    this->vitality = 1;
    this->strength = 1;
    this->dexterity = 1;
    this->agillity = 1;
    this->intelligence = 1;

    this->levelUp();
    this->levelDown();

    this->updateStats(RESET);
}

AttributeComponent::~AttributeComponent()
{
}

/* FUNCTIONS */

void AttributeComponent::update()
{
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

// TODO: fix bug
void AttributeComponent::levelUp()
{
    while (this->exp > this->expNext)
    {
        this->level++;
        this->attributePoints++;
        this->expBefore = this->expNext;
        this->expNext = this->calc_next_exp();

         std::cout << "Before: " << expBefore << " Next: " << expNext << "\n";
    }
}

void AttributeComponent::levelDown()
{
    while (this->exp < this->expBefore && this->level > 0)
    {
        this->level--;
        this->attributePoints--;
        this->expNext = this->expBefore + 10;
        this->expBefore = this->calc_next_exp();

        std::cout << "Before: " << expBefore << " Next: " << expNext << "\n";
    }
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

    this->levelUp();
}

void AttributeComponent::loseExp(const int expAmount)
{
    this->exp -= expAmount;

    if (this->exp <= 0)
        this->exp = 0;

    this->levelDown();
}