#pragma once

#include "Day.cpp"

class Day2 : public Day
{
public:
    std::int32_t day_num() override
    {
        return 2;
    }

    std::string part1(std::istream& input) override
    {
        std::string range;
        int64_t sum = 0;
        while (std::getline(input, range, ','))
        {
            size_t split = range.find('-');

            int64_t start = std::stoll(range.substr(0, split));
            int64_t end = std::stoll(range.substr(split + 1));

            for (int64_t i = start; i <= end; i++)
            {
                std::string str = std::to_string(i);
                size_t len = str.length();

                if (len % 2 == 1)
                    continue;

                if (str.substr(len / 2) == str.substr(0, len / 2))
                {
                    sum += i;
                }
            }
        }

        return std::to_string(sum);
    }

    std::string part2(std::istream& input) override
    {
        std::string range;
        int64_t sum = 0;

        while (std::getline(input, range, ','))
        {
            size_t split = range.find('-');

            int64_t start = std::stoll(range.substr(0, split));
            int64_t end = std::stoll(range.substr(split + 1));

            for (int64_t i = start; i <= end; i++)
            {
                std::string str = std::to_string(i);
                size_t len = str.length();

                for (int32_t j = 1; j <= len / 2; j++)
                {
                    if (len % j != 0)
                        continue;

                    bool isValidId = false;

                    for (int32_t k = j; k < len; k += j)
                    {
                        if (str.substr(0, j) != str.substr(k, j))
                        {
                            isValidId = true;
                            break;
                        }
                    }

                    if (!isValidId)
                    {
                        sum += i;
                        break;
                    }
                }
            }
        }

        return std::to_string(sum);
    }
};