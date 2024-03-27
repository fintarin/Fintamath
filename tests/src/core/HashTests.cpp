#include <gtest/gtest.h>

#include "fintamath/core/Hash.hpp"

using namespace fintamath;
using namespace detail;

TEST(HashTests, hashTest) {
  EXPECT_EQ(Hash<int>{}(123), std::hash<int>{}(123));
  EXPECT_EQ(Hash<double>{}(123.123), std::hash<double>{}(123.123));
  EXPECT_EQ(Hash<std::string>{}("abc"), std::hash<std::string>{}("abc"));
}

TEST(HashTests, hashCombineTest) {
  {
    size_t seed1 = 0;
    hashCombine(seed1, std::string("abc"));
    hashCombine(seed1, 123);

    size_t seed2 = 0;
    hashCombine(seed2, std::string("abc"));
    hashCombine(seed2, 123);

    EXPECT_EQ(seed1, seed2);
  }
  {
    size_t seed1 = 0;
    hashCombine(seed1, std::string("abd"));
    hashCombine(seed1, 123);

    size_t seed2 = 0;
    hashCombine(seed2, std::string("abc"));
    hashCombine(seed2, 123);

    EXPECT_NE(seed1, seed2);
  }
  {
    size_t seed1 = 0;
    hashCombine(seed1, std::string("abc"));
    hashCombine(seed1, 123);

    size_t seed2 = 0;
    hashCombine(seed2, std::string("abc"));
    hashCombine(seed2, 124);

    EXPECT_NE(seed1, seed2);
  }
  {
    size_t seed1 = 0;
    hashCombine(seed1, 123);
    hashCombine(seed1, std::string("abc"));

    size_t seed2 = 0;
    hashCombine(seed2, std::string("abc"));
    hashCombine(seed2, 123);

    EXPECT_NE(seed1, seed2);
  }
}

TEST(HashTests, hashTupleTest) {
  {
    std::tuple tuple1 = {123, 1.23, "abc"};
    std::tuple tuple2 = {123, 1.23, "abc"};

    EXPECT_EQ(Hash<decltype(tuple1)>{}(tuple1), Hash<decltype(tuple2)>{}(tuple2));
  }
  {
    std::tuple tuple1 = {124, 1.23, "abc"};
    std::tuple tuple2 = {123, 1.23, "abc"};

    EXPECT_NE(Hash<decltype(tuple1)>{}(tuple1), Hash<decltype(tuple2)>{}(tuple2));
  }
  {
    std::tuple tuple1 = {123, 1.23, "abc"};
    std::tuple tuple2 = {123, 2.23, "abc"};

    EXPECT_NE(Hash<decltype(tuple1)>{}(tuple1), Hash<decltype(tuple2)>{}(tuple2));
  }
  {
    std::tuple tuple1 = {123, 1.23, "abd"};
    std::tuple tuple2 = {123, 1.23, "abc"};

    EXPECT_NE(Hash<decltype(tuple1)>{}(tuple1), Hash<decltype(tuple2)>{}(tuple2));
  }
  {
    std::tuple tuple1 = {123, "abd", 1.23};
    std::tuple tuple2 = {123, 1.23, "abc"};

    EXPECT_NE(Hash<decltype(tuple1)>{}(tuple1), Hash<decltype(tuple2)>{}(tuple2));
  }
  {
    std::tuple tuple1 = {123, 1.23, "abd"};
    std::tuple tuple2 = {1.23, "abc", 123};

    EXPECT_NE(Hash<decltype(tuple1)>{}(tuple1), Hash<decltype(tuple2)>{}(tuple2));
  }
}
