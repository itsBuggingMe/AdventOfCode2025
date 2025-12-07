#pragma once
#include <unordered_map>

#include "Day.cpp"


class Day7 : public Day
{
public:
    std::int32_t day_num() override
    {
        return 7;
    }

    std::string part1(std::istream& input) override
    {
        std::string grid;
        std::string line;
        while (std::getline(input, line))
        {
            grid += line + "\n";
        }
        int32_t gridWidth = grid.find('\n') + 1;
        int32_t counter = 0;

        CountSplits(grid, counter, gridWidth, grid.find('S'));

        return std::to_string(counter);
    }

    static void CountSplits(std::string& grid, int32_t& counter, int32_t gridWidth, int32_t position)
    {
        while (
            position <= grid.length()
            && grid[position] != '|')
        {
            if (grid[position] == '^')
            {
                counter++;
                CountSplits(grid, counter, gridWidth, position + 1);
                CountSplits(grid, counter, gridWidth, position - 1);
                return;
            }

            grid[position] = '|';
            position += gridWidth;
        }
    }

    std::string part2(std::istream& input) override
    {
        std::string grid;
        std::string line;
        while (std::getline(input, line))
        {
            grid += line + "\n";
        }
        int32_t gridWidth = grid.find('\n') + 1;

        std::unordered_map<int64_t, int64_t> cache;
        int64_t splits = CountTimelinesManyWorlds(grid, cache, gridWidth, grid.find('S'));

        return std::to_string(splits);
    }

    static int64_t CountTimelinesManyWorlds(std::string& grid, std::unordered_map<int64_t, int64_t>& cache, int32_t gridWidth, int32_t position)
    {
        int32_t originalPos = position;

        if (cache.contains(originalPos))
            return cache[originalPos];

        while (position < grid.length())
        {
            if (grid[position] == '^')
            {
                int64_t splits =
                    CountTimelinesManyWorlds(grid, cache, gridWidth, position + 1) +
                    CountTimelinesManyWorlds(grid, cache, gridWidth, position - 1);

                cache[originalPos] = splits;
                return splits;
            }
            position += gridWidth;
        }

        return 1;
    }
};