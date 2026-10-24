// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>
#include <stdexcept>

// Custom exception class derived from std::exception.
// This allows the custom error to follow standard C++ exception practices.
class CustomApplicationException : public std::exception
{
public:
    // Override what() so the exception can provide a useful error message.
    const char* what() const noexcept override
    {
        // Return the message that will be displayed when this exception is caught.
        return "A custom application error occurred.";
    }
};

bool do_even_more_custom_application_logic()
{
    // Throw a standard C++ exception to simulate an error in this function.
    throw std::runtime_error("Even more custom application logic failed.");

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}

void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;

    // Wrap the potentially unsafe function call in a try block.
    try
    {
        // Attempt to execute the additional application logic.
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    // Catch standard C++ exceptions thrown by the function above.
    catch (const std::exception& exception)
    {
        // Display both a descriptive message and the exception's what() text.
        std::cout << "Standard exception caught in custom application logic: "
            << exception.what() << std::endl;
    }

    // Throw the custom exception so it can be explicitly caught in main().
    throw CustomApplicationException();

    std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
    // Check for division by zero before performing the calculation.
    if (den == 0.0f)
    {
        // Throw a standard C++ exception describing the invalid operation.
        throw std::runtime_error("Cannot divide by zero.");
    }

    // Perform the division only when the denominator is valid.
    return (num / den);
}

void do_division() noexcept
{
    float numerator = 10.0f;
    float denominator = 0;

    // Catch the exception inside this function because the function is noexcept.
    try
    {
        // Attempt the division, which may throw an exception.
        auto result = divide(numerator, denominator);

        // Display the result when the division completes successfully.
        std::cout << "divide(" << numerator << ", " << denominator
            << ") = " << result << std::endl;
    }
    // Catch only the standard exception type thrown by divide().
    catch (const std::runtime_error& exception)
    {
        // Display the exception message instead of allowing the application to terminate.
        std::cout << "Division exception caught: "
            << exception.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    // Wrap the main application logic so exceptions can be handled centrally.
    try
    {
        // Test the division exception handling.
        do_division();

        // Test the standard and custom application exceptions.
        do_custom_application_logic();
    }
    // Catch the custom exception before the more general std::exception handler.
    catch (const CustomApplicationException& exception)
    {
        // Display the custom exception's message.
        std::cout << "Custom exception caught in main: "
            << exception.what() << std::endl;
    }
    // Catch any remaining exceptions derived from std::exception.
    catch (const std::exception& exception)
    {
        // Display the standard exception's message.
        std::cout << "Standard exception caught in main: "
            << exception.what() << std::endl;
    }
    // Catch any exception that was not handled by the previous handlers.
    catch (...)
    {
        // A catch-all exception does not provide a what() method because
        // the exception's type is unknown.
        std::cout << "An unknown exception was caught in main." << std::endl;
    }

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu