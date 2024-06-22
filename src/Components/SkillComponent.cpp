#include "stdafx.h"
#include "SkillComponent.h"

void SkillComponent::check_skill_existence(const short unsigned skill)
{
    if (skill < 0 || skill >= skills.size())
        ErrorHandler::throwErr("SKILLCOMPONENT::CHECKSKILLEXISTENCE::ERR_SKILL_OUT_OF_RANGE\n");

    else if (skills.empty())
        ErrorHandler::throwErr("SKILLCOMPONENT::CHECKSKILLEXISTENCE::ERR_EMPTY_SKILL_VECTOR\n");
}

SkillComponent::SkillComponent()
{
    skills.push_back(Skill(HEALTH));
    skills.push_back(Skill(DAMAGE));
    skills.push_back(Skill(ACCURACY));
    skills.push_back(Skill(ENDURANCE));
}

SkillComponent::~SkillComponent()
{
}

/* FUNCTIONS */

void SkillComponent::gainExp(const short unsigned skill, const int exp_amount)
{
    check_skill_existence(skill);

    skills[skill].gainExp(exp_amount);
}

/* ACCESSORS */

const int SkillComponent::getSkillLevel(const short unsigned skill)
{
    check_skill_existence(skill);

    return skills[skill].getLevel();
}

const int SkillComponent::getSkillExp(const short unsigned skill)
{
    check_skill_existence(skill);

    return skills[skill].getExp();
}
