#ifndef VIDEO_H_
#define VIDEO_H_

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

    std::map<const unsigned, sf::Texture> videoFrames;
    sf::RectangleShape frameBuffer;
    sf::Clock videoClock;

    void initFrames(const std::string &path);
    void initFrameBuffer();
    void initClock();

public:
    Video(const std::string path,
          const float x, const float y,
          const float width, const float height,
          const unsigned framerate);

    virtual ~Video();

    void play();

    void render(sf::RenderTarget &target);
};

#endif /* VIDEO_H_ */