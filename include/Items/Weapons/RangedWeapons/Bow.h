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

    void update(const sf::Vector2f &mouse_pos_view, const sf::Vector2f entity_size,
                const sf::Vector2f entity_center, std::string entity_direction);

    void render(sf::RenderTarget &target, sf::Shader *shader = nullptr);

    Bow *clone();
};

#endif // BOW_H_
