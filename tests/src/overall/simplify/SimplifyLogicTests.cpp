#include <gtest/gtest.h>

#include "fintamath/expressions/Expression.hpp"

using namespace fintamath;

TEST(SimplifyLogicTests, simplifyTest) {
  EXPECT_EQ(Expression("~True").toString(),
            "False");
  EXPECT_EQ(Expression("~False").toString(),
            "True");
  EXPECT_EQ(Expression("True&False").toString(),
            "False");
  EXPECT_EQ(Expression("~~~True&~~~~False|~~~~~~False|False").toString(),
            "False");
  EXPECT_EQ(Expression("True|False").toString(),
            "True");
  EXPECT_EQ(Expression("True&False|True&False").toString(),
            "False");
  EXPECT_EQ(Expression("False&True|True&False").toString(),
            "False");
  EXPECT_EQ(Expression("False&True|True&True|False").toString(),
            "True");
  EXPECT_EQ(Expression("False|~False&True").toString(),
            "True");
  EXPECT_EQ(Expression("(False|False&~True)|(True&~(False|True))").toString(),
            "False");
  EXPECT_EQ(Expression("True !<-> True").toString(),
            "False");
  EXPECT_EQ(Expression("(False -> False & ~True) !<-> (True <-> ~(False|True))").toString(),
            "True");
  EXPECT_EQ(Expression("False <-> ~False & True").toString(),
            "False");
  EXPECT_EQ(Expression("False <-> True -> False").toString(),
            "True");

  EXPECT_EQ(Expression("~(1=1)").toString(),
            "False");
  EXPECT_EQ(Expression("~(1=2)").toString(),
            "True");
  EXPECT_EQ(Expression("(1=1)&(1=2)").toString(),
            "False");
  EXPECT_EQ(Expression("(1=1)|(1=2)").toString(),
            "True");
  EXPECT_EQ(Expression("(1=2)|~(1=2)&(1=1)").toString(),
            "True");
  EXPECT_EQ(Expression("((1=2)|(1=2)&~(1=1))|((1=1)&~((1=2)|(1=1)))").toString(),
            "False");
  EXPECT_EQ(Expression("((1=2) -> (1=2) & ~(1=1)) !<-> ((1=1) <-> ~((1=2) | (1=1)))").toString(),
            "True");
  EXPECT_EQ(Expression("False|1=1").toString(),
            "True");
  EXPECT_EQ(Expression("1=1|False").toString(),
            "True");
  EXPECT_EQ(Expression("a>b|a").toString(),
            "a - b > 0 | a");
  EXPECT_EQ(Expression("x = -7 | x = 7 | x = -7 | x = 7").toString(),
            "x - 7 = 0 | x + 7 = 0");
  EXPECT_EQ(Expression("x = -7 & x = 7 & x = -7 & x = 7").toString(),
            "x - 7 = 0 & x + 7 = 0");

  EXPECT_EQ(Expression("~(x = 1)").toString(),
            "x - 1 != 0");
  EXPECT_EQ(Expression("~(x != 1)").toString(),
            "x - 1 = 0");
  EXPECT_EQ(Expression("~(x > 1)").toString(),
            "x - 1 <= 0");
  EXPECT_EQ(Expression("~(x < 1)").toString(),
            "x - 1 >= 0");
  EXPECT_EQ(Expression("~(x >= 1)").toString(),
            "x - 1 < 0");
  EXPECT_EQ(Expression("~(x <= 1)").toString(),
            "x - 1 > 0");
  EXPECT_EQ(Expression("~(x <= 1 | y >= 1)").toString(),
            "y - 1 < 0 & x - 1 > 0");

  EXPECT_EQ(Expression("~a").toString(),
            "~a");
  EXPECT_EQ(Expression("~~a").toString(),
            "a");
  EXPECT_EQ(Expression("~~~a").toString(),
            "~a");
  EXPECT_EQ(Expression("~~~~~~~~~~a").toString(),
            "a");
  EXPECT_EQ(Expression("~~~~~~~~~~~a").toString(),
            "~a");

  EXPECT_EQ(Expression("a & b").toString(),
            "a & b");
  EXPECT_EQ(Expression("a | b").toString(),
            "a | b");
  EXPECT_EQ(Expression("a -> b").toString(),
            "~a | b");
  EXPECT_EQ(Expression("a <-> b").toString(),
            "(~a & ~b) | (a & b)");
  EXPECT_EQ(Expression("a !<-> b").toString(),
            "(~a & b) | (a & ~b)");

  EXPECT_EQ(Expression("a & a").toString(),
            "a");
  EXPECT_EQ(Expression("a | a").toString(),
            "a");
  EXPECT_EQ(Expression("a -> a").toString(),
            "True");
  EXPECT_EQ(Expression("a <-> a").toString(),
            "True");
  EXPECT_EQ(Expression("a !<-> a").toString(),
            "False");

  EXPECT_EQ(Expression("a & ~a").toString(),
            "False");
  EXPECT_EQ(Expression("a | ~a").toString(),
            "True");
  EXPECT_EQ(Expression("a -> ~a").toString(),
            "~a");
  EXPECT_EQ(Expression("a <-> ~a").toString(),
            "False");
  EXPECT_EQ(Expression("a !<-> ~a").toString(),
            "True");

  EXPECT_EQ(Expression("~a & a").toString(),
            "False");
  EXPECT_EQ(Expression("~a | a").toString(),
            "True");
  EXPECT_EQ(Expression("~a -> a").toString(),
            "a");
  EXPECT_EQ(Expression("~a <-> a").toString(),
            "False");
  EXPECT_EQ(Expression("~a !<-> a").toString(),
            "True");

  EXPECT_EQ(Expression("~a & ~a").toString(),
            "~a");
  EXPECT_EQ(Expression("~a | ~a").toString(),
            "~a");
  EXPECT_EQ(Expression("~a -> ~a").toString(),
            "True");
  EXPECT_EQ(Expression("~a <-> ~a").toString(),
            "True");
  EXPECT_EQ(Expression("~a !<-> ~a").toString(),
            "False");

  EXPECT_EQ(Expression("a & False").toString(),
            "False");
  EXPECT_EQ(Expression("a | False").toString(),
            "a");
  EXPECT_EQ(Expression("a -> False").toString(),
            "~a");
  EXPECT_EQ(Expression("a <-> False").toString(),
            "~a");
  EXPECT_EQ(Expression("a !<-> False").toString(),
            "a");

  EXPECT_EQ(Expression("a & True").toString(),
            "a");
  EXPECT_EQ(Expression("a | True").toString(),
            "True");
  EXPECT_EQ(Expression("a -> True").toString(),
            "True");
  EXPECT_EQ(Expression("a <-> True").toString(),
            "a");
  EXPECT_EQ(Expression("a !<-> True").toString(),
            "~a");

  EXPECT_EQ(Expression("a<->(True)<->(False)").toString(),
            "~a");
  EXPECT_EQ(Expression("a<->(True)!<->(False)").toString(),
            "a");
  EXPECT_EQ(Expression("True & b & False & c").toString(),
            "False");
  EXPECT_EQ(Expression("True | b | False | c").toString(),
            "True");
  EXPECT_EQ(Expression("True | a | b | False").toString(),
            "True");
  EXPECT_EQ(Expression("a<->a<->a<->a<->a<->a").toString(),
            "True");
  EXPECT_EQ(Expression("a<->a<->a<->a<->a<->a<->a").toString(),
            "a");
  EXPECT_EQ(Expression("a&b->b&c").toString(),
            "~a | ~b | (b & c)");
  EXPECT_EQ(Expression("a&b&c").toString(),
            "a & b & c");
  EXPECT_EQ(Expression("a&(b&c)").toString(),
            "a & b & c");
  EXPECT_EQ(Expression("a & ~b & c").toString(),
            "a & ~b & c");
  EXPECT_EQ(Expression("a | (~b & c)").toString(),
            "a | (~b & c)");
  EXPECT_EQ(Expression("(a | ~b) & c").toString(),
            "(a & c) | (~b & c)");
  EXPECT_EQ(Expression("~(a & b)").toString(),
            "~a | ~b");
  EXPECT_EQ(Expression("~(a | b)").toString(),
            "~a & ~b");
  EXPECT_EQ(Expression("~(a & b & c)").toString(),
            "~a | ~b | ~c");
  EXPECT_EQ(Expression("~(a | b | c)").toString(),
            "~a & ~b & ~c");
  EXPECT_EQ(Expression("~(~a & ~a)").toString(),
            "a");
  EXPECT_EQ(Expression("b&c&d | a&c&d | a&b&c").toString(),
            "(a & b & c) | (a & c & d) | (b & c & d)");
  EXPECT_EQ(Expression("a | (a & b)").toString(),
            "a");
  EXPECT_EQ(Expression("(a & b & c) | (a & b)").toString(),
            "a & b");
  EXPECT_EQ(Expression("a & (a | b)").toString(),
            "a");
  EXPECT_EQ(Expression("(a | b | c) & (a | b)").toString(),
            "a | b");
  EXPECT_EQ(Expression("(a & b & c) | (a & c)").toString(),
            "a & c");
  EXPECT_EQ(Expression("(a & ~b) | (a & b)").toString(),
            "a");
  EXPECT_EQ(Expression("(a | b | c) & (a | b)").toString(),
            "a | b");
  EXPECT_EQ(Expression("~(a & b) | ~(~a & c)").toString(),
            "True");
  EXPECT_EQ(Expression("~(a | b) & ~(~a | c)").toString(),
            "False");
  EXPECT_EQ(Expression("(x & ~y & z) | (y & z)").toString(),
            "(x & ~y & z) | (y & z)");
  EXPECT_EQ(Expression("(x | ~y | (x | ~y | z) & (y | z)) & (y | (x & ~y & z) | (y & z))").toString(),
            "(x & ~y & z) | (x & y) | (y & z)");
  EXPECT_EQ(Expression("~a & b | ~c -> a <-> b !<-> c").toString(),
            "(~a & ~b & ~c) | (~a & c) | (a & b & ~c) | (~b & c)");
  EXPECT_EQ(Expression("~~~a & ~~b | ~~~c -> ~~a <-> ~~b !<-> ~~c").toString(),
            "(~a & ~b & ~c) | (~a & c) | (a & b & ~c) | (~b & c)");
  EXPECT_EQ(Expression("((a | b) & (a -> c)) <-> (~a -> b)").toString(),
            "~a | (a & c) | (b & c)");

  EXPECT_EQ(Expression("x=1&a").toString(),
            "a & x - 1 = 0");
  EXPECT_EQ(Expression("True & a = b").toString(),
            "a - b = 0");
}

