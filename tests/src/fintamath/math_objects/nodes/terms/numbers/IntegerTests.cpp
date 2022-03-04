#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "fintamath/math_objects/nodes/terms/numbers/Integer.hpp"

using namespace fintamath;

static nlohmann::json &getTestJson();

TEST(IntegerTests, stringConstructorTest) {
  EXPECT_EQ(Integer("10").toString(), "10");
  EXPECT_EQ(Integer("2432432423432432454745").toString(), "2432432423432432454745");
  EXPECT_EQ(Integer("-10"), -10);
  EXPECT_EQ(Integer("01"), 1);

  EXPECT_THROW(Integer("--10"), std::invalid_argument);
  EXPECT_THROW(Integer("test"), std::invalid_argument);
  EXPECT_THROW(Integer(""), std::invalid_argument);
  EXPECT_THROW(Integer("+"), std::invalid_argument);
}

TEST(IntegerTests, intConstructorTest) {
  EXPECT_EQ(Integer(10), 10);

  Integer a = 10;
  EXPECT_EQ(a, 10);
}

TEST(IntegerTests, intAssignmentOperatorTest) {
  Integer a;
  EXPECT_EQ(a = 10, 10);
}

TEST(IntegerTests, plusAssignmentOperatorTest) {
  EXPECT_EQ(Integer(5) += Integer(10), 15);
  EXPECT_EQ(Integer(-5) += Integer(10), 5);
  EXPECT_EQ(Integer(-10) += Integer(10), 0);
  EXPECT_EQ(Integer("-72838928574893245678976545678765457483992") + Integer("-387827392020390239201210"),
            Integer("-72838928574893246066803937699155696685202"));
}

TEST(IntegerTests, intPlusAssignmentOperatorTest) {
  EXPECT_EQ(Integer(5) += 10, 15);
}

TEST(IntegerTests, plusOperatorTest) {
  EXPECT_EQ(Integer(-100) + Integer("10"), -90);
  EXPECT_EQ(Integer("65784932384756574839238475674839") + Integer("-387827392020390239201210"),
            Integer("65784931996929182818848236473629"));
}

TEST(IntegerTests, intPlusOperatorTest) {
  EXPECT_EQ(Integer(5) + 10, 15);
}

TEST(IntegerTests, friendIntPlusOperatorTest) {
  EXPECT_EQ(5 + Integer(10), 15);
}

TEST(IntegerTests, minusAssignmentOperatorTest) {
  EXPECT_EQ(Integer(5) -= Integer(10), -5);
  EXPECT_EQ(Integer(-5) -= Integer(-10105), 10100);
  EXPECT_EQ(Integer("520039026478395743890") -= Integer("-1930275483923745483957483983"),
            Integer("1930276003962771962353227873"));
}

TEST(IntegerTests, intMinusAssignmentOperatorTest) {
  EXPECT_EQ(Integer(5) -= 10, -5);
}

TEST(IntegerTests, minusOperatorTest) {
  EXPECT_EQ(Integer(-100) - Integer("-748"), 648);
  EXPECT_EQ(Integer("65784932384756574839238475674839") - Integer("-387827392020390239201210"),
            Integer("65784932772583966859628714876049"));
}

TEST(IntegerTests, intMinusOperatorTest) {
  EXPECT_EQ(Integer(5) - 10, -5);
}

TEST(IntegerTests, friendIntMinusOperatorTest) {
  EXPECT_EQ(5 - Integer(10), -5);
}

TEST(IntegerTests, multiplyAssignmentOperatorTest) {
  EXPECT_EQ(Integer(5) *= Integer("-12"), -60);
  EXPECT_EQ(Integer(190) *= Integer(100), 19000);

  EXPECT_EQ(Integer(2) *= Integer(2), 4);
  EXPECT_EQ(Integer(2) *= Integer(-2), -4);
  EXPECT_EQ(Integer(-2) *= Integer(2), -4);
  EXPECT_EQ(Integer(-2) *= Integer(-2), 4);

  for (const auto &iter : getTestJson().find("multiply_tests").value()) {
    auto lhs = Integer(iter.find("lhs").value().get<std::string>());
    auto rhs = Integer(iter.find("rhs").value().get<std::string>());
    auto res = Integer(iter.find("res").value().get<std::string>());
    EXPECT_EQ(lhs *= rhs, res);
  }
}

