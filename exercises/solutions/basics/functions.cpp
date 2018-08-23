#include "functions.hpp"
#include <iostream>
#include <limits>     // necessary to clear cin state (if invalid because of bad input)

static void clearStandardInputErrorFlags();

void fun::printSpaces(int n) {
    //Print necessary spaces to right-align the figure
    while (n-- > 0) {
	    std::cout << ' ';
    }
}

void fun::printStars(int n) {
    //Print required number of stars
    while (n-- > 0) {
	    std::cout << '*';
    }
    //Print the new line
    std::cout << std::endl;
}

void fun::printFigure(int width, Direction d) {
    //Print the upper part of the figure
	for (int i = width; i > 1; --i) {
        if(d == right) {
            printSpaces(width-i);
        }
		printStars(i);
	}
    //Print the lower part of the figure
	for (int i = 1; i <= width; ++i) {
        if(d == right) {
            printSpaces(width-i);
        }
		printStars(i);
	}
}

void fun::task2_6_input() {
	std::cout << "Muster mit Sternen." << std::endl;
	int width;
    //Keep asking until a valid value has been entered
	do {
		std::cout << "Geben Sie die Breite ein (zwischen 1 und 75): ";
		clearStandardInputErrorFlags();
		std::cin >> width;
	} while (width < 1 || width > 75);
    
    //Keep asking until a valid value has been entered
    int input;
    Direction d;
	do {
		std::cout << "Geben Sie die Richtung ein (0=linksbündig, 1=rechtsbündig): ";
		std::cin >> input;
	} while (input < 0 || input > 1);
	if(input == 0) {
	    d = left;
	} else {
	    d = right;
	}
	
	//Print the figure with the user-defined settings
	printFigure(width, d);
}

char fun::nextChar() {
	static char c = 'z';
	if (c >= 'z') {
        //Reset char to a
		c = 'a';
	}
	else {
        //Increment the char to the next one
		c++;
	}
	return c;
}

void fun::printChar(int n) {
	while (n-- > 0) {
		std::cout << nextChar();
	}
	std::cout << std::endl;
}

void fun::printCharFigure() {
	std::cout << "Muster mit Buchstaben." << std::endl;
	int width;
	do {
		std::cout << "Geben Sie die Breite ein (zwischen 1 und 75): ";
		clearStandardInputErrorFlags();
		std::cin >> width;
	} while (width < 1 || width > 75);
	
	for (int i = width; i > 1; --i) {
		printChar(i);
	}
	for (int i = 1; i <= width; ++i) {
		printChar(i);
	}
}

/**
 * @brief Clears error flags and buffered invalid values of std::cin
 * 
 * Solution thanks to https://stackoverflow.com/questions/5864560#5864560
 */
void clearStandardInputErrorFlags() {
	if(std::cin.fail()){ // Check validity of cin state
		std::cin.clear(); // Clear cin internal error state, that is set if input is no int or exceeds
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear current buffer of cin
	}
}