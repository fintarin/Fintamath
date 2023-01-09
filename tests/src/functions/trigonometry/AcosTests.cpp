#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Acos.hpp"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Acos f;

TEST(AcosTests, toStringTest) {
  EXPECT_EQ(f.toString(), "acos");
}

TEST(AcosTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Unary);
}

TEST(AcosTests, callTest) {
  EXPECT_EQ(f(Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(0))->toString(),
            "1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");
  EXPECT_EQ(f(Rational(1, 10))->toString(),
            "1.4706289056333368228857985121870581235299087274579233690964484411175055294922419");
  EXPECT_EQ(f(Rational(-1, 5))->toString(),
            "1.7721542475852274106864472438573748523386227810897812967447235396095175777719563");

  EXPECT_EQ(f(Variable("a"))->toString(), "acos(a)");

  EXPECT_THROW(f(Integer(10)), UndefinedFunctionException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
