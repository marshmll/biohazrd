#ifndef ITEM_H_
#define ITEM_H_

enum ItemType
{
    DEFAULT_ITEM = 0,
    RANGED_WEAPON,
    MELEE_WEAPON
};

enum ItemRarity
{
    COMMON = 0,
    UNCOMMON,
    RARE,
    EPIC,
    LEGENDARY,
    MYTHIC
};

class Item
{
private:
    /* INITIALIZERS ============================================================================================= */

    void initVariables();

protected:
    /* PROTECTED VARIABLES =======================================================================================*/

    ItemType type;

    short unsigned value;

public:
    /* CONSTRUCTOR AND DESTRUCTOR =============================================================================== */

    Item(const short unsigned value = 0, const ItemType type = ItemType::DEFAULT_ITEM);

    virtual ~Item();

    /* FUNCTIONS ================================================================================================= */

    virtual Item *clone() = 0;
};

#endif /* ITEM_H_ */