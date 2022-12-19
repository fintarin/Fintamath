#include "gtest/gtest.h"

#include "fintamath/exceptions/UndefinedFunctionException.hpp"
#include "fintamath/functions/logarithms/Lb.hpp"

#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

TEST(LbTests, toStringTest) {
  EXPECT_EQ(Lb().toString(), "lb");
}

TEST(LbTests, getFunctionTypeTest) {
  EXPECT_EQ(Lb().getFunctionType(), IFunction::Type::Unary);
}

TEST(LbTests, callTest) {
  EXPECT_EQ(Lb()(Integer(2)).toString(), "1");
  EXPECT_EQ(Lb()(Integer(10)).toString(),
            "3.3219280948873623478703194294893901758648313930245806120547563958159347766086252");
  EXPECT_EQ(Lb()(Integer(3)).toString(),
            "1.5849625007211561814537389439478165087598144076924810604557526545410982277943586");
  EXPECT_EQ(Lb()(Rational(1, 16)).toString(), "-4");

  EXPECT_EQ(Lb()(Variable("a")).toString(), "lb(a)");

  EXPECT_THROW(Lb()(Integer(-10)), UndefinedFunctionException);

  std::unique_ptr<IFunction> f = std::make_unique<Lb>();
  EXPECT_EQ((*f)(Integer(10)).toString(),
            "3.3219280948873623478703194294893901758648313930245806120547563958159347766086252");
  EXPECT_THROW((*f)(), FunctionCallException);
  EXPECT_THROW((*f)(Integer(10), Integer(10), Integer(10)), FunctionCallException);
}

TEST(LbTests, getClassNameTest) {
  EXPECT_EQ(Lb().getClassName(), "Lb");
}
