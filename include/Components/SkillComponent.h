#ifndef SKILLCOMPONENT_H_
#define SKILLCOMPONENT_H_

enum SKILLS
{
    HEALTH = 0,
    DAMAGE,
    ACCURACY,
    ENDURANCE,
};

class SkillComponent
{
private:
    class Skill
    {
    private:
        /* VARIABLES */

        short unsigned type;
        int level;
        int levelMax;

        int exp;
        int expBefore;
        int expNext;

    public:
        /* CONSTRUCTOR AND DESTRUCTOR */

        Skill(const short unsigned type)
        {
            this->type = type;
            this->level = 1;
            this->levelMax = 100;

            this->exp = 0;
            this->expBefore = 0;
            this->expNext = 0;
        }

        ~Skill() {}

        /* FUNCTIONS */

        void update()
        {
        }

        void levelUp()
        {
            if (this->exp > this->expNext && this->level < this->levelMax)
            {
                this->level++;
                this->expBefore = expNext;
                this->expNext = std::pow(this->level, 2) + this->level * 10 + this->level * 2 + this->level;
            }
        }

        void levelDown()
        {
            if (this->exp < this->expBefore && this->level > 0)
            {
                this->level--;
                this->expNext = expBefore;
                this->expBefore = std::pow(this->level, 2) + this->level * 10 + this->level * 2 + this->level;
            }
        }

        /* ACCESSORS */

        inline const short unsigned &getType() const { return this->type; }

        inline const int &getLevel() const { return this->level; }

        inline const int &getExp() const { return this->exp; }

        inline const int &getExpNext() const { return this->expNext; }

        /* MODIFIERS */

        void setLevel(const int level) { this->level = level; }

        void setLevelMax(const int level_max) { this->levelMax = level_max; }

        void gainExp(const int exp_amount)
        {
            this->exp += exp_amount;
            this->levelUp();
        }

        void loseExp(const int exp_amount)
        {
            this->exp -= exp_amount;

            if (this->exp < 0)
                this->exp = 0;

            this->levelDown();
        }
    };

    std::vector<Skill> skills;

    void check_skill_existence(const short unsigned skill);

public:
    SkillComponent();
    virtual ~SkillComponent();

    /* FUNCTIONS */

    void gainExp(const short unsigned skill, const int exp_amount);

    /* ACCESSORS */

    const int getSkillLevel(const short unsigned skill);

    const int getSkillExp(const short unsigned skill);
};

#endif /* SKILLCOMPONENT_H_ */