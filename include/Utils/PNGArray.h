#ifndef PNGARRAY_H_
#define PNGARRAY_H_

#include <regex>

const std::vector<uint8_t> PNG_SIGNATURE = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};

class PNGArray
{
private:
    static bool isPngSignature(const std::vector<uint8_t> &buffer, size_t pos);

    static int extractNumberFromFilename(const std::filesystem::path &filePath);

public:
    PNGArray();
    virtual ~PNGArray();

    static std::vector<sf::Image> loadPngImagesFromBinary(const std::string &binaryFilePath);

    static void packPngImages(const std::string &dirPath, const std::string &outputFileName);
};

#endif /* PNGARRAY_H_ */