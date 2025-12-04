#include <string>
#include <iostream>

class Day {
public:
	std::int32_t day_number;
    virtual std::string part1(std::istream& input) = 0;
    virtual std::string part2(std::istream& input) = 0;
};