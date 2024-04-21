#ifndef COMPONENTS_ANIMATIONCOMPONENT_H_
#define COMPONENTS_ANIMATIONCOMPONENT_H_

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

		float stdAnimationTimer;
		float timer;

		int width;
		int height;

		sf::IntRect startCropRect;
		sf::IntRect currentCropRect;
		sf::IntRect endCropRect;

		Animation(sf::Sprite &sprite, sf::Texture &texture_sheet,
				float std_animation_timer,
				int start_frame_x_index, int start_frame_y_index,
				int end_frame_x_index, int end_frame_y_index,
				int width, int height) :

				sprite(sprite), textureSheet(texture_sheet), stdAnimationTimer(std_animation_timer),
						width(width), height(height)
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

			this->timer = 0.f;

			this->startCropRect = sf::IntRect(start_frame_x_index * width, start_frame_y_index * height, width, height);
			this->currentCropRect = this->startCropRect;
			this->endCropRect = sf::IntRect(end_frame_x_index * width, end_frame_y_index * height, width, height);

			this->sprite.setTexture(this->textureSheet, true);

			this->sprite.setTextureRect(this->startCropRect);

			this->sprite.setScale(3.5f, 3.5f);
		}

		/* FUNCTIONS */
		void play(const float &dt)
		{
			/**
			 * @return void
			 *
			 * Plays the animation with the stardard animation timer.
			 */

			// Increase timer
			this->timer += 100.f * dt;

			// Set next animation frame
			this->sprite.setTextureRect(this->currentCropRect);

			// If timer hits the desired animation update timer
			if (this->timer >= this->stdAnimationTimer)
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

					// If the current row is past the final frame row
					if (this->currentCropRect.top > this->endCropRect.top)
					{
						// Move current frame row to start frame row and
						// restart animation
						this->currentCropRect.top = this->startCropRect.top;
					}
				}

			}
		}

		void reset()
		{
			/*
			 * @return void
			 *
			 * Resets animation to start.
			 */

			this->timer = 0.f;
			this->currentCropRect = this->startCropRect;
		}
	};

	/* VARIABLES */
	sf::Sprite &sprite;
	sf::Texture &textureSheet;
	std::map<std::string, Animation*> animations;

public:
	/* CONSTRUCTOR AND DESTRUCTOR */
	AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet);
	virtual ~AnimationComponent();

	/* FUNCTIONS */
	void play(const std::string key, const float &dt);
	void reset(const std::string key);

	void addAnimation(
			const std::string key,
			float animation_update_timer,
			int start_frame_x_index, int start_frame_y_index,
			int frames_x_amount, int frames_y_amount,
			int width, int height);
};

#endif /* COMPONENTS_ANIMATIONCOMPONENT_H_ */
