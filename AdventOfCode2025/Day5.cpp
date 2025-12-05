#include <vector>

#pragma once

#include "Day.cpp"

struct Range
{
public:
    int64_t Start;
    int64_t End;

    bool contains(int64_t i)
    {
        return i >= Start && i <= End;
    }
};


class Day5 : public Day
{
public:
    std::int32_t day_num() override
    {
        return 5;
    }

    std::string part1(std::istream& input) override
    {
        std::string currentLine;
        int64_t freshIngrdientsCount = 0;
        std::vector<Range> ranges;

        while (std::getline(input, currentLine))
        {
            if (currentLine.length() == 0)
                continue;

            size_t split = currentLine.find('-');
            if (split == std::string::npos)
            {
                int64_t id = std::stoll(currentLine);
                for (Range r : ranges)
                {
                    if (id >= r.Start && id <= r.End)
                    {
                        freshIngrdientsCount++;
                        break;
                    }
                }
            }
            else
            {
                Range r =
                {
                    .Start = std::stoll(currentLine.substr(0, split)),
                    .End = std::stoll(currentLine.substr(split + 1)),
                };

                ranges.push_back(r);
            }
        }

        return std::to_string(freshIngrdientsCount);

    }

    std::string part2(std::istream& input) override
    {
        std::string currentLine;
        std::vector<Range> ranges;

        while (std::getline(input, currentLine))
        {
            size_t split = currentLine.find('-');
            if (split != std::string::npos)
            {
                Range r =
                {
                    .Start = std::stoll(currentLine.substr(0, split)),
                    .End = std::stoll(currentLine.substr(split + 1)),
                };

                ranges.push_back(r);
            }
        }

        bool merged;
        do
        { // lazy brute force loop
            merged = false;

            for (int32_t i = 0; i < ranges.size(); i++)
            {
                Range* r = &ranges[i];
                // loop backwards are we are removing elements
                // n <= i is stable
                // n > i unstable

                for (int32_t j = ranges.size() - 1; j > i; j--)
                {
                    Range r2 = ranges[j];

                    if (r->contains(r2.Start) || r->contains(r2.End))
                    {// mergeable
                        if (!r->contains(r2.End))
                            r->End = r2.End;
                        if (!r->contains(r2.Start))
                            r->Start = r2.Start;
                        merged = true;
                        ranges.erase(ranges.begin() + j);
                    }
                    else if (r2.contains(r->Start) && r2.contains(r->End))
                    {
                        *r = r2;
                        merged = true;
                        ranges.erase(ranges.begin() + j);
                    }
                }
            }
        } while (merged);

        int64_t freshIngrdientsCount = 0;
        for (Range r : ranges)
        {
            freshIngrdientsCount += r.End - r.Start + 1;
        }

        return std::to_string(freshIngrdientsCount);

    }
};