// #include <gtest/gtest.h>

// #include "fintamath/core/Parser.hpp"

// #include "fintamath/Expression.hpp"
// #include "fintamath/functions/IFunction.hpp"
// #include "fintamath/functions/arithmetic/AddOper.hpp"
// #include "fintamath/constants/E.hpp"
// #include "fintamath/numbers/INumber.hpp"
// #include "fintamath/numbers/Integer.hpp"

// using namespace fintamath;

// template <typename Class, typename String>
// size_t countParseredValues(String &&str) {
//   size_t count = 0;

//   for (const auto &_ : Class::parse(std::forward<String>(str))) {
//     count++;
//   }

//   return count;
// }

// TEST(ParserTests, parseLvalueTest) {
//   std::string str;

//   str = "123";
//   EXPECT_EQ(countParseredValues<INumber>(str), 4);

//   str = "+";
//   EXPECT_EQ(countParseredValues<IFunction>(str), 2);

//   str = "E";
//   EXPECT_EQ(countParseredValues<ILiteral>(str), 1);

//   str = "1+2";
//   EXPECT_EQ(countParseredValues<IMathObject>(str), 1);

//   str = "1*)";
//   EXPECT_EQ(countParseredValues<IMathObject>(str), 0);
// }

// TEST(ParserTests, parseRvalueTest) {
//   EXPECT_EQ(countParseredValues<INumber>("123"), 4);
//   EXPECT_EQ(countParseredValues<IFunction>("+"), 2);
//   EXPECT_EQ(countParseredValues<ILiteral>("E"), 1);
//   EXPECT_EQ(countParseredValues<IMathObject>("1+2"), 1);
//   EXPECT_EQ(countParseredValues<IMathObject>("1*)"), 0);
// }

// TEST(ParserTests, parseFirstTest) {
//   EXPECT_EQ(IMathObject::parseFirst("123").value()->getClass(), Integer::getClassStatic());
//   EXPECT_EQ(IMathObject::parseFirst("+").value()->getClass(), AddOper::getClassStatic());
//   EXPECT_EQ(IMathObject::parseFirst("E").value()->getClass(), E::getClassStatic());
//   EXPECT_EQ(IMathObject::parseFirst("1+1").value()->getClass(), Expression::getClassStatic());
//   EXPECT_FALSE(IMathObject::parseFirst("1*)"));
// }

// TEST(ParserTests, registerTypeTest) {
//   // TODO: implement
// }