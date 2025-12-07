#include <vector>

#pragma once

#include "Day.cpp"

class Day4 : public Day
{
public:
    std::int32_t day_num() override
    {
        return 4;
    }

    std::string part1(std::istream& input) override
    {
        std::string grid;
        std::string line;
        while (std::getline(input, line))
        {
            grid += line + "\n";
        }

        int32_t accessibleRolls = 0;
        int32_t gridWidth = grid.find('\n') + 1;

        int32_t offsets[] = {
            1,
            -1,
            gridWidth,
            -gridWidth,
            gridWidth + 1,
            gridWidth - 1,
            -gridWidth + 1,
            -gridWidth - 1
        };

        for (int32_t i = 0; i < grid.length(); i++)
        {
            if (grid[i] != '@')
                continue;

            int32_t obstructions = 0;

            for (int32_t delta : offsets)
            {

                int32_t index = delta + i;
                if (index >= 0 && index < grid.length() && grid[index] == '@')
                {
                    obstructions++;
                }
            }

            if (obstructions < 4)
                accessibleRolls++;
        }

        return std::to_string(accessibleRolls);
    }

    std::string part2(std::istream& input) override
    {
        std::string grid;
        std::string line;
        while (std::getline(input, line))
        {
            grid += line + "\n";
        }

        int32_t removedRolls = 0;
        int32_t gridWidth = grid.find('\n') + 1;

        int32_t offsets[] = {
            1,
            -1,
            gridWidth,
            -gridWidth,
            gridWidth + 1,
            gridWidth - 1,
            -gridWidth + 1,
            -gridWidth - 1

        };

        std::vector<int32_t> removeIndicies;

        do
        {
            for (int32_t i : removeIndicies)
                grid[i] = '.';
            removeIndicies.clear();

            for (int32_t i = 0; i < grid.length(); i++)
            {
                if (grid[i] != '@')
                    continue;

                int32_t obstructions = 0;

                for (int32_t delta : offsets)
                {

                    int32_t index = delta + i;
                    if (index >= 0 && index < grid.length() && grid[index] == '@')
                        obstructions++;
                }

                if (obstructions < 4)
                {
                    removeIndicies.push_back(i);
                    removedRolls++;
                }
            }
        } while (removeIndicies.size() > 0);

        return std::to_string(removedRolls);
    }
};