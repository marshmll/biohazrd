#include "stdafx.h"
#include "SkillComponent.h"

void SkillComponent::check_skill_existence(const short unsigned skill)
{
    if (skill < 0 || skill >= this->skills.size())
        ErrorHandler::throwErr("SKILLCOMPONENT::CHECKSKILLEXISTENCE::ERR_SKILL_OUT_OF_RANGE\n");

    else if (this->skills.empty())
        ErrorHandler::throwErr("SKILLCOMPONENT::CHECKSKILLEXISTENCE::ERR_EMPTY_SKILL_VECTOR\n");
}

SkillComponent::SkillComponent()
{
    this->skills.push_back(Skill(HEALTH));
    this->skills.push_back(Skill(DAMAGE));
    this->skills.push_back(Skill(ACCURACY));
    this->skills.push_back(Skill(ENDURANCE));
}

SkillComponent::~SkillComponent()
{
}

/* FUNCTIONS */

void SkillComponent::gainExp(const short unsigned skill, const int exp_amount)
{
    this->check_skill_existence(skill);

    this->skills[skill].gainExp(exp_amount);
}

/* ACCESSORS */

const int SkillComponent::getSkillLevel(const short unsigned skill)
{
    this->check_skill_existence(skill);

    return this->skills[skill].getLevel();
}

const int SkillComponent::getSkillExp(const short unsigned skill)
{
    this->check_skill_existence(skill);

    return this->skills[skill].getExp();
}
