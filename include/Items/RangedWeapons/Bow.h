#ifndef BOW_H_
#define BOW_H_

#include "RangedWeapon.h"

class RangedWeapon;

class Bow : public RangedWeapon
{
private:
public:
    Bow();
    virtual ~Bow();

    virtual void update();

    virtual void render();

    virtual Bow *clone();
};

#endif // BOW_H_
