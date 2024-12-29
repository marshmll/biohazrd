#include "stdafx.h"
#include "Video.h"

void Video::initFrames(std::string &path)
{
    videoImages = PNGArray::loadPngImagesFromBinary(path);

    for (int i = 0; i < videoImages.size(); i++)
    {
        videoFrames[i].loadFromImage(videoImages[i]);
        videoFrames[i].setSmooth(true);
    }

    frameCount = videoFrames.size();
}

void Video::initFrameBuffer()
{
    frameBuffer.setSize(sf::Vector2f(width, height));
    frameBuffer.setPosition(x, y);
    frameBuffer.setFillColor(sf::Color::White);
    frameBuffer.setTexture(&videoFrames.at(0));
}

void Video::initClock()
{
    videoClock.restart();
}

Video::Video(std::string path,
             const float x, const float y,
             const float width, const float height,
             const unsigned framerate)

    : x(x), y(y),
      width(width), height(height),
      framerate(framerate), frameCount(0),
      currentFrame(0),
      frametime((1.f / framerate) * 1000) // How many seconds between each frame
{
    initFrames(path);
    initFrameBuffer();
    initClock();
}

Video::~Video()
{
}

void Video::play()
{
    if (videoClock.getElapsedTime().asMilliseconds() >= frametime)
    {
        currentFrame++;

        if (currentFrame >= frameCount)
            currentFrame = 0;

        frameBuffer.setTexture(&videoFrames.at(currentFrame));
        videoClock.restart();
    }
}

void Video::render(sf::RenderTarget &target)
{
    target.draw(frameBuffer);
}

void Video::setPosition(const float &x, const float &y)
{
    frameBuffer.setPosition(x, y);
}

void Video::setSize(const float &width, const float &height)
{
    frameBuffer.setSize(sf::Vector2f(width, height));
}

void Video::setFramerate(const unsigned &framerate)
{
    this->framerate = framerate;
    frametime = (1.f / framerate) * 1000;
}
