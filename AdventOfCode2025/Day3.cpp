#pragma once

#include "Day.cpp"

class Day3 : public Day
{
public:
    std::int32_t day_num() override
    {
        return 3;
    }

    std::string part1(std::istream& input) override
    {
        std::string bank;
        int64_t sum = 0;
        while (std::getline(input, bank))
        {
            int32_t indexOfLargest = std::distance(bank.begin(), std::max_element(bank.begin(), bank.end()));

            int32_t tensIndex;
            int32_t onesIndex;

            if (indexOfLargest == bank.length() - 1)
            {// edge case
                std::string startSeg = bank.substr(0, indexOfLargest);
                int32_t indexOfLargestBefore =
                    std::distance(startSeg.begin(), std::max_element(startSeg.begin(), startSeg.end()));

                tensIndex = indexOfLargestBefore;
                onesIndex = indexOfLargest;
            }
            else
            {
                std::string endSeg = bank.substr(indexOfLargest + 1);
                int32_t indexOfLargestAfter =
                    std::distance(endSeg.begin(), std::max_element(endSeg.begin(), endSeg.end()))
                    + indexOfLargest + 1;

                tensIndex = indexOfLargest;
                onesIndex = indexOfLargestAfter;
            }

            int32_t joltage =
                (bank[tensIndex] - '0') * 10 +
                (bank[onesIndex] - '0');

            sum += joltage;
        }

        return std::to_string(sum);
    }

    std::string part2(std::istream& input) override
    {
        std::string bank;
        int64_t sum = 0;
        while (std::getline(input, bank))
        {
            int64_t joltage = 0;
            int32_t indexUsed = 0;

            const int32_t DIGITS = 12;
            for (int32_t i = 0; i < DIGITS; i++)
            {
                std::string seg = bank.substr(indexUsed, bank.length() - DIGITS + i - indexUsed + 1);
                int32_t maxIndex =
                    std::distance(seg.begin(), std::max_element(seg.begin(), seg.end()));

                joltage += seg[maxIndex] - '0';
                joltage *= 10;

                indexUsed += maxIndex + 1;
            }

            joltage /= 10;
            sum += joltage;
        }

        return std::to_string(sum);
    }
};