TEST(IntegerTests, intMultiplyAssignmentOperatorTest) {
  EXPECT_EQ(Integer(5) *= 10, 50);
}

TEST(IntegerTests, multiplyOperatorTest) {
  EXPECT_EQ(Integer(100) * Integer(-748), -74800);
  EXPECT_EQ(Integer(63275) * Integer(4), 253100);
  EXPECT_EQ(Integer("-46387457368576823782") * Integer("-4837274673279875647746473847384738478378327647387463746372"),
            Integer("224388872686866615413795053083509315281416419176500823292877913926466185818904"));
}

TEST(IntegerTests, intMultiplyOperatorTest) {
  EXPECT_EQ(Integer(5) * 10, 50);
}

TEST(IntegerTests, friendIntMultiplyOperatorTest) {
  EXPECT_EQ(5 * Integer(10), 50);
}

TEST(IntegerTests, divideAssignmentOperatorTest) {
  EXPECT_EQ(Integer(-25) /= Integer(368273929), 0);
  EXPECT_EQ(Integer(2000) /= Integer(-368273929), 0);
  EXPECT_EQ(Integer(-20) /= Integer(-20), 1);
  EXPECT_EQ(Integer(-29829920) /= Integer(1), -29829920);
  EXPECT_EQ(Integer(150067278) / Integer(100000), 1500);

  EXPECT_EQ(Integer(2) /= Integer(2), 1);
  EXPECT_EQ(Integer(2) /= Integer(-2), -1);
  EXPECT_EQ(Integer(-2) /= Integer(2), -1);
  EXPECT_EQ(Integer(-2) /= Integer(-2), 1);

  for (const auto &iter : getTestJson().find("divide_tests").value()) {
    auto lhs = Integer(iter.find("lhs").value().get<std::string>());
    auto rhs = Integer(iter.find("rhs").value().get<std::string>());
    auto res = Integer(iter.find("res").value().get<std::string>());
    EXPECT_EQ(lhs /= rhs, res);
  }

  EXPECT_THROW(Integer(-25) /= Integer(0), std::domain_error);
}

TEST(IntegerTests, intDivideAssignmentOperatorTest) {
  EXPECT_EQ(Integer(10) /= 5, 2);
}

TEST(IntegerTests, divideOperatorTest) {
  EXPECT_EQ(Integer(-25) / Integer(368273929), 0);
  EXPECT_EQ(Integer("-4837274673279875647746473847384738478378327647387463746372") / Integer("-463874573"),
            Integer("10427979792028556925767245809751978965181020274175"));
}

TEST(IntegerTests, intDivideOperatorTest) {
  EXPECT_EQ(Integer(10) / 5, 2);
}

TEST(IntegerTests, friendIntDivideOperatorTest) {
  EXPECT_EQ(10 / Integer(5), 2);
}

TEST(IntegerTests, moduloAssignmentOperatorTest) {
  EXPECT_EQ(Integer(25) %= Integer(368273929), 25);
  EXPECT_EQ(Integer(-25) %= Integer(3), -1);
  EXPECT_EQ(Integer(2000) %= Integer(-36), Integer(20));

  for (const auto &iter : getTestJson().find("modulo_tests").value()) {
    auto lhs = Integer(iter.find("lhs").value().get<std::string>());
    auto rhs = Integer(iter.find("rhs").value().get<std::string>());
    auto res = Integer(iter.find("res").value().get<std::string>());
    EXPECT_EQ(lhs %= rhs, res);
  }

  EXPECT_THROW(Integer(-25) %= Integer(0), std::domain_error);
}

TEST(IntegerTests, intModuloAssignmentOperatorTest) {
  EXPECT_EQ(Integer(10) %= 4, 2);
}

