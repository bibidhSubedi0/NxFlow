#include <gtest/gtest.h> // Include Google Test
#include "MathFunctions.h" // Include CoreLibrary's header

TEST(MathFunctionsTest, AdditionTest) {
    // Test the add function
    EXPECT_EQ(CoreLibrary::add(3, 4), 7); // Expect 3 + 4 = 7
    EXPECT_EQ(CoreLibrary::add(0, 0), 0); // Expect 0 + 0 = 0
    EXPECT_EQ(CoreLibrary::add(-1, 1), 0); // Expect -1 + 1 = 0
}
