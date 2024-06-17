#ifndef ANIMATIONCOMPONENT_H_
#define ANIMATIONCOMPONENT_H_

/* This class is responsible for managing animation functionalities. */
class AnimationComponent
{
private:
    /* This class is an abstraction of a animation. */
    class Animation
    {
    public:
        /* VARIABLES ======================================================= */

        sf::Sprite &sprite;
        sf::Texture &textureSheet;

        float animationTimer;
        float timer;

        int width;
        int height;
        bool done;

        sf::IntRect startCropRect;
        sf::IntRect currentCropRect;
        sf::IntRect endCropRect;

        /* CONSTRUCTOR AND DESTRUCTOR ========================================= */

        /**
         * @brief Constructs an animation class object.
         * @note Parameters:
         * @note -> A sprite reference
         * @note -> A texture sheet reference
         * @note -> An animation update timer
         * @note -> The x-axis index of the texture sheet start frame.
         * @note -> The y-axis index of the texture sheet start frame.
         * @note -> The x-axis index of the texture sheet end frame.
         * @note -> The y-axis index of the texture sheet end frame.
         * @note -> Frame width
         * @note -> Frame height
         */
        Animation(sf::Sprite &sprite, sf::Texture &texture_sheet,
                  float animation_timer,
                  int start_frame_x_index, int start_frame_y_index,
                  int end_frame_x_index, int end_frame_y_index,
                  int width, int height) : sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer),
                                           timer(0.f), width(width), height(height), done(false)
        {
            this->startCropRect = sf::IntRect(start_frame_x_index * width, start_frame_y_index * height, width, height);
            this->currentCropRect = this->startCropRect;
            this->endCropRect = sf::IntRect(end_frame_x_index * width, end_frame_y_index * height, width, height);

            this->sprite.setTexture(this->textureSheet, true);

            this->sprite.setTextureRect(this->startCropRect);

            this->sprite.setScale(3.f, 3.f);
        }

        virtual ~Animation() {}

        /* FUNCTIONS ======================================================= */

        /**
         * @brief Plays the animation with the stardard animation timer.
         *
         * @note Overloaded Method WITHOUT modifier.
         * @note Returns if the animaton is done.
         *
         * @return bool&
         */
        const bool &play(const float &dt)
        {
            this->done = false;

            // Increase timer
            this->timer += 100.f * dt;

            // Set next animation frame
            this->sprite.setTextureRect(this->currentCropRect);

            // If timer hits the desired animation update timer
            if (this->timer >= this->animationTimer)
            {
                // Reset the timer
                this->timer = 0.f;

                // If the current frame row is less than or equal to final
                // frame row
                if (this->currentCropRect.top <= this->endCropRect.top)
                {
                    // If current frame column is less than final frame column
                    if (this->currentCropRect.left < this->endCropRect.left)
                    {
                        // Move to the next frame in the right
                        this->currentCropRect.left += this->width;
                    }
                    // Else if current frame column is past the final frame column
                    else
                    {
                        // Move current frame to the start frame column
                        this->currentCropRect.left = this->startCropRect.left;

                        // Move current frame to the next row
                        this->currentCropRect.top += this->height;
                    }

                    // If the current frame has reached the end
                    if (this->currentCropRect.top > this->endCropRect.top)
                    {
                        // Move current frame row to start frame row and
                        // restart animation
                        this->currentCropRect.top = this->startCropRect.top;
                        this->done = true;
                    }
                }
            }

            return this->done;
        }

        /**
         * @brief Plays the animation with the stardard animation timer.
         *
         * @note Overloaded Method WITH modifier.
         * @note Returns if the animation is done.
         *
         * @return bool&
         */
        const bool &play(const float &dt, float mod_percent)
        {
            // If modifier percent is too small
            if (mod_percent < 0.5f)
            {
                // Assure its at least 50%
                mod_percent = 0.5f;
            }

            this->done = false;

            // Increase timer with modifier percent
            this->timer += mod_percent * 100.f * dt;

            // Set next animation frame
            this->sprite.setTextureRect(this->currentCropRect);

            // If timer hits the desired animation update timer
            if (this->timer >= this->animationTimer)
            {
                // Reset the timer
                this->timer = 0.f;

                // If the current frame row is less than or equal to final
                // frame row
                if (this->currentCropRect.top <= this->endCropRect.top)
                {
                    // If current frame column is less than final frame column
                    if (this->currentCropRect.left < this->endCropRect.left)
                    {
                        // Move to the next frame in the right
                        this->currentCropRect.left += this->width;
                    }
                    // If current frame column is past the final frame column
                    else
                    {
                        // Move current frame to the start frame column
                        this->currentCropRect.left = this->startCropRect.left;

                        // Move current frame to the next row
                        this->currentCropRect.top += this->height;
                    }

                    // If the current frame has reached the end
                    if (this->currentCropRect.top > this->endCropRect.top)
                    {
                        // Move current frame row to start frame row and
                        // restart animation
                        this->currentCropRect.top = this->startCropRect.top;
                        this->done = true;
                    }
                }
            }

            return this->done;
        }

