/**
*   The text is create in "http://randomtextgenerator.com"
*
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdint>
#include <chrono>
/*
uint64_t countLetersInLine(const std::string line, const char searchedLeter)
{
    uint64_t letersInLine = 0;

    const uint64_t lineSize = line.size();

    for(uint64_t i = 0; i < lineSize; ++i)
    {
        if(searchedLeter == line[i])
        {
            letersInLine++;
        }
    }

    return letersInLine;
}

int main()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::ifstream textFile;
    std::string line;
    const char searchedLeter = 'e';
    uint64_t countFoundLetters = 0;

    textFile.open("text");

    std::cout << textFile.is_open() << std::endl;

    if(textFile.is_open())
    {
        while(getline(textFile, line))
        {
            countFoundLetters += countLetersInLine(line, searchedLeter);
        }

        textFile.close();
    }

    std::cout << "Found all letter \"" << searchedLeter << "\" in file text "
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
*/
///-----------------------------------------------------------------------------

#include <thread>
#include <vector>

void countLetersInLine(const std::string line, const char searchedLeter,
                                                       uint64_t & countedLeters)
{
    uint64_t letersInLine = 0;

    const uint64_t lineSize = line.size();

    for(uint64_t i = 0; i < lineSize; ++i)
    {
        if(searchedLeter == line[i])
        {
            letersInLine++;
        }
    }

    countedLeters = letersInLine;
}

int main()
{
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::ifstream textFile;
    std::string line;
    const char searchedLeter = 'e';
    uint64_t countFoundLetters = 0;

    std::vector <std::thread> threadPool;
    threadPool.reserve(100);

    std::vector<uint64_t> letersPerLine;
    letersPerLine.reserve(100);


    textFile.open("text");

    ///std::cout << textFile.is_open() << std::endl;

    if(textFile.is_open())
    {
        while(getline(textFile, line))
        {
//            std::thread singleTh (countLetersInLine, line, searchedLeter);
            letersPerLine.emplace_back(0);
            const uint64_t lastElement = letersPerLine.size() - 1;

            threadPool.emplace_back(std::thread(countLetersInLine, line,
                                    searchedLeter, std::ref(letersPerLine[lastElement])));
        }

        textFile.close();
    }
    std::cout << "letersPerLine.size() = " << letersPerLine.size() << std::endl;
    for(std::thread & activeThreds: threadPool)
    {
        activeThreds.join();
    }

    for(const uint64_t & currentLineCounter: letersPerLine)
    {
        countFoundLetters += currentLineCounter;
    }

    std::cout << "Found all letter \"" << searchedLeter << "\" in file text "
                            "they number is " << countFoundLetters << std::endl;

    std::cout << "Found all letter \"" << searchedLeter << "\" in file text "
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

