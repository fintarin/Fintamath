#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/IFunction.hpp"

#include "fintamath/functions/arithmetic/Div.hpp"
#include "fintamath/functions/arithmetic/Mul.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
#include "fintamath/functions/trigonometry/Sin.hpp"
#include "fintamath/literals/Variable.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

namespace {

class TestFunction : public IFunctionCRTP<INumber, TestFunction, INumber> {
  FINTAMATH_CLASS_BODY(TestFunction, IFunction)

protected:
  std::unique_ptr<IMathObject> call(const ArgumentRefVector &argVect) const override {
    return {};
  }
};

FINTAMATH_CLASS_IMPLEMENTATION(TestFunction)

[[maybe_unused]] const auto config = [] {
  IFunction::registerType<TestFunction>();
  return 0;
}();

}

TEST(IFunctionTests, parseTest) {
  EXPECT_TRUE(is<TestFunction>(*IFunction::parseFirst("TestFunction")));
}

TEST(IFunctionTests, callTest) {
  std::unique_ptr<IFunction> f = std::make_unique<Div>();
  Integer a = 3;
  Rational b(1, 2);
  Variable c("c");

  EXPECT_EQ((*f)(a, a)->toString(), "1");
  EXPECT_EQ((*f)(b, b)->toString(), "1");
  EXPECT_EQ((*f)(a, b)->toString(), "6");
  EXPECT_EQ((*f)(b, a)->toString(), "1/6");

  EXPECT_EQ((*f)(a, c)->toString(), "3/c");
}

TEST(IFunctionTests, callVectTest) {
  std::unique_ptr<IFunction> f = std::make_unique<Div>();
  Integer a = 3;
  Rational b(1, 2);
  Variable c("c");

  EXPECT_EQ((*f)({a, a})->toString(), "1");
  EXPECT_EQ((*f)({b, b})->toString(), "1");
  EXPECT_EQ((*f)({a, b})->toString(), "6");
  EXPECT_EQ((*f)({b, a})->toString(), "1/6");

  EXPECT_EQ((*f)({a, c})->toString(), "3/c");
}

TEST(IFunctionTests, equalsTest) {
  EXPECT_EQ(Div(), Div());
  EXPECT_NE(Div(), Sub());
  EXPECT_NE(Sub(), Div());
  EXPECT_NE(Div(), UnaryPlus());
  EXPECT_NE(UnaryPlus(), Div());
  EXPECT_NE(Div(), Sin());
  EXPECT_NE(Sin(), Div());
}

TEST(IFunctionTests, getArgumentClassesTest) {
  EXPECT_THAT(Div().getArgumentClasses(), testing::ElementsAre(IArithmetic::getClassStatic(), IArithmetic::getClassStatic()));
  EXPECT_THAT(Neg().getArgumentClasses(), testing::ElementsAre(IArithmetic::getClassStatic()));
  EXPECT_THAT(Sin().getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(IFunctionTests, getReturnClassTest) {
  EXPECT_EQ(Div().getReturnClass(), IArithmetic::getClassStatic());
  EXPECT_EQ(Neg().getReturnClass(), IArithmetic::getClassStatic());
  EXPECT_EQ(Sin().getReturnClass(), INumber::getClassStatic());
}

TEST(IFunctionTests, doArgsMatchTest) {
  Integer a = 3;
  Rational b(1, 2);
  Variable c("c");

  {
    EXPECT_TRUE(Div().doArgsMatch({a, b}));
    EXPECT_FALSE(Div().doArgsMatch({c, c}));
    EXPECT_FALSE(Div().doArgsMatch({a, c}));
    EXPECT_FALSE(Div().doArgsMatch({c, a}));

    EXPECT_FALSE(Div().doArgsMatch({}));
    EXPECT_FALSE(Div().doArgsMatch({a}));
    EXPECT_FALSE(Div().doArgsMatch({a, a, a}));
    EXPECT_FALSE(Div().doArgsMatch({a, b, a, b}));
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
  EXPECT_EQ(IFunction::getClassStatic()->getName(), "IFunction");
  EXPECT_EQ(IFunction::getClassStatic()->getParent(), IMathObject::getClassStatic());
}
