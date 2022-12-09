#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Atan.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(AtanTests, toStringTest) {
  EXPECT_EQ(Atan().toString(), "atan");
}

TEST(AtanTests, getFunctionTypeTest) {
  EXPECT_EQ(Atan().getFunctionType(), IFunction::Type::Unary);
}

TEST(AtanTests, callTest) {
  EXPECT_EQ(Atan()(Integer(0))->toString(), "0");
  EXPECT_EQ(Atan()(Integer(1))->toString(), "0.785398163397448309615660845819875721");
  EXPECT_EQ(Atan()(Integer(10))->toString(), "1.471127674303734591852875571761730852");
  EXPECT_EQ(Atan()(Integer(-10))->toString(), "-1.471127674303734591852875571761730852");
  EXPECT_EQ(Atan()(Rational(1, 10))->toString(), "0.09966865249116202737844611987802059");

  EXPECT_EQ(Atan()(Variable("a"))->toString(), "atan(a)");

  std::unique_ptr<IFunction> f = std::make_unique<Atan>();
  EXPECT_EQ((*f)(Integer(10))->toString(), "1.471127674303734591852875571761730852");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}
