#ifndef ATTRIBUTECOMPONENT_H_
#define ATTRIBUTECOMPONENT_H_

class AttributeComponent
{
private:
    /* PRIVATE FUNCTIONS ======================================================================================= */

    /**
     * @brief Calculates the next exp level to level up.
     *
     * @return void
     */
    const int calcNextExp();

public:
    /* LEVELING ================================================================================================= */

    short level;
    short exp;
    short expNext;
    short attributePoints;

    /* ATTRIBUTES ================================================================================================ */

    short vitality;
    short strength;
    short dexterity;
    short agillity;
    short intelligence;

    /* STATS ====================================================================================================== */

    short hp;
    short hpMax;

    short damageMin;
    short damageMax;

    short accuracy;
    short defense;

    short luck;

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
    void earnHp(const short unsigned hp_amount);

    /**
     * @brief Decreases hp by a given amount.
     * @note -> Limits hp to 0
     *
     * @return void
     */
    void loseHp(const short unsigned hp_amount);

    /**
     * @brief Increases exp by a given amount.
     * @note -> Updates the level.
     *
     * @return void
     */
    void earnExp(const short unsigned exp_amount);

    /**
     * @brief Decreases exp by a given amount.
     * @note -> Limits exp to 0
     *
     * @return void
     */
    void loseExp(const short unsigned exp_amount);

    /**
     * @brief Print data for debuggin purposes.
     *
     * @return void
     */
};

#endif
