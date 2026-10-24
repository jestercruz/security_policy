#include "pch.h"
#include <climits>
#include <iostream>
#include <sstream>

// Compliant code from STD-002-CPP in Project One.
void addValues(int valueA, int valueB)
{
    // Check for positive overflow before performing the addition.
    if ((valueB > 0) && (valueA > INT_MAX - valueB))
    {
        // Handle the value that would exceed the maximum int.
        std::cout << "Integer overflow detected." << std::endl;
        return;
    }

    // Check for negative overflow before performing the addition.
    if ((valueB < 0) && (valueA < INT_MIN - valueB))
    {
        // Handle the value that would fall below the minimum int.
        std::cout << "Integer underflow detected." << std::endl;
        return;
    }

    // Perform the addition only after the operands have been checked.
    int result = valueA + valueB;

    // Display the safe result.
    std::cout << result << std::endl;
}

// Test 1: Does normal integer addition produce the correct result?
TEST(IntegerAdditionTests, NormalAdditionProducesCorrectResult)
{
    // Create a stream to capture the program's output.
    std::ostringstream capturedOutput;

    // Save the original standard output destination.
    std::streambuf* originalBuffer = std::cout.rdbuf();

    // Redirect standard output to our capture stream.
    std::cout.rdbuf(capturedOutput.rdbuf());

    // Run the compliant function with two valid integers.
    addValues(10, 20);

    // Restore standard output to its original destination.
    std::cout.rdbuf(originalBuffer);

    // Verify that the function displayed the correct result.
    EXPECT_EQ("30\n", capturedOutput.str());
}

// Test 2: Does the program detect positive integer overflow?
TEST(IntegerAdditionTests, PositiveOverflowIsDetected)
{
    // Create a stream to capture the program's output.
    std::ostringstream capturedOutput;

    // Save the original standard output destination.
    std::streambuf* originalBuffer = std::cout.rdbuf();

    // Redirect standard output to our capture stream.
    std::cout.rdbuf(capturedOutput.rdbuf());

    // Attempt to add 1 to the maximum possible int value.
    addValues(INT_MAX, 1);

    // Restore standard output to its original destination.
    std::cout.rdbuf(originalBuffer);

    // Verify that overflow was detected before addition occurred.
    EXPECT_EQ("Integer overflow detected.\n", capturedOutput.str());
}

// Test 3: Does the program detect negative integer underflow?
TEST(IntegerAdditionTests, NegativeUnderflowIsDetected)
{
    // Create a stream to capture the program's output.
    std::ostringstream capturedOutput;

    // Save the original standard output destination.
    std::streambuf* originalBuffer = std::cout.rdbuf();

    // Redirect standard output to our capture stream.
    std::cout.rdbuf(capturedOutput.rdbuf());

    // Attempt to subtract 1 from the minimum possible int value.
    addValues(INT_MIN, -1);

    // Restore standard output to its original destination.
    std::cout.rdbuf(originalBuffer);

    // Verify that underflow was detected before addition occurred.
    EXPECT_EQ("Integer underflow detected.\n", capturedOutput.str());
}

// Test 4: Does the program accept addition at the maximum valid boundary?
TEST(IntegerAdditionTests, MaximumValidBoundaryIsAccepted)
{
    // Create a stream to capture the program's output.
    std::ostringstream capturedOutput;

    // Save the original standard output destination.
    std::streambuf* originalBuffer = std::cout.rdbuf();

    // Redirect standard output to our capture stream.
    std::cout.rdbuf(capturedOutput.rdbuf());

    // Add two values whose sum is exactly INT_MAX.
    addValues(INT_MAX - 1, 1);

    // Restore standard output to its original destination.
    std::cout.rdbuf(originalBuffer);

    // Construct the expected output using the maximum valid integer.
    std::ostringstream expectedOutput;
    expectedOutput << INT_MAX << '\n';

    // Verify the valid boundary was accepted and calculated correctly.
    EXPECT_EQ(expectedOutput.str(), capturedOutput.str());
}
