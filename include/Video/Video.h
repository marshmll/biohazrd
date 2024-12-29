#ifndef VIDEO_H_
#define VIDEO_H_

#include "PNGArray.h"

class Video
{
private:
    float x;
    float y;
    float width;
    float height;

    unsigned framerate;
    unsigned frameCount;
    unsigned currentFrame;

    sf::Int32 frametime;

    std::vector<sf::Image> videoImages;
    std::map<const unsigned, sf::Texture> videoFrames;
    
    sf::RectangleShape frameBuffer;
    sf::Clock videoClock;

    void initFrames(std::string &path);
    void initFrameBuffer();
    void initClock();

public:
    Video(std::string path,
          const float x, const float y,
          const float width, const float height,
          const unsigned framerate);

    virtual ~Video();

    void play();

    void render(sf::RenderTarget &target);

    void setPosition(const float &x, const float &y);

    void setSize(const float &width, const float &height);

    void setFramerate(const unsigned &framerate);
};

#endif /* VIDEO_H_ */