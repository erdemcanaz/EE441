#include <iostream>

class Date {
	private:
		int day; // Data representation of day
		int month; // Data representation of month
		int year; // Data representation of year
	public:
		// Constructor
		Date (int d=1, int m=1, int y=1900);
		// Method to print the current date
		void PrintDate(void) const;
		// Method to modify the year by j
		int JumpYear(int j) const;
		// Method to directly set the date
		void SetDate(int d, int m, int y);
};
