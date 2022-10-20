#include <gtest/gtest.h>

#include "fintamath/helpers/TypeInfo.hpp"

using namespace fintamath::help;

TEST(TypeInfoTests, typeInfoConstructorTest) {
  EXPECT_NO_THROW(TypeInfo(typeid(std::string)));
  EXPECT_NO_THROW(TypeInfo(typeid(int)));
  EXPECT_NO_THROW(TypeInfo(typeid(char *)));
  EXPECT_NO_THROW(TypeInfo(typeid(const TypeInfo &)));
}

TEST(TypeInfoTests, lessTest) {
  TypeInfo t1(typeid(float));
  TypeInfo t2(typeid(TypeInfo));

  EXPECT_EQ(t1 < t1, typeid(float).before(typeid(float)));
  EXPECT_EQ(t2 < t2, typeid(TypeInfo).before(typeid(TypeInfo)));
  EXPECT_EQ(t1 < t2, typeid(float).before(typeid(TypeInfo)));
  EXPECT_EQ(t2 < t1, typeid(TypeInfo).before(typeid(float)));
}
