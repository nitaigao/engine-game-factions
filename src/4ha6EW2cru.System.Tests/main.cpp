#include <gtest/gtest.h>

//#include "TestEnvironment.hpp"

int main(int argc, char **argv) 
{
  ::testing::InitGoogleTest(&argc, argv);
  //::testing::AddGlobalTestEnvironment(new Testing::Environment());
  return RUN_ALL_TESTS();
}