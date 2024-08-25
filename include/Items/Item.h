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

    std::string name;
    short unsigned value;
    ItemType type;

    sf::Texture &texture;
    sf::IntRect iconIntRect;

public:
    /* CONSTRUCTOR AND DESTRUCTOR =============================================================================== */

    Item(const std::string name, const unsigned short value,
         const ItemType type, sf::Texture &texture);

    virtual ~Item();

    /* FUNCTIONS ================================================================================================= */

    virtual Item *clone() = 0;

    /* ACCESSORS ================================================================================================= */

    virtual const std::string &getName() const;

    virtual const sf::Texture *getTexture() const;

    virtual sf::IntRect getIconIntRect() const;
};

#endif /* ITEM_H_ */