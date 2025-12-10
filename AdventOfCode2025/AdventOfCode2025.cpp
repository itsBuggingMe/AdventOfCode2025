#pragma once

#include <iostream>
#include <fstream>
#include "Day.cpp"
#include "Day1.cpp"
#include "Day2.cpp"
#include "Day3.cpp"
#include "Day4.cpp"
#include "Day5.cpp"
#include "Day6.cpp"
#include "Day7.cpp"
#include "Day8.cpp"
#include "Day9.cpp"

static void run_day(Day* day)
{
	std::string path = "Inputs\\Day" + std::to_string(day->day_num()) + ".txt";
	std::ifstream file(path);

	std::cout << "Day " << day->day_num() << " Part 1" << std::endl;
	std::cout << day->part1(file) << std::endl;

	file.clear();
	file.seekg(0, std::ios::beg);

	std::cout << "Day " << day->day_num() << " Part 2" << std::endl;
	std::cout << day->part2(file) << std::endl;
}

int main()
{
	Day* day = new Day9();
	run_day(day);
}
