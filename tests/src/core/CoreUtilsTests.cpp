#include <gtest/gtest.h>

#include "fintamath/core/CoreUtils.hpp"

#include "fintamath/literals/constants/E.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/NumberConstants.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

E CONST;
Integer INT;

TEST(CoreUtilsTests, castTest) {
  EXPECT_TRUE(cast<IArithmetic>(INT.clone().get()));
  EXPECT_FALSE(cast<IArithmetic>(E().clone().get()));

  EXPECT_TRUE(cast<IArithmetic>(const_cast<const IMathObject *>(INT.clone().get())));
  EXPECT_FALSE(cast<IArithmetic>(const_cast<const IMathObject *>(E().clone().get())));

  EXPECT_NO_THROW(cast<IArithmetic>(INT));
  EXPECT_THROW(cast<IArithmetic>(CONST), std::bad_cast);

  EXPECT_NO_THROW(cast<IArithmetic>(Integer(1)));
  EXPECT_THROW(cast<IArithmetic>(E()), std::bad_cast);

  EXPECT_TRUE(cast<IArithmetic>(INT.clone()));
  EXPECT_FALSE(cast<IArithmetic>(E().clone()));

  EXPECT_TRUE(cast<IArithmetic>(shared_ptr<IMathObject>(INT.clone())));
  EXPECT_FALSE(cast<IArithmetic>(shared_ptr<IMathObject>(E().clone())));

  EXPECT_TRUE(cast<IArithmetic>(std::const_pointer_cast<const IMathObject>(shared_ptr<IMathObject>(INT.clone()))));
  EXPECT_FALSE(cast<IArithmetic>(std::const_pointer_cast<const IMathObject>(shared_ptr<IMathObject>(E().clone()))));
}

TEST(CoreUtilsTests, convertTest) {
  EXPECT_TRUE(is<Rational>(convert(Rational(), Integer())));
  EXPECT_FALSE(convert(Integer(), Rational()));

  EXPECT_TRUE(is<Rational>(convert<Rational>(Integer())));
  EXPECT_THROW(convert<Integer>(Rational()), std::bad_cast);
}

TEST(CoreUtilsTests, isTest) {
  EXPECT_TRUE(is<IArithmetic>(INT.clone().get()));
  EXPECT_FALSE(is<IArithmetic>(E().clone().get()));

  EXPECT_TRUE(is<IArithmetic>(INT));
  EXPECT_FALSE(is<IArithmetic>(CONST));

  EXPECT_TRUE(is<IArithmetic>(INT.clone()));
  EXPECT_FALSE(is<IArithmetic>(E().clone()));

  EXPECT_TRUE(is<IArithmetic>(shared_ptr<IMathObject>(INT.clone())));
  EXPECT_FALSE(is<IArithmetic>(shared_ptr<IMathObject>(E().clone())));

  EXPECT_TRUE(is<IArithmetic>(std::const_pointer_cast<const IMathObject>(shared_ptr<IMathObject>(INT.clone()))));
  EXPECT_FALSE(is<IArithmetic>(std::const_pointer_cast<const IMathObject>(shared_ptr<IMathObject>(E().clone()))));

  EXPECT_TRUE(is<IArithmetic>(std::reference_wrapper<IMathObject>(INT)));
  EXPECT_FALSE(is<IArithmetic>(std::reference_wrapper<IMathObject>(CONST)));

  EXPECT_TRUE(is<IArithmetic>(std::reference_wrapper<const IMathObject>(INT)));
  EXPECT_FALSE(is<IArithmetic>(std::reference_wrapper<const IMathObject>(CONST)));
}