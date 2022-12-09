#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Acos.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(AcosTests, toStringTest) {
  EXPECT_EQ(Acos().toString(), "acos");
}

TEST(AcosTests, getFunctionTypeTest) {
  EXPECT_EQ(Acos().getFunctionType(), IFunction::Type::Unary);
}

TEST(AcosTests, callTest) {
  EXPECT_EQ(Acos()(Integer(1))->toString(), "0");
  EXPECT_EQ(Acos()(Integer(0))->toString(),
            "1.5707963267948966192313216916397514420985846996875529104874722961539082031431045");
  EXPECT_EQ(Acos()(Rational(1, 10))->toString(),
            "1.4706289056333368228857985121870581235299087274579233690964484411175055294922419");
  EXPECT_EQ(Acos()(Rational(-1, 5))->toString(), "1.7721542475852274106864472438573748523386227810897812967447235396095175777719563");

  EXPECT_EQ(Acos()(Variable("a"))->toString(), "acos(a)");

  EXPECT_ANY_THROW(Acos()(Integer(10)));

  std::unique_ptr<IFunction> f = std::make_unique<Acos>();
  EXPECT_EQ((*f)(Rational(1, 10))->toString(), "1.4706289056333368228857985121870581235299087274579233690964484411175055294922419");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}
