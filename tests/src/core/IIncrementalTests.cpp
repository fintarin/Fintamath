#include <gtest/gtest.h>

#include "fintamath/core/IIncremental.hpp"

#include "fintamath/numbers/Integer.hpp"

using namespace fintamath;

TEST(IIncrementalTests, incTest) {
  std::unique_ptr<IIncremental> m1 = std::make_unique<Integer>(1);
  EXPECT_EQ((++*m1).toString(), "2");
  EXPECT_EQ(((*m1)++)->toString(), "2");
  EXPECT_EQ(m1->toString(), "3");

  EXPECT_EQ((++Integer(1)).toString(), "2");
  EXPECT_EQ((Integer(1)++).toString(), "1");
}

TEST(IIncrementalTests, decTest) {
  std::unique_ptr<IIncremental> m1 = std::make_unique<Integer>(1);
  EXPECT_EQ((--*m1).toString(), "0");
  EXPECT_EQ(((*m1)--)->toString(), "0");
  EXPECT_EQ(m1->toString(), "-1");

  EXPECT_EQ((--Integer(1)).toString(), "0");
  EXPECT_EQ((Integer(1)--).toString(), "1");
}
