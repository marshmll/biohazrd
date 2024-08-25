#ifndef PLAYER_H_
#define PLAYER_H_

#include "Entity.h"
#include "Items.h"
#include "Inventory.h"

class Player : public Entity
{
private:
    /* VARIABLES ================================================================================================== */

    Inventory *inventory;

    Sword sword;

    /* INITIALIZERS =============================================================================================== */

    /**
     * @brief Initializes player variables.
     *
     * @return void
     */
    void initVariables();

    /**
     * @brief Initializes player animations.
     *
     * @return void
     */
    void initAnimations();

    /**
     * @brief Initializes player inventory.
     *
     * @return void
     */
    void initInventory();

public:
    /* CONSTRUCTOR AND DESTRUCTOR ================================================================================ */

    /**
     * @brief Player entity class constructor.
     * @note -> Initializes variables
     * @note -> Sets the player position with x and y arguments.
     * @note -> Initializes components
     * @note -> Initializes animations
     */
    Player(const float x, const float y, std::map<std::string, sf::Texture> &textures);

    /**
     * @brief Player destructor
     */
    virtual ~Player();

    /* FUNCTIONS ================================================================================================= */

    /**
     * @brief Updates the player entity.
     * @note -> Updates the movement component.
     * @note -> Plays the respective animation.
     *
     * @return void
     */
    void update(const float &dt, const sf::Vector2f &mouse_pos_view);

    /**
     * @brief Renders the player into a target.
     *
     * @return void
     */
    void render(sf::RenderTarget &target, const bool show_hitbox = false,
                sf::Shader *shader = nullptr, sf::Vector2f light_pos = sf::Vector2f());

    /**
     * @brief Updates the player animations.
     *
     * @return void
     */
    void updateAnimation(const float &dt);

    /* ACCESSORS ================================================================================================ */

    /**
     * @brief Returns a pointer to the player's atribute component.
     *
     * @return AttributeComponent*
     */
    AttributeComponent *getAttributeComponent();

    Inventory *getInventory();

    Weapon *getWeapon();

    const std::string formatStringToCharTab();

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
};

#endif /* PLAYER_H_ */
