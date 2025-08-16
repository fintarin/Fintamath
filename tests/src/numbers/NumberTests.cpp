// #include <gtest/gtest.h>

// #include "fintamath/numbers/INumber.hpp"

// #include "fintamath/numbers/Integer.hpp"
// #include "fintamath/numbers/Rational.hpp"

// using namespace fintamath;

// namespace {

// class TestNumber : public INumberCRTP<TestNumber> {
//   FINTAMATH_CHILD_CLASS_BODY(TestNumber, INumber)

// protected:
//   TestNumber &add(const TestNumber &rhs) override {
//     return *this;
//   }

//   TestNumber &substract(const TestNumber &rhs) override {
//     return *this;
//   }

//   TestNumber &multiply(const TestNumber &rhs) override {
//     return *this;
//   }

//   TestNumber &divide(const TestNumber &rhs) override {
//     return *this;
//   }

//   TestNumber &negate() override {
//     return *this;
//   }

//   std::strong_ordering compare(const TestNumber &rhs) const override {
//     return std::strong_ordering::less;
//   }
// };

// FINTAMATH_CHILD_CLASS_IMPLEMENTATION(TestNumber)

// [[maybe_unused]] const auto config = [] {
//   INumber::registerType<TestNumber>();
//   return 0;
// }();

// }

// TEST(INumberTests, parseTest) {
//   EXPECT_TRUE(is<TestNumber>(*INumber::parseFirst("TestNumber")));
// }

// TEST(INumberTests, addTest) {
//   const std::unique_ptr<INumber> m1 = std::make_unique<Integer>(1);
//   const std::unique_ptr<INumber> m2 = std::make_unique<Rational>(2);
//   const std::unique_ptr<INumber> m3 = std::make_unique<Rational>(1, 2);

//   EXPECT_EQ((*m1 + *m1)->toString(), "2");
//   EXPECT_EQ((*m2 + *m2)->toString(), "4");
//   EXPECT_EQ((*m1 + *m2)->toString(), "3");
//   EXPECT_EQ((*m2 + *m1)->toString(), "3");

//   EXPECT_EQ((*m1 + *m3)->toString(), "3/2");
//   EXPECT_EQ((*m2 + *m3)->toString(), "5/2");
//   EXPECT_EQ((*m3 + *m1)->toString(), "3/2");
//   EXPECT_EQ((*m3 + *m2)->toString(), "5/2");
// }

// TEST(INumberTests, subTest) {
//   const std::unique_ptr<INumber> m1 = std::make_unique<Integer>(1);
//   const std::unique_ptr<INumber> m2 = std::make_unique<Rational>(2);
//   const std::unique_ptr<INumber> m3 = std::make_unique<Rational>(1, 2);

//   EXPECT_EQ((*m1 - *m1)->toString(), "0");
//   EXPECT_EQ((*m2 - *m2)->toString(), "0");
//   EXPECT_EQ((*m1 - *m2)->toString(), "-1");
//   EXPECT_EQ((*m2 - *m1)->toString(), "1");

//   EXPECT_EQ((*m1 - *m3)->toString(), "1/2");
//   EXPECT_EQ((*m2 - *m3)->toString(), "3/2");
//   EXPECT_EQ((*m3 - *m1)->toString(), "-1/2");
//   EXPECT_EQ((*m3 - *m2)->toString(), "-3/2");
// }

// TEST(INumberTests, mulTest) {
//   const std::unique_ptr<INumber> m1 = std::make_unique<Integer>(1);
//   const std::unique_ptr<INumber> m2 = std::make_unique<Rational>(2);
//   const std::unique_ptr<INumber> m3 = std::make_unique<Rational>(1, 2);

//   EXPECT_EQ((*m1 * *m1)->toString(), "1");
//   EXPECT_EQ((*m2 * *m2)->toString(), "4");
//   EXPECT_EQ((*m1 * *m2)->toString(), "2");
//   EXPECT_EQ((*m2 * *m1)->toString(), "2");

//   EXPECT_EQ((*m1 * *m3)->toString(), "1/2");
//   EXPECT_EQ((*m2 * *m3)->toString(), "1");
//   EXPECT_EQ((*m3 * *m1)->toString(), "1/2");
//   EXPECT_EQ((*m3 * *m2)->toString(), "1");
// }

// TEST(INumberTests, divTest) {
//   const std::unique_ptr<INumber> m1 = std::make_unique<Integer>(1);
//   const std::unique_ptr<INumber> m2 = std::make_unique<Integer>(5);
//   const std::unique_ptr<INumber> m3 = std::make_unique<Rational>(2);
//   const std::unique_ptr<INumber> m4 = std::make_unique<Rational>(1, 2);

//   EXPECT_EQ((*m1 / *m2)->toString(), "1/5");

//   EXPECT_EQ((*m1 / *m1)->toString(), "1");
//   EXPECT_EQ((*m3 / *m3)->toString(), "1");
//   EXPECT_EQ((*m1 / *m3)->toString(), "1/2");
//   EXPECT_EQ((*m3 / *m1)->toString(), "2");

//   EXPECT_EQ((*m1 / *m4)->toString(), "2");
//   EXPECT_EQ((*m3 / *m4)->toString(), "4");
//   EXPECT_EQ((*m4 / *m1)->toString(), "1/2");
//   EXPECT_EQ((*m4 / *m3)->toString(), "1/4");
// }

// TEST(INumberTests, convertTest) {
//   const std::unique_ptr<INumber> m1 = std::make_unique<Integer>(1);
//   EXPECT_EQ((+*m1)->toString(), "1");
//   EXPECT_TRUE(is<INumber>(+*m1));
// }

// TEST(INumberTests, negateTest) {
//   const std::unique_ptr<INumber> m1 = std::make_unique<Integer>(1);
//   EXPECT_EQ((-*m1)->toString(), "-1");
//   EXPECT_TRUE(is<INumber>(+*m1));
// }

// TEST(INumberTests, getClassTest) {
//   EXPECT_EQ(INumber::getClassStatic()->getName(), "INumber");
//   EXPECT_EQ(INumber::getClassStatic()->getParent(), IComparable::getClassStatic());
// }
