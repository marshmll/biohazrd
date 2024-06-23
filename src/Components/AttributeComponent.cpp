#include "stdafx.h"
#include "AttributeComponent.h"

/* CONSTRUCTOR AND DESTRUCTOR ==================================================================================== */

const int AttributeComponent::calc_next_exp()
{
    return static_cast<int>(std::pow(level, 4) + std::pow(level + 6, 3));
}

AttributeComponent::AttributeComponent(const short unsigned level)
{
    this->level = level;
    exp = 0;
    expNext = calc_next_exp();
    attributePoints = 1;

    vitality = 1;
    strength = 1;
    dexterity = 1;
    agillity = 1;
    intelligence = 1;

    updateLevel();

    updateStats(RESET);
}

AttributeComponent::~AttributeComponent()
{
}

/* FUNCTIONS ==================================================================================================== */

void AttributeComponent::update()
{
}

void AttributeComponent::updateStats(const bool reset)
{
    hpMax = vitality * 5 + vitality + strength / 2 + intelligence / 5;
    damageMax = strength * 2 + strength / 2 + intelligence / 5;
    damageMin = strength * 2 + strength / 4 + intelligence / 5;
    accuracy = dexterity * 5 + dexterity / 3 + intelligence / 5;
    defense = agillity * 2 + agillity / 3 + intelligence / 5;
    luck = intelligence * 2 + intelligence / 5;

    if (reset)
    {
        hp = hpMax;
    }
}

void AttributeComponent::updateLevel()
{
    while (exp > expNext)
    {
        level++;
        attributePoints++;
        exp -= expNext;
        expNext = calc_next_exp();
    }
}

const bool AttributeComponent::isDead() const
{
    return hp == 0;
}

/* MODIFIERS ==================================================================================================== */

void AttributeComponent::earnHp(const short unsigned hpAmount)
{
    hp += hpAmount;

    if (hp >= hpMax)
        hp = hpMax;
}

void AttributeComponent::loseHp(const short unsigned hpAmount)
{
    hp -= hpAmount;

    if (hp <= 0)
        hp = 0;
}

void AttributeComponent::earnExp(const short unsigned expAmount)
{
    exp += expAmount;

    updateLevel();
}

void AttributeComponent::loseExp(const short unsigned expAmount)
{
    exp -= expAmount;

    if (exp <= 0)
        exp = 0;

    updateLevel();
}
