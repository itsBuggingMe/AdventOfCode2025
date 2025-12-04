#pragma once

#include <string>
#include <iostream>

class Day {
public:
    virtual std::int32_t day_num() = 0;
	virtual std::string part1(std::istream& input) { return ""; }
    virtual std::string part2(std::istream& input) { return ""; }
};