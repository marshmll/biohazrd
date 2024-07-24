#ifndef SOUNDSYSTEM_H_
#define SOUNDSYSTEM_H_

class SoundSystem
{
private:
    std::map<std::string, sf::SoundBuffer> buffers;

public:
    SoundSystem();

    virtual ~SoundSystem();

    const sf::SoundBuffer &getSoundBuffer(const std::string key);
};

#endif /* SOUNDSYSTEM_H_ */