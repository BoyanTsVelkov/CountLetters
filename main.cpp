/**
*   The text is create in "http://randomtextgenerator.com"
*
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>
#include <chrono>

uint64_t countlettersInLine(const std::string line, const char searchedLetter)
{
    uint64_t lettersInLine = 0;

    const uint64_t lineSize = line.size();

    for(uint64_t i = 0; i < lineSize; ++i)
    {
        if(searchedLetter == line[i])
        {
            lettersInLine++;
        }
    }

    return lettersInLine;
}

int main()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::ifstream textFile;
    std::string line;
    const char searchedLetter = 'e';
    uint64_t countFoundLetters = 0;

    textFile.open("text");

    std::cout << textFile.is_open() << std::endl;

    if(textFile.is_open())
    {
        while(getline(textFile, line))
        {
            countFoundLetters += countlettersInLine(line, searchedLetter);
        }

        textFile.close();
    }

    std::cout << "Found all letter \"" << searchedLetter << "\" in file text "
                            "they number is " << countFoundLetters << std::endl;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " <<
    std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
                                                         << "[µs]" << std::endl;

    std::cout << "Time difference = " <<
    std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()
                                                         << "[ns]" << std::endl;

    return 0;
}



///-----------------------------------------------------------------------------

/*
#include <thread>
#include <vector>

#define THREAD_NUMBER 8

void countLettersInLine(const std::string line, const char searchedLetter,
                                                       uint64_t & countedLetters)
{
    uint64_t lettersInLine = 0;

    const uint64_t lineSize = line.size();

    for(uint64_t i = 0; i < lineSize; ++i)
    {
        if(searchedLetter == line[i])
        {
            lettersInLine++;
        }
    }

    countedLetters = lettersInLine;
}

int main()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::ifstream textFile;
    std::string line;
    const char searchedLetter = 'e';
    uint64_t countFoundLetters = 0;

    std::string fullText;

    std::vector <std::thread> threadPool;
    threadPool.resize(THREAD_NUMBER);

    std::vector<uint64_t> lettersPerLine(THREAD_NUMBER,0);

    textFile.open("text");

    ///std::cout << textFile.is_open() << std::endl;

    if(textFile.is_open())
    {
        while(getline(textFile, line))
        {
            fullText.append(line);
        }

        textFile.close();
    }

    const uint64_t textSize = fullText.size();

    std::cout << "textSize = " << textSize << std::endl;

    const uint64_t part = static_cast<uint64_t>(textSize / THREAD_NUMBER);

    std::cout << "part = " << part << std::endl;

    uint64_t beggining = 0;

    //while(beggining < textSize)
    for(uint16_t i = 0; i < THREAD_NUMBER; ++i)
    {
        threadPool[i] = (std::thread(countLettersInLine, fullText.substr(beggining, part),
                                    searchedLetter, std::ref(lettersPerLine[i])));

        beggining += part;
    }

    uint64_t lettersInLastPart = 0;

    if(beggining < textSize)
    {
        countLettersInLine(fullText.substr(beggining), searchedLetter,
                                                             lettersInLastPart);
    }

//    std::cout << "lettersPerLine.size() = " << lettersPerLine.size() << std::endl;

    for(std::thread & activeThreds: threadPool)
    {
        activeThreds.join();
    }

    for(const uint64_t & currentLineCounter: lettersPerLine)
    {
        countFoundLetters += currentLineCounter;
    }

    countFoundLetters += lettersInLastPart;

    std::cout << "Found all letter \"" << searchedLetter << "\" in file text "
                            "they number is " << countFoundLetters << std::endl;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " <<
    std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
                                                         << "[µs]" << std::endl;

    std::cout << "Time difference = " <<
    std::chrono::duration_cast<std::chrono::seconds> (end - begin).count()
                                                         << "[s]" << std::endl;


    return 0;
}

*/
