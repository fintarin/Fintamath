#include "gtest/gtest.h"

#include "fintamath/functions/logarithms/Ln.hpp"

#include "fintamath/functions/Functions.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"
#include "fintamath/numbers/Real.hpp"

using namespace fintamath;

TEST(LnTests, toStringTest) {
  EXPECT_EQ(Ln().toString(), "ln");
}

TEST(LnTests, getFunctionTypeTest) {
  EXPECT_EQ(Ln().getFunctionType(), IFunction::Type::Unary);
}

TEST(LnTests, callTest) {
  EXPECT_EQ(Ln()(Integer(1)).toString(), "0");
  EXPECT_EQ(Ln()(Integer(10)).toString(),
            "2.3025850929940456840179914546843642076011014886287729760333279009675726096773525");
  EXPECT_EQ(Ln()(Integer(5)).toString(),
            "1.6094379124341003746007593332261876395256013542685177219126478914741789877076578");
  EXPECT_EQ(Ln()(Rational(1, 10)).toString(),
            "-2.3025850929940456840179914546843642076011014886287729760333279009675726096773525");
  EXPECT_EQ(Ln()(e()).toString(), "1");

  EXPECT_EQ(Ln()(Variable("a")).toString(), "ln(a)");

  EXPECT_ANY_THROW(Ln()(Integer(-10)));

  std::unique_ptr<IFunction> f = std::make_unique<Ln>();
  EXPECT_EQ((*f)(Integer(10)).toString(),
            "2.3025850929940456840179914546843642076011014886287729760333279009675726096773525");
  EXPECT_ANY_THROW((*f)());
  EXPECT_ANY_THROW((*f)(Integer(1), Integer(1), Integer(1)));
}