TEST(SimplifyLogicTests, simplifyLargeTest) {
  EXPECT_EQ(Expression("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~a").toString(),
            "a");

  EXPECT_EQ(Expression("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~a").toString(),
            "~a");

  // TODO: for benchmark
  // EXPECT_EQ(Expression("a<->b<->c<->d<->e<->f").toString(),

  EXPECT_EQ(Expression("a<->b<->c<->d<->e").toString(),
            "(~a & ~b & ~c & ~d & e) | "
            "(~a & ~b & ~c & d & ~e) | "
            "(~a & ~b & c & ~d & ~e) | "
            "(~a & ~b & c & d & e) | "
            "(~a & b & ~c & ~d & ~e) | "
            "(~a & b & ~c & d & e) | "
            "(~a & b & c & ~d & e) | "
            "(~a & b & c & d & ~e) | "
            "(a & ~b & ~c & ~d & ~e) | "
            "(a & ~b & ~c & d & e) | "
            "(a & ~b & c & ~d & e) | "
            "(a & ~b & c & d & ~e) | "
            "(a & b & ~c & ~d & e) | "
            "(a & b & ~c & d & ~e) | "
            "(a & b & c & ~d & ~e) | "
            "(a & b & c & d & e)");

  EXPECT_EQ(Expression("a & b & c & d & e & f & g & h & i & j & k & l & m & n & o & p & q & r & s & t & u & v & w & x & y & z & x_1 & x_2 & x_3 | x_4").toString(),
            "(a & b & c & d & e & f & g & h & i & j & k & l & m & n & o & p & q & r & s & t & u & v & w & x & x_1 & x_2 & x_3 & y & z) | x_4");

  EXPECT_EQ(Expression("a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x | y | z | x_1 | x_2 | x_3 & x_4").toString(),
            "a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x | x_1 | x_2 | (x_3 & x_4) | y | z");
}
