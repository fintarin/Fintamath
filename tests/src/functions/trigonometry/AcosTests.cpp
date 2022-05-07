#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Acos.hpp"

#include "fintamath/numbers/Rational.hpp"
#include "fintamath/literals/Variable.hpp"

using namespace fintamath;

TEST(AcosTests, toStringTest) {
  EXPECT_EQ(Acos().toString(), "acos");
}

TEST(AcosTests, callTest) {
  EXPECT_EQ(Acos()(Integer(1))->toString(), "0");
  EXPECT_EQ(Acos()(Integer(0))->toString(), "1.570796326794896619231321691639751442");
  EXPECT_EQ(Acos()(Rational(1, 10))->toString(), "1.470628905633336822885798512187058124");
  EXPECT_EQ(Acos()(Rational(-1, 5))->toString(), "1.772154247585227410686447243857374852");

  EXPECT_ANY_THROW(Acos()(Variable("a")));
  EXPECT_ANY_THROW(Acos()(Integer(10)));

  std::unique_ptr<Function> f = std::make_unique<Acos>();
  EXPECT_EQ((*f)(Rational(1, 10))->toString(), "1.470628905633336822885798512187058124");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}
