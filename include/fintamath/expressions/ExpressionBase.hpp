#pragma once

#include <memory>
#include <vector>

#include "fintamath/core/MathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"

namespace fintamath {

class ExpressionBase : public MathObject {
  FINTAMATH_CLASS_BODY(ExpressionBase, MathObject)

public:
  struct ExpressionBaseDeclaration {
    MathObjectClass returnClass;
    std::vector<MathObjectClass> childClasses;
    bool isVariadic = false;
  };

  using Child = std::shared_ptr<MathObject>;
  using Children = std::vector<Child>;

protected:
  ExpressionBase() = default;

  explicit ExpressionBase(Children inChildren);

public:
  virtual const ExpressionBaseDeclaration &getDeclaration() const noexcept;

  const Children &getChildren() const noexcept;

private:
  Children children;
};

}
