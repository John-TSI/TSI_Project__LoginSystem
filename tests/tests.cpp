#include<gtest/gtest.h>
#include"../inc/manager.hpp"


TEST(TrivialTest, BasicAssertions)
{
	EXPECT_STRNE("hello", "world");
	EXPECT_EQ(7*6, 42);
}

// ---- gtest driver code ----
int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}