TEST(IntegerTests, moduloOperatorTest) {
  EXPECT_EQ(Integer(-25) % Integer(3), -1);
  EXPECT_EQ(Integer("54732897657873247528747287294738765738746547387476327946763287467387267328724673874") %
                Integer("47632837528673287446238746237943"),
            Integer("25193809905191080888100466723580"));
}

TEST(IntegerTests, intModuloOperatorTest) {
  EXPECT_EQ(Integer(10) % 4, 2);
}

TEST(IntegerTests, friendIntModuloOperatorTest) {
  EXPECT_EQ(10 % Integer(4), 2);
}

TEST(IntegerTests, preIncrementOperatorTest) {
  Integer a = 5;
  EXPECT_EQ(++a, 6);

  Integer b("4632819374289745632874563287263891364238928");
  EXPECT_EQ(++b, Integer("4632819374289745632874563287263891364238929"));
}

TEST(IntegerTests, postIncrementOperatorTest) {
  Integer a = 5;
  EXPECT_EQ(a++, 5);
  EXPECT_EQ(a, 6);

  Integer b("4632819374289745632874563287263891364238928");
  EXPECT_EQ(b++, Integer("4632819374289745632874563287263891364238928"));
  EXPECT_EQ(b, Integer("4632819374289745632874563287263891364238929"));
}

TEST(IntegerTests, preDecrementOperatorTest) {
  EXPECT_EQ(--Integer(5), 4);
  EXPECT_EQ(--Integer("4632819374289745632874563287263891364238928"),
            Integer("4632819374289745632874563287263891364238927"));
}

TEST(IntegerTests, postDecrementOperatorTest) {
  Integer a = 5;
  EXPECT_EQ(a--, 5);
  EXPECT_EQ(a, 4);

  Integer b("4632819374289745632874563287263891364238928");
  EXPECT_EQ(b--, Integer("4632819374289745632874563287263891364238928"));
  EXPECT_EQ(b, Integer("4632819374289745632874563287263891364238927"));
}

TEST(IntegerTests, unaryPlusOperatorTest) {
  EXPECT_EQ(+Integer(5), 5);
  EXPECT_EQ(+Integer("-6748346738212618723653728362813238128121823281328381262673676266"),
            Integer("-6748346738212618723653728362813238128121823281328381262673676266"));
}

TEST(IntegerTests, unaryMinusOperatorTest) {
  EXPECT_EQ(-Integer(5), -5);
  EXPECT_EQ(-Integer("-6748346738212618723653728362813238128121823281328381262673676266"),
            Integer("6748346738212618723653728362813238128121823281328381262673676266"));
}

TEST(IntegerTests, equalOperatorTest) {
  EXPECT_TRUE(Integer(13663) == Integer(13663));

  EXPECT_FALSE(Integer("5643879274839203876783492873448927") == Integer("-5643879274839203876783492873448927"));
  EXPECT_FALSE(Integer(13663) == Integer(298392));
}

TEST(IntegerTests, intEqualOperatorTest) {
  EXPECT_TRUE(Integer(283746) == 283746);
}

TEST(IntegerTests, friendIntEqualOperatorTest) {
  EXPECT_TRUE(283746 == Integer(283746));
}

TEST(IntegerTests, notEqualOperatorTest) {
  EXPECT_TRUE(Integer(13663) != 298392);
  EXPECT_TRUE(Integer("5643879274839203876783492873448927") != Integer("-5643879274839203876783492873448927"));

  EXPECT_FALSE(Integer(13663) != 13663);
}

TEST(IntegerTests, intNotEqualOperatorTest) {
  EXPECT_TRUE(Integer(283746) != 12121);
}

TEST(IntegerTests, friendIntNotEqualOperatorTest) {
  EXPECT_TRUE(283746 != Integer(12121));
}

TEST(IntegerTests, lessOperatorTest) {
  EXPECT_TRUE(Integer("-724627382732") < Integer("643864837483437378342"));
  EXPECT_TRUE(Integer("7236") < Integer("748274299"));
  EXPECT_TRUE(Integer("1") < Integer("10000000000000000000000000000000000"));

  EXPECT_FALSE(Integer("-7236726372") < Integer("-64283827387283728"));
  EXPECT_FALSE(Integer("7236726372") < Integer("-62736"));
}

