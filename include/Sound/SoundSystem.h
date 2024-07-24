#ifndef SOUNDSYSTEM_H_
#define SOUNDSYSTEM_H_

#include "IniParser.h"

class SoundSystem
{
private:
    IniParser parser;

    std::map<std::string, sf::SoundBuffer> buffers;
    std::map<std::string, sf::Sound> globalSounds;

public:
    SoundSystem(const std::string file_path);

    virtual ~SoundSystem();

    const bool loadBuffers(const std::string file_section);

    void createGlobalSound(const std::string sound_key, const std::string sound_buffer_key,
                           const float volume, const bool loop);

    void play(const std::string sound_key);

    void stop(const std::string sound_key);

    void setLoop(const std::string sound_key, const bool loop);

    void setVolume(const std::string sound_key, const float volume);

    const bool isPlaying(const std::string sound_key);

    const bool getLoop(const std::string sound_key);

    const sf::SoundBuffer &getSoundBuffer(const std::string key);
};

#endif /* SOUNDSYSTEM_H_ */