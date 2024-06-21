#ifndef RANGEDWEAPON_H_
#define RANGEDWEAPON_H_

#include "Item.h"

class Item;

class RangedWeapon : public Item
{
private:

public:
    RangedWeapon(const short unsigned value);

    virtual ~RangedWeapon();

    virtual RangedWeapon *clone() = 0;
};

#endif