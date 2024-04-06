#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/IFunction.hpp"

#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/logarithms/Log.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

namespace {

class TestFunction final : public IFunctionCRTP<INumber, TestFunction, INumber> {
  FINTAMATH_CLASS_BODY(TestFunction)

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return {};
  }
};

[[maybe_unused]] const auto config = [] {
  IFunction::registerType<TestFunction>();
  return 0;
}();

}

TEST(IFunctionTests, parseTest) {
  EXPECT_TRUE(is<TestFunction>(*IFunction::parseFirst("TestFunction")));
}

TEST(IFunctionTests, callTest) {
  std::unique_ptr<IFunction> f = std::make_unique<Log>();
  Integer a = 3;
  Rational b(1, 2);
  Variable c("c");

  EXPECT_EQ((*f)(a, a)->toString(), "1");
  EXPECT_EQ((*f)(b, b)->toString(), "1");
  EXPECT_EQ((*f)(a, b)->toString(), "-0.6309297535714574371");
  EXPECT_EQ((*f)(b, a)->toString(), "-1.5849625007211561815");

  EXPECT_EQ((*f)(a, c)->toString(), "log(3, c)");

  EXPECT_THROW((*f)(), InvalidInputFunctionException);
  EXPECT_THROW((*f)(a), InvalidInputFunctionException);
  EXPECT_THROW((*f)(a, a, a), InvalidInputFunctionException);
  EXPECT_THROW((*f)(a, a, a, a, a, a, a), InvalidInputFunctionException);
}

TEST(IFunctionTests, callVectTest) {
  std::unique_ptr<IFunction> f = std::make_unique<Log>();
  Integer a = 3;
  Rational b(1, 2);
  Variable c("c");

  EXPECT_EQ((*f)({a, a})->toString(), "1");
  EXPECT_EQ((*f)({b, b})->toString(), "1");
  EXPECT_EQ((*f)({a, b})->toString(), "-0.6309297535714574371");
  EXPECT_EQ((*f)({b, a})->toString(), "-1.5849625007211561815");

  EXPECT_EQ((*f)({a, c})->toString(), "log(3, c)");

  EXPECT_THROW((*f)({}), InvalidInputFunctionException);
  EXPECT_THROW((*f)({a}), InvalidInputFunctionException);
  EXPECT_THROW((*f)({a, a, a}), InvalidInputFunctionException);
  EXPECT_THROW((*f)({a, a, a, a, a, a, a}), InvalidInputFunctionException);
}

TEST(IFunctionTests, equalsTest) {
  EXPECT_EQ(Log(), Log());
  EXPECT_NE(Log(), Sub());
  EXPECT_NE(Sub(), Log());
  EXPECT_NE(Log(), UnaryPlus());
  EXPECT_NE(UnaryPlus(), Log());
  EXPECT_NE(Log(), Sin());
  EXPECT_NE(Sin(), Log());
}

TEST(IFunctionTests, getArgumentClassesTest) {
  EXPECT_THAT(Log().getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic(), INumber::getClassStatic()));
  EXPECT_THAT(Neg().getArgumentClasses(), testing::ElementsAre(IArithmetic::getClassStatic()));
  EXPECT_THAT(Sin().getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(IFunctionTests, getReturnClassTest) {
  EXPECT_EQ(Log().getReturnClass(), INumber::getClassStatic());
  EXPECT_EQ(Neg().getReturnClass(), IArithmetic::getClassStatic());
  EXPECT_EQ(Sin().getReturnClass(), INumber::getClassStatic());
}

TEST(IFunctionTests, doArgsMatchTest) {
  Integer a = 3;
  Rational b(1, 2);
  Variable c("c");

  {
    EXPECT_TRUE(Log().doArgsMatch({a, b}));
    EXPECT_FALSE(Log().doArgsMatch({c, c}));
    EXPECT_FALSE(Log().doArgsMatch({a, c}));
    EXPECT_FALSE(Log().doArgsMatch({c, a}));

    EXPECT_FALSE(Log().doArgsMatch({}));
    EXPECT_FALSE(Log().doArgsMatch({a}));
    EXPECT_FALSE(Log().doArgsMatch({a, a, a}));
    EXPECT_FALSE(Log().doArgsMatch({a, b, a, b}));
  }
  {
    EXPECT_TRUE(Mul().doArgsMatch({a, b, a}));
    EXPECT_FALSE(Mul().doArgsMatch({a, c, c}));
    EXPECT_FALSE(Mul().doArgsMatch({c, b, b}));
    EXPECT_FALSE(Mul().doArgsMatch({b, b, c, a}));

    EXPECT_FALSE(Mul().doArgsMatch({}));
    EXPECT_TRUE(Mul().doArgsMatch({a}));
    EXPECT_TRUE(Mul().doArgsMatch({a, a}));
    EXPECT_TRUE(Mul().doArgsMatch({a, a, a}));
    EXPECT_TRUE(Mul().doArgsMatch({a, b, a, b}));
  }
}

TEST(IFunctionTests, getClassTest) {
  EXPECT_EQ(IFunction::getClassStatic(), MathObjectClass("IFunction"));
  EXPECT_EQ(IFunction::getClassStatic().getParent(), IMathObject::getClassStatic());
}
