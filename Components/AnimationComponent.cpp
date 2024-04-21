/*
 * AnimationComponent.cpp
 *
 *  Created on: 20 de abr. de 2024
 *      Author: renan
 */

#include "AnimationComponent.h"

/* CONSTRUCTOR AND DESTRUCTOR */
AnimationComponent::AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet) :
		sprite(sprite), textureSheet(texture_sheet)
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
void AnimationComponent::play(const std::string key, const float &dt)
{
	/**
	 * @return void
	 *
	 * Plays an animation from the animations map.
	 * Plays the animation with the same key passed in.
	 */

	this->animations[key]->play(dt);
}

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
	 * an Animation class object.
	 */

	this->animations[key] = new Animation(
			this->sprite, this->textureSheet,
			animation_update_timer,
			start_frame_x_index, start_frame_y_index,
			end_frame_x_index, end_frame_y_index,
			width, height
			);
}
