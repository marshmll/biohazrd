#include "stdafx.h"
#include "SoundSystem.h"

SoundSystem::SoundSystem()
{
    buffers["TEST"].loadFromFile("Assets/Sounds/Music/Whispering Dreams.mp3");
}

SoundSystem::~SoundSystem()
{
}

const sf::SoundBuffer &SoundSystem::getSoundBuffer(const std::string key)
{
    return buffers.at(key);
}
