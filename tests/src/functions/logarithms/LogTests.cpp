#include "gtest/gtest.h"

#include "fintamath/functions/logarithms/Log.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(LogTests, toStringTest) {
  EXPECT_EQ(Log().toString(), "log");
}

TEST(LogTests, getFunctionTypeTest) {
  EXPECT_EQ(Log().getFunctionType(), IFunction::Type::Binary);
}

TEST(LogTests, callTest) {
  EXPECT_EQ(Log()(Integer(10), Integer(1))->toString(), "0");
  EXPECT_EQ(Log()(Integer(2), Integer(10))->toString(), "3.321928094887362347870319429489390176");
  EXPECT_EQ(Log()(Integer(2), Integer(3))->toString(), "1.584962500721156181453738943947816509");
  EXPECT_EQ(Log()(Rational(1, 10), Integer(10))->toString(), "-1");

  EXPECT_ANY_THROW(Log()(Variable("a"), Variable("b")));
  EXPECT_ANY_THROW(Log()(Integer(-10), Integer(10)));
  EXPECT_ANY_THROW(Log()(Integer(1), Integer(10)));

  std::unique_ptr<IFunction> f = std::make_unique<Log>();
  EXPECT_EQ((*f)(Integer(2), Integer(10))->toString(), "3.321928094887362347870319429489390176");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(10)));
  EXPECT_ANY_THROW((*f)(Integer(10), Integer(10), Integer(10)));
}