// #include <gtest/gtest.h>

// #include "fintamath/core/MathObjectBody.hpp"
// #include "fintamath/core/None.hpp"

// using namespace fintamath;
// using namespace detail;

// namespace {

// class ISuperParentTest {
//   FINTAMATH_CLASS_BODY(ISuperParentTest, None)

// public:
//   virtual MathObjectClass getClass() const noexcept = 0;
// };

// FINTAMATH_CLASS_IMPLEMENTATION(ISuperParentTest)

// class IParentTest1 : public ISuperParentTest {
//   FINTAMATH_CLASS_BODY(IParentTest1, ISuperParentTest)
// };

// FINTAMATH_CLASS_IMPLEMENTATION(IParentTest1)

// class IParentTest2 : public ISuperParentTest {
//   FINTAMATH_CLASS_BODY(IParentTest2, ISuperParentTest)
// };

// FINTAMATH_CLASS_IMPLEMENTATION(IParentTest2)

// class ChildTest1 : public IParentTest1 {
//   FINTAMATH_CHILD_CLASS_BODY(ChildTest1, IParentTest1)
// };

// FINTAMATH_CHILD_CLASS_IMPLEMENTATION(ChildTest1)

// class ChildTest2 : public IParentTest1 {
//   FINTAMATH_CHILD_CLASS_BODY(ChildTest2, IParentTest1)
// };

// FINTAMATH_CHILD_CLASS_IMPLEMENTATION(ChildTest2)

// class ChildTest3 : public IParentTest2 {
//   FINTAMATH_CHILD_CLASS_BODY(ChildTest3, IParentTest2)
// };

// FINTAMATH_CHILD_CLASS_IMPLEMENTATION(ChildTest3)

// class OtherChildTest : public IParentTest2 {
//   FINTAMATH_CHILD_CLASS_BODY(OtherChildTest, IParentTest2)
// };

// FINTAMATH_CHILD_CLASS_IMPLEMENTATION(OtherChildTest)

// [[maybe_unused]] const auto config = [] {
//   ISuperParentTest::registerType<IParentTest1>();
//   IParentTest1::registerType<ChildTest1>();
//   IParentTest1::registerType<ChildTest2>();
//   IParentTest2::registerType<ChildTest3>();
//   ISuperParentTest::registerType<IParentTest2>();
//   return 0;
// }();

// }

// TEST(MathObjectClassTests, constructorTest) {
//   {
//     constexpr MathObjectClassData t("Test");
//     EXPECT_EQ(t.getName(), "Test");
//     EXPECT_FALSE(t.getParent());
//   }
//   {
//     MathObjectClass t1("Test");
//     EXPECT_EQ(t1.getName(), "Test");
//     EXPECT_FALSE(t1.getParent());

//     MathObjectClass t2("Test", ISuperParentTest::getClassStatic());
//     EXPECT_EQ(t2.getName(), "Test");
//     EXPECT_EQ(t2.getParent(), ISuperParentTest::getClassStatic());
//   }
// }

// TEST(MathObjectClassTests, getNameTest) {
//   EXPECT_EQ(ChildTest1::getClassStatic()->getName(), "ChildTest1");
// }

// TEST(MathObjectClassTests, getParentTest) {
//   EXPECT_FALSE(MathObjectClass("Test").getParent());

//   EXPECT_FALSE(ISuperParentTest::getClassStatic()->getParent());

//   EXPECT_EQ(IParentTest1::getClassStatic()->getParent(), ISuperParentTest::getClassStatic());
//   EXPECT_EQ(IParentTest2::getClassStatic()->getParent(), ISuperParentTest::getClassStatic());

//   EXPECT_EQ(ChildTest1::getClassStatic()->getParent(), IParentTest1::getClassStatic());
//   EXPECT_EQ(ChildTest2::getClassStatic()->getParent(), IParentTest1::getClassStatic());
//   EXPECT_EQ(ChildTest3::getClassStatic()->getParent(), IParentTest2::getClassStatic());
// }
