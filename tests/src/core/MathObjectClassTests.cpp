#include <gtest/gtest.h>

#include "fintamath/core/MathObjectBody.hpp"

using namespace fintamath;
using namespace detail;

namespace {

class ISuperParentTest {
  FINTAMATH_PARENT_CLASS_BODY(ISuperParentTest)
};

FINTAMATH_PARENT_CLASS_IMPLEMENTATION(ISuperParentTest)

class IParentTest1 : public ISuperParentTest {
  FINTAMATH_PARENT_CLASS_BODY(IParentTest1)
};

FINTAMATH_PARENT_CLASS_IMPLEMENTATION(IParentTest1)

class IParentTest2 : public ISuperParentTest {
  FINTAMATH_PARENT_CLASS_BODY(IParentTest2)
};

FINTAMATH_PARENT_CLASS_IMPLEMENTATION(IParentTest2)

class ChildTest1 : public IParentTest1 {
  FINTAMATH_CLASS_BODY(ChildTest1)
};

class ChildTest2 : public IParentTest1 {
  FINTAMATH_CLASS_BODY(ChildTest2)
};

class ChildTest3 : public IParentTest2 {
  FINTAMATH_CLASS_BODY(ChildTest3)
};

class OtherChildTest : public IParentTest2 {
  FINTAMATH_CLASS_BODY(OtherChildTest)
};

[[maybe_unused]] const auto config = [] {
  ISuperParentTest::registerType<IParentTest1>();
  IParentTest1::registerType<ChildTest1>();
  IParentTest1::registerType<ChildTest2>();
  IParentTest2::registerType<ChildTest3>();
  ISuperParentTest::registerType<IParentTest2>();
  return 0;
}();

}

TEST(MathObjectClassTests, constructorTest) {
  {
    constexpr MathObjectClass t("Test");
    EXPECT_EQ(t.getName(), "Test");
  }
  {
    MathObjectClass t("Test");
    EXPECT_EQ(t.getName(), "Test");
  }
}

TEST(MathObjectClassTests, equalsTest) {
  EXPECT_TRUE(ChildTest1::getClassStatic() == ChildTest1::getClassStatic());
  EXPECT_FALSE(ChildTest1::getClassStatic() == ChildTest2::getClassStatic());
  EXPECT_FALSE(ChildTest2::getClassStatic() == ChildTest1::getClassStatic());
}

TEST(MathObjectClassTests, compareTest) {
  EXPECT_EQ(ChildTest1::getClassStatic() <=> ChildTest1::getClassStatic(), std::strong_ordering::equal);
  EXPECT_EQ(ChildTest1::getClassStatic() <=> ChildTest2::getClassStatic(), std::strong_ordering::less);
  EXPECT_EQ(ChildTest2::getClassStatic() <=> ChildTest1::getClassStatic(), std::strong_ordering::greater);
}

TEST(MathObjectClassTests, getNameTest) {
  EXPECT_EQ(ChildTest1::getClassStatic().getName(), "ChildTest1");
}

TEST(MathObjectClassTests, getParentTest) {
  EXPECT_FALSE(MathObjectClass("Test").getParent());

  EXPECT_FALSE(ISuperParentTest::getClassStatic().getParent());

  EXPECT_EQ(IParentTest1::getClassStatic().getParent(), ISuperParentTest::getClassStatic());
  EXPECT_EQ(IParentTest2::getClassStatic().getParent(), ISuperParentTest::getClassStatic());

  EXPECT_EQ(ChildTest1::getClassStatic().getParent(), IParentTest1::getClassStatic());
  EXPECT_EQ(ChildTest2::getClassStatic().getParent(), IParentTest1::getClassStatic());
  EXPECT_EQ(ChildTest3::getClassStatic().getParent(), IParentTest2::getClassStatic());
}

TEST(MathObjectClassTests, getChildrenTest) {
  EXPECT_EQ(MathObjectClass("Test").getChildren().size(), 0);

  EXPECT_EQ(ISuperParentTest::getClassStatic().getChildren().size(), 2);

  EXPECT_EQ(IParentTest1::getClassStatic().getChildren().size(), 2);
  EXPECT_EQ(IParentTest2::getClassStatic().getChildren().size(), 1);

  EXPECT_EQ(ChildTest1::getClassStatic().getChildren().size(), 0);
  EXPECT_EQ(ChildTest2::getClassStatic().getChildren().size(), 0);
  EXPECT_EQ(ChildTest3::getClassStatic().getChildren().size(), 0);
}

TEST(MathObjectClassTests, getChildrenRecursiveTest) {
  EXPECT_EQ(MathObjectClass("Test").getChildren(true).size(), 0);

  EXPECT_EQ(ISuperParentTest::getClassStatic().getChildren(true).size(), 5);

  EXPECT_EQ(IParentTest1::getClassStatic().getChildren(true).size(), 2);
  EXPECT_EQ(IParentTest2::getClassStatic().getChildren(true).size(), 1);

  EXPECT_EQ(ChildTest1::getClassStatic().getChildren(true).size(), 0);
  EXPECT_EQ(ChildTest2::getClassStatic().getChildren(true).size(), 0);
  EXPECT_EQ(ChildTest3::getClassStatic().getChildren(true).size(), 0);
}

TEST(MathObjectClassTests, bindTypesTest) {
  EXPECT_FALSE(OtherChildTest::getClassStatic().getParent());

  MathObjectClass::bindTypes<IParentTest2, OtherChildTest>();

  EXPECT_EQ(OtherChildTest::getClassStatic().getParent(), IParentTest2::getClassStatic());
}

TEST(MathObjectClassTests, hashTest) {
  EXPECT_EQ(std::hash<MathObjectClass>{}(MathObjectClass("Test")),
            std::hash<MathObjectClass::Name>{}("Test"));
}
