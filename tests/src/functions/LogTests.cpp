#include "gtest/gtest.h"
#include <fintamath/operators/Add.hpp>
#include <fintamath/literals/Variable.hpp>

#include <fintamath/functions/Log.hpp>

using namespace fintamath;

TEST(LogTests, toStringTest) {
  EXPECT_EQ(Log().toString(), "log");
}

TEST(LogTests, callTest){
  EXPECT_EQ(Log()(Integer(10), Integer(1))->to<Rational>().toString(10), "0");
  EXPECT_EQ(Log()(Integer(2), Integer(10))->to<Rational>().toString(10), "3.3219280949");
  EXPECT_EQ(Log()(Integer(2), Integer(3))->to<Rational>().toString(36), "1.584962500721156181453738943947816535");
  EXPECT_EQ(Log()(Rational(1, 10), Integer(10))->to<Rational>().toString(10), "-1");

  EXPECT_ANY_THROW(Log()(Variable("a"), Variable("b")));
  EXPECT_ANY_THROW(Log()(Integer(-10), Integer(10)));
  EXPECT_ANY_THROW(Log()(Integer(1), Integer(10)));

  std::unique_ptr<Function> f = std::make_unique<Log>();
  EXPECT_EQ((*f)(Integer(2), Integer(10))->to<Rational>().toString(10), "3.3219280949");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(10)));
  EXPECT_ANY_THROW((*f)(Integer(10), Integer(10), Integer(10)));
}

TEST(LogTests, equalsTest) {
  EXPECT_TRUE(Log() == Log());
  EXPECT_FALSE(Log() == Add());
}