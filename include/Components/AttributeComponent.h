#ifndef ATTRIBUTECOMPONENT_H_
#define ATTRIBUTECOMPONENT_H_

#define RESET true

class AttributeComponent
{
private:
    const int calc_next_exp();

public:
    /* LEVELLING */

    int level;
    int exp;
    int expBefore;
    int expNext;
    int attributePoints;

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

    /**
     * @brief Creates an attribute component given a level.
     */
    AttributeComponent(const int level);

    /**
     * @brief Attribute component class destructor
     */
    virtual ~AttributeComponent();

    /* FUNCTIONS */

    /**
     * @brief Updates the attribute component
     * @note -> Updates the level.
     *
     * @return void
     */
    void update();

    /**
     * @brief Update the stats.
     *
     * @return void
     */
    void updateStats(const bool reset = false);

    /**
     * @brief Levels up and calculate the next exp value to level up
     * if exp is greater than the current next exp value.
     *
     * @return void
     */
    void levelUp();

    /**
     * @brief Levels down and recalculate the next exp value to level down
     * with the new level, if level is greater than zero.
     *
     * @return void
     */
    void levelDown();

    /* MODIFIERS */

    /**
     * @brief Increases hp by a given amount.
     * @note -> Limits hp to hpMax
     *
     * @return void
     */
    void earnHp(const int hpAmount);

    /**
     * @brief Decreases hp by a given amount.
     * @note -> Limits hp to 0
     *
     * @return void
     */
    void loseHp(const int hpAmount);

    /**
     * @brief Increases exp by a given amount.
     * @note -> Updates the level.
     *
     * @return void
     */
    void earnExp(const int expAmount);

    /**
     * @brief Decreases exp by a given amount.
     * @note -> Limits exp to 0
     *
     * @return void
     */
    void loseExp(const int expAmount);

    /**
     * @brief Print data for debuggin purposes.
     *
     * @return void
     */
};

#endif