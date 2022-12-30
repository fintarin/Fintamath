#include "gtest/gtest.h"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/functions/powers/Sqrt.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(SqrtTests, toStringTest) {
  EXPECT_EQ(Sqrt().toString(), "sqrt");
}

TEST(SqrtTests, getFunctionTypeTest) {
  EXPECT_EQ(Sqrt().getFunctionType(), IFunction::Type::Unary);
}

TEST(SqrtTests, callTest) {
  EXPECT_EQ(Sqrt()(Integer(100)).toString(), "10");
  EXPECT_EQ(Sqrt()(Integer(10)).toString(),
            "3.1622776601683793319988935444327185337195551393252168268575048527925944386392382");
  EXPECT_EQ(Sqrt()(Integer(10)).toString(),
            "3.1622776601683793319988935444327185337195551393252168268575048527925944386392382");
  EXPECT_EQ(Sqrt()(Rational(1, 10)).toString(),
            "0.31622776601683793319988935444327185337195551393252168268575048527925944386392382");

  EXPECT_EQ(Sqrt()(Variable("a")).toString(), "sqrt(a)");

  EXPECT_THROW(Sqrt()(Integer(-10)), UndefinedFunctionException);

  std::unique_ptr<IFunction> f = std::make_unique<Sqrt>();
  EXPECT_EQ((*f)(Integer(10)).toString(),
            "3.1622776601683793319988935444327185337195551393252168268575048527925944386392382");
  EXPECT_THROW((*f)(), InvalidInputFunctionException);
  EXPECT_THROW((*f)(Integer(1), Integer(1), Integer(1)), InvalidInputFunctionException);
}
