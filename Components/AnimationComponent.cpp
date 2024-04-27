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
	/**
	 * @constructor
	 */

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
	 * @return bool
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

	if (this->priorityAnimation != nullptr)
	{
		if (this->previousAnimation != this->priorityAnimation)
		{
			this->setNewPreviousAnimation(this->priorityAnimation);
		}

		if (this->priorityAnimation->play(dt))
		{
			this->priorityAnimation = nullptr;
			done = true;
		}
	}

	else
	{
		if (this->previousAnimation != this->animations[key])
		{
			this->setNewPreviousAnimation(key);
		}

		this->animations[key]->play(dt);

		done = this->animations[key]->isDone();
	}

	return done;
}

const bool AnimationComponent::play(const std::string key, const float &dt, const float &modifier,
		const float &modifier_max,
		const bool priority)
{
	/**
	 * @return bool
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

	if (this->priorityAnimation != nullptr)
	{
		if (this->previousAnimation != this->priorityAnimation)
		{
			this->setNewPreviousAnimation(this->priorityAnimation);
		}

		if (this->priorityAnimation->play(dt, std::abs(modifier / modifier_max)))
		{
			this->priorityAnimation = nullptr;
			done = true;
		}
	}

	else
	{
		if (this->previousAnimation != this->animations[key])
		{
			this->setNewPreviousAnimation(key);
		}

		this->animations[key]->play(dt, std::abs(modifier / modifier_max));

		done = this->animations[key]->isDone();
	}

	return done;
}

void AnimationComponent::setNewPreviousAnimation(std::string key)
{
	// If there is no previous animation, set it to the animation to be played.
	if (this->previousAnimation == nullptr)
		this->previousAnimation = this->animations[key];

	// If there is a previous animation, reset the previous animation and
	// set it to the animation to be played.
	else
	{
		this->previousAnimation->reset();
		this->previousAnimation = this->animations[key];
	}
}

void AnimationComponent::setNewPreviousAnimation(Animation *animation)
{
	// If there is no previous animation, set it to the animation to be played.
	if (this->previousAnimation == nullptr)
		this->previousAnimation = animation;

	// If there is a previous animation, reset the previous animation and
	// set it to the animation to be played.
	else
	{
		this->previousAnimation->reset();
		this->previousAnimation = animation;
	}
}

const bool& AnimationComponent::isAnimationDone(std::string key)
{
	return this->animations[key]->isDone();
}
