#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

#include "Day.cpp"

struct HorizontalSegment
{
    int32_t A;
    int32_t B;
    int32_t Y;
};

class Day9 : public Day
{
public:
    std::int32_t day_num() override
    {
        return 9;
    }

    std::string part1(std::istream& input) override
    {
        std::vector<int32_t> x;
        std::vector<int32_t> y;
        std::string line;

        while (std::getline(input, line))
        {
            int32_t middle = line.find(',');
            x.push_back(std::stoi(line.substr(0, middle)));
            y.push_back(std::stoi(line.substr(middle + 1)));
        }

        int64_t max = 0;
        for (int32_t i = 0; i < x.size(); i++)
        {
            for (int32_t j = i; j < x.size(); j++)
            {
                int64_t dx = std::abs(x[i] - x[j]) + 1;
                int64_t dy = std::abs(y[i] - y[j]) + 1;
                if (dx * dy > max) max = dx * dy;
            }
        }

        return std::to_string(max);
    }

    std::string part2(std::istream& input) override
    {
        std::vector<int32_t> x;
        std::vector<int32_t> y;
        std::string line;
        int32_t prevYPos = -1;
        std::vector<HorizontalSegment> horizontalSegments;

        while (std::getline(input, line))
        {
            int32_t middle = line.find(',');
            int32_t xpos = std::stoi(line.substr(0, middle));
            int32_t ypos = std::stoi(line.substr(middle + 1));

            if (prevYPos != -1 && ypos == prevYPos)
            {
                horizontalSegments.push_back(HorizontalSegment
                {
                    .A = xpos,
                    .B = x.back(),
                    .Y = ypos
                });
            }

            x.push_back(xpos);
            y.push_back(ypos);
            prevYPos = ypos;
        }

        // prevYPos is now y pos of last point
        if (prevYPos == y[0])
        {
            horizontalSegments.push_back(HorizontalSegment
            {
                .A = x[0],
                .B = x.back(),
                .Y = prevYPos
            });
        }

        int64_t max = 0;
        for (int32_t i = 0; i < x.size(); i++)
        {
            for (int32_t j = i; j < x.size(); j++)
            {
                int64_t dx = std::abs(x[i] - x[j]) + 1;
                int64_t dy = std::abs(y[i] - y[j]) + 1;
                if (dx * dy > max)
                {
                    for (int32_t k = std::min(x[i], x[j]); k <= std::max(x[i], x[j]); k++)
                    {
                        if (!WithinBounds(horizontalSegments, k, y[i]))
                            goto failed;
                    }

                    for (int32_t k = std::min(x[i], x[j]); k <= std::max(x[i], x[j]); k++)
                    {
                        if (!WithinBounds(horizontalSegments, k, y[j]))
                            goto failed;
                    }

                    for (int32_t k = std::min(y[i], y[j]); k <= std::max(y[i], y[j]); k++)
                    {
                        if (!WithinBounds(horizontalSegments, x[i], k))
                            goto failed;
                    }

                    for (int32_t k = std::min(y[i], y[j]); k <= std::max(y[i], y[j]); k++)
                    {
                        if (!WithinBounds(horizontalSegments, x[j], k))
                            goto failed;
                    }

                    max = dx * dy;
                }

            failed:;
            }
        }

        return std::to_string(max);
    }

    bool WithinBounds(std::vector<HorizontalSegment>& segments, float i, float j)
    {
        return WithinBoundsOneRay(segments, i, j)
            || WithinBoundsOneRay(segments, i - 0.5, j)
            || WithinBoundsOneRay(segments, i, j + 0.5)
            || WithinBoundsOneRay(segments, i - 0.5, j + 0.5);
    }

    bool WithinBoundsOneRay(std::vector<HorizontalSegment>& segments, float x, float y)
    {
        // validate rectangle
        bool inside = false;
        for (HorizontalSegment segment : segments)
        {
            if (y <= segment.Y && 
                (segment.A > segment.B ?
                (x >= segment.B && x < segment.A) :
                (x >= segment.A && x < segment.B)))
            {
                inside = !inside;
            }
        }

        return inside;
    }
};