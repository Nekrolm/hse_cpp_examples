
#include "testing.h"

TEST(TwoPlusTwo) {
   int a = 2;
   int b = 2;
   ASSERT(a + b == 2);
}

TEST(TwoMinusTwo) {
   int a = 2;
   int b = 2;
   ASSERT(a - b == 0);
}


int main(int argc, char* argv[]) {
  RUN_ALL_TESTS;
}
