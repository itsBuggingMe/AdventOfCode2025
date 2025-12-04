#pragma once

#include "Day.cpp"

class Day1 : public Day
{
public:
    std::int32_t day_num() override
    {
        return 1;
    }

    std::string part1(std::istream& input) override
    {
        std::string currentLine;
        int32_t rotation = 50 + 100 * 10000000;
        int32_t zeroCount = 0;

        while (input.peek() != EOF)
        {
            input >> currentLine;

            int32_t offset = std::stoi(currentLine.substr(1));

            if (currentLine[0] == 'L')
                offset *= -1;

            rotation += offset;

            if ((rotation % 100) == 0)
                zeroCount++;
        }

        return std::to_string(zeroCount);
    }

    std::string part2(std::istream& input) override
    {
        std::string currentLine;
        int32_t rotation = 50 + 100 * 10000000;
        int32_t zeroCount = 0;

        while (input.peek() != EOF)
        {
            input >> currentLine;

            int32_t offset = std::stoi(currentLine.substr(1));


            int32_t base = rotation % 100;

            if (currentLine[0] == 'L')
            {
                base = (100 - base) % 100;
                offset = -offset;
            }


            int32_t crosses = (base + abs(offset)) / 100;

            rotation += offset;
            zeroCount += crosses;
        }

        return std::to_string(zeroCount);
    }
};