// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start + (increment * steps)</returns>
template <typename T>
T add_numbers(T const& start, T const& increment, unsigned long int const& steps, bool& overflow)
{
    // Start with the value provided by the calling function.
    T result = start;

    // Assume no overflow has occured unless one is detected.
    overflow = false;

    // Perform the requested number of additions one step at a time.
    for (unsigned long int i = 0; i < steps; ++i)
    {
        // Check whether adding the increment would exceed the
        // maximum value that the current numeric type can store.
        if (result > std::numeric_limits<T>::max() - increment)
        {
            // Notify the calling function that overflow was detected.
            overflow = true;

            // Return the last valid value instead of performing
            // the unsafe condition.
            return result;
        }

        // The addition is safe, so perform it.
        result += increment;
    }

    // Return the final result when every addition completed safely.
    return result;
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start - (increment * steps)</returns>

template <typename T>
T subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps, bool& underflow)
{
    // Start with the value provided by the calling function.
    T result = start;

    // Assume no underflow has occured unless one is detected.
    underflow = false;

    // Perform the requested number of subtractions one step at a time.
    for (unsigned long int i = 0; i < steps; ++i)
    {
        // Check whether the next subtraction would go below the
        // expected safe range for the test.
        if (result < decrement)
        {
            // Notify the calling function that underflow was detected.
            underflow = true;

            // Return the last valid value instead of performing
            // the unsafe subtraction.
            return result;
        }

        // The subtraction is safe, so perform it
        result -= decrement;
    }

    // Return the final result when every subtraction completed safely.
    return result;
}


//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
    // TODO: The add_numbers template function will overflow in the second method call
    //        You need to change the add_numbers method to:
    //        1. Detect when an overflow will happen
    //        2. Prevent it from happening
    //        3. Return the correct value when no overflow happened or
    //        4. Return something to tell test_overflow the addition failed
    //        NOTE: The add_numbers method must remain a template in the NumericFunctions header.
    //
    //        You need to change the test_overflow method to:
    //        1. Detect when an add_numbers failed
    //        2. Inform the user the overflow happened
    //        3. A successful result displays the same result as before you changed the method
    //        NOTE: You cannot change anything between START / END DO NOT CHANGE
    //              The test_overflow method must remain a template in the NumericOverflows source file
    //
    //  There are more than one possible solution to this problem. 
    //  The solution must work for all of the data types used to call test_overflow() in main().

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we add each step (result should be: start + (increment * steps))
    const T increment = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    // Store whether the add_numbers function detects an overflow.
    bool overflow = false;


    std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";

    // Pass overflow by reference so add_numbers can change its value.
    T result = add_numbers<T>(start, increment, steps, overflow);

    // Display true or false for the overflow status along with the result.
    std::cout << std::boolalpha
        << "Overflow Status:" << overflow
        << ", Result: " << +result << std::endl;

    // Reset the flag before running the second test.
    overflow = false;

    std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";

    // Run one extra step, which should trigger the overflow protection.
    result = add_numbers<T>(start, increment, steps + 1, overflow);

    // Display the overflow status and the last safe result
    std::cout << std::boolalpha
        << "Overflow Status:" << overflow
        << ", Result: " << +result << std::endl;
}

template <typename T>
void test_underflow()
{
    // TODO: The subtract_numbers template function will underflow in the second method call
    //        You need to change the subtract_numbers method to:
    //        1. Detect when an underflow will happen
    //        2. Prevent it from happening
    //        3. Return the correct value when no underflow happened or
    //        4. Return something to tell test_underflow the subtraction failed
    //        NOTE: The subtract_numbers method must remain a template in the NumericFunctions header.
    //
    //        You need to change the test_underflow method to:
    //        1. Detect when an subtract_numbers failed
    //        2. Inform the user the underflow happened
    //        3. A successful result displays the same result as before you changed the method
    //        NOTE: You cannot change anything between START / END DO NOT CHANGE
    //              The test_underflow method must remain a template in the NumericOverflows source file
    //
    //  There are more than one possible solution to this problem. 
    //  The solution must work for all of the data types used to call test_overflow() in main().

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we subtract each step (result should be: start - (increment * steps))
    const T decrement = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    // Store whether the subtract_numbers function detects an underflow.
    bool underflow = false;

    std::cout << "\tSubtracting Numbers Without Overflow (" << +start << ", " << +decrement << ", " << steps << ") = ";

    // Pass underflow by reference so subtract_numbers can change its value.
    auto result = subtract_numbers<T>(start, decrement, steps, underflow);

    // Display true or false for the underflow status along with the result
    std::cout << std::boolalpha
        << "Underflow status: " << underflow
        << ", Result: " << +result << std::endl;

    // Reset the flag before running the second test.
    underflow = false;

    std::cout << "\tSubtracting Numbers With Overflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";

    // Run one extra subtraction, which should trigger the underflow protection.
    result = subtract_numbers<T>(start, decrement, steps + 1, underflow);

    // Display the underflow status and the last safe result.
    std::cout << std::boolalpha
        << "Underflow status: " << underflow
        << ", Result: " << +result << std::endl;
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Undeflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    //  create a string of "*" to use in the console
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
