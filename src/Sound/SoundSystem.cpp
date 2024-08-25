#include "stdafx.h"
#include "SoundSystem.h"

SoundSystem::SoundSystem(const std::string file_path)
{
    parser.loadFromFile(file_path);
}

SoundSystem::~SoundSystem()
{
}

const bool SoundSystem::loadBuffers(const std::string file_section)
{
    int loaded_amount = 0;
    for (auto &[key, filename] : parser.getAllPropertiesFrom(file_section))
    {
        if (!buffers[key].loadFromFile(filename))
            ErrorHandler::throwErr("SOUNDSYSTEM::LOADBUFFERS::ERR_COULD_NOT_LOAD_BUFFER_" + filename);

        std::cout << "SoundSystem: Loaded " << filename << " sound file." << "\n";

        ++loaded_amount;
    }

    return loaded_amount > 0;
}

void SoundSystem::createGlobalSound(const std::string sound_key, const std::string sound_buffer_key,
                                    const float volume, const bool loop)
{
    globalSounds[sound_key] = sf::Sound(getSoundBuffer(sound_buffer_key));
    globalSounds[sound_key].setVolume(volume);
    globalSounds[sound_key].setLoop(loop);
}

void SoundSystem::play(const std::string sound_key)
{
    if (!isPlaying(sound_key))
        globalSounds.at(sound_key).play();
}

void SoundSystem::stop(const std::string sound_key)
{
    if (isPlaying(sound_key))
        globalSounds.at(sound_key).stop();
}

void SoundSystem::setLoop(const std::string sound_key, const bool loop)
{
    globalSounds.at(sound_key).setLoop(loop);
}

void SoundSystem::setVolume(const std::string sound_key, const float volume)
{
    globalSounds.at(sound_key).setVolume(volume);
}

const bool SoundSystem::isPlaying(const std::string sound_key)
{
    return globalSounds.at(sound_key).getStatus() == sf::Sound::Playing;
}

const bool SoundSystem::getLoop(const std::string sound_key)
{
    return globalSounds.at(sound_key).getLoop();
}

const sf::SoundBuffer &SoundSystem::getSoundBuffer(const std::string key)
{
    return buffers.at(key);
}