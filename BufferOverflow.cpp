// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
#include <limits>

int main()
{
	std::cout << "Buffer Overflow Example" << std::endl;

	const std::string account_number = "CharlieBrown42";
	char user_input[20];
	std::cout << "Enter a value: ";

	// Read input while limiting it to the size of the user_input buffer.
	// getline leaves room for the null terminator, so a 20-byte array
	// can safely hold a maximum of 19 typed characters.
	std::cin.getline(user_input, sizeof(user_input));

	// If the user enters more characters than the buffer can safely hold,
	// getline set the input stream's fail state instead of overflowing memory.
	if (std::cin.fail())
	{
		// Clear the fail state so the input stream can be used normally again.
		std::cin.clear();

		// Discard the remaining characters from the oversized input.
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		// Notify the user that the supplied input exceeded the allowed size.
		std::cout << "Input was too long. Maximum length is "
			<< sizeof(user_input) - 1 << " characters." << std::endl;
	}
	else
	{
		// Display the input only when it fit safely inside the buffer.
		std::cout << "You entered: " << user_input << std::endl;
	}


	std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
