#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "fintamath/functions/IFunction.hpp"

#include "fintamath/functions/arithmetic/Add.hpp"
#include "fintamath/functions/arithmetic/Neg.hpp"
#include "fintamath/functions/arithmetic/Sub.hpp"
#include "fintamath/functions/arithmetic/UnaryPlus.hpp"
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
  std::unique_ptr<IFunction> f = std::make_unique<Add>();
  Integer a = 3;
  Rational b(1, 2);
  Variable c("c");

  EXPECT_EQ((*f)(a, a)->toString(), "6");
  EXPECT_EQ((*f)(b, b)->toString(), "1");
  EXPECT_EQ((*f)(a, b)->toString(), "7/2");
  EXPECT_EQ((*f)(b, a)->toString(), "7/2");

  EXPECT_EQ((*f)(a, c)->toString(), "c + 3");

  EXPECT_THROW((*f)(), InvalidInputFunctionException);
  EXPECT_THROW((*f)(a), InvalidInputFunctionException);
  EXPECT_THROW((*f)(a, a, a), InvalidInputFunctionException);
  EXPECT_THROW((*f)(a, a, a, a, a, a, a), InvalidInputFunctionException);
}

TEST(IFunctionTests, callVectTest) {
  std::unique_ptr<IFunction> f = std::make_unique<Add>();
  Integer a = 3;
  Rational b(1, 2);
  Variable c("c");

  EXPECT_EQ((*f)({a, a})->toString(), "6");
  EXPECT_EQ((*f)({b, b})->toString(), "1");
  EXPECT_EQ((*f)({a, b})->toString(), "7/2");
  EXPECT_EQ((*f)({b, a})->toString(), "7/2");

  EXPECT_EQ((*f)({a, c})->toString(), "c + 3");

  EXPECT_THROW((*f)({}), InvalidInputFunctionException);
  EXPECT_THROW((*f)({a}), InvalidInputFunctionException);
  EXPECT_THROW((*f)({a, a, a}), InvalidInputFunctionException);
  EXPECT_THROW((*f)({a, a, a, a, a, a, a}), InvalidInputFunctionException);
}

TEST(IFunctionTests, equalsTest) {
  EXPECT_EQ(Add(), Add());
  EXPECT_NE(Add(), Sub());
  EXPECT_NE(Sub(), Add());
  EXPECT_NE(Add(), UnaryPlus());
  EXPECT_NE(UnaryPlus(), Add());
  EXPECT_NE(Add(), Sin());
  EXPECT_NE(Sin(), Add());
}

TEST(IFunctionTests, getArgumentClassesTest) {
  EXPECT_THAT(Add().getArgumentClasses(), testing::ElementsAre(IArithmetic::getClassStatic(), IArithmetic::getClassStatic()));
  EXPECT_THAT(Neg().getArgumentClasses(), testing::ElementsAre(IArithmetic::getClassStatic()));
  EXPECT_THAT(Sin().getArgumentClasses(), testing::ElementsAre(INumber::getClassStatic()));
}

TEST(IFunctionTests, getReturnClassTest) {
  EXPECT_EQ(Add().getReturnClass(), IArithmetic::getClassStatic());
  EXPECT_EQ(Neg().getReturnClass(), IArithmetic::getClassStatic());
  EXPECT_EQ(Sin().getReturnClass(), INumber::getClassStatic());
}

TEST(IFunctionTests, doArgsMatchTest) {
  Integer a = 3;
  Rational b(1, 2);
  Variable c("c");

  EXPECT_TRUE(Add().doArgsMatch({a, b}));
  EXPECT_FALSE(Add().doArgsMatch({c, c}));
  EXPECT_FALSE(Add().doArgsMatch({a, c}));
  EXPECT_FALSE(Add().doArgsMatch({c, a}));
  EXPECT_FALSE(Add().doArgsMatch({}));
  EXPECT_FALSE(Add().doArgsMatch({a}));
  EXPECT_FALSE(Add().doArgsMatch({a, a, a}));
  EXPECT_FALSE(Add().doArgsMatch({a, b, a, b}));
}

TEST(IFunctionTests, getClassTest) {
  EXPECT_EQ(IFunction::getClassStatic(), MathObjectClass("IFunction"));
  EXPECT_EQ(IFunction::getClassStatic().getParent(), IMathObject::getClassStatic());
}
