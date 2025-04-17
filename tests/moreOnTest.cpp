#include <gtest/gtest.h>
#include <iostream>

class Fixture : public testing::Test
{
    void SetUp() override
    {
        std::cout << "------------------------ Local Setup -------------------------\n";
    };
    void TearDown() override
    {
        std::cout << "------------------------ Local TearDown -------------------------\n";
    };
};

TEST(custom, floatingTolerance)
{
    double x{4.0};
    double y{0.56};
    ASSERT_NE(4.56, x + y);
}

TEST(custom, floatingTolerance1)
{
    double x{4.0};
    double y{0.56};
    ASSERT_FLOAT_EQ(4.56, x + y);
}

TEST(custom, exceptions)
{
    ASSERT_ANY_THROW(throw std::runtime_error("Test exception"));
}

TEST(custom, DISABLED_disabled)
{
}

TEST_F(Fixture, withSetup)
{
}

/**
 * @brief A simple class to perform addition of two integers.
 */
class Adder
{
    public:
    /**
     * @brief Computes the sum of two integers.
     * @param a First integer.
     * @param b Second integer.
     * @return The sum of a and b.
     */
    static int sum(int a, int b)
    {
        return a + b;
    }
};

TEST(custom, GeneratesASumFromTwoNumbers)
{
    // Test to verify the sum of two numbers using the Adder class
    ASSERT_EQ(Adder::sum(1, 1), 2);
}

/**
 * @brief Represents a test case for summing two integers.
 * designed to capture two input numbers and an expected sum. 
 */
struct SumCase {
   int a, b, expected;

   /**
    * @brief Constructs a SumCase object.
    * @param anA First integer.
    * @param aB Second integer.
    * @param anExpected Expected result of the sum.
    */
   SumCase(int anA, int aB, int anExpected)
      : a(anA), b(aB), expected(anExpected) {}
};

/**
 * @brief Parameterized test class for testing the Adder class with multiple inputs.
 */
class AddFixture: public testing::TestWithParam<SumCase> {
};
// Array of test cases for parameterized testing
SumCase sums[] = {
    SumCase(1, 1, 2), // Test case 1: 1 + 1 = 2
    SumCase(1, 2, 3), // Test case 2: 1 + 2 = 3
    // SumCase(2, 2, 5)  // Test case 3: 2 + 2 = 5 (intentional failure for demonstration)
};

// Instantiate the parameterized test suite (prefix,test_suite_name,__VA_ARGS__...)
INSTANTIATE_TEST_SUITE_P(BulkTest, AddFixture, testing::ValuesIn(sums));
/* The ​ValuesIn ​function indicates that the injection process should use 
an element from the array ​sums​ to inject into the test 
(GeneratesLotsOfSumsFromTwoNumbers) each time it’s called. 
The first line in the test calls​GetParam​, which returns 
the injected value (a ​SumCase​ object).*/

TEST_P(AddFixture, GeneratesLotsOfSumsFromTwoNumbers)
{
    // Retrieve the current parameter (SumCase object)
    SumCase input = GetParam();

    // Test to verify the sum of two numbers using the Adder class
    ASSERT_EQ(Adder::sum(input.a, input.b), input.expected);
}
