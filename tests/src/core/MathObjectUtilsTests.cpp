#include <gtest/gtest.h>

#include "fintamath/core/MathObjectUtils.hpp"

#include "fintamath/literals/constants/E.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

E c;
Integer i;

TEST(MathObjectUtilsTests, isTest) {
  EXPECT_TRUE(is<IArithmetic>(i));
  EXPECT_FALSE(is<IArithmetic>(c));

  EXPECT_TRUE(is<IArithmetic>(i.clone().get()));
  EXPECT_FALSE(is<IArithmetic>(E().clone().get()));
  EXPECT_FALSE(is<IArithmetic>(std::unique_ptr<IArithmetic>().get()));

  EXPECT_TRUE(is<IArithmetic>(i.clone()));
  EXPECT_FALSE(is<IArithmetic>(E().clone()));

  EXPECT_TRUE(is<IArithmetic>(std::shared_ptr(i.clone())));
  EXPECT_FALSE(is<IArithmetic>(std::shared_ptr(E().clone())));

  EXPECT_TRUE(is<IArithmetic>(std::const_pointer_cast<const IMathObject>(std::shared_ptr(i.clone()))));
  EXPECT_FALSE(is<IArithmetic>(std::const_pointer_cast<const IMathObject>(std::shared_ptr(E().clone()))));

  EXPECT_TRUE(is<IArithmetic>(std::reference_wrapper<IMathObject>(i)));
  EXPECT_FALSE(is<IArithmetic>(std::reference_wrapper<IMathObject>(c)));

  EXPECT_TRUE(is<IArithmetic>(std::reference_wrapper<const IMathObject>(i)));
  EXPECT_FALSE(is<IArithmetic>(std::reference_wrapper<const IMathObject>(c)));
}

TEST(MathObjectUtilsTests, castTest) {
  EXPECT_NO_THROW(cast<IArithmetic>(i));
  EXPECT_DEBUG_DEATH(cast<IArithmetic>(cast<IMathObject>(c)), "");

  EXPECT_NO_THROW(cast<IArithmetic>(Integer(1)));
  EXPECT_DEBUG_DEATH(cast<IArithmetic>(cast<IMathObject>(E())), "");

  EXPECT_TRUE(cast<IArithmetic>(i.clone().get()));
  EXPECT_FALSE(cast<IArithmetic>(E().clone().get()));

  EXPECT_TRUE(cast<IArithmetic>(const_cast<const IMathObject *>(i.clone().get())));
  EXPECT_FALSE(cast<IArithmetic>(const_cast<const IMathObject *>(E().clone().get())));

  EXPECT_TRUE(cast<IArithmetic>(i.clone()));
  EXPECT_FALSE(cast<IArithmetic>(E().clone()));

  EXPECT_TRUE(cast<IArithmetic>(std::shared_ptr(i.clone())));
  EXPECT_FALSE(cast<IArithmetic>(std::shared_ptr(E().clone())));

  EXPECT_TRUE(cast<IArithmetic>(std::const_pointer_cast<const IMathObject>(std::shared_ptr(i.clone()))));
  EXPECT_FALSE(cast<IArithmetic>(std::const_pointer_cast<const IMathObject>(std::shared_ptr(E().clone()))));
}

TEST(MathObjectUtilsTests, compareByToStringTest) {
  // TODO: implement
}
