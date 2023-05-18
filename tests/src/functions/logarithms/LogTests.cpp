#include "gtest/gtest.h"

#include "fintamath/functions/logarithms/Log.hpp"

#include "fintamath/exceptions/UndefinedException.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

const Log f;

TEST(LogTests, toStringTest) {
  EXPECT_EQ(f.toString(), "log");
}

TEST(LogTests, getFunctionTypeTest) {
  EXPECT_EQ(f.getFunctionType(), IFunction::Type::Binary);
}

TEST(LogTests, callTest) {
  EXPECT_EQ(f(Integer(10), Integer(1))->toString(), "0");
  EXPECT_EQ(f(Integer(2), Integer(10))->toString(),
            "3.3219280948873623478703194294893901758648313930245806120547563958159347766086252");
  EXPECT_EQ(f(Integer(2), Integer(3))->toString(),
            "1.5849625007211561814537389439478165087598144076924810604557526545410982277943586");
  EXPECT_EQ(f(Rational(1, 10), Integer(10))->toString(), "-1");

  EXPECT_EQ(f(Variable("a"), Variable("b"))->toString(), "log(a, b)");

  EXPECT_THROW(f(Integer(-10), Integer(10)), UndefinedFunctionException);
  EXPECT_THROW(f(Integer(1), Integer(10)), UndefinedFunctionException);

  EXPECT_THROW(f(), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(10)), InvalidInputFunctionException);
  EXPECT_THROW(f(Integer(10), Integer(10), Integer(10)), InvalidInputFunctionException);
}

TEST(LogTests, doArgsMatchTest) {
  Integer a;

  EXPECT_FALSE(f.doArgsMatch({}));
  EXPECT_FALSE(f.doArgsMatch({a}));
  EXPECT_TRUE(f.doArgsMatch({a, a}));
  EXPECT_FALSE(f.doArgsMatch({a, a, a}));
}

TEST(LogTests, equalsTest) {
  EXPECT_EQ(f, f);
  EXPECT_EQ(f, Log());
  EXPECT_EQ(Log(), f);
  EXPECT_EQ(f, cast<IMathObject>(Log()));
  EXPECT_EQ(cast<IMathObject>(Log()), f);
  EXPECT_NE(f, Sub());
  EXPECT_NE(Sub(), f);
  EXPECT_NE(f, UnaryPlus());
  EXPECT_NE(UnaryPlus(), f);
}

TEST(LogTests, getTypeIdTest) {
  EXPECT_EQ(Log::getTypeIdStatic(), MathObjectTypeId(MathObjectType::Log));
  EXPECT_EQ(Log().getTypeId(), MathObjectTypeId(MathObjectType::Log));
}
