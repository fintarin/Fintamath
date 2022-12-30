#include "gtest/gtest.h"

#include "fintamath/functions/powers/Exp.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(ExpTests, toStringTest) {
  EXPECT_EQ(Exp().toString(), "exp");
}

TEST(ExpTests, getFunctionTypeTest) {
  EXPECT_EQ(Exp().getFunctionType(), IFunction::Type::Unary);
}

TEST(ExpTests, callTest) {
  EXPECT_EQ(Exp()(Integer(3)).toString(),
            "20.085536923187667740928529654581717896987907838554150144378934229698845878091974");
  EXPECT_EQ(Exp()(Integer(3)).toString(),
            "20.085536923187667740928529654581717896987907838554150144378934229698845878091974");
  EXPECT_EQ(Exp()(Integer(-3)).toString(),
            "0.04978706836786394297934241565006177663169959218842321556762772760606066773019955");
  EXPECT_EQ(Exp()(Rational(1, 3)).toString(),
            "1.3956124250860895286281253196025868375979065151994069826175167060317390156459518");

  EXPECT_EQ(Exp()(Variable("a")).toString(), "exp(a)");

  std::unique_ptr<IFunction> f = std::make_unique<Exp>();
  EXPECT_EQ((*f)(Integer(3)).toString(),
            "20.085536923187667740928529654581717896987907838554150144378934229698845878091974");
  EXPECT_THROW((*f)(), InvalidInputFunctionException);
  EXPECT_THROW((*f)(Integer(1), Integer(1)), InvalidInputFunctionException);
}
