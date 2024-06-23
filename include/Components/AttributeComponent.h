#ifndef ATTRIBUTECOMPONENT_H_
#define ATTRIBUTECOMPONENT_H_

class AttributeComponent
{
private:
    /**
     * @brief Calculates the next exp level to level up.
     *
     * @return void
     */
    const int calc_next_exp();

public:
    /* LEVELING ================================================================================================= */

    short unsigned level;
    short unsigned exp;
    short unsigned expNext;
    short unsigned attributePoints;

    /* ATTRIBUTES ================================================================================================ */

    short unsigned vitality;
    short unsigned strength;
    short unsigned dexterity;
    short unsigned agillity;
    short unsigned intelligence;

    /* STATS ====================================================================================================== */

    short unsigned hp;
    short unsigned hpMax;

    short unsigned damageMin;
    short unsigned damageMax;

    short unsigned accuracy;
    short unsigned defense;

    short unsigned luck;

    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================= */

    /**
     * @brief Creates an attribute component given a level.
     */
    AttributeComponent(const short unsigned level);

    /**
     * @brief Attribute component class destructor
     */
    virtual ~AttributeComponent();

    /* FUNCTIONS ================================================================================================== */

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
     * @brief Updates the level based on the exp.
     *
     * @return void
     */
    void updateLevel();

    /* ACCESSORS ================================================================================================= */

    /**
     * @brief Returns if the hp is equal to 0.
     *
     * @return const bool
     */
    const bool isDead() const;

    /* MODIFIERS ================================================================================================= */

    /**
     * @brief Increases hp by a given amount.
     * @note -> Limits hp to hpMax
     *
     * @return void
     */
    void earnHp(const short unsigned hpAmount);

    /**
     * @brief Decreases hp by a given amount.
     * @note -> Limits hp to 0
     *
     * @return void
     */
    void loseHp(const short unsigned hpAmount);

    /**
     * @brief Increases exp by a given amount.
     * @note -> Updates the level.
     *
     * @return void
     */
    void earnExp(const short unsigned expAmount);

    /**
     * @brief Decreases exp by a given amount.
     * @note -> Limits exp to 0
     *
     * @return void
     */
    void loseExp(const short unsigned expAmount);

    /**
     * @brief Print data for debuggin purposes.
     *
     * @return void
     */
};

#endif
