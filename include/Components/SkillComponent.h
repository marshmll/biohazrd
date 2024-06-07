#ifndef SKILLCOMPONENT_H_
#define SKILLCOMPONENT_H_

class SkillComponent
{
private:
    class Skill
    {
    private:
        /* VARIABLES */

        int level;
        int levelMax;

        int exp;
        int expBefore;
        int expNext;

    public:
        /* CONSTRUCTOR AND DESTRUCTOR */

        Skill()
        {
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

        inline const int &getLevel() { return this->level; }

        inline const int &getExp() { return this->exp; }

        inline const int &getExpNext() { return this->expNext; }

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

public:
    SkillComponent();
    virtual ~SkillComponent();
};

#endif /* SKILLCOMPONENT_H_ */