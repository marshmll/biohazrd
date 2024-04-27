/*
 * AnimationComponent.cpp
 *
 *  Created on: 20 de abr. de 2024
 *      Author: renan
 */

#include "AnimationComponent.h"

/* CONSTRUCTOR AND DESTRUCTOR */
AnimationComponent::AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet) :
		sprite(sprite), textureSheet(texture_sheet),
				previousAnimation(nullptr), priorityAnimation(nullptr)
{

}

AnimationComponent::~AnimationComponent()
{
	/**
	 * @destructor
	 *
	 * Delete all animations allocated memory
	 */

	for (auto &it : this->animations)
	{
		delete it.second;
	}
}

/* FUNCTIONS */
void AnimationComponent::addAnimation(
		const std::string key,
		float animation_update_timer,
		int start_frame_x_index, int start_frame_y_index,
		int end_frame_x_index, int end_frame_y_index,
		int width, int height
		)
{
	/**
	 * @return void
	 *
	 * Adds a new animation to the animations map.
	 * Sets a key for the animation and instantiates
	 * an Animation object for the animation.
	 *
	 * Parameters:
	 * -> A animation key
	 * -> An animation update timer
	 * -> The x-axis index of the texture sheet start frame.
	 * -> The y-axis index of the texture sheet start frame.
	 * -> The x-axis index of the texture sheet end frame.
	 * -> The y-axis index of the texture sheet end frame.
	 * -> Frame width
	 * -> Frame height
	 */

	this->animations[key] = new Animation(
			this->sprite, this->textureSheet,
			animation_update_timer,
			start_frame_x_index, start_frame_y_index,
			end_frame_x_index, end_frame_y_index,
			width, height
			);
}

const bool AnimationComponent::play(const std::string key, const float &dt, const bool priority)
{
	/**
	 * @return const bool&
	 *
	 * OVERLOADED METHOD
	 *
	 * Uses normal playing speed.
	 *
	 * Plays an animation from the animations map.
	 * Plays the animation with the same key passed in, OR
	 * Plays the priority animation until its done.
	 * -> If switched animations, reset previous animation and
	 * 	  update previous animation pointer.
	 */

	bool done = false;

	if (priority && this->priorityAnimation == nullptr)
		this->priorityAnimation = this->animations[key];

	// If there is a prioritary animation
	if (this->priorityAnimation != nullptr)
	{
		// If the previous animation is not the prioritary animation
		// already, set it.
		if (this->previousAnimation != this->priorityAnimation)
			this->setNewPreviousAnimation(this->priorityAnimation);

		// If the animation is done
		if (this->priorityAnimation->play(dt))
		{
			// Reset the pointer and set done to true.
			this->priorityAnimation = nullptr;
			done = true;
		}
	}
	// If there is no prioritary animation
	else
	{
		// If the previous animation is not the animation to be
		// player already, set it.
		if (this->previousAnimation != this->animations[key])
			this->setNewPreviousAnimation(key);

		// Sets done equals to if the animation is done.
		done = this->animations[key]->play(dt);
	}

	return done;
}

const bool AnimationComponent::play(const std::string key, const float &dt, const float &modifier,
		const float &modifier_max, const bool priority)
{
	/**
	 * @return const bool&
	 *
	 * OVERLOADED METHOD
	 *
	 * Uses a modifier and a modifier max for the playing speed.
	 *
	 * Plays an animation from the animations map.
	 * Plays the animation with the same key passed in, OR
	 * Plays the priority animation until its done.
	 * -> If switched animations, reset previous animation and
	 * 	  update previous animation pointer.
	 */

	bool done = false;

	if (priority && this->priorityAnimation == nullptr)
		this->priorityAnimation = this->animations[key];

	// If there is a prioritary animation
	if (this->priorityAnimation != nullptr)
	{
		// If the previous animation is not the prioritary animation
		// already, set it.
		if (this->previousAnimation != this->priorityAnimation)
			this->setNewPreviousAnimation(this->priorityAnimation);

		// If the animation is done
		if (this->priorityAnimation->play(dt, std::abs(modifier / modifier_max)))
		{
			// Reset the pointer and set done to true.
			this->priorityAnimation = nullptr;
			done = true;
		}
	}
	// If there is no prioritary animation
	else
	{
		// If the previous animation is not the animation to be
		// player already, set it.
		if (this->previousAnimation != this->animations[key])
			this->setNewPreviousAnimation(key);

		// Sets done equals to if the animation is done.
		done = this->animations[key]->play(dt, std::abs(modifier / modifier_max));
	}

	return done;
}

void AnimationComponent::setNewPreviousAnimation(std::string key)
{
	/**
	 * @return void
	 *
	 * OVERLOADED METHOD
	 *
	 * Uses a std::string as parameter.
	 *
	 * Sets previous animation pointer to be equal a
	 * refered animation.
	 */

	// If there is no previous animation, set it to the refered animation.
	if (this->previousAnimation == nullptr)
		this->previousAnimation = this->animations[key];

	// If there is a previous animation, reset it and
	// set the pointer to the animation to be played.
	else
	{
		this->previousAnimation->reset();
		this->previousAnimation = this->animations[key];
	}
}

void AnimationComponent::setNewPreviousAnimation(Animation *animation)
{
	/**
	 * @return void
	 *
	 * OVERLOADED METHOD
	 *
	 * Uses a Animation* as parameter.
	 *
	 * Sets previous animation pointer to be equal a
	 * refered animation.
	 */

	// If there is no previous animation, set it to the refered animation.
	if (this->previousAnimation == nullptr)
		this->previousAnimation = animation;

	// If there is a previous animation, reset it and
	// set the pointer to the animation to be played.
	else
	{
		this->previousAnimation->reset();
		this->previousAnimation = animation;
	}
}

const bool& AnimationComponent::isAnimationDone(std::string key)
{
	/**
	 * @return const bool&
	 *
	 * Returns is a animation is done playing.
	 */

	return this->animations[key]->isDone();
}
