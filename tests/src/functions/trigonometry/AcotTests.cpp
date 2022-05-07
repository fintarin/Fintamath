#include "gtest/gtest.h"

#include "fintamath/functions/trigonometry/Acot.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(AcotTests, toStringTest) {
  EXPECT_EQ(Acot().toString(), "acot");
}

TEST(AcotTests, callTest) {
  EXPECT_EQ(Acot()(Integer(0))->toString(), "1.570796326794896619231321691639751442");
  EXPECT_EQ(Acot()(Integer(1))->toString(), "0.785398163397448309615660845819875721");
  EXPECT_EQ(Acot()(Integer(10))->toString(), "0.09966865249116202737844611987802059");
  EXPECT_EQ(Acot()(Integer(-10))->toString(), "-0.09966865249116202737844611987802059");
  EXPECT_EQ(Acot()(Rational(1, 10))->toString(), "1.471127674303734591852875571761730852");

  EXPECT_ANY_THROW(Acot()(Variable("a")));

  std::unique_ptr<Function> f = std::make_unique<Acot>();
  EXPECT_EQ((*f)(Integer(10))->toString(), "0.09966865249116202737844611987802059");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}
