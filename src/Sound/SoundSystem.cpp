#include "stdafx.h"
#include "SoundSystem.h"

SoundSystem::SoundSystem(const std::string file_path)
{
    parser.loadFromFile(file_path);
}

SoundSystem::~SoundSystem() {}

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
    try
    {
        if (!isPlaying(sound_key))
            globalSounds.at(sound_key).play();
    }
    catch (std::exception err)
    {
        std::cout << err.what() << "\n";
        ErrorHandler::printErr("SOUNDSYSTEM::PLAY::ERR_INVALID_SOUND_" + sound_key);
    }
}

void SoundSystem::stop(const std::string sound_key)
{
    try
    {
        if (isPlaying(sound_key))
            globalSounds.at(sound_key).stop();
    }
    catch (std::exception err)
    {
        std::cout << err.what() << "\n";
        ErrorHandler::printErr("SOUNDSYSTEM::STOP::ERR_INVALID_SOUND_" + sound_key);
    }
}

void SoundSystem::setLoop(const std::string sound_key, const bool loop)
{
    try
    {
        globalSounds.at(sound_key).setLoop(loop);
    }
    catch (std::exception err)
    {
        std::cout << err.what() << "\n";
        ErrorHandler::printErr("SOUNDSYSTEM::SETLOOP::ERR_INVALID_SOUND_" + sound_key);
    }
}

void SoundSystem::setVolume(const std::string sound_key, const float volume)
{
    try
    {
        globalSounds.at(sound_key).setVolume(volume);
    }
    catch (std::exception err)
    {
        std::cout << err.what() << "\n";
        ErrorHandler::printErr("SOUNDSYSTEM::SETVOLUME::ERR_INVALID_SOUND_" + sound_key);
    }
}

const bool SoundSystem::isPlaying(const std::string sound_key)
{
    try
    {
        return globalSounds.at(sound_key).getStatus() == sf::Sound::Playing;
    }
    catch (std::exception err)
    {
        std::cout << err.what() << "\n";
        ErrorHandler::printErr("SOUNDSYSTEM::ISPLAYING::ERR_INVALID_SOUND_" + sound_key);
    }

    return false;
}

const bool SoundSystem::getLoop(const std::string sound_key)
{
    try
    {
        return globalSounds.at(sound_key).getLoop();
    }
    catch (std::exception err)
    {
        std::cout << err.what() << "\n";
        ErrorHandler::printErr("SOUNDSYSTEM::GETLOOP::ERR_INVALID_SOUND_" + sound_key);
    }

    return false;
}

const sf::SoundBuffer &SoundSystem::getSoundBuffer(const std::string key)
{
    try
    {
        return buffers.at(key);
    }
    catch (std::exception err)
    {
        std::cout << err.what() << "\n";
        ErrorHandler::throwErr("SOUNDSYSTEM::GETSOUNDBUFFER::ERR_INVALID_SOUNDBUFFER_" + key);
    }

    return buffers.at(key); // Should never reach here
}