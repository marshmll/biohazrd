#ifndef ATTRIBUTECOMPONENT_H_
#define ATTRIBUTECOMPONENT_H_

class AttributeComponent
{
public:
    /* LEVELLING */

    int level;
    int exp;
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
     * @brief Updates the level while the exp is bigger than or
     * equal to the next exp.
     *
     * @return void
     */
    void updateLevel();

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