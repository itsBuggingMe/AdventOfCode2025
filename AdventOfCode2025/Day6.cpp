#pragma once

#include "Day.cpp"


class Day6 : public Day
{
public:
    std::int32_t day_num() override
    {
        return 6;
    }

    std::string part1(std::istream& input) override
    {
        std::string currentLine;
        std::string problems;
        int32_t lineCount = 0;
        while (std::getline(input, currentLine))
        {
            lineCount++;
            problems += currentLine;
        }

        int64_t checksum = 0;
        int32_t prevColumnEnd = 0;
        for (int32_t i = 0; i < currentLine.length(); i++)
        {
            bool hasNonWhiteSpace = false;

            if (i != currentLine.length() - 1)
            {
                for (int32_t j = 0; j < lineCount; j++)
                    if (problems[i + j * currentLine.length()] != ' ')
                    {
                        hasNonWhiteSpace = true;
                        break;
                    }
            }
            else
            {
                i++;
            }
            

            if (!hasNonWhiteSpace)
            {
                // calc
                char opcode = problems[prevColumnEnd + (static_cast<size_t>(lineCount) - 1) * currentLine.length()];
                int64_t accumulator = opcode == '*' ? 1 : 0;

                for (int32_t j = 0; j < lineCount - 1; j++)
                {
                    int64_t operand = std::stoll(problems.substr(prevColumnEnd + j * currentLine.length(), i - prevColumnEnd));

                    switch (opcode) {
                        case '*':
                            accumulator *= operand;
                            break;
                        case '+':
                            accumulator += operand;
                            break;
                    }
                }

                checksum += accumulator;

                prevColumnEnd = i + 1;
            }
        }

        return std::to_string(checksum);
    }

    std::string part2(std::istream& input) override
    {
        std::string currentLine;
        std::string problems;
        int32_t lineCount = 0;
        while (std::getline(input, currentLine))
        {
            lineCount++;
            problems += currentLine;
        }

        int64_t checksum = 0;
        int32_t prevColumnEnd = 0;
        for (int32_t i = 0; i < currentLine.length(); i++)
        {
            bool hasNonWhiteSpace = false;

            if (i != currentLine.length() - 1)
            {
                for (int32_t j = 0; j < lineCount; j++)
                    if (problems[i + j * currentLine.length()] != ' ')
                    {
                        hasNonWhiteSpace = true;
                        break;
                    }
            }
            else
            {
                i++;
            }


            if (!hasNonWhiteSpace)
            {
                // calc
                char opcode = problems[prevColumnEnd + (static_cast<size_t>(lineCount) - 1) * currentLine.length()];
                int64_t accumulator = opcode == '*' ? 1 : 0;

                for (int32_t j = 0; j < i - prevColumnEnd; j++)
                {
                    std::string chars;
                    for (int32_t k = 0; k < lineCount - 1; k++)
                    {
                        chars += problems[k * currentLine.length() + prevColumnEnd + j];
                    }

                    int64_t operand = std::stoll(chars);

                    switch (opcode) {
                    case '*':
                        accumulator *= operand;
                        break;
                    case '+':
                        accumulator += operand;
                        break;
                    }
                }

                checksum += accumulator;

                prevColumnEnd = i + 1;
            }
        }

        return std::to_string(checksum);
    }
};