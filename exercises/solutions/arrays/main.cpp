#include <cstddef>
#include <iostream>

// Task 2
void printArray(const int *arr, const size_t& size) {
	std::cout << "printArray" << std::endl;
	for (size_t i = 0; i < size; ++i) {
		std::cout << arr[i] << std::endl;
	}
}

// Task 3
void printArrayPointer(const int *arr, size_t size) {
	std::cout << "printArrayPointer" << std::endl;
	for (const int *p = arr; p != arr + size; ++p) {
		std::cout << *p << std::endl;
	}
}

/**
 * @brief Task 4: Iterator-style implementation for printing an array
 * @param begin the point to the first array element to print
 * @param end the pointer to the array element behind the last array element to print
 */
void printArray(const int *begin, const int *end) {
	std::cout << "printArray" << std::endl;
	for (const int *p = begin; p != end; ++p) {
		std::cout << *p << std::endl;
	}
}

/**
 * @brief Task 6: Reads a user-specified amount of numbers from standard input
 * @param size the output variable that stores the user-defined amount of numbers
 * @return a point to an array on the heap of the length stored in the output parameter size
 */
int* readNumbers(size_t *size) {
	size_t n;
	std::cout << "Geben Sie die Groesse ein: ";
	std::cin >> n;

	std::cout << "Geben Sie " << n << " Zahlen ein: " << std::endl;
	int *arr = new int[n];
	for (size_t i = 0; i < n; ++i) {
		std::cin >> arr[i];
	}
	*size = n;
	return arr;
}

/**
 * @brief Task 7: Reads the given amount of numbers from the standard input
 * @param n the amount of numbers to read
 * @return a point to an array on the heap of length n
 */
int* readNumbers(const size_t n) {
	std::cout << "Geben Sie " << n << " Zahlen ein: " << std::endl;

	int *arr = new int[n];

	for (size_t i = 0; i < n; ++i) {
		std::cin >> arr[i];
	}

	return arr;
}

int main(int argc, char** argv) {
	// Task 1
	int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	for (size_t i = 0; i < 10; ++i) {
		std::cout << arr[i] << std::endl;
	}

	// Task 2
	printArray(arr, 10);

	// Task 3
	printArrayPointer(arr, 10);

	// Task 4
	printArray(arr, arr + 10);

	// Task 5
	printArray(arr + 3, arr + 7); // elements 4, 5, 6, 7

	// Task 6
	{// This brace defines a scope that allows to use the variable 'size' multiple times within 'main'.
		size_t size;	// variable to store array size
		int *pArr = readNumbers(&size);		// read some numbers

		printArray(pArr, pArr + size);		// print the numbers

		delete[] pArr;	// delete array
		pArr = NULL;	// avoid dangling pointer
	}

	// Task 7
	{
		std::cout << "argv[0]: " << argv[0] << std::endl;
		if (argc >= 2) {
			size_t size = std::stoi(argv[1]);	// convert C string to integer
			int *pArr = readNumbers(size);		// read size numbers

			printArray(pArr, pArr + size);		// print the numbers

			delete[] pArr;	// delete array
			pArr = NULL;	// avoid dangling pointer
		} else {
			// std::cerr is the standard error log
			std::cerr << "Not enough command-line parameters given. Expecting at least one parameter." << std::endl;
		}
	}
}
