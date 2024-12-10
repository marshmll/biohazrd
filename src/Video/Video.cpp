#include "stdafx.h"
#include "Video.h"

void Video::initFrames(const std::string &path)
{
    auto dir_iter = std::filesystem::directory_iterator(path);
    int file_count = std::count_if(
        begin(dir_iter),
        end(dir_iter),
        [](auto &entry)
        { return entry.is_regular_file(); });

    for (int i = 0; i < file_count; ++i)
    {
        videoFrames[i].loadFromFile(path + std::to_string(i + 1) + ".png");
        frameCount++;
    }

    if (frameCount == 0)
    {
        ErrorHandler::throwErr("VIDEO::INITFRAMES::ERR_ZERO_FRAMES_LOADED");
    }
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

Video::Video(const std::string path,
             const float x, const float y,
             const float width, const float height,
             const unsigned framerate)

    : x(x), y(y),
      width(width), height(height),
      framerate(framerate), frameCount(0),
      currentFrame(0),
      frametime(static_cast<unsigned>((60 / framerate) * 10 * 2))
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
