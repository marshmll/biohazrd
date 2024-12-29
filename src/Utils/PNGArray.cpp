#include "stdafx.h"
#include "PNGArray.h"

bool PNGArray::isPngSignature(const std::vector<uint8_t> &buffer, size_t pos)
{
    if (buffer.size() < pos + PNG_SIGNATURE.size())
        return false;
    return std::equal(PNG_SIGNATURE.begin(), PNG_SIGNATURE.end(), buffer.begin() + pos);
}

int PNGArray::extractNumberFromFilename(const std::filesystem::path &filePath)
{
    std::string filename = filePath.stem().string(); // Get filename without extension
    std::regex numberRegex(R"(\d+)");                // Regex to match numbers
    std::smatch match;

    if (std::regex_search(filename, match, numberRegex))
    {
        return std::stoi(match.str()); // Return the first matched number
    }
    return -1; // Return -1 if no number is found (error case)
}

PNGArray::PNGArray() {}

PNGArray::~PNGArray() {}

// Main function to read PNG images from a directory and write them to a binary file
void PNGArray::packPngImages(const std::string &dirPath, const std::string &outputFileName)
{
    std::filesystem::path dir(dirPath);
    if (!std::filesystem::exists(dir) || !std::filesystem::is_directory(dir))
    {
        throw std::runtime_error("Error: Invalid directory path: " + dirPath);
    }

    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!outputFile)
    {
        throw std::runtime_error("Error: Unable to open output file: " + outputFileName);
    }

    // Collect file paths
    std::vector<std::filesystem::path> pngFiles;
    for (const auto &entry : std::filesystem::directory_iterator(dir))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".png")
        {
            pngFiles.push_back(entry.path());
        }
    }

    // Sort files by the numeric value in the filenames
    std::sort(pngFiles.begin(), pngFiles.end(), [](const std::filesystem::path &a, const std::filesystem::path &b)
              { return extractNumberFromFilename(a) < extractNumberFromFilename(b); });

    // Write PNG files to the output binary file
    for (const auto &filePath : pngFiles)
    {
        std::ifstream inputFile(filePath, std::ios::binary);
        if (!inputFile)
        {
            throw std::runtime_error("Error: Unable to open input file: " + filePath.string());
        }

        outputFile << inputFile.rdbuf(); // Append PNG content to the output file
        std::cout << "Packed: " << filePath.filename() << std::endl;
    }

    std::cout << "All PNG images packed into " << outputFileName << std::endl;
}

std::vector<sf::Image> PNGArray::loadPngImagesFromBinary(const std::string &binaryFilePath)
{
    // Open the binary file
    std::ifstream inputFile(binaryFilePath, std::ios::binary);
    if (!inputFile)
    {
        throw std::runtime_error("Error: Unable to open binary file: " + binaryFilePath);
    }

    // Read the entire file into memory
    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();

    std::vector<sf::Image> images;
    size_t pos = 0;

    while (pos < buffer.size())
    {
        if (isPngSignature(buffer, pos))
        {
            size_t start = pos;

            // Find the end of the PNG file
            bool foundEnd = false;
            for (size_t i = start + PNG_SIGNATURE.size(); i + 8 <= buffer.size(); ++i)
            {
                if (buffer[i] == 'I' && buffer[i + 1] == 'E' && buffer[i + 2] == 'N' && buffer[i + 3] == 'D')
                {
                    size_t length = (buffer[i - 4] << 24) | (buffer[i - 3] << 16) | (buffer[i - 2] << 8) | buffer[i - 1];
                    size_t end = i + 8; // After "IEND" + CRC

                    if (end <= buffer.size())
                    {
                        sf::Image image;
                        if (image.loadFromMemory(buffer.data() + start, end - start))
                        {
                            images.push_back(std::move(image));
                            // std::cout << "Loaded image " << images.size() << " from binary.\n";
                        }
                        else
                        {
                            std::cerr << "Failed to load image at position " << start << "\n";
                        }

                        pos = end;
                        foundEnd = true;
                        break;
                    }
                }
            }

            if (!foundEnd)
            {
                throw std::runtime_error("Error: Could not find end of PNG starting at position " + std::to_string(start));
            }
        }
        else
        {
            ++pos;
        }
    }

    std::cout << "Loaded " << images.size() << " PNG images from binary file: " << binaryFilePath << "\n";
    return images;
}