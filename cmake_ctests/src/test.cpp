#include <gtest/gtest.h>


TEST(example_group, example_true) {
  ASSERT_EQ(1,1);
  ASSERT_NE(1,2);
}

TEST(example_group, example_false) {
  ASSERT_NE(1,1);
  ASSERT_EQ(1,2);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}