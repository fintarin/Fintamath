#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Asinh.hpp"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Asinh f;

TEST(AsinhTests, toStringTest) {
  EXPECT_EQ(f.toString(), "asinh");
}

TEST(AsinhTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AsinhTests, callTest) {
  EXPECT_EQ(f(Integer(0))->toString(), "0");
  EXPECT_EQ(f(Integer(1))->toString(),
            "0.88137358701954302523260932497979230902816032826163541075329560865337718422202609");
  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "0.099834078899207563327303124704769443267712911708825010742382695651591768393613465");
  EXPECT_EQ(f(Rational(-1, 5))->toString(),
            "-0.19869011034924140647463691595020696822130879422445377302126322228548564789597237");

  EXPECT_EQ(f(Variable("a"))->toString(), "asinh(a)");

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
