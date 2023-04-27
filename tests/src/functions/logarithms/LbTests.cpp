#include "gtest/gtest.h"

#include "fintamath/functions/logarithms/Lb.hpp"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Lb f;

TEST(LbTests, toStringTest) {
  EXPECT_EQ(f.toString(), "lb");
}

TEST(LbTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(LbTests, callTest) {
  EXPECT_EQ(f(Integer(2))->toString(), "1");
  EXPECT_EQ(f(Integer(10))->toString(),
            "3.3219280948873623478703194294893901758648313930245806120547563958159347766086252");
  EXPECT_EQ(f(Integer(3))->toString(),
            "1.5849625007211561814537389439478165087598144076924810604557526545410982277943586");
  EXPECT_EQ(f(Rational(1, 16))->toString(), "-4");

  EXPECT_EQ(f(Variable("a"))->toString(), "ln(a)/ln(2)");

  EXPECT_THROW(f(Integer(-10)), UndefinedFunctionException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(10), Integer(10), Integer(10)), InvalidInputFunctionException);
}
