#ifndef ARITHMETICEXPRESSION_HPP
#define ARITHMETICEXPRESSION_HPP

#include <memory>
#include <string>

#include "fintamath/math_objects/nodes/expressions/Expression.hpp"

class ArithmeticExpression {
public:
  struct Elem {
    std::shared_ptr<MathObject> info;
    std::shared_ptr<Elem> left;
    std::shared_ptr<Elem> right;
  };

  ArithmeticExpression() = default;
  explicit ArithmeticExpression(const std::string &strExpr);

  std::shared_ptr<Elem> &getRootModifiable();

private:
  std::shared_ptr<Elem> root = std::make_shared<Elem>();
};

#endif // ARITHMETICEXPRESSION_HPP
