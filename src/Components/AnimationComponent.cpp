/*
 * AnimationComponent.cpp
 *
 *  Created on: 20 de abr. de 2024
 *      Author: Renan Andrade
 */

#include "stdafx.h"
#include "AnimationComponent.h"

/* CONSTRUCTOR AND DESTRUCTOR =================================================================================== */

AnimationComponent::AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet)
    : sprite(sprite), textureSheet(texture_sheet),
      previousAnimation(nullptr), priorityAnimation(nullptr)
{
}

AnimationComponent::~AnimationComponent()
{
    for (auto &[key, animation] : animations)
        delete animation;
}

/* FUNCTIONS ==================================================================================================== */

void AnimationComponent::addAnimation(
    const std::string key,
    const float animation_update_timer,
    const int start_frame_x_index, const int start_frame_y_index,
    const int end_frame_x_index, const int end_frame_y_index,
    const float width, const float height)
{
    animations[key] = new Animation(sprite, textureSheet,
                                    animation_update_timer,
                                    start_frame_x_index, start_frame_y_index,
                                    end_frame_x_index, end_frame_y_index,
                                    width, height);
}

const bool AnimationComponent::play(const std::string key, const float &dt, const bool priority)
{

    bool done = false;

    // If its a prioritary animation and there is no current prioritary anim.
    if (priority && priorityAnimation == nullptr)
        priorityAnimation = animations[key];

    if (priorityAnimation != nullptr)
    {
        // If the previous animation is not the prioritary animation
        // already, set it.
        if (previousAnimation != priorityAnimation)
            setNewPreviousAnimation(priorityAnimation);

        // If the animation is done
        if (priorityAnimation->play(dt))
        {
            // Reset the pointer and set done to true.
            priorityAnimation = nullptr;
            done = true;
        }
    }
    // If there is no prioritary animation
    else
    {
        // If the previous animation is not the animation to be
        // player already, set it.
        if (previousAnimation != animations[key])
            setNewPreviousAnimation(key);

        // Sets done equals to if the animation is done.
        done = animations[key]->play(dt);
    }

    return done;
}

const bool AnimationComponent::play(const std::string key, const float &dt,
                                    const float &modifier, const float &modifier_max,
                                    const bool priority)
{

    bool done = false;

    // If its a prioritary animation and there is no current prioritary anim.
    if (priority && priorityAnimation == nullptr)
        priorityAnimation = animations[key];

    // If there is a prioritary animation
    if (priorityAnimation != nullptr)
    {
        // If the previous animation is not the prioritary animation
        // already, set it.
        if (previousAnimation != priorityAnimation)
            setNewPreviousAnimation(priorityAnimation);

        // If the animation is done
        if (priorityAnimation->play(dt, std::abs(modifier / modifier_max)))
        {
            // Reset the pointer and set done to true.
            priorityAnimation = nullptr;
            done = true;
        }
    }
    // If there is no prioritary animation
    else
    {
        // If the previous animation is not the animation to be
        // player already, set it.
        if (previousAnimation != animations[key])
            setNewPreviousAnimation(key);

        // Sets done equals to if the animation is done.
        done = animations[key]->play(dt, std::abs(modifier / modifier_max));
    }

    return done;
}

void AnimationComponent::setNewPreviousAnimation(std::string key)
{
    // If there is no previous animation, set it to the refered animation.
    if (previousAnimation == nullptr)
        previousAnimation = animations[key];

    // If there is a previous animation, reset it and
    // set the pointer to the animation to be played.
    else
    {
        previousAnimation->reset();
        previousAnimation = animations[key];
    }
}

void AnimationComponent::setNewPreviousAnimation(Animation *animation)
{
    // If there is no previous animation, set it to the refered animation.
    if (previousAnimation == nullptr)
        previousAnimation = animation;

    // If there is a previous animation, reset it and
    // set the pointer to the animation to be played.
    else
    {
        previousAnimation->reset();
        previousAnimation = animation;
    }
}

/* ACCESSORS =================================================================================================== */

const bool &AnimationComponent::isAnimationDone(std::string key)
{
    return animations[key]->isDone();
}
