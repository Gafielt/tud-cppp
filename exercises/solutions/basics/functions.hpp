#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

/**
 * @file functions.hpp
 * @author C++ Praktikums Teilnehmer
 * @brief Contains necessary functions of ex02_basics
 */

/**
 * @brief This namespace encapsulates all functions for printing patterns
 */
namespace fun {

    /**
     * @author cppp
     * @brief This enum defines the possible directions of the figure.
     */
    enum Direction {
      /** Prints the figure left-adjusted. */
      left,
      /** Prints the figure right-adjusted. */
      right };

    /**
     * @author cppp
     * @brief Prints a given number of spaces (' ').
     * @param n defines the number of printed spaces.
     * @return void
     */
    void printSpaces(int n);

    /**
     * @author cppp
     * @brief Prints a given number of stars ('*') and ends with a new line.
     * @param n Defines the number of printed stars.
     * @return void
     */
	void printStars(int n);
    
    /**
     * @author cppp
     * @brief Prints the required star form depending on the given direction.
     * @param width The width of the figure.
     * @param d The direction how to align the figure.
     * @return void
     */
	void printFigure(int width, Direction d);
    
    /**
     * @author cppp
     * @brief Captures user input (figure width and figure direction).
     * @return void
     */
	void task2_6_input();
    
    /**
     * @author cppp
     * @brief Calculates the next char based on a static one.
     * @return void
     */
	char nextChar();
    
    /**
     * @sa print_stars(int n);
     * @author cppp
     * @brief Prints a given number of letters. Ends with a new line.
     * @param n Defines the number of printed letters.
     * @return void
     */
	void printChar(int n);
    
    /**
     * @author cppp
     * @brief Asks for the width and prints the figure of alphabet characters.
     * @return void
     */
	void printCharFigure();
};

#endif /* FUNCTIONS_HPP_ */
