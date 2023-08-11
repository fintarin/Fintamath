#include <gtest/gtest.h>

#include "fintamath/core/CoreUtils.hpp"

#include "fintamath/literals/constants/E.hpp"
#include "fintamath/numbers/Integer.hpp"
#include "fintamath/numbers/Rational.hpp"

using namespace fintamath;

E CONST;
Integer INT;

TEST(CoreUtilsTests, isTest) {
  EXPECT_TRUE(is<IArithmetic>(INT));
  EXPECT_FALSE(is<IArithmetic>(CONST));

  EXPECT_TRUE(is<IArithmetic>(INT.clone().get()));
  EXPECT_FALSE(is<IArithmetic>(E().clone().get()));
  EXPECT_FALSE(is<IArithmetic>(std::unique_ptr<IArithmetic>().get()));

  EXPECT_TRUE(is<IArithmetic>(INT.clone()));
  EXPECT_FALSE(is<IArithmetic>(E().clone()));

  EXPECT_TRUE(is<IArithmetic>(std::shared_ptr<IMathObject>(INT.clone())));
  EXPECT_FALSE(is<IArithmetic>(std::shared_ptr<IMathObject>(E().clone())));

  EXPECT_TRUE(is<IArithmetic>(std::const_pointer_cast<const IMathObject>(std::shared_ptr<IMathObject>(INT.clone()))));
  EXPECT_FALSE(is<IArithmetic>(std::const_pointer_cast<const IMathObject>(std::shared_ptr<IMathObject>(E().clone()))));

  EXPECT_TRUE(is<IArithmetic>(std::reference_wrapper<IMathObject>(INT)));
  EXPECT_FALSE(is<IArithmetic>(std::reference_wrapper<IMathObject>(CONST)));

  EXPECT_TRUE(is<IArithmetic>(std::reference_wrapper<const IMathObject>(INT)));
  EXPECT_FALSE(is<IArithmetic>(std::reference_wrapper<const IMathObject>(CONST)));
}

TEST(CoreUtilsTests, castTest) {
  EXPECT_NO_THROW(cast<IArithmetic>(INT));
  EXPECT_THROW(cast<IArithmetic>(cast<IMathObject>(CONST)), std::bad_cast);

  EXPECT_NO_THROW(cast<IArithmetic>(Integer(1)));
  EXPECT_THROW(cast<IArithmetic>(cast<IMathObject>(E())), std::bad_cast);

  EXPECT_TRUE(cast<IArithmetic>(INT.clone().get()));
  EXPECT_FALSE(cast<IArithmetic>(E().clone().get()));

  EXPECT_TRUE(cast<IArithmetic>(const_cast<const IMathObject *>(INT.clone().get())));
  EXPECT_FALSE(cast<IArithmetic>(const_cast<const IMathObject *>(E().clone().get())));

  EXPECT_TRUE(cast<IArithmetic>(INT.clone()));
  EXPECT_FALSE(cast<IArithmetic>(E().clone()));

  EXPECT_TRUE(cast<IArithmetic>(std::shared_ptr<IMathObject>(INT.clone())));
  EXPECT_FALSE(cast<IArithmetic>(std::shared_ptr<IMathObject>(E().clone())));

  EXPECT_TRUE(cast<IArithmetic>(std::const_pointer_cast<const IMathObject>(std::shared_ptr<IMathObject>(INT.clone()))));
  EXPECT_FALSE(
      cast<IArithmetic>(std::const_pointer_cast<const IMathObject>(std::shared_ptr<IMathObject>(E().clone()))));
}
