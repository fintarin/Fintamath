#pragma once

#include <memory>
#include <vector>

#include "fintamath/core/IMathObject.hpp"
#include "fintamath/core/MathObjectClass.hpp"

namespace fintamath {

class IExpression : public IMathObject {
  FINTAMATH_INTERFACE_BODY(IExpression, IMathObject)

public:
  struct ExpressionDeclaration {
    struct DomainAndRange {
      MathObjectClass returnClass = {};
      std::vector<MathObjectClass> childClasses;
    };

    std::vector<DomainAndRange> domainAndRangeVariants;
    bool isVariadic = false;
  };

  using Child = std::shared_ptr<const IMathObject>;
  using Children = std::vector<Child>;

protected:
  IExpression() = default;

  explicit IExpression(Children inChildren);

public:
  virtual const ExpressionDeclaration &getExpressionDeclaration() const noexcept = 0;

  const Children &getChildren() const noexcept;

private:
  Children children;
};

}
