#pragma once

#include <memory>
#include <vector>

#include "fintamath/core/MathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"

namespace fintamath {

class ExpressionBase : public MathObject {
  FINTAMATH_INTERFACE_BODY(ExpressionBase, MathObject)

public:
  struct ExpressionDeclaration {
    struct DomainAndRange {
      MathObjectClass returnClass;
      std::vector<MathObjectClass> childClasses;
    };

    std::vector<DomainAndRange> domainAndRangeVariants;
    bool isVariadic = false;
  };

  using Child = std::shared_ptr<MathObject>;
  using Children = std::vector<Child>;

protected:
  ExpressionBase() = default;

  explicit ExpressionBase(Children inChildren);

public:
  virtual constexpr ExpressionDeclaration getExpressionDeclaration() const noexcept = 0;

  const Children &getChildren() const noexcept;

private:
  Children children;
};

}
