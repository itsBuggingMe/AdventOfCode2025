#include <iostream>
#include <fstream>
#include "Day.cpp"
#include "Day1.cpp"

void run_day(Day* day)
{


	day->part1();
}

int main()
{
	Day* day = new Day1();
	run_day(day);
}