TEST(IntegerTests, intLessOperatorTest) {
  EXPECT_TRUE(Integer(283746) < 2379264);
}

TEST(IntegerTests, friendIntLessOperatorTest) {
  EXPECT_TRUE(283746 < Integer(2379264));
}

TEST(IntegerTests, moreOperatorTest) {
  EXPECT_TRUE(Integer("-7236726372") > Integer("-64283827387283728"));
  EXPECT_TRUE(Integer("7236726372") > Integer("-727"));
  EXPECT_TRUE(Integer("7236") > Integer("483"));

  EXPECT_FALSE(Integer("-724627382732") > Integer("643864837483437378342"));
  EXPECT_FALSE(Integer("1") > Integer("10000000000000000000000000000000000"));
}

TEST(IntegerTests, intMoreOperatorTest) {
  EXPECT_TRUE(Integer(283746) > 12121);
}

TEST(IntegerTests, friendIntMoreOperatorTest) {
  EXPECT_TRUE(283746 > Integer(12121));
}

TEST(IntegerTests, lessEqualOperatorTest) {
  EXPECT_TRUE(Integer("-724627382732") <= Integer("643864837483437378342"));
  EXPECT_TRUE(Integer("-7246") <= Integer("-7246"));
  EXPECT_TRUE(Integer("1") <= Integer("10000000000000000000000000000000000"));

  EXPECT_FALSE(Integer("-7236726372") <= Integer("-64283827387283728"));
  EXPECT_FALSE(Integer("7236726372") <= Integer("0"));
  EXPECT_FALSE(Integer("7236") <= Integer("-74827"));
}

TEST(IntegerTests, intLessEqualOperatorTest) {
  EXPECT_TRUE(Integer(12121) <= 283746);
}

TEST(IntegerTests, friendIntLessEqualOperatorTest) {
  EXPECT_TRUE(12121 <= Integer(283746));
}

TEST(IntegerTests, moreEqualOperatorTest) {
  EXPECT_TRUE(Integer("-7246") >= Integer("-7246"));
  EXPECT_TRUE(Integer("-7236726372") >= Integer("-64283827387283728"));
  EXPECT_TRUE(Integer("7236726372") >= Integer("0"));
  EXPECT_TRUE(Integer("7236") >= Integer("-748274299"));

  EXPECT_FALSE(Integer("-724627382732") >= Integer("643864837483437378342"));
  EXPECT_FALSE(Integer("1") >= Integer("10000000000000000000000000000000000"));
}

TEST(IntegerTests, intMoreEqualOperatorTest) {
  EXPECT_TRUE(Integer(283746) >= 12121);
}

TEST(IntegerTests, friendIntMoreEqualOperatorTest) {
  EXPECT_TRUE(283746 >= Integer(12121));
}

TEST(IntegerTests, sqrtTest) {
  EXPECT_EQ(Integer(35).sqrt(), 5);
  EXPECT_EQ(Integer(100).sqrt(), 10);
  EXPECT_EQ(Integer(4212).sqrt(), Integer(64));

  for (const auto &iter : getTestJson().find("sqrt_tests").value()) {
    auto rhs = Integer(iter.find("rhs").value().get<std::string>());
    auto res = Integer(iter.find("res").value().get<std::string>());
    EXPECT_EQ(rhs.sqrt(), res);
  }

  EXPECT_THROW(Integer(-9289).sqrt(), std::domain_error);
}

TEST(IntegerTests, toStringTest) {
  EXPECT_EQ(Integer("618288").toString(), "618288");
  EXPECT_EQ(Integer("0").toString(), "0");
  EXPECT_EQ(Integer("-738").toString(), "-738");
}

TEST(IntegerTests, minimizeTest) {
  auto a = std::make_shared<Integer>(100);
  EXPECT_EQ(a->toString(), a->minimize()->toString());
}

static nlohmann::json &getTestJson() {
  static nlohmann::json json;
  if (json.empty()) {
    std::ifstream in("resources/numbers/integer_tests.json");
    in >> json;
  }
  return json;
}