        /**
         * @brief Resets animation to initial state.
         * @note -> Sets done to false
         * @note -> Sets timer to the animation timer
         * @note -> Sets current crop rect to the start crop rect.
         *
         * @return void
         */
        void reset()
        {
            this->done = false;
            this->timer = this->animationTimer;
            this->currentCropRect = this->startCropRect;
        }

        /* ACCESSORS ======================================================= */

        /**
         * @brief Returns if the animation is done.
         *
         * @return const bool&
         */
        const bool &isDone()
        {
            return this->done;
        }
    };

    /* VARIABLES ============================================================================== */

    sf::Sprite &sprite;
    sf::Texture &textureSheet;
    std::map<std::string, Animation *> animations;

    Animation *previousAnimation;
    Animation *priorityAnimation;

public:
    /* CONSTRUCTOR AND DESTRUCTOR ============================================================ */

    AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet);

    /**
     * @brief Delete all animations allocated memory
     */
    virtual ~AnimationComponent();

    /* FUNCTIONS ============================================================================ */

    /**
     * @brief Adds a new animation to the animations map.
     * Sets a key for the animation and instantiates
     * an Animation object for the animation.
     *
     * @param key A animation key
     * @param animation_update_timer An animation update timer
     * @param start_frame_x_index The x-axis index of the texture sheet start frame
     * @param start_frame_y_index The y-axis index of the texture sheet start frame
     * @param end_frame_x_index The x-axis index of the texture sheet end frame
     * @param end_frame_y_index The y-axis index of the texture sheet end frame
     * @param width Frame width
     * @param height Frame height
     *
     * @return void
     */
    void addAnimation(
        const std::string key,
        const float animation_update_timer,
        const int start_frame_x_index, const int start_frame_y_index,
        const int end_frame_x_index, const int end_frame_y_index,
        const float width, const float height);

    /**
     * @brief Plays an animation from the animations map.
     * Plays the animation with the same key passed in, OR
     * Plays the priority animation until its done.
     * @note -> If switched animations, reset previous animation and
     * 	  update previous animation pointer.
     *
     *
     * @note Uses normal playing speed.
     * @note OVERLOADED METHOD
     *
     * @return const bool&
     */
    const bool play(const std::string key, const float &dt, const bool priority = false);

    /**
     * @brief Plays an animation from the animations map.
     * Plays the animation with the same key passed in, OR
     * Plays the priority animation until its done.
     *
     * @note Uses a modifier and a modifier max for the playing speed.
     * @note OVERLOADED METHOD
     * @note -> If switched animations, reset previous animation and
     * 					update previous animation pointer.
     *
     * @return const bool&
     */
    const bool play(const std::string key, const float &dt,
                    const float &modifier, const float &modifier_max,
                    const bool priority = false);

    /**
     * @brief Sets previous animation pointer to be equal a
     * refered animation.
     *
     * @note OVERLOADED METHOD
     * @note Uses a std::string as parameter.
     *
     * @return void
     */
    void setNewPreviousAnimation(std::string key);

    /**
     * @brief Sets previous animation pointer to be equal a refered animation.
     *
     * @note OVERLOADED METHOD
     *
     * @note Uses a Animation* as parameter.
     *
     * @return void
     */
    void setNewPreviousAnimation(Animation *animation);

    /* ACCESSORS ================================================================================= */

    /**
     * @brief Returns is a animation is done playing.
     *
     * @return const bool&
     */
    const bool &isAnimationDone(std::string key);
};

#endif /* ANIMATIONCOMPONENT_H_ */
