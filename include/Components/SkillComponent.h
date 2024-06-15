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
    /* Private class for the skill component. Represents a generic skill */
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

        /**
         * @brief The Skill class constructor.
         * @param type The skill's type based on the SKILLS enum.
         */
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

        /**
         * @brief Returns the skills's type.
         *
         * @return const short unsigned.
         */
        inline const short unsigned &getType() const { return this->type; }

        /**
         * @brief Returns the skills's level.
         *
         * @return const int.
         */
        inline const int &getLevel() const { return this->level; }

        /**
         * @brief Returns the skills's exp.
         *
         * @return const int.
         */
        inline const int &getExp() const { return this->exp; }

        /**
         * @brief Returns the skills's exp next.
         *
         * @return const int.
         */
        inline const int &getExpNext() const { return this->expNext; }

        /* MODIFIERS */

        /**
         * @brief Sets the skills's level.
         *
         * @param level The level to be set.
         *
         * @return void
         */
        void setLevel(const int level) { this->level = level; }

        /**
         * @brief Sets the skills's level's maximum.
         *
         * @param level_max The level's maximum to be set.
         *
         * @return void
         */
        void setLevelMax(const int level_max) { this->levelMax = level_max; }

        /**
         * @brief Increases the skills's exp..
         *
         * @param exp_amount The amount of exp to increase.
         *
         * @return void
         */
        void gainExp(const int exp_amount)
        {
            this->exp += exp_amount;
            this->levelUp();
        }

        /**
         * @brief Decreases the skills's exp..
         *
         * @param exp_amount The amount of exp to decrease.
         *
         * @return void
         */
        void loseExp(const int exp_amount)
        {
            this->exp -= exp_amount;

            if (this->exp < 0)
                this->exp = 0;

            this->levelDown();
        }
    };

    std::vector<Skill> skills;

    /**
     * @brief Checks if a skill exists in SKILLS enum.
     *
     * @note -> Checks if the skills vector is not empty;
     * @note -> Checks if the skill is out of the vector bounds.
     * @note -> Throws and error in case one of the previous situations is true.
     *
     * @param skill The skill's index.
     *
     * @return void
     */
    void check_skill_existence(const short unsigned skill);

public:
    SkillComponent();

    virtual ~SkillComponent();

    /* FUNCTIONS */

    /**
     * @brief Increases the exp of a skill with the exp_amount argument.
     *
     * @param skill The skill index (based on the SKILLS enum)
     * @param exp_amount The amount to increase the exp.
     *
     * @return void
     */
    void gainExp(const short unsigned skill, const int exp_amount);

    /* ACCESSORS */

    /**
     * @brief Returns the skill's level.
     *
     * @param skill The skill index.
     *
     * @return const int
     */
    const int getSkillLevel(const short unsigned skill);

    /**
     * @brief Returns the skill's exp.
     *
     * @param skill The skill index.
     *
     * @return const int
     */
    const int getSkillExp(const short unsigned skill);
};

#endif /* SKILLCOMPONENT_H_ */