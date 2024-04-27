#ifndef COMPONENTS_ANIMATIONCOMPONENT_H_
#define COMPONENTS_ANIMATIONCOMPONENT_H_

#include <iostream>
#include <string>
#include <map>

#include <SFML/Graphics.hpp>

class AnimationComponent
{
private:
	/* ANIMATION SUBCLASS */
	class Animation
	{
	public:
		/* VARIABLES */
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

		Animation(sf::Sprite &sprite, sf::Texture &texture_sheet,
				float animation_timer,
				int start_frame_x_index, int start_frame_y_index,
				int end_frame_x_index, int end_frame_y_index,
				int width, int height) :

				sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer),
						timer(0.f), width(width), height(height), done(false)
		{
			/**
			 * @constructor
			 *
			 * Constructs an animation class object.
			 * Parameters:
			 * -> A sprite reference
			 * -> A texture sheet reference
			 * -> An animation update timer
			 * -> The x-axis index of the texture sheet start frame.
			 * -> The y-axis index of the texture sheet start frame.
			 * -> The x-axis index of the texture sheet end frame.
			 * -> The y-axis index of the texture sheet end frame.
			 * -> Frame width
			 * -> Frame height
			 */

			this->startCropRect = sf::IntRect(start_frame_x_index * width, start_frame_y_index * height, width, height);
			this->currentCropRect = this->startCropRect;
			this->endCropRect = sf::IntRect(end_frame_x_index * width, end_frame_y_index * height, width, height);

			this->sprite.setTexture(this->textureSheet, true);

			this->sprite.setTextureRect(this->startCropRect);

			this->sprite.setScale(3.f, 3.f);
		}

		/* FUNCTIONS */
		const bool& play(const float &dt)
		{
			/**
			 * @return bool
			 * Overloaded Method WITHOUT modifier.
			 *
			 * Plays the animation with the stardard animation timer.
			 *
			 * Returns if the animaton is done.
			 */

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

		const bool& play(const float &dt, float mod_percent)
		{
			/**
			 * @return bool
			 * Overloaded Method WITH modifier.
			 *
			 * Plays the animation with the stardard animation timer.
			 *
			 * Returns if the animation is done.
			 */

			// If modifier percent is too small
			if (mod_percent < 0.7f)
			{
				// Assure its at least 50%
				mod_percent = 0.7f;
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

		void reset()
		{
			/*
			 * @return void
			 *
			 * Resets animation to initial state.
			 * -> Sets done to false
			 * -> Sets timer to the animation timer
			 * -> Sets current crop rect to the start crop rect.
			 */

			this->done = false;
			this->timer = this->animationTimer;
			this->currentCropRect = this->startCropRect;
		}

		/* ACCESSORS */
		const bool& isDone()
		{
			/**
			 * @return const bool&
			 *
			 * Returns if the animation is done.
			 */

			return this->done;
		}
	};

	/* VARIABLES */
	sf::Sprite &sprite;
	sf::Texture &textureSheet;
	std::map<std::string, Animation*> animations;

	Animation *previousAnimation;
	Animation *priorityAnimation;

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet);
	virtual ~AnimationComponent();

	/* FUNCTIONS */
	void addAnimation(
			const std::string key,
			float animation_update_timer,
			int start_frame_x_index, int start_frame_y_index,
			int frames_x_amount, int frames_y_amount,
			int width, int height);

	const bool play(const std::string key, const float &dt, const bool priority = false);

	const bool play(const std::string key, const float &dt, const float &modifier, const float &modifier_max,
			const bool priority = false);

	void setNewPreviousAnimation(std::string key);
	void setNewPreviousAnimation(Animation *animation);

	/* ACCESSORS */
	const bool& isAnimationDone(std::string key);

};

#endif /* COMPONENTS_ANIMATIONCOMPONENT_H_ */
